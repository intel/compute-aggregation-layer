/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_global_state.h"

#include "client/client_malloc_override.h"
#include "client/icd/icd_ocl.h"
#include "client/icd/icd_page_fault_manager.h"
#include "client/icd/level_zero/icd_level_zero.h"
#include "generated_icd_level_zero.h"
#include "generated_icd_ocl.h"
#include "shared/ipc.h"
#include "shared/log.h"
#include "shared/rpc.h"
#include "shared/shmem.h"

#include <unistd.h>

namespace Cal::Client::Icd {

IcdGlobalState *icdGlobalStateStorage = new IcdGlobalState;
IcdGlobalState &icdGlobalState = *icdGlobalStateStorage;
IcdGlobalState::IcdGlobalState() {
    this->enableCache = Cal::Utils::getCalEnvFlag(calIcdEnableCacheEnvName, true);
    tracingEnabled = Cal::Utils::getCalEnvFlag("ZET_ENABLE_API_TRACING_EXP", false);
    if (tracingEnabled) {
        log<Verbosity::performance>("API tracing requires turning async calls off");
        Cal::Sys::setenv("CAL_ASYNC_CALLS", "0", true);
    }
}

IcdGlobalState::~IcdGlobalState() = default;

Cal::Client::Icd::Ocl::IcdOclPlatform *IcdGlobalState::getOclPlatform() {
    std::call_once(oclPlatform.onceFlag, [this]() {
        if (this->ensureApiIsAvailable(ApiType::OpenCL) == false) {
            return;
        }
        Cal::Client::Icd::Ocl::initOclIcdDispatchTable(clIcdDispatchTable);
        log<Verbosity::info>("Creating Compute Aggregation Layer OCL platform from pid : %d", getpid());
        this->oclPlatform.platform = std::make_unique<Icd::Ocl::IcdOclPlatform>(*this);
    });
    return oclPlatform.platform.get();
}

Cal::Client::Icd::LevelZero::IcdL0Platform *IcdGlobalState::getL0Platform() {
    std::call_once(l0Platform.onceFlag, [this]() {
        if (this->ensureApiIsAvailable(ApiType::LevelZero) == false) {
            log<Verbosity::debug>("L0 API is not available for client with pid : %d", getpid());
            return;
        }
        Cal::Client::Icd::LevelZero::initL0Ddi(l0Ddi);
        log<Verbosity::info>("Creating Compute Aggregation Layer Level Zero platform from pid : %d", getpid());
        this->l0Platform.platform = std::make_unique<Icd::LevelZero::IcdL0Platform>(*this);
    });
    return l0Platform.platform.get();
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

void IcdGlobalState::connect() {
    ClientConnection::connect();
    if (connectionTraits.isConnected) {
        this->pageFaultManager = std::make_unique<Cal::Client::Icd::PageFaultManager>(*this->connection);
    }
}

IcdGlobalsRegistryAtExitWatcher icdGlobalsRegistryAtExitWatcher;

} // namespace Cal::Client::Icd
