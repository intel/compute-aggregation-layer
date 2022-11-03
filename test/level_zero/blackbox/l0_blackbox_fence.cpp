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

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

enum class FenceStatus {
    NotSignaled = 0,
    Signaled = 1,
};

bool verifyFenceStatus(ze_fence_handle_t fence, FenceStatus status) {
    log<Verbosity::info>("Checking fence status via zeFenceQueryStatus()!");

    const auto zeFenceQueryStatusResult = zeFenceQueryStatus(fence);
    const auto expectedResult = (status == FenceStatus::NotSignaled) ? ZE_RESULT_NOT_READY : ZE_RESULT_SUCCESS;
    if (zeFenceQueryStatusResult != expectedResult) {
        log<Verbosity::error>("zeFenceQueryStatus() call returned value different than expected! Expected: %d, Actual: %d",
                              static_cast<int>(expectedResult), static_cast<int>(zeFenceQueryStatusResult));
        return false;
    }

    log<Verbosity::info>("Fence status check passed!");
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
    RUN_REQUIRED_STEP(createCommandQueue(context, devices[0], ordinal, queue));

    ze_command_list_handle_t cmdList{};
    RUN_REQUIRED_STEP(createCommandList(context, devices[0], ordinal, cmdList));

    ze_fence_handle_t fence{};
    RUN_REQUIRED_STEP(createFence(queue, fence));
    RUN_REQUIRED_STEP(verifyFenceStatus(fence, FenceStatus::NotSignaled));

    constexpr size_t elementsCount{1024};
    constexpr size_t bufferSize{elementsCount * sizeof(unsigned int)};
    constexpr size_t alignment{8};

    void *sourceBuffer{nullptr};
    void *destinationBuffer{nullptr};

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, sourceBuffer));
    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, destinationBuffer));

    std::memset(sourceBuffer, 0xFF, bufferSize);
    std::memset(destinationBuffer, 0xAA, bufferSize);

    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBuffer, sourceBuffer, bufferSize));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));

    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, fence));
    RUN_REQUIRED_STEP(synchronizeViaFence(fence));

    RUN_REQUIRED_STEP(verifyFenceStatus(fence, FenceStatus::Signaled));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(sourceBuffer, destinationBuffer, bufferSize));

    RUN_REQUIRED_STEP(resetFence(fence));
    RUN_REQUIRED_STEP(verifyFenceStatus(fence, FenceStatus::NotSignaled));

    RUN_REQUIRED_STEP(destroyFence(fence));
    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));

    RUN_REQUIRED_STEP(freeMemory(context, sourceBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, destinationBuffer));

    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
