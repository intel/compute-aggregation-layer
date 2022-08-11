/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_platform.h"

#include "generated_icd_ocl.h"
#include "generated_rpc_messages_ocl.h"
#include "icd/icd_global_state.h"
#include "include/cal.h"
#include "shared/log.h"
#include "shared/usm.h"

#include <CL/cl_ext.h>
#include <cstring>

namespace Cal {
namespace Icd {

void IcdPlatform::initializeConnection() {
    auto connectionFactory = createConnectionFactory();
    log<Verbosity::debug>("Connecting to CAL service");
    auto connectionPathEnv = Cal::Utils::getCalEnv(calListenerSocketPathEnvName);
    if (connectionPathEnv) {
        socketPath = std::string(connectionPathEnv);
    }
    this->connection = connectionFactory->connect(getSocketPath());
    if (nullptr == this->connection) {
        log<Verbosity::debug>("Could not connect to CAL service");
        return;
    } else {
        log<Verbosity::debug>("Connected to CAL service");
    }

    log<Verbosity::debug>("Performing handshake");
    if (false == this->connection->send(Cal::Messages::ReqHandshake(Cal::Messages::ReqHandshake::ocl))) {
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
    this->shmemManager.setShmemPathBase(Cal::Ipc::getCalShmemPathBase(serviceConfig.pid));

    this->mallocShmemZeroCopyManager.loadLibrary(serviceConfig.mallocShmemLibraryPath);
    if (this->mallocShmemZeroCopyManager.isAvailable()) {
        log<Verbosity::debug>("Exporting user address space for zero-copy sharing of user allocated memory (malloc)");
        if (false == this->mallocShmemZeroCopyManager.exportUserAddressSpace()) {
            log<Verbosity::debug>("Failed to export user address space for zero-copy sharing of user allocated memory (malloc)");
        } else {
            Cal::Messages::ReqImportAddressSpace reqImportAddressSpace;
            reqImportAddressSpace.addressSpace = this->mallocShmemZeroCopyManager.getExportedUserAddressSpace();
            log<Verbosity::debug>("Sending exported user address space handle %ld to service", reqImportAddressSpace.addressSpace);
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

            this->allowedToUseZeroCopyForMallocShmem = respImportAddressSpace.allowedToUseZeroCopyForMallocShmem;
            if (respImportAddressSpace.allowedToUseZeroCopyForMallocShmem) {
                log<Verbosity::performance>("Service has allowed to use zero-copy haring for user allocated memory (malloc) ");
                log<Verbosity::info>("Service has allowed to use zero-copy sharing for user allocated memory (malloc) ");
            } else {
                log<Verbosity::performance>("Service has allowed to use zero-copy haring for user allocated memory (malloc) ");
                log<Verbosity::debug>("Service has denied the use of zero-copy sharing for user allocated memory (malloc) ");
            }
        }
    }

    log<Verbosity::debug>("Negotiating initial USM heap");
    auto negotiatedUsmRangeOpt = Cal::Usm::negotiateUsmRangeWithService(*this->connection, nullptr, 0U);
    if (!negotiatedUsmRangeOpt) {
        log<Verbosity::critical>("Failed to negotiate initial USM heap");
        this->connection.reset();
        return;
    }
    this->usmHeaps.heaps.push_back(negotiatedUsmRangeOpt.value());
    log<Verbosity::debug>("Initial USM heap negotiated successfully, base : %p, size : %zu", this->usmHeaps.heaps[0].base(), this->usmHeaps.heaps[0].size());
    log<Verbosity::info>("USM HEAP : %p - %p (size : %zx)", this->usmHeaps.heaps[0].base(), Cal::Utils::moveByBytes(this->usmHeaps.heaps[0].base(), this->usmHeaps.heaps[0].size()), this->usmHeaps.heaps[0].size());

    log<Verbosity::debug>("Creating RPC channel");
    rpcChannel = std::make_unique<Cal::Rpc::ChannelClient>(*this->connection, shmemManager);
    if (false == rpcChannel->init()) {
        log<Verbosity::critical>("Failed to initialize RPC channel client");
        this->connection.reset();
        return;
    }
    log<Verbosity::debug>("Created RPC channel client");

    log<Verbosity::info>("Compute Aggregation Layer platform initialized");
}

const char *IcdPlatform::getSocketPath() {
    if (socketPath.empty()) {
        socketPath = Utils::getPathForTempFiles() + "socket";
    }

    return socketPath.c_str();
}

} // namespace Icd
} // namespace Cal
