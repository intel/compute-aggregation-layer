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
#include "shared/synchronization.h"

#include <thread>

namespace Cal::Client::Icd::LevelZero {

ze_result_t zeEventPoolGetIpcHandle(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t *phIpc) {
    const auto rpcCommandResult = zeEventPoolGetIpcHandleRpcHelper(hEventPool, phIpc);
    if (rpcCommandResult != ZE_RESULT_SUCCESS) {
        return rpcCommandResult;
    }

    return Cal::Client::Icd::LevelZero::Ipc::toLocalFds("zeEventPoolGetIpcHandle", 1u, phIpc);
}

ze_result_t zeEventPoolOpenIpcHandle(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t *phEventPool) {
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::toRemoteFds("zeEventPoolOpenIpcHandle", 1u, &hIpc);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    return zeEventPoolOpenIpcHandleRpcHelper(hContext, hIpc, phEventPool);
}

ze_result_t zeEventPoolPutIpcHandle(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc) {
    Cal::Utils::LocalFd localFd{*(int *)hIpc.data};
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::toRemoteFds("zeEventPoolPutIpcHandle", 1u, &hIpc);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    auto *globalL0Platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    if (globalL0Platform->decreaseRefcountForIpcFd(Cal::Utils::RemoteFd(*reinterpret_cast<int *>(hIpc.data)))) {
        Cal::Sys::close(localFd.fd);
    }

    return zeEventPoolPutIpcHandleRpcHelper(hContext, hIpc);
}

ze_result_t zeEventHostSynchronize(ze_event_handle_t hEvent, uint64_t timeout) {
    return Cal::Utils::waitForCompletionWithTimeout<std::chrono::nanoseconds>(hEvent, std::chrono::nanoseconds(timeout), zeEventHostSynchronizeRpcHelper,
                                                                              ZE_RESULT_SUCCESS, ZE_RESULT_NOT_READY);
}

} // namespace Cal::Client::Icd::LevelZero
