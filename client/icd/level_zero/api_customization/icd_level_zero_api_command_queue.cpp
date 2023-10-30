/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/level_zero/icd_level_zero.h"
#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"

namespace Cal::Icd::LevelZero {

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

    return zeCommandQueueExecuteCommandListsRpcHelper(hCommandQueue, numCommandLists, phCommandLists, hFence);
}

} // namespace Cal::Icd::LevelZero
