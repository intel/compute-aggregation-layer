/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_global_state.h"

#include "generated_icd_level_zero.h"
#include "generated_icd_ocl.h"
#include "icd/icd_ocl.h"
#include "icd/level_zero/icd_level_zero.h"
#include "shared/log.h"
#include "shared/shmem.h"

#include <unistd.h>

namespace Cal {
namespace Icd {

IcdGlobalState *icdGlobalStateStorage = new IcdGlobalState;
IcdGlobalState &icdGlobalState = *icdGlobalStateStorage;
IcdGlobalState::IcdGlobalState() {
    this->globalShmemImporter = std::make_unique<Cal::Ipc::ShmemImporter>();
    this->usmShmemImporter = std::make_unique<Cal::Usm::UsmShmemImporter>(*this->globalShmemImporter);
    this->mallocShmemZeroCopyManager = std::make_unique<Cal::Ipc::MallocShmemZeroCopyManager>();

    this->enableCache = Cal::Utils::getCalEnvFlag(calIcdEnableCacheEnvName, true);
}
IcdGlobalState::~IcdGlobalState() = default;

Cal::Icd::Ocl::IcdOclPlatform *IcdGlobalState::getOclPlatform() {
    std::call_once(oclPlatform.onceFlag, [this]() {
        Cal::Utils::initDynamicVerbosity();
        Cal::Icd::Ocl::initOclIcdDispatchTable(clIcdDispatchTable);
        log<Verbosity::info>("Creating Compute Aggregation Layer OCL platform from pid : %d", getpid());
        this->oclPlatform.platform = std::make_unique<Icd::Ocl::IcdOclPlatform>(*globalShmemImporter, *usmShmemImporter, *mallocShmemZeroCopyManager);
        if (false == this->oclPlatform.platform->valid()) {
            this->oclPlatform.platform.reset();
        }
    });
    return oclPlatform.platform.get();
}

Cal::Icd::LevelZero::IcdL0Platform *IcdGlobalState::getL0Platform() {
    std::call_once(l0Platform.onceFlag, [this]() {
        Cal::Utils::initDynamicVerbosity();
        Cal::Icd::LevelZero::initL0Ddi(l0Ddi);
        log<Verbosity::info>("Creating Compute Aggregation Layer Level Zero platform from pid : %d", getpid());
        this->l0Platform.platform = std::make_unique<Icd::LevelZero::IcdL0Platform>(*globalShmemImporter, *usmShmemImporter, *mallocShmemZeroCopyManager);
        if (false == this->l0Platform.platform->valid()) {
            this->l0Platform.platform.reset();
        }
    });
    return l0Platform.platform.get();
}

IcdGlobalsRegistryAtExitWatcher icdGlobalsRegistryAtExitWatcher;

} // namespace Icd
} // namespace Cal
