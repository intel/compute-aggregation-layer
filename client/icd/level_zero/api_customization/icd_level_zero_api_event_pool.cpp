/*
 * Copyright (C) 2022-2024 Intel Corporation
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

ze_result_t zeEventHostSynchronize(ze_event_handle_t hEvent, uint64_t timeout) {
    using namespace std::literals::chrono_literals;
    uint64_t pollingThreshold = std::chrono::nanoseconds(1s).count();
    uint64_t pollingTimeout = (timeout < pollingThreshold) ? timeout : pollingThreshold;
    uint64_t totalWaited = 0;
    while (true) {
        log<Verbosity::debug>("Establishing RPC for zeEventHostSynchronize with timeout %llu - polling timeout %llu, totalWaited %llu", timeout, pollingTimeout, totalWaited);
        auto result = zeEventHostSynchronizeRpcHelper(hEvent, pollingTimeout);
        if (result == ZE_RESULT_SUCCESS) {
            log<Verbosity::debug>("zeEventHostSynchronize returned ZE_RESULT_SUCCESS - totalWaited %llu", pollingTimeout + totalWaited);
            return ZE_RESULT_SUCCESS;
        }
        if (result != ZE_RESULT_NOT_READY) {
            log<Verbosity::debug>("zeEventHostSynchronize failed with error code %d", static_cast<int>(result));
            return result;
        }
        totalWaited += pollingTimeout;
        if (totalWaited >= timeout) {
            log<Verbosity::debug>("zeEventHostSynchronize returned ZE_RESULT_NOT_READY - totalWaited %llu >= timeout %llu", totalWaited, timeout);
            return ZE_RESULT_NOT_READY;
        }
    }
}

} // namespace Cal::Client::Icd::LevelZero
