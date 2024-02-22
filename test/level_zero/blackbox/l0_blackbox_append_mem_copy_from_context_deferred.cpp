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
    ze_event_handle_t allCopiesFinishedEvent = nullptr;
    uint32_t ordinal = 0xffffffff;
};

int copyToUsmFromUsm(TestHandles th, bool isQueueAsynchronous = false) {
    void *srcUsmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.srcContext, bufferSize, alignment, srcUsmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(srcUsmHostBuffer, 0xAA, bufferSize));
    void *dstUsmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.dstContext, bufferSize, alignment, dstUsmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(dstUsmHostBuffer, 0xC0, bufferSize));

    RUN_REQUIRED_STEP(appendMemoryCopyFromContext(th.cmdList, dstUsmHostBuffer, th.srcContext, srcUsmHostBuffer, bufferSize));
    RUN_REQUIRED_STEP(closeCommandList(th.cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(th.queue, 1u, &th.cmdList, nullptr));

    if (isQueueAsynchronous) {
        RUN_REQUIRED_STEP(synchronizeCommandQueue(th.queue));
    }

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(dstUsmHostBuffer, srcUsmHostBuffer, bufferSize));

    RUN_REQUIRED_STEP(freeMemory(th.srcContext, srcUsmHostBuffer));
    RUN_REQUIRED_STEP(freeMemory(th.dstContext, dstUsmHostBuffer));
    RUN_REQUIRED_STEP(resetCommandList(th.cmdList));

    return 0;
}

int copyToRemappedFromUsm(TestHandles th, bool isQueueAsynchronous = false) {
    void *srcUsmBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(th.srcContext, bufferSize, alignment, srcUsmBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(srcUsmBuffer, 0xED, bufferSize));
    auto dstBuff = std::make_unique<std::byte[]>(bufferSize);
    void *dstHostBuffer = dstBuff.get();
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(dstHostBuffer, 0xBB, bufferSize));

    RUN_REQUIRED_STEP(appendMemoryCopyFromContext(th.cmdList, dstHostBuffer, th.srcContext, srcUsmBuffer, bufferSize));
    RUN_REQUIRED_STEP(closeCommandList(th.cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(th.queue, 1u, &th.cmdList, nullptr));

    if (isQueueAsynchronous) {
        RUN_REQUIRED_STEP(synchronizeCommandQueue(th.queue));
    }

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(dstHostBuffer, srcUsmBuffer, bufferSize));

    RUN_REQUIRED_STEP(freeMemory(th.srcContext, srcUsmBuffer));
    RUN_REQUIRED_STEP(resetCommandList(th.cmdList));
    return 0;
}

int synchronousCopyFromContext(TestHandles th) {
    RUN_REQUIRED_STEP(createCommandQueue(th.dstContext, th.device, th.ordinal, th.queue, ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS));
    RUN_REQUIRED_STEP(createCommandList(th.dstContext, th.device, th.ordinal, th.cmdList));

    RUN_REQUIRED_STEP(0 == copyToUsmFromUsm(th))
    RUN_REQUIRED_STEP(0 == copyToRemappedFromUsm(th))

    RUN_REQUIRED_STEP(destroyCommandList(th.cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(th.queue));
    return 0;
}

int asynchronousCopyFromContext(TestHandles th) {
    RUN_REQUIRED_STEP(createCommandQueue(th.dstContext, th.device, th.ordinal, th.queue, ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS));
    RUN_REQUIRED_STEP(createCommandList(th.dstContext, th.device, th.ordinal, th.cmdList));

    constexpr uint32_t eventsCount{10};
    RUN_REQUIRED_STEP(createEventPool(th.dstContext, eventsCount, &th.device, 1u, th.eventPool));
    RUN_REQUIRED_STEP(createEvent(th.eventPool, 1, th.allCopiesFinishedEvent));

    constexpr bool isAsync = true;
    RUN_REQUIRED_STEP(0 == copyToUsmFromUsm(th, isAsync))
    RUN_REQUIRED_STEP(0 == copyToRemappedFromUsm(th, isAsync))

    RUN_REQUIRED_STEP(destroyEvent(th.allCopiesFinishedEvent));
    RUN_REQUIRED_STEP(destroyEventPool(th.eventPool));

    RUN_REQUIRED_STEP(destroyCommandList(th.cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(th.queue));
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
