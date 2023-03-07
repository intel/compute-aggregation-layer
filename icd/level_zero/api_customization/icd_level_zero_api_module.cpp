/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd/level_zero/logic/properties_cache.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeModuleGetProperties(ze_module_handle_t hModule, ze_module_properties_t *pModuleProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Module *>(hModule), pModuleProperties, zeModuleGetPropertiesRpcHelper);
}

ze_result_t zeModuleGetKernelNames(ze_module_handle_t hModule, uint32_t *pCount, const char **pNames) {
    auto icdModule = static_cast<IcdL0Module *>(hModule);
    if (!icdModule) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (!pCount) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if (*pCount == 0) {
        return icdModule->getKernelNamesCount(pCount);
    }

    return icdModule->getKernelNames(pCount, pNames);
}

} // namespace Cal::Icd::LevelZero
