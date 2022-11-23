/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeInit(ze_init_flags_t flags);

ze_result_t zeDriverGet(uint32_t *pCount, ze_driver_handle_t *phDrivers);
ze_result_t zeDriverGetProperties(ze_driver_handle_t hDriver, ze_driver_properties_t *pDriverProperties);
ze_result_t zeDriverGetIpcProperties(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t *pIpcProperties);
ze_result_t zeDriverGetExtensionProperties(ze_driver_handle_t hDriver, uint32_t *pCount, ze_driver_extension_properties_t *pExtensionProperties);

ze_result_t zeDeviceGet(ze_driver_handle_t hDriver, uint32_t *pCount, ze_device_handle_t *phDevices);
ze_result_t zeDeviceGetSubDevices(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_handle_t *phDevices);
ze_result_t zeDeviceGetProperties(ze_device_handle_t hDevice, ze_device_properties_t *pDeviceProperties);
ze_result_t zeDeviceGetComputeProperties(ze_device_handle_t hDevice, ze_device_compute_properties_t *pComputeProperties);
ze_result_t zeDeviceGetModuleProperties(ze_device_handle_t hDevice, ze_device_module_properties_t *pModuleProperties);
ze_result_t zeDeviceGetMemoryAccessProperties(ze_device_handle_t hDevice, ze_device_memory_access_properties_t *pMemAccessProperties);
ze_result_t zeDeviceGetImageProperties(ze_device_handle_t hDevice, ze_device_image_properties_t *pImageProperties);
ze_result_t zeDeviceGetExternalMemoryProperties(ze_device_handle_t hDevice, ze_device_external_memory_properties_t *pExternalMemoryProperties);
ze_result_t zeDeviceGetCacheProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_cache_properties_t *pCacheProperties);
ze_result_t zeDeviceGetCommandQueueGroupProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_command_queue_group_properties_t *pCommandQueueGroupProperties);
ze_result_t zeDeviceGetMemoryProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_memory_properties_t *pMemProperties);

ze_result_t zeCommandQueueExecuteCommandLists(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeCommandQueueSynchronize(ze_command_queue_handle_t hCommandQueue, uint64_t timeout);

ze_result_t zeEventHostSynchronize(ze_event_handle_t hEvent, uint64_t timeout);
ze_result_t zeFenceHostSynchronize(ze_fence_handle_t hFence, uint64_t timeout);

ze_result_t zeEventPoolGetIpcHandle(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t *phIpc);
ze_result_t zeEventPoolOpenIpcHandle(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t *phEventPool);

ze_result_t zeMemGetAllocProperties(ze_context_handle_t hContext, const void *ptr, ze_memory_allocation_properties_t *pMemAllocProperties, ze_device_handle_t *phDevice);
ze_result_t zeMemAllocHost(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, void **pptr);
ze_result_t zeMemAllocShared(ze_context_handle_t hContext,
                             const ze_device_mem_alloc_desc_t *device_desc,
                             const ze_host_mem_alloc_desc_t *host_desc,
                             size_t size, size_t alignment,
                             ze_device_handle_t hDevice,
                             void **pptr);

ze_result_t zeModuleGetProperties(ze_module_handle_t hModule, ze_module_properties_t *pModuleProperties);
ze_result_t zeKernelSetArgumentValue(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void *pArgValue);
ze_result_t zeKernelGetProperties(ze_kernel_handle_t hKernel, ze_kernel_properties_t *pKernelProperties);

} // namespace Cal::Icd::LevelZero
