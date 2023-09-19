/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_global_state.h"

#include "generated_icd_level_zero.h"
#include "generated_icd_ocl.h"
#include "icd/icd_malloc_override.h"
#include "icd/icd_ocl.h"
#include "icd/icd_page_fault_manager.h"
#include "icd/level_zero/icd_level_zero.h"
#include "shared/ipc.h"
#include "shared/log.h"
#include "shared/rpc.h"
#include "shared/shmem.h"

#include <unistd.h>

namespace Cal {
namespace Icd {

IcdGlobalState *icdGlobalStateStorage = new IcdGlobalState;
IcdGlobalState &icdGlobalState = *icdGlobalStateStorage;
IcdGlobalState::IcdGlobalState() {
    Cal::Utils::initDynamicVerbosity();
    this->enableCache = Cal::Utils::getCalEnvFlag(calIcdEnableCacheEnvName, true);
    this->usesSharedVaForRpcChannel = Cal::Utils::getCalEnvFlag(calUseSharedVaForRpcChannel, false);
    auto cpuInfoOpt = cpuInfo.read();
    if (cpuInfoOpt) {
        this->cpuInfo = cpuInfoOpt.value();
        log<Verbosity::debug>("Cpu virtual address bits : %d", this->cpuInfo.virtual_);
    } else {
        log<Verbosity::error>("Could not read information about the CPU virtual address bits - will have impact on USM device memory");
    }
}

IcdGlobalState::~IcdGlobalState() {
    log<Verbosity::debug>("Performing cleanup of initial USM heap (base : %p, size : %zu)", initialUsmHeap.base(), initialUsmHeap.size());
    if (-1 == Cal::Sys::munmap(initialUsmHeap.base(), initialUsmHeap.size())) {
        log<Verbosity::error>("Failed to munamp USM heap (base : %p, size : %zu)", initialUsmHeap.base(), initialUsmHeap.size());
    }
}

Cal::Icd::Ocl::IcdOclPlatform *IcdGlobalState::getOclPlatform() {
    std::call_once(oclPlatform.onceFlag, [this]() {
        if (this->ensureApiIsAvailable(ApiType::OpenCL) == false) {
            return;
        }
        Cal::Icd::Ocl::initOclIcdDispatchTable(clIcdDispatchTable);
        log<Verbosity::info>("Creating Compute Aggregation Layer OCL platform from pid : %d", getpid());
        this->oclPlatform.platform = std::make_unique<Icd::Ocl::IcdOclPlatform>(*this);
    });
    return oclPlatform.platform.get();
}

Cal::Icd::LevelZero::IcdL0Platform *IcdGlobalState::getL0Platform() {
    std::call_once(l0Platform.onceFlag, [this]() {
        if (this->ensureApiIsAvailable(ApiType::LevelZero) == false) {
            log<Verbosity::debug>("L0 API is not available for client with pid : %d", getpid());
            return;
        }
        Cal::Icd::LevelZero::initL0Ddi(l0Ddi);
        log<Verbosity::info>("Creating Compute Aggregation Layer Level Zero platform from pid : %d", getpid());
        this->l0Platform.platform = std::make_unique<Icd::LevelZero::IcdL0Platform>(*this);
    });
    return l0Platform.platform.get();
}

std::unique_ptr<Cal::Ipc::ClientConnectionFactory> IcdGlobalState::createConnectionFactory() {
    log<Verbosity::debug>("Creating connection factory based on local named socket");
    return std::make_unique<Cal::Ipc::NamedSocketClientConnectionFactory>();
}

bool IcdGlobalState::ensureServiceIsAvailable() {
    if (connectionTraits.isConnected) {
        return true;
    }

    std::call_once(connectionTraits.onceFlag, [this]() { this->connect(); });

    return connectionTraits.isConnected;
}

bool IcdGlobalState::ensureApiIsAvailable(ApiType api) {
    if (false == ensureServiceIsAvailable()) {
        log<Verbosity::debug>("CAL service is not available for client with pid : %d", getpid());
        return false;
    }

    log<Verbosity::debug>("Checking if %s API is available on service side", asStr(api));
    auto connectionLock = this->connection->lock();
    if (false == this->connection->send(Cal::Messages::ReqCheckApiAvailability(api))) {
        log<Verbosity::critical>("Failed to check availability of %s API on service side", asStr(api));
        return false;
    }
    Cal::Messages::RespCheckApiAvailability respApiAvailability;
    if ((false == this->connection->receive(respApiAvailability)) || respApiAvailability.isInvalid()) {
        log<Verbosity::critical>("Failed to check availability of %s API on service side", asStr(api));
        return false;
    }

    log<Verbosity::info>("%s API is %s in CAL service", asStr(api), respApiAvailability.available ? "available" : "NOT available");

    return respApiAvailability.available;
}

void serviceDebugBreak(uint64_t thisClientOrdinal) {
    auto breakOrdinal = Cal::Utils::getCalEnvI64(calDebugBreakClientOrdinalEnvName, -1);
    if (breakOrdinal < 0) {
        return;
    }

    if (static_cast<uint64_t>(breakOrdinal) != thisClientOrdinal) {
        return;
    }

    auto pid = getpid();
    log<Verbosity::critical>("Entering debug break mode for client ordinal : %lld, pid : %d, (ppid : %d)", thisClientOrdinal, pid, getppid());
    while (Cal::Utils::isDebuggerConnected() == false) {
        log<Verbosity::critical>("Waiting for debugger on pid %d (e.g. gdb -p %d)", pid, pid);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5s);
    }
    log<Verbosity::critical>("Debugger connected");
}

void IcdGlobalState::connect() {
    auto connectionFactory = createConnectionFactory();
    log<Verbosity::debug>("Connecting to CAL service");
    auto connectionPathEnv = Cal::Utils::getCalEnv(calListenerSocketPathEnvName);
    if (connectionPathEnv) {
        this->connectionTraits.socketPath = std::string(connectionPathEnv);
    }
    this->connection = connectionFactory->connect(getSocketPath());
    if (nullptr == this->connection) {
        log<Verbosity::debug>("Could not connect to CAL service");
        return;
    } else {
        log<Verbosity::debug>("Connected to CAL service");
    }

    log<Verbosity::debug>("Performing handshake");
    if (false == this->connection->send(Cal::Messages::ReqHandshake(true))) {
        log<Verbosity::critical>("Handshake with Compute Aggregation Layer service failed");
        this->connection.reset();
        return;
    }
    Cal::Messages::RespHandshake serviceConfig;
    if ((false == this->connection->receive(serviceConfig)) || serviceConfig.isInvalid()) {
        log<Verbosity::critical>("Failed to read Compute Aggregation Layer service config");
        this->connection.reset();
        return;
    }
    log<Verbosity::debug>("Handshake successful (CAL service pid : %d)", serviceConfig.pid);
    this->globalShmemImporter = std::make_unique<Cal::Ipc::ShmemImporter>(Cal::Ipc::getCalShmemPathBase(serviceConfig.pid));
    this->usmShmemImporter = std::make_unique<Cal::Usm::UsmShmemImporter>(*this->globalShmemImporter);

    serviceDebugBreak(serviceConfig.assignedClientOrdinal);

    this->mallocShmemExporter = std::make_unique<Cal::Icd::MallocOverride::MallocShmemExporter>();
    if (this->mallocShmemExporter->isAllowed()) {
        log<Verbosity::debug>("Exporting user address space for zero-copy sharing of user allocated memory (malloc)");
        Cal::Messages::ReqImportAddressSpace reqImportAddressSpace;
        strncpy(reqImportAddressSpace.mallocShmemResourcePath, this->mallocShmemExporter->getResourcePath(), sizeof(reqImportAddressSpace.mallocShmemResourcePath) - 1);
        reqImportAddressSpace.clientAddressSpaceBaseAddress = reinterpret_cast<uintptr_t>(this->mallocShmemExporter->getHeapBaseAddress());
        reqImportAddressSpace.clientAddressSpaceSize = this->mallocShmemExporter->getHeapCapacity();
        log<Verbosity::debug>("Sending exported user address space resource %p to service", reqImportAddressSpace.mallocShmemResourcePath);
        if (false == this->connection->send(reqImportAddressSpace)) {
            log<Verbosity::critical>("Failed to send request to import client address space");
            this->connection.reset();
            return;
        }

        Cal::Messages::RespImportAddressSpace respImportAddressSpace;
        if ((false == this->connection->receive(respImportAddressSpace)) || respImportAddressSpace.isInvalid()) {
            log<Verbosity::critical>("Failed to read response for request of importing client address space");
            this->connection.reset();
            return;
        }

        this->connectionTraits.isZeroCopyForMallocShmemAllowed = respImportAddressSpace.successfullyImported;
        if (respImportAddressSpace.successfullyImported) {
            log<Verbosity::performance>("Service has allowed to use zero-copy sharing for user allocated memory (malloc) ");
            log<Verbosity::info>("Service has allowed to use zero-copy sharing for user allocated memory (malloc) ");
            this->mallocShmemExporter->setRemoteHeapBaseAddress(respImportAddressSpace.serviceBaseAddressForClientAddressSpace);
            this->mallocShmemExporter->enable();
        } else {
            log<Verbosity::performance>("Service has denied the use of zero-copy sharing for user allocated memory (malloc) ");
            log<Verbosity::debug>("Service has denied the use of zero-copy sharing for user allocated memory (malloc) ");
            this->mallocShmemExporter->disable();
        }
    } else {
        log<Verbosity::performance>("Could not export user address space for zero-copy sharing of user allocated memory (malloc)");
        log<Verbosity::debug>("Could not export user address space for zero-copy sharing of user allocated memory (malloc)");
    }

    log<Verbosity::debug>("Negotiating initial USM heap");
    auto negotiatedUsmRangeOpt = Cal::Usm::negotiateUsmRangeWithService(*this->connection, nullptr, 0U);
    if (!negotiatedUsmRangeOpt) {
        log<Verbosity::critical>("Failed to negotiate initial USM heap");
        this->connection.reset();
        return;
    }
    initialUsmHeap = negotiatedUsmRangeOpt.value();
    log<Verbosity::debug>("Initial USM heap negotiated successfully, base : %p, size : %zu", initialUsmHeap.base(), initialUsmHeap.size());
    log<Verbosity::info>("USM HEAP : %p - %p (size : %zx)", initialUsmHeap.base(), Cal::Utils::moveByBytes(initialUsmHeap.base(), initialUsmHeap.size()), initialUsmHeap.size());

    log<Verbosity::debug>("Creating RPC channel");
    rpcChannel = std::make_unique<Cal::Rpc::ChannelClient>(*this->connection, *this->globalShmemImporter, *this->usmShmemImporter);
    Cal::Rpc::ChannelClient::ClientSynchronizationMethod clientSynchMethod = Cal::Rpc::ChannelClient::activePolling;
    if (Cal::Utils::getCalEnvFlag(calUseSemaphoresInChannelClientEnvName, true)) {
        clientSynchMethod = Cal::Rpc::ChannelClient::semaphores;
    }
    if (Cal::Utils::getCalEnvFlag(calUseSemaphoresThresholdInChannelClientEnvName, false)) {
        clientSynchMethod = Cal::Rpc::ChannelClient::latencyBased;
    }
    if (false == rpcChannel->init(clientSynchMethod, this->usesSharedVaForRpcChannel)) {
        log<Verbosity::critical>("Failed to initialize RPC channel client");
        this->connection.reset();
        return;
    }
    log<Verbosity::debug>("Created RPC channel client");

    log<Verbosity::info>("Compute Aggregation Layer platform initialized");

    this->pageFaultManager = std::make_unique<Cal::Icd::PageFaultManager>(*this->connection);
    connectionTraits.isConnected = true;
}

const char *IcdGlobalState::getSocketPath() {
    if (connectionTraits.socketPath.empty()) {
        connectionTraits.socketPath = Utils::getPathForTempFiles() + "socket";
    }

    return connectionTraits.socketPath.c_str();
}

IcdGlobalsRegistryAtExitWatcher icdGlobalsRegistryAtExitWatcher;

} // namespace Icd
} // namespace Cal
