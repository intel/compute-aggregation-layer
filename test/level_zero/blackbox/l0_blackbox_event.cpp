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
#include "test/utils/assertions.h"
#include "test/utils/dynamic_library.h"
#include "test/utils/l0_common_steps.h"

#include <cinttypes>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

enum class EventStatus {
    signaled = 0,
    notSignaled = 1,
};

bool testIpcFunctionality(ze_context_handle_t context, ze_event_pool_handle_t eventPool) {
    log<Verbosity::info>("Testing IPC functionality");

    log<Verbosity::info>("Getting IPC handle of ze_event_pool_handle_t = %p", eventPool);
    ze_ipc_event_pool_handle_t eventPoolIpcHandle{};
    const auto zeEventPoolGetIpcHandleResult = zeEventPoolGetIpcHandle(eventPool, &eventPoolIpcHandle);
    if (zeEventPoolGetIpcHandleResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
        log<Verbosity::info>("Events IPC features are not supported on this device. Skipping...");
        return true;
    } else if (zeEventPoolGetIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolGetIpcHandle() call has failed! Error code: %d", static_cast<int>(zeEventPoolGetIpcHandleResult));
        return false;
    }

    uint64_t firstBytes{};
    std::memcpy(&firstBytes, eventPoolIpcHandle.data, sizeof(firstBytes));
    log<Verbosity::info>("Successfully got IPC handle of %p! First bytes of handle as u64 = " PRIu64, eventPool, firstBytes);

    log<Verbosity::info>("Opening ze_ipc_event_pool_handle_t via zeEventPoolOpenIpcHandle()!");
    ze_event_pool_handle_t eventPoolOpenedFromIpcHandle{};
    const auto zeEventPoolOpenIpcHandleResult = zeEventPoolOpenIpcHandle(context, eventPoolIpcHandle, &eventPoolOpenedFromIpcHandle);
    if (zeEventPoolOpenIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolOpenIpcHandle() call has failed! Error code: %d", static_cast<int>(zeEventPoolOpenIpcHandleResult));
        return false;
    }
    log<Verbosity::info>("Successfully opened IPC handle! Event pool handle = %p", static_cast<void *>(eventPoolOpenedFromIpcHandle));

    log<Verbosity::info>("Closing ze_ipc_event_pool_handle_t via zeEventPoolCloseIpcHandle()");
    const auto zeEventPoolCloseIpcHandleResult = zeEventPoolCloseIpcHandle(eventPoolOpenedFromIpcHandle);
    if (zeEventPoolCloseIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolCloseIpcHandle() call has failed! Error code: %d", static_cast<int>(zeEventPoolCloseIpcHandleResult));
        return false;
    }
    eventPoolOpenedFromIpcHandle = nullptr;
    log<Verbosity::info>("Successfully closed IPC handle!");

    log<Verbosity::info>("Successfully run IPC functionality test!");
    return true;
}

bool copyBuffersOnHost(void *destination, const void *source, size_t size) {
    log<Verbosity::info>("Copying %zd bytes from %p to %p", size, source, destination);
    std::memcpy(destination, source, size);

    log<Verbosity::info>("Data has been copied successfully!");
    return true;
}

bool signalEventFromHost(ze_event_handle_t event) {
    log<Verbosity::info>("Signaling event = %p from host!", static_cast<void *>(event));

    const auto zeEventHostSignalResult = zeEventHostSignal(event);
    if (zeEventHostSignalResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventHostSignal() call has failed! Error code: %d", static_cast<int>(zeEventHostSignalResult));
        return false;
    }

    log<Verbosity::info>("Successfully signaled given event!");
    return true;
}

bool ensureEventInState(ze_event_handle_t event, EventStatus eventStatus) {
    const auto eventStatusLabel = (eventStatus == EventStatus::signaled) ? "signaled" : "not signaled";
    log<Verbosity::info>("Ensuring that event is in state: %s", eventStatusLabel);

    const auto zeEventQueryStatusResult = zeEventQueryStatus(event);
    if (zeEventQueryStatusResult != ZE_RESULT_SUCCESS && zeEventQueryStatusResult != ZE_RESULT_NOT_READY) {
        log<Verbosity::error>("zeEventQueryStatus() call has failed! Error code: %d", static_cast<int>(zeEventQueryStatusResult));
        return false;
    }

    const auto expectedZeStatus = (eventStatus == EventStatus::signaled) ? ZE_RESULT_SUCCESS : ZE_RESULT_NOT_READY;
    if (expectedZeStatus != zeEventQueryStatusResult) {
        log<Verbosity::error>("Actual status is different than expected one!");
        return false;
    } else {
        log<Verbosity::info>("Actual status matches the expected one!");
        return true;
    }
}

bool appendSignalEvent(ze_command_list_handle_t cmdList, ze_event_handle_t event) {
    log<Verbosity::info>("Appending signal event (%p) operation to command list (%p)", static_cast<void *>(event), static_cast<void *>(cmdList));

    const auto zeCommandListAppendSignalEventResult = zeCommandListAppendSignalEvent(cmdList, event);
    if (zeCommandListAppendSignalEventResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendSignalEvent() call has failed! Error code: %d", static_cast<int>(zeCommandListAppendSignalEventResult));
        return false;
    }

    log<Verbosity::info>("Successfully appended signal operation for given event!");
    return true;
}

bool appendResetEvent(ze_command_list_handle_t cmdList, ze_event_handle_t event) {
    log<Verbosity::info>("Appending reset event (%p) operation to command list (%p)", static_cast<void *>(event), static_cast<void *>(cmdList));

    const auto zeCommandListAppendEventResetResult = zeCommandListAppendEventReset(cmdList, event);
    if (zeCommandListAppendEventResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendEventReset() call has failed! Error code: %d", static_cast<int>(zeCommandListAppendEventResetResult));
        return false;
    }

    log<Verbosity::info>("Successfully appended reset operation for given event!");
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

    constexpr size_t elementsCount{1024};
    constexpr size_t bufferSize{elementsCount * sizeof(unsigned int)};
    constexpr size_t alignment{8};

    void *sourceBuffer{nullptr};
    void *intermediateBuffer1{nullptr};
    void *intermediateBuffer2{nullptr};
    void *destinationBuffer{nullptr};

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, sourceBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(sourceBuffer, 0xAA, bufferSize));

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, intermediateBuffer1));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(intermediateBuffer1, 0xBB, bufferSize));

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, intermediateBuffer2));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(intermediateBuffer2, 0xCC, bufferSize));

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, destinationBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(destinationBuffer, 0xDD, bufferSize));

    constexpr uint32_t eventsCount{10};
    ze_event_pool_handle_t eventPool{};
    RUN_REQUIRED_STEP(createEventPool(context, eventsCount, &devices[0], 1, eventPool));

    ze_event_handle_t eventToBeResetFromCmdList{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 5, eventToBeResetFromCmdList));
    RUN_REQUIRED_STEP(signalEventFromHost(eventToBeResetFromCmdList));
    RUN_REQUIRED_STEP(ensureEventInState(eventToBeResetFromCmdList, EventStatus::signaled));
    RUN_REQUIRED_STEP(appendResetEvent(cmdList, eventToBeResetFromCmdList));

    ze_event_handle_t eventToBeSignaledFromCmdList{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 4, eventToBeSignaledFromCmdList));
    RUN_REQUIRED_STEP(appendSignalEvent(cmdList, eventToBeSignaledFromCmdList));

    ze_event_handle_t intermediateBuffer1FilledEvent{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 3, intermediateBuffer1FilledEvent));

    RUN_REQUIRED_STEP(copyBuffersOnHost(intermediateBuffer1, sourceBuffer, bufferSize));
    RUN_REQUIRED_STEP(signalEventFromHost(intermediateBuffer1FilledEvent));

    ze_event_handle_t intermediateBuffer2FilledEvent{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 2, intermediateBuffer2FilledEvent));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, intermediateBuffer2, intermediateBuffer1, bufferSize, intermediateBuffer2FilledEvent, 1, &intermediateBuffer1FilledEvent));

    ze_event_handle_t copyingFinishedEvent{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 1, copyingFinishedEvent));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destinationBuffer, intermediateBuffer2, bufferSize, copyingFinishedEvent, 1, &intermediateBuffer2FilledEvent));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));

    RUN_REQUIRED_STEP(synchronizeViaEvent(copyingFinishedEvent));
    RUN_REQUIRED_STEP(verifyMemoryCopyResults(sourceBuffer, destinationBuffer, bufferSize));

    RUN_REQUIRED_STEP(ensureEventInState(eventToBeResetFromCmdList, EventStatus::notSignaled));

    RUN_REQUIRED_STEP(ensureEventInState(eventToBeSignaledFromCmdList, EventStatus::signaled));
    RUN_REQUIRED_STEP(resetEvent(eventToBeSignaledFromCmdList));
    RUN_REQUIRED_STEP(ensureEventInState(eventToBeSignaledFromCmdList, EventStatus::notSignaled));

    RUN_REQUIRED_STEP(testIpcFunctionality(context, eventPool));

    RUN_REQUIRED_STEP(destroyEvent(copyingFinishedEvent));
    RUN_REQUIRED_STEP(destroyEvent(intermediateBuffer2FilledEvent));
    RUN_REQUIRED_STEP(destroyEvent(intermediateBuffer1FilledEvent));
    RUN_REQUIRED_STEP(destroyEvent(eventToBeSignaledFromCmdList));
    RUN_REQUIRED_STEP(destroyEvent(eventToBeResetFromCmdList));
    RUN_REQUIRED_STEP(destroyEventPool(eventPool));

    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));

    RUN_REQUIRED_STEP(freeMemory(context, sourceBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, intermediateBuffer1));
    RUN_REQUIRED_STEP(freeMemory(context, intermediateBuffer2));
    RUN_REQUIRED_STEP(freeMemory(context, destinationBuffer));

    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
