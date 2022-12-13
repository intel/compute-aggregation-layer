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
#include "icd/level_zero/icd_level_zero.h"
#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"
#include "level_zero/zes_api.h"
#include "level_zero/zes_ddi.h"
#include "level_zero/zet_api.h"
#include "level_zero/zet_ddi.h"
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
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediate (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2Malloc (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2Malloc (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFill (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Malloc (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemAdviseRpcHelper (ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice);
ze_result_t zeDeviceGetRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
ze_result_t zeDeviceGetSubDevicesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
ze_result_t zeDeviceGetPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties);
ze_result_t zeDeviceGetComputePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties);
ze_result_t zeDeviceGetModulePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties);
ze_result_t zeDeviceGetCommandQueueGroupPropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
ze_result_t zeDeviceGetMemoryPropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
ze_result_t zeDeviceGetMemoryAccessPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties);
ze_result_t zeDeviceGetCachePropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
ze_result_t zeDeviceGetImagePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties);
ze_result_t zeDeviceGetExternalMemoryPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties);
ze_result_t zeDeviceGetP2PProperties (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties);
ze_result_t zeDeviceCanAccessPeer (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value);
ze_result_t zeDeviceGetStatus (ze_device_handle_t hDevice);
ze_result_t zeDeviceGetGlobalTimestamps (ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp);
ze_result_t zeDriverGetRpcHelper (uint32_t* pCount, ze_driver_handle_t* phDrivers);
ze_result_t zeDriverGetApiVersion (ze_driver_handle_t hDriver, ze_api_version_t* version);
ze_result_t zeDriverGetPropertiesRpcHelper (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties);
ze_result_t zeDriverGetIpcPropertiesRpcHelper (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties);
ze_result_t zeDriverGetExtensionPropertiesRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
ze_result_t zeDriverGetExtensionFunctionAddress (ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress);
ze_result_t zeEventPoolCreate (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool);
ze_result_t zeEventCreate (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent);
ze_result_t zeEventDestroy (ze_event_handle_t hEvent);
ze_result_t zeEventPoolGetIpcHandleRpcHelper (ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc);
ze_result_t zeEventPoolOpenIpcHandleRpcHelper (ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolCloseIpcHandle (ze_event_pool_handle_t hEventPool);
ze_result_t zeCommandListAppendBarrier (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
ze_result_t zeEventHostSignal (ze_event_handle_t hEvent);
ze_result_t zeEventHostSynchronizeRpcHelper (ze_event_handle_t hEvent, uint64_t timeout);
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendEventReset (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeEventHostReset (ze_event_handle_t hEvent);
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr);
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence);
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence);
ze_result_t zeFenceHostSynchronizeRpcHelper (ze_fence_handle_t hFence, uint64_t timeout);
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence);
ze_result_t zeFenceReset (ze_fence_handle_t hFence);
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
ze_result_t zeImageGetProperties (ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties);
ze_result_t zeImageCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage);
ze_result_t zeImageDestroy (ze_image_handle_t hImage);
ze_result_t zeMemAllocSharedRpcHelper (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::ImplicitArgs &implArgsForZeMemAllocSharedRpcM);
ze_result_t zeMemAllocDevice (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
ze_result_t zeMemAllocHostRpcHelper (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocHostRpcM::ImplicitArgs &implArgsForZeMemAllocHostRpcM);
ze_result_t zeMemFree (ze_context_handle_t hContext, void* ptr);
ze_result_t zeMemGetAllocPropertiesRpcHelper (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice);
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize);
ze_result_t zeMemGetIpcHandleRpcHelper (ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle);
ze_result_t zeMemOpenIpcHandleRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zeMemCloseIpcHandle (ze_context_handle_t hContext, const void* ptr);
ze_result_t zexMemGetIpcHandlesRpcHelper (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
ze_result_t zexMemOpenIpcHandlesRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
ze_result_t zeModuleDestroy (ze_module_handle_t hModule);
ze_result_t zeModuleDynamicLink (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog);
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog);
ze_result_t zeModuleBuildLogGetString (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
ze_result_t zeModuleGetNativeBinary (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary);
ze_result_t zeModuleGetGlobalPointer (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
ze_result_t zeModuleGetKernelNames (ze_module_handle_t hModule, uint32_t* pCount, const char** pNames);
ze_result_t zeModuleGetKernelNamesRpcHelper (ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer);
ze_result_t zeModuleGetPropertiesRpcHelper (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties);
ze_result_t zeKernelCreate (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel);
ze_result_t zeModuleGetFunctionPointer (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
ze_result_t zeKernelSetGroupSize (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ);
ze_result_t zeKernelSuggestGroupSize (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ);
ze_result_t zeKernelSuggestMaxCooperativeGroupCount (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount);
ze_result_t zeKernelSetArgumentValueRpcHelper (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags);
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags);
ze_result_t zeKernelSetCacheConfig (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags);
ze_result_t zeKernelGetPropertiesRpcHelper (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties);
ze_result_t zeKernelGetName (ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
ze_result_t zeCommandListAppendLaunchKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchKernelIndirect (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
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
inline void zeMemFreeExtUnimpl() {
    log<Verbosity::critical>("Function Mem.zeMemFreeExt is not yet implemented in Compute Aggregation Layer - aborting");
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
inline void zesDeviceEnumRasErrorSetsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumRasErrorSets is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesRasGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Ras.zesRasGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesRasGetConfigUnimpl() {
    log<Verbosity::critical>("Function Ras.zesRasGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesRasSetConfigUnimpl() {
    log<Verbosity::critical>("Function Ras.zesRasSetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesRasGetStateUnimpl() {
    log<Verbosity::critical>("Function Ras.zesRasGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceGetStateUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceResetUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceReset is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceProcessesGetStateUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceProcessesGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDevicePciGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Device.zesDevicePciGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDevicePciGetStateUnimpl() {
    log<Verbosity::critical>("Function Device.zesDevicePciGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDevicePciGetBarsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDevicePciGetBars is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDevicePciGetStatsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDevicePciGetStats is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumFansUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumFans is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFanGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Fan.zesFanGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFanGetConfigUnimpl() {
    log<Verbosity::critical>("Function Fan.zesFanGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFanSetDefaultModeUnimpl() {
    log<Verbosity::critical>("Function Fan.zesFanSetDefaultMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFanSetFixedSpeedModeUnimpl() {
    log<Verbosity::critical>("Function Fan.zesFanSetFixedSpeedMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFanSetSpeedTableModeUnimpl() {
    log<Verbosity::critical>("Function Fan.zesFanSetSpeedTableMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFanGetStateUnimpl() {
    log<Verbosity::critical>("Function Fan.zesFanGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumFirmwaresUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumFirmwares is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFirmwareGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Firmware.zesFirmwareGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFirmwareFlashUnimpl() {
    log<Verbosity::critical>("Function Firmware.zesFirmwareFlash is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerGetLimitsExtUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerGetLimitsExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerSetLimitsExtUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerSetLimitsExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumStandbyDomainsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumStandbyDomains is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesStandbyGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Standby.zesStandbyGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesStandbyGetModeUnimpl() {
    log<Verbosity::critical>("Function Standby.zesStandbyGetMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesStandbySetModeUnimpl() {
    log<Verbosity::critical>("Function Standby.zesStandbySetMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumTemperatureSensorsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumTemperatureSensors is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesTemperatureGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Temperature.zesTemperatureGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesTemperatureGetConfigUnimpl() {
    log<Verbosity::critical>("Function Temperature.zesTemperatureGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesTemperatureSetConfigUnimpl() {
    log<Verbosity::critical>("Function Temperature.zesTemperatureSetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesTemperatureGetStateUnimpl() {
    log<Verbosity::critical>("Function Temperature.zesTemperatureGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEccAvailableUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEccAvailable is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEccConfigurableUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEccConfigurable is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceGetEccStateUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceGetEccState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceSetEccStateUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceSetEccState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumEngineGroupsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumEngineGroups is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesEngineGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Engine.zesEngineGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesEngineGetActivityUnimpl() {
    log<Verbosity::critical>("Function Engine.zesEngineGetActivity is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumSchedulersUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumSchedulers is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerGetCurrentModeUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerGetCurrentMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerGetTimeoutModePropertiesUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerGetTimeoutModeProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerGetTimesliceModePropertiesUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerGetTimesliceModeProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerSetTimeoutModeUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerSetTimeoutMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerSetTimesliceModeUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerSetTimesliceMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerSetExclusiveModeUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerSetExclusiveMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesSchedulerSetComputeUnitDebugModeUnimpl() {
    log<Verbosity::critical>("Function Scheduler.zesSchedulerSetComputeUnitDebugMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumMemoryModulesUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumMemoryModules is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesMemoryGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Memory.zesMemoryGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesMemoryGetStateUnimpl() {
    log<Verbosity::critical>("Function Memory.zesMemoryGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesMemoryGetBandwidthUnimpl() {
    log<Verbosity::critical>("Function Memory.zesMemoryGetBandwidth is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumPerformanceFactorDomainsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumPerformanceFactorDomains is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPerformanceFactorGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function PerformanceFactor.zesPerformanceFactorGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPerformanceFactorGetConfigUnimpl() {
    log<Verbosity::critical>("Function PerformanceFactor.zesPerformanceFactorGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPerformanceFactorSetConfigUnimpl() {
    log<Verbosity::critical>("Function PerformanceFactor.zesPerformanceFactorSetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumLedsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumLeds is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesLedGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Led.zesLedGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesLedGetStateUnimpl() {
    log<Verbosity::critical>("Function Led.zesLedGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesLedSetStateUnimpl() {
    log<Verbosity::critical>("Function Led.zesLedSetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesLedSetColorUnimpl() {
    log<Verbosity::critical>("Function Led.zesLedSetColor is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumPowerDomainsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumPowerDomains is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceGetCardPowerDomainUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceGetCardPowerDomain is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerGetEnergyCounterUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerGetEnergyCounter is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerGetLimitsUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerGetLimits is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerSetLimitsUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerSetLimits is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerGetEnergyThresholdUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerGetEnergyThreshold is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPowerSetEnergyThresholdUnimpl() {
    log<Verbosity::critical>("Function Power.zesPowerSetEnergyThreshold is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumFabricPortsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumFabricPorts is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFabricPortGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function FabricPort.zesFabricPortGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFabricPortGetLinkTypeUnimpl() {
    log<Verbosity::critical>("Function FabricPort.zesFabricPortGetLinkType is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFabricPortGetConfigUnimpl() {
    log<Verbosity::critical>("Function FabricPort.zesFabricPortGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFabricPortSetConfigUnimpl() {
    log<Verbosity::critical>("Function FabricPort.zesFabricPortSetConfig is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFabricPortGetStateUnimpl() {
    log<Verbosity::critical>("Function FabricPort.zesFabricPortGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFabricPortGetThroughputUnimpl() {
    log<Verbosity::critical>("Function FabricPort.zesFabricPortGetThroughput is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEventRegisterUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEventRegister is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDriverEventListenUnimpl() {
    log<Verbosity::critical>("Function Driver.zesDriverEventListen is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDriverEventListenExUnimpl() {
    log<Verbosity::critical>("Function Driver.zesDriverEventListenEx is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumDiagnosticTestSuitesUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumDiagnosticTestSuites is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDiagnosticsGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Diagnostics.zesDiagnosticsGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDiagnosticsGetTestsUnimpl() {
    log<Verbosity::critical>("Function Diagnostics.zesDiagnosticsGetTests is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDiagnosticsRunTestsUnimpl() {
    log<Verbosity::critical>("Function Diagnostics.zesDiagnosticsRunTests is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumPsusUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumPsus is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPsuGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Psu.zesPsuGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesPsuGetStateUnimpl() {
    log<Verbosity::critical>("Function Psu.zesPsuGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesDeviceEnumFrequencyDomainsUnimpl() {
    log<Verbosity::critical>("Function Device.zesDeviceEnumFrequencyDomains is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyGetAvailableClocksUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyGetAvailableClocks is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyGetRangeUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyGetRange is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencySetRangeUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencySetRange is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyGetStateUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyGetState is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyGetThrottleTimeUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyGetThrottleTime is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcGetCapabilitiesUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcGetCapabilities is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcGetVoltageTargetUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcGetVoltageTarget is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcSetVoltageTargetUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcSetVoltageTarget is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcSetModeUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcSetMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcGetModeUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcGetMode is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcGetIccMaxUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcGetIccMax is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcSetIccMaxUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcSetIccMax is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcGetTjMaxUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcGetTjMax is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zesFrequencyOcSetTjMaxUnimpl() {
    log<Verbosity::critical>("Function Frequency.zesFrequencyOcSetTjMax is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetKernelGetProfileInfoUnimpl() {
    log<Verbosity::critical>("Function Kernel.zetKernelGetProfileInfo is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricGroupCalculateMultipleMetricValuesExpUnimpl() {
    log<Verbosity::critical>("Function MetricGroupExp.zetMetricGroupCalculateMultipleMetricValuesExp is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDeviceGetDebugPropertiesUnimpl() {
    log<Verbosity::critical>("Function Device.zetDeviceGetDebugProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugAttachUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugAttach is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugDetachUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugDetach is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugReadEventUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugReadEvent is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugAcknowledgeEventUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugAcknowledgeEvent is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugInterruptUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugInterrupt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugResumeUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugResume is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugReadMemoryUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugReadMemory is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugWriteMemoryUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugWriteMemory is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugGetRegisterSetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugGetRegisterSetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugReadRegistersUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugReadRegisters is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetDebugWriteRegistersUnimpl() {
    log<Verbosity::critical>("Function Debug.zetDebugWriteRegisters is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetModuleGetDebugInfoUnimpl() {
    log<Verbosity::critical>("Function Module.zetModuleGetDebugInfo is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricGroupGetUnimpl() {
    log<Verbosity::critical>("Function MetricGroup.zetMetricGroupGet is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricGroupGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function MetricGroup.zetMetricGroupGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricGroupCalculateMetricValuesUnimpl() {
    log<Verbosity::critical>("Function MetricGroup.zetMetricGroupCalculateMetricValues is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricGetUnimpl() {
    log<Verbosity::critical>("Function Metric.zetMetricGet is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricGetPropertiesUnimpl() {
    log<Verbosity::critical>("Function Metric.zetMetricGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetContextActivateMetricGroupsUnimpl() {
    log<Verbosity::critical>("Function Context.zetContextActivateMetricGroups is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricStreamerOpenUnimpl() {
    log<Verbosity::critical>("Function MetricStreamer.zetMetricStreamerOpen is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetCommandListAppendMetricStreamerMarkerUnimpl() {
    log<Verbosity::critical>("Function CommandList.zetCommandListAppendMetricStreamerMarker is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricStreamerCloseUnimpl() {
    log<Verbosity::critical>("Function MetricStreamer.zetMetricStreamerClose is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricStreamerReadDataUnimpl() {
    log<Verbosity::critical>("Function MetricStreamer.zetMetricStreamerReadData is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricQueryPoolCreateUnimpl() {
    log<Verbosity::critical>("Function MetricQueryPool.zetMetricQueryPoolCreate is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricQueryPoolDestroyUnimpl() {
    log<Verbosity::critical>("Function MetricQueryPool.zetMetricQueryPoolDestroy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricQueryCreateUnimpl() {
    log<Verbosity::critical>("Function MetricQuery.zetMetricQueryCreate is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricQueryDestroyUnimpl() {
    log<Verbosity::critical>("Function MetricQuery.zetMetricQueryDestroy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricQueryResetUnimpl() {
    log<Verbosity::critical>("Function MetricQuery.zetMetricQueryReset is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetCommandListAppendMetricQueryBeginUnimpl() {
    log<Verbosity::critical>("Function CommandList.zetCommandListAppendMetricQueryBegin is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetCommandListAppendMetricQueryEndUnimpl() {
    log<Verbosity::critical>("Function CommandList.zetCommandListAppendMetricQueryEnd is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetCommandListAppendMetricMemoryBarrierUnimpl() {
    log<Verbosity::critical>("Function CommandList.zetCommandListAppendMetricMemoryBarrier is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetMetricQueryGetDataUnimpl() {
    log<Verbosity::critical>("Function MetricQuery.zetMetricQueryGetData is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetTracerExpCreateUnimpl() {
    log<Verbosity::critical>("Function TracerExp.zetTracerExpCreate is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetTracerExpDestroyUnimpl() {
    log<Verbosity::critical>("Function TracerExp.zetTracerExpDestroy is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetTracerExpSetProloguesUnimpl() {
    log<Verbosity::critical>("Function TracerExp.zetTracerExpSetPrologues is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetTracerExpSetEpiloguesUnimpl() {
    log<Verbosity::critical>("Function TracerExp.zetTracerExpSetEpilogues is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zetTracerExpSetEnabledUnimpl() {
    log<Verbosity::critical>("Function TracerExp.zetTracerExpSetEnabled is not yet implemented in Compute Aggregation Layer - aborting");
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
    dt.CommandList.pfnAppendMemAdvise = Cal::Icd::LevelZero::zeCommandListAppendMemAdvise;
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
    dt.Device.pfnGetP2PProperties = Cal::Icd::LevelZero::zeDeviceGetP2PProperties;
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
    dt.EventPool.pfnGetIpcHandle = Cal::Icd::LevelZero::zeEventPoolGetIpcHandle;
    dt.EventPool.pfnOpenIpcHandle = Cal::Icd::LevelZero::zeEventPoolOpenIpcHandle;
    dt.EventPool.pfnCloseIpcHandle = Cal::Icd::LevelZero::zeEventPoolCloseIpcHandle;
    dt.CommandList.pfnAppendBarrier = Cal::Icd::LevelZero::zeCommandListAppendBarrier;
    dt.CommandList.pfnAppendSignalEvent = Cal::Icd::LevelZero::zeCommandListAppendSignalEvent;
    dt.CommandList.pfnAppendWaitOnEvents = Cal::Icd::LevelZero::zeCommandListAppendWaitOnEvents;
    dt.Event.pfnHostSignal = Cal::Icd::LevelZero::zeEventHostSignal;
    dt.Event.pfnHostSynchronize = Cal::Icd::LevelZero::zeEventHostSynchronize;
    dt.Event.pfnQueryStatus = Cal::Icd::LevelZero::zeEventQueryStatus;
    dt.CommandList.pfnAppendEventReset = Cal::Icd::LevelZero::zeCommandListAppendEventReset;
    dt.Event.pfnHostReset = Cal::Icd::LevelZero::zeEventHostReset;
    dt.Event.pfnQueryKernelTimestamp = Cal::Icd::LevelZero::zeEventQueryKernelTimestamp;
    dt.Fence.pfnCreate = Cal::Icd::LevelZero::zeFenceCreate;
    dt.Fence.pfnDestroy = Cal::Icd::LevelZero::zeFenceDestroy;
    dt.Fence.pfnHostSynchronize = Cal::Icd::LevelZero::zeFenceHostSynchronize;
    dt.Fence.pfnQueryStatus = Cal::Icd::LevelZero::zeFenceQueryStatus;
    dt.Fence.pfnReset = Cal::Icd::LevelZero::zeFenceReset;
    dt.KernelExp.pfnSetGlobalOffsetExp = Cal::Icd::LevelZero::zeKernelSetGlobalOffsetExp;
    dt.Image.pfnGetProperties = Cal::Icd::LevelZero::zeImageGetProperties;
    dt.Image.pfnCreate = Cal::Icd::LevelZero::zeImageCreate;
    dt.Image.pfnDestroy = Cal::Icd::LevelZero::zeImageDestroy;
    dt.Mem.pfnAllocShared = Cal::Icd::LevelZero::zeMemAllocShared;
    dt.Mem.pfnAllocDevice = Cal::Icd::LevelZero::zeMemAllocDevice;
    dt.Mem.pfnAllocHost = Cal::Icd::LevelZero::zeMemAllocHost;
    dt.Mem.pfnFree = Cal::Icd::LevelZero::zeMemFree;
    dt.Mem.pfnGetAllocProperties = Cal::Icd::LevelZero::zeMemGetAllocProperties;
    dt.Mem.pfnGetAddressRange = Cal::Icd::LevelZero::zeMemGetAddressRange;
    dt.Mem.pfnGetIpcHandle = Cal::Icd::LevelZero::zeMemGetIpcHandle;
    dt.Mem.pfnOpenIpcHandle = Cal::Icd::LevelZero::zeMemOpenIpcHandle;
    dt.Mem.pfnCloseIpcHandle = Cal::Icd::LevelZero::zeMemCloseIpcHandle;
    dt.Module.pfnCreate = Cal::Icd::LevelZero::zeModuleCreate;
    dt.Module.pfnDestroy = Cal::Icd::LevelZero::zeModuleDestroy;
    dt.Module.pfnDynamicLink = Cal::Icd::LevelZero::zeModuleDynamicLink;
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
    dt.CommandList.pfnAppendLaunchKernelIndirect = Cal::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect;
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
    dt.CommandList.pfnAppendImageCopyToMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemoryExt)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryExtUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemoryExt)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryExtUnimpl);
    dt.ImageExp.pfnGetMemoryPropertiesExp = reinterpret_cast<decltype(dt.ImageExp.pfnGetMemoryPropertiesExp)>(Cal::Icd::LevelZero::Unimplemented::zeImageGetMemoryPropertiesExpUnimpl);
    dt.Image.pfnGetAllocPropertiesExt = reinterpret_cast<decltype(dt.Image.pfnGetAllocPropertiesExt)>(Cal::Icd::LevelZero::Unimplemented::zeImageGetAllocPropertiesExtUnimpl);
    dt.ImageExp.pfnViewCreateExp = reinterpret_cast<decltype(dt.ImageExp.pfnViewCreateExp)>(Cal::Icd::LevelZero::Unimplemented::zeImageViewCreateExpUnimpl);
    dt.KernelExp.pfnSchedulingHintExp = reinterpret_cast<decltype(dt.KernelExp.pfnSchedulingHintExp)>(Cal::Icd::LevelZero::Unimplemented::zeKernelSchedulingHintExpUnimpl);
    dt.Module.pfnInspectLinkageExt = reinterpret_cast<decltype(dt.Module.pfnInspectLinkageExt)>(Cal::Icd::LevelZero::Unimplemented::zeModuleInspectLinkageExtUnimpl);
    dt.Mem.pfnFreeExt = reinterpret_cast<decltype(dt.Mem.pfnFreeExt)>(Cal::Icd::LevelZero::Unimplemented::zeMemFreeExtUnimpl);
    dt.Kernel.pfnGetSourceAttributes = reinterpret_cast<decltype(dt.Kernel.pfnGetSourceAttributes)>(Cal::Icd::LevelZero::Unimplemented::zeKernelGetSourceAttributesUnimpl);
    dt.CommandList.pfnAppendLaunchCooperativeKernel = reinterpret_cast<decltype(dt.CommandList.pfnAppendLaunchCooperativeKernel)>(Cal::Icd::LevelZero::Unimplemented::zeCommandListAppendLaunchCooperativeKernelUnimpl);
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

inline void initL0SysmanDdi(zes_dditable_t &dt){
    dt.Device.pfnEnumRasErrorSets = reinterpret_cast<decltype(dt.Device.pfnEnumRasErrorSets)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumRasErrorSetsUnimpl);
    dt.Ras.pfnGetProperties = reinterpret_cast<decltype(dt.Ras.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesRasGetPropertiesUnimpl);
    dt.Ras.pfnGetConfig = reinterpret_cast<decltype(dt.Ras.pfnGetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesRasGetConfigUnimpl);
    dt.Ras.pfnSetConfig = reinterpret_cast<decltype(dt.Ras.pfnSetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesRasSetConfigUnimpl);
    dt.Ras.pfnGetState = reinterpret_cast<decltype(dt.Ras.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesRasGetStateUnimpl);
    dt.Device.pfnGetProperties = reinterpret_cast<decltype(dt.Device.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceGetPropertiesUnimpl);
    dt.Device.pfnGetState = reinterpret_cast<decltype(dt.Device.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceGetStateUnimpl);
    dt.Device.pfnReset = reinterpret_cast<decltype(dt.Device.pfnReset)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceResetUnimpl);
    dt.Device.pfnProcessesGetState = reinterpret_cast<decltype(dt.Device.pfnProcessesGetState)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceProcessesGetStateUnimpl);
    dt.Device.pfnPciGetProperties = reinterpret_cast<decltype(dt.Device.pfnPciGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesDevicePciGetPropertiesUnimpl);
    dt.Device.pfnPciGetState = reinterpret_cast<decltype(dt.Device.pfnPciGetState)>(Cal::Icd::LevelZero::Unimplemented::zesDevicePciGetStateUnimpl);
    dt.Device.pfnPciGetBars = reinterpret_cast<decltype(dt.Device.pfnPciGetBars)>(Cal::Icd::LevelZero::Unimplemented::zesDevicePciGetBarsUnimpl);
    dt.Device.pfnPciGetStats = reinterpret_cast<decltype(dt.Device.pfnPciGetStats)>(Cal::Icd::LevelZero::Unimplemented::zesDevicePciGetStatsUnimpl);
    dt.Device.pfnEnumFans = reinterpret_cast<decltype(dt.Device.pfnEnumFans)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumFansUnimpl);
    dt.Fan.pfnGetProperties = reinterpret_cast<decltype(dt.Fan.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesFanGetPropertiesUnimpl);
    dt.Fan.pfnGetConfig = reinterpret_cast<decltype(dt.Fan.pfnGetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesFanGetConfigUnimpl);
    dt.Fan.pfnSetDefaultMode = reinterpret_cast<decltype(dt.Fan.pfnSetDefaultMode)>(Cal::Icd::LevelZero::Unimplemented::zesFanSetDefaultModeUnimpl);
    dt.Fan.pfnSetFixedSpeedMode = reinterpret_cast<decltype(dt.Fan.pfnSetFixedSpeedMode)>(Cal::Icd::LevelZero::Unimplemented::zesFanSetFixedSpeedModeUnimpl);
    dt.Fan.pfnSetSpeedTableMode = reinterpret_cast<decltype(dt.Fan.pfnSetSpeedTableMode)>(Cal::Icd::LevelZero::Unimplemented::zesFanSetSpeedTableModeUnimpl);
    dt.Fan.pfnGetState = reinterpret_cast<decltype(dt.Fan.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesFanGetStateUnimpl);
    dt.Device.pfnEnumFirmwares = reinterpret_cast<decltype(dt.Device.pfnEnumFirmwares)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumFirmwaresUnimpl);
    dt.Firmware.pfnGetProperties = reinterpret_cast<decltype(dt.Firmware.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesFirmwareGetPropertiesUnimpl);
    dt.Firmware.pfnFlash = reinterpret_cast<decltype(dt.Firmware.pfnFlash)>(Cal::Icd::LevelZero::Unimplemented::zesFirmwareFlashUnimpl);
    dt.Power.pfnGetLimitsExt = reinterpret_cast<decltype(dt.Power.pfnGetLimitsExt)>(Cal::Icd::LevelZero::Unimplemented::zesPowerGetLimitsExtUnimpl);
    dt.Power.pfnSetLimitsExt = reinterpret_cast<decltype(dt.Power.pfnSetLimitsExt)>(Cal::Icd::LevelZero::Unimplemented::zesPowerSetLimitsExtUnimpl);
    dt.Device.pfnEnumStandbyDomains = reinterpret_cast<decltype(dt.Device.pfnEnumStandbyDomains)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumStandbyDomainsUnimpl);
    dt.Standby.pfnGetProperties = reinterpret_cast<decltype(dt.Standby.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesStandbyGetPropertiesUnimpl);
    dt.Standby.pfnGetMode = reinterpret_cast<decltype(dt.Standby.pfnGetMode)>(Cal::Icd::LevelZero::Unimplemented::zesStandbyGetModeUnimpl);
    dt.Standby.pfnSetMode = reinterpret_cast<decltype(dt.Standby.pfnSetMode)>(Cal::Icd::LevelZero::Unimplemented::zesStandbySetModeUnimpl);
    dt.Device.pfnEnumTemperatureSensors = reinterpret_cast<decltype(dt.Device.pfnEnumTemperatureSensors)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumTemperatureSensorsUnimpl);
    dt.Temperature.pfnGetProperties = reinterpret_cast<decltype(dt.Temperature.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesTemperatureGetPropertiesUnimpl);
    dt.Temperature.pfnGetConfig = reinterpret_cast<decltype(dt.Temperature.pfnGetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesTemperatureGetConfigUnimpl);
    dt.Temperature.pfnSetConfig = reinterpret_cast<decltype(dt.Temperature.pfnSetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesTemperatureSetConfigUnimpl);
    dt.Temperature.pfnGetState = reinterpret_cast<decltype(dt.Temperature.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesTemperatureGetStateUnimpl);
    dt.Device.pfnEccAvailable = reinterpret_cast<decltype(dt.Device.pfnEccAvailable)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEccAvailableUnimpl);
    dt.Device.pfnEccConfigurable = reinterpret_cast<decltype(dt.Device.pfnEccConfigurable)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEccConfigurableUnimpl);
    dt.Device.pfnGetEccState = reinterpret_cast<decltype(dt.Device.pfnGetEccState)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceGetEccStateUnimpl);
    dt.Device.pfnSetEccState = reinterpret_cast<decltype(dt.Device.pfnSetEccState)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceSetEccStateUnimpl);
    dt.Device.pfnEnumEngineGroups = reinterpret_cast<decltype(dt.Device.pfnEnumEngineGroups)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumEngineGroupsUnimpl);
    dt.Engine.pfnGetProperties = reinterpret_cast<decltype(dt.Engine.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesEngineGetPropertiesUnimpl);
    dt.Engine.pfnGetActivity = reinterpret_cast<decltype(dt.Engine.pfnGetActivity)>(Cal::Icd::LevelZero::Unimplemented::zesEngineGetActivityUnimpl);
    dt.Device.pfnEnumSchedulers = reinterpret_cast<decltype(dt.Device.pfnEnumSchedulers)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumSchedulersUnimpl);
    dt.Scheduler.pfnGetProperties = reinterpret_cast<decltype(dt.Scheduler.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerGetPropertiesUnimpl);
    dt.Scheduler.pfnGetCurrentMode = reinterpret_cast<decltype(dt.Scheduler.pfnGetCurrentMode)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerGetCurrentModeUnimpl);
    dt.Scheduler.pfnGetTimeoutModeProperties = reinterpret_cast<decltype(dt.Scheduler.pfnGetTimeoutModeProperties)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerGetTimeoutModePropertiesUnimpl);
    dt.Scheduler.pfnGetTimesliceModeProperties = reinterpret_cast<decltype(dt.Scheduler.pfnGetTimesliceModeProperties)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerGetTimesliceModePropertiesUnimpl);
    dt.Scheduler.pfnSetTimeoutMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetTimeoutMode)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerSetTimeoutModeUnimpl);
    dt.Scheduler.pfnSetTimesliceMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetTimesliceMode)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerSetTimesliceModeUnimpl);
    dt.Scheduler.pfnSetExclusiveMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetExclusiveMode)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerSetExclusiveModeUnimpl);
    dt.Scheduler.pfnSetComputeUnitDebugMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetComputeUnitDebugMode)>(Cal::Icd::LevelZero::Unimplemented::zesSchedulerSetComputeUnitDebugModeUnimpl);
    dt.Device.pfnEnumMemoryModules = reinterpret_cast<decltype(dt.Device.pfnEnumMemoryModules)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumMemoryModulesUnimpl);
    dt.Memory.pfnGetProperties = reinterpret_cast<decltype(dt.Memory.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesMemoryGetPropertiesUnimpl);
    dt.Memory.pfnGetState = reinterpret_cast<decltype(dt.Memory.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesMemoryGetStateUnimpl);
    dt.Memory.pfnGetBandwidth = reinterpret_cast<decltype(dt.Memory.pfnGetBandwidth)>(Cal::Icd::LevelZero::Unimplemented::zesMemoryGetBandwidthUnimpl);
    dt.Device.pfnEnumPerformanceFactorDomains = reinterpret_cast<decltype(dt.Device.pfnEnumPerformanceFactorDomains)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumPerformanceFactorDomainsUnimpl);
    dt.PerformanceFactor.pfnGetProperties = reinterpret_cast<decltype(dt.PerformanceFactor.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesPerformanceFactorGetPropertiesUnimpl);
    dt.PerformanceFactor.pfnGetConfig = reinterpret_cast<decltype(dt.PerformanceFactor.pfnGetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesPerformanceFactorGetConfigUnimpl);
    dt.PerformanceFactor.pfnSetConfig = reinterpret_cast<decltype(dt.PerformanceFactor.pfnSetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesPerformanceFactorSetConfigUnimpl);
    dt.Device.pfnEnumLeds = reinterpret_cast<decltype(dt.Device.pfnEnumLeds)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumLedsUnimpl);
    dt.Led.pfnGetProperties = reinterpret_cast<decltype(dt.Led.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesLedGetPropertiesUnimpl);
    dt.Led.pfnGetState = reinterpret_cast<decltype(dt.Led.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesLedGetStateUnimpl);
    dt.Led.pfnSetState = reinterpret_cast<decltype(dt.Led.pfnSetState)>(Cal::Icd::LevelZero::Unimplemented::zesLedSetStateUnimpl);
    dt.Led.pfnSetColor = reinterpret_cast<decltype(dt.Led.pfnSetColor)>(Cal::Icd::LevelZero::Unimplemented::zesLedSetColorUnimpl);
    dt.Device.pfnEnumPowerDomains = reinterpret_cast<decltype(dt.Device.pfnEnumPowerDomains)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumPowerDomainsUnimpl);
    dt.Device.pfnGetCardPowerDomain = reinterpret_cast<decltype(dt.Device.pfnGetCardPowerDomain)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceGetCardPowerDomainUnimpl);
    dt.Power.pfnGetProperties = reinterpret_cast<decltype(dt.Power.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesPowerGetPropertiesUnimpl);
    dt.Power.pfnGetEnergyCounter = reinterpret_cast<decltype(dt.Power.pfnGetEnergyCounter)>(Cal::Icd::LevelZero::Unimplemented::zesPowerGetEnergyCounterUnimpl);
    dt.Power.pfnGetLimits = reinterpret_cast<decltype(dt.Power.pfnGetLimits)>(Cal::Icd::LevelZero::Unimplemented::zesPowerGetLimitsUnimpl);
    dt.Power.pfnSetLimits = reinterpret_cast<decltype(dt.Power.pfnSetLimits)>(Cal::Icd::LevelZero::Unimplemented::zesPowerSetLimitsUnimpl);
    dt.Power.pfnGetEnergyThreshold = reinterpret_cast<decltype(dt.Power.pfnGetEnergyThreshold)>(Cal::Icd::LevelZero::Unimplemented::zesPowerGetEnergyThresholdUnimpl);
    dt.Power.pfnSetEnergyThreshold = reinterpret_cast<decltype(dt.Power.pfnSetEnergyThreshold)>(Cal::Icd::LevelZero::Unimplemented::zesPowerSetEnergyThresholdUnimpl);
    dt.Device.pfnEnumFabricPorts = reinterpret_cast<decltype(dt.Device.pfnEnumFabricPorts)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumFabricPortsUnimpl);
    dt.FabricPort.pfnGetProperties = reinterpret_cast<decltype(dt.FabricPort.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesFabricPortGetPropertiesUnimpl);
    dt.FabricPort.pfnGetLinkType = reinterpret_cast<decltype(dt.FabricPort.pfnGetLinkType)>(Cal::Icd::LevelZero::Unimplemented::zesFabricPortGetLinkTypeUnimpl);
    dt.FabricPort.pfnGetConfig = reinterpret_cast<decltype(dt.FabricPort.pfnGetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesFabricPortGetConfigUnimpl);
    dt.FabricPort.pfnSetConfig = reinterpret_cast<decltype(dt.FabricPort.pfnSetConfig)>(Cal::Icd::LevelZero::Unimplemented::zesFabricPortSetConfigUnimpl);
    dt.FabricPort.pfnGetState = reinterpret_cast<decltype(dt.FabricPort.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesFabricPortGetStateUnimpl);
    dt.FabricPort.pfnGetThroughput = reinterpret_cast<decltype(dt.FabricPort.pfnGetThroughput)>(Cal::Icd::LevelZero::Unimplemented::zesFabricPortGetThroughputUnimpl);
    dt.Device.pfnEventRegister = reinterpret_cast<decltype(dt.Device.pfnEventRegister)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEventRegisterUnimpl);
    dt.Driver.pfnEventListen = reinterpret_cast<decltype(dt.Driver.pfnEventListen)>(Cal::Icd::LevelZero::Unimplemented::zesDriverEventListenUnimpl);
    dt.Driver.pfnEventListenEx = reinterpret_cast<decltype(dt.Driver.pfnEventListenEx)>(Cal::Icd::LevelZero::Unimplemented::zesDriverEventListenExUnimpl);
    dt.Device.pfnEnumDiagnosticTestSuites = reinterpret_cast<decltype(dt.Device.pfnEnumDiagnosticTestSuites)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumDiagnosticTestSuitesUnimpl);
    dt.Diagnostics.pfnGetProperties = reinterpret_cast<decltype(dt.Diagnostics.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesDiagnosticsGetPropertiesUnimpl);
    dt.Diagnostics.pfnGetTests = reinterpret_cast<decltype(dt.Diagnostics.pfnGetTests)>(Cal::Icd::LevelZero::Unimplemented::zesDiagnosticsGetTestsUnimpl);
    dt.Diagnostics.pfnRunTests = reinterpret_cast<decltype(dt.Diagnostics.pfnRunTests)>(Cal::Icd::LevelZero::Unimplemented::zesDiagnosticsRunTestsUnimpl);
    dt.Device.pfnEnumPsus = reinterpret_cast<decltype(dt.Device.pfnEnumPsus)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumPsusUnimpl);
    dt.Psu.pfnGetProperties = reinterpret_cast<decltype(dt.Psu.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesPsuGetPropertiesUnimpl);
    dt.Psu.pfnGetState = reinterpret_cast<decltype(dt.Psu.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesPsuGetStateUnimpl);
    dt.Device.pfnEnumFrequencyDomains = reinterpret_cast<decltype(dt.Device.pfnEnumFrequencyDomains)>(Cal::Icd::LevelZero::Unimplemented::zesDeviceEnumFrequencyDomainsUnimpl);
    dt.Frequency.pfnGetProperties = reinterpret_cast<decltype(dt.Frequency.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyGetPropertiesUnimpl);
    dt.Frequency.pfnGetAvailableClocks = reinterpret_cast<decltype(dt.Frequency.pfnGetAvailableClocks)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyGetAvailableClocksUnimpl);
    dt.Frequency.pfnGetRange = reinterpret_cast<decltype(dt.Frequency.pfnGetRange)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyGetRangeUnimpl);
    dt.Frequency.pfnSetRange = reinterpret_cast<decltype(dt.Frequency.pfnSetRange)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencySetRangeUnimpl);
    dt.Frequency.pfnGetState = reinterpret_cast<decltype(dt.Frequency.pfnGetState)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyGetStateUnimpl);
    dt.Frequency.pfnGetThrottleTime = reinterpret_cast<decltype(dt.Frequency.pfnGetThrottleTime)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyGetThrottleTimeUnimpl);
    dt.Frequency.pfnOcGetCapabilities = reinterpret_cast<decltype(dt.Frequency.pfnOcGetCapabilities)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcGetCapabilitiesUnimpl);
    dt.Frequency.pfnOcGetVoltageTarget = reinterpret_cast<decltype(dt.Frequency.pfnOcGetVoltageTarget)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcGetVoltageTargetUnimpl);
    dt.Frequency.pfnOcSetVoltageTarget = reinterpret_cast<decltype(dt.Frequency.pfnOcSetVoltageTarget)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcSetVoltageTargetUnimpl);
    dt.Frequency.pfnOcSetMode = reinterpret_cast<decltype(dt.Frequency.pfnOcSetMode)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcSetModeUnimpl);
    dt.Frequency.pfnOcGetMode = reinterpret_cast<decltype(dt.Frequency.pfnOcGetMode)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcGetModeUnimpl);
    dt.Frequency.pfnOcGetIccMax = reinterpret_cast<decltype(dt.Frequency.pfnOcGetIccMax)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcGetIccMaxUnimpl);
    dt.Frequency.pfnOcSetIccMax = reinterpret_cast<decltype(dt.Frequency.pfnOcSetIccMax)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcSetIccMaxUnimpl);
    dt.Frequency.pfnOcGetTjMax = reinterpret_cast<decltype(dt.Frequency.pfnOcGetTjMax)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcGetTjMaxUnimpl);
    dt.Frequency.pfnOcSetTjMax = reinterpret_cast<decltype(dt.Frequency.pfnOcSetTjMax)>(Cal::Icd::LevelZero::Unimplemented::zesFrequencyOcSetTjMaxUnimpl);
}
inline void initL0ToolsDdi(zet_dditable_t &dt){
    dt.Kernel.pfnGetProfileInfo = reinterpret_cast<decltype(dt.Kernel.pfnGetProfileInfo)>(Cal::Icd::LevelZero::Unimplemented::zetKernelGetProfileInfoUnimpl);
    dt.MetricGroupExp.pfnCalculateMultipleMetricValuesExp = reinterpret_cast<decltype(dt.MetricGroupExp.pfnCalculateMultipleMetricValuesExp)>(Cal::Icd::LevelZero::Unimplemented::zetMetricGroupCalculateMultipleMetricValuesExpUnimpl);
    dt.Device.pfnGetDebugProperties = reinterpret_cast<decltype(dt.Device.pfnGetDebugProperties)>(Cal::Icd::LevelZero::Unimplemented::zetDeviceGetDebugPropertiesUnimpl);
    dt.Debug.pfnAttach = reinterpret_cast<decltype(dt.Debug.pfnAttach)>(Cal::Icd::LevelZero::Unimplemented::zetDebugAttachUnimpl);
    dt.Debug.pfnDetach = reinterpret_cast<decltype(dt.Debug.pfnDetach)>(Cal::Icd::LevelZero::Unimplemented::zetDebugDetachUnimpl);
    dt.Debug.pfnReadEvent = reinterpret_cast<decltype(dt.Debug.pfnReadEvent)>(Cal::Icd::LevelZero::Unimplemented::zetDebugReadEventUnimpl);
    dt.Debug.pfnAcknowledgeEvent = reinterpret_cast<decltype(dt.Debug.pfnAcknowledgeEvent)>(Cal::Icd::LevelZero::Unimplemented::zetDebugAcknowledgeEventUnimpl);
    dt.Debug.pfnInterrupt = reinterpret_cast<decltype(dt.Debug.pfnInterrupt)>(Cal::Icd::LevelZero::Unimplemented::zetDebugInterruptUnimpl);
    dt.Debug.pfnResume = reinterpret_cast<decltype(dt.Debug.pfnResume)>(Cal::Icd::LevelZero::Unimplemented::zetDebugResumeUnimpl);
    dt.Debug.pfnReadMemory = reinterpret_cast<decltype(dt.Debug.pfnReadMemory)>(Cal::Icd::LevelZero::Unimplemented::zetDebugReadMemoryUnimpl);
    dt.Debug.pfnWriteMemory = reinterpret_cast<decltype(dt.Debug.pfnWriteMemory)>(Cal::Icd::LevelZero::Unimplemented::zetDebugWriteMemoryUnimpl);
    dt.Debug.pfnGetRegisterSetProperties = reinterpret_cast<decltype(dt.Debug.pfnGetRegisterSetProperties)>(Cal::Icd::LevelZero::Unimplemented::zetDebugGetRegisterSetPropertiesUnimpl);
    dt.Debug.pfnReadRegisters = reinterpret_cast<decltype(dt.Debug.pfnReadRegisters)>(Cal::Icd::LevelZero::Unimplemented::zetDebugReadRegistersUnimpl);
    dt.Debug.pfnWriteRegisters = reinterpret_cast<decltype(dt.Debug.pfnWriteRegisters)>(Cal::Icd::LevelZero::Unimplemented::zetDebugWriteRegistersUnimpl);
    dt.Module.pfnGetDebugInfo = reinterpret_cast<decltype(dt.Module.pfnGetDebugInfo)>(Cal::Icd::LevelZero::Unimplemented::zetModuleGetDebugInfoUnimpl);
    dt.MetricGroup.pfnGet = reinterpret_cast<decltype(dt.MetricGroup.pfnGet)>(Cal::Icd::LevelZero::Unimplemented::zetMetricGroupGetUnimpl);
    dt.MetricGroup.pfnGetProperties = reinterpret_cast<decltype(dt.MetricGroup.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zetMetricGroupGetPropertiesUnimpl);
    dt.MetricGroup.pfnCalculateMetricValues = reinterpret_cast<decltype(dt.MetricGroup.pfnCalculateMetricValues)>(Cal::Icd::LevelZero::Unimplemented::zetMetricGroupCalculateMetricValuesUnimpl);
    dt.Metric.pfnGet = reinterpret_cast<decltype(dt.Metric.pfnGet)>(Cal::Icd::LevelZero::Unimplemented::zetMetricGetUnimpl);
    dt.Metric.pfnGetProperties = reinterpret_cast<decltype(dt.Metric.pfnGetProperties)>(Cal::Icd::LevelZero::Unimplemented::zetMetricGetPropertiesUnimpl);
    dt.Context.pfnActivateMetricGroups = reinterpret_cast<decltype(dt.Context.pfnActivateMetricGroups)>(Cal::Icd::LevelZero::Unimplemented::zetContextActivateMetricGroupsUnimpl);
    dt.MetricStreamer.pfnOpen = reinterpret_cast<decltype(dt.MetricStreamer.pfnOpen)>(Cal::Icd::LevelZero::Unimplemented::zetMetricStreamerOpenUnimpl);
    dt.CommandList.pfnAppendMetricStreamerMarker = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricStreamerMarker)>(Cal::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricStreamerMarkerUnimpl);
    dt.MetricStreamer.pfnClose = reinterpret_cast<decltype(dt.MetricStreamer.pfnClose)>(Cal::Icd::LevelZero::Unimplemented::zetMetricStreamerCloseUnimpl);
    dt.MetricStreamer.pfnReadData = reinterpret_cast<decltype(dt.MetricStreamer.pfnReadData)>(Cal::Icd::LevelZero::Unimplemented::zetMetricStreamerReadDataUnimpl);
    dt.MetricQueryPool.pfnCreate = reinterpret_cast<decltype(dt.MetricQueryPool.pfnCreate)>(Cal::Icd::LevelZero::Unimplemented::zetMetricQueryPoolCreateUnimpl);
    dt.MetricQueryPool.pfnDestroy = reinterpret_cast<decltype(dt.MetricQueryPool.pfnDestroy)>(Cal::Icd::LevelZero::Unimplemented::zetMetricQueryPoolDestroyUnimpl);
    dt.MetricQuery.pfnCreate = reinterpret_cast<decltype(dt.MetricQuery.pfnCreate)>(Cal::Icd::LevelZero::Unimplemented::zetMetricQueryCreateUnimpl);
    dt.MetricQuery.pfnDestroy = reinterpret_cast<decltype(dt.MetricQuery.pfnDestroy)>(Cal::Icd::LevelZero::Unimplemented::zetMetricQueryDestroyUnimpl);
    dt.MetricQuery.pfnReset = reinterpret_cast<decltype(dt.MetricQuery.pfnReset)>(Cal::Icd::LevelZero::Unimplemented::zetMetricQueryResetUnimpl);
    dt.CommandList.pfnAppendMetricQueryBegin = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricQueryBegin)>(Cal::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricQueryBeginUnimpl);
    dt.CommandList.pfnAppendMetricQueryEnd = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricQueryEnd)>(Cal::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricQueryEndUnimpl);
    dt.CommandList.pfnAppendMetricMemoryBarrier = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricMemoryBarrier)>(Cal::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricMemoryBarrierUnimpl);
    dt.MetricQuery.pfnGetData = reinterpret_cast<decltype(dt.MetricQuery.pfnGetData)>(Cal::Icd::LevelZero::Unimplemented::zetMetricQueryGetDataUnimpl);
    dt.TracerExp.pfnCreate = reinterpret_cast<decltype(dt.TracerExp.pfnCreate)>(Cal::Icd::LevelZero::Unimplemented::zetTracerExpCreateUnimpl);
    dt.TracerExp.pfnDestroy = reinterpret_cast<decltype(dt.TracerExp.pfnDestroy)>(Cal::Icd::LevelZero::Unimplemented::zetTracerExpDestroyUnimpl);
    dt.TracerExp.pfnSetPrologues = reinterpret_cast<decltype(dt.TracerExp.pfnSetPrologues)>(Cal::Icd::LevelZero::Unimplemented::zetTracerExpSetProloguesUnimpl);
    dt.TracerExp.pfnSetEpilogues = reinterpret_cast<decltype(dt.TracerExp.pfnSetEpilogues)>(Cal::Icd::LevelZero::Unimplemented::zetTracerExpSetEpiloguesUnimpl);
    dt.TracerExp.pfnSetEnabled = reinterpret_cast<decltype(dt.TracerExp.pfnSetEnabled)>(Cal::Icd::LevelZero::Unimplemented::zetTracerExpSetEnabledUnimpl);
}

void *getL0ExtensionFuncionAddressRpcHelper(const char *funcName);
} // namespace LevelZero
} // namespace Icd
} // namespace Cal
// #### Generated code -- end ####
