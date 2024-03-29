/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/icd_global_state.h"
#include "client/icd/level_zero/icd_level_zero.h"
#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/log.h"
#include "shared/synchronization.h"
#include "shared/usm.h"

#include <array>
#include <boost/container/small_vector.hpp>

namespace Cal::Client::Icd::LevelZero {

static auto arePointersUsm(void *dstptr, const void *srcptr) {
    const auto globalL0Platform = Cal::Client::Icd::icdGlobalState.getL0Platform();

    std::array<const void *, 2> ptrs = {dstptr, srcptr};
    std::array<bool, 2> testResults = {};

    globalL0Platform->areUsm(2, ptrs.data(), testResults.data());
    return testResults;
}

static ze_result_t zeCommandListAppendMemoryFillImmediate(ze_command_list_handle_t hCommandList,
                                                          void *ptr,
                                                          const void *pattern,
                                                          size_t pattern_size,
                                                          size_t size,
                                                          ze_event_handle_t hSignalEvent,
                                                          uint32_t numWaitEvents,
                                                          ze_event_handle_t *phWaitEvents) {
    const auto [dstIsUsm, srcIsUsm] = arePointersUsm(ptr, pattern);
    if (dstIsUsm && srcIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperUsm2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }

    if (dstIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperMalloc2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }

    if (srcIsUsm) {
        log<Verbosity::error>("zeCommandListAppendMemoryFill() from USM to host's heap/stack is not supported yet for immediate command lists!");
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    if (IcdL0CommandList::rangesOverlap(pattern, pattern_size, ptr, size)) {
        log<Verbosity::debug>("zeCommandListAppendMemoryFill(): host's heap/stack memory blocks overlap!");
        return ZE_RESULT_ERROR_OVERLAPPING_REGIONS;
    }

    log<Verbosity::debug>("zeCommandListAppendMemoryFill() from host's heap/stack to host's heap/stack is not supported yet for immediate command lists!");
    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

static ze_result_t zeCommandListAppendMemoryFillRegular(ze_command_list_handle_t hCommandList,
                                                        void *ptr,
                                                        const void *pattern,
                                                        size_t pattern_size,
                                                        size_t size,
                                                        ze_event_handle_t hSignalEvent,
                                                        uint32_t numWaitEvents,
                                                        ze_event_handle_t *phWaitEvents) {
    const auto [dstIsUsm, srcIsUsm] = arePointersUsm(ptr, pattern);

    if (dstIsUsm && srcIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperUsm2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }

    if (dstIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperMalloc2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }

    if (srcIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperUsm2Malloc(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }

    if (IcdL0CommandList::rangesOverlap(pattern, pattern_size, ptr, size)) {
        log<Verbosity::debug>("zeCommandListAppendMemoryFill(): host's heap/stack memory blocks overlap!");
        return ZE_RESULT_ERROR_OVERLAPPING_REGIONS;
    }

    return zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
}

ze_result_t zeCommandListAppendMemoryFill(ze_command_list_handle_t hCommandList,
                                          void *ptr,
                                          const void *pattern,
                                          size_t pattern_size,
                                          size_t size,
                                          ze_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          ze_event_handle_t *phWaitEvents) {
    const auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (ptr == nullptr || pattern == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    icdCommandList->moveSharedAllocationsToGpu(ptr, pattern);

    if (icdCommandList->isImmediate()) {
        return zeCommandListAppendMemoryFillImmediate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else {
        return zeCommandListAppendMemoryFillRegular(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}

ze_result_t zeCommandListAppendMemoryCopy(ze_command_list_handle_t hCommandList,
                                          void *dstptr,
                                          const void *srcptr,
                                          size_t size,
                                          ze_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          ze_event_handle_t *phWaitEvents) {

    const auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (dstptr == nullptr || srcptr == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    icdCommandList->moveSharedAllocationsToGpu(dstptr, srcptr);

    if (icdCommandList->isImmediate()) {
        if (icdCommandList->isImmediateSynchronous()) {
            return zeCommandListAppendMemoryCopyImmediateSynchronous(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        } else {
            return zeCommandListAppendMemoryCopyImmediate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    } else {
        return zeCommandListAppendMemoryCopyDeferred(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}

ze_result_t zeCommandListAppendMemoryCopyRegion(ze_command_list_handle_t hCommandList,
                                                void *dstptr,
                                                const ze_copy_region_t *dstRegion,
                                                uint32_t dstPitch,
                                                uint32_t dstSlicePitch,
                                                const void *srcptr,
                                                const ze_copy_region_t *srcRegion,
                                                uint32_t srcPitch,
                                                uint32_t srcSlicePitch,
                                                ze_event_handle_t hSignalEvent,
                                                uint32_t numWaitEvents,
                                                ze_event_handle_t *phWaitEvents) {

    const auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (dstptr == nullptr || srcptr == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    icdCommandList->moveSharedAllocationsToGpu(dstptr, srcptr);

    if (icdCommandList->isImmediate()) {
        if (icdCommandList->isImmediateSynchronous()) {
            return zeCommandListAppendMemoryCopyRegionImmediateSynchronous(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
        } else {
            return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    } else {
        return zeCommandListAppendMemoryCopyRegionDeferred(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}

ze_result_t zeCommandListAppendMemoryCopyFromContext(ze_command_list_handle_t hCommandList,
                                                     void *dstptr,
                                                     ze_context_handle_t hContextSrc,
                                                     const void *srcptr,
                                                     size_t size,
                                                     ze_event_handle_t hSignalEvent,
                                                     uint32_t numWaitEvents,
                                                     ze_event_handle_t *phWaitEvents) {

    const auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    const auto icdContextSrc = static_cast<IcdL0Context *>(hContextSrc);
    if (icdCommandList == nullptr || icdContextSrc == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (dstptr == nullptr || srcptr == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    icdCommandList->moveSharedAllocationsToGpu(dstptr, srcptr);

    if (icdCommandList->isImmediate()) {
        if (icdCommandList->isImmediateSynchronous()) {
            return zeCommandListAppendMemoryCopyFromContextImmediateSynchronous(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        } else {
            return zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
        }
    } else {
        return zeCommandListAppendMemoryCopyFromContextDeferred(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}

ze_result_t zeCommandListAppendMemAdvise(ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void *ptr, size_t size, ze_memory_advice_t advice) {
    log<Verbosity::debug>("zeCommandListAppendMemAdvise(): Ignoring passed advice!");
    return ZE_RESULT_SUCCESS;
}

ze_result_t zeCommandListAppendQueryKernelTimestamps(ze_command_list_handle_t hCommandList,
                                                     uint32_t numEvents,
                                                     ze_event_handle_t *phEvents,
                                                     void *dstptr,
                                                     const size_t *pOffsets,
                                                     ze_event_handle_t hSignalEvent,
                                                     uint32_t numWaitEvents,
                                                     ze_event_handle_t *phWaitEvents) {

    if (dstptr == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if (pOffsets == nullptr) {
        return zeCommandListAppendQueryKernelTimestampsRpcHelper(hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents);
    } else {
        boost::container::small_vector<ze_kernel_timestamp_result_t, 8> results{numEvents};

        ze_result_t ret = zeCommandListAppendQueryKernelTimestampsRpcHelper(hCommandList, numEvents, phEvents, results.data(), nullptr, hSignalEvent, numWaitEvents, phWaitEvents);

        for (uint32_t i = 0; i < numEvents; i++) {
            *reinterpret_cast<ze_kernel_timestamp_result_t *>(reinterpret_cast<char *>(dstptr) + pOffsets[i]) = results[i];
        }

        return ret;
    }
}

ze_result_t zeCommandListHostSynchronize(ze_command_list_handle_t hCommandList, uint64_t timeout) {
    return Cal::Utils::waitForCompletionWithTimeout<std::chrono::nanoseconds>(hCommandList, std::chrono::nanoseconds(timeout), zeCommandListHostSynchronizeRpcHelper,
                                                                              ZE_RESULT_SUCCESS, ZE_RESULT_NOT_READY);
}

} // namespace Cal::Client::Icd::LevelZero
