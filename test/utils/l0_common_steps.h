/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "shared/log.h"

#include <type_traits>
#include <vector>

namespace Cal::Testing::Utils::LevelZero {

bool initL0();
bool getDrivers(std::vector<ze_driver_handle_t> &drivers);
bool getExtensionFunctionAddress(ze_driver_handle_t driver, void **outFunctionAddress, const char *extensionName);

bool getDevices(ze_driver_handle_t driver, std::vector<ze_device_handle_t> &devices);

bool createContext(ze_driver_handle_t driver, ze_context_handle_t &context);
bool destroyContext(ze_context_handle_t &context);

bool getComputeQueueOrdinal(ze_device_handle_t device, uint32_t &ordinal);
bool createCommandQueue(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal, ze_command_queue_handle_t &queue);
bool executeCommandLists(ze_command_queue_handle_t queue, uint32_t numCmdLists, ze_command_list_handle_t *cmdLists, ze_fence_handle_t fence);
bool synchronizeCommandQueue(ze_command_queue_handle_t queue);
bool destroyCommandQueue(ze_command_queue_handle_t &queue);

bool createCommandList(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal, ze_command_list_handle_t &list);
bool appendMemoryCopy(ze_command_list_handle_t cmdList,
                      void *destination,
                      const void *source,
                      size_t size,
                      ze_event_handle_t signalEvent = nullptr,
                      uint32_t waitEventsCount = 0,
                      ze_event_handle_t *waitEvents = nullptr);

bool appendMemoryFill(ze_command_list_handle_t cmdList,
                      void *destination,
                      const void *pattern,
                      size_t patternSize,
                      size_t bufferSize,
                      ze_event_handle_t signalEvent = nullptr,
                      uint32_t waitEventsCount = 0,
                      ze_event_handle_t *waitEvents = nullptr);

bool closeCommandList(ze_command_list_handle_t list);
bool resetCommandList(ze_command_list_handle_t list);
bool destroyCommandList(ze_command_list_handle_t &list);

bool allocateHostMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, void *&usmHostBuffer);
bool allocateSharedMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, ze_device_handle_t device, void *&usmSharedBuffer);
bool allocateDeviceMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, ze_device_handle_t device, void *&usmDeviceBuffer);
bool freeMemory(ze_context_handle_t context, void *&buffer);
bool closeMemIpcHandle(ze_context_handle_t context, void *ptr);

bool createEventPool(ze_context_handle_t context, uint32_t eventsCount, ze_device_handle_t *devices, uint32_t devicesCount, ze_event_pool_handle_t &eventPool);
bool destroyEventPool(ze_event_pool_handle_t &eventPool);

bool createEvent(ze_event_pool_handle_t eventPool, uint32_t index, ze_event_handle_t &event);
bool destroyEvent(ze_event_handle_t &event);

bool createFence(ze_command_queue_handle_t queue, ze_fence_handle_t &fence);
bool synchronizeViaFence(ze_fence_handle_t fence);
bool resetFence(ze_fence_handle_t fence);
bool destroyFence(ze_fence_handle_t &fence);

bool fillBufferOnHostViaMemcpy(void *buffer, int value, size_t bufferSize);
bool verifyMemoryCopyResults(const void *sourceBuffer, const void *destinationBuffer, size_t bufferSize);
bool verifyMemoryFillResults(const void *destination, size_t destinationSize, const void *pattern, size_t patternSize);

template <typename T>
bool ensureNullptr(const T *pointer) {
    if (pointer == nullptr) {
        log<Verbosity::info>("Validation passed! Passed pointer is null!");
        return true;
    }

    log<Verbosity::error>("Validation failed! Passed pointer is: %p", static_cast<const void *>(pointer));
    return false;
}

template <typename T>
bool ensurePointersEqual(const T *expected, const T *actual) {
    if (expected == actual) {
        log<Verbosity::info>("Validation passed! Actual address is equal to the expected one!");
        return true;
    }

    log<Verbosity::error>("Validation failed! Addresses are not equal! Expected: %p, Actual: %p",
                          static_cast<const void *>(expected),
                          static_cast<const void *>(actual));
    return false;
}

} // namespace Cal::Testing::Utils::LevelZero
