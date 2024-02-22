/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "shared/sys.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

#include <memory>

namespace {
using namespace Cal::Testing::Utils::LevelZero;

constexpr size_t bufferSize{8192};
constexpr size_t alignment{8};
} // namespace

struct TestHandles {
    ze_device_handle_t device = nullptr;
    ze_driver_handle_t driver = nullptr;
    ze_context_handle_t srcContext = nullptr;
    ze_context_handle_t dstContext = nullptr;
    ze_command_queue_handle_t queue = nullptr;
    ze_command_list_handle_t cmdList = nullptr;
    ze_event_pool_handle_t eventPool = nullptr;
    ze_event_handle_t copyFromContextFinishedEvent = nullptr;
    ze_event_handle_t allCopiesFinishedEvent = nullptr;
    uint32_t ordinal = 0xffffffff;
};

int copyToUsmFromUsm(TestHandles th, bool isQueueAsynchronous = false) {
    void *srcUsmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.srcContext, bufferSize, alignment, srcUsmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(srcUsmHostBuffer, 0xAA, bufferSize));
    void *tmpUsmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(th.dstContext, bufferSize, alignment, th.device, tmpUsmDeviceBuffer));
    void *dstUsmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.dstContext, bufferSize, alignment, dstUsmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(dstUsmHostBuffer, 0xC0, bufferSize));

    if (isQueueAsynchronous) {
        RUN_REQUIRED_STEP(appendMemoryCopyFromContext(th.cmdList, tmpUsmDeviceBuffer, th.srcContext, srcUsmHostBuffer, bufferSize, th.copyFromContextFinishedEvent));
        RUN_REQUIRED_STEP(appendMemoryCopy(th.cmdList, dstUsmHostBuffer, tmpUsmDeviceBuffer, bufferSize, th.allCopiesFinishedEvent, 1u, &th.copyFromContextFinishedEvent));
        RUN_REQUIRED_STEP(synchronizeViaEvent(th.allCopiesFinishedEvent));

        RUN_REQUIRED_STEP(resetEvent(th.copyFromContextFinishedEvent));
        RUN_REQUIRED_STEP(resetEvent(th.allCopiesFinishedEvent));
    } else {
        RUN_REQUIRED_STEP(appendMemoryCopyFromContext(th.cmdList, tmpUsmDeviceBuffer, th.srcContext, srcUsmHostBuffer, bufferSize));
        RUN_REQUIRED_STEP(appendMemoryCopy(th.cmdList, dstUsmHostBuffer, tmpUsmDeviceBuffer, bufferSize));
    }

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(dstUsmHostBuffer, srcUsmHostBuffer, bufferSize));

    RUN_REQUIRED_STEP(freeMemory(th.srcContext, srcUsmHostBuffer));
    RUN_REQUIRED_STEP(freeMemory(th.dstContext, tmpUsmDeviceBuffer));
    RUN_REQUIRED_STEP(freeMemory(th.dstContext, dstUsmHostBuffer));
    return 0;
}

int copyToLocalFromUsm(TestHandles th, bool isQueueAsynchronous = false) {
    void *srcUsmBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.srcContext, bufferSize, alignment, srcUsmBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(srcUsmBuffer, 0xED, bufferSize));
    auto dstBuff = std::make_unique<std::byte[]>(bufferSize);
    void *dstHostBuffer = dstBuff.get();
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(dstHostBuffer, 0xBB, bufferSize));

    if (isQueueAsynchronous) {
        RUN_REQUIRED_STEP(appendMemoryCopyFromContext(th.cmdList, dstHostBuffer, th.srcContext, srcUsmBuffer, bufferSize, th.copyFromContextFinishedEvent));
        RUN_REQUIRED_STEP(synchronizeViaEvent(th.copyFromContextFinishedEvent));
        RUN_REQUIRED_STEP(resetEvent(th.copyFromContextFinishedEvent));
    } else {
        RUN_REQUIRED_STEP(appendMemoryCopyFromContext(th.cmdList, dstHostBuffer, th.srcContext, srcUsmBuffer, bufferSize));
    }

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(dstHostBuffer, srcUsmBuffer, bufferSize));

    RUN_REQUIRED_STEP(freeMemory(th.srcContext, srcUsmBuffer));
    return 0;
}

int synchronousCopyFromContext(TestHandles th) {
    RUN_REQUIRED_STEP(createImmediateCommandList(th.dstContext, th.device, th.ordinal, ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS, th.cmdList));

    RUN_REQUIRED_STEP(0 == copyToUsmFromUsm(th))
    RUN_REQUIRED_STEP(0 == copyToLocalFromUsm(th))

    RUN_REQUIRED_STEP(destroyCommandList(th.cmdList));
    return 0;
}

int asynchronousCopyFromContext(TestHandles th) {
    RUN_REQUIRED_STEP(createImmediateCommandList(th.dstContext, th.device, th.ordinal, ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS, th.cmdList));

    constexpr uint32_t eventsCount{2};
    RUN_REQUIRED_STEP(createEventPool(th.dstContext, eventsCount, &th.device, 1u, th.eventPool));
    RUN_REQUIRED_STEP(createEvent(th.eventPool, 1, th.copyFromContextFinishedEvent));
    RUN_REQUIRED_STEP(createEvent(th.eventPool, 1, th.allCopiesFinishedEvent));

    constexpr bool isAsync = true;
    RUN_REQUIRED_STEP(0 == copyToUsmFromUsm(th, isAsync))
    RUN_REQUIRED_STEP(0 == copyToLocalFromUsm(th, isAsync))

    RUN_REQUIRED_STEP(destroyEvent(th.copyFromContextFinishedEvent));
    RUN_REQUIRED_STEP(destroyEvent(th.allCopiesFinishedEvent));
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
    RUN_REQUIRED_STEP(createContext(th.driver, th.srcContext));
    RUN_REQUIRED_STEP(createContext(th.driver, th.dstContext));
    RUN_REQUIRED_STEP(getComputeQueueOrdinal(th.device, th.ordinal));

    RUN_REQUIRED_STEP(0 == synchronousCopyFromContext(th));
    RUN_REQUIRED_STEP(0 == asynchronousCopyFromContext(th));

    RUN_REQUIRED_STEP(destroyContext(th.srcContext));
    RUN_REQUIRED_STEP(destroyContext(th.dstContext));
}
