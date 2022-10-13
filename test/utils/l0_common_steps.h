/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"

#include <vector>

namespace Cal::Testing::Utils::LevelZero {

bool initL0();
bool getDrivers(std::vector<ze_driver_handle_t> &drivers);

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
bool closeCommandList(ze_command_list_handle_t list);
bool destroyCommandList(ze_command_list_handle_t &list);

bool allocateHostMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, void *&usmHostBuffer);
bool freeMemory(ze_context_handle_t context, void *&buffer);

bool createEventPool(ze_context_handle_t context, uint32_t eventsCount, ze_device_handle_t *devices, uint32_t devicesCount, ze_event_pool_handle_t &eventPool);
bool destroyEventPool(ze_event_pool_handle_t &eventPool);

bool createEvent(ze_event_pool_handle_t eventPool, uint32_t index, ze_event_handle_t &event);
bool destroyEvent(ze_event_handle_t &event);

bool createFence(ze_command_queue_handle_t queue, ze_fence_handle_t &fence);
bool synchronizeViaFence(ze_fence_handle_t fence);
bool destroyFence(ze_fence_handle_t &fence);

} // namespace Cal::Testing::Utils::LevelZero
