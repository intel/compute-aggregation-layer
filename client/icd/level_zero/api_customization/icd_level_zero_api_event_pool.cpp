/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "icd_level_zero_ipc_helpers.h"
#include "shared/log.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zeEventPoolGetIpcHandle(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t *phIpc) {
    const auto rpcCommandResult = zeEventPoolGetIpcHandleRpcHelper(hEventPool, phIpc);
    if (rpcCommandResult != ZE_RESULT_SUCCESS) {
        return rpcCommandResult;
    }

    return Cal::Client::Icd::LevelZero::Ipc::translateIpcHandles("zeEventPoolGetIpcHandle", 1u, phIpc);
}

ze_result_t zeEventPoolOpenIpcHandle(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t *phEventPool) {
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::reverseTranslateIpcHandles("zeEventPoolOpenIpcHandle", 1u, &hIpc);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    return zeEventPoolOpenIpcHandleRpcHelper(hContext, hIpc, phEventPool);
}

} // namespace Cal::Client::Icd::LevelZero
