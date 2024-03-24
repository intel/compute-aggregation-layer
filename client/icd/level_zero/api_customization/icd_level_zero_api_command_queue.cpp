/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/level_zero/icd_level_zero.h"
#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/synchronization.h"

namespace Cal::Client::Icd::LevelZero {

extern uint32_t calCommandQueueSynchronizePollingTimeoutDivisor;
ze_result_t zeCommandQueueCreate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t *desc, ze_command_queue_handle_t *phCommandQueue) {
    static auto isCommandQueueModeEmulatedSynchronousEnabled = Cal::Utils::getCalEnvFlag(calCommandQueueModeEmulatedSynchronousEnvName, true);
    if (isCommandQueueModeEmulatedSynchronousEnabled && ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS == desc->mode) {
        auto queueAsyncDesc = *desc;
        queueAsyncDesc.mode = ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
        auto result = zeCommandQueueCreateRpcHelper(hContext, hDevice, &queueAsyncDesc, phCommandQueue);
        if (result == ZE_RESULT_SUCCESS) {
            static_cast<IcdL0CommandQueue *>(*phCommandQueue)->setEmulatedSynchronousMode(true);
        }
        return result;
    }
    return zeCommandQueueCreateRpcHelper(hContext, hDevice, desc, phCommandQueue);
}

ze_result_t zeCommandQueueSynchronizeImpl(ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    if (calCommandQueueSynchronizePollingTimeoutDivisor == 1000) {
        return Cal::Utils::waitForCompletionWithTimeout<std::chrono::microseconds>(hCommandQueue, std::chrono::nanoseconds(timeout), zeCommandQueueSynchronizeRpcHelper,
                                                                                   ZE_RESULT_SUCCESS, ZE_RESULT_NOT_READY);
    } else {
        return Cal::Utils::waitForCompletionWithTimeout<std::chrono::nanoseconds>(hCommandQueue, std::chrono::nanoseconds(timeout), zeCommandQueueSynchronizeRpcHelper,
                                                                                  ZE_RESULT_SUCCESS, ZE_RESULT_NOT_READY);
    }
}

ze_result_t zeCommandQueueExecuteCommandLists(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t hFence) {
    auto icdCommandQueue = static_cast<IcdL0CommandQueue *>(hCommandQueue);
    auto queueLock = icdCommandQueue->lock();

    icdCommandQueue->moveSharedAllocationsToGpu(numCommandLists, phCommandLists);

    for (uint32_t i = 0u; i < numCommandLists; ++i) {
        const auto icdCommandList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        const auto writeResult = icdCommandList->writeRequiredMemory();

        if (writeResult != ZE_RESULT_SUCCESS) {
            return writeResult;
        }
    }

    if (icdCommandQueue->isEmulatedSynchronousMode()) {
        auto result = zeCommandQueueExecuteCommandListsRpcHelper(hCommandQueue, numCommandLists, phCommandLists, hFence);
        if (result != ZE_RESULT_SUCCESS) {
            return result;
        }
        return zeCommandQueueSynchronizeImpl(icdCommandQueue, std::numeric_limits<uint64_t>::max());
    }

    return zeCommandQueueExecuteCommandListsRpcHelper(hCommandQueue, numCommandLists, phCommandLists, hFence);
}

ze_result_t zeCommandQueueSynchronize(ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    if (static_cast<IcdL0CommandQueue *>(hCommandQueue)->isEmulatedSynchronousMode()) {
        return ZE_RESULT_SUCCESS;
    }
    return zeCommandQueueSynchronizeImpl(hCommandQueue, timeout);
}

ze_result_t zeFenceHostSynchronize(ze_fence_handle_t hFence, uint64_t timeout) {
    return Cal::Utils::waitForCompletionWithTimeout<std::chrono::nanoseconds>(hFence, std::chrono::nanoseconds(timeout), zeFenceHostSynchronizeRpcHelper,
                                                                              ZE_RESULT_SUCCESS, ZE_RESULT_NOT_READY);
}

} // namespace Cal::Client::Icd::LevelZero
