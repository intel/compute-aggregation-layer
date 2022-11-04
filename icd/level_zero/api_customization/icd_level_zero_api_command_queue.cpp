/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeCommandQueueSynchronize(ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    auto icdCommandQueue = static_cast<IcdL0CommandQueue *>(hCommandQueue);
    auto lock = icdCommandQueue->lock();

    auto result = zeCommandQueueSynchronizeRpcHelper(hCommandQueue, timeout);
    if (result == ZE_RESULT_SUCCESS) {
        result = icdCommandQueue->readMemoryRequiredByCurrentlyExecutedCommandLists();
        icdCommandQueue->clearExecutedCommandListsPointers();
    }

    return result;
}

ze_result_t zeCommandQueueExecuteCommandLists(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t hFence) {
    auto icdCommandQueue = static_cast<IcdL0CommandQueue *>(hCommandQueue);
    auto queueLock = icdCommandQueue->lock();

    icdCommandQueue->storeExecutedCommandListsPointers(numCommandLists, phCommandLists);

    if (hFence) {
        auto icdFence = static_cast<IcdL0Fence *>(hFence);
        icdFence->storeExecutedCommandListsPointers(numCommandLists, phCommandLists);
    }

    for (uint32_t i = 0u; i < numCommandLists; ++i) {
        const auto icdCommandList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        const auto writeResult = icdCommandList->writeRequiredMemory();

        if (writeResult != ZE_RESULT_SUCCESS) {
            return writeResult;
        }
    }

    queueLock.unlock();
    return zeCommandQueueExecuteCommandListsRpcHelper(hCommandQueue, numCommandLists, phCommandLists, hFence);
}

} // namespace Cal::Icd::LevelZero
