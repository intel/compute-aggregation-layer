/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####
#include "icd/icd_global_state.h"
#include "shared/rpc.h"
#include "icd/icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"

#include <cstdlib>

namespace Cal {
namespace Icd {
namespace LevelZero {
ze_result_t zeInitRpcHelper (ze_init_flags_t flags);
ze_result_t zeCommandListCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList);
ze_result_t zeCommandListCreateImmediate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList);
ze_result_t zeCommandListDestroy (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListClose (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListReset (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandQueueCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue);
ze_result_t zeCommandQueueExecuteCommandListsRpcHelper (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::ShmemTransferDesc* transferDescs);
ze_result_t zeCommandQueueSynchronizeRpcHelper (ze_command_queue_handle_t hCommandQueue, uint64_t timeout);
ze_result_t zeContextCreate (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext);
ze_result_t zeContextCreateEx (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext);
ze_result_t zeContextDestroy (ze_context_handle_t hContext);
ze_result_t zeContextGetStatus (ze_context_handle_t hContext);
ze_result_t zeCommandListAppendMemoryCopy (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2Malloc (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2Malloc (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFill (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeDeviceGetRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
ze_result_t zeDeviceGetSubDevicesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
ze_result_t zeDeviceGetProperties (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties);
ze_result_t zeDeviceGetComputeProperties (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties);
ze_result_t zeDeviceGetModuleProperties (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties);
ze_result_t zeDeviceGetCommandQueueGroupProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
ze_result_t zeDeviceGetMemoryProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
ze_result_t zeDeviceGetMemoryAccessProperties (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties);
ze_result_t zeDeviceGetCacheProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
ze_result_t zeDeviceGetImageProperties (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties);
ze_result_t zeDeviceGetExternalMemoryProperties (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties);
ze_result_t zeDeviceCanAccessPeer (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value);
ze_result_t zeDeviceGetStatus (ze_device_handle_t hDevice);
ze_result_t zeDeviceGetGlobalTimestamps (ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp);
ze_result_t zeDriverGetRpcHelper (uint32_t* pCount, ze_driver_handle_t* phDrivers);
ze_result_t zeDriverGetApiVersion (ze_driver_handle_t hDriver, ze_api_version_t* version);
ze_result_t zeDriverGetProperties (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties);
ze_result_t zeDriverGetIpcProperties (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties);
ze_result_t zeDriverGetExtensionProperties (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
ze_result_t zeDriverGetExtensionFunctionAddress (ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress);
ze_result_t zeEventPoolCreate (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool);
ze_result_t zeEventCreate (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent);
ze_result_t zeEventDestroy (ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendBarrier (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
ze_result_t zeEventHostSynchronizeRpcHelper (ze_event_handle_t hEvent, uint64_t timeout);
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent);
ze_result_t zeEventHostReset (ze_event_handle_t hEvent);
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr);
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence);
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence);
ze_result_t zeFenceHostSynchronizeRpcHelper (ze_fence_handle_t hFence, uint64_t timeout);
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence);
ze_result_t zeFenceReset (ze_fence_handle_t hFence);
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
ze_result_t zeMemAllocSharedRpcHelper (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::ImplicitArgs &implArgsForZeMemAllocSharedRpcM);
ze_result_t zeMemAllocDevice (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
ze_result_t zeMemAllocHostRpcHelper (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocHostRpcM::ImplicitArgs &implArgsForZeMemAllocHostRpcM);
ze_result_t zeMemFree (ze_context_handle_t hContext, void* ptr);
ze_result_t zeMemGetAllocProperties (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice);
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize);
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
ze_result_t zeModuleDestroy (ze_module_handle_t hModule);
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog);
ze_result_t zeModuleBuildLogGetString (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
ze_result_t zeModuleGetNativeBinary (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary);
ze_result_t zeModuleGetGlobalPointer (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
ze_result_t zeModuleGetKernelNames (ze_module_handle_t hModule, uint32_t* pCount, const char** pNames);
ze_result_t zeModuleGetKernelNamesRpcHelper (ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer);
ze_result_t zeModuleGetProperties (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties);
ze_result_t zeKernelCreate (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel);
ze_result_t zeModuleGetFunctionPointer (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
ze_result_t zeKernelSetGroupSize (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ);
ze_result_t zeKernelSuggestGroupSize (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ);
ze_result_t zeKernelSuggestMaxCooperativeGroupCount (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount);
ze_result_t zeKernelSetArgumentValue (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags);
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags);
ze_result_t zeKernelSetCacheConfig (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags);
ze_result_t zeKernelGetProperties (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties);
ze_result_t zeKernelGetName (ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
ze_result_t zeCommandListAppendLaunchKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeDevicePciGetPropertiesExt (ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties);

namespace Unimplemented {
inline void zeCommandListAppendMemoryRangesBarrierUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendMemoryRangesBarrier is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeContextSystemBarrierUnimpl() {
    log<Verbosity::critical>("Function Context.zeContextSystemBarrier is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeDeviceReserveCacheExtUnimpl() {
    log<Verbosity::critical>("Function Device.zeDeviceReserveCacheExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeDeviceSetCacheAdviceExtUnimpl() {
    log<Verbosity::critical>("Function Device.zeDeviceSetCacheAdviceExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendWriteGlobalTimestampUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendWriteGlobalTimestamp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendMemoryCopyRegionUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendMemoryCopyRegion is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendMemoryCopyFromContextUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendMemoryCopyFromContext is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendImageCopyUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendImageCopy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendImageCopyRegionUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendImageCopyRegion is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendImageCopyToMemoryUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendImageCopyToMemory is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendImageCopyFromMemoryUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendImageCopyFromMemory is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendMemoryPrefetchUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendMemoryPrefetch is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendMemAdviseUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendMemAdvise is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeDeviceGetP2PPropertiesUnimpl() {
    log<Verbosity::critical>("Function Device.zeDeviceGetP2PProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeEventPoolGetIpcHandleUnimpl() {
    log<Verbosity::critical>("Function EventPool.zeEventPoolGetIpcHandle is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeEventPoolOpenIpcHandleUnimpl() {
    log<Verbosity::critical>("Function EventPool.zeEventPoolOpenIpcHandle is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeEventPoolCloseIpcHandleUnimpl() {
    log<Verbosity::critical>("Function EventPool.zeEventPoolCloseIpcHandle is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeEventHostSignalUnimpl() {
    log<Verbosity::critical>("Function Event.zeEventHostSignal is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendEventResetUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendEventReset is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendQueryKernelTimestampsUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendQueryKernelTimestamps is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeEventQueryTimestampsExpUnimpl() {
    log<Verbosity::critical>("Function EventExp.zeEventQueryTimestampsExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricVertexGetExpUnimpl() {
    log<Verbosity::critical>("Function FabricVertexExp.zeFabricVertexGetExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricVertexGetSubVerticesExpUnimpl() {
    log<Verbosity::critical>("Function FabricVertexExp.zeFabricVertexGetSubVerticesExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricVertexGetPropertiesExpUnimpl() {
    log<Verbosity::critical>("Function FabricVertexExp.zeFabricVertexGetPropertiesExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricVertexGetDeviceExpUnimpl() {
    log<Verbosity::critical>("Function FabricVertexExp.zeFabricVertexGetDeviceExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeDeviceGetFabricVertexExpUnimpl() {
    log<Verbosity::critical>("Function DeviceExp.zeDeviceGetFabricVertexExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricEdgeGetExpUnimpl() {
    log<Verbosity::critical>("Function FabricEdgeExp.zeFabricEdgeGetExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricEdgeGetVerticesExpUnimpl() {
    log<Verbosity::critical>("Function FabricEdgeExp.zeFabricEdgeGetVerticesExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeFabricEdgeGetPropertiesExpUnimpl() {
    log<Verbosity::critical>("Function FabricEdgeExp.zeFabricEdgeGetPropertiesExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeImageGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Image.zeImageGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeImageCreateUnimpl() {
    log<Verbosity::critical>("Function Image.zeImageCreate is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeImageDestroyUnimpl() {
    log<Verbosity::critical>("Function Image.zeImageDestroy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendImageCopyToMemoryExtUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendImageCopyToMemoryExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendImageCopyFromMemoryExtUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendImageCopyFromMemoryExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeImageGetMemoryPropertiesExpUnimpl() {
    log<Verbosity::critical>("Function ImageExp.zeImageGetMemoryPropertiesExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeImageGetAllocPropertiesExtUnimpl() {
    log<Verbosity::critical>("Function Image.zeImageGetAllocPropertiesExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeImageViewCreateExpUnimpl() {
    log<Verbosity::critical>("Function ImageExp.zeImageViewCreateExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeKernelSchedulingHintExpUnimpl() {
    log<Verbosity::critical>("Function KernelExp.zeKernelSchedulingHintExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeModuleInspectLinkageExtUnimpl() {
    log<Verbosity::critical>("Function Module.zeModuleInspectLinkageExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeMemGetIpcHandleUnimpl() {
    log<Verbosity::critical>("Function Mem.zeMemGetIpcHandle is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeMemOpenIpcHandleUnimpl() {
    log<Verbosity::critical>("Function Mem.zeMemOpenIpcHandle is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeMemCloseIpcHandleUnimpl() {
    log<Verbosity::critical>("Function Mem.zeMemCloseIpcHandle is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeMemFreeExtUnimpl() {
    log<Verbosity::critical>("Function Mem.zeMemFreeExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeModuleDynamicLinkUnimpl() {
    log<Verbosity::critical>("Function Module.zeModuleDynamicLink is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeKernelGetSourceAttributesUnimpl() {
    log<Verbosity::critical>("Function Kernel.zeKernelGetSourceAttributes is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendLaunchCooperativeKernelUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendLaunchCooperativeKernel is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendLaunchKernelIndirectUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendLaunchKernelIndirect is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeCommandListAppendLaunchMultipleKernelsIndirectUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendLaunchMultipleKernelsIndirect is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeContextMakeMemoryResidentUnimpl() {
    log<Verbosity::critical>("Function Context.zeContextMakeMemoryResident is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeContextEvictMemoryUnimpl() {
    log<Verbosity::critical>("Function Context.zeContextEvictMemory is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeContextMakeImageResidentUnimpl() {
    log<Verbosity::critical>("Function Context.zeContextMakeImageResident is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeContextEvictImageUnimpl() {
    log<Verbosity::critical>("Function Context.zeContextEvictImage is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeSamplerCreateUnimpl() {
    log<Verbosity::critical>("Function Sampler.zeSamplerCreate is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeSamplerDestroyUnimpl() {
    log<Verbosity::critical>("Function Sampler.zeSamplerDestroy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemReserveUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemReserve is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemFreeUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemFree is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemQueryPageSizeUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemQueryPageSize is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zePhysicalMemCreateUnimpl() {
    log<Verbosity::critical>("Function PhysicalMem.zePhysicalMemCreate is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zePhysicalMemDestroyUnimpl() {
    log<Verbosity::critical>("Function PhysicalMem.zePhysicalMemDestroy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemMapUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemMap is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemUnmapUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemUnmap is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemSetAccessAttributeUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemSetAccessAttribute is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeVirtualMemGetAccessAttributeUnimpl() {
    log<Verbosity::critical>("Function VirtualMem.zeVirtualMemGetAccessAttribute is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
} // Unimplemented

inline void initL0Ddi(ze_dditable_t &dt){
    dt.Global.pfnInit = Cal::Icd::LevelZero::zeInit;
    dt.CommandList.pfnCreate = Cal::Icd::LevelZero::zeCommandListCreate;
    dt.CommandList.pfnCreateImmediate = Cal::Icd::LevelZero::zeCommandListCreateImmediate;
    dt.CommandList.pfnDestroy = Cal::Icd::LevelZero::zeCommandListDestroy;
    dt.CommandList.pfnClose = Cal::Icd::LevelZero::zeCommandListClose;
    dt.CommandList.pfnReset = Cal::Icd::LevelZero::zeCommandListReset;
    dt.CommandQueue.pfnCreate = Cal::Icd::LevelZero::zeCommandQueueCreate;
    dt.CommandQueue.pfnDestroy = Cal::Icd::LevelZero::zeCommandQueueDestroy;
    dt.CommandQueue.pfnExecuteCommandLists = Cal::Icd::LevelZero::zeCommandQueueExecuteCommandLists;
    dt.CommandQueue.pfnSynchronize = Cal::Icd::LevelZero::zeCommandQueueSynchronize;
    dt.Context.pfnCreate = Cal::Icd::LevelZero::zeContextCreate;
    dt.Context.pfnCreateEx = Cal::Icd::LevelZero::zeContextCreateEx;
    dt.Context.pfnDestroy = Cal::Icd::LevelZero::zeContextDestroy;
    dt.Context.pfnGetStatus = Cal::Icd::LevelZero::zeContextGetStatus;
    dt.CommandList.pfnAppendMemoryCopy = Cal::Icd::LevelZero::zeCommandListAppendMemoryCopy;
    dt.CommandList.pfnAppendMemoryFill = Cal::Icd::LevelZero::zeCommandListAppendMemoryFill;
    dt.Device.pfnGet = Cal::Icd::LevelZero::zeDeviceGet;
    dt.Device.pfnGetSubDevices = Cal::Icd::LevelZero::zeDeviceGetSubDevices;
    dt.Device.pfnGetProperties = Cal::Icd::LevelZero::zeDeviceGetProperties;
    dt.Device.pfnGetComputeProperties = Cal::Icd::LevelZero::zeDeviceGetComputeProperties;
    dt.Device.pfnGetModuleProperties = Cal::Icd::LevelZero::zeDeviceGetModuleProperties;
    dt.Device.pfnGetCommandQueueGroupProperties = Cal::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties;
    dt.Device.pfnGetMemoryProperties = Cal::Icd::LevelZero::zeDeviceGetMemoryProperties;
    dt.Device.pfnGetMemoryAccessProperties = Cal::Icd::LevelZero::zeDeviceGetMemoryAccessProperties;
    dt.Device.pfnGetCacheProperties = Cal::Icd::LevelZero::zeDeviceGetCacheProperties;
    dt.Device.pfnGetImageProperties = Cal::Icd::LevelZero::zeDeviceGetImageProperties;
    dt.Device.pfnGetExternalMemoryProperties = Cal::Icd::LevelZero::zeDeviceGetExternalMemoryProperties;
    dt.Device.pfnCanAccessPeer = Cal::Icd::LevelZero::zeDeviceCanAccessPeer;
    dt.Device.pfnGetStatus = Cal::Icd::LevelZero::zeDeviceGetStatus;
    dt.Device.pfnGetGlobalTimestamps = Cal::Icd::LevelZero::zeDeviceGetGlobalTimestamps;
    dt.Driver.pfnGet = Cal::Icd::LevelZero::zeDriverGet;
    dt.Driver.pfnGetApiVersion = Cal::Icd::LevelZero::zeDriverGetApiVersion;
    dt.Driver.pfnGetProperties = Cal::Icd::LevelZero::zeDriverGetProperties;
    dt.Driver.pfnGetIpcProperties = Cal::Icd::LevelZero::zeDriverGetIpcProperties;
    dt.Driver.pfnGetExtensionProperties = Cal::Icd::LevelZero::zeDriverGetExtensionProperties;
    dt.Driver.pfnGetExtensionFunctionAddress = Cal::Icd::LevelZero::zeDriverGetExtensionFunctionAddress;
    dt.EventPool.pfnCreate = Cal::Icd::LevelZero::zeEventPoolCreate;
    dt.EventPool.pfnDestroy = Cal::Icd::LevelZero::zeEventPoolDestroy;
    dt.Event.pfnCreate = Cal::Icd::LevelZero::zeEventCreate;
    dt.Event.pfnDestroy = Cal::Icd::LevelZero::zeEventDestroy;
    dt.CommandList.pfnAppendBarrier = Cal::Icd::LevelZero::zeCommandListAppendBarrier;
    dt.CommandList.pfnAppendSignalEvent = Cal::Icd::LevelZero::zeCommandListAppendSignalEvent;
    dt.CommandList.pfnAppendWaitOnEvents = Cal::Icd::LevelZero::zeCommandListAppendWaitOnEvents;
    dt.Event.pfnHostSynchronize = Cal::Icd::LevelZero::zeEventHostSynchronize;
    dt.Event.pfnQueryStatus = Cal::Icd::LevelZero::zeEventQueryStatus;
    dt.Event.pfnHostReset = Cal::Icd::LevelZero::zeEventHostReset;
    dt.Event.pfnQueryKernelTimestamp = Cal::Icd::LevelZero::zeEventQueryKernelTimestamp;
    dt.Fence.pfnCreate = Cal::Icd::LevelZero::zeFenceCreate;
    dt.Fence.pfnDestroy = Cal::Icd::LevelZero::zeFenceDestroy;
    dt.Fence.pfnHostSynchronize = Cal::Icd::LevelZero::zeFenceHostSynchronize;
    dt.Fence.pfnQueryStatus = Cal::Icd::LevelZero::zeFenceQueryStatus;
    dt.Fence.pfnReset = Cal::Icd::LevelZero::zeFenceReset;
    dt.KernelExp.pfnSetGlobalOffsetExp = Cal::Icd::LevelZero::zeKernelSetGlobalOffsetExp;
    dt.Mem.pfnAllocShared = Cal::Icd::LevelZero::zeMemAllocShared;
    dt.Mem.pfnAllocDevice = Cal::Icd::LevelZero::zeMemAllocDevice;
    dt.Mem.pfnAllocHost = Cal::Icd::LevelZero::zeMemAllocHost;
    dt.Mem.pfnFree = Cal::Icd::LevelZero::zeMemFree;
    dt.Mem.pfnGetAllocProperties = Cal::Icd::LevelZero::zeMemGetAllocProperties;
    dt.Mem.pfnGetAddressRange = Cal::Icd::LevelZero::zeMemGetAddressRange;
    dt.Module.pfnCreate = Cal::Icd::LevelZero::zeModuleCreate;
    dt.Module.pfnDestroy = Cal::Icd::LevelZero::zeModuleDestroy;
    dt.ModuleBuildLog.pfnDestroy = Cal::Icd::LevelZero::zeModuleBuildLogDestroy;
    dt.ModuleBuildLog.pfnGetString = Cal::Icd::LevelZero::zeModuleBuildLogGetString;
    dt.Module.pfnGetNativeBinary = Cal::Icd::LevelZero::zeModuleGetNativeBinary;
    dt.Module.pfnGetGlobalPointer = Cal::Icd::LevelZero::zeModuleGetGlobalPointer;
    dt.Module.pfnGetKernelNames = Cal::Icd::LevelZero::zeModuleGetKernelNames;
    dt.Module.pfnGetProperties = Cal::Icd::LevelZero::zeModuleGetProperties;
    dt.Kernel.pfnCreate = Cal::Icd::LevelZero::zeKernelCreate;
    dt.Kernel.pfnDestroy = Cal::Icd::LevelZero::zeKernelDestroy;
    dt.Module.pfnGetFunctionPointer = Cal::Icd::LevelZero::zeModuleGetFunctionPointer;
    dt.Kernel.pfnSetGroupSize = Cal::Icd::LevelZero::zeKernelSetGroupSize;
    dt.Kernel.pfnSuggestGroupSize = Cal::Icd::LevelZero::zeKernelSuggestGroupSize;
    dt.Kernel.pfnSuggestMaxCooperativeGroupCount = Cal::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount;
    dt.Kernel.pfnSetArgumentValue = Cal::Icd::LevelZero::zeKernelSetArgumentValue;
    dt.Kernel.pfnSetIndirectAccess = Cal::Icd::LevelZero::zeKernelSetIndirectAccess;
    dt.Kernel.pfnGetIndirectAccess = Cal::Icd::LevelZero::zeKernelGetIndirectAccess;
    dt.Kernel.pfnSetCacheConfig = Cal::Icd::LevelZero::zeKernelSetCacheConfig;
    dt.Kernel.pfnGetProperties = Cal::Icd::LevelZero::zeKernelGetProperties;
    dt.Kernel.pfnGetName = Cal::Icd::LevelZero::zeKernelGetName;
    dt.CommandList.pfnAppendLaunchKernel = Cal::Icd::LevelZero::zeCommandListAppendLaunchKernel;
    dt.Device.pfnPciGetPropertiesExt = Cal::Icd::LevelZero::zeDevicePciGetPropertiesExt;
    // below are unimplemented, provided bindings are for easier debugging only
    dt.CommandList.pfnAppendMemoryRangesBarrier = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryRangesBarrier)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryRangesBarrierUnimpl);
    dt.Context.pfnSystemBarrier = reinterpret_cast<decltype(dt.Context.pfnSystemBarrier)>(Cal::Icd::LevelZero::Unimplemented::zeContextSystemBarrierUnimpl);
    dt.Device.pfnReserveCacheExt = reinterpret_cast<decltype(dt.Device.pfnReserveCacheExt)>(Cal::Icd::LevelZero::Unimplemented::zeDeviceReserveCacheExtUnimpl);
    dt.Device.pfnSetCacheAdviceExt = reinterpret_cast<decltype(dt.Device.pfnSetCacheAdviceExt)>(Cal::Icd::LevelZero::Unimplemented::zeDeviceSetCacheAdviceExtUnimpl);
    dt.CommandList.pfnAppendWriteGlobalTimestamp = reinterpret_cast<decltype(dt.CommandList.pfnAppendWriteGlobalTimestamp)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendWriteGlobalTimestampUnimpl);
    dt.CommandList.pfnAppendMemoryCopyRegion = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryCopyRegion)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryCopyRegionUnimpl);
    dt.CommandList.pfnAppendMemoryCopyFromContext = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryCopyFromContext)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryCopyFromContextUnimpl);
    dt.CommandList.pfnAppendImageCopy = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopy)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyUnimpl);
    dt.CommandList.pfnAppendImageCopyRegion = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyRegion)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyRegionUnimpl);
    dt.CommandList.pfnAppendImageCopyToMemory = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemory)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemory = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemory)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryUnimpl);
    dt.CommandList.pfnAppendMemoryPrefetch = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryPrefetch)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryPrefetchUnimpl);
    dt.CommandList.pfnAppendMemAdvise = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemAdvise)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendMemAdviseUnimpl);
    dt.Device.pfnGetP2PProperties = reinterpret_cast<decltype(dt.Device.pfnGetP2PProperties)>(Cal::Icd::LevelZero::Unimplemented::zeDeviceGetP2PPropertiesUnimpl);
    dt.EventPool.pfnGetIpcHandle = reinterpret_cast<decltype(dt.EventPool.pfnGetIpcHandle)>(Cal::Icd::LevelZero::Unimplemented::zeEventPoolGetIpcHandleUnimpl);
    dt.EventPool.pfnOpenIpcHandle = reinterpret_cast<decltype(dt.EventPool.pfnOpenIpcHandle)>(Cal::Icd::LevelZero::Unimplemented::zeEventPoolOpenIpcHandleUnimpl);
    dt.EventPool.pfnCloseIpcHandle = reinterpret_cast<decltype(dt.EventPool.pfnCloseIpcHandle)>(Cal::Icd::LevelZero::Unimplemented::zeEventPoolCloseIpcHandleUnimpl);
    dt.Event.pfnHostSignal = reinterpret_cast<decltype(dt.Event.pfnHostSignal)>(Cal::Icd::LevelZero::Unimplemented::zeEventHostSignalUnimpl);
    dt.CommandList.pfnAppendEventReset = reinterpret_cast<decltype(dt.CommandList.pfnAppendEventReset)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendEventResetUnimpl);
    dt.CommandList.pfnAppendQueryKernelTimestamps = reinterpret_cast<decltype(dt.CommandList.pfnAppendQueryKernelTimestamps)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendQueryKernelTimestampsUnimpl);
    dt.EventExp.pfnQueryTimestampsExp = reinterpret_cast<decltype(dt.EventExp.pfnQueryTimestampsExp)>(Cal::Icd::LevelZero::Unimplemented::zeEventQueryTimestampsExpUnimpl);
    dt.FabricVertexExp.pfnGetExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricVertexGetExpUnimpl);
    dt.FabricVertexExp.pfnGetSubVerticesExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetSubVerticesExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricVertexGetSubVerticesExpUnimpl);
    dt.FabricVertexExp.pfnGetPropertiesExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetPropertiesExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricVertexGetPropertiesExpUnimpl);
    dt.FabricVertexExp.pfnGetDeviceExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetDeviceExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricVertexGetDeviceExpUnimpl);
    dt.DeviceExp.pfnGetFabricVertexExp = reinterpret_cast<decltype(dt.DeviceExp.pfnGetFabricVertexExp)>(Cal::Icd::LevelZero::Unimplemented::zeDeviceGetFabricVertexExpUnimpl);
    dt.FabricEdgeExp.pfnGetExp = reinterpret_cast<decltype(dt.FabricEdgeExp.pfnGetExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricEdgeGetExpUnimpl);
    dt.FabricEdgeExp.pfnGetVerticesExp = reinterpret_cast<decltype(dt.FabricEdgeExp.pfnGetVerticesExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricEdgeGetVerticesExpUnimpl);
    dt.FabricEdgeExp.pfnGetPropertiesExp = reinterpret_cast<decltype(dt.FabricEdgeExp.pfnGetPropertiesExp)>(Cal::Icd::LevelZero::Unimplemented::zeFabricEdgeGetPropertiesExpUnimpl);
    dt.Image.pfnGetProperties = reinterpret_cast<decltype(dt.Image.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zeImageGetPropertiesUnimpl);
    dt.Image.pfnCreate = reinterpret_cast<decltype(dt.Image.pfnCreate)>(Cal::Icd::LevelZero::Unimplemented::zeImageCreateUnimpl);
    dt.Image.pfnDestroy = reinterpret_cast<decltype(dt.Image.pfnDestroy)>(Cal::Icd::LevelZero::Unimplemented::zeImageDestroyUnimpl);
    dt.CommandList.pfnAppendImageCopyToMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemoryExt)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryExtUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemoryExt)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryExtUnimpl);
    dt.ImageExp.pfnGetMemoryPropertiesExp = reinterpret_cast<decltype(dt.ImageExp.pfnGetMemoryPropertiesExp)>(Cal::Icd::LevelZero::Unimplemented::zeImageGetMemoryPropertiesExpUnimpl);
    dt.Image.pfnGetAllocPropertiesExt = reinterpret_cast<decltype(dt.Image.pfnGetAllocPropertiesExt)>(Cal::Icd::LevelZero::Unimplemented::zeImageGetAllocPropertiesExtUnimpl);
    dt.ImageExp.pfnViewCreateExp = reinterpret_cast<decltype(dt.ImageExp.pfnViewCreateExp)>(Cal::Icd::LevelZero::Unimplemented::zeImageViewCreateExpUnimpl);
    dt.KernelExp.pfnSchedulingHintExp = reinterpret_cast<decltype(dt.KernelExp.pfnSchedulingHintExp)>(Cal::Icd::LevelZero::Unimplemented::zeKernelSchedulingHintExpUnimpl);
    dt.Module.pfnInspectLinkageExt = reinterpret_cast<decltype(dt.Module.pfnInspectLinkageExt)>(Cal::Icd::LevelZero::Unimplemented::zeModuleInspectLinkageExtUnimpl);
    dt.Mem.pfnGetIpcHandle = reinterpret_cast<decltype(dt.Mem.pfnGetIpcHandle)>(Cal::Icd::LevelZero::Unimplemented::zeMemGetIpcHandleUnimpl);
    dt.Mem.pfnOpenIpcHandle = reinterpret_cast<decltype(dt.Mem.pfnOpenIpcHandle)>(Cal::Icd::LevelZero::Unimplemented::zeMemOpenIpcHandleUnimpl);
    dt.Mem.pfnCloseIpcHandle = reinterpret_cast<decltype(dt.Mem.pfnCloseIpcHandle)>(Cal::Icd::LevelZero::Unimplemented::zeMemCloseIpcHandleUnimpl);
    dt.Mem.pfnFreeExt = reinterpret_cast<decltype(dt.Mem.pfnFreeExt)>(Cal::Icd::LevelZero::Unimplemented::zeMemFreeExtUnimpl);
    dt.Module.pfnDynamicLink = reinterpret_cast<decltype(dt.Module.pfnDynamicLink)>(Cal::Icd::LevelZero::Unimplemented::zeModuleDynamicLinkUnimpl);
    dt.Kernel.pfnGetSourceAttributes = reinterpret_cast<decltype(dt.Kernel.pfnGetSourceAttributes)>(Cal::Icd::LevelZero::Unimplemented::zeKernelGetSourceAttributesUnimpl);
    dt.CommandList.pfnAppendLaunchCooperativeKernel = reinterpret_cast<decltype(dt.CommandList.pfnAppendLaunchCooperativeKernel)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendLaunchCooperativeKernelUnimpl);
    dt.CommandList.pfnAppendLaunchKernelIndirect = reinterpret_cast<decltype(dt.CommandList.pfnAppendLaunchKernelIndirect)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendLaunchKernelIndirectUnimpl);
    dt.CommandList.pfnAppendLaunchMultipleKernelsIndirect = reinterpret_cast<decltype(dt.CommandList.pfnAppendLaunchMultipleKernelsIndirect)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendLaunchMultipleKernelsIndirectUnimpl);
    dt.Context.pfnMakeMemoryResident = reinterpret_cast<decltype(dt.Context.pfnMakeMemoryResident)>(Cal::Icd::LevelZero::Unimplemented::zeContextMakeMemoryResidentUnimpl);
    dt.Context.pfnEvictMemory = reinterpret_cast<decltype(dt.Context.pfnEvictMemory)>(Cal::Icd::LevelZero::Unimplemented::zeContextEvictMemoryUnimpl);
    dt.Context.pfnMakeImageResident = reinterpret_cast<decltype(dt.Context.pfnMakeImageResident)>(Cal::Icd::LevelZero::Unimplemented::zeContextMakeImageResidentUnimpl);
    dt.Context.pfnEvictImage = reinterpret_cast<decltype(dt.Context.pfnEvictImage)>(Cal::Icd::LevelZero::Unimplemented::zeContextEvictImageUnimpl);
    dt.Sampler.pfnCreate = reinterpret_cast<decltype(dt.Sampler.pfnCreate)>(Cal::Icd::LevelZero::Unimplemented::zeSamplerCreateUnimpl);
    dt.Sampler.pfnDestroy = reinterpret_cast<decltype(dt.Sampler.pfnDestroy)>(Cal::Icd::LevelZero::Unimplemented::zeSamplerDestroyUnimpl);
    dt.VirtualMem.pfnReserve = reinterpret_cast<decltype(dt.VirtualMem.pfnReserve)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemReserveUnimpl);
    dt.VirtualMem.pfnFree = reinterpret_cast<decltype(dt.VirtualMem.pfnFree)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemFreeUnimpl);
    dt.VirtualMem.pfnQueryPageSize = reinterpret_cast<decltype(dt.VirtualMem.pfnQueryPageSize)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemQueryPageSizeUnimpl);
    dt.PhysicalMem.pfnCreate = reinterpret_cast<decltype(dt.PhysicalMem.pfnCreate)>(Cal::Icd::LevelZero::Unimplemented::zePhysicalMemCreateUnimpl);
    dt.PhysicalMem.pfnDestroy = reinterpret_cast<decltype(dt.PhysicalMem.pfnDestroy)>(Cal::Icd::LevelZero::Unimplemented::zePhysicalMemDestroyUnimpl);
    dt.VirtualMem.pfnMap = reinterpret_cast<decltype(dt.VirtualMem.pfnMap)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemMapUnimpl);
    dt.VirtualMem.pfnUnmap = reinterpret_cast<decltype(dt.VirtualMem.pfnUnmap)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemUnmapUnimpl);
    dt.VirtualMem.pfnSetAccessAttribute = reinterpret_cast<decltype(dt.VirtualMem.pfnSetAccessAttribute)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemSetAccessAttributeUnimpl);
    dt.VirtualMem.pfnGetAccessAttribute = reinterpret_cast<decltype(dt.VirtualMem.pfnGetAccessAttribute)>(Cal::Icd::LevelZero::Unimplemented::zeVirtualMemGetAccessAttributeUnimpl);
}

} // namespace LevelZero
} // namespace Icd
} // namespace Cal
// #### Generated code -- end ####
