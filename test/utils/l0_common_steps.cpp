/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "l0_common_steps.h"

#include "test/utils/dynamic_library.h"

#include <cstdint>

namespace Cal::Testing::Utils::LevelZero {

bool initL0() {
    const auto zeInitResult = zeInit(0);
    if (zeInitResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeInit() call has failed! Error code = %d", static_cast<int>(zeInitResult));
        return false;
    }

    return true;
}

bool getDrivers(std::vector<ze_driver_handle_t> &drivers) {
    uint32_t numDrivers{0};

    auto zeDriverGetResult = zeDriverGet(&numDrivers, nullptr);
    if (zeDriverGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGet() call has failed! Error code = %d", static_cast<int>(zeDriverGetResult));
        return false;
    }

    if (numDrivers == 0) {
        log<Verbosity::error>("zeDriverGet() returned drivers count equals 0!");
        return false;
    } else {
        log<Verbosity::info>("Number of supported drivers: %d", static_cast<int>(numDrivers));
    }

    log<Verbosity::info>("Calling zeDriverGet() to get drivers!");
    drivers.resize(numDrivers);

    zeDriverGetResult = zeDriverGet(&numDrivers, drivers.data());
    if (zeDriverGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGet() call has failed! Error code = %d", static_cast<int>(zeDriverGetResult));
        return false;
    }

    return !drivers.empty();
}

bool getExtensionFunctionAddress(ze_driver_handle_t driver, void **outFunctionAddress, const char *extensionName) {
    const auto zeDriverGetExtensionFunctionAddressResult = zeDriverGetExtensionFunctionAddress(driver, extensionName, outFunctionAddress);
    if (zeDriverGetExtensionFunctionAddressResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionFunctionAddress() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionFunctionAddressResult));
        return false;
    }

    log<Verbosity::info>("zeDriverGetExtensionFunctionAddress() returned success for extensionName = '%s'. Checking passed outFunctionAddress...", extensionName);

    if (*outFunctionAddress == nullptr) {
        log<Verbosity::error>("Passed outFunctionAddress should not be set to nullptr! Validation failed!");
        return false;
    }

    log<Verbosity::info>("*outFunctionAddress is not nullptr as expected! *outFunctionAddress = %p", *outFunctionAddress);
    return true;
}

bool getDevices(ze_driver_handle_t driver, std::vector<ze_device_handle_t> &devices) {
    uint32_t numDevices{0};

    auto zeDeviceGetResult = zeDeviceGet(driver, &numDevices, nullptr);
    if (zeDeviceGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGet() call has failed! Error code = %d", static_cast<int>(zeDeviceGetResult));
        return false;
    }

    if (numDevices == 0) {
        log<Verbosity::error>("zeDeviceGet() returned devices count equals 0!");
        return false;
    } else {
        log<Verbosity::info>("Number of available devices: %d", static_cast<int>(numDevices));
    }

    log<Verbosity::info>("Calling zeDeviceGet() to get devices!");
    devices.resize(numDevices);

    zeDeviceGetResult = zeDeviceGet(driver, &numDevices, devices.data());
    if (zeDeviceGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGet() call has failed! Error code = %d", static_cast<int>(zeDeviceGetResult));
        return false;
    }

    return !devices.empty();
}

bool createContext(ze_driver_handle_t driver, ze_context_handle_t &context) {
    ze_context_desc_t contextDescription{};
    contextDescription.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;

    const auto zeContextCreateResult = zeContextCreate(driver, &contextDescription, &context);
    if (zeContextCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextCreate() call has failed! Error code = %d", static_cast<int>(zeContextCreateResult));
        return false;
    }

    log<Verbosity::info>("L0 context has been created! context = %p", static_cast<void *>(context));
    return true;
}

bool destroyContext(ze_context_handle_t &context) {
    const auto zeContextDestroyResult = zeContextDestroy(context);
    if (zeContextDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextDestroy() call has failed for context = %p! Error code = %d", context, static_cast<int>(zeContextDestroyResult));
        return false;
    }

    context = nullptr;
    log<Verbosity::info>("L0 context has been destroyed!");

    return true;
}

bool getComputeQueueOrdinal(ze_device_handle_t device, uint32_t &ordinal) {
    log<Verbosity::info>("Getting command queue properties for device to get compute queue ordinal!");

    uint32_t queueGroupPropertiesCount{0};
    auto zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, nullptr);
    if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call for getting count has failed! Error code = %d",
                              static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
        return false;
    }

    std::vector<ze_command_queue_group_properties_t> queueGroupProperties{};
    queueGroupProperties.resize(queueGroupPropertiesCount);

    for (auto &queueGroupProperty : queueGroupProperties) {
        queueGroupProperty.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    }

    zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, queueGroupProperties.data());
    if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call for getting properties has failed! Error code = %d",
                              static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
        return false;
    }

    for (uint32_t i = 0; i < queueGroupPropertiesCount; ++i) {
        if (queueGroupProperties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE) {
            log<Verbosity::info>("Using ordinal = %d --> compute flag enabled", static_cast<int>(i));
            ordinal = i;

            return true;
        }
    }

    log<Verbosity::error>("Could not find the ordinal for compute!");
    return false;
}

bool createCommandQueue(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal,
                        ze_command_queue_handle_t &queue, ze_command_queue_mode_t mode) {
    ze_command_queue_desc_t queueDescription{};

    queueDescription.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    queueDescription.mode = mode;
    queueDescription.priority = ZE_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDescription.ordinal = ordinal;

    const auto zeCommandQueueCreateResult = zeCommandQueueCreate(context, device, &queueDescription, &queue);
    if (zeCommandQueueCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueCreate() call has failed! Error code = %d", static_cast<int>(zeCommandQueueCreateResult));
        return false;
    }

    log<Verbosity::info>("Command queue created successfully! Handle = %p", static_cast<void *>(queue));
    return true;
}

bool executeCommandLists(ze_command_queue_handle_t queue, uint32_t numCmdLists, ze_command_list_handle_t *cmdLists,
                         ze_fence_handle_t fence) {
    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    const auto zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(queue, numCmdLists, cmdLists, fence);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return false;
    }

    log<Verbosity::info>("Execution started!");
    return true;
}

bool synchronizeCommandQueue(ze_command_queue_handle_t queue) {
    log<Verbosity::info>("Waiting for finishing execution via zeCommandQueueSynchronize()!");

    const auto zeCommandQueueSynchronizeResult = zeCommandQueueSynchronize(queue, UINT64_MAX);
    if (zeCommandQueueSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueSynchronize() call has failed! Error code = %d", static_cast<int>(zeCommandQueueSynchronizeResult));
        return false;
    }

    log<Verbosity::info>("Execution finished!");
    return true;
}

bool destroyCommandQueue(ze_command_queue_handle_t &queue) {
    const auto zeCommandQueueDestroyResult = zeCommandQueueDestroy(queue);
    if (zeCommandQueueDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueDestroy() call has failed! Error code = %d", static_cast<int>(zeCommandQueueDestroyResult));
        return false;
    }

    queue = nullptr;
    log<Verbosity::info>("L0 command queue has been destroyed!");

    return true;
}

bool createCommandList(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal,
                       ze_command_list_handle_t &list) {
    ze_command_list_desc_t commandListDescription = {ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC, nullptr, ordinal, 0};
    const auto zeCommandListCreateResult = zeCommandListCreate(context, device, &commandListDescription, &list);
    if (zeCommandListCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListCreate() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListCreateResult));
        return false;
    }

    log<Verbosity::info>("Command list created successfully! Handle = %p", static_cast<void *>(list));
    return true;
}

bool createImmediateCommandList(ze_context_handle_t context, ze_device_handle_t device, uint32_t ordinal,
                                ze_command_queue_mode_t mode, ze_command_list_handle_t &list) {
    ze_command_queue_desc_t queueDescription{};

    queueDescription.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    queueDescription.mode = mode;
    queueDescription.priority = ZE_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDescription.ordinal = ordinal;

    const auto zeCommandListCreateImmediateResult = zeCommandListCreateImmediate(context, device, &queueDescription, &list);
    if (zeCommandListCreateImmediateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListCreateImmediate() call has failed! Error code = %d", static_cast<int>(zeCommandListCreateImmediateResult));
        return false;
    }

    log<Verbosity::info>("Command list created successfully! Handle = %p", static_cast<void *>(list));
    return true;
}

bool appendMemoryCopy(ze_command_list_handle_t cmdList,
                      void *destination,
                      const void *source,
                      size_t size,
                      ze_event_handle_t signalEvent,
                      uint32_t waitEventsCount,
                      ze_event_handle_t *waitEvents) {
    log<Verbosity::info>("Appending memory copy operation to command list!");

    const auto zeCommandListAppendMemoryCopyResult = zeCommandListAppendMemoryCopy(cmdList,
                                                                                   destination,
                                                                                   source,
                                                                                   size,
                                                                                   signalEvent,
                                                                                   waitEventsCount,
                                                                                   waitEvents);
    if (zeCommandListAppendMemoryCopyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryCopy() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryCopyResult));
        return false;
    }

    log<Verbosity::info>("Memory copy operation appended successfuly!");
    return true;
}

bool appendMemoryFill(ze_command_list_handle_t cmdList,
                      void *destination,
                      const void *pattern,
                      size_t patternSize,
                      size_t bufferSize,
                      ze_event_handle_t signalEvent,
                      uint32_t waitEventsCount,
                      ze_event_handle_t *waitEvents) {
    log<Verbosity::info>("Appending memory fill operation to command list!");

    const auto zeCommandListAppendMemoryFillResult = zeCommandListAppendMemoryFill(cmdList,
                                                                                   destination,
                                                                                   pattern,
                                                                                   patternSize,
                                                                                   bufferSize,
                                                                                   signalEvent,
                                                                                   waitEventsCount,
                                                                                   waitEvents);
    if (zeCommandListAppendMemoryFillResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryFill() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryFillResult));
        return false;
    }

    log<Verbosity::info>("Memory fill operation appended successfully!");
    return true;
}

bool closeCommandList(ze_command_list_handle_t list) {
    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    const auto zeCommandListCloseResult = zeCommandListClose(list);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return false;
    }

    log<Verbosity::info>("Command list closed succesfully!");
    return true;
}

bool resetCommandList(ze_command_list_handle_t list) {
    log<Verbosity::info>("Resetting command list via zeCommandListReset()!");

    const auto zeCommandListResetResult = zeCommandListReset(list);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return false;
    }

    log<Verbosity::info>("Command list reset succesfully!");
    return true;
}

bool destroyCommandList(ze_command_list_handle_t &list) {
    const auto zeCommandListDestroyResult = zeCommandListDestroy(list);
    if (zeCommandListDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListDestroy() call has failed! Error code = %d", static_cast<int>(zeCommandListDestroyResult));
        return false;
    }

    list = nullptr;
    log<Verbosity::info>("L0 command list has been destroyed!");

    return true;
}

bool allocateHostMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, void *&usmHostBuffer, const void *descPNext) {
    ze_host_mem_alloc_desc_t hostMemAllocDesc = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC, descPNext};

    const auto zeMemAllocHostResult = zeMemAllocHost(context, &hostMemAllocDesc, bufferSize, alignment, &usmHostBuffer);
    if (zeMemAllocHostResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocHost() call has failed! Error code: %d", static_cast<int>(zeMemAllocHostResult));
        return false;
    }

    log<Verbosity::info>("zeMemAllocHost() returned success. Checking returned pointer...");

    if (usmHostBuffer == nullptr) {
        log<Verbosity::error>("zeMemAllocHost() returned nullptr! This should not happen! Validation failed!");
        return false;
    }

    log<Verbosity::info>("zeMemAllocHost() returned non-null pointer! usmHostBuffer = %p", usmHostBuffer);
    return true;
}

bool allocateSharedMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, ze_device_handle_t device, void *&usmSharedBuffer) {
    ze_host_mem_alloc_desc_t hostMemAllocDesc = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC};

    ze_device_mem_alloc_desc_t deviceMemAllocDesc = {ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC};
    deviceMemAllocDesc.flags = ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED;
    deviceMemAllocDesc.ordinal = 0;

    const auto zeMemAllocSharedResult = zeMemAllocShared(context, &deviceMemAllocDesc, &hostMemAllocDesc, bufferSize, alignment, device, &usmSharedBuffer);
    if (zeMemAllocSharedResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocShared() call has failed! Error code: %d", static_cast<int>(zeMemAllocSharedResult));
        return false;
    }

    log<Verbosity::info>("zeMemAllocShared() returned success. Checking returned pointer...");

    if (usmSharedBuffer == nullptr) {
        log<Verbosity::error>("zeMemAllocShared() returned nullptr! This should not happen! Validation failed!");
        return false;
    }

    log<Verbosity::info>("zeMemAllocShared() returned non-null pointer! usmSharedBuffer = %p", usmSharedBuffer);
    return true;
}

bool allocateDeviceMemory(ze_context_handle_t context, size_t bufferSize, size_t alignment, ze_device_handle_t device, void *&usmDeviceBuffer, const void *descPNext) {
    ze_device_mem_alloc_desc_t deviceMemAllocDesc = {ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC, descPNext};
    deviceMemAllocDesc.flags = ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED;
    deviceMemAllocDesc.ordinal = 0;

    const auto zeMemAllocDeviceResult = zeMemAllocDevice(context, &deviceMemAllocDesc, bufferSize, alignment, device, &usmDeviceBuffer);
    if (zeMemAllocDeviceResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocDevice() call has failed! Error code: %d", static_cast<int>(zeMemAllocDeviceResult));
        return false;
    }

    log<Verbosity::info>("zeMemAllocDevice() returned success. Checking returned pointer...");

    if (usmDeviceBuffer == nullptr) {
        log<Verbosity::error>("zeMemAllocDevice() returned nullptr! This should not happen! Validation failed!");
        return false;
    }

    log<Verbosity::info>("zeMemAllocDevice() returned non-null pointer! usmDeviceBuffer = %p", usmDeviceBuffer);
    return true;
}

bool freeMemory(ze_context_handle_t context, void *&buffer) {
    const auto zeMemFreeResult = zeMemFree(context, buffer);
    if (zeMemFreeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemFree() call has failed! Error code: %d", static_cast<int>(zeMemFreeResult));
        return false;
    }

    buffer = nullptr;
    log<Verbosity::info>("Memory has been freed successfuly!");

    return true;
}

bool closeMemIpcHandle(ze_context_handle_t context, void *ptr) {
    const auto zeMemCloseIpcHandleResult = zeMemCloseIpcHandle(context, ptr);
    if (zeMemCloseIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemCloseIpcHandle() failed! Error code: %d", static_cast<int>(zeMemCloseIpcHandleResult));
        return false;
    }

    log<Verbosity::info>("Successfully closed the opened IPC handle!");
    return true;
}

bool createEventPool(ze_context_handle_t context, uint32_t eventsCount, ze_device_handle_t *poolDevices, uint32_t devicesCount, ze_event_pool_handle_t &eventPool) {
    log<Verbosity::info>("Creating event pool via zeEventPoolCreate()!");

    ze_event_pool_desc_t eventPoolDescription{};
    eventPoolDescription.count = eventsCount;
    eventPoolDescription.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE | ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP | ZE_EVENT_POOL_FLAG_IPC;

    const auto zeEventPoolCreateResult = zeEventPoolCreate(context, &eventPoolDescription, devicesCount, poolDevices, &eventPool);
    if (zeEventPoolCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolCreate() call has failed! Error code: %d", static_cast<int>(zeEventPoolCreateResult));
        return false;
    }

    log<Verbosity::info>("Event pool has been created successfully! Handle = %p", static_cast<void *>(eventPool));
    return true;
}

bool synchronizeViaEvent(ze_event_handle_t event) {
    log<Verbosity::info>("Waiting for finish of execution via zeEventHostSynchronize()!");

    const auto zeEventHostSynchronizeResult = zeEventHostSynchronize(event, UINT64_MAX);
    if (zeEventHostSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventHostSynchronize() call has failed! Error code = %d", static_cast<int>(zeEventHostSynchronizeResult));
        return false;
    }

    log<Verbosity::info>("zeEventHostSynchronize() completed for event = %p!", event);
    return true;
}

bool destroyEventPool(ze_event_pool_handle_t &eventPool) {
    log<Verbosity::info>("Destroying event pool via zeEventPoolDestroy()!");

    const auto zeEventPoolDestroyResult = zeEventPoolDestroy(eventPool);
    if (zeEventPoolDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolDestroy() call has failed! Error code = %d", static_cast<int>(zeEventPoolDestroyResult));
        return false;
    }

    eventPool = nullptr;
    log<Verbosity::info>("Destruction of event pool has been successful!");

    return true;
}

bool createEvent(ze_event_pool_handle_t eventPool, uint32_t index, ze_event_handle_t &event) {
    log<Verbosity::info>("Creating an event via zeEventCreate()!");

    ze_event_desc_t eventDesc{};
    eventDesc.index = index;
    eventDesc.wait = ZE_EVENT_SCOPE_FLAG_HOST;

    const auto zeEventCreateResult = zeEventCreate(eventPool, &eventDesc, &event);
    if (zeEventCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventCreate() call has failed! Error code = %d", static_cast<int>(zeEventCreateResult));
        return false;
    }

    log<Verbosity::info>("Event has been created successfully! Handle = %p", static_cast<void *>(event));
    return true;
}

bool destroyEvent(ze_event_handle_t &event) {
    log<Verbosity::info>("Destroying event via zeEventDestroy()!");

    const auto zeEventDestroyResult = zeEventDestroy(event);
    if (zeEventDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventDestroy() call has failed! Error code: %d", static_cast<int>(zeEventDestroyResult));
        return false;
    }

    event = nullptr;
    log<Verbosity::info>("Event destruction has been successful!");

    return true;
}

bool createFence(ze_command_queue_handle_t queue, ze_fence_handle_t &fence) {
    log<Verbosity::info>("Creating fence via zeFenceCreate()!");

    ze_fence_desc_t fenceDesc{};
    const auto zeFenceCreateResult = zeFenceCreate(queue, &fenceDesc, &fence);
    if (zeFenceCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceCreate() call has failed! Error code = %d", static_cast<int>(zeFenceCreateResult));
        return false;
    }

    log<Verbosity::info>("Successfully created a fence! Handle = %p", static_cast<void *>(fence));
    return true;
}

bool synchronizeViaFence(ze_fence_handle_t fence) {
    log<Verbosity::info>("Waiting for finish of command queue via zeFenceHostSynchronize()!");

    const auto zeFenceHostSynchronizeResult = zeFenceHostSynchronize(fence, UINT64_MAX);
    if (zeFenceHostSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceHostSynchronize() call has failed! Error code = %d",
                              static_cast<int>(zeFenceHostSynchronizeResult));
        return false;
    }

    log<Verbosity::info>("Execution finished!");
    return true;
}

bool resetFence(ze_fence_handle_t fence) {
    log<Verbosity::info>("Resetting fence via zeFenceReset()!");

    const auto zeFenceResetResult = zeFenceReset(fence);
    if (zeFenceResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceReset() call has failed! Error code = %d", static_cast<int>(zeFenceResetResult));
        return false;
    }

    log<Verbosity::info>("zeFenceReset() has been successful!");
    return true;
}

bool destroyFence(ze_fence_handle_t &fence) {
    log<Verbosity::info>("Destroying fence via zeFenceDestroy()!");

    const auto zeFenceDestroyResult = zeFenceDestroy(fence);
    if (zeFenceDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceDestroy() call has failed! Error code = %d", static_cast<int>(zeFenceDestroyResult));
        return false;
    }

    fence = nullptr;
    log<Verbosity::info>("Fence destruction has been successful!");

    return true;
}

bool fillBufferOnHostViaMemset(void *buffer, int value, size_t bufferSize) {
    log<Verbosity::info>("Filling buffer (%p) of size (%zd) with value (%d)", buffer, bufferSize, value);
    std::memset(buffer, value, bufferSize);

    log<Verbosity::info>("Fill operation was successful!");
    return true;
}

bool verifyMemoryCopyResults(const void *sourceBuffer, const void *destinationBuffer, size_t bufferSize) {
    log<Verbosity::info>("Validating results of copying buffer!");

    const auto src = static_cast<const char *>(sourceBuffer);
    const auto dst = static_cast<const char *>(destinationBuffer);

    for (size_t i = 0; i < bufferSize; ++i) {
        if (src[i] != dst[i]) {
            log<Verbosity::error>("Destination contains invalid value! Expected: %d, Actual: %d at index %zd.",
                                  static_cast<int>(src[i]), static_cast<int>(dst[i]), i);
            return false;
        }
    }

    log<Verbosity::info>("Validation passed!");
    return true;
}

bool verifyMemoryFillResults(const void *destination, size_t destinationSize, const void *pattern, size_t patternSize) {
    log<Verbosity::info>("Validating results of filling buffer!");

    const auto src = static_cast<const char *>(pattern);
    const auto dst = static_cast<const char *>(destination);

    for (size_t i = 0; i < destinationSize; ++i) {
        if (src[i % patternSize] != dst[i]) {
            log<Verbosity::error>("Destination contains invalid value! Expected: %d, Actual: %d at index %zd.",
                                  static_cast<int>(src[i % patternSize]), static_cast<int>(dst[i]), i);
            return false;
        }
    }

    log<Verbosity::info>("Validation passed!");
    return true;
}

bool generateSpirv(std::vector<uint8_t> &spirv, const char *source) {
    log<Verbosity::info>("Compiling OCLC kernels to SPIR-V via libocloc.so!");

    DynamicLibrary oclocLib{"libocloc.so"};
    if (!oclocLib.isLoaded()) {
        log<Verbosity::error>("Could not find libocloc.so!");
        return false;
    }

    using OclocInvokeFunT = int(unsigned int, const char *[], const uint32_t, const uint8_t **, const uint64_t *,
                                const char **, const uint32_t, const uint8_t **, const uint64_t *, const char **,
                                uint32_t *, uint8_t ***, uint64_t **, char ***);

    auto *oclocInvoke = oclocLib.getFunction<OclocInvokeFunT>("oclocInvoke");
    if (!oclocInvoke) {
        log<Verbosity::error>("Cannot find oclocInvoke() function inside libocloc.so!");
        return false;
    }

    using OclocFreeOutputFunT = int(uint32_t *, uint8_t ***, uint64_t **, char ***);

    auto *oclocFreeOutput = oclocLib.getFunction<OclocFreeOutputFunT>("oclocFreeOutput");
    if (!oclocFreeOutput) {
        log<Verbosity::error>("Cannot find oclocFreeOutput() function inside libocloc.so!");
        return false;
    }

    std::array oclocArgs = {"ocloc", "-file", "kernel.cl", "-spv_only"};
    std::array sources = {reinterpret_cast<const unsigned char *>(source)};
    std::array sourcesLengths = {strlen(source) + 1};
    std::array sourcesNames = {"kernel.cl"};

    uint32_t numOutputs = 0U;
    uint8_t **outputs = nullptr;
    uint64_t *ouputLengths = nullptr;
    char **outputNames = nullptr;

    const auto compilationResult = oclocInvoke(oclocArgs.size(), oclocArgs.data(), sources.size(), sources.data(),
                                               sourcesLengths.data(), sourcesNames.data(), 0, nullptr, nullptr, nullptr,
                                               &numOutputs, &outputs, &ouputLengths, &outputNames);
    if (compilationResult != 0) {
        log<Verbosity::error>("Compilation via ocloc lib has failed! Error code = %d",
                              static_cast<int>(compilationResult));
        return false;
    }

    unsigned char *spirV = nullptr;
    size_t spirVlen = 0;

    for (unsigned int i = 0; i < numOutputs; ++i) {
        auto nameLen = strlen(outputNames[i]);
        if ((nameLen > 4) && (strstr(&outputNames[i][nameLen - 4], ".spv") != nullptr)) {
            spirV = outputs[i];
            spirVlen = ouputLengths[i];
            break;
        }
    }

    if (!spirV) {
        log<Verbosity::error>("Could not get generated SPIR-V file!");
        return false;
    }

    spirv.resize(spirVlen);
    std::memcpy(spirv.data(), spirV, spirVlen);

    oclocFreeOutput(&numOutputs, &outputs, &ouputLengths, &outputNames);
    return true;
}

bool createModule(ze_context_handle_t context, ze_device_handle_t device, const std::vector<uint8_t> &binary,
                  ze_module_format_t binaryFormat, ze_module_handle_t &module, const char *flags) {
    log<Verbosity::info>("Creating module via zeModuleCreate()!");

    ze_module_desc_t moduleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC, nullptr, binaryFormat, binary.size(), binary.data(), flags, nullptr};

    ze_module_build_log_handle_t buildLog{};

    auto zeModuleCreateResult = zeModuleCreate(context, device, &moduleDescription, &module, &buildLog);
    if (zeModuleCreateResult == ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("Module creation succeeded! Module = %p", static_cast<void *>(module));
    } else {
        log<Verbosity::error>("zeModuleCreate() has failed! Error code: %d", static_cast<int>(zeModuleCreateResult));
    }

    if (checkBuildLog(buildLog)) {
        log<Verbosity::info>("Build log checking succeeded!");
    } else {
        log<Verbosity::error>("build log checking has failed!");
    }

    return zeModuleCreateResult == ZE_RESULT_SUCCESS;
}

bool destroyModule(ze_module_handle_t &module) {
    const auto zeModuleDestroyResult = zeModuleDestroy(module);
    if (zeModuleDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleDestroy() call has failed for moduleHandle! Error code = %d",
                              static_cast<int>(zeModuleDestroyResult));
        return false;
    }

    module = nullptr;
    log<Verbosity::info>("Module has been destroyed!");

    return true;
}

bool checkBuildLog(ze_module_build_log_handle_t buildLog) {
    log<Verbosity::info>("Getting build log size!");

    size_t buildLogSize{0};
    auto zeModuleBuildLogGetStringResult = zeModuleBuildLogGetString(buildLog, &buildLogSize, nullptr);
    if (zeModuleBuildLogGetStringResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleBuildLogGetString() call has failed! Error code = %d",
                              static_cast<int>(zeModuleBuildLogGetStringResult));
        return false;
    }

    log<Verbosity::info>("Build log size is %zd!", buildLogSize);
    if (buildLogSize > 0) {
        log<Verbosity::info>("Getting build log!");

        std::string buildLogStr{};
        buildLogStr.resize(buildLogSize + 1);

        zeModuleBuildLogGetStringResult = zeModuleBuildLogGetString(buildLog, &buildLogSize, buildLogStr.data());
        if (zeModuleBuildLogGetStringResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeModuleBuildLogGetString() call has failed! Error code = %d",
                                  static_cast<int>(zeModuleBuildLogGetStringResult));
            return false;
        }

        log<Verbosity::info>("Build log : %s", buildLogStr.c_str());
    } else {
        log<Verbosity::info>("Build log is empty!");
    }

    log<Verbosity::info>("Destroying module build log via zeModuleBuildLogDestroy()!");

    auto zeModuleBuildLogDestroyResult = zeModuleBuildLogDestroy(buildLog);
    if (zeModuleBuildLogDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleBuildLogDestroy() call has failed! Error code = %d",
                              static_cast<int>(zeModuleBuildLogDestroyResult));
        return false;
    }

    log<Verbosity::info>("Destruction of L0 module build log has been successful!");
    return true;
}

} // namespace Cal::Testing::Utils::LevelZero
