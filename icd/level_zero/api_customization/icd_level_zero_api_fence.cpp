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

ze_result_t zeFenceHostSynchronize(ze_fence_handle_t hFence, uint64_t timeout) {
    auto icdFence = static_cast<IcdL0Fence *>(hFence);
    auto icdQueue = icdFence->peekQueue();
    auto queueLock = icdQueue->lock();

    const auto result = zeFenceHostSynchronizeRpcHelper(hFence, timeout);
    if (result == ZE_RESULT_SUCCESS) {
        auto icdCommandLists = icdFence->clearExecutedCommandListsPointers();

        for (const auto &commandList : icdCommandLists) {
            const auto icdCommandList = static_cast<IcdL0CommandList *>(commandList);
            const auto readResult = icdCommandList->readRequiredMemory();

            if (readResult != ZE_RESULT_SUCCESS) {
                return readResult;
            }
        }

        icdQueue->removeFromExecutedCommandLists(icdCommandLists);
    }

    return result;
}

} // namespace Cal::Icd::LevelZero
