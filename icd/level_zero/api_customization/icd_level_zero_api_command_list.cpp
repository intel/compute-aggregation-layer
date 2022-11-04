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
#include "shared/usm.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeCommandListAppendMemoryFill(ze_command_list_handle_t hCommandList,
                                          void *ptr,
                                          const void *pattern,
                                          size_t pattern_size,
                                          size_t size,
                                          ze_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          ze_event_handle_t *phWaitEvents) {
    auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (ptr == nullptr || pattern == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();

    const void *ptrs[] = {ptr, pattern};
    bool testResults[2] = {};
    globalL0Platform->areUsm(2, ptrs, testResults);

    const auto &[dstIsUsm, srcIsUsm] = testResults;
    if (dstIsUsm && srcIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperUsm2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (dstIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperMalloc2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (srcIsUsm) {
        if (icdCommandList->isImmediate()) {
            log<Verbosity::error>("zeCommandListAppendMemoryFill() from USM to host's heap/stack is not supported yet for immediate command lists!");
        } else {
            icdCommandList->registerMemoryToRead(ptr, size);
            return zeCommandListAppendMemoryFillRpcHelperUsm2Malloc(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    } else {
        if (IcdL0CommandList::rangesOverlap(pattern, pattern_size, ptr, size)) {
            log<Verbosity::debug>("zeCommandListAppendMemoryFill(): host's heap/stack memory blocks overlap!");
            return ZE_RESULT_ERROR_OVERLAPPING_REGIONS;
        }

        if (icdCommandList->isImmediate()) {
            log<Verbosity::debug>("zeCommandListAppendMemoryFill() from host's heap/stack to host's heap/stack is not supported yet for immediate command lists!");
        } else {
            icdCommandList->registerMemoryToRead(ptr, size);
            return zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    }

    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

ze_result_t zeCommandListAppendMemoryCopy(ze_command_list_handle_t hCommandList,
                                          void *dstptr,
                                          const void *srcptr,
                                          size_t size,
                                          ze_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          ze_event_handle_t *phWaitEvents) {

    auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (dstptr == nullptr || srcptr == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();

    const void *ptrs[] = {dstptr, srcptr};
    bool testResults[2] = {};
    globalL0Platform->areUsm(2, ptrs, testResults);

    const auto &[dstIsUsm, srcIsUsm] = testResults;
    if (dstIsUsm && srcIsUsm) {
        return zeCommandListAppendMemoryCopyRpcHelperUsm2Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (dstIsUsm) {
        if (icdCommandList->isImmediate()) {
            return zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        } else {
            icdCommandList->registerMemoryToWrite(srcptr, size);
            return zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    } else if (srcIsUsm) {
        if (icdCommandList->isImmediate()) {
            log<Verbosity::error>("zeCommandListAppendMemoryCopy for USM2M is not supported for immediate command lists yet!");
        } else {
            icdCommandList->registerMemoryToRead(dstptr, size);
            return zeCommandListAppendMemoryCopyRpcHelperUsm2Malloc(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    } else {
        if (IcdL0CommandList::rangesOverlap(srcptr, dstptr, size)) {
            log<Verbosity::debug>("zeCommandListAppendMemoryCopy(): host's heap/stack memory blocks overlap!");
            return ZE_RESULT_ERROR_OVERLAPPING_REGIONS;
        }

        if (icdCommandList->isImmediate()) {
            log<Verbosity::error>("zeCommandListAppendMemoryCopy for M2M is not supported for immediate command lists yet!");
        } else {
            icdCommandList->registerMemoryToWrite(srcptr, size);
            icdCommandList->registerMemoryToRead(dstptr, size);

            return zeCommandListAppendMemoryCopyRpcHelperMalloc2Malloc(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    }

    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

} // namespace Cal::Icd::LevelZero
