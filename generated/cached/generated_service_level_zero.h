/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####

#include "service/service.h"
#include "shared/rpc.h"
#include "shared/utils.h"

#include "generated_rpc_messages_level_zero.h"

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

namespace Cal {
namespace Service {
namespace Apis {
namespace LevelZero {

namespace Standard {
bool loadLevelZeroLibrary(std::optional<std::string> path);
void unloadLevelZeroLibrary();
bool isLevelZeroLibraryLoaded();

extern ze_result_t (*zetTracerExpCreate)(zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer);
extern ze_result_t (*zetTracerExpDestroy)(zet_tracer_exp_handle_t hTracer);
extern ze_result_t (*zetTracerExpSetPrologues)(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs);
extern ze_result_t (*zetTracerExpSetEpilogues)(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs);
extern ze_result_t (*zetTracerExpSetEnabled)(zet_tracer_exp_handle_t hTracer, ze_bool_t enable);
extern ze_result_t (*zesDeviceReset)(zes_device_handle_t hDevice, ze_bool_t force);
extern ze_result_t (*zesDeviceResetExt)(zes_device_handle_t hDevice, zes_reset_properties_t* pProperties);
extern ze_result_t (*zesDeviceEnumPowerDomains)(zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower);
extern ze_result_t (*zesDeviceGetCardPowerDomain)(zes_device_handle_t hDevice, zes_pwr_handle_t* phPower);
extern ze_result_t (*zesPowerGetProperties)(zes_pwr_handle_t hPower, zes_power_properties_t* pProperties);
extern ze_result_t (*zesPowerGetEnergyCounter)(zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy);
extern ze_result_t (*zesPowerGetLimits)(zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak);
extern ze_result_t (*zesPowerSetLimits)(zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak);
extern ze_result_t (*zesPowerGetLimitsExt)(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained);
extern ze_result_t (*zesPowerSetLimitsExt)(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained);
extern ze_result_t (*zesPowerGetEnergyThreshold)(zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold);
extern ze_result_t (*zesPowerSetEnergyThreshold)(zes_pwr_handle_t hPower, double pThreshold);
extern ze_result_t (*zesDeviceEventRegister)(zes_device_handle_t hDevice, zes_event_type_flags_t events);
extern ze_result_t (*zesDriverEventListen)(ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents);
extern ze_result_t (*zesDriverEventListenEx)(ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents);
extern ze_result_t (*zesDeviceEnumTemperatureSensors)(zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature);
extern ze_result_t (*zesTemperatureGetProperties)(zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties);
extern ze_result_t (*zesTemperatureGetConfig)(zes_temp_handle_t hTemperature, zes_temp_config_t * pConfig);
extern ze_result_t (*zesTemperatureSetConfig)(zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig);
extern ze_result_t (*zesTemperatureGetState)(zes_temp_handle_t hTemperature, double* pTemperature);
extern ze_result_t (*zesDeviceEnumRasErrorSets)(zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas);
extern ze_result_t (*zesRasGetProperties)(zes_ras_handle_t hRas, zes_ras_properties_t* pProperties);
extern ze_result_t (*zesRasGetConfig)(zes_ras_handle_t hRas, zes_ras_config_t * pConfig);
extern ze_result_t (*zesRasSetConfig)(zes_ras_handle_t hRas, const zes_ras_config_t* pConfig);
extern ze_result_t (*zesRasGetState)(zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState);
extern ze_result_t (*zesDeviceEnumFrequencyDomains)(zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency);
extern ze_result_t (*zesFrequencyGetProperties)(zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties);
extern ze_result_t (*zesFrequencyGetAvailableClocks)(zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency);
extern ze_result_t (*zesFrequencyGetRange)(zes_freq_handle_t hFrequency, zes_freq_range_t* pConfig);
extern ze_result_t (*zesFrequencySetRange)(zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits);
extern ze_result_t (*zesFrequencyGetState)(zes_freq_handle_t hFrequency, zes_freq_state_t* pState);
extern ze_result_t (*zesFrequencyGetThrottleTime)(zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime);
extern ze_result_t (*zesFrequencyOcGetCapabilities)(zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities);
extern ze_result_t (*zesFrequencyOcGetVoltageTarget)(zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset);
extern ze_result_t (*zesFrequencyOcSetVoltageTarget)(zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset);
extern ze_result_t (*zesFrequencyOcSetMode)(zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode);
extern ze_result_t (*zesFrequencyOcGetMode)(zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode);
extern ze_result_t (*zesFrequencyOcGetIccMax)(zes_freq_handle_t hFrequency, double* pOcIccMax);
extern ze_result_t (*zesFrequencyOcSetIccMax)(zes_freq_handle_t hFrequency, double ocIccMax);
extern ze_result_t (*zesFrequencyOcGetTjMax)(zes_freq_handle_t hFrequency, double* pOcTjMax);
extern ze_result_t (*zesFrequencyOcSetTjMax)(zes_freq_handle_t hFrequency, double ocTjMax);
extern ze_result_t (*zesDeviceEnumEngineGroups)(zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine);
extern ze_result_t (*zesDeviceEnumSchedulers)(zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler);
extern ze_result_t (*zesSchedulerGetProperties)(zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties);
extern ze_result_t (*zesSchedulerGetCurrentMode)(zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode);
extern ze_result_t (*zesSchedulerGetTimeoutModeProperties)(zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig);
extern ze_result_t (*zesSchedulerGetTimesliceModeProperties)(zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig);
extern ze_result_t (*zesSchedulerSetTimeoutMode)(zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload);
extern ze_result_t (*zesSchedulerSetTimesliceMode)(zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload);
extern ze_result_t (*zesSchedulerSetExclusiveMode)(zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload);
extern ze_result_t (*zesSchedulerSetComputeUnitDebugMode)(zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload);
extern ze_result_t (*zesEngineGetProperties)(zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties);
extern ze_result_t (*zesEngineGetActivity)(zes_engine_handle_t hEngine, zes_engine_stats_t* pStats);
extern ze_result_t (*zesDeviceGetState)(zes_device_handle_t hDevice, zes_device_state_t* pState);
extern ze_result_t (*zesDeviceProcessesGetState)(zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses);
extern ze_result_t (*zesDevicePciGetProperties)(zes_device_handle_t hDevice, zes_pci_properties_t* pProperties);
extern ze_result_t (*zesDevicePciGetState)(zes_device_handle_t hDevice, zes_pci_state_t* pState);
extern ze_result_t (*zesDevicePciGetBars)(zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties);
extern ze_result_t (*zesDevicePciGetStats)(zes_device_handle_t hDevice, zes_pci_stats_t* pStats);
extern ze_result_t (*zesDeviceGetProperties)(zes_device_handle_t hDevice, zes_device_properties_t* pProperties);
extern ze_result_t (*zesDeviceEnumMemoryModules)(zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory);
extern ze_result_t (*zeInit)(ze_init_flags_t flags);
extern ze_result_t (*zeCommandListAppendMemoryRangesBarrier)(ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeContextSystemBarrier)(ze_context_handle_t hContext, ze_device_handle_t hDevice);
extern ze_result_t (*zeCommandListCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList);
extern ze_result_t (*zeCommandListCreateImmediate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList);
extern ze_result_t (*zeCommandListDestroy)(ze_command_list_handle_t hCommandList);
extern ze_result_t (*zeCommandListClose)(ze_command_list_handle_t hCommandList);
extern ze_result_t (*zeCommandListReset)(ze_command_list_handle_t hCommandList);
extern ze_result_t (*zeCommandListAppendWriteGlobalTimestamp)(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandQueueCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
extern ze_result_t (*zeCommandQueueDestroy)(ze_command_queue_handle_t hCommandQueue);
extern ze_result_t (*zeCommandQueueExecuteCommandLists)(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
extern ze_result_t (*zeCommandQueueSynchronize)(ze_command_queue_handle_t hCommandQueue, uint64_t timeout);
extern ze_result_t (*zeContextCreate)(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext);
extern ze_result_t (*zeContextCreateEx)(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext);
extern ze_result_t (*zeContextDestroy)(ze_context_handle_t hContext);
extern ze_result_t (*zeContextGetStatus)(ze_context_handle_t hContext);
extern ze_result_t (*zeCommandListAppendMemoryCopy)(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendMemoryFill)(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendMemoryPrefetch)(ze_command_list_handle_t hCommandList, const void* ptr, size_t size);
extern ze_result_t (*zeCommandListAppendMemAdvise)(ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice);
extern ze_result_t (*zeDeviceGet)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
extern ze_result_t (*zeDeviceGetSubDevices)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
extern ze_result_t (*zeDeviceGetProperties)(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties);
extern ze_result_t (*zeDeviceGetComputeProperties)(ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties);
extern ze_result_t (*zeDeviceGetModuleProperties)(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties);
extern ze_result_t (*zeDeviceGetCommandQueueGroupProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
extern ze_result_t (*zeDeviceGetMemoryProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
extern ze_result_t (*zeDeviceGetMemoryAccessProperties)(ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties);
extern ze_result_t (*zeDeviceGetCacheProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
extern ze_result_t (*zeDeviceGetImageProperties)(ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties);
extern ze_result_t (*zeDeviceGetExternalMemoryProperties)(ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties);
extern ze_result_t (*zeDeviceGetP2PProperties)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties);
extern ze_result_t (*zeDeviceCanAccessPeer)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value);
extern ze_result_t (*zeDeviceGetStatus)(ze_device_handle_t hDevice);
extern ze_result_t (*zeDeviceGetGlobalTimestamps)(ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp);
extern ze_result_t (*zeDeviceReserveCacheExt)(ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize);
extern ze_result_t (*zeDeviceSetCacheAdviceExt)(ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion);
extern ze_result_t (*zeDriverGet)(uint32_t* pCount, ze_driver_handle_t* phDrivers);
extern ze_result_t (*zeDriverGetApiVersion)(ze_driver_handle_t hDriver, ze_api_version_t* version);
extern ze_result_t (*zeDriverGetProperties)(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties);
extern ze_result_t (*zeDriverGetIpcProperties)(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties);
extern ze_result_t (*zeDriverGetExtensionProperties)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
extern ze_result_t (*zeDriverGetExtensionFunctionAddress)(ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress);
extern ze_result_t (*zeEventPoolCreate)(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
extern ze_result_t (*zeEventPoolDestroy)(ze_event_pool_handle_t hEventPool);
extern ze_result_t (*zeEventCreate)(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent);
extern ze_result_t (*zeEventDestroy)(ze_event_handle_t hEvent);
extern ze_result_t (*zeEventPoolGetIpcHandle)(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc);
extern ze_result_t (*zeEventPoolOpenIpcHandle)(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool);
extern ze_result_t (*zeEventPoolCloseIpcHandle)(ze_event_pool_handle_t hEventPool);
extern ze_result_t (*zeCommandListAppendBarrier)(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendSignalEvent)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
extern ze_result_t (*zeCommandListAppendWaitOnEvents)(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
extern ze_result_t (*zeEventHostSignal)(ze_event_handle_t hEvent);
extern ze_result_t (*zeEventHostSynchronize)(ze_event_handle_t hEvent, uint64_t timeout);
extern ze_result_t (*zeEventQueryStatus)(ze_event_handle_t hEvent);
extern ze_result_t (*zeCommandListAppendEventReset)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
extern ze_result_t (*zeEventHostReset)(ze_event_handle_t hEvent);
extern ze_result_t (*zeEventQueryKernelTimestamp)(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr);
extern ze_result_t (*zeCommandListAppendQueryKernelTimestamps)(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeEventQueryTimestampsExp)(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps);
extern ze_result_t (*zeEventQueryKernelTimestampsExt)(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults);
extern ze_result_t (*zeFabricVertexGetExp)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices);
extern ze_result_t (*zeFabricVertexGetSubVerticesExp)(ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices);
extern ze_result_t (*zeFabricVertexGetPropertiesExp)(ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties);
extern ze_result_t (*zeFabricVertexGetDeviceExp)(ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* pDevice);
extern ze_result_t (*zeDeviceGetFabricVertexExp)(ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* pVertex);
extern ze_result_t (*zeFabricEdgeGetExp)(ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges);
extern ze_result_t (*zeFabricEdgeGetVerticesExp)(ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB);
extern ze_result_t (*zeFabricEdgeGetPropertiesExp)(ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties);
extern ze_result_t (*zeFenceCreate)(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence);
extern ze_result_t (*zeFenceDestroy)(ze_fence_handle_t hFence);
extern ze_result_t (*zeFenceHostSynchronize)(ze_fence_handle_t hFence, uint64_t timeout);
extern ze_result_t (*zeFenceQueryStatus)(ze_fence_handle_t hFence);
extern ze_result_t (*zeFenceReset)(ze_fence_handle_t hFence);
extern ze_result_t (*zeKernelSetGlobalOffsetExp)(ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
extern ze_result_t (*zeImageGetProperties)(ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties);
extern ze_result_t (*zeImageCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage);
extern ze_result_t (*zeImageDestroy)(ze_image_handle_t hImage);
extern ze_result_t (*zeKernelSchedulingHintExp)(ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint);
extern ze_result_t (*zeMemAllocShared)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
extern ze_result_t (*zeMemAllocDevice)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
extern ze_result_t (*zeMemAllocHost)(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr);
extern ze_result_t (*zeMemFree)(ze_context_handle_t hContext, void* ptr);
extern ze_result_t (*zeMemGetAllocProperties)(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice);
extern ze_result_t (*zeMemGetAddressRange)(ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize);
extern ze_result_t (*zeMemGetIpcHandle)(ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle);
extern ze_result_t (*zeMemOpenIpcHandle)(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr);
extern ze_result_t (*zeMemCloseIpcHandle)(ze_context_handle_t hContext, const void* ptr);
extern ze_result_t (*zeMemFreeExt)(ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr);
extern ze_result_t (*zeModuleCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
extern ze_result_t (*zeModuleDestroy)(ze_module_handle_t hModule);
extern ze_result_t (*zeModuleDynamicLink)(uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog);
extern ze_result_t (*zeModuleBuildLogDestroy)(ze_module_build_log_handle_t hModuleBuildLog);
extern ze_result_t (*zeModuleBuildLogGetString)(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
extern ze_result_t (*zeModuleGetNativeBinary)(ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary);
extern ze_result_t (*zeModuleGetGlobalPointer)(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
extern ze_result_t (*zeModuleGetKernelNames)(ze_module_handle_t hModule, uint32_t* pCount, const char** pNames);
extern ze_result_t (*zeModuleGetProperties)(ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties);
extern ze_result_t (*zeKernelCreate)(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
extern ze_result_t (*zeKernelDestroy)(ze_kernel_handle_t hKernel);
extern ze_result_t (*zeModuleGetFunctionPointer)(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
extern ze_result_t (*zeKernelSetGroupSize)(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ);
extern ze_result_t (*zeKernelSuggestGroupSize)(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ);
extern ze_result_t (*zeKernelSuggestMaxCooperativeGroupCount)(ze_kernel_handle_t hKernel, uint32_t* totalGroupCount);
extern ze_result_t (*zeKernelSetArgumentValue)(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
extern ze_result_t (*zeKernelSetIndirectAccess)(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags);
extern ze_result_t (*zeKernelGetIndirectAccess)(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags);
extern ze_result_t (*zeKernelSetCacheConfig)(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags);
extern ze_result_t (*zeKernelGetProperties)(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties);
extern ze_result_t (*zeKernelGetName)(ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
extern ze_result_t (*zeCommandListAppendLaunchKernel)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendLaunchCooperativeKernel)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendLaunchKernelIndirect)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendLaunchMultipleKernelsIndirect)(ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListHostSynchronize)(ze_command_list_handle_t hCommandList, uint64_t timeout);
extern ze_result_t (*zeDevicePciGetPropertiesExt)(ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties);
extern ze_result_t (*zeContextMakeMemoryResident)(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size);
extern ze_result_t (*zeContextEvictMemory)(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size);
extern ze_result_t (*zeVirtualMemReserve)(ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr);
extern ze_result_t (*zeVirtualMemFree)(ze_context_handle_t hContext, const void* ptr, size_t size);
extern ze_result_t (*zeVirtualMemQueryPageSize)(ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize);
extern ze_result_t (*zePhysicalMemCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory);
extern ze_result_t (*zePhysicalMemDestroy)(ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory);
extern ze_result_t (*zeVirtualMemMap)(ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access);
extern ze_result_t (*zeVirtualMemUnmap)(ze_context_handle_t hContext, const void* ptr, size_t size);
extern ze_result_t (*zeVirtualMemSetAccessAttribute)(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access);
extern ze_result_t (*zeVirtualMemGetAccessAttribute)(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize);
} // Standard

namespace Extensions {
extern ze_result_t (*zexMemGetIpcHandles)(ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
extern ze_result_t (*zexMemOpenIpcHandles)(ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
extern ze_result_t (*zexDriverImportExternalPointer)(ze_driver_handle_t hDriver, void* ptr, size_t size);
extern ze_result_t (*zexDriverReleaseImportedPointer)(ze_driver_handle_t hDriver, void* ptr);
extern ze_result_t (*zexDriverGetHostPointerBaseAddress)(ze_driver_handle_t hDriver, void* ptr, void** baseAddress);
} // Extensions

bool isSuccessful(ze_result_t result);

inline bool zesDeviceResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceReset(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.force
                                                );
    return true;
}
inline bool zesDeviceResetExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceResetExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceResetExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceResetExt(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pProperties
                                                );
    return true;
}
inline bool zesDeviceEnumPowerDomainsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumPowerDomains");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumPowerDomainsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumPowerDomains(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phPower ? apiCommand->captures.phPower : nullptr
                                                );
    return true;
}
inline bool zesDeviceGetCardPowerDomainHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceGetCardPowerDomain");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceGetCardPowerDomainRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceGetCardPowerDomain(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.phPower ? &apiCommand->captures.phPower : nullptr
                                                );
    return true;
}
inline bool zesPowerGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetProperties(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesPowerGetEnergyCounterHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerGetEnergyCounter");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetEnergyCounterRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetEnergyCounter(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pEnergy ? &apiCommand->captures.pEnergy : nullptr
                                                );
    return true;
}
inline bool zesPowerGetLimitsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerGetLimits");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetLimitsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetLimits(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pSustained ? &apiCommand->captures.pSustained : nullptr, 
                                                apiCommand->args.pBurst ? &apiCommand->captures.pBurst : nullptr, 
                                                apiCommand->args.pPeak ? &apiCommand->captures.pPeak : nullptr
                                                );
    return true;
}
inline bool zesPowerSetLimitsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerSetLimits");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerSetLimitsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerSetLimits(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pSustained ? &apiCommand->captures.pSustained : nullptr, 
                                                apiCommand->args.pBurst ? &apiCommand->captures.pBurst : nullptr, 
                                                apiCommand->args.pPeak ? &apiCommand->captures.pPeak : nullptr
                                                );
    return true;
}
inline bool zesPowerGetLimitsExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerGetLimitsExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetLimitsExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetLimitsExt(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pSustained ? apiCommand->captures.pSustained : nullptr
                                                );
    return true;
}
inline bool zesPowerSetLimitsExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerSetLimitsExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerSetLimitsExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerSetLimitsExt(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pSustained ? apiCommand->captures.pSustained : nullptr
                                                );
    return true;
}
inline bool zesPowerGetEnergyThresholdHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerGetEnergyThreshold");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetEnergyThresholdRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetEnergyThreshold(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pThreshold ? &apiCommand->captures.pThreshold : nullptr
                                                );
    return true;
}
inline bool zesPowerSetEnergyThresholdHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesPowerSetEnergyThreshold");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerSetEnergyThresholdRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerSetEnergyThreshold(
                                                apiCommand->args.hPower, 
                                                apiCommand->args.pThreshold
                                                );
    return true;
}
inline bool zesDeviceEventRegisterHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEventRegister");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEventRegisterRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEventRegister(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.events
                                                );
    return true;
}
inline bool zesDriverEventListenHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDriverEventListen");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDriverEventListenRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDriverEventListen(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.timeout, 
                                                apiCommand->args.count, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr, 
                                                apiCommand->args.pNumDeviceEvents ? &apiCommand->captures.pNumDeviceEvents : nullptr, 
                                                apiCommand->args.pEvents ? &apiCommand->captures.pEvents : nullptr
                                                );
    return true;
}
inline bool zesDriverEventListenExHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDriverEventListenEx");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDriverEventListenExRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDriverEventListenEx(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.timeout, 
                                                apiCommand->args.count, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr, 
                                                apiCommand->args.pNumDeviceEvents ? &apiCommand->captures.pNumDeviceEvents : nullptr, 
                                                apiCommand->args.pEvents ? &apiCommand->captures.pEvents : nullptr
                                                );
    return true;
}
inline bool zesDeviceEnumTemperatureSensorsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumTemperatureSensors");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumTemperatureSensorsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumTemperatureSensors(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phTemperature ? apiCommand->captures.phTemperature : nullptr
                                                );
    return true;
}
inline bool zesTemperatureGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesTemperatureGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureGetProperties(
                                                apiCommand->args.hTemperature, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesTemperatureGetConfigHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesTemperatureGetConfig");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureGetConfigRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureGetConfig(
                                                apiCommand->args.hTemperature, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesTemperatureSetConfigHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesTemperatureSetConfig");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureSetConfigRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureSetConfig(
                                                apiCommand->args.hTemperature, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesTemperatureGetStateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesTemperatureGetState");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureGetStateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureGetState(
                                                apiCommand->args.hTemperature, 
                                                apiCommand->args.pTemperature ? &apiCommand->captures.pTemperature : nullptr
                                                );
    return true;
}
inline bool zesDeviceEnumRasErrorSetsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumRasErrorSets");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumRasErrorSetsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumRasErrorSets(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phRas ? apiCommand->captures.phRas : nullptr
                                                );
    return true;
}
inline bool zesRasGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesRasGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesRasGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasGetProperties(
                                                apiCommand->args.hRas, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesRasGetConfigHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesRasGetConfig");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesRasGetConfigRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasGetConfig(
                                                apiCommand->args.hRas, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesRasSetConfigHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesRasSetConfig");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesRasSetConfigRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasSetConfig(
                                                apiCommand->args.hRas, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesRasGetStateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesRasGetState");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesRasGetStateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasGetState(
                                                apiCommand->args.hRas, 
                                                apiCommand->args.clear, 
                                                apiCommand->args.pState
                                                );
    return true;
}
inline bool zesDeviceEnumFrequencyDomainsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumFrequencyDomains");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumFrequencyDomainsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumFrequencyDomains(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phFrequency ? apiCommand->captures.phFrequency : nullptr
                                                );
    return true;
}
inline bool zesFrequencyGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetProperties(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesFrequencyGetAvailableClocksHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyGetAvailableClocks");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetAvailableClocksRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetAvailableClocks(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phFrequency ? apiCommand->captures.phFrequency : nullptr
                                                );
    return true;
}
inline bool zesFrequencyGetRangeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyGetRange");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetRangeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetRange(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesFrequencySetRangeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencySetRange");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencySetRangeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencySetRange(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pLimits ? &apiCommand->captures.pLimits : nullptr
                                                );
    return true;
}
inline bool zesFrequencyGetStateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyGetState");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetStateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetState(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pState ? &apiCommand->captures.pState : nullptr
                                                );
    return true;
}
inline bool zesFrequencyGetThrottleTimeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyGetThrottleTime");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetThrottleTimeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetThrottleTime(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pThrottleTime ? &apiCommand->captures.pThrottleTime : nullptr
                                                );
    return true;
}
inline bool zesFrequencyOcGetCapabilitiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcGetCapabilities");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetCapabilitiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetCapabilities(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pOcCapabilities ? &apiCommand->captures.pOcCapabilities : nullptr
                                                );
    return true;
}
inline bool zesFrequencyOcGetVoltageTargetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcGetVoltageTarget");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetVoltageTargetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetVoltageTarget(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pCurrentVoltageTarget, 
                                                apiCommand->args.pCurrentVoltageOffset
                                                );
    return true;
}
inline bool zesFrequencyOcSetVoltageTargetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcSetVoltageTarget");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetVoltageTargetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetVoltageTarget(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.CurrentVoltageTarget, 
                                                apiCommand->args.CurrentVoltageOffset
                                                );
    return true;
}
inline bool zesFrequencyOcSetModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcSetMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetMode(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.CurrentOcMode
                                                );
    return true;
}
inline bool zesFrequencyOcGetModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcGetMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetMode(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pCurrentOcMode
                                                );
    return true;
}
inline bool zesFrequencyOcGetIccMaxHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcGetIccMax");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetIccMaxRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetIccMax(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pOcIccMax
                                                );
    return true;
}
inline bool zesFrequencyOcSetIccMaxHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcSetIccMax");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetIccMaxRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetIccMax(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.ocIccMax
                                                );
    return true;
}
inline bool zesFrequencyOcGetTjMaxHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcGetTjMax");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetTjMaxRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetTjMax(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.pOcTjMax
                                                );
    return true;
}
inline bool zesFrequencyOcSetTjMaxHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesFrequencyOcSetTjMax");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetTjMaxRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetTjMax(
                                                apiCommand->args.hFrequency, 
                                                apiCommand->args.ocTjMax
                                                );
    return true;
}
inline bool zesDeviceEnumEngineGroupsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumEngineGroups");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumEngineGroupsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumEngineGroups(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phEngine ? apiCommand->captures.phEngine : nullptr
                                                );
    return true;
}
inline bool zesDeviceEnumSchedulersHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumSchedulers");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumSchedulersRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumSchedulers(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phScheduler ? apiCommand->captures.phScheduler : nullptr
                                                );
    return true;
}
inline bool zesSchedulerGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetProperties(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesSchedulerGetCurrentModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerGetCurrentMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetCurrentModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetCurrentMode(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.pMode ? &apiCommand->captures.pMode : nullptr
                                                );
    return true;
}
inline bool zesSchedulerGetTimeoutModePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerGetTimeoutModeProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetTimeoutModePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetTimeoutModeProperties(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.getDefaults, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesSchedulerGetTimesliceModePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerGetTimesliceModeProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetTimesliceModePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetTimesliceModeProperties(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.getDefaults, 
                                                apiCommand->args.pConfig ? &apiCommand->captures.pConfig : nullptr
                                                );
    return true;
}
inline bool zesSchedulerSetTimeoutModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerSetTimeoutMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetTimeoutModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetTimeoutMode(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr, 
                                                apiCommand->args.pNeedReload ? &apiCommand->captures.pNeedReload : nullptr
                                                );
    return true;
}
inline bool zesSchedulerSetTimesliceModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerSetTimesliceMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetTimesliceModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetTimesliceMode(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr, 
                                                apiCommand->args.pNeedReload ? &apiCommand->captures.pNeedReload : nullptr
                                                );
    return true;
}
inline bool zesSchedulerSetExclusiveModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerSetExclusiveMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetExclusiveModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetExclusiveMode(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.pNeedReload ? &apiCommand->captures.pNeedReload : nullptr
                                                );
    return true;
}
inline bool zesSchedulerSetComputeUnitDebugModeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesSchedulerSetComputeUnitDebugMode");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetComputeUnitDebugModeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetComputeUnitDebugMode(
                                                apiCommand->args.hScheduler, 
                                                apiCommand->args.pNeedReload ? &apiCommand->captures.pNeedReload : nullptr
                                                );
    return true;
}
inline bool zesEngineGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesEngineGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesEngineGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesEngineGetProperties(
                                                apiCommand->args.hEngine, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesEngineGetActivityHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesEngineGetActivity");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesEngineGetActivityRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesEngineGetActivity(
                                                apiCommand->args.hEngine, 
                                                apiCommand->args.pStats ? &apiCommand->captures.pStats : nullptr
                                                );
    return true;
}
inline bool zesDeviceGetStateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceGetState");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceGetStateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceGetState(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pState ? &apiCommand->captures.pState : nullptr
                                                );
    return true;
}
inline bool zesDeviceProcessesGetStateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceProcessesGetState");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceProcessesGetStateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceProcessesGetState(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount, 
                                                apiCommand->args.pProcesses ? apiCommand->captures.pProcesses : nullptr
                                                );
    return true;
}
inline bool zesDevicePciGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDevicePciGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesDevicePciGetStateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDevicePciGetState");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetStateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetState(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pState ? &apiCommand->captures.pState : nullptr
                                                );
    return true;
}
inline bool zesDevicePciGetBarsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDevicePciGetBars");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetBarsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetBars(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesDevicePciGetStatsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDevicePciGetStats");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetStatsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetStats(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pStats ? &apiCommand->captures.pStats : nullptr
                                                );
    return true;
}
inline bool zesDeviceGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceGetProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pProperties ? &apiCommand->captures.pProperties : nullptr
                                                );
    return true;
}
inline bool zesDeviceEnumMemoryModulesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zesDeviceEnumMemoryModules");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumMemoryModulesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumMemoryModules(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount, 
                                                apiCommand->args.phMemory ? apiCommand->captures.phMemory : nullptr
                                                );
    return true;
}
bool zeInitHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendMemoryRangesBarrierHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryRangesBarrier");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryRangesBarrierRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryRangesBarrier(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.numRanges, 
                                                apiCommand->args.pRangeSizes ? apiCommand->captures.getPRangeSizes() : nullptr, 
                                                apiCommand->args.pRanges ? apiCommand->captures.getPRanges() : nullptr, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
inline bool zeContextSystemBarrierHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextSystemBarrier");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextSystemBarrierRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextSystemBarrier(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice
                                                );
    return true;
}
inline bool zeCommandListCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListCreate");
    service.overrideCommandListDesc(reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateRpcM*>(command)->args.desc ? &reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateRpcM*>(command)->captures.desc : nullptr, ctx);
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
            ctx.getCommandListToContextTracker().registerCommandListToContextMapping(*resource, apiCommand->args.hContext);
        }
    }
    return true;
}
inline bool zeCommandListCreateImmediateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListCreateImmediate");
    service.overrideCommandQueueDesc(reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM*>(command)->args.altdesc ? &reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM*>(command)->captures.altdesc : nullptr, ctx);
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreateImmediate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.altdesc ? &apiCommand->captures.altdesc : nullptr, 
                                                apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
            ctx.getCommandListToContextTracker().registerCommandListToContextMapping(*resource, apiCommand->args.hContext);
        }
    }
    return true;
}
bool zeCommandListDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListCloseHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListClose");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCloseRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListClose(
                                                apiCommand->args.hCommandList
                                                );
    return true;
}
bool zeCommandListResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendWriteGlobalTimestampHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendWriteGlobalTimestamp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendWriteGlobalTimestampRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendWriteGlobalTimestamp(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandQueueCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueCreate");
    service.overrideCommandQueueDesc(reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM*>(command)->args.desc ? &reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM*>(command)->captures.desc : nullptr, ctx);
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phCommandQueue ? &apiCommand->captures.phCommandQueue : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phCommandQueue ? &apiCommand->captures.phCommandQueue : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeCommandQueueDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueDestroy(
                                                apiCommand->args.hCommandQueue
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hCommandQueue;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
bool zeCommandQueueExecuteCommandListsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeCommandQueueExecuteCommandListsCopyMemoryRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeCommandQueueSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeContextCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreate(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeContextCreateExHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextCreateEx");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateExRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreateEx(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.numDevices, 
                                                apiCommand->args.phDevices ? apiCommand->captures.getPhDevices() : nullptr, 
                                                apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
bool zeContextDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeContextGetStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextGetStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextGetStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextGetStatus(
                                                apiCommand->args.hContext
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferredHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferredRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate (as zeCommandListAppendMemoryCopyImmediateHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronousHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronousRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous (as zeCommandListAppendMemoryCopyImmediateSynchronousHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryFillRpcHelperUsm2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperUsm2Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pattern, 
                                                apiCommand->args.pattern_size, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
bool zeCommandListAppendMemoryFillRpcHelperUsm2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendMemoryFillRpcHelperMalloc2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperMalloc2Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr, 
                                                apiCommand->args.pattern_size, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
bool zeCommandListAppendMemoryFillRpcHelperMalloc2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendMemoryPrefetchHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryPrefetch");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryPrefetchRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryPrefetch(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size
                                                );
    return true;
}
inline bool zeDeviceGetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGet");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetSubDevicesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetSubDevices");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetSubDevices(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phSubdevices ? apiCommand->captures.phSubdevices : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pDeviceProperties ? &apiCommand->captures.pDeviceProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetComputePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetComputeProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetComputeProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pComputeProperties ? &apiCommand->captures.pComputeProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetModulePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetModuleProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetModuleProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pModuleProperties ? &apiCommand->captures.pModuleProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetCommandQueueGroupPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetCommandQueueGroupProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCommandQueueGroupProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pCommandQueueGroupProperties ? apiCommand->captures.pCommandQueueGroupProperties : nullptr
                                                );
    service.parseCommandQueueGroups(apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, apiCommand->args.pCommandQueueGroupProperties ? apiCommand->captures.pCommandQueueGroupProperties : nullptr);
    return true;
}
inline bool zeDeviceGetMemoryPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetMemoryProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pMemProperties ? apiCommand->captures.getPMemProperties() : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetMemoryAccessPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetMemoryAccessProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryAccessProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pMemAccessProperties ? &apiCommand->captures.pMemAccessProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetCachePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetCacheProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCacheProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pCacheProperties ? apiCommand->captures.getPCacheProperties() : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetImagePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetImageProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetImageProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pImageProperties ? &apiCommand->captures.pImageProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetExternalMemoryPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetExternalMemoryProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetExternalMemoryProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pExternalMemoryProperties ? &apiCommand->captures.pExternalMemoryProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetP2PPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetP2PProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetP2PProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.hPeerDevice, 
                                                apiCommand->args.pP2PProperties ? &apiCommand->captures.pP2PProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceCanAccessPeerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceCanAccessPeer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceCanAccessPeer(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.hPeerDevice, 
                                                apiCommand->args.value ? &apiCommand->captures.value : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetStatus(
                                                apiCommand->args.hDevice
                                                );
    return true;
}
inline bool zeDeviceGetGlobalTimestampsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetGlobalTimestamps");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetGlobalTimestamps(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.hostTimestamp ? &apiCommand->captures.hostTimestamp : nullptr, 
                                                apiCommand->args.deviceTimestamp ? &apiCommand->captures.deviceTimestamp : nullptr
                                                );
    return true;
}
inline bool zeDeviceReserveCacheExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceReserveCacheExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceReserveCacheExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceReserveCacheExt(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.cacheLevel, 
                                                apiCommand->args.cacheReservationSize
                                                );
    return true;
}
inline bool zeDeviceSetCacheAdviceExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceSetCacheAdviceExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceSetCacheAdviceExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceSetCacheAdviceExt(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.regionSize, 
                                                apiCommand->args.cacheRegion
                                                );
    return true;
}
bool zeDriverGetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeDriverGetApiVersionHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetApiVersion");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetApiVersion(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.version ? &apiCommand->captures.version : nullptr
                                                );
    return true;
}
inline bool zeDriverGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetProperties(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pDriverProperties ? &apiCommand->captures.pDriverProperties : nullptr
                                                );
    return true;
}
inline bool zeDriverGetIpcPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetIpcProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetIpcProperties(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pIpcProperties ? &apiCommand->captures.pIpcProperties : nullptr
                                                );
    return true;
}
inline bool zeDriverGetExtensionPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetExtensionProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetExtensionProperties(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pExtensionProperties ? apiCommand->captures.pExtensionProperties : nullptr
                                                );
    return true;
}
inline bool zeEventPoolCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.numDevices, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr, 
                                                apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeEventPoolDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolDestroy(
                                                apiCommand->args.hEventPool
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hEventPool;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeEventCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventCreate(
                                                apiCommand->args.hEventPool, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phEvent ? &apiCommand->captures.phEvent : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phEvent ? &apiCommand->captures.phEvent : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeEventDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventDestroy(
                                                apiCommand->args.hEvent
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hEvent;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeEventPoolGetIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolGetIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolGetIpcHandle(
                                                apiCommand->args.hEventPool, 
                                                apiCommand->args.phIpc ? &apiCommand->captures.phIpc : nullptr
                                                );
    return true;
}
inline bool zeEventPoolOpenIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolOpenIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolOpenIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hIpc, 
                                                apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeEventPoolCloseIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolCloseIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCloseIpcHandle(
                                                apiCommand->args.hEventPool
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hEventPool;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeCommandListAppendBarrierHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendBarrier");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendBarrier(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendBarrier (as zeCommandListAppendBarrierHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendSignalEventHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendSignalEvent");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendSignalEvent(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hEvent
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendSignalEvent (as zeCommandListAppendSignalEventHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendWaitOnEventsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendWaitOnEvents");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendWaitOnEvents(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.numEvents, 
                                                apiCommand->args.phEvents ? apiCommand->captures.phEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendWaitOnEvents (as zeCommandListAppendWaitOnEventsHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeEventHostSignalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventHostSignal");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSignalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSignal(
                                                apiCommand->args.hEvent
                                                );
    return true;
}
bool zeEventHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeEventQueryStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendEventResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendEventReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendEventReset(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hEvent
                                                );
    return true;
}
inline bool zeEventHostResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventHostReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostReset(
                                                apiCommand->args.hEvent
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeEventHostReset (as zeEventHostResetHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeEventQueryKernelTimestampHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventQueryKernelTimestamp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryKernelTimestamp(
                                                apiCommand->args.hEvent, 
                                                apiCommand->args.dstptr ? &apiCommand->captures.dstptr : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendQueryKernelTimestampsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendQueryKernelTimestamps");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendQueryKernelTimestampsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendQueryKernelTimestamps(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.numEvents, 
                                                apiCommand->args.phEvents ? apiCommand->captures.getPhEvents() : nullptr, 
                                                apiCommand->args.dstptr ? apiCommand->captures.getDstptr() : nullptr, 
                                                apiCommand->args.pOffsets, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
inline bool zeEventQueryTimestampsExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventQueryTimestampsExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryTimestampsExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryTimestampsExp(
                                                apiCommand->args.hEvent, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pTimestamps ? apiCommand->captures.pTimestamps : nullptr
                                                );
    return true;
}
bool zeEventQueryKernelTimestampsExtRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeFabricVertexGetExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricVertexGetExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetExp(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phVertices ? apiCommand->captures.phVertices : nullptr
                                                );
    return true;
}
inline bool zeFabricVertexGetSubVerticesExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricVertexGetSubVerticesExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetSubVerticesExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetSubVerticesExp(
                                                apiCommand->args.hVertex, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phSubvertices ? apiCommand->captures.phSubvertices : nullptr
                                                );
    return true;
}
inline bool zeFabricVertexGetPropertiesExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricVertexGetPropertiesExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetPropertiesExpRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetPropertiesExp(
                                                apiCommand->args.hVertex, 
                                                apiCommand->args.pVertexProperties ? &apiCommand->captures.pVertexProperties : nullptr
                                                );
    return true;
}
inline bool zeFabricVertexGetDeviceExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricVertexGetDeviceExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetDeviceExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetDeviceExp(
                                                apiCommand->args.hVertex, 
                                                apiCommand->args.pDevice ? &apiCommand->captures.pDevice : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetFabricVertexExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetFabricVertexExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetFabricVertexExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetFabricVertexExp(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pVertex ? &apiCommand->captures.pVertex : nullptr
                                                );
    return true;
}
inline bool zeFabricEdgeGetExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricEdgeGetExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricEdgeGetExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricEdgeGetExp(
                                                apiCommand->args.hVertexA, 
                                                apiCommand->args.hVertexB, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phEdges ? apiCommand->captures.phEdges : nullptr
                                                );
    return true;
}
inline bool zeFabricEdgeGetVerticesExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricEdgeGetVerticesExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricEdgeGetVerticesExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricEdgeGetVerticesExp(
                                                apiCommand->args.hEdge, 
                                                apiCommand->args.phVertexA ? &apiCommand->captures.phVertexA : nullptr, 
                                                apiCommand->args.phVertexB ? &apiCommand->captures.phVertexB : nullptr
                                                );
    return true;
}
inline bool zeFabricEdgeGetPropertiesExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFabricEdgeGetPropertiesExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricEdgeGetPropertiesExpRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricEdgeGetPropertiesExp(
                                                apiCommand->args.hEdge, 
                                                apiCommand->args.pEdgeProperties ? &apiCommand->captures.pEdgeProperties : nullptr
                                                );
    return true;
}
inline bool zeFenceCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceCreate(
                                                apiCommand->args.hCommandQueue, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phFence ? &apiCommand->captures.phFence : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phFence ? &apiCommand->captures.phFence : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeFenceDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceDestroy(
                                                apiCommand->args.hFence
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hFence;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
bool zeFenceHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeFenceQueryStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeFenceResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceReset(
                                                apiCommand->args.hFence
                                                );
    return true;
}
inline bool zeKernelSetGlobalOffsetExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetGlobalOffsetExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGlobalOffsetExp(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.offsetX, 
                                                apiCommand->args.offsetY, 
                                                apiCommand->args.offsetZ
                                                );
    return true;
}
inline bool zeImageGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeImageGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageGetProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.pImageProperties ? &apiCommand->captures.pImageProperties : nullptr
                                                );
    return true;
}
inline bool zeImageCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeImageCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeImageCreateRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phImage ? &apiCommand->captures.phImage : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phImage ? &apiCommand->captures.phImage : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeImageDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeImageDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeImageDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageDestroy(
                                                apiCommand->args.hImage
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hImage;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeKernelSchedulingHintExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSchedulingHintExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSchedulingHintExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSchedulingHintExp(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pHint ? &apiCommand->captures.pHint : nullptr
                                                );
    return true;
}
bool zeMemAllocSharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeMemAllocDeviceHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemAllocDevice");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocDevice(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.device_desc ? &apiCommand->captures.device_desc : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.alignment, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
bool zeMemAllocHostHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeMemFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeMemGetAllocPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemGetAllocProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAllocProperties(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pMemAllocProperties ? &apiCommand->captures.pMemAllocProperties : nullptr, 
                                                apiCommand->args.phDevice ? &apiCommand->captures.phDevice : nullptr
                                                );
    return true;
}
inline bool zeMemGetAddressRangeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemGetAddressRange");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAddressRange(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pBase ? &apiCommand->captures.pBase : nullptr, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr
                                                );
    return true;
}
inline bool zeMemGetIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemGetIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pIpcHandle ? &apiCommand->captures.pIpcHandle : nullptr
                                                );
    return true;
}
inline bool zeMemOpenIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemOpenIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemOpenIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.handle, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
inline bool zeMemCloseIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemCloseIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemCloseIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr
                                                );
    return true;
}
inline bool zexMemGetIpcHandlesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexMemGetIpcHandles");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemGetIpcHandles(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.numIpcHandles ? &apiCommand->captures.numIpcHandles : nullptr, 
                                                apiCommand->args.pIpcHandles ? apiCommand->captures.pIpcHandles : nullptr
                                                );
    return true;
}
inline bool zexMemOpenIpcHandlesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexMemOpenIpcHandles");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemOpenIpcHandles(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.numIpcHandles, 
                                                apiCommand->args.pIpcHandles ? apiCommand->captures.pIpcHandles : nullptr, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
bool zeMemFreeExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeModuleCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeModuleDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDestroy(
                                                apiCommand->args.hModule
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hModule;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeModuleDynamicLinkHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleDynamicLink");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDynamicLink(
                                                apiCommand->args.numModules, 
                                                apiCommand->args.phModules ? apiCommand->captures.phModules : nullptr, 
                                                apiCommand->args.phLinkLog ? &apiCommand->captures.phLinkLog : nullptr
                                                );
    {
        const auto& resource = apiCommand->args.phLinkLog ? &apiCommand->captures.phLinkLog : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeModuleBuildLogDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleBuildLogDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogDestroy(
                                                apiCommand->args.hModuleBuildLog
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hModuleBuildLog;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeModuleBuildLogGetStringHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleBuildLogGetString");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogGetString(
                                                apiCommand->args.hModuleBuildLog, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pBuildLog ? apiCommand->captures.pBuildLog : nullptr
                                                );
    return true;
}
inline bool zeModuleGetNativeBinaryHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetNativeBinary");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetNativeBinary(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pModuleNativeBinary ? apiCommand->captures.pModuleNativeBinary : nullptr
                                                );
    return true;
}
inline bool zeModuleGetGlobalPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetGlobalPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetGlobalPointer(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pGlobalName ? apiCommand->captures.pGlobalName : nullptr, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
bool zeModuleGetKernelNamesRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeModuleGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetProperties(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pModuleProperties ? &apiCommand->captures.pModuleProperties : nullptr
                                                );
    return true;
}
inline bool zeKernelCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelCreateRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelCreate(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phKernel ? &apiCommand->captures.phKernel : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phKernel ? &apiCommand->captures.phKernel : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeKernelDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelDestroy(
                                                apiCommand->args.hKernel
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hKernel;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeModuleGetFunctionPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetFunctionPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetFunctionPointer(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pFunctionName ? apiCommand->captures.pFunctionName : nullptr, 
                                                apiCommand->args.pfnFunction ? &apiCommand->captures.pfnFunction : nullptr
                                                );
    return true;
}
inline bool zeKernelSetGroupSizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetGroupSize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGroupSize(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.groupSizeX, 
                                                apiCommand->args.groupSizeY, 
                                                apiCommand->args.groupSizeZ
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeKernelSetGroupSize (as zeKernelSetGroupSizeHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeKernelSuggestGroupSizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSuggestGroupSize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestGroupSize(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.globalSizeX, 
                                                apiCommand->args.globalSizeY, 
                                                apiCommand->args.globalSizeZ, 
                                                apiCommand->args.groupSizeX ? &apiCommand->captures.groupSizeX : nullptr, 
                                                apiCommand->args.groupSizeY ? &apiCommand->captures.groupSizeY : nullptr, 
                                                apiCommand->args.groupSizeZ ? &apiCommand->captures.groupSizeZ : nullptr
                                                );
    return true;
}
inline bool zeKernelSuggestMaxCooperativeGroupCountHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSuggestMaxCooperativeGroupCount");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestMaxCooperativeGroupCount(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.totalGroupCount ? &apiCommand->captures.totalGroupCount : nullptr
                                                );
    return true;
}
inline bool zeKernelSetArgumentValueHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetArgumentValue");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetArgumentValue(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.argIndex, 
                                                apiCommand->args.argSize, 
                                                apiCommand->args.pArgValue ? apiCommand->captures.pArgValue : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeKernelSetArgumentValue (as zeKernelSetArgumentValueHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeKernelSetIndirectAccessHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetIndirectAccess");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetIndirectAccess(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.flags
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeKernelSetIndirectAccess (as zeKernelSetIndirectAccessHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeKernelGetIndirectAccessHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetIndirectAccess");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetIndirectAccess(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pFlags ? &apiCommand->captures.pFlags : nullptr
                                                );
    return true;
}
inline bool zeKernelSetCacheConfigHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetCacheConfig");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetCacheConfig(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.flags
                                                );
    return true;
}
inline bool zeKernelGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetProperties(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pKernelProperties ? &apiCommand->captures.pKernelProperties : nullptr
                                                );
    return true;
}
inline bool zeKernelGetNameHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetName");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetNameRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetName(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pName ? apiCommand->captures.pName : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendLaunchKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendLaunchKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernel(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pLaunchFuncArgs ? &apiCommand->captures.pLaunchFuncArgs : nullptr, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendLaunchKernel (as zeCommandListAppendLaunchKernelHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendLaunchCooperativeKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendLaunchCooperativeKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchCooperativeKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchCooperativeKernel(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pLaunchFuncArgs ? &apiCommand->captures.pLaunchFuncArgs : nullptr, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendLaunchKernelIndirectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendLaunchKernelIndirect");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernelIndirect(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pLaunchArgumentsBuffer, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendLaunchMultipleKernelsIndirectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendLaunchMultipleKernelsIndirect");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchMultipleKernelsIndirect(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.numKernels, 
                                                apiCommand->args.phKernels ? apiCommand->captures.getPhKernels() : nullptr, 
                                                apiCommand->args.pCountBuffer, 
                                                apiCommand->args.pLaunchArgumentsBuffer, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
inline bool zeCommandListHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListHostSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListHostSynchronizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListHostSynchronize(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.timeout
                                                );
    return true;
}
inline bool zeDevicePciGetPropertiesExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDevicePciGetPropertiesExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDevicePciGetPropertiesExt(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pPciProperties ? &apiCommand->captures.pPciProperties : nullptr
                                                );
    return true;
}
inline bool zeContextMakeMemoryResidentHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextMakeMemoryResident");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextMakeMemoryResidentRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextMakeMemoryResident(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size
                                                );
    return true;
}
inline bool zeContextEvictMemoryHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextEvictMemory");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextEvictMemoryRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextEvictMemory(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size
                                                );
    return true;
}
inline bool zeVirtualMemReserveHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemReserve");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemReserveRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemReserve(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.pStart, 
                                                apiCommand->args.size, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
inline bool zeVirtualMemFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemFree");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemFreeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemFree(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size
                                                );
    return true;
}
inline bool zeVirtualMemQueryPageSizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemQueryPageSize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemQueryPageSizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemQueryPageSize(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.size, 
                                                apiCommand->args.pagesize ? &apiCommand->captures.pagesize : nullptr
                                                );
    return true;
}
inline bool zePhysicalMemCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zePhysicalMemCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZePhysicalMemCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zePhysicalMemCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phPhysicalMemory ? &apiCommand->captures.phPhysicalMemory : nullptr
                                                );
    return true;
}
inline bool zePhysicalMemDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zePhysicalMemDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZePhysicalMemDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zePhysicalMemDestroy(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hPhysicalMemory
                                                );
    return true;
}
inline bool zeVirtualMemMapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemMap");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemMapRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemMap(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hPhysicalMemory, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.access
                                                );
    return true;
}
inline bool zeVirtualMemUnmapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemUnmap");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemUnmapRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemUnmap(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size
                                                );
    return true;
}
inline bool zeVirtualMemSetAccessAttributeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemSetAccessAttribute");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemSetAccessAttributeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemSetAccessAttribute(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.access
                                                );
    return true;
}
inline bool zeVirtualMemGetAccessAttributeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeVirtualMemGetAccessAttribute");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemGetAccessAttributeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemGetAccessAttribute(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.access ? &apiCommand->captures.access : nullptr, 
                                                apiCommand->args.outSize ? &apiCommand->captures.outSize : nullptr
                                                );
    return true;
}
inline bool zexDriverImportExternalPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexDriverImportExternalPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexDriverImportExternalPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexDriverImportExternalPointer(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size
                                                );
    return true;
}
inline bool zexDriverReleaseImportedPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexDriverReleaseImportedPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexDriverReleaseImportedPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexDriverReleaseImportedPointer(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.ptr
                                                );
    return true;
}
inline bool zexDriverGetHostPointerBaseAddressHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexDriverGetHostPointerBaseAddress");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexDriverGetHostPointerBaseAddressRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexDriverGetHostPointerBaseAddress(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.baseAddress ? &apiCommand->captures.baseAddress : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Usm_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Usm_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Usm_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Usm_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM*>(command);
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Usm_RemappedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Usm_Remapped");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM*>(command);
    void *remappedPtrSrcptr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.srcptr, apiCommand->args.size);
    if((nullptr == remappedPtrSrcptr) && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                remappedPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Shared_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Shared_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Shared_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Shared_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Shared_RemappedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Shared_Remapped");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    void *remappedPtrSrcptr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.srcptr, apiCommand->args.size);
    if((nullptr == remappedPtrSrcptr) && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                remappedPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Remapped_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Remapped_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM*>(command);
    void *remappedPtrDstptr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.dstptr, apiCommand->args.size);
    if((nullptr == remappedPtrDstptr) && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    auto opEndMarkerEvent = Cal::Service::Apis::LevelZero::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                remappedPtrDstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                opEndMarkerEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    Cal::Service::Apis::LevelZero::addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, apiCommand->args.dstptr, apiCommand->args.size, true);
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Remapped_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Remapped_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM*>(command);
    void *remappedPtrDstptr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.dstptr, apiCommand->args.size);
    if((nullptr == remappedPtrDstptr) && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    auto opEndMarkerEvent = Cal::Service::Apis::LevelZero::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                remappedPtrDstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                opEndMarkerEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    Cal::Service::Apis::LevelZero::addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, apiCommand->args.dstptr, apiCommand->args.size, true);
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyDeferred_Remapped_RemappedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyDeferred_Remapped_Remapped");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM*>(command);
    void *remappedPtrDstptr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.dstptr, apiCommand->args.size);
    if((nullptr == remappedPtrDstptr) && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    void *remappedPtrSrcptr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.srcptr, apiCommand->args.size);
    if((nullptr == remappedPtrSrcptr) && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    auto opEndMarkerEvent = Cal::Service::Apis::LevelZero::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                remappedPtrDstptr, 
                                                remappedPtrSrcptr, 
                                                apiCommand->args.size, 
                                                opEndMarkerEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    Cal::Service::Apis::LevelZero::addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, apiCommand->args.dstptr, apiCommand->args.size, true);
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Local_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Local_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM*>(command);
    ctx.getMemoryBlocksManager().registerUSMStaging(apiCommand->args.dstptr, apiCommand->args.size);
    auto opEndMarkerEvent = Cal::Service::Apis::LevelZero::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                opEndMarkerEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Local_Local (as zeCommandListAppendMemoryCopyImmediate_Local_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    Cal::Service::Apis::LevelZero::addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, apiCommand->args.dstptr, apiCommand->args.size, false);
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Local_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Local_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM*>(command);
    ctx.getMemoryBlocksManager().registerUSMStaging(apiCommand->args.dstptr, apiCommand->args.size);
    auto opEndMarkerEvent = Cal::Service::Apis::LevelZero::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                opEndMarkerEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Local_Usm (as zeCommandListAppendMemoryCopyImmediate_Local_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    Cal::Service::Apis::LevelZero::addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, apiCommand->args.dstptr, apiCommand->args.size, false);
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Local_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Local_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM*>(command);
    ctx.getMemoryBlocksManager().registerUSMStaging(apiCommand->args.dstptr, apiCommand->args.size);
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    auto opEndMarkerEvent = Cal::Service::Apis::LevelZero::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                opEndMarkerEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Local_Shared (as zeCommandListAppendMemoryCopyImmediate_Local_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    Cal::Service::Apis::LevelZero::addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, apiCommand->args.dstptr, apiCommand->args.size, false);
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Usm_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Usm_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Usm_Local (as zeCommandListAppendMemoryCopyImmediate_Usm_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Usm_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Usm_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Usm_Usm (as zeCommandListAppendMemoryCopyImmediate_Usm_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Usm_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Usm_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM*>(command);
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Usm_Shared (as zeCommandListAppendMemoryCopyImmediate_Usm_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Shared_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Shared_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Shared_Local (as zeCommandListAppendMemoryCopyImmediate_Shared_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Shared_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Shared_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Shared_Usm (as zeCommandListAppendMemoryCopyImmediate_Shared_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediate_Shared_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediate_Shared_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediate_Shared_Shared (as zeCommandListAppendMemoryCopyImmediate_Shared_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr ? apiCommand->captures.getDstptr() : nullptr, 
                                                apiCommand->args.srcptr ? apiCommand->captures.getSrcptr() : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local (as zeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr ? apiCommand->captures.getDstptr() : nullptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm (as zeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM*>(command);
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr ? apiCommand->captures.getDstptr() : nullptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared (as zeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr ? apiCommand->captures.getSrcptr() : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local (as zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm (as zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM*>(command);
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared (as zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                apiCommand->args.srcptr ? apiCommand->captures.getSrcptr() : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local (as zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm (as zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM*>(command);
    void *importedMallocPtrDstptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstptr)  && (nullptr != apiCommand->args.dstptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstptr, apiCommand->args.size);
        return false;
    }
    void *importedMallocPtrSrcptr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcptr)  && (nullptr != apiCommand->args.srcptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                importedMallocPtrDstptr, 
                                                importedMallocPtrSrcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared (as zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}

inline void registerGeneratedHandlersLevelZero(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
    using namespace Cal::Rpc::LevelZero;
    outHandlers.resize(ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::messageSubtype + 1);
    outHandlers[ZesDeviceResetRpcM::messageSubtype] = zesDeviceResetHandler;
    outHandlers[ZesDeviceResetExtRpcM::messageSubtype] = zesDeviceResetExtHandler;
    outHandlers[ZesDeviceEnumPowerDomainsRpcM::messageSubtype] = zesDeviceEnumPowerDomainsHandler;
    outHandlers[ZesDeviceGetCardPowerDomainRpcM::messageSubtype] = zesDeviceGetCardPowerDomainHandler;
    outHandlers[ZesPowerGetPropertiesRpcM::messageSubtype] = zesPowerGetPropertiesHandler;
    outHandlers[ZesPowerGetEnergyCounterRpcM::messageSubtype] = zesPowerGetEnergyCounterHandler;
    outHandlers[ZesPowerGetLimitsRpcM::messageSubtype] = zesPowerGetLimitsHandler;
    outHandlers[ZesPowerSetLimitsRpcM::messageSubtype] = zesPowerSetLimitsHandler;
    outHandlers[ZesPowerGetLimitsExtRpcM::messageSubtype] = zesPowerGetLimitsExtHandler;
    outHandlers[ZesPowerSetLimitsExtRpcM::messageSubtype] = zesPowerSetLimitsExtHandler;
    outHandlers[ZesPowerGetEnergyThresholdRpcM::messageSubtype] = zesPowerGetEnergyThresholdHandler;
    outHandlers[ZesPowerSetEnergyThresholdRpcM::messageSubtype] = zesPowerSetEnergyThresholdHandler;
    outHandlers[ZesDeviceEventRegisterRpcM::messageSubtype] = zesDeviceEventRegisterHandler;
    outHandlers[ZesDriverEventListenRpcM::messageSubtype] = zesDriverEventListenHandler;
    outHandlers[ZesDriverEventListenExRpcM::messageSubtype] = zesDriverEventListenExHandler;
    outHandlers[ZesDeviceEnumTemperatureSensorsRpcM::messageSubtype] = zesDeviceEnumTemperatureSensorsHandler;
    outHandlers[ZesTemperatureGetPropertiesRpcM::messageSubtype] = zesTemperatureGetPropertiesHandler;
    outHandlers[ZesTemperatureGetConfigRpcM::messageSubtype] = zesTemperatureGetConfigHandler;
    outHandlers[ZesTemperatureSetConfigRpcM::messageSubtype] = zesTemperatureSetConfigHandler;
    outHandlers[ZesTemperatureGetStateRpcM::messageSubtype] = zesTemperatureGetStateHandler;
    outHandlers[ZesDeviceEnumRasErrorSetsRpcM::messageSubtype] = zesDeviceEnumRasErrorSetsHandler;
    outHandlers[ZesRasGetPropertiesRpcM::messageSubtype] = zesRasGetPropertiesHandler;
    outHandlers[ZesRasGetConfigRpcM::messageSubtype] = zesRasGetConfigHandler;
    outHandlers[ZesRasSetConfigRpcM::messageSubtype] = zesRasSetConfigHandler;
    outHandlers[ZesRasGetStateRpcM::messageSubtype] = zesRasGetStateHandler;
    outHandlers[ZesDeviceEnumFrequencyDomainsRpcM::messageSubtype] = zesDeviceEnumFrequencyDomainsHandler;
    outHandlers[ZesFrequencyGetPropertiesRpcM::messageSubtype] = zesFrequencyGetPropertiesHandler;
    outHandlers[ZesFrequencyGetAvailableClocksRpcM::messageSubtype] = zesFrequencyGetAvailableClocksHandler;
    outHandlers[ZesFrequencyGetRangeRpcM::messageSubtype] = zesFrequencyGetRangeHandler;
    outHandlers[ZesFrequencySetRangeRpcM::messageSubtype] = zesFrequencySetRangeHandler;
    outHandlers[ZesFrequencyGetStateRpcM::messageSubtype] = zesFrequencyGetStateHandler;
    outHandlers[ZesFrequencyGetThrottleTimeRpcM::messageSubtype] = zesFrequencyGetThrottleTimeHandler;
    outHandlers[ZesFrequencyOcGetCapabilitiesRpcM::messageSubtype] = zesFrequencyOcGetCapabilitiesHandler;
    outHandlers[ZesFrequencyOcGetVoltageTargetRpcM::messageSubtype] = zesFrequencyOcGetVoltageTargetHandler;
    outHandlers[ZesFrequencyOcSetVoltageTargetRpcM::messageSubtype] = zesFrequencyOcSetVoltageTargetHandler;
    outHandlers[ZesFrequencyOcSetModeRpcM::messageSubtype] = zesFrequencyOcSetModeHandler;
    outHandlers[ZesFrequencyOcGetModeRpcM::messageSubtype] = zesFrequencyOcGetModeHandler;
    outHandlers[ZesFrequencyOcGetIccMaxRpcM::messageSubtype] = zesFrequencyOcGetIccMaxHandler;
    outHandlers[ZesFrequencyOcSetIccMaxRpcM::messageSubtype] = zesFrequencyOcSetIccMaxHandler;
    outHandlers[ZesFrequencyOcGetTjMaxRpcM::messageSubtype] = zesFrequencyOcGetTjMaxHandler;
    outHandlers[ZesFrequencyOcSetTjMaxRpcM::messageSubtype] = zesFrequencyOcSetTjMaxHandler;
    outHandlers[ZesDeviceEnumEngineGroupsRpcM::messageSubtype] = zesDeviceEnumEngineGroupsHandler;
    outHandlers[ZesDeviceEnumSchedulersRpcM::messageSubtype] = zesDeviceEnumSchedulersHandler;
    outHandlers[ZesSchedulerGetPropertiesRpcM::messageSubtype] = zesSchedulerGetPropertiesHandler;
    outHandlers[ZesSchedulerGetCurrentModeRpcM::messageSubtype] = zesSchedulerGetCurrentModeHandler;
    outHandlers[ZesSchedulerGetTimeoutModePropertiesRpcM::messageSubtype] = zesSchedulerGetTimeoutModePropertiesHandler;
    outHandlers[ZesSchedulerGetTimesliceModePropertiesRpcM::messageSubtype] = zesSchedulerGetTimesliceModePropertiesHandler;
    outHandlers[ZesSchedulerSetTimeoutModeRpcM::messageSubtype] = zesSchedulerSetTimeoutModeHandler;
    outHandlers[ZesSchedulerSetTimesliceModeRpcM::messageSubtype] = zesSchedulerSetTimesliceModeHandler;
    outHandlers[ZesSchedulerSetExclusiveModeRpcM::messageSubtype] = zesSchedulerSetExclusiveModeHandler;
    outHandlers[ZesSchedulerSetComputeUnitDebugModeRpcM::messageSubtype] = zesSchedulerSetComputeUnitDebugModeHandler;
    outHandlers[ZesEngineGetPropertiesRpcM::messageSubtype] = zesEngineGetPropertiesHandler;
    outHandlers[ZesEngineGetActivityRpcM::messageSubtype] = zesEngineGetActivityHandler;
    outHandlers[ZesDeviceGetStateRpcM::messageSubtype] = zesDeviceGetStateHandler;
    outHandlers[ZesDeviceProcessesGetStateRpcM::messageSubtype] = zesDeviceProcessesGetStateHandler;
    outHandlers[ZesDevicePciGetPropertiesRpcM::messageSubtype] = zesDevicePciGetPropertiesHandler;
    outHandlers[ZesDevicePciGetStateRpcM::messageSubtype] = zesDevicePciGetStateHandler;
    outHandlers[ZesDevicePciGetBarsRpcM::messageSubtype] = zesDevicePciGetBarsHandler;
    outHandlers[ZesDevicePciGetStatsRpcM::messageSubtype] = zesDevicePciGetStatsHandler;
    outHandlers[ZesDeviceGetPropertiesRpcM::messageSubtype] = zesDeviceGetPropertiesHandler;
    outHandlers[ZesDeviceEnumMemoryModulesRpcM::messageSubtype] = zesDeviceEnumMemoryModulesHandler;
    outHandlers[ZeInitRpcM::messageSubtype] = zeInitHandler;
    outHandlers[ZeCommandListAppendMemoryRangesBarrierRpcM::messageSubtype] = zeCommandListAppendMemoryRangesBarrierHandler;
    outHandlers[ZeContextSystemBarrierRpcM::messageSubtype] = zeContextSystemBarrierHandler;
    outHandlers[ZeCommandListCreateRpcM::messageSubtype] = zeCommandListCreateHandler;
    outHandlers[ZeCommandListCreateImmediateRpcM::messageSubtype] = zeCommandListCreateImmediateHandler;
    outHandlers[ZeCommandListDestroyRpcM::messageSubtype] = zeCommandListDestroyHandler;
    outHandlers[ZeCommandListCloseRpcM::messageSubtype] = zeCommandListCloseHandler;
    outHandlers[ZeCommandListResetRpcM::messageSubtype] = zeCommandListResetHandler;
    outHandlers[ZeCommandListAppendWriteGlobalTimestampRpcM::messageSubtype] = zeCommandListAppendWriteGlobalTimestampHandler;
    outHandlers[ZeCommandQueueCreateRpcM::messageSubtype] = zeCommandQueueCreateHandler;
    outHandlers[ZeCommandQueueDestroyRpcM::messageSubtype] = zeCommandQueueDestroyHandler;
    outHandlers[ZeCommandQueueExecuteCommandListsRpcM::messageSubtype] = zeCommandQueueExecuteCommandListsHandler;
    outHandlers[ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::messageSubtype] = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelperHandler;
    outHandlers[ZeCommandQueueSynchronizeRpcM::messageSubtype] = zeCommandQueueSynchronizeHandler;
    outHandlers[ZeContextCreateRpcM::messageSubtype] = zeContextCreateHandler;
    outHandlers[ZeContextCreateExRpcM::messageSubtype] = zeContextCreateExHandler;
    outHandlers[ZeContextDestroyRpcM::messageSubtype] = zeContextDestroyHandler;
    outHandlers[ZeContextGetStatusRpcM::messageSubtype] = zeContextGetStatusHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferredRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferredHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronousRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronousHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperUsm2UsmHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperUsm2MallocHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperMalloc2UsmHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperMalloc2MallocHandler;
    outHandlers[ZeCommandListAppendMemoryPrefetchRpcM::messageSubtype] = zeCommandListAppendMemoryPrefetchHandler;
    outHandlers[ZeDeviceGetRpcM::messageSubtype] = zeDeviceGetHandler;
    outHandlers[ZeDeviceGetSubDevicesRpcM::messageSubtype] = zeDeviceGetSubDevicesHandler;
    outHandlers[ZeDeviceGetPropertiesRpcM::messageSubtype] = zeDeviceGetPropertiesHandler;
    outHandlers[ZeDeviceGetComputePropertiesRpcM::messageSubtype] = zeDeviceGetComputePropertiesHandler;
    outHandlers[ZeDeviceGetModulePropertiesRpcM::messageSubtype] = zeDeviceGetModulePropertiesHandler;
    outHandlers[ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype] = zeDeviceGetCommandQueueGroupPropertiesHandler;
    outHandlers[ZeDeviceGetMemoryPropertiesRpcM::messageSubtype] = zeDeviceGetMemoryPropertiesHandler;
    outHandlers[ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype] = zeDeviceGetMemoryAccessPropertiesHandler;
    outHandlers[ZeDeviceGetCachePropertiesRpcM::messageSubtype] = zeDeviceGetCachePropertiesHandler;
    outHandlers[ZeDeviceGetImagePropertiesRpcM::messageSubtype] = zeDeviceGetImagePropertiesHandler;
    outHandlers[ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype] = zeDeviceGetExternalMemoryPropertiesHandler;
    outHandlers[ZeDeviceGetP2PPropertiesRpcM::messageSubtype] = zeDeviceGetP2PPropertiesHandler;
    outHandlers[ZeDeviceCanAccessPeerRpcM::messageSubtype] = zeDeviceCanAccessPeerHandler;
    outHandlers[ZeDeviceGetStatusRpcM::messageSubtype] = zeDeviceGetStatusHandler;
    outHandlers[ZeDeviceGetGlobalTimestampsRpcM::messageSubtype] = zeDeviceGetGlobalTimestampsHandler;
    outHandlers[ZeDeviceReserveCacheExtRpcM::messageSubtype] = zeDeviceReserveCacheExtHandler;
    outHandlers[ZeDeviceSetCacheAdviceExtRpcM::messageSubtype] = zeDeviceSetCacheAdviceExtHandler;
    outHandlers[ZeDriverGetRpcM::messageSubtype] = zeDriverGetHandler;
    outHandlers[ZeDriverGetApiVersionRpcM::messageSubtype] = zeDriverGetApiVersionHandler;
    outHandlers[ZeDriverGetPropertiesRpcM::messageSubtype] = zeDriverGetPropertiesHandler;
    outHandlers[ZeDriverGetIpcPropertiesRpcM::messageSubtype] = zeDriverGetIpcPropertiesHandler;
    outHandlers[ZeDriverGetExtensionPropertiesRpcM::messageSubtype] = zeDriverGetExtensionPropertiesHandler;
    outHandlers[ZeEventPoolCreateRpcM::messageSubtype] = zeEventPoolCreateHandler;
    outHandlers[ZeEventPoolDestroyRpcM::messageSubtype] = zeEventPoolDestroyHandler;
    outHandlers[ZeEventCreateRpcM::messageSubtype] = zeEventCreateHandler;
    outHandlers[ZeEventDestroyRpcM::messageSubtype] = zeEventDestroyHandler;
    outHandlers[ZeEventPoolGetIpcHandleRpcM::messageSubtype] = zeEventPoolGetIpcHandleHandler;
    outHandlers[ZeEventPoolOpenIpcHandleRpcM::messageSubtype] = zeEventPoolOpenIpcHandleHandler;
    outHandlers[ZeEventPoolCloseIpcHandleRpcM::messageSubtype] = zeEventPoolCloseIpcHandleHandler;
    outHandlers[ZeCommandListAppendBarrierRpcM::messageSubtype] = zeCommandListAppendBarrierHandler;
    outHandlers[ZeCommandListAppendSignalEventRpcM::messageSubtype] = zeCommandListAppendSignalEventHandler;
    outHandlers[ZeCommandListAppendWaitOnEventsRpcM::messageSubtype] = zeCommandListAppendWaitOnEventsHandler;
    outHandlers[ZeEventHostSignalRpcM::messageSubtype] = zeEventHostSignalHandler;
    outHandlers[ZeEventHostSynchronizeRpcM::messageSubtype] = zeEventHostSynchronizeHandler;
    outHandlers[ZeEventQueryStatusRpcM::messageSubtype] = zeEventQueryStatusHandler;
    outHandlers[ZeCommandListAppendEventResetRpcM::messageSubtype] = zeCommandListAppendEventResetHandler;
    outHandlers[ZeEventHostResetRpcM::messageSubtype] = zeEventHostResetHandler;
    outHandlers[ZeEventQueryKernelTimestampRpcM::messageSubtype] = zeEventQueryKernelTimestampHandler;
    outHandlers[ZeCommandListAppendQueryKernelTimestampsRpcM::messageSubtype] = zeCommandListAppendQueryKernelTimestampsHandler;
    outHandlers[ZeEventQueryTimestampsExpRpcM::messageSubtype] = zeEventQueryTimestampsExpHandler;
    outHandlers[ZeEventQueryKernelTimestampsExtRpcHelperRpcM::messageSubtype] = zeEventQueryKernelTimestampsExtRpcHelperHandler;
    outHandlers[ZeFabricVertexGetExpRpcM::messageSubtype] = zeFabricVertexGetExpHandler;
    outHandlers[ZeFabricVertexGetSubVerticesExpRpcM::messageSubtype] = zeFabricVertexGetSubVerticesExpHandler;
    outHandlers[ZeFabricVertexGetPropertiesExpRpcM::messageSubtype] = zeFabricVertexGetPropertiesExpHandler;
    outHandlers[ZeFabricVertexGetDeviceExpRpcM::messageSubtype] = zeFabricVertexGetDeviceExpHandler;
    outHandlers[ZeDeviceGetFabricVertexExpRpcM::messageSubtype] = zeDeviceGetFabricVertexExpHandler;
    outHandlers[ZeFabricEdgeGetExpRpcM::messageSubtype] = zeFabricEdgeGetExpHandler;
    outHandlers[ZeFabricEdgeGetVerticesExpRpcM::messageSubtype] = zeFabricEdgeGetVerticesExpHandler;
    outHandlers[ZeFabricEdgeGetPropertiesExpRpcM::messageSubtype] = zeFabricEdgeGetPropertiesExpHandler;
    outHandlers[ZeFenceCreateRpcM::messageSubtype] = zeFenceCreateHandler;
    outHandlers[ZeFenceDestroyRpcM::messageSubtype] = zeFenceDestroyHandler;
    outHandlers[ZeFenceHostSynchronizeRpcM::messageSubtype] = zeFenceHostSynchronizeHandler;
    outHandlers[ZeFenceQueryStatusRpcM::messageSubtype] = zeFenceQueryStatusHandler;
    outHandlers[ZeFenceResetRpcM::messageSubtype] = zeFenceResetHandler;
    outHandlers[ZeKernelSetGlobalOffsetExpRpcM::messageSubtype] = zeKernelSetGlobalOffsetExpHandler;
    outHandlers[ZeImageGetPropertiesRpcM::messageSubtype] = zeImageGetPropertiesHandler;
    outHandlers[ZeImageCreateRpcM::messageSubtype] = zeImageCreateHandler;
    outHandlers[ZeImageDestroyRpcM::messageSubtype] = zeImageDestroyHandler;
    outHandlers[ZeKernelSchedulingHintExpRpcM::messageSubtype] = zeKernelSchedulingHintExpHandler;
    outHandlers[ZeMemAllocSharedRpcM::messageSubtype] = zeMemAllocSharedHandler;
    outHandlers[ZeMemAllocDeviceRpcM::messageSubtype] = zeMemAllocDeviceHandler;
    outHandlers[ZeMemAllocHostRpcM::messageSubtype] = zeMemAllocHostHandler;
    outHandlers[ZeMemFreeRpcM::messageSubtype] = zeMemFreeHandler;
    outHandlers[ZeMemGetAllocPropertiesRpcM::messageSubtype] = zeMemGetAllocPropertiesHandler;
    outHandlers[ZeMemGetAddressRangeRpcM::messageSubtype] = zeMemGetAddressRangeHandler;
    outHandlers[ZeMemGetIpcHandleRpcM::messageSubtype] = zeMemGetIpcHandleHandler;
    outHandlers[ZeMemOpenIpcHandleRpcM::messageSubtype] = zeMemOpenIpcHandleHandler;
    outHandlers[ZeMemCloseIpcHandleRpcM::messageSubtype] = zeMemCloseIpcHandleHandler;
    outHandlers[ZexMemGetIpcHandlesRpcM::messageSubtype] = zexMemGetIpcHandlesHandler;
    outHandlers[ZexMemOpenIpcHandlesRpcM::messageSubtype] = zexMemOpenIpcHandlesHandler;
    outHandlers[ZeMemFreeExtRpcM::messageSubtype] = zeMemFreeExtHandler;
    outHandlers[ZeModuleCreateRpcM::messageSubtype] = zeModuleCreateHandler;
    outHandlers[ZeModuleDestroyRpcM::messageSubtype] = zeModuleDestroyHandler;
    outHandlers[ZeModuleDynamicLinkRpcM::messageSubtype] = zeModuleDynamicLinkHandler;
    outHandlers[ZeModuleBuildLogDestroyRpcM::messageSubtype] = zeModuleBuildLogDestroyHandler;
    outHandlers[ZeModuleBuildLogGetStringRpcM::messageSubtype] = zeModuleBuildLogGetStringHandler;
    outHandlers[ZeModuleGetNativeBinaryRpcM::messageSubtype] = zeModuleGetNativeBinaryHandler;
    outHandlers[ZeModuleGetGlobalPointerRpcM::messageSubtype] = zeModuleGetGlobalPointerHandler;
    outHandlers[ZeModuleGetKernelNamesRpcHelperRpcM::messageSubtype] = zeModuleGetKernelNamesRpcHelperHandler;
    outHandlers[ZeModuleGetPropertiesRpcM::messageSubtype] = zeModuleGetPropertiesHandler;
    outHandlers[ZeKernelCreateRpcM::messageSubtype] = zeKernelCreateHandler;
    outHandlers[ZeKernelDestroyRpcM::messageSubtype] = zeKernelDestroyHandler;
    outHandlers[ZeModuleGetFunctionPointerRpcM::messageSubtype] = zeModuleGetFunctionPointerHandler;
    outHandlers[ZeKernelSetGroupSizeRpcM::messageSubtype] = zeKernelSetGroupSizeHandler;
    outHandlers[ZeKernelSuggestGroupSizeRpcM::messageSubtype] = zeKernelSuggestGroupSizeHandler;
    outHandlers[ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype] = zeKernelSuggestMaxCooperativeGroupCountHandler;
    outHandlers[ZeKernelSetArgumentValueRpcM::messageSubtype] = zeKernelSetArgumentValueHandler;
    outHandlers[ZeKernelSetIndirectAccessRpcM::messageSubtype] = zeKernelSetIndirectAccessHandler;
    outHandlers[ZeKernelGetIndirectAccessRpcM::messageSubtype] = zeKernelGetIndirectAccessHandler;
    outHandlers[ZeKernelSetCacheConfigRpcM::messageSubtype] = zeKernelSetCacheConfigHandler;
    outHandlers[ZeKernelGetPropertiesRpcM::messageSubtype] = zeKernelGetPropertiesHandler;
    outHandlers[ZeKernelGetNameRpcM::messageSubtype] = zeKernelGetNameHandler;
    outHandlers[ZeCommandListAppendLaunchKernelRpcM::messageSubtype] = zeCommandListAppendLaunchKernelHandler;
    outHandlers[ZeCommandListAppendLaunchCooperativeKernelRpcM::messageSubtype] = zeCommandListAppendLaunchCooperativeKernelHandler;
    outHandlers[ZeCommandListAppendLaunchKernelIndirectRpcM::messageSubtype] = zeCommandListAppendLaunchKernelIndirectHandler;
    outHandlers[ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM::messageSubtype] = zeCommandListAppendLaunchMultipleKernelsIndirectHandler;
    outHandlers[ZeCommandListHostSynchronizeRpcM::messageSubtype] = zeCommandListHostSynchronizeHandler;
    outHandlers[ZeDevicePciGetPropertiesExtRpcM::messageSubtype] = zeDevicePciGetPropertiesExtHandler;
    outHandlers[ZeContextMakeMemoryResidentRpcM::messageSubtype] = zeContextMakeMemoryResidentHandler;
    outHandlers[ZeContextEvictMemoryRpcM::messageSubtype] = zeContextEvictMemoryHandler;
    outHandlers[ZeVirtualMemReserveRpcM::messageSubtype] = zeVirtualMemReserveHandler;
    outHandlers[ZeVirtualMemFreeRpcM::messageSubtype] = zeVirtualMemFreeHandler;
    outHandlers[ZeVirtualMemQueryPageSizeRpcM::messageSubtype] = zeVirtualMemQueryPageSizeHandler;
    outHandlers[ZePhysicalMemCreateRpcM::messageSubtype] = zePhysicalMemCreateHandler;
    outHandlers[ZePhysicalMemDestroyRpcM::messageSubtype] = zePhysicalMemDestroyHandler;
    outHandlers[ZeVirtualMemMapRpcM::messageSubtype] = zeVirtualMemMapHandler;
    outHandlers[ZeVirtualMemUnmapRpcM::messageSubtype] = zeVirtualMemUnmapHandler;
    outHandlers[ZeVirtualMemSetAccessAttributeRpcM::messageSubtype] = zeVirtualMemSetAccessAttributeHandler;
    outHandlers[ZeVirtualMemGetAccessAttributeRpcM::messageSubtype] = zeVirtualMemGetAccessAttributeHandler;
    outHandlers[ZexDriverImportExternalPointerRpcM::messageSubtype] = zexDriverImportExternalPointerHandler;
    outHandlers[ZexDriverReleaseImportedPointerRpcM::messageSubtype] = zexDriverReleaseImportedPointerHandler;
    outHandlers[ZexDriverGetHostPointerBaseAddressRpcM::messageSubtype] = zexDriverGetHostPointerBaseAddressHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Usm_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Usm_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Usm_RemappedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Shared_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Shared_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Shared_RemappedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Remapped_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Remapped_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyDeferred_Remapped_RemappedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Local_LocalHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Local_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Local_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Usm_LocalHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Usm_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Usm_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Shared_LocalHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Shared_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediate_Shared_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::messageSubtype] = zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedHandler;
}

inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceReset(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.force
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceResetExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceResetExt(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumPowerDomainsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumPowerDomains(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phPower
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceGetCardPowerDomainRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceGetCardPowerDomain(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.phPower
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetProperties(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerGetEnergyCounterRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetEnergyCounter(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pEnergy
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerGetLimitsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetLimits(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pSustained, 
                                                apiCommand.args.pBurst, 
                                                apiCommand.args.pPeak
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerSetLimitsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerSetLimits(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pSustained, 
                                                apiCommand.args.pBurst, 
                                                apiCommand.args.pPeak
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerGetLimitsExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetLimitsExt(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pSustained
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerSetLimitsExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerSetLimitsExt(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pSustained
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerGetEnergyThresholdRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerGetEnergyThreshold(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pThreshold
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesPowerSetEnergyThresholdRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesPowerSetEnergyThreshold(
                                                apiCommand.args.hPower, 
                                                apiCommand.args.pThreshold
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEventRegisterRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEventRegister(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.events
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDriverEventListenRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDriverEventListen(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.timeout, 
                                                apiCommand.args.count, 
                                                apiCommand.args.phDevices, 
                                                apiCommand.args.pNumDeviceEvents, 
                                                apiCommand.args.pEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDriverEventListenExRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDriverEventListenEx(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.timeout, 
                                                apiCommand.args.count, 
                                                apiCommand.args.phDevices, 
                                                apiCommand.args.pNumDeviceEvents, 
                                                apiCommand.args.pEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumTemperatureSensorsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumTemperatureSensors(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phTemperature
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesTemperatureGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureGetProperties(
                                                apiCommand.args.hTemperature, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesTemperatureGetConfigRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureGetConfig(
                                                apiCommand.args.hTemperature, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesTemperatureSetConfigRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureSetConfig(
                                                apiCommand.args.hTemperature, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesTemperatureGetStateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesTemperatureGetState(
                                                apiCommand.args.hTemperature, 
                                                apiCommand.args.pTemperature
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumRasErrorSetsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumRasErrorSets(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phRas
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesRasGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasGetProperties(
                                                apiCommand.args.hRas, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesRasGetConfigRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasGetConfig(
                                                apiCommand.args.hRas, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesRasSetConfigRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasSetConfig(
                                                apiCommand.args.hRas, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesRasGetStateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesRasGetState(
                                                apiCommand.args.hRas, 
                                                apiCommand.args.clear, 
                                                apiCommand.args.pState
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumFrequencyDomainsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumFrequencyDomains(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phFrequency
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetProperties(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyGetAvailableClocksRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetAvailableClocks(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phFrequency
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyGetRangeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetRange(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencySetRangeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencySetRange(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pLimits
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyGetStateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetState(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pState
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyGetThrottleTimeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyGetThrottleTime(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pThrottleTime
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcGetCapabilitiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetCapabilities(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pOcCapabilities
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcGetVoltageTargetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetVoltageTarget(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pCurrentVoltageTarget, 
                                                apiCommand.args.pCurrentVoltageOffset
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcSetVoltageTargetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetVoltageTarget(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.CurrentVoltageTarget, 
                                                apiCommand.args.CurrentVoltageOffset
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcSetModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetMode(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.CurrentOcMode
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcGetModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetMode(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pCurrentOcMode
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcGetIccMaxRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetIccMax(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pOcIccMax
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcSetIccMaxRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetIccMax(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.ocIccMax
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcGetTjMaxRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcGetTjMax(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.pOcTjMax
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesFrequencyOcSetTjMaxRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesFrequencyOcSetTjMax(
                                                apiCommand.args.hFrequency, 
                                                apiCommand.args.ocTjMax
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumEngineGroupsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumEngineGroups(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phEngine
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumSchedulersRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumSchedulers(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phScheduler
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetProperties(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerGetCurrentModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetCurrentMode(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.pMode
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerGetTimeoutModePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetTimeoutModeProperties(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.getDefaults, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerGetTimesliceModePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerGetTimesliceModeProperties(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.getDefaults, 
                                                apiCommand.args.pConfig
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerSetTimeoutModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetTimeoutMode(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.pProperties, 
                                                apiCommand.args.pNeedReload
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerSetTimesliceModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetTimesliceMode(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.pProperties, 
                                                apiCommand.args.pNeedReload
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerSetExclusiveModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetExclusiveMode(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.pNeedReload
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesSchedulerSetComputeUnitDebugModeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesSchedulerSetComputeUnitDebugMode(
                                                apiCommand.args.hScheduler, 
                                                apiCommand.args.pNeedReload
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesEngineGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesEngineGetProperties(
                                                apiCommand.args.hEngine, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesEngineGetActivityRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesEngineGetActivity(
                                                apiCommand.args.hEngine, 
                                                apiCommand.args.pStats
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceGetStateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceGetState(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pState
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceProcessesGetStateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceProcessesGetState(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pProcesses
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDevicePciGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDevicePciGetStateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetState(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pState
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDevicePciGetBarsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetBars(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDevicePciGetStatsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDevicePciGetStats(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pStats
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceGetProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZesDeviceEnumMemoryModulesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zesDeviceEnumMemoryModules(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phMemory
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeInitRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeInit(
                                                apiCommand.args.flags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryRangesBarrierRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryRangesBarrier(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.numRanges, 
                                                apiCommand.args.pRangeSizes, 
                                                apiCommand.args.pRanges, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextSystemBarrierRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextSystemBarrier(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreateImmediate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.altdesc, 
                                                apiCommand.args.phCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListDestroy(
                                                apiCommand.args.hCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListCloseRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListClose(
                                                apiCommand.args.hCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListReset(
                                                apiCommand.args.hCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendWriteGlobalTimestampRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendWriteGlobalTimestamp(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phCommandQueue
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueDestroy(
                                                apiCommand.args.hCommandQueue
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueExecuteCommandLists(
                                                apiCommand.args.hCommandQueue, 
                                                apiCommand.args.numCommandLists, 
                                                apiCommand.args.phCommandLists, 
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueSynchronize(
                                                apiCommand.args.hCommandQueue, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreate(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextCreateExRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreateEx(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.numDevices, 
                                                apiCommand.args.phDevices, 
                                                apiCommand.args.phContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextDestroy(
                                                apiCommand.args.hContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextGetStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextGetStatus(
                                                apiCommand.args.hContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferredRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronousRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryPrefetchRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryPrefetch(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phDevices
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetSubDevices(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phSubdevices
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pDeviceProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetComputeProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pComputeProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetModuleProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pModuleProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCommandQueueGroupProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pCommandQueueGroupProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pMemProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryAccessProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pMemAccessProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCacheProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pCacheProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetImageProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pImageProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetExternalMemoryProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pExternalMemoryProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetP2PProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.hPeerDevice, 
                                                apiCommand.args.pP2PProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceCanAccessPeer(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.hPeerDevice, 
                                                apiCommand.args.value
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetStatus(
                                                apiCommand.args.hDevice
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetGlobalTimestamps(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.hostTimestamp, 
                                                apiCommand.args.deviceTimestamp
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceReserveCacheExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceReserveCacheExt(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.cacheLevel, 
                                                apiCommand.args.cacheReservationSize
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceSetCacheAdviceExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceSetCacheAdviceExt(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.regionSize, 
                                                apiCommand.args.cacheRegion
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGet(
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phDrivers
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetApiVersion(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.version
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetProperties(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pDriverProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetIpcProperties(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pIpcProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetExtensionProperties(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pExtensionProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.numDevices, 
                                                apiCommand.args.phDevices, 
                                                apiCommand.args.phEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolDestroy(
                                                apiCommand.args.hEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventCreate(
                                                apiCommand.args.hEventPool, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventDestroy(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolGetIpcHandle(
                                                apiCommand.args.hEventPool, 
                                                apiCommand.args.phIpc
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolOpenIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hIpc, 
                                                apiCommand.args.phEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCloseIpcHandle(
                                                apiCommand.args.hEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendBarrier(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendSignalEvent(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendWaitOnEvents(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.numEvents, 
                                                apiCommand.args.phEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventHostSignalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSignal(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSynchronize(
                                                apiCommand.args.hEvent, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryStatus(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendEventReset(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventHostResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostReset(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryKernelTimestamp(
                                                apiCommand.args.hEvent, 
                                                apiCommand.args.dstptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendQueryKernelTimestampsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendQueryKernelTimestamps(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.numEvents, 
                                                apiCommand.args.phEvents, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.pOffsets, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventQueryTimestampsExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryTimestampsExp(
                                                apiCommand.args.hEvent, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pTimestamps
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricVertexGetExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetExp(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phVertices
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricVertexGetSubVerticesExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetSubVerticesExp(
                                                apiCommand.args.hVertex, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phSubvertices
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricVertexGetPropertiesExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetPropertiesExp(
                                                apiCommand.args.hVertex, 
                                                apiCommand.args.pVertexProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricVertexGetDeviceExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricVertexGetDeviceExp(
                                                apiCommand.args.hVertex, 
                                                apiCommand.args.pDevice
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetFabricVertexExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetFabricVertexExp(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pVertex
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricEdgeGetExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricEdgeGetExp(
                                                apiCommand.args.hVertexA, 
                                                apiCommand.args.hVertexB, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phEdges
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricEdgeGetVerticesExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricEdgeGetVerticesExp(
                                                apiCommand.args.hEdge, 
                                                apiCommand.args.phVertexA, 
                                                apiCommand.args.phVertexB
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFabricEdgeGetPropertiesExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFabricEdgeGetPropertiesExp(
                                                apiCommand.args.hEdge, 
                                                apiCommand.args.pEdgeProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceCreate(
                                                apiCommand.args.hCommandQueue, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceDestroy(
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceHostSynchronize(
                                                apiCommand.args.hFence, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceQueryStatus(
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceReset(
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGlobalOffsetExp(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.offsetX, 
                                                apiCommand.args.offsetY, 
                                                apiCommand.args.offsetZ
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageGetProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.pImageProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeImageCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phImage
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeImageDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageDestroy(
                                                apiCommand.args.hImage
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSchedulingHintExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSchedulingHintExp(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pHint
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocShared(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.device_desc, 
                                                apiCommand.args.host_desc, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocDevice(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.device_desc, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemAllocHostRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocHost(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.host_desc, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemFreeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemFree(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAllocProperties(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pMemAllocProperties, 
                                                apiCommand.args.phDevice
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAddressRange(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pBase, 
                                                apiCommand.args.pSize
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pIpcHandle
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemOpenIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.handle, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemCloseIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemGetIpcHandles(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.numIpcHandles, 
                                                apiCommand.args.pIpcHandles
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemOpenIpcHandles(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.numIpcHandles, 
                                                apiCommand.args.pIpcHandles, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemFreeExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemFreeExt(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.pMemFreeDesc, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phModule, 
                                                apiCommand.args.phBuildLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDestroy(
                                                apiCommand.args.hModule
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDynamicLink(
                                                apiCommand.args.numModules, 
                                                apiCommand.args.phModules, 
                                                apiCommand.args.phLinkLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogDestroy(
                                                apiCommand.args.hModuleBuildLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogGetString(
                                                apiCommand.args.hModuleBuildLog, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pBuildLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetNativeBinary(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pModuleNativeBinary
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetGlobalPointer(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pGlobalName, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetProperties(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pModuleProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelCreate(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phKernel
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelDestroy(
                                                apiCommand.args.hKernel
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetFunctionPointer(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pFunctionName, 
                                                apiCommand.args.pfnFunction
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGroupSize(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.groupSizeX, 
                                                apiCommand.args.groupSizeY, 
                                                apiCommand.args.groupSizeZ
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestGroupSize(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.globalSizeX, 
                                                apiCommand.args.globalSizeY, 
                                                apiCommand.args.globalSizeZ, 
                                                apiCommand.args.groupSizeX, 
                                                apiCommand.args.groupSizeY, 
                                                apiCommand.args.groupSizeZ
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestMaxCooperativeGroupCount(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.totalGroupCount
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetArgumentValue(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.argIndex, 
                                                apiCommand.args.argSize, 
                                                apiCommand.args.pArgValue
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetIndirectAccess(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.flags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetIndirectAccess(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pFlags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetCacheConfig(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.flags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetProperties(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pKernelProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelGetNameRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetName(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pName
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernel(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pLaunchFuncArgs, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendLaunchCooperativeKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchCooperativeKernel(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pLaunchFuncArgs, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernelIndirect(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pLaunchArgumentsBuffer, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchMultipleKernelsIndirect(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.numKernels, 
                                                apiCommand.args.phKernels, 
                                                apiCommand.args.pCountBuffer, 
                                                apiCommand.args.pLaunchArgumentsBuffer, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListHostSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListHostSynchronize(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDevicePciGetPropertiesExt(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pPciProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextMakeMemoryResidentRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextMakeMemoryResident(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextEvictMemoryRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextEvictMemory(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemReserveRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemReserve(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.pStart, 
                                                apiCommand.args.size, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemFreeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemFree(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemQueryPageSizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemQueryPageSize(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.size, 
                                                apiCommand.args.pagesize
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZePhysicalMemCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zePhysicalMemCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phPhysicalMemory
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZePhysicalMemDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zePhysicalMemDestroy(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hPhysicalMemory
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemMapRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemMap(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hPhysicalMemory, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.access
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemUnmapRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemUnmap(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemSetAccessAttributeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemSetAccessAttribute(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.access
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeVirtualMemGetAccessAttributeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeVirtualMemGetAccessAttribute(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.access, 
                                                apiCommand.args.outSize
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexDriverImportExternalPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexDriverImportExternalPointer(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexDriverReleaseImportedPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexDriverReleaseImportedPointer(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexDriverGetHostPointerBaseAddressRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexDriverGetHostPointerBaseAddress(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.baseAddress
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}

inline bool callDirectly(Cal::Rpc::RpcMessageHeader *command) {
    if(nullptr == command){
        log<Verbosity::debug>("Tried to call directly with empty command message header");
        return false;
    }
    if(command->type != Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero){
        log<Verbosity::debug>("Tried to call directly %d message type as LevelZero", command->type);
        return false;
    }
    switch(command->subtype){
        default:
            log<Verbosity::debug>("Tried to call directly unknown message subtype %d", command->subtype);
            return false;
        case Cal::Rpc::LevelZero::ZesDeviceResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceResetExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceResetExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumPowerDomainsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumPowerDomainsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceGetCardPowerDomainRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceGetCardPowerDomainRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerGetEnergyCounterRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetEnergyCounterRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerGetLimitsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetLimitsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerSetLimitsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerSetLimitsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerGetLimitsExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetLimitsExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerSetLimitsExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerSetLimitsExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerGetEnergyThresholdRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerGetEnergyThresholdRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesPowerSetEnergyThresholdRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesPowerSetEnergyThresholdRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEventRegisterRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEventRegisterRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDriverEventListenRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDriverEventListenRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDriverEventListenExRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDriverEventListenExRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumTemperatureSensorsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumTemperatureSensorsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesTemperatureGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesTemperatureGetConfigRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureGetConfigRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesTemperatureSetConfigRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureSetConfigRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesTemperatureGetStateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesTemperatureGetStateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumRasErrorSetsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumRasErrorSetsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesRasGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesRasGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesRasGetConfigRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesRasGetConfigRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesRasSetConfigRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesRasSetConfigRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesRasGetStateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesRasGetStateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumFrequencyDomainsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumFrequencyDomainsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyGetAvailableClocksRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetAvailableClocksRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyGetRangeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetRangeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencySetRangeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencySetRangeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyGetStateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetStateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyGetThrottleTimeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyGetThrottleTimeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcGetCapabilitiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetCapabilitiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcGetVoltageTargetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetVoltageTargetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcSetVoltageTargetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetVoltageTargetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcSetModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcGetModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcGetIccMaxRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetIccMaxRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcSetIccMaxRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetIccMaxRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcGetTjMaxRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcGetTjMaxRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesFrequencyOcSetTjMaxRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesFrequencyOcSetTjMaxRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumEngineGroupsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumEngineGroupsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumSchedulersRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumSchedulersRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerGetCurrentModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetCurrentModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerGetTimeoutModePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetTimeoutModePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerGetTimesliceModePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerGetTimesliceModePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerSetTimeoutModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetTimeoutModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerSetTimesliceModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetTimesliceModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerSetExclusiveModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetExclusiveModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesSchedulerSetComputeUnitDebugModeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesSchedulerSetComputeUnitDebugModeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesEngineGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesEngineGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesEngineGetActivityRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesEngineGetActivityRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceGetStateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceGetStateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceProcessesGetStateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceProcessesGetStateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDevicePciGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDevicePciGetStateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetStateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDevicePciGetBarsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetBarsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDevicePciGetStatsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDevicePciGetStatsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZesDeviceEnumMemoryModulesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZesDeviceEnumMemoryModulesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeInitRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeInitRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryRangesBarrierRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryRangesBarrierRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextSystemBarrierRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextSystemBarrierRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListCloseRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCloseRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendWriteGlobalTimestampRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendWriteGlobalTimestampRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextCreateExRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateExRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextGetStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextGetStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferredRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferredRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronousRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronousRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryPrefetchRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryPrefetchRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceReserveCacheExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceReserveCacheExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceSetCacheAdviceExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceSetCacheAdviceExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventHostSignalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSignalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventHostResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendQueryKernelTimestampsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendQueryKernelTimestampsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventQueryTimestampsExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryTimestampsExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricVertexGetExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricVertexGetSubVerticesExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetSubVerticesExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricVertexGetPropertiesExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetPropertiesExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricVertexGetDeviceExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricVertexGetDeviceExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetFabricVertexExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetFabricVertexExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricEdgeGetExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricEdgeGetExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricEdgeGetVerticesExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricEdgeGetVerticesExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFabricEdgeGetPropertiesExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFabricEdgeGetPropertiesExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeImageCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeImageCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeImageDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeImageDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSchedulingHintExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSchedulingHintExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemAllocHostRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocHostRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemFreeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemFreeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemFreeExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemFreeExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelGetNameRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetNameRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendLaunchCooperativeKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchCooperativeKernelRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListHostSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListHostSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextMakeMemoryResidentRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextMakeMemoryResidentRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextEvictMemoryRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextEvictMemoryRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemReserveRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemReserveRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemFreeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemFreeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemQueryPageSizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemQueryPageSizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZePhysicalMemCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZePhysicalMemCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZePhysicalMemDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZePhysicalMemDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemMapRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemMapRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemUnmapRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemUnmapRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemSetAccessAttributeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemSetAccessAttributeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeVirtualMemGetAccessAttributeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeVirtualMemGetAccessAttributeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexDriverImportExternalPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexDriverImportExternalPointerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexDriverReleaseImportedPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexDriverReleaseImportedPointerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexDriverGetHostPointerBaseAddressRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexDriverGetHostPointerBaseAddressRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM*>(command)); break;
    }
    return true;
}

} // namespae LevelZero
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
