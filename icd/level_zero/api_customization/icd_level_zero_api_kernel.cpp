/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "include/cal.h"
#include "shared/log.h"

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
    return PropertiesCache::obtainProperties(static_cast<IcdL0Kernel *>(hKernel), pKernelProperties, zeKernelGetPropertiesRpcHelper);
}

} // namespace Cal::Icd::LevelZero
