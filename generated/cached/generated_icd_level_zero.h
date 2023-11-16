/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####

#include "shared/log.h"
#include "shared/shmem_transfer_desc.h"
#include "client/icd/icd_global_state.h"
#include "client/icd/level_zero/api_customization/icd_level_zero_api.h"
#include "client/icd/level_zero/api_customization/icd_level_zero_api_sysman.h"
#include "client/icd/level_zero/api_customization/icd_level_zero_api_tracing.h"
#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"
#include "level_zero/zes_api.h"
#include "level_zero/zes_ddi.h"
#include "level_zero/zet_api.h"
#include "level_zero/zet_ddi.h"

#include <cstdlib>

// Forward declarations of used RPC types
namespace Cal {
namespace Rpc {
namespace LevelZero {

struct ZeMemAllocSharedRpcMImplicitArgs;
struct ZeMemAllocHostRpcMImplicitArgs;

} // namespace LevelZero
} // namespace Rpc
} // namespace Cal

namespace Cal {
namespace Client {
namespace Icd {
namespace LevelZero {
ze_result_t zetTracerExpCreate (zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer);
ze_result_t zetTracerExpDestroy (zet_tracer_exp_handle_t hTracer);
ze_result_t zetTracerExpSetPrologues (zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs);
ze_result_t zetTracerExpSetEpilogues (zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs);
ze_result_t zetTracerExpSetEnabled (zet_tracer_exp_handle_t hTracer, ze_bool_t enable);
ze_result_t zesDeviceReset (zes_device_handle_t hDevice, ze_bool_t force);
ze_result_t zesDeviceResetExt (zes_device_handle_t hDevice, zes_reset_properties_t* pProperties);
ze_result_t zesDeviceEnumPowerDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower);
ze_result_t zesDeviceGetCardPowerDomain (zes_device_handle_t hDevice, zes_pwr_handle_t* phPower);
ze_result_t zesPowerGetProperties (zes_pwr_handle_t hPower, zes_power_properties_t* pProperties);
ze_result_t zesPowerGetEnergyCounter (zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy);
ze_result_t zesPowerGetLimits (zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak);
ze_result_t zesPowerSetLimits (zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak);
ze_result_t zesPowerGetEnergyThreshold (zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold);
ze_result_t zesPowerSetEnergyThreshold (zes_pwr_handle_t hPower, double pThreshold);
ze_result_t zesDeviceEnumEngineGroups (zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine);
ze_result_t zesEngineGetProperties (zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties);
ze_result_t zesEngineGetActivity (zes_engine_handle_t hEngine, zes_engine_stats_t* pStats);
ze_result_t zesDeviceGetState (zes_device_handle_t hDevice, zes_device_state_t* pState);
ze_result_t zesDeviceProcessesGetState (zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses);
ze_result_t zesDevicePciGetProperties (zes_device_handle_t hDevice, zes_pci_properties_t* pProperties);
ze_result_t zesDevicePciGetState (zes_device_handle_t hDevice, zes_pci_state_t* pState);
ze_result_t zesDevicePciGetBars (zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties);
ze_result_t zesDevicePciGetStats (zes_device_handle_t hDevice, zes_pci_stats_t* pStats);
ze_result_t zesDeviceGetPropertiesRpcHelper (zes_device_handle_t hDevice, zes_device_properties_t* pProperties);
ze_result_t zesDeviceEnumMemoryModules (zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory);
ze_result_t zeInitRpcHelper (ze_init_flags_t flags);
ze_result_t zeContextSystemBarrier (ze_context_handle_t hContext, ze_device_handle_t hDevice);
ze_result_t zeContextSystemBarrier_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice);
ze_result_t zeCommandListCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList);
ze_result_t zeCommandListCreate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList);
ze_result_t zeCommandListCreateImmediate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList);
ze_result_t zeCommandListCreateImmediate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList);
ze_result_t zeCommandListDestroy (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListDestroy_WithTracing (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListClose (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListClose_WithTracing (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListReset (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListReset_WithTracing (ze_command_list_handle_t hCommandList);
ze_result_t zeCommandListAppendWriteGlobalTimestamp (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendWriteGlobalTimestamp_WithTracing (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandQueueCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
ze_result_t zeCommandQueueCreate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue);
ze_result_t zeCommandQueueDestroy_WithTracing (ze_command_queue_handle_t hCommandQueue);
ze_result_t zeCommandQueueExecuteCommandListsRpcHelper (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeCommandQueueExecuteCommandLists_WithTracing (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::TransferDesc* transferDescs);
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper_WithTracing (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::TransferDesc* transferDescs);
ze_result_t zeCommandQueueSynchronize (ze_command_queue_handle_t hCommandQueue, uint64_t timeout);
ze_result_t zeCommandQueueSynchronize_WithTracing (ze_command_queue_handle_t hCommandQueue, uint64_t timeout);
ze_result_t zeContextCreate (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext);
ze_result_t zeContextCreate_WithTracing (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext);
ze_result_t zeContextCreateEx (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext);
ze_result_t zeContextDestroy (ze_context_handle_t hContext);
ze_result_t zeContextDestroy_WithTracing (ze_context_handle_t hContext);
ze_result_t zeContextGetStatus (ze_context_handle_t hContext);
ze_result_t zeContextGetStatus_WithTracing (ze_context_handle_t hContext);
ze_result_t zeCommandListAppendMemoryCopy (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopy_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFill (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFill_WithTracing (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Usm_WithTracing (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Malloc (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Malloc_WithTracing (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Usm_WithTracing (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc_WithTracing (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryPrefetch (ze_command_list_handle_t hCommandList, const void* ptr, size_t size);
ze_result_t zeCommandListAppendMemoryPrefetch_WithTracing (ze_command_list_handle_t hCommandList, const void* ptr, size_t size);
ze_result_t zeCommandListAppendMemAdvise (ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice);
ze_result_t zeCommandListAppendMemAdvise_WithTracing (ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice);
ze_result_t zeDeviceGetRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
ze_result_t zeDeviceGet_WithTracing (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
ze_result_t zeDeviceGetSubDevicesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
ze_result_t zeDeviceGetSubDevices_WithTracing (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
ze_result_t zeDeviceGetPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties);
ze_result_t zeDeviceGetProperties_WithTracing (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties);
ze_result_t zeDeviceGetComputePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties);
ze_result_t zeDeviceGetComputeProperties_WithTracing (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties);
ze_result_t zeDeviceGetModulePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties);
ze_result_t zeDeviceGetModuleProperties_WithTracing (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties);
ze_result_t zeDeviceGetCommandQueueGroupPropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
ze_result_t zeDeviceGetCommandQueueGroupProperties_WithTracing (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
ze_result_t zeDeviceGetMemoryPropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
ze_result_t zeDeviceGetMemoryProperties_WithTracing (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
ze_result_t zeDeviceGetMemoryAccessPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties);
ze_result_t zeDeviceGetMemoryAccessProperties_WithTracing (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties);
ze_result_t zeDeviceGetCachePropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
ze_result_t zeDeviceGetCacheProperties_WithTracing (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
ze_result_t zeDeviceGetImagePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties);
ze_result_t zeDeviceGetImageProperties_WithTracing (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties);
ze_result_t zeDeviceGetExternalMemoryPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties);
ze_result_t zeDeviceGetExternalMemoryProperties_WithTracing (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties);
ze_result_t zeDeviceGetP2PProperties (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties);
ze_result_t zeDeviceGetP2PProperties_WithTracing (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties);
ze_result_t zeDeviceCanAccessPeer (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value);
ze_result_t zeDeviceCanAccessPeer_WithTracing (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value);
ze_result_t zeDeviceGetStatus (ze_device_handle_t hDevice);
ze_result_t zeDeviceGetStatus_WithTracing (ze_device_handle_t hDevice);
ze_result_t zeDeviceGetGlobalTimestamps (ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp);
ze_result_t zeDeviceReserveCacheExt (ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize);
ze_result_t zeDeviceSetCacheAdviceExt (ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion);
ze_result_t zeDriverGetRpcHelper (uint32_t* pCount, ze_driver_handle_t* phDrivers);
ze_result_t zeDriverGet_WithTracing (uint32_t* pCount, ze_driver_handle_t* phDrivers);
ze_result_t zeDriverGetApiVersion (ze_driver_handle_t hDriver, ze_api_version_t* version);
ze_result_t zeDriverGetApiVersion_WithTracing (ze_driver_handle_t hDriver, ze_api_version_t* version);
ze_result_t zeDriverGetPropertiesRpcHelper (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties);
ze_result_t zeDriverGetProperties_WithTracing (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties);
ze_result_t zeDriverGetIpcPropertiesRpcHelper (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties);
ze_result_t zeDriverGetIpcProperties_WithTracing (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties);
ze_result_t zeDriverGetExtensionPropertiesRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
ze_result_t zeDriverGetExtensionProperties_WithTracing (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
ze_result_t zeDriverGetExtensionFunctionAddress (ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress);
ze_result_t zeEventPoolCreate (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolCreate_WithTracing (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool);
ze_result_t zeEventPoolDestroy_WithTracing (ze_event_pool_handle_t hEventPool);
ze_result_t zeEventCreate (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent);
ze_result_t zeEventCreate_WithTracing (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent);
ze_result_t zeEventDestroy (ze_event_handle_t hEvent);
ze_result_t zeEventDestroy_WithTracing (ze_event_handle_t hEvent);
ze_result_t zeEventPoolGetIpcHandleRpcHelper (ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc);
ze_result_t zeEventPoolGetIpcHandle_WithTracing (ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc);
ze_result_t zeEventPoolOpenIpcHandleRpcHelper (ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolOpenIpcHandle_WithTracing (ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool);
ze_result_t zeEventPoolCloseIpcHandle (ze_event_pool_handle_t hEventPool);
ze_result_t zeEventPoolCloseIpcHandle_WithTracing (ze_event_pool_handle_t hEventPool);
ze_result_t zeCommandListAppendBarrier (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendBarrier_WithTracing (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendSignalEvent_WithTracing (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
ze_result_t zeCommandListAppendWaitOnEvents_WithTracing (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
ze_result_t zeEventHostSignal (ze_event_handle_t hEvent);
ze_result_t zeEventHostSignal_WithTracing (ze_event_handle_t hEvent);
ze_result_t zeEventHostSynchronize (ze_event_handle_t hEvent, uint64_t timeout);
ze_result_t zeEventHostSynchronize_WithTracing (ze_event_handle_t hEvent, uint64_t timeout);
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent);
ze_result_t zeEventQueryStatus_WithTracing (ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendEventReset (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeCommandListAppendEventReset_WithTracing (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
ze_result_t zeEventHostReset (ze_event_handle_t hEvent);
ze_result_t zeEventHostReset_WithTracing (ze_event_handle_t hEvent);
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr);
ze_result_t zeEventQueryKernelTimestamp_WithTracing (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr);
ze_result_t zeCommandListAppendQueryKernelTimestampsRpcHelper (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendQueryKernelTimestamps_WithTracing (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeEventQueryTimestampsExp (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps);
ze_result_t zeEventQueryKernelTimestampsExt (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults);
ze_result_t zeEventQueryKernelTimestampsExtRpcHelper (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pResultsTimestamps, ze_synchronized_timestamp_result_ext_t* pResultsSynchronizedTimestamps);
ze_result_t zeEventQueryKernelTimestampsExtRpcHelper_WithTracing (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pResultsTimestamps, ze_synchronized_timestamp_result_ext_t* pResultsSynchronizedTimestamps);
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence);
ze_result_t zeFenceCreate_WithTracing (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence);
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence);
ze_result_t zeFenceDestroy_WithTracing (ze_fence_handle_t hFence);
ze_result_t zeFenceHostSynchronize (ze_fence_handle_t hFence, uint64_t timeout);
ze_result_t zeFenceHostSynchronize_WithTracing (ze_fence_handle_t hFence, uint64_t timeout);
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence);
ze_result_t zeFenceQueryStatus_WithTracing (ze_fence_handle_t hFence);
ze_result_t zeFenceReset (ze_fence_handle_t hFence);
ze_result_t zeFenceReset_WithTracing (ze_fence_handle_t hFence);
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
ze_result_t zeImageGetProperties (ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties);
ze_result_t zeImageGetProperties_WithTracing (ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties);
ze_result_t zeImageCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage);
ze_result_t zeImageCreate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage);
ze_result_t zeImageDestroy (ze_image_handle_t hImage);
ze_result_t zeImageDestroy_WithTracing (ze_image_handle_t hImage);
ze_result_t zeKernelSchedulingHintExp (ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint);
ze_result_t zeMemAllocSharedRpcHelper (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocSharedRpcMImplicitArgs &implArgsForZeMemAllocSharedRpcM);
ze_result_t zeMemAllocShared_WithTracing (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
ze_result_t zeMemAllocDevice (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
ze_result_t zeMemAllocDevice_WithTracing (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
ze_result_t zeMemAllocHostRpcHelper (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocHostRpcMImplicitArgs &implArgsForZeMemAllocHostRpcM);
ze_result_t zeMemAllocHost_WithTracing (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr);
ze_result_t zeMemFree (ze_context_handle_t hContext, void* ptr);
ze_result_t zeMemFree_WithTracing (ze_context_handle_t hContext, void* ptr);
ze_result_t zeMemGetAllocPropertiesRpcHelper (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice);
ze_result_t zeMemGetAllocProperties_WithTracing (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice);
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize);
ze_result_t zeMemGetAddressRange_WithTracing (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize);
ze_result_t zeMemGetIpcHandleRpcHelper (ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle);
ze_result_t zeMemGetIpcHandle_WithTracing (ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle);
ze_result_t zeMemOpenIpcHandleRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zeMemOpenIpcHandle_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zeMemCloseIpcHandle (ze_context_handle_t hContext, const void* ptr);
ze_result_t zeMemCloseIpcHandle_WithTracing (ze_context_handle_t hContext, const void* ptr);
ze_result_t zexMemGetIpcHandlesRpcHelper (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
ze_result_t zexMemGetIpcHandles_WithTracing (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
ze_result_t zexMemOpenIpcHandlesRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zexMemOpenIpcHandles_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zeMemFreeExt (ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr);
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
ze_result_t zeModuleCreate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
ze_result_t zeModuleDestroy (ze_module_handle_t hModule);
ze_result_t zeModuleDestroy_WithTracing (ze_module_handle_t hModule);
ze_result_t zeModuleDynamicLink (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog);
ze_result_t zeModuleDynamicLink_WithTracing (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog);
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog);
ze_result_t zeModuleBuildLogDestroy_WithTracing (ze_module_build_log_handle_t hModuleBuildLog);
ze_result_t zeModuleBuildLogGetString (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
ze_result_t zeModuleBuildLogGetString_WithTracing (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
ze_result_t zeModuleGetNativeBinary (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary);
ze_result_t zeModuleGetNativeBinary_WithTracing (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary);
ze_result_t zeModuleGetGlobalPointer (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
ze_result_t zeModuleGetGlobalPointer_WithTracing (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
ze_result_t zeModuleGetKernelNames (ze_module_handle_t hModule, uint32_t* pCount, const char** pNames);
ze_result_t zeModuleGetKernelNames_WithTracing (ze_module_handle_t hModule, uint32_t* pCount, const char** pNames);
ze_result_t zeModuleGetKernelNamesRpcHelper (ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer);
ze_result_t zeModuleGetKernelNamesRpcHelper_WithTracing (ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer);
ze_result_t zeModuleGetPropertiesRpcHelper (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties);
ze_result_t zeModuleGetProperties_WithTracing (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties);
ze_result_t zeKernelCreate (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
ze_result_t zeKernelCreate_WithTracing (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel);
ze_result_t zeKernelDestroy_WithTracing (ze_kernel_handle_t hKernel);
ze_result_t zeModuleGetFunctionPointer (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
ze_result_t zeModuleGetFunctionPointer_WithTracing (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
ze_result_t zeKernelSetGroupSizeRpcHelper (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ);
ze_result_t zeKernelSetGroupSize_WithTracing (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ);
ze_result_t zeKernelSuggestGroupSizeRpcHelper (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ);
ze_result_t zeKernelSuggestGroupSize_WithTracing (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ);
ze_result_t zeKernelSuggestMaxCooperativeGroupCount (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount);
ze_result_t zeKernelSuggestMaxCooperativeGroupCount_WithTracing (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount);
ze_result_t zeKernelSetArgumentValueRpcHelper (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
ze_result_t zeKernelSetArgumentValue_WithTracing (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags);
ze_result_t zeKernelSetIndirectAccess_WithTracing (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags);
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags);
ze_result_t zeKernelGetIndirectAccess_WithTracing (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags);
ze_result_t zeKernelSetCacheConfig (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags);
ze_result_t zeKernelSetCacheConfig_WithTracing (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags);
ze_result_t zeKernelGetPropertiesRpcHelper (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties);
ze_result_t zeKernelGetProperties_WithTracing (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties);
ze_result_t zeKernelGetName (ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
ze_result_t zeKernelGetName_WithTracing (ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
ze_result_t zeCommandListAppendLaunchKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchKernel_WithTracing (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchCooperativeKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchCooperativeKernel_WithTracing (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchKernelIndirect (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchKernelIndirect_WithTracing (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirect (ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirect_WithTracing (ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListHostSynchronize (ze_command_list_handle_t hCommandList, uint64_t timeout);
ze_result_t zeDevicePciGetPropertiesExt (ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties);
ze_result_t zeContextMakeMemoryResident (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size);
ze_result_t zeContextMakeMemoryResident_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size);
ze_result_t zeContextEvictMemory (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size);
ze_result_t zeContextEvictMemory_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size);
ze_result_t zeVirtualMemReserve (ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr);
ze_result_t zeVirtualMemReserve_WithTracing (ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr);
ze_result_t zeVirtualMemFree (ze_context_handle_t hContext, const void* ptr, size_t size);
ze_result_t zeVirtualMemFree_WithTracing (ze_context_handle_t hContext, const void* ptr, size_t size);
ze_result_t zeVirtualMemQueryPageSize (ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize);
ze_result_t zeVirtualMemQueryPageSize_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize);
ze_result_t zePhysicalMemCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory);
ze_result_t zePhysicalMemCreate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory);
ze_result_t zePhysicalMemDestroy (ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory);
ze_result_t zePhysicalMemDestroy_WithTracing (ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory);
ze_result_t zeVirtualMemMap (ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access);
ze_result_t zeVirtualMemMap_WithTracing (ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access);
ze_result_t zeVirtualMemUnmap (ze_context_handle_t hContext, const void* ptr, size_t size);
ze_result_t zeVirtualMemUnmap_WithTracing (ze_context_handle_t hContext, const void* ptr, size_t size);
ze_result_t zeVirtualMemSetAccessAttribute (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access);
ze_result_t zeVirtualMemSetAccessAttribute_WithTracing (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access);
ze_result_t zeVirtualMemGetAccessAttribute (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize);
ze_result_t zeVirtualMemGetAccessAttribute_WithTracing (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize);
ze_result_t zexDriverImportExternalPointerRpcHelper (ze_driver_handle_t hDriver, void* ptr, size_t size);
ze_result_t zexDriverImportExternalPointer_WithTracing (ze_driver_handle_t hDriver, void* ptr, size_t size);
ze_result_t zexDriverReleaseImportedPointerRpcHelper (ze_driver_handle_t hDriver, void* ptr);
ze_result_t zexDriverReleaseImportedPointer_WithTracing (ze_driver_handle_t hDriver, void* ptr);
ze_result_t zexDriverGetHostPointerBaseAddressRpcHelper (ze_driver_handle_t hDriver, void* ptr, void** baseAddress);
ze_result_t zexDriverGetHostPointerBaseAddress_WithTracing (ze_driver_handle_t hDriver, void* ptr, void** baseAddress);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Local_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Local_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Local_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);

namespace Unimplemented {
inline void zeCommandListAppendMemoryRangesBarrierUnimpl() {
    log<Verbosity::critical>("Function CommandList.zeCommandListAppendMemoryRangesBarrier is not yet implemented in Compute Aggregation Layer - aborting");
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
inline void zeModuleInspectLinkageExtUnimpl() {
    log<Verbosity::critical>("Function Module.zeModuleInspectLinkageExt is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
inline void zeKernelGetSourceAttributesUnimpl() {
    log<Verbosity::critical>("Function Kernel.zeKernelGetSourceAttributes is not yet implemented in Compute Aggregation Layer - aborting");
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
} // Unimplemented

inline void initL0Ddi(ze_dditable_t &dt){
    dt.Global.pfnInit = Cal::Client::Icd::LevelZero::zeInit;
    dt.Context.pfnSystemBarrier = Cal::Client::Icd::LevelZero::zeContextSystemBarrier;
    if (tracingEnabled) {
        dt.Context.pfnSystemBarrier = Cal::Client::Icd::LevelZero::zeContextSystemBarrier_WithTracing;
    }
    dt.CommandList.pfnCreate = Cal::Client::Icd::LevelZero::zeCommandListCreate;
    if (tracingEnabled) {
        dt.CommandList.pfnCreate = Cal::Client::Icd::LevelZero::zeCommandListCreate_WithTracing;
    }
    dt.CommandList.pfnCreateImmediate = Cal::Client::Icd::LevelZero::zeCommandListCreateImmediate;
    if (tracingEnabled) {
        dt.CommandList.pfnCreateImmediate = Cal::Client::Icd::LevelZero::zeCommandListCreateImmediate_WithTracing;
    }
    dt.CommandList.pfnDestroy = Cal::Client::Icd::LevelZero::zeCommandListDestroy;
    if (tracingEnabled) {
        dt.CommandList.pfnDestroy = Cal::Client::Icd::LevelZero::zeCommandListDestroy_WithTracing;
    }
    dt.CommandList.pfnClose = Cal::Client::Icd::LevelZero::zeCommandListClose;
    if (tracingEnabled) {
        dt.CommandList.pfnClose = Cal::Client::Icd::LevelZero::zeCommandListClose_WithTracing;
    }
    dt.CommandList.pfnReset = Cal::Client::Icd::LevelZero::zeCommandListReset;
    if (tracingEnabled) {
        dt.CommandList.pfnReset = Cal::Client::Icd::LevelZero::zeCommandListReset_WithTracing;
    }
    dt.CommandList.pfnAppendWriteGlobalTimestamp = Cal::Client::Icd::LevelZero::zeCommandListAppendWriteGlobalTimestamp;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendWriteGlobalTimestamp = Cal::Client::Icd::LevelZero::zeCommandListAppendWriteGlobalTimestamp_WithTracing;
    }
    dt.CommandQueue.pfnCreate = Cal::Client::Icd::LevelZero::zeCommandQueueCreate;
    if (tracingEnabled) {
        dt.CommandQueue.pfnCreate = Cal::Client::Icd::LevelZero::zeCommandQueueCreate_WithTracing;
    }
    dt.CommandQueue.pfnDestroy = Cal::Client::Icd::LevelZero::zeCommandQueueDestroy;
    if (tracingEnabled) {
        dt.CommandQueue.pfnDestroy = Cal::Client::Icd::LevelZero::zeCommandQueueDestroy_WithTracing;
    }
    dt.CommandQueue.pfnExecuteCommandLists = Cal::Client::Icd::LevelZero::zeCommandQueueExecuteCommandLists;
    if (tracingEnabled) {
        dt.CommandQueue.pfnExecuteCommandLists = Cal::Client::Icd::LevelZero::zeCommandQueueExecuteCommandLists_WithTracing;
    }
    dt.CommandQueue.pfnSynchronize = Cal::Client::Icd::LevelZero::zeCommandQueueSynchronize;
    if (tracingEnabled) {
        dt.CommandQueue.pfnSynchronize = Cal::Client::Icd::LevelZero::zeCommandQueueSynchronize_WithTracing;
    }
    dt.Context.pfnCreate = Cal::Client::Icd::LevelZero::zeContextCreate;
    if (tracingEnabled) {
        dt.Context.pfnCreate = Cal::Client::Icd::LevelZero::zeContextCreate_WithTracing;
    }
    dt.Context.pfnCreateEx = Cal::Client::Icd::LevelZero::zeContextCreateEx;
    dt.Context.pfnDestroy = Cal::Client::Icd::LevelZero::zeContextDestroy;
    if (tracingEnabled) {
        dt.Context.pfnDestroy = Cal::Client::Icd::LevelZero::zeContextDestroy_WithTracing;
    }
    dt.Context.pfnGetStatus = Cal::Client::Icd::LevelZero::zeContextGetStatus;
    if (tracingEnabled) {
        dt.Context.pfnGetStatus = Cal::Client::Icd::LevelZero::zeContextGetStatus_WithTracing;
    }
    dt.CommandList.pfnAppendMemoryCopy = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopy;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemoryCopy = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopy_WithTracing;
    }
    dt.CommandList.pfnAppendMemoryFill = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryFill;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemoryFill = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryFill_WithTracing;
    }
    dt.CommandList.pfnAppendMemoryPrefetch = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryPrefetch;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemoryPrefetch = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryPrefetch_WithTracing;
    }
    dt.CommandList.pfnAppendMemAdvise = Cal::Client::Icd::LevelZero::zeCommandListAppendMemAdvise;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemAdvise = Cal::Client::Icd::LevelZero::zeCommandListAppendMemAdvise_WithTracing;
    }
    dt.Device.pfnGet = Cal::Client::Icd::LevelZero::zeDeviceGet;
    if (tracingEnabled) {
        dt.Device.pfnGet = Cal::Client::Icd::LevelZero::zeDeviceGet_WithTracing;
    }
    dt.Device.pfnGetSubDevices = Cal::Client::Icd::LevelZero::zeDeviceGetSubDevices;
    if (tracingEnabled) {
        dt.Device.pfnGetSubDevices = Cal::Client::Icd::LevelZero::zeDeviceGetSubDevices_WithTracing;
    }
    dt.Device.pfnGetProperties = Cal::Client::Icd::LevelZero::zeDeviceGetProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetProperties = Cal::Client::Icd::LevelZero::zeDeviceGetProperties_WithTracing;
    }
    dt.Device.pfnGetComputeProperties = Cal::Client::Icd::LevelZero::zeDeviceGetComputeProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetComputeProperties = Cal::Client::Icd::LevelZero::zeDeviceGetComputeProperties_WithTracing;
    }
    dt.Device.pfnGetModuleProperties = Cal::Client::Icd::LevelZero::zeDeviceGetModuleProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetModuleProperties = Cal::Client::Icd::LevelZero::zeDeviceGetModuleProperties_WithTracing;
    }
    dt.Device.pfnGetCommandQueueGroupProperties = Cal::Client::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetCommandQueueGroupProperties = Cal::Client::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties_WithTracing;
    }
    dt.Device.pfnGetMemoryProperties = Cal::Client::Icd::LevelZero::zeDeviceGetMemoryProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetMemoryProperties = Cal::Client::Icd::LevelZero::zeDeviceGetMemoryProperties_WithTracing;
    }
    dt.Device.pfnGetMemoryAccessProperties = Cal::Client::Icd::LevelZero::zeDeviceGetMemoryAccessProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetMemoryAccessProperties = Cal::Client::Icd::LevelZero::zeDeviceGetMemoryAccessProperties_WithTracing;
    }
    dt.Device.pfnGetCacheProperties = Cal::Client::Icd::LevelZero::zeDeviceGetCacheProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetCacheProperties = Cal::Client::Icd::LevelZero::zeDeviceGetCacheProperties_WithTracing;
    }
    dt.Device.pfnGetImageProperties = Cal::Client::Icd::LevelZero::zeDeviceGetImageProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetImageProperties = Cal::Client::Icd::LevelZero::zeDeviceGetImageProperties_WithTracing;
    }
    dt.Device.pfnGetExternalMemoryProperties = Cal::Client::Icd::LevelZero::zeDeviceGetExternalMemoryProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetExternalMemoryProperties = Cal::Client::Icd::LevelZero::zeDeviceGetExternalMemoryProperties_WithTracing;
    }
    dt.Device.pfnGetP2PProperties = Cal::Client::Icd::LevelZero::zeDeviceGetP2PProperties;
    if (tracingEnabled) {
        dt.Device.pfnGetP2PProperties = Cal::Client::Icd::LevelZero::zeDeviceGetP2PProperties_WithTracing;
    }
    dt.Device.pfnCanAccessPeer = Cal::Client::Icd::LevelZero::zeDeviceCanAccessPeer;
    if (tracingEnabled) {
        dt.Device.pfnCanAccessPeer = Cal::Client::Icd::LevelZero::zeDeviceCanAccessPeer_WithTracing;
    }
    dt.Device.pfnGetStatus = Cal::Client::Icd::LevelZero::zeDeviceGetStatus;
    if (tracingEnabled) {
        dt.Device.pfnGetStatus = Cal::Client::Icd::LevelZero::zeDeviceGetStatus_WithTracing;
    }
    dt.Device.pfnGetGlobalTimestamps = Cal::Client::Icd::LevelZero::zeDeviceGetGlobalTimestamps;
    dt.Device.pfnReserveCacheExt = Cal::Client::Icd::LevelZero::zeDeviceReserveCacheExt;
    dt.Device.pfnSetCacheAdviceExt = Cal::Client::Icd::LevelZero::zeDeviceSetCacheAdviceExt;
    dt.Driver.pfnGet = Cal::Client::Icd::LevelZero::zeDriverGet;
    if (tracingEnabled) {
        dt.Driver.pfnGet = Cal::Client::Icd::LevelZero::zeDriverGet_WithTracing;
    }
    dt.Driver.pfnGetApiVersion = Cal::Client::Icd::LevelZero::zeDriverGetApiVersion;
    if (tracingEnabled) {
        dt.Driver.pfnGetApiVersion = Cal::Client::Icd::LevelZero::zeDriverGetApiVersion_WithTracing;
    }
    dt.Driver.pfnGetProperties = Cal::Client::Icd::LevelZero::zeDriverGetProperties;
    if (tracingEnabled) {
        dt.Driver.pfnGetProperties = Cal::Client::Icd::LevelZero::zeDriverGetProperties_WithTracing;
    }
    dt.Driver.pfnGetIpcProperties = Cal::Client::Icd::LevelZero::zeDriverGetIpcProperties;
    if (tracingEnabled) {
        dt.Driver.pfnGetIpcProperties = Cal::Client::Icd::LevelZero::zeDriverGetIpcProperties_WithTracing;
    }
    dt.Driver.pfnGetExtensionProperties = Cal::Client::Icd::LevelZero::zeDriverGetExtensionProperties;
    if (tracingEnabled) {
        dt.Driver.pfnGetExtensionProperties = Cal::Client::Icd::LevelZero::zeDriverGetExtensionProperties_WithTracing;
    }
    dt.Driver.pfnGetExtensionFunctionAddress = Cal::Client::Icd::LevelZero::zeDriverGetExtensionFunctionAddress;
    dt.EventPool.pfnCreate = Cal::Client::Icd::LevelZero::zeEventPoolCreate;
    if (tracingEnabled) {
        dt.EventPool.pfnCreate = Cal::Client::Icd::LevelZero::zeEventPoolCreate_WithTracing;
    }
    dt.EventPool.pfnDestroy = Cal::Client::Icd::LevelZero::zeEventPoolDestroy;
    if (tracingEnabled) {
        dt.EventPool.pfnDestroy = Cal::Client::Icd::LevelZero::zeEventPoolDestroy_WithTracing;
    }
    dt.Event.pfnCreate = Cal::Client::Icd::LevelZero::zeEventCreate;
    if (tracingEnabled) {
        dt.Event.pfnCreate = Cal::Client::Icd::LevelZero::zeEventCreate_WithTracing;
    }
    dt.Event.pfnDestroy = Cal::Client::Icd::LevelZero::zeEventDestroy;
    if (tracingEnabled) {
        dt.Event.pfnDestroy = Cal::Client::Icd::LevelZero::zeEventDestroy_WithTracing;
    }
    dt.EventPool.pfnGetIpcHandle = Cal::Client::Icd::LevelZero::zeEventPoolGetIpcHandle;
    if (tracingEnabled) {
        dt.EventPool.pfnGetIpcHandle = Cal::Client::Icd::LevelZero::zeEventPoolGetIpcHandle_WithTracing;
    }
    dt.EventPool.pfnOpenIpcHandle = Cal::Client::Icd::LevelZero::zeEventPoolOpenIpcHandle;
    if (tracingEnabled) {
        dt.EventPool.pfnOpenIpcHandle = Cal::Client::Icd::LevelZero::zeEventPoolOpenIpcHandle_WithTracing;
    }
    dt.EventPool.pfnCloseIpcHandle = Cal::Client::Icd::LevelZero::zeEventPoolCloseIpcHandle;
    if (tracingEnabled) {
        dt.EventPool.pfnCloseIpcHandle = Cal::Client::Icd::LevelZero::zeEventPoolCloseIpcHandle_WithTracing;
    }
    dt.CommandList.pfnAppendBarrier = Cal::Client::Icd::LevelZero::zeCommandListAppendBarrier;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendBarrier = Cal::Client::Icd::LevelZero::zeCommandListAppendBarrier_WithTracing;
    }
    dt.CommandList.pfnAppendSignalEvent = Cal::Client::Icd::LevelZero::zeCommandListAppendSignalEvent;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendSignalEvent = Cal::Client::Icd::LevelZero::zeCommandListAppendSignalEvent_WithTracing;
    }
    dt.CommandList.pfnAppendWaitOnEvents = Cal::Client::Icd::LevelZero::zeCommandListAppendWaitOnEvents;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendWaitOnEvents = Cal::Client::Icd::LevelZero::zeCommandListAppendWaitOnEvents_WithTracing;
    }
    dt.Event.pfnHostSignal = Cal::Client::Icd::LevelZero::zeEventHostSignal;
    if (tracingEnabled) {
        dt.Event.pfnHostSignal = Cal::Client::Icd::LevelZero::zeEventHostSignal_WithTracing;
    }
    dt.Event.pfnHostSynchronize = Cal::Client::Icd::LevelZero::zeEventHostSynchronize;
    if (tracingEnabled) {
        dt.Event.pfnHostSynchronize = Cal::Client::Icd::LevelZero::zeEventHostSynchronize_WithTracing;
    }
    dt.Event.pfnQueryStatus = Cal::Client::Icd::LevelZero::zeEventQueryStatus;
    if (tracingEnabled) {
        dt.Event.pfnQueryStatus = Cal::Client::Icd::LevelZero::zeEventQueryStatus_WithTracing;
    }
    dt.CommandList.pfnAppendEventReset = Cal::Client::Icd::LevelZero::zeCommandListAppendEventReset;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendEventReset = Cal::Client::Icd::LevelZero::zeCommandListAppendEventReset_WithTracing;
    }
    dt.Event.pfnHostReset = Cal::Client::Icd::LevelZero::zeEventHostReset;
    if (tracingEnabled) {
        dt.Event.pfnHostReset = Cal::Client::Icd::LevelZero::zeEventHostReset_WithTracing;
    }
    dt.Event.pfnQueryKernelTimestamp = Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestamp;
    if (tracingEnabled) {
        dt.Event.pfnQueryKernelTimestamp = Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestamp_WithTracing;
    }
    dt.CommandList.pfnAppendQueryKernelTimestamps = Cal::Client::Icd::LevelZero::zeCommandListAppendQueryKernelTimestamps;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendQueryKernelTimestamps = Cal::Client::Icd::LevelZero::zeCommandListAppendQueryKernelTimestamps_WithTracing;
    }
    dt.EventExp.pfnQueryTimestampsExp = Cal::Client::Icd::LevelZero::zeEventQueryTimestampsExp;
    dt.Event.pfnQueryKernelTimestampsExt = Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestampsExt;
    dt.Fence.pfnCreate = Cal::Client::Icd::LevelZero::zeFenceCreate;
    if (tracingEnabled) {
        dt.Fence.pfnCreate = Cal::Client::Icd::LevelZero::zeFenceCreate_WithTracing;
    }
    dt.Fence.pfnDestroy = Cal::Client::Icd::LevelZero::zeFenceDestroy;
    if (tracingEnabled) {
        dt.Fence.pfnDestroy = Cal::Client::Icd::LevelZero::zeFenceDestroy_WithTracing;
    }
    dt.Fence.pfnHostSynchronize = Cal::Client::Icd::LevelZero::zeFenceHostSynchronize;
    if (tracingEnabled) {
        dt.Fence.pfnHostSynchronize = Cal::Client::Icd::LevelZero::zeFenceHostSynchronize_WithTracing;
    }
    dt.Fence.pfnQueryStatus = Cal::Client::Icd::LevelZero::zeFenceQueryStatus;
    if (tracingEnabled) {
        dt.Fence.pfnQueryStatus = Cal::Client::Icd::LevelZero::zeFenceQueryStatus_WithTracing;
    }
    dt.Fence.pfnReset = Cal::Client::Icd::LevelZero::zeFenceReset;
    if (tracingEnabled) {
        dt.Fence.pfnReset = Cal::Client::Icd::LevelZero::zeFenceReset_WithTracing;
    }
    dt.KernelExp.pfnSetGlobalOffsetExp = Cal::Client::Icd::LevelZero::zeKernelSetGlobalOffsetExp;
    dt.Image.pfnGetProperties = Cal::Client::Icd::LevelZero::zeImageGetProperties;
    if (tracingEnabled) {
        dt.Image.pfnGetProperties = Cal::Client::Icd::LevelZero::zeImageGetProperties_WithTracing;
    }
    dt.Image.pfnCreate = Cal::Client::Icd::LevelZero::zeImageCreate;
    if (tracingEnabled) {
        dt.Image.pfnCreate = Cal::Client::Icd::LevelZero::zeImageCreate_WithTracing;
    }
    dt.Image.pfnDestroy = Cal::Client::Icd::LevelZero::zeImageDestroy;
    if (tracingEnabled) {
        dt.Image.pfnDestroy = Cal::Client::Icd::LevelZero::zeImageDestroy_WithTracing;
    }
    dt.KernelExp.pfnSchedulingHintExp = Cal::Client::Icd::LevelZero::zeKernelSchedulingHintExp;
    dt.Mem.pfnAllocShared = Cal::Client::Icd::LevelZero::zeMemAllocShared;
    if (tracingEnabled) {
        dt.Mem.pfnAllocShared = Cal::Client::Icd::LevelZero::zeMemAllocShared_WithTracing;
    }
    dt.Mem.pfnAllocDevice = Cal::Client::Icd::LevelZero::zeMemAllocDevice;
    if (tracingEnabled) {
        dt.Mem.pfnAllocDevice = Cal::Client::Icd::LevelZero::zeMemAllocDevice_WithTracing;
    }
    dt.Mem.pfnAllocHost = Cal::Client::Icd::LevelZero::zeMemAllocHost;
    if (tracingEnabled) {
        dt.Mem.pfnAllocHost = Cal::Client::Icd::LevelZero::zeMemAllocHost_WithTracing;
    }
    dt.Mem.pfnFree = Cal::Client::Icd::LevelZero::zeMemFree;
    if (tracingEnabled) {
        dt.Mem.pfnFree = Cal::Client::Icd::LevelZero::zeMemFree_WithTracing;
    }
    dt.Mem.pfnGetAllocProperties = Cal::Client::Icd::LevelZero::zeMemGetAllocProperties;
    if (tracingEnabled) {
        dt.Mem.pfnGetAllocProperties = Cal::Client::Icd::LevelZero::zeMemGetAllocProperties_WithTracing;
    }
    dt.Mem.pfnGetAddressRange = Cal::Client::Icd::LevelZero::zeMemGetAddressRange;
    if (tracingEnabled) {
        dt.Mem.pfnGetAddressRange = Cal::Client::Icd::LevelZero::zeMemGetAddressRange_WithTracing;
    }
    dt.Mem.pfnGetIpcHandle = Cal::Client::Icd::LevelZero::zeMemGetIpcHandle;
    if (tracingEnabled) {
        dt.Mem.pfnGetIpcHandle = Cal::Client::Icd::LevelZero::zeMemGetIpcHandle_WithTracing;
    }
    dt.Mem.pfnOpenIpcHandle = Cal::Client::Icd::LevelZero::zeMemOpenIpcHandle;
    if (tracingEnabled) {
        dt.Mem.pfnOpenIpcHandle = Cal::Client::Icd::LevelZero::zeMemOpenIpcHandle_WithTracing;
    }
    dt.Mem.pfnCloseIpcHandle = Cal::Client::Icd::LevelZero::zeMemCloseIpcHandle;
    if (tracingEnabled) {
        dt.Mem.pfnCloseIpcHandle = Cal::Client::Icd::LevelZero::zeMemCloseIpcHandle_WithTracing;
    }
    dt.Mem.pfnFreeExt = Cal::Client::Icd::LevelZero::zeMemFreeExt;
    dt.Module.pfnCreate = Cal::Client::Icd::LevelZero::zeModuleCreate;
    if (tracingEnabled) {
        dt.Module.pfnCreate = Cal::Client::Icd::LevelZero::zeModuleCreate_WithTracing;
    }
    dt.Module.pfnDestroy = Cal::Client::Icd::LevelZero::zeModuleDestroy;
    if (tracingEnabled) {
        dt.Module.pfnDestroy = Cal::Client::Icd::LevelZero::zeModuleDestroy_WithTracing;
    }
    dt.Module.pfnDynamicLink = Cal::Client::Icd::LevelZero::zeModuleDynamicLink;
    if (tracingEnabled) {
        dt.Module.pfnDynamicLink = Cal::Client::Icd::LevelZero::zeModuleDynamicLink_WithTracing;
    }
    dt.ModuleBuildLog.pfnDestroy = Cal::Client::Icd::LevelZero::zeModuleBuildLogDestroy;
    if (tracingEnabled) {
        dt.ModuleBuildLog.pfnDestroy = Cal::Client::Icd::LevelZero::zeModuleBuildLogDestroy_WithTracing;
    }
    dt.ModuleBuildLog.pfnGetString = Cal::Client::Icd::LevelZero::zeModuleBuildLogGetString;
    if (tracingEnabled) {
        dt.ModuleBuildLog.pfnGetString = Cal::Client::Icd::LevelZero::zeModuleBuildLogGetString_WithTracing;
    }
    dt.Module.pfnGetNativeBinary = Cal::Client::Icd::LevelZero::zeModuleGetNativeBinary;
    if (tracingEnabled) {
        dt.Module.pfnGetNativeBinary = Cal::Client::Icd::LevelZero::zeModuleGetNativeBinary_WithTracing;
    }
    dt.Module.pfnGetGlobalPointer = Cal::Client::Icd::LevelZero::zeModuleGetGlobalPointer;
    if (tracingEnabled) {
        dt.Module.pfnGetGlobalPointer = Cal::Client::Icd::LevelZero::zeModuleGetGlobalPointer_WithTracing;
    }
    dt.Module.pfnGetKernelNames = Cal::Client::Icd::LevelZero::zeModuleGetKernelNames;
    if (tracingEnabled) {
        dt.Module.pfnGetKernelNames = Cal::Client::Icd::LevelZero::zeModuleGetKernelNames_WithTracing;
    }
    dt.Module.pfnGetProperties = Cal::Client::Icd::LevelZero::zeModuleGetProperties;
    if (tracingEnabled) {
        dt.Module.pfnGetProperties = Cal::Client::Icd::LevelZero::zeModuleGetProperties_WithTracing;
    }
    dt.Kernel.pfnCreate = Cal::Client::Icd::LevelZero::zeKernelCreate;
    if (tracingEnabled) {
        dt.Kernel.pfnCreate = Cal::Client::Icd::LevelZero::zeKernelCreate_WithTracing;
    }
    dt.Kernel.pfnDestroy = Cal::Client::Icd::LevelZero::zeKernelDestroy;
    if (tracingEnabled) {
        dt.Kernel.pfnDestroy = Cal::Client::Icd::LevelZero::zeKernelDestroy_WithTracing;
    }
    dt.Module.pfnGetFunctionPointer = Cal::Client::Icd::LevelZero::zeModuleGetFunctionPointer;
    if (tracingEnabled) {
        dt.Module.pfnGetFunctionPointer = Cal::Client::Icd::LevelZero::zeModuleGetFunctionPointer_WithTracing;
    }
    dt.Kernel.pfnSetGroupSize = Cal::Client::Icd::LevelZero::zeKernelSetGroupSize;
    if (tracingEnabled) {
        dt.Kernel.pfnSetGroupSize = Cal::Client::Icd::LevelZero::zeKernelSetGroupSize_WithTracing;
    }
    dt.Kernel.pfnSuggestGroupSize = Cal::Client::Icd::LevelZero::zeKernelSuggestGroupSize;
    if (tracingEnabled) {
        dt.Kernel.pfnSuggestGroupSize = Cal::Client::Icd::LevelZero::zeKernelSuggestGroupSize_WithTracing;
    }
    dt.Kernel.pfnSuggestMaxCooperativeGroupCount = Cal::Client::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount;
    if (tracingEnabled) {
        dt.Kernel.pfnSuggestMaxCooperativeGroupCount = Cal::Client::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount_WithTracing;
    }
    dt.Kernel.pfnSetArgumentValue = Cal::Client::Icd::LevelZero::zeKernelSetArgumentValue;
    if (tracingEnabled) {
        dt.Kernel.pfnSetArgumentValue = Cal::Client::Icd::LevelZero::zeKernelSetArgumentValue_WithTracing;
    }
    dt.Kernel.pfnSetIndirectAccess = Cal::Client::Icd::LevelZero::zeKernelSetIndirectAccess;
    if (tracingEnabled) {
        dt.Kernel.pfnSetIndirectAccess = Cal::Client::Icd::LevelZero::zeKernelSetIndirectAccess_WithTracing;
    }
    dt.Kernel.pfnGetIndirectAccess = Cal::Client::Icd::LevelZero::zeKernelGetIndirectAccess;
    if (tracingEnabled) {
        dt.Kernel.pfnGetIndirectAccess = Cal::Client::Icd::LevelZero::zeKernelGetIndirectAccess_WithTracing;
    }
    dt.Kernel.pfnSetCacheConfig = Cal::Client::Icd::LevelZero::zeKernelSetCacheConfig;
    if (tracingEnabled) {
        dt.Kernel.pfnSetCacheConfig = Cal::Client::Icd::LevelZero::zeKernelSetCacheConfig_WithTracing;
    }
    dt.Kernel.pfnGetProperties = Cal::Client::Icd::LevelZero::zeKernelGetProperties;
    if (tracingEnabled) {
        dt.Kernel.pfnGetProperties = Cal::Client::Icd::LevelZero::zeKernelGetProperties_WithTracing;
    }
    dt.Kernel.pfnGetName = Cal::Client::Icd::LevelZero::zeKernelGetName;
    if (tracingEnabled) {
        dt.Kernel.pfnGetName = Cal::Client::Icd::LevelZero::zeKernelGetName_WithTracing;
    }
    dt.CommandList.pfnAppendLaunchKernel = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernel;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendLaunchKernel = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernel_WithTracing;
    }
    dt.CommandList.pfnAppendLaunchCooperativeKernel = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchCooperativeKernel;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendLaunchCooperativeKernel = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchCooperativeKernel_WithTracing;
    }
    dt.CommandList.pfnAppendLaunchKernelIndirect = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendLaunchKernelIndirect = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect_WithTracing;
    }
    dt.CommandList.pfnAppendLaunchMultipleKernelsIndirect = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchMultipleKernelsIndirect;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendLaunchMultipleKernelsIndirect = Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchMultipleKernelsIndirect_WithTracing;
    }
    dt.CommandList.pfnHostSynchronize = Cal::Client::Icd::LevelZero::zeCommandListHostSynchronize;
    dt.Device.pfnPciGetPropertiesExt = Cal::Client::Icd::LevelZero::zeDevicePciGetPropertiesExt;
    dt.Context.pfnMakeMemoryResident = Cal::Client::Icd::LevelZero::zeContextMakeMemoryResident;
    if (tracingEnabled) {
        dt.Context.pfnMakeMemoryResident = Cal::Client::Icd::LevelZero::zeContextMakeMemoryResident_WithTracing;
    }
    dt.Context.pfnEvictMemory = Cal::Client::Icd::LevelZero::zeContextEvictMemory;
    if (tracingEnabled) {
        dt.Context.pfnEvictMemory = Cal::Client::Icd::LevelZero::zeContextEvictMemory_WithTracing;
    }
    dt.VirtualMem.pfnReserve = Cal::Client::Icd::LevelZero::zeVirtualMemReserve;
    if (tracingEnabled) {
        dt.VirtualMem.pfnReserve = Cal::Client::Icd::LevelZero::zeVirtualMemReserve_WithTracing;
    }
    dt.VirtualMem.pfnFree = Cal::Client::Icd::LevelZero::zeVirtualMemFree;
    if (tracingEnabled) {
        dt.VirtualMem.pfnFree = Cal::Client::Icd::LevelZero::zeVirtualMemFree_WithTracing;
    }
    dt.VirtualMem.pfnQueryPageSize = Cal::Client::Icd::LevelZero::zeVirtualMemQueryPageSize;
    if (tracingEnabled) {
        dt.VirtualMem.pfnQueryPageSize = Cal::Client::Icd::LevelZero::zeVirtualMemQueryPageSize_WithTracing;
    }
    dt.PhysicalMem.pfnCreate = Cal::Client::Icd::LevelZero::zePhysicalMemCreate;
    if (tracingEnabled) {
        dt.PhysicalMem.pfnCreate = Cal::Client::Icd::LevelZero::zePhysicalMemCreate_WithTracing;
    }
    dt.PhysicalMem.pfnDestroy = Cal::Client::Icd::LevelZero::zePhysicalMemDestroy;
    if (tracingEnabled) {
        dt.PhysicalMem.pfnDestroy = Cal::Client::Icd::LevelZero::zePhysicalMemDestroy_WithTracing;
    }
    dt.VirtualMem.pfnMap = Cal::Client::Icd::LevelZero::zeVirtualMemMap;
    if (tracingEnabled) {
        dt.VirtualMem.pfnMap = Cal::Client::Icd::LevelZero::zeVirtualMemMap_WithTracing;
    }
    dt.VirtualMem.pfnUnmap = Cal::Client::Icd::LevelZero::zeVirtualMemUnmap;
    if (tracingEnabled) {
        dt.VirtualMem.pfnUnmap = Cal::Client::Icd::LevelZero::zeVirtualMemUnmap_WithTracing;
    }
    dt.VirtualMem.pfnSetAccessAttribute = Cal::Client::Icd::LevelZero::zeVirtualMemSetAccessAttribute;
    if (tracingEnabled) {
        dt.VirtualMem.pfnSetAccessAttribute = Cal::Client::Icd::LevelZero::zeVirtualMemSetAccessAttribute_WithTracing;
    }
    dt.VirtualMem.pfnGetAccessAttribute = Cal::Client::Icd::LevelZero::zeVirtualMemGetAccessAttribute;
    if (tracingEnabled) {
        dt.VirtualMem.pfnGetAccessAttribute = Cal::Client::Icd::LevelZero::zeVirtualMemGetAccessAttribute_WithTracing;
    }
    // below are unimplemented, provided bindings are for easier debugging only
    dt.CommandList.pfnAppendMemoryRangesBarrier = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryRangesBarrier)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryRangesBarrierUnimpl);
    dt.CommandList.pfnAppendMemoryCopyRegion = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryCopyRegion)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryCopyRegionUnimpl);
    dt.CommandList.pfnAppendMemoryCopyFromContext = reinterpret_cast<decltype(dt.CommandList.pfnAppendMemoryCopyFromContext)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendMemoryCopyFromContextUnimpl);
    dt.CommandList.pfnAppendImageCopy = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopy)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyUnimpl);
    dt.CommandList.pfnAppendImageCopyRegion = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyRegion)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyRegionUnimpl);
    dt.CommandList.pfnAppendImageCopyToMemory = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemory)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemory = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemory)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryUnimpl);
    dt.FabricVertexExp.pfnGetExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricVertexGetExpUnimpl);
    dt.FabricVertexExp.pfnGetSubVerticesExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetSubVerticesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricVertexGetSubVerticesExpUnimpl);
    dt.FabricVertexExp.pfnGetPropertiesExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetPropertiesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricVertexGetPropertiesExpUnimpl);
    dt.FabricVertexExp.pfnGetDeviceExp = reinterpret_cast<decltype(dt.FabricVertexExp.pfnGetDeviceExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricVertexGetDeviceExpUnimpl);
    dt.DeviceExp.pfnGetFabricVertexExp = reinterpret_cast<decltype(dt.DeviceExp.pfnGetFabricVertexExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeDeviceGetFabricVertexExpUnimpl);
    dt.FabricEdgeExp.pfnGetExp = reinterpret_cast<decltype(dt.FabricEdgeExp.pfnGetExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricEdgeGetExpUnimpl);
    dt.FabricEdgeExp.pfnGetVerticesExp = reinterpret_cast<decltype(dt.FabricEdgeExp.pfnGetVerticesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricEdgeGetVerticesExpUnimpl);
    dt.FabricEdgeExp.pfnGetPropertiesExp = reinterpret_cast<decltype(dt.FabricEdgeExp.pfnGetPropertiesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeFabricEdgeGetPropertiesExpUnimpl);
    dt.CommandList.pfnAppendImageCopyToMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemoryExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryExtUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemoryExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryExtUnimpl);
    dt.ImageExp.pfnGetMemoryPropertiesExp = reinterpret_cast<decltype(dt.ImageExp.pfnGetMemoryPropertiesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeImageGetMemoryPropertiesExpUnimpl);
    dt.Image.pfnGetAllocPropertiesExt = reinterpret_cast<decltype(dt.Image.pfnGetAllocPropertiesExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeImageGetAllocPropertiesExtUnimpl);
    dt.ImageExp.pfnViewCreateExp = reinterpret_cast<decltype(dt.ImageExp.pfnViewCreateExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeImageViewCreateExpUnimpl);
    dt.Module.pfnInspectLinkageExt = reinterpret_cast<decltype(dt.Module.pfnInspectLinkageExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeModuleInspectLinkageExtUnimpl);
    dt.Kernel.pfnGetSourceAttributes = reinterpret_cast<decltype(dt.Kernel.pfnGetSourceAttributes)>(Cal::Client::Icd::LevelZero::Unimplemented::zeKernelGetSourceAttributesUnimpl);
    dt.Context.pfnMakeImageResident = reinterpret_cast<decltype(dt.Context.pfnMakeImageResident)>(Cal::Client::Icd::LevelZero::Unimplemented::zeContextMakeImageResidentUnimpl);
    dt.Context.pfnEvictImage = reinterpret_cast<decltype(dt.Context.pfnEvictImage)>(Cal::Client::Icd::LevelZero::Unimplemented::zeContextEvictImageUnimpl);
    dt.Sampler.pfnCreate = reinterpret_cast<decltype(dt.Sampler.pfnCreate)>(Cal::Client::Icd::LevelZero::Unimplemented::zeSamplerCreateUnimpl);
    dt.Sampler.pfnDestroy = reinterpret_cast<decltype(dt.Sampler.pfnDestroy)>(Cal::Client::Icd::LevelZero::Unimplemented::zeSamplerDestroyUnimpl);
}
inline void initL0SysmanDdi(zes_dditable_t &dt){
    dt.Device.pfnReset = Cal::Client::Icd::LevelZero::zesDeviceReset;
    dt.Device.pfnResetExt = Cal::Client::Icd::LevelZero::zesDeviceResetExt;
    dt.Device.pfnEnumPowerDomains = Cal::Client::Icd::LevelZero::zesDeviceEnumPowerDomains;
    dt.Device.pfnGetCardPowerDomain = Cal::Client::Icd::LevelZero::zesDeviceGetCardPowerDomain;
    dt.Power.pfnGetProperties = Cal::Client::Icd::LevelZero::zesPowerGetProperties;
    dt.Power.pfnGetEnergyCounter = Cal::Client::Icd::LevelZero::zesPowerGetEnergyCounter;
    dt.Power.pfnGetLimits = Cal::Client::Icd::LevelZero::zesPowerGetLimits;
    dt.Power.pfnSetLimits = Cal::Client::Icd::LevelZero::zesPowerSetLimits;
    dt.Power.pfnGetEnergyThreshold = Cal::Client::Icd::LevelZero::zesPowerGetEnergyThreshold;
    dt.Power.pfnSetEnergyThreshold = Cal::Client::Icd::LevelZero::zesPowerSetEnergyThreshold;
    dt.Device.pfnEnumEngineGroups = Cal::Client::Icd::LevelZero::zesDeviceEnumEngineGroups;
    dt.Engine.pfnGetProperties = Cal::Client::Icd::LevelZero::zesEngineGetProperties;
    dt.Engine.pfnGetActivity = Cal::Client::Icd::LevelZero::zesEngineGetActivity;
    dt.Device.pfnGetState = Cal::Client::Icd::LevelZero::zesDeviceGetState;
    dt.Device.pfnProcessesGetState = Cal::Client::Icd::LevelZero::zesDeviceProcessesGetState;
    dt.Device.pfnPciGetProperties = Cal::Client::Icd::LevelZero::zesDevicePciGetProperties;
    dt.Device.pfnPciGetState = Cal::Client::Icd::LevelZero::zesDevicePciGetState;
    dt.Device.pfnPciGetBars = Cal::Client::Icd::LevelZero::zesDevicePciGetBars;
    dt.Device.pfnPciGetStats = Cal::Client::Icd::LevelZero::zesDevicePciGetStats;
    dt.Device.pfnGetProperties = Cal::Client::Icd::LevelZero::zesDeviceGetProperties;
    dt.Device.pfnEnumMemoryModules = Cal::Client::Icd::LevelZero::zesDeviceEnumMemoryModules;
    // below are unimplemented, provided bindings are for easier debugging only
    dt.Device.pfnEnumRasErrorSets = reinterpret_cast<decltype(dt.Device.pfnEnumRasErrorSets)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumRasErrorSetsUnimpl);
    dt.Ras.pfnGetProperties = reinterpret_cast<decltype(dt.Ras.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesRasGetPropertiesUnimpl);
    dt.Ras.pfnGetConfig = reinterpret_cast<decltype(dt.Ras.pfnGetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesRasGetConfigUnimpl);
    dt.Ras.pfnSetConfig = reinterpret_cast<decltype(dt.Ras.pfnSetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesRasSetConfigUnimpl);
    dt.Ras.pfnGetState = reinterpret_cast<decltype(dt.Ras.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesRasGetStateUnimpl);
    dt.Device.pfnEnumFans = reinterpret_cast<decltype(dt.Device.pfnEnumFans)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumFansUnimpl);
    dt.Fan.pfnGetProperties = reinterpret_cast<decltype(dt.Fan.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFanGetPropertiesUnimpl);
    dt.Fan.pfnGetConfig = reinterpret_cast<decltype(dt.Fan.pfnGetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFanGetConfigUnimpl);
    dt.Fan.pfnSetDefaultMode = reinterpret_cast<decltype(dt.Fan.pfnSetDefaultMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFanSetDefaultModeUnimpl);
    dt.Fan.pfnSetFixedSpeedMode = reinterpret_cast<decltype(dt.Fan.pfnSetFixedSpeedMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFanSetFixedSpeedModeUnimpl);
    dt.Fan.pfnSetSpeedTableMode = reinterpret_cast<decltype(dt.Fan.pfnSetSpeedTableMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFanSetSpeedTableModeUnimpl);
    dt.Fan.pfnGetState = reinterpret_cast<decltype(dt.Fan.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFanGetStateUnimpl);
    dt.Device.pfnEnumFirmwares = reinterpret_cast<decltype(dt.Device.pfnEnumFirmwares)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumFirmwaresUnimpl);
    dt.Firmware.pfnGetProperties = reinterpret_cast<decltype(dt.Firmware.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFirmwareGetPropertiesUnimpl);
    dt.Firmware.pfnFlash = reinterpret_cast<decltype(dt.Firmware.pfnFlash)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFirmwareFlashUnimpl);
    dt.Power.pfnGetLimitsExt = reinterpret_cast<decltype(dt.Power.pfnGetLimitsExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPowerGetLimitsExtUnimpl);
    dt.Power.pfnSetLimitsExt = reinterpret_cast<decltype(dt.Power.pfnSetLimitsExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPowerSetLimitsExtUnimpl);
    dt.Device.pfnEnumStandbyDomains = reinterpret_cast<decltype(dt.Device.pfnEnumStandbyDomains)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumStandbyDomainsUnimpl);
    dt.Standby.pfnGetProperties = reinterpret_cast<decltype(dt.Standby.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesStandbyGetPropertiesUnimpl);
    dt.Standby.pfnGetMode = reinterpret_cast<decltype(dt.Standby.pfnGetMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesStandbyGetModeUnimpl);
    dt.Standby.pfnSetMode = reinterpret_cast<decltype(dt.Standby.pfnSetMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesStandbySetModeUnimpl);
    dt.Device.pfnEnumTemperatureSensors = reinterpret_cast<decltype(dt.Device.pfnEnumTemperatureSensors)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumTemperatureSensorsUnimpl);
    dt.Temperature.pfnGetProperties = reinterpret_cast<decltype(dt.Temperature.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesTemperatureGetPropertiesUnimpl);
    dt.Temperature.pfnGetConfig = reinterpret_cast<decltype(dt.Temperature.pfnGetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesTemperatureGetConfigUnimpl);
    dt.Temperature.pfnSetConfig = reinterpret_cast<decltype(dt.Temperature.pfnSetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesTemperatureSetConfigUnimpl);
    dt.Temperature.pfnGetState = reinterpret_cast<decltype(dt.Temperature.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesTemperatureGetStateUnimpl);
    dt.Device.pfnEccAvailable = reinterpret_cast<decltype(dt.Device.pfnEccAvailable)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEccAvailableUnimpl);
    dt.Device.pfnEccConfigurable = reinterpret_cast<decltype(dt.Device.pfnEccConfigurable)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEccConfigurableUnimpl);
    dt.Device.pfnGetEccState = reinterpret_cast<decltype(dt.Device.pfnGetEccState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceGetEccStateUnimpl);
    dt.Device.pfnSetEccState = reinterpret_cast<decltype(dt.Device.pfnSetEccState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceSetEccStateUnimpl);
    dt.Device.pfnEnumSchedulers = reinterpret_cast<decltype(dt.Device.pfnEnumSchedulers)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumSchedulersUnimpl);
    dt.Scheduler.pfnGetProperties = reinterpret_cast<decltype(dt.Scheduler.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerGetPropertiesUnimpl);
    dt.Scheduler.pfnGetCurrentMode = reinterpret_cast<decltype(dt.Scheduler.pfnGetCurrentMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerGetCurrentModeUnimpl);
    dt.Scheduler.pfnGetTimeoutModeProperties = reinterpret_cast<decltype(dt.Scheduler.pfnGetTimeoutModeProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerGetTimeoutModePropertiesUnimpl);
    dt.Scheduler.pfnGetTimesliceModeProperties = reinterpret_cast<decltype(dt.Scheduler.pfnGetTimesliceModeProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerGetTimesliceModePropertiesUnimpl);
    dt.Scheduler.pfnSetTimeoutMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetTimeoutMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerSetTimeoutModeUnimpl);
    dt.Scheduler.pfnSetTimesliceMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetTimesliceMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerSetTimesliceModeUnimpl);
    dt.Scheduler.pfnSetExclusiveMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetExclusiveMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerSetExclusiveModeUnimpl);
    dt.Scheduler.pfnSetComputeUnitDebugMode = reinterpret_cast<decltype(dt.Scheduler.pfnSetComputeUnitDebugMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesSchedulerSetComputeUnitDebugModeUnimpl);
    dt.Memory.pfnGetProperties = reinterpret_cast<decltype(dt.Memory.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesMemoryGetPropertiesUnimpl);
    dt.Memory.pfnGetState = reinterpret_cast<decltype(dt.Memory.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesMemoryGetStateUnimpl);
    dt.Memory.pfnGetBandwidth = reinterpret_cast<decltype(dt.Memory.pfnGetBandwidth)>(Cal::Client::Icd::LevelZero::Unimplemented::zesMemoryGetBandwidthUnimpl);
    dt.Device.pfnEnumPerformanceFactorDomains = reinterpret_cast<decltype(dt.Device.pfnEnumPerformanceFactorDomains)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumPerformanceFactorDomainsUnimpl);
    dt.PerformanceFactor.pfnGetProperties = reinterpret_cast<decltype(dt.PerformanceFactor.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPerformanceFactorGetPropertiesUnimpl);
    dt.PerformanceFactor.pfnGetConfig = reinterpret_cast<decltype(dt.PerformanceFactor.pfnGetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPerformanceFactorGetConfigUnimpl);
    dt.PerformanceFactor.pfnSetConfig = reinterpret_cast<decltype(dt.PerformanceFactor.pfnSetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPerformanceFactorSetConfigUnimpl);
    dt.Device.pfnEnumLeds = reinterpret_cast<decltype(dt.Device.pfnEnumLeds)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumLedsUnimpl);
    dt.Led.pfnGetProperties = reinterpret_cast<decltype(dt.Led.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesLedGetPropertiesUnimpl);
    dt.Led.pfnGetState = reinterpret_cast<decltype(dt.Led.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesLedGetStateUnimpl);
    dt.Led.pfnSetState = reinterpret_cast<decltype(dt.Led.pfnSetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesLedSetStateUnimpl);
    dt.Led.pfnSetColor = reinterpret_cast<decltype(dt.Led.pfnSetColor)>(Cal::Client::Icd::LevelZero::Unimplemented::zesLedSetColorUnimpl);
    dt.Device.pfnEnumFabricPorts = reinterpret_cast<decltype(dt.Device.pfnEnumFabricPorts)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumFabricPortsUnimpl);
    dt.FabricPort.pfnGetProperties = reinterpret_cast<decltype(dt.FabricPort.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFabricPortGetPropertiesUnimpl);
    dt.FabricPort.pfnGetLinkType = reinterpret_cast<decltype(dt.FabricPort.pfnGetLinkType)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFabricPortGetLinkTypeUnimpl);
    dt.FabricPort.pfnGetConfig = reinterpret_cast<decltype(dt.FabricPort.pfnGetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFabricPortGetConfigUnimpl);
    dt.FabricPort.pfnSetConfig = reinterpret_cast<decltype(dt.FabricPort.pfnSetConfig)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFabricPortSetConfigUnimpl);
    dt.FabricPort.pfnGetState = reinterpret_cast<decltype(dt.FabricPort.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFabricPortGetStateUnimpl);
    dt.FabricPort.pfnGetThroughput = reinterpret_cast<decltype(dt.FabricPort.pfnGetThroughput)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFabricPortGetThroughputUnimpl);
    dt.Device.pfnEventRegister = reinterpret_cast<decltype(dt.Device.pfnEventRegister)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEventRegisterUnimpl);
    dt.Driver.pfnEventListen = reinterpret_cast<decltype(dt.Driver.pfnEventListen)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDriverEventListenUnimpl);
    dt.Driver.pfnEventListenEx = reinterpret_cast<decltype(dt.Driver.pfnEventListenEx)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDriverEventListenExUnimpl);
    dt.Device.pfnEnumDiagnosticTestSuites = reinterpret_cast<decltype(dt.Device.pfnEnumDiagnosticTestSuites)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumDiagnosticTestSuitesUnimpl);
    dt.Diagnostics.pfnGetProperties = reinterpret_cast<decltype(dt.Diagnostics.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDiagnosticsGetPropertiesUnimpl);
    dt.Diagnostics.pfnGetTests = reinterpret_cast<decltype(dt.Diagnostics.pfnGetTests)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDiagnosticsGetTestsUnimpl);
    dt.Diagnostics.pfnRunTests = reinterpret_cast<decltype(dt.Diagnostics.pfnRunTests)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDiagnosticsRunTestsUnimpl);
    dt.Device.pfnEnumPsus = reinterpret_cast<decltype(dt.Device.pfnEnumPsus)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumPsusUnimpl);
    dt.Psu.pfnGetProperties = reinterpret_cast<decltype(dt.Psu.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPsuGetPropertiesUnimpl);
    dt.Psu.pfnGetState = reinterpret_cast<decltype(dt.Psu.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPsuGetStateUnimpl);
    dt.Device.pfnEnumFrequencyDomains = reinterpret_cast<decltype(dt.Device.pfnEnumFrequencyDomains)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumFrequencyDomainsUnimpl);
    dt.Frequency.pfnGetProperties = reinterpret_cast<decltype(dt.Frequency.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyGetPropertiesUnimpl);
    dt.Frequency.pfnGetAvailableClocks = reinterpret_cast<decltype(dt.Frequency.pfnGetAvailableClocks)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyGetAvailableClocksUnimpl);
    dt.Frequency.pfnGetRange = reinterpret_cast<decltype(dt.Frequency.pfnGetRange)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyGetRangeUnimpl);
    dt.Frequency.pfnSetRange = reinterpret_cast<decltype(dt.Frequency.pfnSetRange)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencySetRangeUnimpl);
    dt.Frequency.pfnGetState = reinterpret_cast<decltype(dt.Frequency.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyGetStateUnimpl);
    dt.Frequency.pfnGetThrottleTime = reinterpret_cast<decltype(dt.Frequency.pfnGetThrottleTime)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyGetThrottleTimeUnimpl);
    dt.Frequency.pfnOcGetCapabilities = reinterpret_cast<decltype(dt.Frequency.pfnOcGetCapabilities)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcGetCapabilitiesUnimpl);
    dt.Frequency.pfnOcGetVoltageTarget = reinterpret_cast<decltype(dt.Frequency.pfnOcGetVoltageTarget)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcGetVoltageTargetUnimpl);
    dt.Frequency.pfnOcSetVoltageTarget = reinterpret_cast<decltype(dt.Frequency.pfnOcSetVoltageTarget)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcSetVoltageTargetUnimpl);
    dt.Frequency.pfnOcSetMode = reinterpret_cast<decltype(dt.Frequency.pfnOcSetMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcSetModeUnimpl);
    dt.Frequency.pfnOcGetMode = reinterpret_cast<decltype(dt.Frequency.pfnOcGetMode)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcGetModeUnimpl);
    dt.Frequency.pfnOcGetIccMax = reinterpret_cast<decltype(dt.Frequency.pfnOcGetIccMax)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcGetIccMaxUnimpl);
    dt.Frequency.pfnOcSetIccMax = reinterpret_cast<decltype(dt.Frequency.pfnOcSetIccMax)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcSetIccMaxUnimpl);
    dt.Frequency.pfnOcGetTjMax = reinterpret_cast<decltype(dt.Frequency.pfnOcGetTjMax)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcGetTjMaxUnimpl);
    dt.Frequency.pfnOcSetTjMax = reinterpret_cast<decltype(dt.Frequency.pfnOcSetTjMax)>(Cal::Client::Icd::LevelZero::Unimplemented::zesFrequencyOcSetTjMaxUnimpl);
}
inline void initL0ToolsDdi(zet_dditable_t &dt){
    dt.TracerExp.pfnCreate = Cal::Client::Icd::LevelZero::zetTracerExpCreate;
    dt.TracerExp.pfnDestroy = Cal::Client::Icd::LevelZero::zetTracerExpDestroy;
    dt.TracerExp.pfnSetPrologues = Cal::Client::Icd::LevelZero::zetTracerExpSetPrologues;
    dt.TracerExp.pfnSetEpilogues = Cal::Client::Icd::LevelZero::zetTracerExpSetEpilogues;
    dt.TracerExp.pfnSetEnabled = Cal::Client::Icd::LevelZero::zetTracerExpSetEnabled;
    // below are unimplemented, provided bindings are for easier debugging only
    dt.Kernel.pfnGetProfileInfo = reinterpret_cast<decltype(dt.Kernel.pfnGetProfileInfo)>(Cal::Client::Icd::LevelZero::Unimplemented::zetKernelGetProfileInfoUnimpl);
    dt.MetricGroupExp.pfnCalculateMultipleMetricValuesExp = reinterpret_cast<decltype(dt.MetricGroupExp.pfnCalculateMultipleMetricValuesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricGroupCalculateMultipleMetricValuesExpUnimpl);
    dt.Device.pfnGetDebugProperties = reinterpret_cast<decltype(dt.Device.pfnGetDebugProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDeviceGetDebugPropertiesUnimpl);
    dt.Debug.pfnAttach = reinterpret_cast<decltype(dt.Debug.pfnAttach)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugAttachUnimpl);
    dt.Debug.pfnDetach = reinterpret_cast<decltype(dt.Debug.pfnDetach)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugDetachUnimpl);
    dt.Debug.pfnReadEvent = reinterpret_cast<decltype(dt.Debug.pfnReadEvent)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugReadEventUnimpl);
    dt.Debug.pfnAcknowledgeEvent = reinterpret_cast<decltype(dt.Debug.pfnAcknowledgeEvent)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugAcknowledgeEventUnimpl);
    dt.Debug.pfnInterrupt = reinterpret_cast<decltype(dt.Debug.pfnInterrupt)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugInterruptUnimpl);
    dt.Debug.pfnResume = reinterpret_cast<decltype(dt.Debug.pfnResume)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugResumeUnimpl);
    dt.Debug.pfnReadMemory = reinterpret_cast<decltype(dt.Debug.pfnReadMemory)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugReadMemoryUnimpl);
    dt.Debug.pfnWriteMemory = reinterpret_cast<decltype(dt.Debug.pfnWriteMemory)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugWriteMemoryUnimpl);
    dt.Debug.pfnGetRegisterSetProperties = reinterpret_cast<decltype(dt.Debug.pfnGetRegisterSetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugGetRegisterSetPropertiesUnimpl);
    dt.Debug.pfnReadRegisters = reinterpret_cast<decltype(dt.Debug.pfnReadRegisters)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugReadRegistersUnimpl);
    dt.Debug.pfnWriteRegisters = reinterpret_cast<decltype(dt.Debug.pfnWriteRegisters)>(Cal::Client::Icd::LevelZero::Unimplemented::zetDebugWriteRegistersUnimpl);
    dt.Module.pfnGetDebugInfo = reinterpret_cast<decltype(dt.Module.pfnGetDebugInfo)>(Cal::Client::Icd::LevelZero::Unimplemented::zetModuleGetDebugInfoUnimpl);
    dt.MetricGroup.pfnGet = reinterpret_cast<decltype(dt.MetricGroup.pfnGet)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricGroupGetUnimpl);
    dt.MetricGroup.pfnGetProperties = reinterpret_cast<decltype(dt.MetricGroup.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricGroupGetPropertiesUnimpl);
    dt.MetricGroup.pfnCalculateMetricValues = reinterpret_cast<decltype(dt.MetricGroup.pfnCalculateMetricValues)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricGroupCalculateMetricValuesUnimpl);
    dt.Metric.pfnGet = reinterpret_cast<decltype(dt.Metric.pfnGet)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricGetUnimpl);
    dt.Metric.pfnGetProperties = reinterpret_cast<decltype(dt.Metric.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricGetPropertiesUnimpl);
    dt.Context.pfnActivateMetricGroups = reinterpret_cast<decltype(dt.Context.pfnActivateMetricGroups)>(Cal::Client::Icd::LevelZero::Unimplemented::zetContextActivateMetricGroupsUnimpl);
    dt.MetricStreamer.pfnOpen = reinterpret_cast<decltype(dt.MetricStreamer.pfnOpen)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricStreamerOpenUnimpl);
    dt.CommandList.pfnAppendMetricStreamerMarker = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricStreamerMarker)>(Cal::Client::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricStreamerMarkerUnimpl);
    dt.MetricStreamer.pfnClose = reinterpret_cast<decltype(dt.MetricStreamer.pfnClose)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricStreamerCloseUnimpl);
    dt.MetricStreamer.pfnReadData = reinterpret_cast<decltype(dt.MetricStreamer.pfnReadData)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricStreamerReadDataUnimpl);
    dt.MetricQueryPool.pfnCreate = reinterpret_cast<decltype(dt.MetricQueryPool.pfnCreate)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricQueryPoolCreateUnimpl);
    dt.MetricQueryPool.pfnDestroy = reinterpret_cast<decltype(dt.MetricQueryPool.pfnDestroy)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricQueryPoolDestroyUnimpl);
    dt.MetricQuery.pfnCreate = reinterpret_cast<decltype(dt.MetricQuery.pfnCreate)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricQueryCreateUnimpl);
    dt.MetricQuery.pfnDestroy = reinterpret_cast<decltype(dt.MetricQuery.pfnDestroy)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricQueryDestroyUnimpl);
    dt.MetricQuery.pfnReset = reinterpret_cast<decltype(dt.MetricQuery.pfnReset)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricQueryResetUnimpl);
    dt.CommandList.pfnAppendMetricQueryBegin = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricQueryBegin)>(Cal::Client::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricQueryBeginUnimpl);
    dt.CommandList.pfnAppendMetricQueryEnd = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricQueryEnd)>(Cal::Client::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricQueryEndUnimpl);
    dt.CommandList.pfnAppendMetricMemoryBarrier = reinterpret_cast<decltype(dt.CommandList.pfnAppendMetricMemoryBarrier)>(Cal::Client::Icd::LevelZero::Unimplemented::zetCommandListAppendMetricMemoryBarrierUnimpl);
    dt.MetricQuery.pfnGetData = reinterpret_cast<decltype(dt.MetricQuery.pfnGetData)>(Cal::Client::Icd::LevelZero::Unimplemented::zetMetricQueryGetDataUnimpl);
}

void *getL0ExtensionFuncionAddressRpcHelper(const char *funcName);
} // namespace LevelZero
} // namespace Icd
} // namespace Client
} // namespace Cal
// #### Generated code -- end ####
