/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "shared/log.h"

#include <chrono>
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
bool createCommandQueue(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal, ze_command_queue_handle_t &queue, ze_command_queue_mode_t mode);
bool executeCommandLists(ze_command_queue_handle_t queue, uint32_t numCmdLists, ze_command_list_handle_t *cmdLists, ze_fence_handle_t fence);
bool synchronizeCommandQueue(ze_command_queue_handle_t queue);
bool destroyCommandQueue(ze_command_queue_handle_t &queue);

bool createCommandList(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal, ze_command_list_handle_t &list);
bool createImmediateCommandList(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal, ze_command_queue_mode_t mode, ze_command_list_handle_t &list);
bool appendBarrier(ze_command_list_handle_t cmdList,
                   ze_event_handle_t signalEvent,
                   uint32_t waitEventsCount = 0,
                   ze_event_handle_t *waitEvents = nullptr);

bool appendMemoryCopy(ze_command_list_handle_t cmdList,
                      void *destination,
                      const void *source,
                      size_t size,
                      ze_event_handle_t signalEvent = nullptr,
                      uint32_t waitEventsCount = 0,
                      ze_event_handle_t *waitEvents = nullptr);

bool appendMemoryCopyRegion(ze_command_list_handle_t cmdList,
                            void *destination,
                            const ze_copy_region_t *destinationRegion,
                            uint32_t destinationPitch,
                            uint32_t destinationSlicePitch,
                            const void *source,
                            const ze_copy_region_t *sourceRegion,
                            uint32_t sourcePitch,
                            uint32_t sourceSlicePitch,
                            ze_event_handle_t signalEvent = nullptr,
                            uint32_t waitEventsCount = 0,
                            ze_event_handle_t *waitEvents = nullptr);

bool appendMemoryCopyFromContext(ze_command_list_handle_t cmdList,
                                 void *destination,
                                 ze_context_handle_t sourceContext,
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
bool appendMemoryPrefetch(ze_command_list_handle_t commandList, const void *sharedPtr, size_t size);
bool closeCommandList(ze_command_list_handle_t list);
bool resetCommandList(ze_command_list_handle_t list);
bool destroyCommandList(ze_command_list_handle_t &list);
bool synchronizeOnHost(ze_command_list_handle_t list);

bool allocateHostMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, void *&usmHostBuffer, const void *descPNext = nullptr);
bool allocateSharedMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, ze_device_handle_t device,
                          void *&usmSharedBuffer, uint32_t ordinal = 0u);
bool allocateDeviceMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, ze_device_handle_t device,
                          void *&usmDeviceBuffer, const void *descPNext = nullptr);
bool freeMemory(ze_context_handle_t context, void *&buffer);
bool freeMemoryExt(ze_context_handle_t context, void *&buffer, ze_driver_memory_free_policy_ext_flags_t policyFlag, const char *policyLabel);
bool closeMemIpcHandle(ze_context_handle_t context, void *ptr);

bool createEventPool(ze_context_handle_t context, uint32_t eventsCount, ze_device_handle_t *devices, uint32_t devicesCount, ze_event_pool_handle_t &eventPool);
bool destroyEventPool(ze_event_pool_handle_t &eventPool);

bool createEvent(ze_event_pool_handle_t eventPool, uint32_t index, ze_event_handle_t &event);
bool synchronizeViaEvent(ze_event_handle_t event);
bool synchronizeViaEventPooling(ze_event_handle_t event, std::chrono::milliseconds msTimeout);
bool resetEvent(ze_event_handle_t event);
bool destroyEvent(ze_event_handle_t &event);

bool createFence(ze_command_queue_handle_t queue, ze_fence_handle_t &fence);
bool synchronizeViaFence(ze_fence_handle_t fence);
bool synchronizeViaFencePooling(ze_fence_handle_t fence, std::chrono::milliseconds msTimeout);
bool resetFence(ze_fence_handle_t fence);
bool destroyFence(ze_fence_handle_t &fence);

bool fillBufferOnHostViaMemset(void *buffer, int value, size_t bufferSize);
bool verifyMemoryCopyResults(const void *sourceBuffer, const void *destinationBuffer, size_t bufferSize);
bool verifyMemoryFillResults(const void *destination, size_t destinationSize, const void *pattern, size_t patternSize);

bool generateSpirv(std::vector<uint8_t> &spirv, const char *source);
bool createModule(ze_context_handle_t context, ze_device_handle_t device, const std::vector<uint8_t> &binary,
                  ze_module_format_t binaryFormat, ze_module_handle_t &module, const char *flags = "");
bool destroyModule(ze_module_handle_t &module);
bool checkBuildLog(ze_module_build_log_handle_t buildLog);

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
                          static_cast<const void *>(expected), static_cast<const void *>(actual));
    return false;
}

} // namespace Cal::Testing::Utils::LevelZero
