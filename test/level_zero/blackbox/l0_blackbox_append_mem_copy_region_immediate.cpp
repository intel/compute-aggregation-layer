/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "shared/sys.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

#include <memory>

namespace {
using namespace Cal::Testing::Utils::LevelZero;

constexpr size_t width{1024};
constexpr size_t height{512};
constexpr size_t depth{1};
constexpr size_t alignment{8};
} // namespace

struct TestHandles {
    ze_device_handle_t device = nullptr;
    ze_driver_handle_t driver = nullptr;
    ze_context_handle_t context = nullptr;
    ze_command_queue_handle_t queue = nullptr;
    ze_command_list_handle_t cmdList = nullptr;
    ze_event_pool_handle_t eventPool = nullptr;
    ze_event_handle_t copyRegionFinishedEvent = nullptr;
    uint32_t ordinal = 0xffffffff;
};

int copyToUsmFromUsm(TestHandles th, bool isQueueAsynchronous = false) {
    size_t bufferSize = width * height * depth;

    void *srcUsmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.context, bufferSize, alignment, srcUsmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(srcUsmHostBuffer, 0xAA, bufferSize));

    void *dstUsmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.context, bufferSize, alignment, dstUsmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(dstUsmHostBuffer, 0xC0, bufferSize));

    ze_copy_region_t srcRegion = {0, 0, 0, width, height, depth};
    ze_copy_region_t dstRegion = {0, 0, 0, width, height, depth};

    if (isQueueAsynchronous) {
        RUN_REQUIRED_STEP(appendMemoryCopyRegion(th.cmdList, dstUsmHostBuffer, &dstRegion, width, 0,
                                                 srcUsmHostBuffer, &srcRegion, width, 0, th.copyRegionFinishedEvent));
        RUN_REQUIRED_STEP(synchronizeViaEvent(th.copyRegionFinishedEvent));

        RUN_REQUIRED_STEP(resetEvent(th.copyRegionFinishedEvent));
    } else {
        RUN_REQUIRED_STEP(appendMemoryCopyRegion(th.cmdList, dstUsmHostBuffer, &dstRegion, width, 0,
                                                 srcUsmHostBuffer, &srcRegion, width, 0));
    }

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(dstUsmHostBuffer, srcUsmHostBuffer, width * height * depth));

    RUN_REQUIRED_STEP(freeMemory(th.context, srcUsmHostBuffer));
    RUN_REQUIRED_STEP(freeMemory(th.context, dstUsmHostBuffer));

    return 0;
}

int copyToLocalFromUsm(TestHandles th, bool isQueueAsynchronous = false) {
    size_t bufferSize = width * height * depth;

    void *srcUsmBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.context, bufferSize, alignment, srcUsmBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(srcUsmBuffer, 0xED, bufferSize));

    auto dstBuff = std::make_unique<std::byte[]>(bufferSize);
    void *dstHostBuffer = dstBuff.get();
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(dstHostBuffer, 0xBB, bufferSize));

    ze_copy_region_t srcRegion = {0, 0, 0, width, height, depth};
    ze_copy_region_t dstRegion = {0, 0, 0, width, height, depth};

    if (isQueueAsynchronous) {
        RUN_REQUIRED_STEP(appendMemoryCopyRegion(th.cmdList, dstHostBuffer, &dstRegion, width, 0,
                                                 srcUsmBuffer, &srcRegion, width, 0, th.copyRegionFinishedEvent));
        RUN_REQUIRED_STEP(synchronizeViaEvent(th.copyRegionFinishedEvent));

        RUN_REQUIRED_STEP(resetEvent(th.copyRegionFinishedEvent));
    } else {
        RUN_REQUIRED_STEP(appendMemoryCopyRegion(th.cmdList, dstHostBuffer, &dstRegion, width, 0,
                                                 srcUsmBuffer, &srcRegion, width, 0));
    }

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(dstHostBuffer, srcUsmBuffer, width * height * depth));

    RUN_REQUIRED_STEP(freeMemory(th.context, srcUsmBuffer));

    return 0;
}

int synchronousCopyRegion(TestHandles th) {
    RUN_REQUIRED_STEP(createImmediateCommandList(th.context, th.device, th.ordinal, ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS, th.cmdList));

    RUN_REQUIRED_STEP(0 == copyToUsmFromUsm(th))
    RUN_REQUIRED_STEP(0 == copyToLocalFromUsm(th))

    RUN_REQUIRED_STEP(destroyCommandList(th.cmdList));

    return 0;
}

int asynchronousCopyRegion(TestHandles th) {
    RUN_REQUIRED_STEP(createImmediateCommandList(th.context, th.device, th.ordinal, ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS, th.cmdList));

    constexpr uint32_t eventsCount{2};
    RUN_REQUIRED_STEP(createEventPool(th.context, eventsCount, &th.device, 1u, th.eventPool));
    RUN_REQUIRED_STEP(createEvent(th.eventPool, 1, th.copyRegionFinishedEvent));

    constexpr bool isAsync = true;
    RUN_REQUIRED_STEP(0 == copyToUsmFromUsm(th, isAsync))
    RUN_REQUIRED_STEP(0 == copyToLocalFromUsm(th, isAsync))

    RUN_REQUIRED_STEP(destroyEvent(th.copyRegionFinishedEvent));
    RUN_REQUIRED_STEP(destroyEventPool(th.eventPool));

    RUN_REQUIRED_STEP(destroyCommandList(th.cmdList));

    return 0;
}

int main() {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};
    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    TestHandles th;
    th.device = devices[0];
    th.driver = drivers[0];
    RUN_REQUIRED_STEP(createContext(th.driver, th.context));
    RUN_REQUIRED_STEP(getComputeQueueOrdinal(th.device, th.ordinal));

    RUN_REQUIRED_STEP(0 == synchronousCopyRegion(th));
    RUN_REQUIRED_STEP(0 == asynchronousCopyRegion(th));

    RUN_REQUIRED_STEP(destroyContext(th.context));
}
