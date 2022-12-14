/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/dynamic_library.h"
#include "test/utils/l0_common_steps.h"

#include <cinttypes>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

bool appendMemoryAdvise(ze_command_list_handle_t commandList, ze_device_handle_t device, const void *sharedPtr, size_t size, ze_memory_advice_t advice) {
    log<Verbosity::info>("Appending memory advise operation to command list (%p)!", static_cast<void *>(commandList));

    const auto zeCommandListAppendMemAdviseResult = zeCommandListAppendMemAdvise(commandList, device, sharedPtr, size, advice);
    if (zeCommandListAppendMemAdviseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Error! zeCommandListAppendMemAdvise() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemAdviseResult));
        return false;
    }

    log<Verbosity::info>("Success! Memory advise operation has been appended!");
    return true;
}

bool appendMemoryPrefetch(ze_command_list_handle_t commandList, const void *sharedPtr, size_t size) {
    log<Verbosity::info>("Appending memory prefetch operation to command list (%p)!", static_cast<void *>(commandList));

    const auto zeCommandListAppendMemoryPrefetchResult = zeCommandListAppendMemoryPrefetch(commandList, sharedPtr, size);
    if (zeCommandListAppendMemoryPrefetchResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Error! zeCommandListAppendMemoryPrefetch() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryPrefetchResult));
        return false;
    }

    log<Verbosity::info>("Success! Memory prefetch operation has been appended!");
    return true;
}

int main(int argc, const char *argv[]) {
    using namespace Cal::Testing::Utils::LevelZero;

    // Setup.
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    ze_context_handle_t context{};
    RUN_REQUIRED_STEP(createContext(drivers[0], context));

    uint32_t ordinal{};
    RUN_REQUIRED_STEP(getComputeQueueOrdinal(devices[0], ordinal));

    ze_command_queue_handle_t queue{};
    RUN_REQUIRED_STEP(createCommandQueue(context, devices[0], ordinal, queue));

    ze_command_list_handle_t cmdList{};
    RUN_REQUIRED_STEP(createCommandList(context, devices[0], ordinal, cmdList));

    ze_fence_handle_t fence{};
    RUN_REQUIRED_STEP(createFence(queue, fence));

    constexpr size_t bufferSize{1024};
    constexpr size_t patternSize{16};
    constexpr size_t alignment{8};

    std::vector<char> sourceBufferFromHeap(bufferSize);
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(sourceBufferFromHeap.data(), 0x44, bufferSize));

    std::vector<char> destinationBufferFromHeap(bufferSize);
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(destinationBufferFromHeap.data(), 0x55, bufferSize));

    void *usmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, usmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0xAA, bufferSize));

    void *usmSharedBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateSharedMemory(context, bufferSize, alignment, devices[0], usmSharedBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmSharedBuffer, 0xBB, bufferSize));

    RUN_REQUIRED_STEP(appendMemoryAdvise(cmdList, devices[0], usmSharedBuffer, bufferSize, ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION));
    RUN_REQUIRED_STEP(appendMemoryPrefetch(cmdList, usmSharedBuffer, bufferSize));

    void *usmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], usmDeviceBuffer));

    // Case 1: zeCommandListAppendMemoryCopy synchronized via zeCommandQueueSynchronize.
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmDeviceBuffer, sourceBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBufferFromHeap.data(), usmSharedBuffer, bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmHostBuffer, usmSharedBuffer, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmSharedBuffer, destinationBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmSharedBuffer, usmHostBuffer, bufferSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBufferFromHeap.data(), sourceBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmHostBuffer, usmDeviceBuffer, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(sourceBufferFromHeap.data(), destinationBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(sourceBufferFromHeap.data(), usmHostBuffer, bufferSize));

    // Case 2: zeCommandListAppendMemoryCopy synchronized via zeFenceHostSynchronize.
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(sourceBufferFromHeap.data(), 0x11, bufferSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(destinationBufferFromHeap.data(), 0x22, bufferSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0x33, bufferSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmSharedBuffer, 0x77, bufferSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmDeviceBuffer, sourceBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBufferFromHeap.data(), usmSharedBuffer, bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmHostBuffer, usmSharedBuffer, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, fence));
    RUN_REQUIRED_STEP(synchronizeViaFence(fence));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmSharedBuffer, destinationBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmSharedBuffer, usmHostBuffer, bufferSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(resetFence(fence));

    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBufferFromHeap.data(), sourceBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmHostBuffer, usmDeviceBuffer, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, fence));
    RUN_REQUIRED_STEP(synchronizeViaFence(fence));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(sourceBufferFromHeap.data(), destinationBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(sourceBufferFromHeap.data(), usmHostBuffer, bufferSize));

    // Case 3: zeCommandListAppendMemoryFill synchronized via zeCommandQueueSynchronize.
    static constexpr std::array<char, patternSize> patternFromStack = {1, 7, 1, 9, 1, 5, 1, 4, 2, 3, 4, 5, 6, 2, 3, 3};
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0xEE, patternSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmSharedBuffer, 0xDD, bufferSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(appendMemoryFill(cmdList, usmHostBuffer, patternFromStack.data(), patternSize, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryFillResults(usmHostBuffer, bufferSize, patternFromStack.data(), patternSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(appendMemoryFill(cmdList, usmSharedBuffer, usmHostBuffer, patternSize, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryFillResults(usmSharedBuffer, bufferSize, usmHostBuffer, patternSize));

    // Case 4: zeCommandListAppendMemoryFill synchronized via zeFenceHostSynchronize.
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0xEE, patternSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmSharedBuffer, 0xDD, bufferSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(resetFence(fence));
    RUN_REQUIRED_STEP(appendMemoryFill(cmdList, usmHostBuffer, patternFromStack.data(), patternSize, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, fence));
    RUN_REQUIRED_STEP(synchronizeViaFence(fence));

    RUN_REQUIRED_STEP(verifyMemoryFillResults(usmHostBuffer, bufferSize, patternFromStack.data(), patternSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(resetFence(fence));
    RUN_REQUIRED_STEP(appendMemoryFill(cmdList, usmSharedBuffer, usmHostBuffer, patternSize, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, fence));
    RUN_REQUIRED_STEP(synchronizeViaFence(fence));

    RUN_REQUIRED_STEP(verifyMemoryFillResults(usmSharedBuffer, bufferSize, usmHostBuffer, patternSize));

    // Teardown.
    RUN_REQUIRED_STEP(freeMemory(context, usmDeviceBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmSharedBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmHostBuffer));

    RUN_REQUIRED_STEP(destroyFence(fence));
    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));

    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
