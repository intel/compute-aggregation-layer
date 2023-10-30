/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/icd_global_state.h"
#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "icd_level_zero_ipc_helpers.h"

namespace Cal::Icd::LevelZero {

ze_result_t zexMemGetIpcHandles(ze_context_handle_t hContext, const void *ptr, uint32_t *numIpcHandles, ze_ipc_mem_handle_t *pIpcHandles) {
    const auto rpcCommandResult = zexMemGetIpcHandlesRpcHelper(hContext, ptr, numIpcHandles, pIpcHandles);
    if (rpcCommandResult != ZE_RESULT_SUCCESS || pIpcHandles == nullptr) {
        return rpcCommandResult;
    }

    constexpr const char *functionName = "zexMemGetIpcHandles";
    return Cal::Icd::LevelZero::Ipc::translateIpcHandles(functionName, *numIpcHandles, pIpcHandles);
}

ze_result_t zexMemOpenIpcHandles(ze_context_handle_t hContext,
                                 ze_device_handle_t hDevice,
                                 uint32_t numIpcHandles,
                                 ze_ipc_mem_handle_t *pIpcHandles,
                                 ze_ipc_memory_flags_t flags,
                                 void **pptr) {
    if (pIpcHandles == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if (numIpcHandles == 0) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    // Do not modify data passed by user.
    // Before calling real API the IPC handles need to be translated.
    std::vector<ze_ipc_mem_handle_t> ipcHandles(numIpcHandles);
    std::memcpy(ipcHandles.data(), pIpcHandles, numIpcHandles);

    constexpr const char *functionName = "zexMemOpenIpcHandles";
    const auto reverseTranslationResult = Cal::Icd::LevelZero::Ipc::reverseTranslateIpcHandles(functionName, numIpcHandles, ipcHandles.data());
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    return zexMemOpenIpcHandlesRpcHelper(hContext, hDevice, numIpcHandles, ipcHandles.data(), flags, pptr);
}

} // namespace Cal::Icd::LevelZero
