/*
 * Copyright (C) 2022-2024 Intel Corporation
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
#include "client/icd/level_zero/api_customization/icd_level_zero_api_tools.h"
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
ze_result_t zetMetricGroupGet (zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups);
ze_result_t zetMetricGroupGetProperties (zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties);
ze_result_t zetMetricGroupGetGlobalTimestampsExp (zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp);
ze_result_t zetMetricGroupGetExportDataExp (zet_metric_group_handle_t hMetricGroup, const uint8_t * pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t* pExportData);
ze_result_t zetMetricGroupCalculateMetricValues (zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues);
ze_result_t zetMetricGroupCalculateMultipleMetricValuesExp (zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues);
ze_result_t zetMetricGet (zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics);
ze_result_t zetMetricGetProperties (zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties);
ze_result_t zetContextActivateMetricGroups (zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups);
ze_result_t zetMetricStreamerOpen (zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer);
ze_result_t zetMetricStreamerReadData (zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData);
ze_result_t zetMetricStreamerReadDataRpcHelper (zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData);
ze_result_t zetMetricStreamerClose (zet_metric_streamer_handle_t hMetricStreamer);
ze_result_t zetMetricQueryPoolCreate (zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t * desc, zet_metric_query_pool_handle_t* phMetricQueryPool);
ze_result_t zetMetricQueryPoolDestroy (zet_metric_query_pool_handle_t hMetricQueryPool);
ze_result_t zetMetricQueryCreate (zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery);
ze_result_t zetMetricQueryDestroy (zet_metric_query_handle_t hMetricQuery);
ze_result_t zetMetricQueryReset (zet_metric_query_handle_t hMetricQuery);
ze_result_t zetMetricQueryGetData (zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData);
ze_result_t zetCommandListAppendMetricQueryBegin (zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery);
ze_result_t zetCommandListAppendMetricQueryEnd (zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zetCommandListAppendMetricMemoryBarrier (zet_command_list_handle_t hCommandList);
ze_result_t zetCommandListAppendMetricStreamerMarker (zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value);
ze_result_t zetTracerExpCreate (zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer);
ze_result_t zetTracerExpDestroy (zet_tracer_exp_handle_t hTracer);
ze_result_t zetTracerExpSetPrologues (zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs);
ze_result_t zetTracerExpSetEpilogues (zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs);
ze_result_t zetTracerExpSetEnabled (zet_tracer_exp_handle_t hTracer, ze_bool_t enable);
ze_result_t zetDeviceGetDebugProperties (ze_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties);
ze_result_t zetDebugAttach (ze_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug);
ze_result_t zetDebugDetach (zet_debug_session_handle_t hDebug);
ze_result_t zetKernelGetProfileInfo (ze_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties);
ze_result_t zesDeviceReset (zes_device_handle_t hDevice, ze_bool_t force);
ze_result_t zesDeviceResetExt (zes_device_handle_t hDevice, zes_reset_properties_t* pProperties);
ze_result_t zesDeviceEnumPowerDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower);
ze_result_t zesDeviceGetCardPowerDomain (zes_device_handle_t hDevice, zes_pwr_handle_t* phPower);
ze_result_t zesPowerGetProperties (zes_pwr_handle_t hPower, zes_power_properties_t* pProperties);
ze_result_t zesPowerGetEnergyCounter (zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy);
ze_result_t zesPowerGetLimits (zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak);
ze_result_t zesPowerSetLimits (zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak);
ze_result_t zesPowerGetLimitsExt (zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained);
ze_result_t zesPowerSetLimitsExt (zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained);
ze_result_t zesPowerGetEnergyThreshold (zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold);
ze_result_t zesPowerSetEnergyThreshold (zes_pwr_handle_t hPower, double pThreshold);
ze_result_t zesDeviceEventRegister (zes_device_handle_t hDevice, zes_event_type_flags_t events);
ze_result_t zesDriverEventListen (ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents);
ze_result_t zesDriverEventListenEx (ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents);
ze_result_t zesDeviceEnumTemperatureSensors (zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature);
ze_result_t zesTemperatureGetProperties (zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties);
ze_result_t zesTemperatureGetConfig (zes_temp_handle_t hTemperature, zes_temp_config_t * pConfig);
ze_result_t zesTemperatureSetConfig (zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig);
ze_result_t zesTemperatureGetState (zes_temp_handle_t hTemperature, double* pTemperature);
ze_result_t zesDeviceEnumRasErrorSets (zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas);
ze_result_t zesRasGetProperties (zes_ras_handle_t hRas, zes_ras_properties_t* pProperties);
ze_result_t zesRasGetConfig (zes_ras_handle_t hRas, zes_ras_config_t * pConfig);
ze_result_t zesRasSetConfig (zes_ras_handle_t hRas, const zes_ras_config_t* pConfig);
ze_result_t zesRasGetState (zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState);
ze_result_t zesDeviceEnumFrequencyDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency);
ze_result_t zesFrequencyGetProperties (zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties);
ze_result_t zesFrequencyGetAvailableClocks (zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency);
ze_result_t zesFrequencyGetRange (zes_freq_handle_t hFrequency, zes_freq_range_t* pConfig);
ze_result_t zesFrequencySetRange (zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits);
ze_result_t zesFrequencyGetState (zes_freq_handle_t hFrequency, zes_freq_state_t* pState);
ze_result_t zesFrequencyGetThrottleTime (zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime);
ze_result_t zesFrequencyOcGetCapabilities (zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities);
ze_result_t zesFrequencyOcGetVoltageTarget (zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset);
ze_result_t zesFrequencyOcSetVoltageTarget (zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset);
ze_result_t zesFrequencyOcSetMode (zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode);
ze_result_t zesFrequencyOcGetMode (zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode);
ze_result_t zesFrequencyOcGetIccMax (zes_freq_handle_t hFrequency, double* pOcIccMax);
ze_result_t zesFrequencyOcSetIccMax (zes_freq_handle_t hFrequency, double ocIccMax);
ze_result_t zesFrequencyOcGetTjMax (zes_freq_handle_t hFrequency, double* pOcTjMax);
ze_result_t zesFrequencyOcSetTjMax (zes_freq_handle_t hFrequency, double ocTjMax);
ze_result_t zesDeviceEnumEngineGroups (zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine);
ze_result_t zesDeviceEnumSchedulers (zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler);
ze_result_t zesSchedulerGetProperties (zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties);
ze_result_t zesSchedulerGetCurrentMode (zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode);
ze_result_t zesSchedulerGetTimeoutModeProperties (zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig);
ze_result_t zesSchedulerGetTimesliceModeProperties (zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig);
ze_result_t zesSchedulerSetTimeoutMode (zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload);
ze_result_t zesSchedulerSetTimesliceMode (zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload);
ze_result_t zesSchedulerSetExclusiveMode (zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload);
ze_result_t zesSchedulerSetComputeUnitDebugMode (zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload);
ze_result_t zesEngineGetProperties (zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties);
ze_result_t zesEngineGetActivity (zes_engine_handle_t hEngine, zes_engine_stats_t* pStats);
ze_result_t zesDeviceGetState (zes_device_handle_t hDevice, zes_device_state_t* pState);
ze_result_t zesDeviceProcessesGetStateRpcHelper (zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses);
ze_result_t zesDevicePciGetProperties (zes_device_handle_t hDevice, zes_pci_properties_t* pProperties);
ze_result_t zesDevicePciGetState (zes_device_handle_t hDevice, zes_pci_state_t* pState);
ze_result_t zesDevicePciGetBars (zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties);
ze_result_t zesDevicePciGetStats (zes_device_handle_t hDevice, zes_pci_stats_t* pStats);
ze_result_t zesDeviceGetPropertiesRpcHelper (zes_device_handle_t hDevice, zes_device_properties_t* pProperties);
ze_result_t zesDeviceEnumMemoryModules (zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory);
ze_result_t zesMemoryGetProperties (zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties);
ze_result_t zesMemoryGetState (zes_mem_handle_t hMemory, zes_mem_state_t* pState);
ze_result_t zesMemoryGetBandwidth (zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth);
ze_result_t zesDeviceEnumPerformanceFactorDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf);
ze_result_t zesPerformanceFactorGetProperties (zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties);
ze_result_t zesPerformanceFactorGetConfig (zes_perf_handle_t hPerf, double* pFactor);
ze_result_t zesPerformanceFactorSetConfig (zes_perf_handle_t hPerf, double pFactor);
ze_result_t zesDeviceEnumStandbyDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby);
ze_result_t zesStandbyGetProperties (zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties);
ze_result_t zesStandbyGetMode (zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode);
ze_result_t zesStandbySetMode (zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode);
ze_result_t zeInitRpcHelper (ze_init_flags_t flags);
ze_result_t zeCommandListAppendMemoryRangesBarrier (ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryRangesBarrier_WithTracing (ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
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
ze_result_t zeCommandQueueCreateRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
ze_result_t zeCommandQueueCreate_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue);
ze_result_t zeCommandQueueDestroy_WithTracing (ze_command_queue_handle_t hCommandQueue);
ze_result_t zeCommandQueueExecuteCommandListsRpcHelper (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeCommandQueueExecuteCommandLists_WithTracing (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::TransferDesc* transferDescs);
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper_WithTracing (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::TransferDesc* transferDescs);
ze_result_t zeCommandQueueSynchronizeRpcHelper (ze_command_queue_handle_t hCommandQueue, uint64_t timeout);
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
ze_result_t zeCommandListAppendMemoryCopyRegion (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegion_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContext (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContext_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
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
ze_result_t zeDriverGetLastErrorDescriptionRpcHelper (ze_driver_handle_t hDriver, const char** ppString);
ze_result_t zeDriverGetLastErrorDescriptionRpcHelper (ze_driver_handle_t hDriver, size_t stringLength, char* pString);
ze_result_t zeDriverGetLastErrorDescriptionRpcHelper_WithTracing (ze_driver_handle_t hDriver, size_t stringLength, char* pString);
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
ze_result_t zeEventHostSynchronizeRpcHelper (ze_event_handle_t hEvent, uint64_t timeout);
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
ze_result_t zeFabricVertexGetExp (ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices);
ze_result_t zeFabricVertexGetSubVerticesExp (ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices);
ze_result_t zeFabricVertexGetPropertiesExp (ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties);
ze_result_t zeFabricVertexGetDeviceExp (ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* pDevice);
ze_result_t zeDeviceGetFabricVertexExp (ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* pVertex);
ze_result_t zeFabricEdgeGetExp (ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges);
ze_result_t zeFabricEdgeGetVerticesExp (ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB);
ze_result_t zeFabricEdgeGetPropertiesExp (ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties);
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
ze_result_t zeModuleInspectLinkageExt (ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog);
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
ze_result_t zeMemPutIpcHandle (ze_context_handle_t hContext, ze_ipc_mem_handle_t handle);
ze_result_t zexMemGetIpcHandlesRpcHelper (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
ze_result_t zexMemGetIpcHandles_WithTracing (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
ze_result_t zexMemOpenIpcHandlesRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zexMemOpenIpcHandles_WithTracing (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
ze_result_t zeMemFreeExt (ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr);
ze_result_t zeMemGetFileDescriptorFromIpcHandleExp (ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t* pHandle);
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
ze_result_t zeKernelGetSourceAttributes (ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString);
ze_result_t zeKernelGetSourceAttributes_WithTracing (ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString);
ze_result_t zeKernelGetSourceAttributesRpcHelper (ze_kernel_handle_t hKernel, uint32_t* pSize, char* pString);
ze_result_t zeKernelGetSourceAttributesRpcHelper_WithTracing (ze_kernel_handle_t hKernel, uint32_t* pSize, char* pString);
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
ze_result_t zeCommandListAppendWriteGlobalTimestamp_Local (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendWriteGlobalTimestamp_Local_WithTracing (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendWriteGlobalTimestamp_Usm (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendWriteGlobalTimestamp_Usm_WithTracing (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendWriteGlobalTimestamp_Shared (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendWriteGlobalTimestamp_Shared_WithTracing (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Shared_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Remapped_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Remapped_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Remapped_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_Usm_WithTracing (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);

namespace Unimplemented {
inline void zeCommandListAppendImageCopyUnimpl() {
    Cal::Utils::signalAbort("Function CommandList.zeCommandListAppendImageCopy is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeCommandListAppendImageCopyRegionUnimpl() {
    Cal::Utils::signalAbort("Function CommandList.zeCommandListAppendImageCopyRegion is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeCommandListAppendImageCopyToMemoryUnimpl() {
    Cal::Utils::signalAbort("Function CommandList.zeCommandListAppendImageCopyToMemory is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeCommandListAppendImageCopyFromMemoryUnimpl() {
    Cal::Utils::signalAbort("Function CommandList.zeCommandListAppendImageCopyFromMemory is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeCommandListAppendImageCopyToMemoryExtUnimpl() {
    Cal::Utils::signalAbort("Function CommandList.zeCommandListAppendImageCopyToMemoryExt is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeCommandListAppendImageCopyFromMemoryExtUnimpl() {
    Cal::Utils::signalAbort("Function CommandList.zeCommandListAppendImageCopyFromMemoryExt is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeImageGetMemoryPropertiesExpUnimpl() {
    Cal::Utils::signalAbort("Function ImageExp.zeImageGetMemoryPropertiesExp is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeImageGetAllocPropertiesExtUnimpl() {
    Cal::Utils::signalAbort("Function Image.zeImageGetAllocPropertiesExt is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeImageViewCreateExpUnimpl() {
    Cal::Utils::signalAbort("Function ImageExp.zeImageViewCreateExp is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeContextMakeImageResidentUnimpl() {
    Cal::Utils::signalAbort("Function Context.zeContextMakeImageResident is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeContextEvictImageUnimpl() {
    Cal::Utils::signalAbort("Function Context.zeContextEvictImage is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeSamplerCreateUnimpl() {
    Cal::Utils::signalAbort("Function Sampler.zeSamplerCreate is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zeSamplerDestroyUnimpl() {
    Cal::Utils::signalAbort("Function Sampler.zeSamplerDestroy is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEnumFansUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEnumFans is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFanGetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function Fan.zesFanGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFanGetConfigUnimpl() {
    Cal::Utils::signalAbort("Function Fan.zesFanGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFanSetDefaultModeUnimpl() {
    Cal::Utils::signalAbort("Function Fan.zesFanSetDefaultMode is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFanSetFixedSpeedModeUnimpl() {
    Cal::Utils::signalAbort("Function Fan.zesFanSetFixedSpeedMode is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFanSetSpeedTableModeUnimpl() {
    Cal::Utils::signalAbort("Function Fan.zesFanSetSpeedTableMode is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFanGetStateUnimpl() {
    Cal::Utils::signalAbort("Function Fan.zesFanGetState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEnumFirmwaresUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEnumFirmwares is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFirmwareGetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function Firmware.zesFirmwareGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFirmwareFlashUnimpl() {
    Cal::Utils::signalAbort("Function Firmware.zesFirmwareFlash is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEccAvailableUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEccAvailable is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEccConfigurableUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEccConfigurable is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceGetEccStateUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceGetEccState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceSetEccStateUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceSetEccState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEnumLedsUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEnumLeds is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesLedGetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function Led.zesLedGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesLedGetStateUnimpl() {
    Cal::Utils::signalAbort("Function Led.zesLedGetState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesLedSetStateUnimpl() {
    Cal::Utils::signalAbort("Function Led.zesLedSetState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesLedSetColorUnimpl() {
    Cal::Utils::signalAbort("Function Led.zesLedSetColor is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEnumFabricPortsUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEnumFabricPorts is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFabricPortGetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function FabricPort.zesFabricPortGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFabricPortGetLinkTypeUnimpl() {
    Cal::Utils::signalAbort("Function FabricPort.zesFabricPortGetLinkType is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFabricPortGetConfigUnimpl() {
    Cal::Utils::signalAbort("Function FabricPort.zesFabricPortGetConfig is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFabricPortSetConfigUnimpl() {
    Cal::Utils::signalAbort("Function FabricPort.zesFabricPortSetConfig is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFabricPortGetStateUnimpl() {
    Cal::Utils::signalAbort("Function FabricPort.zesFabricPortGetState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesFabricPortGetThroughputUnimpl() {
    Cal::Utils::signalAbort("Function FabricPort.zesFabricPortGetThroughput is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEnumDiagnosticTestSuitesUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEnumDiagnosticTestSuites is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDiagnosticsGetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function Diagnostics.zesDiagnosticsGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDiagnosticsGetTestsUnimpl() {
    Cal::Utils::signalAbort("Function Diagnostics.zesDiagnosticsGetTests is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDiagnosticsRunTestsUnimpl() {
    Cal::Utils::signalAbort("Function Diagnostics.zesDiagnosticsRunTests is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesDeviceEnumPsusUnimpl() {
    Cal::Utils::signalAbort("Function Device.zesDeviceEnumPsus is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesPsuGetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function Psu.zesPsuGetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zesPsuGetStateUnimpl() {
    Cal::Utils::signalAbort("Function Psu.zesPsuGetState is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugAttachUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugAttach is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugDetachUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugDetach is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugReadEventUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugReadEvent is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugAcknowledgeEventUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugAcknowledgeEvent is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugInterruptUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugInterrupt is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugResumeUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugResume is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugReadMemoryUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugReadMemory is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugWriteMemoryUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugWriteMemory is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugGetRegisterSetPropertiesUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugGetRegisterSetProperties is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugReadRegistersUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugReadRegisters is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetDebugWriteRegistersUnimpl() {
    Cal::Utils::signalAbort("Function Debug.zetDebugWriteRegisters is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void zetModuleGetDebugInfoUnimpl() {
    Cal::Utils::signalAbort("Function Module.zetModuleGetDebugInfo is not yet implemented in Compute Aggregation Layer - aborting");
}
} // Unimplemented

inline void initL0Ddi(ze_dditable_t &dt){
    dt.Global.pfnInit = Cal::Client::Icd::LevelZero::zeInit;
    dt.CommandList.pfnAppendMemoryRangesBarrier = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryRangesBarrier;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemoryRangesBarrier = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryRangesBarrier_WithTracing;
    }
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
    dt.CommandList.pfnAppendMemoryCopyRegion = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyRegion;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemoryCopyRegion = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyRegion_WithTracing;
    }
    dt.CommandList.pfnAppendMemoryCopyFromContext = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyFromContext;
    if (tracingEnabled) {
        dt.CommandList.pfnAppendMemoryCopyFromContext = Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyFromContext_WithTracing;
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
    dt.Driver.pfnGetLastErrorDescription = Cal::Client::Icd::LevelZero::zeDriverGetLastErrorDescription;
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
    dt.FabricVertexExp.pfnGetExp = Cal::Client::Icd::LevelZero::zeFabricVertexGetExp;
    dt.FabricVertexExp.pfnGetSubVerticesExp = Cal::Client::Icd::LevelZero::zeFabricVertexGetSubVerticesExp;
    dt.FabricVertexExp.pfnGetPropertiesExp = Cal::Client::Icd::LevelZero::zeFabricVertexGetPropertiesExp;
    dt.FabricVertexExp.pfnGetDeviceExp = Cal::Client::Icd::LevelZero::zeFabricVertexGetDeviceExp;
    dt.DeviceExp.pfnGetFabricVertexExp = Cal::Client::Icd::LevelZero::zeDeviceGetFabricVertexExp;
    dt.FabricEdgeExp.pfnGetExp = Cal::Client::Icd::LevelZero::zeFabricEdgeGetExp;
    dt.FabricEdgeExp.pfnGetVerticesExp = Cal::Client::Icd::LevelZero::zeFabricEdgeGetVerticesExp;
    dt.FabricEdgeExp.pfnGetPropertiesExp = Cal::Client::Icd::LevelZero::zeFabricEdgeGetPropertiesExp;
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
    dt.Module.pfnInspectLinkageExt = Cal::Client::Icd::LevelZero::zeModuleInspectLinkageExt;
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
    dt.Mem.pfnPutIpcHandle = Cal::Client::Icd::LevelZero::zeMemPutIpcHandle;
    dt.Mem.pfnFreeExt = Cal::Client::Icd::LevelZero::zeMemFreeExt;
    dt.MemExp.pfnGetFileDescriptorFromIpcHandleExp = Cal::Client::Icd::LevelZero::zeMemGetFileDescriptorFromIpcHandleExp;
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
    dt.Kernel.pfnGetSourceAttributes = Cal::Client::Icd::LevelZero::zeKernelGetSourceAttributes;
    if (tracingEnabled) {
        dt.Kernel.pfnGetSourceAttributes = Cal::Client::Icd::LevelZero::zeKernelGetSourceAttributes_WithTracing;
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
    dt.CommandList.pfnAppendImageCopy = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopy)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyUnimpl);
    dt.CommandList.pfnAppendImageCopyRegion = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyRegion)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyRegionUnimpl);
    dt.CommandList.pfnAppendImageCopyToMemory = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemory)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemory = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemory)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryUnimpl);
    dt.CommandList.pfnAppendImageCopyToMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyToMemoryExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyToMemoryExtUnimpl);
    dt.CommandList.pfnAppendImageCopyFromMemoryExt = reinterpret_cast<decltype(dt.CommandList.pfnAppendImageCopyFromMemoryExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeCommandListAppendImageCopyFromMemoryExtUnimpl);
    dt.ImageExp.pfnGetMemoryPropertiesExp = reinterpret_cast<decltype(dt.ImageExp.pfnGetMemoryPropertiesExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeImageGetMemoryPropertiesExpUnimpl);
    dt.Image.pfnGetAllocPropertiesExt = reinterpret_cast<decltype(dt.Image.pfnGetAllocPropertiesExt)>(Cal::Client::Icd::LevelZero::Unimplemented::zeImageGetAllocPropertiesExtUnimpl);
    dt.ImageExp.pfnViewCreateExp = reinterpret_cast<decltype(dt.ImageExp.pfnViewCreateExp)>(Cal::Client::Icd::LevelZero::Unimplemented::zeImageViewCreateExpUnimpl);
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
    dt.Power.pfnGetLimitsExt = Cal::Client::Icd::LevelZero::zesPowerGetLimitsExt;
    dt.Power.pfnSetLimitsExt = Cal::Client::Icd::LevelZero::zesPowerSetLimitsExt;
    dt.Power.pfnGetEnergyThreshold = Cal::Client::Icd::LevelZero::zesPowerGetEnergyThreshold;
    dt.Power.pfnSetEnergyThreshold = Cal::Client::Icd::LevelZero::zesPowerSetEnergyThreshold;
    dt.Device.pfnEventRegister = Cal::Client::Icd::LevelZero::zesDeviceEventRegister;
    dt.Driver.pfnEventListen = Cal::Client::Icd::LevelZero::zesDriverEventListen;
    dt.Driver.pfnEventListenEx = Cal::Client::Icd::LevelZero::zesDriverEventListenEx;
    dt.Device.pfnEnumTemperatureSensors = Cal::Client::Icd::LevelZero::zesDeviceEnumTemperatureSensors;
    dt.Temperature.pfnGetProperties = Cal::Client::Icd::LevelZero::zesTemperatureGetProperties;
    dt.Temperature.pfnGetConfig = Cal::Client::Icd::LevelZero::zesTemperatureGetConfig;
    dt.Temperature.pfnSetConfig = Cal::Client::Icd::LevelZero::zesTemperatureSetConfig;
    dt.Temperature.pfnGetState = Cal::Client::Icd::LevelZero::zesTemperatureGetState;
    dt.Device.pfnEnumRasErrorSets = Cal::Client::Icd::LevelZero::zesDeviceEnumRasErrorSets;
    dt.Ras.pfnGetProperties = Cal::Client::Icd::LevelZero::zesRasGetProperties;
    dt.Ras.pfnGetConfig = Cal::Client::Icd::LevelZero::zesRasGetConfig;
    dt.Ras.pfnSetConfig = Cal::Client::Icd::LevelZero::zesRasSetConfig;
    dt.Ras.pfnGetState = Cal::Client::Icd::LevelZero::zesRasGetState;
    dt.Device.pfnEnumFrequencyDomains = Cal::Client::Icd::LevelZero::zesDeviceEnumFrequencyDomains;
    dt.Frequency.pfnGetProperties = Cal::Client::Icd::LevelZero::zesFrequencyGetProperties;
    dt.Frequency.pfnGetAvailableClocks = Cal::Client::Icd::LevelZero::zesFrequencyGetAvailableClocks;
    dt.Frequency.pfnGetRange = Cal::Client::Icd::LevelZero::zesFrequencyGetRange;
    dt.Frequency.pfnSetRange = Cal::Client::Icd::LevelZero::zesFrequencySetRange;
    dt.Frequency.pfnGetState = Cal::Client::Icd::LevelZero::zesFrequencyGetState;
    dt.Frequency.pfnGetThrottleTime = Cal::Client::Icd::LevelZero::zesFrequencyGetThrottleTime;
    dt.Frequency.pfnOcGetCapabilities = Cal::Client::Icd::LevelZero::zesFrequencyOcGetCapabilities;
    dt.Frequency.pfnOcGetVoltageTarget = Cal::Client::Icd::LevelZero::zesFrequencyOcGetVoltageTarget;
    dt.Frequency.pfnOcSetVoltageTarget = Cal::Client::Icd::LevelZero::zesFrequencyOcSetVoltageTarget;
    dt.Frequency.pfnOcSetMode = Cal::Client::Icd::LevelZero::zesFrequencyOcSetMode;
    dt.Frequency.pfnOcGetMode = Cal::Client::Icd::LevelZero::zesFrequencyOcGetMode;
    dt.Frequency.pfnOcGetIccMax = Cal::Client::Icd::LevelZero::zesFrequencyOcGetIccMax;
    dt.Frequency.pfnOcSetIccMax = Cal::Client::Icd::LevelZero::zesFrequencyOcSetIccMax;
    dt.Frequency.pfnOcGetTjMax = Cal::Client::Icd::LevelZero::zesFrequencyOcGetTjMax;
    dt.Frequency.pfnOcSetTjMax = Cal::Client::Icd::LevelZero::zesFrequencyOcSetTjMax;
    dt.Device.pfnEnumEngineGroups = Cal::Client::Icd::LevelZero::zesDeviceEnumEngineGroups;
    dt.Device.pfnEnumSchedulers = Cal::Client::Icd::LevelZero::zesDeviceEnumSchedulers;
    dt.Scheduler.pfnGetProperties = Cal::Client::Icd::LevelZero::zesSchedulerGetProperties;
    dt.Scheduler.pfnGetCurrentMode = Cal::Client::Icd::LevelZero::zesSchedulerGetCurrentMode;
    dt.Scheduler.pfnGetTimeoutModeProperties = Cal::Client::Icd::LevelZero::zesSchedulerGetTimeoutModeProperties;
    dt.Scheduler.pfnGetTimesliceModeProperties = Cal::Client::Icd::LevelZero::zesSchedulerGetTimesliceModeProperties;
    dt.Scheduler.pfnSetTimeoutMode = Cal::Client::Icd::LevelZero::zesSchedulerSetTimeoutMode;
    dt.Scheduler.pfnSetTimesliceMode = Cal::Client::Icd::LevelZero::zesSchedulerSetTimesliceMode;
    dt.Scheduler.pfnSetExclusiveMode = Cal::Client::Icd::LevelZero::zesSchedulerSetExclusiveMode;
    dt.Scheduler.pfnSetComputeUnitDebugMode = Cal::Client::Icd::LevelZero::zesSchedulerSetComputeUnitDebugMode;
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
    dt.Memory.pfnGetProperties = Cal::Client::Icd::LevelZero::zesMemoryGetProperties;
    dt.Memory.pfnGetState = Cal::Client::Icd::LevelZero::zesMemoryGetState;
    dt.Memory.pfnGetBandwidth = Cal::Client::Icd::LevelZero::zesMemoryGetBandwidth;
    dt.Device.pfnEnumPerformanceFactorDomains = Cal::Client::Icd::LevelZero::zesDeviceEnumPerformanceFactorDomains;
    dt.PerformanceFactor.pfnGetProperties = Cal::Client::Icd::LevelZero::zesPerformanceFactorGetProperties;
    dt.PerformanceFactor.pfnGetConfig = Cal::Client::Icd::LevelZero::zesPerformanceFactorGetConfig;
    dt.PerformanceFactor.pfnSetConfig = Cal::Client::Icd::LevelZero::zesPerformanceFactorSetConfig;
    dt.Device.pfnEnumStandbyDomains = Cal::Client::Icd::LevelZero::zesDeviceEnumStandbyDomains;
    dt.Standby.pfnGetProperties = Cal::Client::Icd::LevelZero::zesStandbyGetProperties;
    dt.Standby.pfnGetMode = Cal::Client::Icd::LevelZero::zesStandbyGetMode;
    dt.Standby.pfnSetMode = Cal::Client::Icd::LevelZero::zesStandbySetMode;
    // below are unimplemented, provided bindings are for easier debugging only
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
    dt.Device.pfnEccAvailable = reinterpret_cast<decltype(dt.Device.pfnEccAvailable)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEccAvailableUnimpl);
    dt.Device.pfnEccConfigurable = reinterpret_cast<decltype(dt.Device.pfnEccConfigurable)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEccConfigurableUnimpl);
    dt.Device.pfnGetEccState = reinterpret_cast<decltype(dt.Device.pfnGetEccState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceGetEccStateUnimpl);
    dt.Device.pfnSetEccState = reinterpret_cast<decltype(dt.Device.pfnSetEccState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceSetEccStateUnimpl);
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
    dt.Device.pfnEnumDiagnosticTestSuites = reinterpret_cast<decltype(dt.Device.pfnEnumDiagnosticTestSuites)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumDiagnosticTestSuitesUnimpl);
    dt.Diagnostics.pfnGetProperties = reinterpret_cast<decltype(dt.Diagnostics.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDiagnosticsGetPropertiesUnimpl);
    dt.Diagnostics.pfnGetTests = reinterpret_cast<decltype(dt.Diagnostics.pfnGetTests)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDiagnosticsGetTestsUnimpl);
    dt.Diagnostics.pfnRunTests = reinterpret_cast<decltype(dt.Diagnostics.pfnRunTests)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDiagnosticsRunTestsUnimpl);
    dt.Device.pfnEnumPsus = reinterpret_cast<decltype(dt.Device.pfnEnumPsus)>(Cal::Client::Icd::LevelZero::Unimplemented::zesDeviceEnumPsusUnimpl);
    dt.Psu.pfnGetProperties = reinterpret_cast<decltype(dt.Psu.pfnGetProperties)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPsuGetPropertiesUnimpl);
    dt.Psu.pfnGetState = reinterpret_cast<decltype(dt.Psu.pfnGetState)>(Cal::Client::Icd::LevelZero::Unimplemented::zesPsuGetStateUnimpl);
}
inline void initL0ToolsDdi(zet_dditable_t &dt){
    dt.MetricGroup.pfnGet = Cal::Client::Icd::LevelZero::zetMetricGroupGet;
    dt.MetricGroup.pfnGetProperties = Cal::Client::Icd::LevelZero::zetMetricGroupGetProperties;
    dt.MetricGroupExp.pfnGetGlobalTimestampsExp = Cal::Client::Icd::LevelZero::zetMetricGroupGetGlobalTimestampsExp;
    dt.MetricGroupExp.pfnGetExportDataExp = Cal::Client::Icd::LevelZero::zetMetricGroupGetExportDataExp;
    dt.MetricGroup.pfnCalculateMetricValues = Cal::Client::Icd::LevelZero::zetMetricGroupCalculateMetricValues;
    dt.MetricGroupExp.pfnCalculateMultipleMetricValuesExp = Cal::Client::Icd::LevelZero::zetMetricGroupCalculateMultipleMetricValuesExp;
    dt.Metric.pfnGet = Cal::Client::Icd::LevelZero::zetMetricGet;
    dt.Metric.pfnGetProperties = Cal::Client::Icd::LevelZero::zetMetricGetProperties;
    dt.Context.pfnActivateMetricGroups = Cal::Client::Icd::LevelZero::zetContextActivateMetricGroups;
    dt.MetricStreamer.pfnOpen = Cal::Client::Icd::LevelZero::zetMetricStreamerOpen;
    dt.MetricStreamer.pfnReadData = Cal::Client::Icd::LevelZero::zetMetricStreamerReadData;
    dt.MetricStreamer.pfnClose = Cal::Client::Icd::LevelZero::zetMetricStreamerClose;
    dt.MetricQueryPool.pfnCreate = Cal::Client::Icd::LevelZero::zetMetricQueryPoolCreate;
    dt.MetricQueryPool.pfnDestroy = Cal::Client::Icd::LevelZero::zetMetricQueryPoolDestroy;
    dt.MetricQuery.pfnCreate = Cal::Client::Icd::LevelZero::zetMetricQueryCreate;
    dt.MetricQuery.pfnDestroy = Cal::Client::Icd::LevelZero::zetMetricQueryDestroy;
    dt.MetricQuery.pfnReset = Cal::Client::Icd::LevelZero::zetMetricQueryReset;
    dt.MetricQuery.pfnGetData = Cal::Client::Icd::LevelZero::zetMetricQueryGetData;
    dt.CommandList.pfnAppendMetricQueryBegin = Cal::Client::Icd::LevelZero::zetCommandListAppendMetricQueryBegin;
    dt.CommandList.pfnAppendMetricQueryEnd = Cal::Client::Icd::LevelZero::zetCommandListAppendMetricQueryEnd;
    dt.CommandList.pfnAppendMetricMemoryBarrier = Cal::Client::Icd::LevelZero::zetCommandListAppendMetricMemoryBarrier;
    dt.CommandList.pfnAppendMetricStreamerMarker = Cal::Client::Icd::LevelZero::zetCommandListAppendMetricStreamerMarker;
    dt.TracerExp.pfnCreate = Cal::Client::Icd::LevelZero::zetTracerExpCreate;
    dt.TracerExp.pfnDestroy = Cal::Client::Icd::LevelZero::zetTracerExpDestroy;
    dt.TracerExp.pfnSetPrologues = Cal::Client::Icd::LevelZero::zetTracerExpSetPrologues;
    dt.TracerExp.pfnSetEpilogues = Cal::Client::Icd::LevelZero::zetTracerExpSetEpilogues;
    dt.TracerExp.pfnSetEnabled = Cal::Client::Icd::LevelZero::zetTracerExpSetEnabled;
    dt.Device.pfnGetDebugProperties = Cal::Client::Icd::LevelZero::zetDeviceGetDebugProperties;
    dt.Debug.pfnAttach = Cal::Client::Icd::LevelZero::zetDebugAttach;
    dt.Debug.pfnDetach = Cal::Client::Icd::LevelZero::zetDebugDetach;
    dt.Kernel.pfnGetProfileInfo = Cal::Client::Icd::LevelZero::zetKernelGetProfileInfo;
    // below are unimplemented, provided bindings are for easier debugging only
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
}

void *getL0ExtensionFuncionAddressRpcHelper(const char *funcName);
} // namespace LevelZero
} // namespace Icd
} // namespace Client
} // namespace Cal
// #### Generated code -- end ####
