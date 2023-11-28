/*
 * Copyright (C) 2023 Intel Corporation
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

bool appendMemoryRangesBarrier(ze_command_list_handle_t cmdList, uint32_t numRanges, const size_t *rangeSizes, const void *ranges) {
    const auto zeCommandListAppendMemoryRangesBarrierResult = zeCommandListAppendMemoryRangesBarrier(
        cmdList, numRanges, rangeSizes, &ranges, nullptr, 0, nullptr);
    if (zeCommandListAppendMemoryRangesBarrierResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryRangesBarrier() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListAppendMemoryRangesBarrierResult));
        return false;
    }

    log<Verbosity::info>("Memory ranges barrier appended successfully!");
    return true;
}

int main(int argc, const char *argv[]) {
    using namespace Cal::Testing::Utils::LevelZero;

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
    RUN_REQUIRED_STEP(createCommandQueue(context, devices[0], ordinal, queue, ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS));

    ze_command_list_handle_t cmdList{};
    RUN_REQUIRED_STEP(createCommandList(context, devices[0], ordinal, cmdList));

    constexpr size_t bufferSize{1024};
    constexpr size_t alignment{8};

    void *usmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], usmDeviceBuffer));

    RUN_REQUIRED_STEP(appendMemoryRangesBarrier(cmdList, 1, &bufferSize, &usmDeviceBuffer));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));
}
