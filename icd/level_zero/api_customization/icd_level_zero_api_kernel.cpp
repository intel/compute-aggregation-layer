/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/api_type_wrapper/kernel_wrapper.h"
#include "icd/level_zero/logic/properties_cache.h"
#include "icd_level_zero_api.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeKernelSetArgumentValue(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void *pArgValue) {
    auto l0Kernel = static_cast<IcdL0Kernel *>(hKernel);
    l0Kernel->storeKernelArg(pArgValue, argIndex);

    auto cacheEnabled = Cal::Icd::icdGlobalState.isCacheEnabled();
    if (!cacheEnabled) {
        return zeKernelSetArgumentValueRpcHelper(hKernel, argIndex, argSize, pArgValue);
    }

    auto cacheRet = l0Kernel->zeKernelSetArgumentValueCache.findCachedKernelArg(argIndex, argSize, pArgValue);
    if (cacheRet != l0Kernel->zeKernelSetArgumentValueCache.cache.end()) {
        return ZE_RESULT_SUCCESS;
    }

    l0Kernel->zeKernelSetArgumentValueCache.cacheKernelArg(argIndex, argSize, pArgValue);
    return zeKernelSetArgumentValueRpcHelper(hKernel, argIndex, argSize, pArgValue);
}

ze_result_t zeKernelGetProperties(ze_kernel_handle_t hKernel, ze_kernel_properties_t *pKernelProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Kernel *>(hKernel), pKernelProperties, zeKernelGetPropertiesRpcHelper);
}

ze_result_t zeKernelSetGroupSize(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
    auto l0Kernel = static_cast<IcdL0Kernel *>(hKernel);
    if (groupSizeX == l0Kernel->groupSize.x &&
        groupSizeY == l0Kernel->groupSize.y &&
        groupSizeZ == l0Kernel->groupSize.z) {
        return ZE_RESULT_SUCCESS;
    }
    l0Kernel->groupSize.x = groupSizeX;
    l0Kernel->groupSize.y = groupSizeY;
    l0Kernel->groupSize.z = groupSizeZ;
    return zeKernelSetGroupSizeRpcHelper(hKernel, groupSizeX, groupSizeY, groupSizeZ);
}

ze_result_t zeKernelSuggestGroupSize(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t *groupSizeX, uint32_t *groupSizeY, uint32_t *groupSizeZ) {
    auto l0Kernel = static_cast<IcdL0Kernel *>(hKernel);
    if (l0Kernel->obtainSuggestedGroupSizes(globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ)) {
        return ZE_RESULT_SUCCESS;
    }
    auto ret = zeKernelSuggestGroupSizeRpcHelper(hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
    l0Kernel->storeSuggestedGroupSizes(globalSizeX, globalSizeY, globalSizeZ, *groupSizeX, *groupSizeY, *groupSizeZ);
    return ret;
}

} // namespace Cal::Icd::LevelZero
