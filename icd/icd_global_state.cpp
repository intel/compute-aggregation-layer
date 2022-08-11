/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_global_state.h"

#include "generated_icd_level_zero.h"
#include "generated_icd_ocl.h"
#include "icd/icd_level_zero.h"
#include "icd/icd_ocl.h"
#include "shared/log.h"
#include "shared/shmem.h"

#include <unistd.h>

namespace Cal {
namespace Icd {

IcdGlobalState *icdGlobalStateStorage = new IcdGlobalState;
IcdGlobalState &icdGlobalState = *icdGlobalStateStorage;
IcdGlobalState::IcdGlobalState() {
    this->shmemManager = std::make_unique<Cal::Ipc::ShmemManager>();
    this->mallocShmemZeroCopyManager = std::make_unique<Cal::Ipc::MallocShmemZeroCopyManager>();

    this->enableCache = Cal::Utils::getCalEnvFlag(calIcdEnableCacheEnvName);
}
IcdGlobalState::~IcdGlobalState() {
    this->cache.clear();
}

Cal::Icd::Ocl::IcdOclPlatform *IcdGlobalState::getOclPlatform() {
    std::call_once(oclPlatform.onceFlag, [this]() {
        Cal::Utils::initDynamicVerbosity();
        Cal::Icd::Ocl::initOclIcdDispatchTable(clIcdDispatchTable);
        log<Verbosity::info>("Creating Compute Aggregation Layer OCL platform from pid : %d", getpid());
        this->oclPlatform.platform = std::make_unique<Icd::Ocl::IcdOclPlatform>(*shmemManager, *mallocShmemZeroCopyManager);
        if (false == this->oclPlatform.platform->valid()) {
            this->oclPlatform.platform.reset();
        }
    });
    return oclPlatform.platform.get();
}

Cal::Icd::LevelZero::IcdL0Platform *IcdGlobalState::getL0Platform() {
    std::call_once(l0Platform.onceFlag, [this]() {
        Cal::Utils::initDynamicVerbosity();
        Cal::Icd::LevelZero::initL0Ddi(l0Dddi);
        log<Verbosity::info>("Creating Compute Aggregation Layer Level Zero platform from pid : %d", getpid());
        this->l0Platform.platform = std::make_unique<Icd::LevelZero::IcdL0Platform>(*shmemManager, *mallocShmemZeroCopyManager);
        if (false == this->l0Platform.platform->valid()) {
            this->l0Platform.platform.reset();
        }
    });
    return l0Platform.platform.get();
}

IcdGlobalsRegistryAtExitWatcher icdGlobalsRegistryAtExitWatcher;

} // namespace Icd
} // namespace Cal
