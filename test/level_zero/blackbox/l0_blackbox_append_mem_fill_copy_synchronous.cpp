/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

int main() {
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
    RUN_REQUIRED_STEP(createCommandQueue(context, devices[0], ordinal, queue, ze_command_queue_mode_t ::ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS));

    ze_command_list_handle_t cmdList{};
    RUN_REQUIRED_STEP(createCommandList(context, devices[0], ordinal, cmdList));

    constexpr size_t bufferSize{1024};
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

    void *usmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], usmDeviceBuffer));

    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmDeviceBuffer, sourceBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBufferFromHeap.data(), usmSharedBuffer, bufferSize));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, usmHostBuffer, usmSharedBuffer, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmSharedBuffer, destinationBufferFromHeap.data(), bufferSize));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmSharedBuffer, usmHostBuffer, bufferSize));

    RUN_REQUIRED_STEP(freeMemory(context, usmDeviceBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmSharedBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmHostBuffer));

    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));

    RUN_REQUIRED_STEP(destroyContext(context));
}
