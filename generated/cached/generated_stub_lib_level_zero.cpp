/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "level_zero/ze_api.h"
#include "level_zero/zes_api.h"
#include "level_zero/zet_ddi.h"

ze_result_t zesDeviceReset(zes_device_handle_t hDevice, ze_bool_t force){
   return {};
}

ze_result_t zesDeviceResetExt(zes_device_handle_t hDevice, zes_reset_properties_t* pProperties){
   return {};
}

ze_result_t zesDeviceGetState(zes_device_handle_t hDevice, zes_device_state_t* pState){
   return {};
}

ze_result_t zesDeviceProcessesGetState(zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses){
   return {};
}

ze_result_t zesDevicePciGetProperties(zes_device_handle_t hDevice, zes_pci_properties_t* pProperties){
   return {};
}

ze_result_t zesDevicePciGetState(zes_device_handle_t hDevice, zes_pci_state_t* pState){
   return {};
}

ze_result_t zesDevicePciGetBars(zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties){
   return {};
}

ze_result_t zesDevicePciGetStats(zes_device_handle_t hDevice, zes_pci_stats_t* pStats){
   return {};
}

ze_result_t zesDeviceGetProperties(zes_device_handle_t hDevice, zes_device_properties_t* pProperties){
   return {};
}

ze_result_t zesDeviceEnumMemoryModules(zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory){
   return {};
}

ze_result_t zeInit(ze_init_flags_t flags){
   return {};
}

ze_result_t zeCommandListCreate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList){
   return {};
}

ze_result_t zeCommandListCreateImmediate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList){
   return {};
}

ze_result_t zeCommandListDestroy(ze_command_list_handle_t hCommandList){
   return {};
}

ze_result_t zeCommandListClose(ze_command_list_handle_t hCommandList){
   return {};
}

ze_result_t zeCommandListReset(ze_command_list_handle_t hCommandList){
   return {};
}

ze_result_t zeCommandListAppendWriteGlobalTimestamp(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandQueueCreate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue){
   return {};
}

ze_result_t zeCommandQueueDestroy(ze_command_queue_handle_t hCommandQueue){
   return {};
}

ze_result_t zeCommandQueueExecuteCommandLists(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence){
   return {};
}

ze_result_t zeCommandQueueSynchronize(ze_command_queue_handle_t hCommandQueue, uint64_t timeout){
   return {};
}

ze_result_t zeContextCreate(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext){
   return {};
}

ze_result_t zeContextCreateEx(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext){
   return {};
}

ze_result_t zeContextDestroy(ze_context_handle_t hContext){
   return {};
}

ze_result_t zeContextGetStatus(ze_context_handle_t hContext){
   return {};
}

ze_result_t zeCommandListAppendMemoryCopy(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendMemoryFill(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendMemoryPrefetch(ze_command_list_handle_t hCommandList, const void* ptr, size_t size){
   return {};
}

ze_result_t zeCommandListAppendMemAdvise(ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice){
   return {};
}

ze_result_t zeDeviceGet(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices){
   return {};
}

ze_result_t zeDeviceGetSubDevices(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices){
   return {};
}

ze_result_t zeDeviceGetProperties(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties){
   return {};
}

ze_result_t zeDeviceGetComputeProperties(ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties){
   return {};
}

ze_result_t zeDeviceGetModuleProperties(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties){
   return {};
}

ze_result_t zeDeviceGetCommandQueueGroupProperties(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties){
   return {};
}

ze_result_t zeDeviceGetMemoryProperties(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties){
   return {};
}

ze_result_t zeDeviceGetMemoryAccessProperties(ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties){
   return {};
}

ze_result_t zeDeviceGetCacheProperties(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties){
   return {};
}

ze_result_t zeDeviceGetImageProperties(ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties){
   return {};
}

ze_result_t zeDeviceGetExternalMemoryProperties(ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties){
   return {};
}

ze_result_t zeDeviceGetP2PProperties(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties){
   return {};
}

ze_result_t zeDeviceCanAccessPeer(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value){
   return {};
}

ze_result_t zeDeviceGetStatus(ze_device_handle_t hDevice){
   return {};
}

ze_result_t zeDeviceGetGlobalTimestamps(ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp){
   return {};
}

ze_result_t zeDeviceReserveCacheExt(ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize){
   return {};
}

ze_result_t zeDeviceSetCacheAdviceExt(ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion){
   return {};
}

ze_result_t zeDriverGet(uint32_t* pCount, ze_driver_handle_t* phDrivers){
   return {};
}

ze_result_t zeDriverGetApiVersion(ze_driver_handle_t hDriver, ze_api_version_t* version){
   return {};
}

ze_result_t zeDriverGetProperties(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties){
   return {};
}

ze_result_t zeDriverGetIpcProperties(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties){
   return {};
}

ze_result_t zeDriverGetExtensionProperties(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties){
   return {};
}

ze_result_t zeDriverGetExtensionFunctionAddress(ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress){
   return {};
}

ze_result_t zeEventPoolCreate(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool){
   return {};
}

ze_result_t zeEventPoolDestroy(ze_event_pool_handle_t hEventPool){
   return {};
}

ze_result_t zeEventCreate(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent){
   return {};
}

ze_result_t zeEventDestroy(ze_event_handle_t hEvent){
   return {};
}

ze_result_t zeEventPoolGetIpcHandle(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc){
   return {};
}

ze_result_t zeEventPoolOpenIpcHandle(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool){
   return {};
}

ze_result_t zeEventPoolCloseIpcHandle(ze_event_pool_handle_t hEventPool){
   return {};
}

ze_result_t zeCommandListAppendBarrier(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendSignalEvent(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent){
   return {};
}

ze_result_t zeCommandListAppendWaitOnEvents(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents){
   return {};
}

ze_result_t zeEventHostSignal(ze_event_handle_t hEvent){
   return {};
}

ze_result_t zeEventHostSynchronize(ze_event_handle_t hEvent, uint64_t timeout){
   return {};
}

ze_result_t zeEventQueryStatus(ze_event_handle_t hEvent){
   return {};
}

ze_result_t zeCommandListAppendEventReset(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent){
   return {};
}

ze_result_t zeEventHostReset(ze_event_handle_t hEvent){
   return {};
}

ze_result_t zeEventQueryKernelTimestamp(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr){
   return {};
}

ze_result_t zeFenceCreate(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence){
   return {};
}

ze_result_t zeFenceDestroy(ze_fence_handle_t hFence){
   return {};
}

ze_result_t zeFenceHostSynchronize(ze_fence_handle_t hFence, uint64_t timeout){
   return {};
}

ze_result_t zeFenceQueryStatus(ze_fence_handle_t hFence){
   return {};
}

ze_result_t zeFenceReset(ze_fence_handle_t hFence){
   return {};
}

ze_result_t zeKernelSetGlobalOffsetExp(ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ){
   return {};
}

ze_result_t zeImageGetProperties(ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties){
   return {};
}

ze_result_t zeImageCreate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage){
   return {};
}

ze_result_t zeImageDestroy(ze_image_handle_t hImage){
   return {};
}

ze_result_t zeKernelSchedulingHintExp(ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint){
   return {};
}

ze_result_t zeMemAllocShared(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr){
   return {};
}

ze_result_t zeMemAllocDevice(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr){
   return {};
}

ze_result_t zeMemAllocHost(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr){
   return {};
}

ze_result_t zeMemFree(ze_context_handle_t hContext, void* ptr){
   return {};
}

ze_result_t zeMemGetAllocProperties(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice){
   return {};
}

ze_result_t zeMemGetAddressRange(ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize){
   return {};
}

ze_result_t zeMemGetIpcHandle(ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle){
   return {};
}

ze_result_t zeMemOpenIpcHandle(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr){
   return {};
}

ze_result_t zeMemCloseIpcHandle(ze_context_handle_t hContext, const void* ptr){
   return {};
}

ze_result_t zeModuleCreate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog){
   return {};
}

ze_result_t zeModuleDestroy(ze_module_handle_t hModule){
   return {};
}

ze_result_t zeModuleDynamicLink(uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog){
   return {};
}

ze_result_t zeModuleBuildLogDestroy(ze_module_build_log_handle_t hModuleBuildLog){
   return {};
}

ze_result_t zeModuleBuildLogGetString(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog){
   return {};
}

ze_result_t zeModuleGetNativeBinary(ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary){
   return {};
}

ze_result_t zeModuleGetGlobalPointer(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr){
   return {};
}

ze_result_t zeModuleGetKernelNames(ze_module_handle_t hModule, uint32_t* pCount, const char** pNames){
   return {};
}

ze_result_t zeModuleGetProperties(ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties){
   return {};
}

ze_result_t zeKernelCreate(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel){
   return {};
}

ze_result_t zeKernelDestroy(ze_kernel_handle_t hKernel){
   return {};
}

ze_result_t zeModuleGetFunctionPointer(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction){
   return {};
}

ze_result_t zeKernelSetGroupSize(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ){
   return {};
}

ze_result_t zeKernelSuggestGroupSize(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ){
   return {};
}

ze_result_t zeKernelSuggestMaxCooperativeGroupCount(ze_kernel_handle_t hKernel, uint32_t* totalGroupCount){
   return {};
}

ze_result_t zeKernelSetArgumentValue(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue){
   return {};
}

ze_result_t zeKernelSetIndirectAccess(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags){
   return {};
}

ze_result_t zeKernelGetIndirectAccess(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags){
   return {};
}

ze_result_t zeKernelSetCacheConfig(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags){
   return {};
}

ze_result_t zeKernelGetProperties(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties){
   return {};
}

ze_result_t zeKernelGetName(ze_kernel_handle_t hKernel, size_t* pSize, char* pName){
   return {};
}

ze_result_t zeCommandListAppendLaunchKernel(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendLaunchKernelIndirect(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListHostSynchronize(ze_command_list_handle_t hCommandList, uint64_t timeout){
   return {};
}

ze_result_t zeDevicePciGetPropertiesExt(ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties){
   return {};
}

ze_result_t zeContextMakeMemoryResident(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size){
   return {};
}

ze_result_t zeContextEvictMemory(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size){
   return {};
}

ze_result_t zeVirtualMemReserve(ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr){
   return {};
}

ze_result_t zeVirtualMemFree(ze_context_handle_t hContext, const void* ptr, size_t size){
   return {};
}

ze_result_t zeVirtualMemQueryPageSize(ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize){
   return {};
}

ze_result_t zePhysicalMemCreate(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory){
   return {};
}

ze_result_t zePhysicalMemDestroy(ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory){
   return {};
}

ze_result_t zeVirtualMemMap(ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access){
   return {};
}

ze_result_t zeVirtualMemUnmap(ze_context_handle_t hContext, const void* ptr, size_t size){
   return {};
}

ze_result_t zeVirtualMemSetAccessAttribute(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access){
   return {};
}

ze_result_t zeVirtualMemGetAccessAttribute(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize){
   return {};
}

// #### Generated code -- end ####
