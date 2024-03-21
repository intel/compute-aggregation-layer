/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "generated_service_level_zero.h"

#include <shared/log.h>

#include <cassert>
#include <mutex>

namespace Cal {
namespace Service {
namespace Apis {
namespace LevelZero {

namespace Standard {
ze_result_t (*zetMetricGroupGet)(zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups) = nullptr;
ze_result_t (*zetMetricGroupGetProperties)(zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties) = nullptr;
ze_result_t (*zetMetricGroupGetGlobalTimestampsExp)(zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp) = nullptr;
ze_result_t (*zetMetricGroupGetExportDataExp)(zet_metric_group_handle_t hMetricGroup, const uint8_t * pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t* pExportData) = nullptr;
ze_result_t (*zetMetricGroupCalculateMetricValues)(zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues) = nullptr;
ze_result_t (*zetMetricGroupCalculateMultipleMetricValuesExp)(zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues) = nullptr;
ze_result_t (*zetMetricGet)(zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics) = nullptr;
ze_result_t (*zetMetricGetProperties)(zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties) = nullptr;
ze_result_t (*zetContextActivateMetricGroups)(zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups) = nullptr;
ze_result_t (*zetMetricStreamerOpen)(zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer) = nullptr;
ze_result_t (*zetMetricStreamerReadData)(zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData) = nullptr;
ze_result_t (*zetMetricStreamerClose)(zet_metric_streamer_handle_t hMetricStreamer) = nullptr;
ze_result_t (*zetMetricQueryPoolCreate)(zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t * desc, zet_metric_query_pool_handle_t* phMetricQueryPool) = nullptr;
ze_result_t (*zetMetricQueryPoolDestroy)(zet_metric_query_pool_handle_t hMetricQueryPool) = nullptr;
ze_result_t (*zetMetricQueryCreate)(zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery) = nullptr;
ze_result_t (*zetMetricQueryDestroy)(zet_metric_query_handle_t hMetricQuery) = nullptr;
ze_result_t (*zetMetricQueryReset)(zet_metric_query_handle_t hMetricQuery) = nullptr;
ze_result_t (*zetMetricQueryGetData)(zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData) = nullptr;
ze_result_t (*zetCommandListAppendMetricQueryBegin)(zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery) = nullptr;
ze_result_t (*zetCommandListAppendMetricQueryEnd)(zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zetCommandListAppendMetricMemoryBarrier)(zet_command_list_handle_t hCommandList) = nullptr;
ze_result_t (*zetCommandListAppendMetricStreamerMarker)(zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value) = nullptr;
ze_result_t (*zetTracerExpCreate)(zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer) = nullptr;
ze_result_t (*zetTracerExpDestroy)(zet_tracer_exp_handle_t hTracer) = nullptr;
ze_result_t (*zetTracerExpSetPrologues)(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs) = nullptr;
ze_result_t (*zetTracerExpSetEpilogues)(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs) = nullptr;
ze_result_t (*zetTracerExpSetEnabled)(zet_tracer_exp_handle_t hTracer, ze_bool_t enable) = nullptr;
ze_result_t (*zetDeviceGetDebugProperties)(ze_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties) = nullptr;
ze_result_t (*zetDebugAttach)(ze_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug) = nullptr;
ze_result_t (*zetDebugDetach)(zet_debug_session_handle_t hDebug) = nullptr;
ze_result_t (*zetKernelGetProfileInfo)(ze_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties) = nullptr;
ze_result_t (*zesDeviceReset)(zes_device_handle_t hDevice, ze_bool_t force) = nullptr;
ze_result_t (*zesDeviceResetExt)(zes_device_handle_t hDevice, zes_reset_properties_t* pProperties) = nullptr;
ze_result_t (*zesDeviceEnumPowerDomains)(zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower) = nullptr;
ze_result_t (*zesDeviceGetCardPowerDomain)(zes_device_handle_t hDevice, zes_pwr_handle_t* phPower) = nullptr;
ze_result_t (*zesPowerGetProperties)(zes_pwr_handle_t hPower, zes_power_properties_t* pProperties) = nullptr;
ze_result_t (*zesPowerGetEnergyCounter)(zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy) = nullptr;
ze_result_t (*zesPowerGetLimits)(zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak) = nullptr;
ze_result_t (*zesPowerSetLimits)(zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak) = nullptr;
ze_result_t (*zesPowerGetLimitsExt)(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) = nullptr;
ze_result_t (*zesPowerSetLimitsExt)(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) = nullptr;
ze_result_t (*zesPowerGetEnergyThreshold)(zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold) = nullptr;
ze_result_t (*zesPowerSetEnergyThreshold)(zes_pwr_handle_t hPower, double pThreshold) = nullptr;
ze_result_t (*zesDeviceEventRegister)(zes_device_handle_t hDevice, zes_event_type_flags_t events) = nullptr;
ze_result_t (*zesDriverEventListen)(ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) = nullptr;
ze_result_t (*zesDriverEventListenEx)(ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) = nullptr;
ze_result_t (*zesDeviceEnumTemperatureSensors)(zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature) = nullptr;
ze_result_t (*zesTemperatureGetProperties)(zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties) = nullptr;
ze_result_t (*zesTemperatureGetConfig)(zes_temp_handle_t hTemperature, zes_temp_config_t * pConfig) = nullptr;
ze_result_t (*zesTemperatureSetConfig)(zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig) = nullptr;
ze_result_t (*zesTemperatureGetState)(zes_temp_handle_t hTemperature, double* pTemperature) = nullptr;
ze_result_t (*zesDeviceEnumRasErrorSets)(zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas) = nullptr;
ze_result_t (*zesRasGetProperties)(zes_ras_handle_t hRas, zes_ras_properties_t* pProperties) = nullptr;
ze_result_t (*zesRasGetConfig)(zes_ras_handle_t hRas, zes_ras_config_t * pConfig) = nullptr;
ze_result_t (*zesRasSetConfig)(zes_ras_handle_t hRas, const zes_ras_config_t* pConfig) = nullptr;
ze_result_t (*zesRasGetState)(zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState) = nullptr;
ze_result_t (*zesDeviceEnumFrequencyDomains)(zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency) = nullptr;
ze_result_t (*zesFrequencyGetProperties)(zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties) = nullptr;
ze_result_t (*zesFrequencyGetAvailableClocks)(zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency) = nullptr;
ze_result_t (*zesFrequencyGetRange)(zes_freq_handle_t hFrequency, zes_freq_range_t* pConfig) = nullptr;
ze_result_t (*zesFrequencySetRange)(zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits) = nullptr;
ze_result_t (*zesFrequencyGetState)(zes_freq_handle_t hFrequency, zes_freq_state_t* pState) = nullptr;
ze_result_t (*zesFrequencyGetThrottleTime)(zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime) = nullptr;
ze_result_t (*zesFrequencyOcGetCapabilities)(zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities) = nullptr;
ze_result_t (*zesFrequencyOcGetVoltageTarget)(zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset) = nullptr;
ze_result_t (*zesFrequencyOcSetVoltageTarget)(zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset) = nullptr;
ze_result_t (*zesFrequencyOcSetMode)(zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode) = nullptr;
ze_result_t (*zesFrequencyOcGetMode)(zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode) = nullptr;
ze_result_t (*zesFrequencyOcGetIccMax)(zes_freq_handle_t hFrequency, double* pOcIccMax) = nullptr;
ze_result_t (*zesFrequencyOcSetIccMax)(zes_freq_handle_t hFrequency, double ocIccMax) = nullptr;
ze_result_t (*zesFrequencyOcGetTjMax)(zes_freq_handle_t hFrequency, double* pOcTjMax) = nullptr;
ze_result_t (*zesFrequencyOcSetTjMax)(zes_freq_handle_t hFrequency, double ocTjMax) = nullptr;
ze_result_t (*zesDeviceEnumEngineGroups)(zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine) = nullptr;
ze_result_t (*zesDeviceEnumSchedulers)(zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler) = nullptr;
ze_result_t (*zesSchedulerGetProperties)(zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties) = nullptr;
ze_result_t (*zesSchedulerGetCurrentMode)(zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode) = nullptr;
ze_result_t (*zesSchedulerGetTimeoutModeProperties)(zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig) = nullptr;
ze_result_t (*zesSchedulerGetTimesliceModeProperties)(zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig) = nullptr;
ze_result_t (*zesSchedulerSetTimeoutMode)(zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload) = nullptr;
ze_result_t (*zesSchedulerSetTimesliceMode)(zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload) = nullptr;
ze_result_t (*zesSchedulerSetExclusiveMode)(zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload) = nullptr;
ze_result_t (*zesSchedulerSetComputeUnitDebugMode)(zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload) = nullptr;
ze_result_t (*zesEngineGetProperties)(zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties) = nullptr;
ze_result_t (*zesEngineGetActivity)(zes_engine_handle_t hEngine, zes_engine_stats_t* pStats) = nullptr;
ze_result_t (*zesDeviceGetState)(zes_device_handle_t hDevice, zes_device_state_t* pState) = nullptr;
ze_result_t (*zesDeviceProcessesGetState)(zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses) = nullptr;
ze_result_t (*zesDevicePciGetProperties)(zes_device_handle_t hDevice, zes_pci_properties_t* pProperties) = nullptr;
ze_result_t (*zesDevicePciGetState)(zes_device_handle_t hDevice, zes_pci_state_t* pState) = nullptr;
ze_result_t (*zesDevicePciGetBars)(zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties) = nullptr;
ze_result_t (*zesDevicePciGetStats)(zes_device_handle_t hDevice, zes_pci_stats_t* pStats) = nullptr;
ze_result_t (*zesDeviceGetProperties)(zes_device_handle_t hDevice, zes_device_properties_t* pProperties) = nullptr;
ze_result_t (*zesDeviceEnumMemoryModules)(zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory) = nullptr;
ze_result_t (*zesMemoryGetProperties)(zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties) = nullptr;
ze_result_t (*zesMemoryGetState)(zes_mem_handle_t hMemory, zes_mem_state_t* pState) = nullptr;
ze_result_t (*zesMemoryGetBandwidth)(zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth) = nullptr;
ze_result_t (*zesDeviceEnumPerformanceFactorDomains)(zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf) = nullptr;
ze_result_t (*zesPerformanceFactorGetProperties)(zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties) = nullptr;
ze_result_t (*zesPerformanceFactorGetConfig)(zes_perf_handle_t hPerf, double* pFactor) = nullptr;
ze_result_t (*zesPerformanceFactorSetConfig)(zes_perf_handle_t hPerf, double pFactor) = nullptr;
ze_result_t (*zesDeviceEnumStandbyDomains)(zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby) = nullptr;
ze_result_t (*zesStandbyGetProperties)(zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties) = nullptr;
ze_result_t (*zesStandbyGetMode)(zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode) = nullptr;
ze_result_t (*zesStandbySetMode)(zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode) = nullptr;
ze_result_t (*zeInit)(ze_init_flags_t flags) = nullptr;
ze_result_t (*zeCommandListAppendMemoryRangesBarrier)(ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeContextSystemBarrier)(ze_context_handle_t hContext, ze_device_handle_t hDevice) = nullptr;
ze_result_t (*zeCommandListCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) = nullptr;
ze_result_t (*zeCommandListCreateImmediate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) = nullptr;
ze_result_t (*zeCommandListDestroy)(ze_command_list_handle_t hCommandList) = nullptr;
ze_result_t (*zeCommandListClose)(ze_command_list_handle_t hCommandList) = nullptr;
ze_result_t (*zeCommandListReset)(ze_command_list_handle_t hCommandList) = nullptr;
ze_result_t (*zeCommandListAppendWriteGlobalTimestamp)(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandQueueCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) = nullptr;
ze_result_t (*zeCommandQueueDestroy)(ze_command_queue_handle_t hCommandQueue) = nullptr;
ze_result_t (*zeCommandQueueExecuteCommandLists)(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeCommandQueueSynchronize)(ze_command_queue_handle_t hCommandQueue, uint64_t timeout) = nullptr;
ze_result_t (*zeContextCreate)(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) = nullptr;
ze_result_t (*zeContextCreateEx)(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) = nullptr;
ze_result_t (*zeContextDestroy)(ze_context_handle_t hContext) = nullptr;
ze_result_t (*zeContextGetStatus)(ze_context_handle_t hContext) = nullptr;
ze_result_t (*zeCommandListAppendMemoryCopy)(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendMemoryFill)(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendMemoryCopyRegion)(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendMemoryCopyFromContext)(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendMemoryPrefetch)(ze_command_list_handle_t hCommandList, const void* ptr, size_t size) = nullptr;
ze_result_t (*zeCommandListAppendMemAdvise)(ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice) = nullptr;
ze_result_t (*zeDeviceGet)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) = nullptr;
ze_result_t (*zeDeviceGetSubDevices)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) = nullptr;
ze_result_t (*zeDeviceGetProperties)(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) = nullptr;
ze_result_t (*zeDeviceGetComputeProperties)(ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) = nullptr;
ze_result_t (*zeDeviceGetModuleProperties)(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) = nullptr;
ze_result_t (*zeDeviceGetCommandQueueGroupProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) = nullptr;
ze_result_t (*zeDeviceGetMemoryProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) = nullptr;
ze_result_t (*zeDeviceGetMemoryAccessProperties)(ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) = nullptr;
ze_result_t (*zeDeviceGetCacheProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) = nullptr;
ze_result_t (*zeDeviceGetImageProperties)(ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) = nullptr;
ze_result_t (*zeDeviceGetExternalMemoryProperties)(ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) = nullptr;
ze_result_t (*zeDeviceGetP2PProperties)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) = nullptr;
ze_result_t (*zeDeviceCanAccessPeer)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) = nullptr;
ze_result_t (*zeDeviceGetStatus)(ze_device_handle_t hDevice) = nullptr;
ze_result_t (*zeDeviceGetGlobalTimestamps)(ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) = nullptr;
ze_result_t (*zeDeviceReserveCacheExt)(ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize) = nullptr;
ze_result_t (*zeDeviceSetCacheAdviceExt)(ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion) = nullptr;
ze_result_t (*zeDriverGet)(uint32_t* pCount, ze_driver_handle_t* phDrivers) = nullptr;
ze_result_t (*zeDriverGetApiVersion)(ze_driver_handle_t hDriver, ze_api_version_t* version) = nullptr;
ze_result_t (*zeDriverGetProperties)(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) = nullptr;
ze_result_t (*zeDriverGetIpcProperties)(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) = nullptr;
ze_result_t (*zeDriverGetExtensionProperties)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) = nullptr;
ze_result_t (*zeDriverGetExtensionFunctionAddress)(ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress) = nullptr;
ze_result_t (*zeDriverGetLastErrorDescription)(ze_driver_handle_t hDriver, const char** ppString) = nullptr;
ze_result_t (*zeEventPoolCreate)(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) = nullptr;
ze_result_t (*zeEventPoolDestroy)(ze_event_pool_handle_t hEventPool) = nullptr;
ze_result_t (*zeEventCreate)(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) = nullptr;
ze_result_t (*zeEventDestroy)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventPoolGetIpcHandle)(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc) = nullptr;
ze_result_t (*zeEventPoolOpenIpcHandle)(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool) = nullptr;
ze_result_t (*zeEventPoolCloseIpcHandle)(ze_event_pool_handle_t hEventPool) = nullptr;
ze_result_t (*zeEventPoolPutIpcHandle)(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc) = nullptr;
ze_result_t (*zeCommandListAppendBarrier)(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendSignalEvent)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeCommandListAppendWaitOnEvents)(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) = nullptr;
ze_result_t (*zeEventHostSignal)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventHostSynchronize)(ze_event_handle_t hEvent, uint64_t timeout) = nullptr;
ze_result_t (*zeEventQueryStatus)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeCommandListAppendEventReset)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventHostReset)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventQueryKernelTimestamp)(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) = nullptr;
ze_result_t (*zeCommandListAppendQueryKernelTimestamps)(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeEventQueryTimestampsExp)(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps) = nullptr;
ze_result_t (*zeEventQueryKernelTimestampsExt)(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults) = nullptr;
ze_result_t (*zeFabricVertexGetExp)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices) = nullptr;
ze_result_t (*zeFabricVertexGetSubVerticesExp)(ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices) = nullptr;
ze_result_t (*zeFabricVertexGetPropertiesExp)(ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties) = nullptr;
ze_result_t (*zeFabricVertexGetDeviceExp)(ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* pDevice) = nullptr;
ze_result_t (*zeDeviceGetFabricVertexExp)(ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* pVertex) = nullptr;
ze_result_t (*zeFabricEdgeGetExp)(ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges) = nullptr;
ze_result_t (*zeFabricEdgeGetVerticesExp)(ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB) = nullptr;
ze_result_t (*zeFabricEdgeGetPropertiesExp)(ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties) = nullptr;
ze_result_t (*zeFenceCreate)(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) = nullptr;
ze_result_t (*zeFenceDestroy)(ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeFenceHostSynchronize)(ze_fence_handle_t hFence, uint64_t timeout) = nullptr;
ze_result_t (*zeFenceQueryStatus)(ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeFenceReset)(ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeKernelSetGlobalOffsetExp)(ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) = nullptr;
ze_result_t (*zeImageGetProperties)(ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties) = nullptr;
ze_result_t (*zeImageCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage) = nullptr;
ze_result_t (*zeImageDestroy)(ze_image_handle_t hImage) = nullptr;
ze_result_t (*zeKernelSchedulingHintExp)(ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint) = nullptr;
ze_result_t (*zeModuleInspectLinkageExt)(ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog) = nullptr;
ze_result_t (*zeMemAllocShared)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) = nullptr;
ze_result_t (*zeMemAllocDevice)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) = nullptr;
ze_result_t (*zeMemAllocHost)(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) = nullptr;
ze_result_t (*zeMemFree)(ze_context_handle_t hContext, void* ptr) = nullptr;
ze_result_t (*zeMemGetAllocProperties)(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) = nullptr;
ze_result_t (*zeMemGetAddressRange)(ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) = nullptr;
ze_result_t (*zeMemGetIpcHandle)(ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle) = nullptr;
ze_result_t (*zeMemOpenIpcHandle)(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr) = nullptr;
ze_result_t (*zeMemCloseIpcHandle)(ze_context_handle_t hContext, const void* ptr) = nullptr;
ze_result_t (*zeMemPutIpcHandle)(ze_context_handle_t hContext, ze_ipc_mem_handle_t handle) = nullptr;
ze_result_t (*zeMemFreeExt)(ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr) = nullptr;
ze_result_t (*zeMemGetIpcHandleFromFileDescriptorExp)(ze_context_handle_t hContext, uint64_t handle, ze_ipc_mem_handle_t* pIpcHandle) = nullptr;
ze_result_t (*zeMemGetFileDescriptorFromIpcHandleExp)(ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t* pHandle) = nullptr;
ze_result_t (*zeModuleCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) = nullptr;
ze_result_t (*zeModuleDestroy)(ze_module_handle_t hModule) = nullptr;
ze_result_t (*zeModuleDynamicLink)(uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) = nullptr;
ze_result_t (*zeModuleBuildLogDestroy)(ze_module_build_log_handle_t hModuleBuildLog) = nullptr;
ze_result_t (*zeModuleBuildLogGetString)(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) = nullptr;
ze_result_t (*zeModuleGetNativeBinary)(ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary) = nullptr;
ze_result_t (*zeModuleGetGlobalPointer)(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) = nullptr;
ze_result_t (*zeModuleGetKernelNames)(ze_module_handle_t hModule, uint32_t* pCount, const char** pNames) = nullptr;
ze_result_t (*zeModuleGetProperties)(ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) = nullptr;
ze_result_t (*zeKernelCreate)(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) = nullptr;
ze_result_t (*zeKernelDestroy)(ze_kernel_handle_t hKernel) = nullptr;
ze_result_t (*zeModuleGetFunctionPointer)(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) = nullptr;
ze_result_t (*zeKernelSetGroupSize)(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) = nullptr;
ze_result_t (*zeKernelSuggestGroupSize)(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) = nullptr;
ze_result_t (*zeKernelSuggestMaxCooperativeGroupCount)(ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) = nullptr;
ze_result_t (*zeKernelSetArgumentValue)(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) = nullptr;
ze_result_t (*zeKernelSetIndirectAccess)(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) = nullptr;
ze_result_t (*zeKernelGetIndirectAccess)(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) = nullptr;
ze_result_t (*zeKernelGetSourceAttributes)(ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString) = nullptr;
ze_result_t (*zeKernelSetCacheConfig)(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) = nullptr;
ze_result_t (*zeKernelGetProperties)(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) = nullptr;
ze_result_t (*zeKernelGetName)(ze_kernel_handle_t hKernel, size_t* pSize, char* pName) = nullptr;
ze_result_t (*zeCommandListAppendLaunchKernel)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendLaunchCooperativeKernel)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendLaunchKernelIndirect)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendLaunchMultipleKernelsIndirect)(ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListHostSynchronize)(ze_command_list_handle_t hCommandList, uint64_t timeout) = nullptr;
ze_result_t (*zeDevicePciGetPropertiesExt)(ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties) = nullptr;
ze_result_t (*zeContextMakeMemoryResident)(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) = nullptr;
ze_result_t (*zeContextEvictMemory)(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) = nullptr;
ze_result_t (*zeVirtualMemReserve)(ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr) = nullptr;
ze_result_t (*zeVirtualMemFree)(ze_context_handle_t hContext, const void* ptr, size_t size) = nullptr;
ze_result_t (*zeVirtualMemQueryPageSize)(ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize) = nullptr;
ze_result_t (*zePhysicalMemCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory) = nullptr;
ze_result_t (*zePhysicalMemDestroy)(ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory) = nullptr;
ze_result_t (*zeVirtualMemMap)(ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access) = nullptr;
ze_result_t (*zeVirtualMemUnmap)(ze_context_handle_t hContext, const void* ptr, size_t size) = nullptr;
ze_result_t (*zeVirtualMemSetAccessAttribute)(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access) = nullptr;
ze_result_t (*zeVirtualMemGetAccessAttribute)(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize) = nullptr;

void *libraryHandle = nullptr;

bool loadLevelZeroLibrary(std::optional<std::string> path) {
    if(libraryHandle){
        return false == path.has_value();
    }
    
    std::string loadPath = path.value_or("libze_loader.so.1");
    libraryHandle = dlopen(loadPath.c_str(), RTLD_NOW);
    

    if(nullptr == libraryHandle){
        return false;
    }

    zetMetricGroupGet = reinterpret_cast<decltype(zetMetricGroupGet)>(dlsym(libraryHandle, "zetMetricGroupGet"));
    if(nullptr == zetMetricGroupGet){
        log<Verbosity::error>("Missing symbol zetMetricGroupGet in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGroupGetProperties = reinterpret_cast<decltype(zetMetricGroupGetProperties)>(dlsym(libraryHandle, "zetMetricGroupGetProperties"));
    if(nullptr == zetMetricGroupGetProperties){
        log<Verbosity::error>("Missing symbol zetMetricGroupGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGroupGetGlobalTimestampsExp = reinterpret_cast<decltype(zetMetricGroupGetGlobalTimestampsExp)>(dlsym(libraryHandle, "zetMetricGroupGetGlobalTimestampsExp"));
    if(nullptr == zetMetricGroupGetGlobalTimestampsExp){
        log<Verbosity::error>("Missing symbol zetMetricGroupGetGlobalTimestampsExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGroupGetExportDataExp = reinterpret_cast<decltype(zetMetricGroupGetExportDataExp)>(dlsym(libraryHandle, "zetMetricGroupGetExportDataExp"));
    if(nullptr == zetMetricGroupGetExportDataExp){
        log<Verbosity::error>("Missing symbol zetMetricGroupGetExportDataExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGroupCalculateMetricValues = reinterpret_cast<decltype(zetMetricGroupCalculateMetricValues)>(dlsym(libraryHandle, "zetMetricGroupCalculateMetricValues"));
    if(nullptr == zetMetricGroupCalculateMetricValues){
        log<Verbosity::error>("Missing symbol zetMetricGroupCalculateMetricValues in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGroupCalculateMultipleMetricValuesExp = reinterpret_cast<decltype(zetMetricGroupCalculateMultipleMetricValuesExp)>(dlsym(libraryHandle, "zetMetricGroupCalculateMultipleMetricValuesExp"));
    if(nullptr == zetMetricGroupCalculateMultipleMetricValuesExp){
        log<Verbosity::error>("Missing symbol zetMetricGroupCalculateMultipleMetricValuesExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGet = reinterpret_cast<decltype(zetMetricGet)>(dlsym(libraryHandle, "zetMetricGet"));
    if(nullptr == zetMetricGet){
        log<Verbosity::error>("Missing symbol zetMetricGet in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricGetProperties = reinterpret_cast<decltype(zetMetricGetProperties)>(dlsym(libraryHandle, "zetMetricGetProperties"));
    if(nullptr == zetMetricGetProperties){
        log<Verbosity::error>("Missing symbol zetMetricGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetContextActivateMetricGroups = reinterpret_cast<decltype(zetContextActivateMetricGroups)>(dlsym(libraryHandle, "zetContextActivateMetricGroups"));
    if(nullptr == zetContextActivateMetricGroups){
        log<Verbosity::error>("Missing symbol zetContextActivateMetricGroups in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricStreamerOpen = reinterpret_cast<decltype(zetMetricStreamerOpen)>(dlsym(libraryHandle, "zetMetricStreamerOpen"));
    if(nullptr == zetMetricStreamerOpen){
        log<Verbosity::error>("Missing symbol zetMetricStreamerOpen in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricStreamerReadData = reinterpret_cast<decltype(zetMetricStreamerReadData)>(dlsym(libraryHandle, "zetMetricStreamerReadData"));
    if(nullptr == zetMetricStreamerReadData){
        log<Verbosity::error>("Missing symbol zetMetricStreamerReadData in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricStreamerClose = reinterpret_cast<decltype(zetMetricStreamerClose)>(dlsym(libraryHandle, "zetMetricStreamerClose"));
    if(nullptr == zetMetricStreamerClose){
        log<Verbosity::error>("Missing symbol zetMetricStreamerClose in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricQueryPoolCreate = reinterpret_cast<decltype(zetMetricQueryPoolCreate)>(dlsym(libraryHandle, "zetMetricQueryPoolCreate"));
    if(nullptr == zetMetricQueryPoolCreate){
        log<Verbosity::error>("Missing symbol zetMetricQueryPoolCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricQueryPoolDestroy = reinterpret_cast<decltype(zetMetricQueryPoolDestroy)>(dlsym(libraryHandle, "zetMetricQueryPoolDestroy"));
    if(nullptr == zetMetricQueryPoolDestroy){
        log<Verbosity::error>("Missing symbol zetMetricQueryPoolDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricQueryCreate = reinterpret_cast<decltype(zetMetricQueryCreate)>(dlsym(libraryHandle, "zetMetricQueryCreate"));
    if(nullptr == zetMetricQueryCreate){
        log<Verbosity::error>("Missing symbol zetMetricQueryCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricQueryDestroy = reinterpret_cast<decltype(zetMetricQueryDestroy)>(dlsym(libraryHandle, "zetMetricQueryDestroy"));
    if(nullptr == zetMetricQueryDestroy){
        log<Verbosity::error>("Missing symbol zetMetricQueryDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricQueryReset = reinterpret_cast<decltype(zetMetricQueryReset)>(dlsym(libraryHandle, "zetMetricQueryReset"));
    if(nullptr == zetMetricQueryReset){
        log<Verbosity::error>("Missing symbol zetMetricQueryReset in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetMetricQueryGetData = reinterpret_cast<decltype(zetMetricQueryGetData)>(dlsym(libraryHandle, "zetMetricQueryGetData"));
    if(nullptr == zetMetricQueryGetData){
        log<Verbosity::error>("Missing symbol zetMetricQueryGetData in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetCommandListAppendMetricQueryBegin = reinterpret_cast<decltype(zetCommandListAppendMetricQueryBegin)>(dlsym(libraryHandle, "zetCommandListAppendMetricQueryBegin"));
    if(nullptr == zetCommandListAppendMetricQueryBegin){
        log<Verbosity::error>("Missing symbol zetCommandListAppendMetricQueryBegin in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetCommandListAppendMetricQueryEnd = reinterpret_cast<decltype(zetCommandListAppendMetricQueryEnd)>(dlsym(libraryHandle, "zetCommandListAppendMetricQueryEnd"));
    if(nullptr == zetCommandListAppendMetricQueryEnd){
        log<Verbosity::error>("Missing symbol zetCommandListAppendMetricQueryEnd in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetCommandListAppendMetricMemoryBarrier = reinterpret_cast<decltype(zetCommandListAppendMetricMemoryBarrier)>(dlsym(libraryHandle, "zetCommandListAppendMetricMemoryBarrier"));
    if(nullptr == zetCommandListAppendMetricMemoryBarrier){
        log<Verbosity::error>("Missing symbol zetCommandListAppendMetricMemoryBarrier in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetCommandListAppendMetricStreamerMarker = reinterpret_cast<decltype(zetCommandListAppendMetricStreamerMarker)>(dlsym(libraryHandle, "zetCommandListAppendMetricStreamerMarker"));
    if(nullptr == zetCommandListAppendMetricStreamerMarker){
        log<Verbosity::error>("Missing symbol zetCommandListAppendMetricStreamerMarker in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetTracerExpCreate = reinterpret_cast<decltype(zetTracerExpCreate)>(dlsym(libraryHandle, "zetTracerExpCreate"));
    if(nullptr == zetTracerExpCreate){
        log<Verbosity::error>("Missing symbol zetTracerExpCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetTracerExpDestroy = reinterpret_cast<decltype(zetTracerExpDestroy)>(dlsym(libraryHandle, "zetTracerExpDestroy"));
    if(nullptr == zetTracerExpDestroy){
        log<Verbosity::error>("Missing symbol zetTracerExpDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetTracerExpSetPrologues = reinterpret_cast<decltype(zetTracerExpSetPrologues)>(dlsym(libraryHandle, "zetTracerExpSetPrologues"));
    if(nullptr == zetTracerExpSetPrologues){
        log<Verbosity::error>("Missing symbol zetTracerExpSetPrologues in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetTracerExpSetEpilogues = reinterpret_cast<decltype(zetTracerExpSetEpilogues)>(dlsym(libraryHandle, "zetTracerExpSetEpilogues"));
    if(nullptr == zetTracerExpSetEpilogues){
        log<Verbosity::error>("Missing symbol zetTracerExpSetEpilogues in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetTracerExpSetEnabled = reinterpret_cast<decltype(zetTracerExpSetEnabled)>(dlsym(libraryHandle, "zetTracerExpSetEnabled"));
    if(nullptr == zetTracerExpSetEnabled){
        log<Verbosity::error>("Missing symbol zetTracerExpSetEnabled in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetDeviceGetDebugProperties = reinterpret_cast<decltype(zetDeviceGetDebugProperties)>(dlsym(libraryHandle, "zetDeviceGetDebugProperties"));
    if(nullptr == zetDeviceGetDebugProperties){
        log<Verbosity::error>("Missing symbol zetDeviceGetDebugProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetDebugAttach = reinterpret_cast<decltype(zetDebugAttach)>(dlsym(libraryHandle, "zetDebugAttach"));
    if(nullptr == zetDebugAttach){
        log<Verbosity::error>("Missing symbol zetDebugAttach in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetDebugDetach = reinterpret_cast<decltype(zetDebugDetach)>(dlsym(libraryHandle, "zetDebugDetach"));
    if(nullptr == zetDebugDetach){
        log<Verbosity::error>("Missing symbol zetDebugDetach in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zetKernelGetProfileInfo = reinterpret_cast<decltype(zetKernelGetProfileInfo)>(dlsym(libraryHandle, "zetKernelGetProfileInfo"));
    if(nullptr == zetKernelGetProfileInfo){
        log<Verbosity::error>("Missing symbol zetKernelGetProfileInfo in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceReset = reinterpret_cast<decltype(zesDeviceReset)>(dlsym(libraryHandle, "zesDeviceReset"));
    if(nullptr == zesDeviceReset){
        log<Verbosity::error>("Missing symbol zesDeviceReset in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceResetExt = reinterpret_cast<decltype(zesDeviceResetExt)>(dlsym(libraryHandle, "zesDeviceResetExt"));
    if(nullptr == zesDeviceResetExt){
        log<Verbosity::debug>("Missing symbol zesDeviceResetExt in %s", loadPath.c_str());
    }
    zesDeviceEnumPowerDomains = reinterpret_cast<decltype(zesDeviceEnumPowerDomains)>(dlsym(libraryHandle, "zesDeviceEnumPowerDomains"));
    if(nullptr == zesDeviceEnumPowerDomains){
        log<Verbosity::error>("Missing symbol zesDeviceEnumPowerDomains in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceGetCardPowerDomain = reinterpret_cast<decltype(zesDeviceGetCardPowerDomain)>(dlsym(libraryHandle, "zesDeviceGetCardPowerDomain"));
    if(nullptr == zesDeviceGetCardPowerDomain){
        log<Verbosity::error>("Missing symbol zesDeviceGetCardPowerDomain in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerGetProperties = reinterpret_cast<decltype(zesPowerGetProperties)>(dlsym(libraryHandle, "zesPowerGetProperties"));
    if(nullptr == zesPowerGetProperties){
        log<Verbosity::error>("Missing symbol zesPowerGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerGetEnergyCounter = reinterpret_cast<decltype(zesPowerGetEnergyCounter)>(dlsym(libraryHandle, "zesPowerGetEnergyCounter"));
    if(nullptr == zesPowerGetEnergyCounter){
        log<Verbosity::error>("Missing symbol zesPowerGetEnergyCounter in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerGetLimits = reinterpret_cast<decltype(zesPowerGetLimits)>(dlsym(libraryHandle, "zesPowerGetLimits"));
    if(nullptr == zesPowerGetLimits){
        log<Verbosity::error>("Missing symbol zesPowerGetLimits in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerSetLimits = reinterpret_cast<decltype(zesPowerSetLimits)>(dlsym(libraryHandle, "zesPowerSetLimits"));
    if(nullptr == zesPowerSetLimits){
        log<Verbosity::error>("Missing symbol zesPowerSetLimits in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerGetLimitsExt = reinterpret_cast<decltype(zesPowerGetLimitsExt)>(dlsym(libraryHandle, "zesPowerGetLimitsExt"));
    if(nullptr == zesPowerGetLimitsExt){
        log<Verbosity::error>("Missing symbol zesPowerGetLimitsExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerSetLimitsExt = reinterpret_cast<decltype(zesPowerSetLimitsExt)>(dlsym(libraryHandle, "zesPowerSetLimitsExt"));
    if(nullptr == zesPowerSetLimitsExt){
        log<Verbosity::error>("Missing symbol zesPowerSetLimitsExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerGetEnergyThreshold = reinterpret_cast<decltype(zesPowerGetEnergyThreshold)>(dlsym(libraryHandle, "zesPowerGetEnergyThreshold"));
    if(nullptr == zesPowerGetEnergyThreshold){
        log<Verbosity::error>("Missing symbol zesPowerGetEnergyThreshold in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPowerSetEnergyThreshold = reinterpret_cast<decltype(zesPowerSetEnergyThreshold)>(dlsym(libraryHandle, "zesPowerSetEnergyThreshold"));
    if(nullptr == zesPowerSetEnergyThreshold){
        log<Verbosity::error>("Missing symbol zesPowerSetEnergyThreshold in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEventRegister = reinterpret_cast<decltype(zesDeviceEventRegister)>(dlsym(libraryHandle, "zesDeviceEventRegister"));
    if(nullptr == zesDeviceEventRegister){
        log<Verbosity::error>("Missing symbol zesDeviceEventRegister in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDriverEventListen = reinterpret_cast<decltype(zesDriverEventListen)>(dlsym(libraryHandle, "zesDriverEventListen"));
    if(nullptr == zesDriverEventListen){
        log<Verbosity::error>("Missing symbol zesDriverEventListen in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDriverEventListenEx = reinterpret_cast<decltype(zesDriverEventListenEx)>(dlsym(libraryHandle, "zesDriverEventListenEx"));
    if(nullptr == zesDriverEventListenEx){
        log<Verbosity::error>("Missing symbol zesDriverEventListenEx in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumTemperatureSensors = reinterpret_cast<decltype(zesDeviceEnumTemperatureSensors)>(dlsym(libraryHandle, "zesDeviceEnumTemperatureSensors"));
    if(nullptr == zesDeviceEnumTemperatureSensors){
        log<Verbosity::error>("Missing symbol zesDeviceEnumTemperatureSensors in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesTemperatureGetProperties = reinterpret_cast<decltype(zesTemperatureGetProperties)>(dlsym(libraryHandle, "zesTemperatureGetProperties"));
    if(nullptr == zesTemperatureGetProperties){
        log<Verbosity::error>("Missing symbol zesTemperatureGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesTemperatureGetConfig = reinterpret_cast<decltype(zesTemperatureGetConfig)>(dlsym(libraryHandle, "zesTemperatureGetConfig"));
    if(nullptr == zesTemperatureGetConfig){
        log<Verbosity::error>("Missing symbol zesTemperatureGetConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesTemperatureSetConfig = reinterpret_cast<decltype(zesTemperatureSetConfig)>(dlsym(libraryHandle, "zesTemperatureSetConfig"));
    if(nullptr == zesTemperatureSetConfig){
        log<Verbosity::error>("Missing symbol zesTemperatureSetConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesTemperatureGetState = reinterpret_cast<decltype(zesTemperatureGetState)>(dlsym(libraryHandle, "zesTemperatureGetState"));
    if(nullptr == zesTemperatureGetState){
        log<Verbosity::error>("Missing symbol zesTemperatureGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumRasErrorSets = reinterpret_cast<decltype(zesDeviceEnumRasErrorSets)>(dlsym(libraryHandle, "zesDeviceEnumRasErrorSets"));
    if(nullptr == zesDeviceEnumRasErrorSets){
        log<Verbosity::error>("Missing symbol zesDeviceEnumRasErrorSets in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesRasGetProperties = reinterpret_cast<decltype(zesRasGetProperties)>(dlsym(libraryHandle, "zesRasGetProperties"));
    if(nullptr == zesRasGetProperties){
        log<Verbosity::error>("Missing symbol zesRasGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesRasGetConfig = reinterpret_cast<decltype(zesRasGetConfig)>(dlsym(libraryHandle, "zesRasGetConfig"));
    if(nullptr == zesRasGetConfig){
        log<Verbosity::error>("Missing symbol zesRasGetConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesRasSetConfig = reinterpret_cast<decltype(zesRasSetConfig)>(dlsym(libraryHandle, "zesRasSetConfig"));
    if(nullptr == zesRasSetConfig){
        log<Verbosity::error>("Missing symbol zesRasSetConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesRasGetState = reinterpret_cast<decltype(zesRasGetState)>(dlsym(libraryHandle, "zesRasGetState"));
    if(nullptr == zesRasGetState){
        log<Verbosity::error>("Missing symbol zesRasGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumFrequencyDomains = reinterpret_cast<decltype(zesDeviceEnumFrequencyDomains)>(dlsym(libraryHandle, "zesDeviceEnumFrequencyDomains"));
    if(nullptr == zesDeviceEnumFrequencyDomains){
        log<Verbosity::error>("Missing symbol zesDeviceEnumFrequencyDomains in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyGetProperties = reinterpret_cast<decltype(zesFrequencyGetProperties)>(dlsym(libraryHandle, "zesFrequencyGetProperties"));
    if(nullptr == zesFrequencyGetProperties){
        log<Verbosity::error>("Missing symbol zesFrequencyGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyGetAvailableClocks = reinterpret_cast<decltype(zesFrequencyGetAvailableClocks)>(dlsym(libraryHandle, "zesFrequencyGetAvailableClocks"));
    if(nullptr == zesFrequencyGetAvailableClocks){
        log<Verbosity::error>("Missing symbol zesFrequencyGetAvailableClocks in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyGetRange = reinterpret_cast<decltype(zesFrequencyGetRange)>(dlsym(libraryHandle, "zesFrequencyGetRange"));
    if(nullptr == zesFrequencyGetRange){
        log<Verbosity::error>("Missing symbol zesFrequencyGetRange in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencySetRange = reinterpret_cast<decltype(zesFrequencySetRange)>(dlsym(libraryHandle, "zesFrequencySetRange"));
    if(nullptr == zesFrequencySetRange){
        log<Verbosity::error>("Missing symbol zesFrequencySetRange in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyGetState = reinterpret_cast<decltype(zesFrequencyGetState)>(dlsym(libraryHandle, "zesFrequencyGetState"));
    if(nullptr == zesFrequencyGetState){
        log<Verbosity::error>("Missing symbol zesFrequencyGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyGetThrottleTime = reinterpret_cast<decltype(zesFrequencyGetThrottleTime)>(dlsym(libraryHandle, "zesFrequencyGetThrottleTime"));
    if(nullptr == zesFrequencyGetThrottleTime){
        log<Verbosity::error>("Missing symbol zesFrequencyGetThrottleTime in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcGetCapabilities = reinterpret_cast<decltype(zesFrequencyOcGetCapabilities)>(dlsym(libraryHandle, "zesFrequencyOcGetCapabilities"));
    if(nullptr == zesFrequencyOcGetCapabilities){
        log<Verbosity::error>("Missing symbol zesFrequencyOcGetCapabilities in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcGetVoltageTarget = reinterpret_cast<decltype(zesFrequencyOcGetVoltageTarget)>(dlsym(libraryHandle, "zesFrequencyOcGetVoltageTarget"));
    if(nullptr == zesFrequencyOcGetVoltageTarget){
        log<Verbosity::error>("Missing symbol zesFrequencyOcGetVoltageTarget in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcSetVoltageTarget = reinterpret_cast<decltype(zesFrequencyOcSetVoltageTarget)>(dlsym(libraryHandle, "zesFrequencyOcSetVoltageTarget"));
    if(nullptr == zesFrequencyOcSetVoltageTarget){
        log<Verbosity::error>("Missing symbol zesFrequencyOcSetVoltageTarget in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcSetMode = reinterpret_cast<decltype(zesFrequencyOcSetMode)>(dlsym(libraryHandle, "zesFrequencyOcSetMode"));
    if(nullptr == zesFrequencyOcSetMode){
        log<Verbosity::error>("Missing symbol zesFrequencyOcSetMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcGetMode = reinterpret_cast<decltype(zesFrequencyOcGetMode)>(dlsym(libraryHandle, "zesFrequencyOcGetMode"));
    if(nullptr == zesFrequencyOcGetMode){
        log<Verbosity::error>("Missing symbol zesFrequencyOcGetMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcGetIccMax = reinterpret_cast<decltype(zesFrequencyOcGetIccMax)>(dlsym(libraryHandle, "zesFrequencyOcGetIccMax"));
    if(nullptr == zesFrequencyOcGetIccMax){
        log<Verbosity::error>("Missing symbol zesFrequencyOcGetIccMax in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcSetIccMax = reinterpret_cast<decltype(zesFrequencyOcSetIccMax)>(dlsym(libraryHandle, "zesFrequencyOcSetIccMax"));
    if(nullptr == zesFrequencyOcSetIccMax){
        log<Verbosity::error>("Missing symbol zesFrequencyOcSetIccMax in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcGetTjMax = reinterpret_cast<decltype(zesFrequencyOcGetTjMax)>(dlsym(libraryHandle, "zesFrequencyOcGetTjMax"));
    if(nullptr == zesFrequencyOcGetTjMax){
        log<Verbosity::error>("Missing symbol zesFrequencyOcGetTjMax in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesFrequencyOcSetTjMax = reinterpret_cast<decltype(zesFrequencyOcSetTjMax)>(dlsym(libraryHandle, "zesFrequencyOcSetTjMax"));
    if(nullptr == zesFrequencyOcSetTjMax){
        log<Verbosity::error>("Missing symbol zesFrequencyOcSetTjMax in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumEngineGroups = reinterpret_cast<decltype(zesDeviceEnumEngineGroups)>(dlsym(libraryHandle, "zesDeviceEnumEngineGroups"));
    if(nullptr == zesDeviceEnumEngineGroups){
        log<Verbosity::error>("Missing symbol zesDeviceEnumEngineGroups in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumSchedulers = reinterpret_cast<decltype(zesDeviceEnumSchedulers)>(dlsym(libraryHandle, "zesDeviceEnumSchedulers"));
    if(nullptr == zesDeviceEnumSchedulers){
        log<Verbosity::error>("Missing symbol zesDeviceEnumSchedulers in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerGetProperties = reinterpret_cast<decltype(zesSchedulerGetProperties)>(dlsym(libraryHandle, "zesSchedulerGetProperties"));
    if(nullptr == zesSchedulerGetProperties){
        log<Verbosity::error>("Missing symbol zesSchedulerGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerGetCurrentMode = reinterpret_cast<decltype(zesSchedulerGetCurrentMode)>(dlsym(libraryHandle, "zesSchedulerGetCurrentMode"));
    if(nullptr == zesSchedulerGetCurrentMode){
        log<Verbosity::error>("Missing symbol zesSchedulerGetCurrentMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerGetTimeoutModeProperties = reinterpret_cast<decltype(zesSchedulerGetTimeoutModeProperties)>(dlsym(libraryHandle, "zesSchedulerGetTimeoutModeProperties"));
    if(nullptr == zesSchedulerGetTimeoutModeProperties){
        log<Verbosity::error>("Missing symbol zesSchedulerGetTimeoutModeProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerGetTimesliceModeProperties = reinterpret_cast<decltype(zesSchedulerGetTimesliceModeProperties)>(dlsym(libraryHandle, "zesSchedulerGetTimesliceModeProperties"));
    if(nullptr == zesSchedulerGetTimesliceModeProperties){
        log<Verbosity::error>("Missing symbol zesSchedulerGetTimesliceModeProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerSetTimeoutMode = reinterpret_cast<decltype(zesSchedulerSetTimeoutMode)>(dlsym(libraryHandle, "zesSchedulerSetTimeoutMode"));
    if(nullptr == zesSchedulerSetTimeoutMode){
        log<Verbosity::error>("Missing symbol zesSchedulerSetTimeoutMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerSetTimesliceMode = reinterpret_cast<decltype(zesSchedulerSetTimesliceMode)>(dlsym(libraryHandle, "zesSchedulerSetTimesliceMode"));
    if(nullptr == zesSchedulerSetTimesliceMode){
        log<Verbosity::error>("Missing symbol zesSchedulerSetTimesliceMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerSetExclusiveMode = reinterpret_cast<decltype(zesSchedulerSetExclusiveMode)>(dlsym(libraryHandle, "zesSchedulerSetExclusiveMode"));
    if(nullptr == zesSchedulerSetExclusiveMode){
        log<Verbosity::error>("Missing symbol zesSchedulerSetExclusiveMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesSchedulerSetComputeUnitDebugMode = reinterpret_cast<decltype(zesSchedulerSetComputeUnitDebugMode)>(dlsym(libraryHandle, "zesSchedulerSetComputeUnitDebugMode"));
    if(nullptr == zesSchedulerSetComputeUnitDebugMode){
        log<Verbosity::error>("Missing symbol zesSchedulerSetComputeUnitDebugMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesEngineGetProperties = reinterpret_cast<decltype(zesEngineGetProperties)>(dlsym(libraryHandle, "zesEngineGetProperties"));
    if(nullptr == zesEngineGetProperties){
        log<Verbosity::error>("Missing symbol zesEngineGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesEngineGetActivity = reinterpret_cast<decltype(zesEngineGetActivity)>(dlsym(libraryHandle, "zesEngineGetActivity"));
    if(nullptr == zesEngineGetActivity){
        log<Verbosity::error>("Missing symbol zesEngineGetActivity in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceGetState = reinterpret_cast<decltype(zesDeviceGetState)>(dlsym(libraryHandle, "zesDeviceGetState"));
    if(nullptr == zesDeviceGetState){
        log<Verbosity::error>("Missing symbol zesDeviceGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceProcessesGetState = reinterpret_cast<decltype(zesDeviceProcessesGetState)>(dlsym(libraryHandle, "zesDeviceProcessesGetState"));
    if(nullptr == zesDeviceProcessesGetState){
        log<Verbosity::error>("Missing symbol zesDeviceProcessesGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDevicePciGetProperties = reinterpret_cast<decltype(zesDevicePciGetProperties)>(dlsym(libraryHandle, "zesDevicePciGetProperties"));
    if(nullptr == zesDevicePciGetProperties){
        log<Verbosity::error>("Missing symbol zesDevicePciGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDevicePciGetState = reinterpret_cast<decltype(zesDevicePciGetState)>(dlsym(libraryHandle, "zesDevicePciGetState"));
    if(nullptr == zesDevicePciGetState){
        log<Verbosity::error>("Missing symbol zesDevicePciGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDevicePciGetBars = reinterpret_cast<decltype(zesDevicePciGetBars)>(dlsym(libraryHandle, "zesDevicePciGetBars"));
    if(nullptr == zesDevicePciGetBars){
        log<Verbosity::error>("Missing symbol zesDevicePciGetBars in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDevicePciGetStats = reinterpret_cast<decltype(zesDevicePciGetStats)>(dlsym(libraryHandle, "zesDevicePciGetStats"));
    if(nullptr == zesDevicePciGetStats){
        log<Verbosity::error>("Missing symbol zesDevicePciGetStats in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceGetProperties = reinterpret_cast<decltype(zesDeviceGetProperties)>(dlsym(libraryHandle, "zesDeviceGetProperties"));
    if(nullptr == zesDeviceGetProperties){
        log<Verbosity::error>("Missing symbol zesDeviceGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumMemoryModules = reinterpret_cast<decltype(zesDeviceEnumMemoryModules)>(dlsym(libraryHandle, "zesDeviceEnumMemoryModules"));
    if(nullptr == zesDeviceEnumMemoryModules){
        log<Verbosity::error>("Missing symbol zesDeviceEnumMemoryModules in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesMemoryGetProperties = reinterpret_cast<decltype(zesMemoryGetProperties)>(dlsym(libraryHandle, "zesMemoryGetProperties"));
    if(nullptr == zesMemoryGetProperties){
        log<Verbosity::error>("Missing symbol zesMemoryGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesMemoryGetState = reinterpret_cast<decltype(zesMemoryGetState)>(dlsym(libraryHandle, "zesMemoryGetState"));
    if(nullptr == zesMemoryGetState){
        log<Verbosity::error>("Missing symbol zesMemoryGetState in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesMemoryGetBandwidth = reinterpret_cast<decltype(zesMemoryGetBandwidth)>(dlsym(libraryHandle, "zesMemoryGetBandwidth"));
    if(nullptr == zesMemoryGetBandwidth){
        log<Verbosity::error>("Missing symbol zesMemoryGetBandwidth in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumPerformanceFactorDomains = reinterpret_cast<decltype(zesDeviceEnumPerformanceFactorDomains)>(dlsym(libraryHandle, "zesDeviceEnumPerformanceFactorDomains"));
    if(nullptr == zesDeviceEnumPerformanceFactorDomains){
        log<Verbosity::error>("Missing symbol zesDeviceEnumPerformanceFactorDomains in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPerformanceFactorGetProperties = reinterpret_cast<decltype(zesPerformanceFactorGetProperties)>(dlsym(libraryHandle, "zesPerformanceFactorGetProperties"));
    if(nullptr == zesPerformanceFactorGetProperties){
        log<Verbosity::error>("Missing symbol zesPerformanceFactorGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPerformanceFactorGetConfig = reinterpret_cast<decltype(zesPerformanceFactorGetConfig)>(dlsym(libraryHandle, "zesPerformanceFactorGetConfig"));
    if(nullptr == zesPerformanceFactorGetConfig){
        log<Verbosity::error>("Missing symbol zesPerformanceFactorGetConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesPerformanceFactorSetConfig = reinterpret_cast<decltype(zesPerformanceFactorSetConfig)>(dlsym(libraryHandle, "zesPerformanceFactorSetConfig"));
    if(nullptr == zesPerformanceFactorSetConfig){
        log<Verbosity::error>("Missing symbol zesPerformanceFactorSetConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesDeviceEnumStandbyDomains = reinterpret_cast<decltype(zesDeviceEnumStandbyDomains)>(dlsym(libraryHandle, "zesDeviceEnumStandbyDomains"));
    if(nullptr == zesDeviceEnumStandbyDomains){
        log<Verbosity::error>("Missing symbol zesDeviceEnumStandbyDomains in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesStandbyGetProperties = reinterpret_cast<decltype(zesStandbyGetProperties)>(dlsym(libraryHandle, "zesStandbyGetProperties"));
    if(nullptr == zesStandbyGetProperties){
        log<Verbosity::error>("Missing symbol zesStandbyGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesStandbyGetMode = reinterpret_cast<decltype(zesStandbyGetMode)>(dlsym(libraryHandle, "zesStandbyGetMode"));
    if(nullptr == zesStandbyGetMode){
        log<Verbosity::error>("Missing symbol zesStandbyGetMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zesStandbySetMode = reinterpret_cast<decltype(zesStandbySetMode)>(dlsym(libraryHandle, "zesStandbySetMode"));
    if(nullptr == zesStandbySetMode){
        log<Verbosity::error>("Missing symbol zesStandbySetMode in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeInit = reinterpret_cast<decltype(zeInit)>(dlsym(libraryHandle, "zeInit"));
    if(nullptr == zeInit){
        log<Verbosity::error>("Missing symbol zeInit in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemoryRangesBarrier = reinterpret_cast<decltype(zeCommandListAppendMemoryRangesBarrier)>(dlsym(libraryHandle, "zeCommandListAppendMemoryRangesBarrier"));
    if(nullptr == zeCommandListAppendMemoryRangesBarrier){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemoryRangesBarrier in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextSystemBarrier = reinterpret_cast<decltype(zeContextSystemBarrier)>(dlsym(libraryHandle, "zeContextSystemBarrier"));
    if(nullptr == zeContextSystemBarrier){
        log<Verbosity::error>("Missing symbol zeContextSystemBarrier in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListCreate = reinterpret_cast<decltype(zeCommandListCreate)>(dlsym(libraryHandle, "zeCommandListCreate"));
    if(nullptr == zeCommandListCreate){
        log<Verbosity::error>("Missing symbol zeCommandListCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListCreateImmediate = reinterpret_cast<decltype(zeCommandListCreateImmediate)>(dlsym(libraryHandle, "zeCommandListCreateImmediate"));
    if(nullptr == zeCommandListCreateImmediate){
        log<Verbosity::error>("Missing symbol zeCommandListCreateImmediate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListDestroy = reinterpret_cast<decltype(zeCommandListDestroy)>(dlsym(libraryHandle, "zeCommandListDestroy"));
    if(nullptr == zeCommandListDestroy){
        log<Verbosity::error>("Missing symbol zeCommandListDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListClose = reinterpret_cast<decltype(zeCommandListClose)>(dlsym(libraryHandle, "zeCommandListClose"));
    if(nullptr == zeCommandListClose){
        log<Verbosity::error>("Missing symbol zeCommandListClose in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListReset = reinterpret_cast<decltype(zeCommandListReset)>(dlsym(libraryHandle, "zeCommandListReset"));
    if(nullptr == zeCommandListReset){
        log<Verbosity::error>("Missing symbol zeCommandListReset in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendWriteGlobalTimestamp = reinterpret_cast<decltype(zeCommandListAppendWriteGlobalTimestamp)>(dlsym(libraryHandle, "zeCommandListAppendWriteGlobalTimestamp"));
    if(nullptr == zeCommandListAppendWriteGlobalTimestamp){
        log<Verbosity::error>("Missing symbol zeCommandListAppendWriteGlobalTimestamp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandQueueCreate = reinterpret_cast<decltype(zeCommandQueueCreate)>(dlsym(libraryHandle, "zeCommandQueueCreate"));
    if(nullptr == zeCommandQueueCreate){
        log<Verbosity::error>("Missing symbol zeCommandQueueCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandQueueDestroy = reinterpret_cast<decltype(zeCommandQueueDestroy)>(dlsym(libraryHandle, "zeCommandQueueDestroy"));
    if(nullptr == zeCommandQueueDestroy){
        log<Verbosity::error>("Missing symbol zeCommandQueueDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandQueueExecuteCommandLists = reinterpret_cast<decltype(zeCommandQueueExecuteCommandLists)>(dlsym(libraryHandle, "zeCommandQueueExecuteCommandLists"));
    if(nullptr == zeCommandQueueExecuteCommandLists){
        log<Verbosity::error>("Missing symbol zeCommandQueueExecuteCommandLists in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandQueueSynchronize = reinterpret_cast<decltype(zeCommandQueueSynchronize)>(dlsym(libraryHandle, "zeCommandQueueSynchronize"));
    if(nullptr == zeCommandQueueSynchronize){
        log<Verbosity::error>("Missing symbol zeCommandQueueSynchronize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextCreate = reinterpret_cast<decltype(zeContextCreate)>(dlsym(libraryHandle, "zeContextCreate"));
    if(nullptr == zeContextCreate){
        log<Verbosity::error>("Missing symbol zeContextCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextCreateEx = reinterpret_cast<decltype(zeContextCreateEx)>(dlsym(libraryHandle, "zeContextCreateEx"));
    if(nullptr == zeContextCreateEx){
        log<Verbosity::error>("Missing symbol zeContextCreateEx in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextDestroy = reinterpret_cast<decltype(zeContextDestroy)>(dlsym(libraryHandle, "zeContextDestroy"));
    if(nullptr == zeContextDestroy){
        log<Verbosity::error>("Missing symbol zeContextDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextGetStatus = reinterpret_cast<decltype(zeContextGetStatus)>(dlsym(libraryHandle, "zeContextGetStatus"));
    if(nullptr == zeContextGetStatus){
        log<Verbosity::error>("Missing symbol zeContextGetStatus in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemoryCopy = reinterpret_cast<decltype(zeCommandListAppendMemoryCopy)>(dlsym(libraryHandle, "zeCommandListAppendMemoryCopy"));
    if(nullptr == zeCommandListAppendMemoryCopy){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemoryCopy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemoryFill = reinterpret_cast<decltype(zeCommandListAppendMemoryFill)>(dlsym(libraryHandle, "zeCommandListAppendMemoryFill"));
    if(nullptr == zeCommandListAppendMemoryFill){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemoryFill in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemoryCopyRegion = reinterpret_cast<decltype(zeCommandListAppendMemoryCopyRegion)>(dlsym(libraryHandle, "zeCommandListAppendMemoryCopyRegion"));
    if(nullptr == zeCommandListAppendMemoryCopyRegion){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemoryCopyRegion in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemoryCopyFromContext = reinterpret_cast<decltype(zeCommandListAppendMemoryCopyFromContext)>(dlsym(libraryHandle, "zeCommandListAppendMemoryCopyFromContext"));
    if(nullptr == zeCommandListAppendMemoryCopyFromContext){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemoryCopyFromContext in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemoryPrefetch = reinterpret_cast<decltype(zeCommandListAppendMemoryPrefetch)>(dlsym(libraryHandle, "zeCommandListAppendMemoryPrefetch"));
    if(nullptr == zeCommandListAppendMemoryPrefetch){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemoryPrefetch in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendMemAdvise = reinterpret_cast<decltype(zeCommandListAppendMemAdvise)>(dlsym(libraryHandle, "zeCommandListAppendMemAdvise"));
    if(nullptr == zeCommandListAppendMemAdvise){
        log<Verbosity::error>("Missing symbol zeCommandListAppendMemAdvise in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGet = reinterpret_cast<decltype(zeDeviceGet)>(dlsym(libraryHandle, "zeDeviceGet"));
    if(nullptr == zeDeviceGet){
        log<Verbosity::error>("Missing symbol zeDeviceGet in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetSubDevices = reinterpret_cast<decltype(zeDeviceGetSubDevices)>(dlsym(libraryHandle, "zeDeviceGetSubDevices"));
    if(nullptr == zeDeviceGetSubDevices){
        log<Verbosity::error>("Missing symbol zeDeviceGetSubDevices in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetProperties = reinterpret_cast<decltype(zeDeviceGetProperties)>(dlsym(libraryHandle, "zeDeviceGetProperties"));
    if(nullptr == zeDeviceGetProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetComputeProperties = reinterpret_cast<decltype(zeDeviceGetComputeProperties)>(dlsym(libraryHandle, "zeDeviceGetComputeProperties"));
    if(nullptr == zeDeviceGetComputeProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetComputeProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetModuleProperties = reinterpret_cast<decltype(zeDeviceGetModuleProperties)>(dlsym(libraryHandle, "zeDeviceGetModuleProperties"));
    if(nullptr == zeDeviceGetModuleProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetModuleProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetCommandQueueGroupProperties = reinterpret_cast<decltype(zeDeviceGetCommandQueueGroupProperties)>(dlsym(libraryHandle, "zeDeviceGetCommandQueueGroupProperties"));
    if(nullptr == zeDeviceGetCommandQueueGroupProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetCommandQueueGroupProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetMemoryProperties = reinterpret_cast<decltype(zeDeviceGetMemoryProperties)>(dlsym(libraryHandle, "zeDeviceGetMemoryProperties"));
    if(nullptr == zeDeviceGetMemoryProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetMemoryProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetMemoryAccessProperties = reinterpret_cast<decltype(zeDeviceGetMemoryAccessProperties)>(dlsym(libraryHandle, "zeDeviceGetMemoryAccessProperties"));
    if(nullptr == zeDeviceGetMemoryAccessProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetMemoryAccessProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetCacheProperties = reinterpret_cast<decltype(zeDeviceGetCacheProperties)>(dlsym(libraryHandle, "zeDeviceGetCacheProperties"));
    if(nullptr == zeDeviceGetCacheProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetCacheProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetImageProperties = reinterpret_cast<decltype(zeDeviceGetImageProperties)>(dlsym(libraryHandle, "zeDeviceGetImageProperties"));
    if(nullptr == zeDeviceGetImageProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetImageProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetExternalMemoryProperties = reinterpret_cast<decltype(zeDeviceGetExternalMemoryProperties)>(dlsym(libraryHandle, "zeDeviceGetExternalMemoryProperties"));
    if(nullptr == zeDeviceGetExternalMemoryProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetExternalMemoryProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetP2PProperties = reinterpret_cast<decltype(zeDeviceGetP2PProperties)>(dlsym(libraryHandle, "zeDeviceGetP2PProperties"));
    if(nullptr == zeDeviceGetP2PProperties){
        log<Verbosity::error>("Missing symbol zeDeviceGetP2PProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceCanAccessPeer = reinterpret_cast<decltype(zeDeviceCanAccessPeer)>(dlsym(libraryHandle, "zeDeviceCanAccessPeer"));
    if(nullptr == zeDeviceCanAccessPeer){
        log<Verbosity::error>("Missing symbol zeDeviceCanAccessPeer in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetStatus = reinterpret_cast<decltype(zeDeviceGetStatus)>(dlsym(libraryHandle, "zeDeviceGetStatus"));
    if(nullptr == zeDeviceGetStatus){
        log<Verbosity::error>("Missing symbol zeDeviceGetStatus in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetGlobalTimestamps = reinterpret_cast<decltype(zeDeviceGetGlobalTimestamps)>(dlsym(libraryHandle, "zeDeviceGetGlobalTimestamps"));
    if(nullptr == zeDeviceGetGlobalTimestamps){
        log<Verbosity::error>("Missing symbol zeDeviceGetGlobalTimestamps in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceReserveCacheExt = reinterpret_cast<decltype(zeDeviceReserveCacheExt)>(dlsym(libraryHandle, "zeDeviceReserveCacheExt"));
    if(nullptr == zeDeviceReserveCacheExt){
        log<Verbosity::error>("Missing symbol zeDeviceReserveCacheExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceSetCacheAdviceExt = reinterpret_cast<decltype(zeDeviceSetCacheAdviceExt)>(dlsym(libraryHandle, "zeDeviceSetCacheAdviceExt"));
    if(nullptr == zeDeviceSetCacheAdviceExt){
        log<Verbosity::error>("Missing symbol zeDeviceSetCacheAdviceExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGet = reinterpret_cast<decltype(zeDriverGet)>(dlsym(libraryHandle, "zeDriverGet"));
    if(nullptr == zeDriverGet){
        log<Verbosity::error>("Missing symbol zeDriverGet in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGetApiVersion = reinterpret_cast<decltype(zeDriverGetApiVersion)>(dlsym(libraryHandle, "zeDriverGetApiVersion"));
    if(nullptr == zeDriverGetApiVersion){
        log<Verbosity::error>("Missing symbol zeDriverGetApiVersion in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGetProperties = reinterpret_cast<decltype(zeDriverGetProperties)>(dlsym(libraryHandle, "zeDriverGetProperties"));
    if(nullptr == zeDriverGetProperties){
        log<Verbosity::error>("Missing symbol zeDriverGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGetIpcProperties = reinterpret_cast<decltype(zeDriverGetIpcProperties)>(dlsym(libraryHandle, "zeDriverGetIpcProperties"));
    if(nullptr == zeDriverGetIpcProperties){
        log<Verbosity::error>("Missing symbol zeDriverGetIpcProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGetExtensionProperties = reinterpret_cast<decltype(zeDriverGetExtensionProperties)>(dlsym(libraryHandle, "zeDriverGetExtensionProperties"));
    if(nullptr == zeDriverGetExtensionProperties){
        log<Verbosity::error>("Missing symbol zeDriverGetExtensionProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGetExtensionFunctionAddress = reinterpret_cast<decltype(zeDriverGetExtensionFunctionAddress)>(dlsym(libraryHandle, "zeDriverGetExtensionFunctionAddress"));
    if(nullptr == zeDriverGetExtensionFunctionAddress){
        log<Verbosity::error>("Missing symbol zeDriverGetExtensionFunctionAddress in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDriverGetLastErrorDescription = reinterpret_cast<decltype(zeDriverGetLastErrorDescription)>(dlsym(libraryHandle, "zeDriverGetLastErrorDescription"));
    if(nullptr == zeDriverGetLastErrorDescription){
        log<Verbosity::error>("Missing symbol zeDriverGetLastErrorDescription in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventPoolCreate = reinterpret_cast<decltype(zeEventPoolCreate)>(dlsym(libraryHandle, "zeEventPoolCreate"));
    if(nullptr == zeEventPoolCreate){
        log<Verbosity::error>("Missing symbol zeEventPoolCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventPoolDestroy = reinterpret_cast<decltype(zeEventPoolDestroy)>(dlsym(libraryHandle, "zeEventPoolDestroy"));
    if(nullptr == zeEventPoolDestroy){
        log<Verbosity::error>("Missing symbol zeEventPoolDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventCreate = reinterpret_cast<decltype(zeEventCreate)>(dlsym(libraryHandle, "zeEventCreate"));
    if(nullptr == zeEventCreate){
        log<Verbosity::error>("Missing symbol zeEventCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventDestroy = reinterpret_cast<decltype(zeEventDestroy)>(dlsym(libraryHandle, "zeEventDestroy"));
    if(nullptr == zeEventDestroy){
        log<Verbosity::error>("Missing symbol zeEventDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventPoolGetIpcHandle = reinterpret_cast<decltype(zeEventPoolGetIpcHandle)>(dlsym(libraryHandle, "zeEventPoolGetIpcHandle"));
    if(nullptr == zeEventPoolGetIpcHandle){
        log<Verbosity::error>("Missing symbol zeEventPoolGetIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventPoolOpenIpcHandle = reinterpret_cast<decltype(zeEventPoolOpenIpcHandle)>(dlsym(libraryHandle, "zeEventPoolOpenIpcHandle"));
    if(nullptr == zeEventPoolOpenIpcHandle){
        log<Verbosity::error>("Missing symbol zeEventPoolOpenIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventPoolCloseIpcHandle = reinterpret_cast<decltype(zeEventPoolCloseIpcHandle)>(dlsym(libraryHandle, "zeEventPoolCloseIpcHandle"));
    if(nullptr == zeEventPoolCloseIpcHandle){
        log<Verbosity::error>("Missing symbol zeEventPoolCloseIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventPoolPutIpcHandle = reinterpret_cast<decltype(zeEventPoolPutIpcHandle)>(dlsym(libraryHandle, "zeEventPoolPutIpcHandle"));
    if(nullptr == zeEventPoolPutIpcHandle){
        log<Verbosity::error>("Missing symbol zeEventPoolPutIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendBarrier = reinterpret_cast<decltype(zeCommandListAppendBarrier)>(dlsym(libraryHandle, "zeCommandListAppendBarrier"));
    if(nullptr == zeCommandListAppendBarrier){
        log<Verbosity::error>("Missing symbol zeCommandListAppendBarrier in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendSignalEvent = reinterpret_cast<decltype(zeCommandListAppendSignalEvent)>(dlsym(libraryHandle, "zeCommandListAppendSignalEvent"));
    if(nullptr == zeCommandListAppendSignalEvent){
        log<Verbosity::error>("Missing symbol zeCommandListAppendSignalEvent in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendWaitOnEvents = reinterpret_cast<decltype(zeCommandListAppendWaitOnEvents)>(dlsym(libraryHandle, "zeCommandListAppendWaitOnEvents"));
    if(nullptr == zeCommandListAppendWaitOnEvents){
        log<Verbosity::error>("Missing symbol zeCommandListAppendWaitOnEvents in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventHostSignal = reinterpret_cast<decltype(zeEventHostSignal)>(dlsym(libraryHandle, "zeEventHostSignal"));
    if(nullptr == zeEventHostSignal){
        log<Verbosity::error>("Missing symbol zeEventHostSignal in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventHostSynchronize = reinterpret_cast<decltype(zeEventHostSynchronize)>(dlsym(libraryHandle, "zeEventHostSynchronize"));
    if(nullptr == zeEventHostSynchronize){
        log<Verbosity::error>("Missing symbol zeEventHostSynchronize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventQueryStatus = reinterpret_cast<decltype(zeEventQueryStatus)>(dlsym(libraryHandle, "zeEventQueryStatus"));
    if(nullptr == zeEventQueryStatus){
        log<Verbosity::error>("Missing symbol zeEventQueryStatus in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendEventReset = reinterpret_cast<decltype(zeCommandListAppendEventReset)>(dlsym(libraryHandle, "zeCommandListAppendEventReset"));
    if(nullptr == zeCommandListAppendEventReset){
        log<Verbosity::error>("Missing symbol zeCommandListAppendEventReset in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventHostReset = reinterpret_cast<decltype(zeEventHostReset)>(dlsym(libraryHandle, "zeEventHostReset"));
    if(nullptr == zeEventHostReset){
        log<Verbosity::error>("Missing symbol zeEventHostReset in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventQueryKernelTimestamp = reinterpret_cast<decltype(zeEventQueryKernelTimestamp)>(dlsym(libraryHandle, "zeEventQueryKernelTimestamp"));
    if(nullptr == zeEventQueryKernelTimestamp){
        log<Verbosity::error>("Missing symbol zeEventQueryKernelTimestamp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendQueryKernelTimestamps = reinterpret_cast<decltype(zeCommandListAppendQueryKernelTimestamps)>(dlsym(libraryHandle, "zeCommandListAppendQueryKernelTimestamps"));
    if(nullptr == zeCommandListAppendQueryKernelTimestamps){
        log<Verbosity::error>("Missing symbol zeCommandListAppendQueryKernelTimestamps in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventQueryTimestampsExp = reinterpret_cast<decltype(zeEventQueryTimestampsExp)>(dlsym(libraryHandle, "zeEventQueryTimestampsExp"));
    if(nullptr == zeEventQueryTimestampsExp){
        log<Verbosity::error>("Missing symbol zeEventQueryTimestampsExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeEventQueryKernelTimestampsExt = reinterpret_cast<decltype(zeEventQueryKernelTimestampsExt)>(dlsym(libraryHandle, "zeEventQueryKernelTimestampsExt"));
    if(nullptr == zeEventQueryKernelTimestampsExt){
        log<Verbosity::error>("Missing symbol zeEventQueryKernelTimestampsExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricVertexGetExp = reinterpret_cast<decltype(zeFabricVertexGetExp)>(dlsym(libraryHandle, "zeFabricVertexGetExp"));
    if(nullptr == zeFabricVertexGetExp){
        log<Verbosity::error>("Missing symbol zeFabricVertexGetExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricVertexGetSubVerticesExp = reinterpret_cast<decltype(zeFabricVertexGetSubVerticesExp)>(dlsym(libraryHandle, "zeFabricVertexGetSubVerticesExp"));
    if(nullptr == zeFabricVertexGetSubVerticesExp){
        log<Verbosity::error>("Missing symbol zeFabricVertexGetSubVerticesExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricVertexGetPropertiesExp = reinterpret_cast<decltype(zeFabricVertexGetPropertiesExp)>(dlsym(libraryHandle, "zeFabricVertexGetPropertiesExp"));
    if(nullptr == zeFabricVertexGetPropertiesExp){
        log<Verbosity::error>("Missing symbol zeFabricVertexGetPropertiesExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricVertexGetDeviceExp = reinterpret_cast<decltype(zeFabricVertexGetDeviceExp)>(dlsym(libraryHandle, "zeFabricVertexGetDeviceExp"));
    if(nullptr == zeFabricVertexGetDeviceExp){
        log<Verbosity::error>("Missing symbol zeFabricVertexGetDeviceExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDeviceGetFabricVertexExp = reinterpret_cast<decltype(zeDeviceGetFabricVertexExp)>(dlsym(libraryHandle, "zeDeviceGetFabricVertexExp"));
    if(nullptr == zeDeviceGetFabricVertexExp){
        log<Verbosity::error>("Missing symbol zeDeviceGetFabricVertexExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricEdgeGetExp = reinterpret_cast<decltype(zeFabricEdgeGetExp)>(dlsym(libraryHandle, "zeFabricEdgeGetExp"));
    if(nullptr == zeFabricEdgeGetExp){
        log<Verbosity::error>("Missing symbol zeFabricEdgeGetExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricEdgeGetVerticesExp = reinterpret_cast<decltype(zeFabricEdgeGetVerticesExp)>(dlsym(libraryHandle, "zeFabricEdgeGetVerticesExp"));
    if(nullptr == zeFabricEdgeGetVerticesExp){
        log<Verbosity::error>("Missing symbol zeFabricEdgeGetVerticesExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFabricEdgeGetPropertiesExp = reinterpret_cast<decltype(zeFabricEdgeGetPropertiesExp)>(dlsym(libraryHandle, "zeFabricEdgeGetPropertiesExp"));
    if(nullptr == zeFabricEdgeGetPropertiesExp){
        log<Verbosity::error>("Missing symbol zeFabricEdgeGetPropertiesExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFenceCreate = reinterpret_cast<decltype(zeFenceCreate)>(dlsym(libraryHandle, "zeFenceCreate"));
    if(nullptr == zeFenceCreate){
        log<Verbosity::error>("Missing symbol zeFenceCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFenceDestroy = reinterpret_cast<decltype(zeFenceDestroy)>(dlsym(libraryHandle, "zeFenceDestroy"));
    if(nullptr == zeFenceDestroy){
        log<Verbosity::error>("Missing symbol zeFenceDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFenceHostSynchronize = reinterpret_cast<decltype(zeFenceHostSynchronize)>(dlsym(libraryHandle, "zeFenceHostSynchronize"));
    if(nullptr == zeFenceHostSynchronize){
        log<Verbosity::error>("Missing symbol zeFenceHostSynchronize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFenceQueryStatus = reinterpret_cast<decltype(zeFenceQueryStatus)>(dlsym(libraryHandle, "zeFenceQueryStatus"));
    if(nullptr == zeFenceQueryStatus){
        log<Verbosity::error>("Missing symbol zeFenceQueryStatus in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeFenceReset = reinterpret_cast<decltype(zeFenceReset)>(dlsym(libraryHandle, "zeFenceReset"));
    if(nullptr == zeFenceReset){
        log<Verbosity::error>("Missing symbol zeFenceReset in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSetGlobalOffsetExp = reinterpret_cast<decltype(zeKernelSetGlobalOffsetExp)>(dlsym(libraryHandle, "zeKernelSetGlobalOffsetExp"));
    if(nullptr == zeKernelSetGlobalOffsetExp){
        log<Verbosity::error>("Missing symbol zeKernelSetGlobalOffsetExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeImageGetProperties = reinterpret_cast<decltype(zeImageGetProperties)>(dlsym(libraryHandle, "zeImageGetProperties"));
    if(nullptr == zeImageGetProperties){
        log<Verbosity::error>("Missing symbol zeImageGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeImageCreate = reinterpret_cast<decltype(zeImageCreate)>(dlsym(libraryHandle, "zeImageCreate"));
    if(nullptr == zeImageCreate){
        log<Verbosity::error>("Missing symbol zeImageCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeImageDestroy = reinterpret_cast<decltype(zeImageDestroy)>(dlsym(libraryHandle, "zeImageDestroy"));
    if(nullptr == zeImageDestroy){
        log<Verbosity::error>("Missing symbol zeImageDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSchedulingHintExp = reinterpret_cast<decltype(zeKernelSchedulingHintExp)>(dlsym(libraryHandle, "zeKernelSchedulingHintExp"));
    if(nullptr == zeKernelSchedulingHintExp){
        log<Verbosity::error>("Missing symbol zeKernelSchedulingHintExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleInspectLinkageExt = reinterpret_cast<decltype(zeModuleInspectLinkageExt)>(dlsym(libraryHandle, "zeModuleInspectLinkageExt"));
    if(nullptr == zeModuleInspectLinkageExt){
        log<Verbosity::error>("Missing symbol zeModuleInspectLinkageExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemAllocShared = reinterpret_cast<decltype(zeMemAllocShared)>(dlsym(libraryHandle, "zeMemAllocShared"));
    if(nullptr == zeMemAllocShared){
        log<Verbosity::error>("Missing symbol zeMemAllocShared in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemAllocDevice = reinterpret_cast<decltype(zeMemAllocDevice)>(dlsym(libraryHandle, "zeMemAllocDevice"));
    if(nullptr == zeMemAllocDevice){
        log<Verbosity::error>("Missing symbol zeMemAllocDevice in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemAllocHost = reinterpret_cast<decltype(zeMemAllocHost)>(dlsym(libraryHandle, "zeMemAllocHost"));
    if(nullptr == zeMemAllocHost){
        log<Verbosity::error>("Missing symbol zeMemAllocHost in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemFree = reinterpret_cast<decltype(zeMemFree)>(dlsym(libraryHandle, "zeMemFree"));
    if(nullptr == zeMemFree){
        log<Verbosity::error>("Missing symbol zeMemFree in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemGetAllocProperties = reinterpret_cast<decltype(zeMemGetAllocProperties)>(dlsym(libraryHandle, "zeMemGetAllocProperties"));
    if(nullptr == zeMemGetAllocProperties){
        log<Verbosity::error>("Missing symbol zeMemGetAllocProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemGetAddressRange = reinterpret_cast<decltype(zeMemGetAddressRange)>(dlsym(libraryHandle, "zeMemGetAddressRange"));
    if(nullptr == zeMemGetAddressRange){
        log<Verbosity::error>("Missing symbol zeMemGetAddressRange in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemGetIpcHandle = reinterpret_cast<decltype(zeMemGetIpcHandle)>(dlsym(libraryHandle, "zeMemGetIpcHandle"));
    if(nullptr == zeMemGetIpcHandle){
        log<Verbosity::error>("Missing symbol zeMemGetIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemOpenIpcHandle = reinterpret_cast<decltype(zeMemOpenIpcHandle)>(dlsym(libraryHandle, "zeMemOpenIpcHandle"));
    if(nullptr == zeMemOpenIpcHandle){
        log<Verbosity::error>("Missing symbol zeMemOpenIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemCloseIpcHandle = reinterpret_cast<decltype(zeMemCloseIpcHandle)>(dlsym(libraryHandle, "zeMemCloseIpcHandle"));
    if(nullptr == zeMemCloseIpcHandle){
        log<Verbosity::error>("Missing symbol zeMemCloseIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemPutIpcHandle = reinterpret_cast<decltype(zeMemPutIpcHandle)>(dlsym(libraryHandle, "zeMemPutIpcHandle"));
    if(nullptr == zeMemPutIpcHandle){
        log<Verbosity::error>("Missing symbol zeMemPutIpcHandle in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemFreeExt = reinterpret_cast<decltype(zeMemFreeExt)>(dlsym(libraryHandle, "zeMemFreeExt"));
    if(nullptr == zeMemFreeExt){
        log<Verbosity::error>("Missing symbol zeMemFreeExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemGetIpcHandleFromFileDescriptorExp = reinterpret_cast<decltype(zeMemGetIpcHandleFromFileDescriptorExp)>(dlsym(libraryHandle, "zeMemGetIpcHandleFromFileDescriptorExp"));
    if(nullptr == zeMemGetIpcHandleFromFileDescriptorExp){
        log<Verbosity::error>("Missing symbol zeMemGetIpcHandleFromFileDescriptorExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeMemGetFileDescriptorFromIpcHandleExp = reinterpret_cast<decltype(zeMemGetFileDescriptorFromIpcHandleExp)>(dlsym(libraryHandle, "zeMemGetFileDescriptorFromIpcHandleExp"));
    if(nullptr == zeMemGetFileDescriptorFromIpcHandleExp){
        log<Verbosity::error>("Missing symbol zeMemGetFileDescriptorFromIpcHandleExp in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleCreate = reinterpret_cast<decltype(zeModuleCreate)>(dlsym(libraryHandle, "zeModuleCreate"));
    if(nullptr == zeModuleCreate){
        log<Verbosity::error>("Missing symbol zeModuleCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleDestroy = reinterpret_cast<decltype(zeModuleDestroy)>(dlsym(libraryHandle, "zeModuleDestroy"));
    if(nullptr == zeModuleDestroy){
        log<Verbosity::error>("Missing symbol zeModuleDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleDynamicLink = reinterpret_cast<decltype(zeModuleDynamicLink)>(dlsym(libraryHandle, "zeModuleDynamicLink"));
    if(nullptr == zeModuleDynamicLink){
        log<Verbosity::error>("Missing symbol zeModuleDynamicLink in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleBuildLogDestroy = reinterpret_cast<decltype(zeModuleBuildLogDestroy)>(dlsym(libraryHandle, "zeModuleBuildLogDestroy"));
    if(nullptr == zeModuleBuildLogDestroy){
        log<Verbosity::error>("Missing symbol zeModuleBuildLogDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleBuildLogGetString = reinterpret_cast<decltype(zeModuleBuildLogGetString)>(dlsym(libraryHandle, "zeModuleBuildLogGetString"));
    if(nullptr == zeModuleBuildLogGetString){
        log<Verbosity::error>("Missing symbol zeModuleBuildLogGetString in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleGetNativeBinary = reinterpret_cast<decltype(zeModuleGetNativeBinary)>(dlsym(libraryHandle, "zeModuleGetNativeBinary"));
    if(nullptr == zeModuleGetNativeBinary){
        log<Verbosity::error>("Missing symbol zeModuleGetNativeBinary in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleGetGlobalPointer = reinterpret_cast<decltype(zeModuleGetGlobalPointer)>(dlsym(libraryHandle, "zeModuleGetGlobalPointer"));
    if(nullptr == zeModuleGetGlobalPointer){
        log<Verbosity::error>("Missing symbol zeModuleGetGlobalPointer in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleGetKernelNames = reinterpret_cast<decltype(zeModuleGetKernelNames)>(dlsym(libraryHandle, "zeModuleGetKernelNames"));
    if(nullptr == zeModuleGetKernelNames){
        log<Verbosity::error>("Missing symbol zeModuleGetKernelNames in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleGetProperties = reinterpret_cast<decltype(zeModuleGetProperties)>(dlsym(libraryHandle, "zeModuleGetProperties"));
    if(nullptr == zeModuleGetProperties){
        log<Verbosity::error>("Missing symbol zeModuleGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelCreate = reinterpret_cast<decltype(zeKernelCreate)>(dlsym(libraryHandle, "zeKernelCreate"));
    if(nullptr == zeKernelCreate){
        log<Verbosity::error>("Missing symbol zeKernelCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelDestroy = reinterpret_cast<decltype(zeKernelDestroy)>(dlsym(libraryHandle, "zeKernelDestroy"));
    if(nullptr == zeKernelDestroy){
        log<Verbosity::error>("Missing symbol zeKernelDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeModuleGetFunctionPointer = reinterpret_cast<decltype(zeModuleGetFunctionPointer)>(dlsym(libraryHandle, "zeModuleGetFunctionPointer"));
    if(nullptr == zeModuleGetFunctionPointer){
        log<Verbosity::error>("Missing symbol zeModuleGetFunctionPointer in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSetGroupSize = reinterpret_cast<decltype(zeKernelSetGroupSize)>(dlsym(libraryHandle, "zeKernelSetGroupSize"));
    if(nullptr == zeKernelSetGroupSize){
        log<Verbosity::error>("Missing symbol zeKernelSetGroupSize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSuggestGroupSize = reinterpret_cast<decltype(zeKernelSuggestGroupSize)>(dlsym(libraryHandle, "zeKernelSuggestGroupSize"));
    if(nullptr == zeKernelSuggestGroupSize){
        log<Verbosity::error>("Missing symbol zeKernelSuggestGroupSize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSuggestMaxCooperativeGroupCount = reinterpret_cast<decltype(zeKernelSuggestMaxCooperativeGroupCount)>(dlsym(libraryHandle, "zeKernelSuggestMaxCooperativeGroupCount"));
    if(nullptr == zeKernelSuggestMaxCooperativeGroupCount){
        log<Verbosity::error>("Missing symbol zeKernelSuggestMaxCooperativeGroupCount in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSetArgumentValue = reinterpret_cast<decltype(zeKernelSetArgumentValue)>(dlsym(libraryHandle, "zeKernelSetArgumentValue"));
    if(nullptr == zeKernelSetArgumentValue){
        log<Verbosity::error>("Missing symbol zeKernelSetArgumentValue in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSetIndirectAccess = reinterpret_cast<decltype(zeKernelSetIndirectAccess)>(dlsym(libraryHandle, "zeKernelSetIndirectAccess"));
    if(nullptr == zeKernelSetIndirectAccess){
        log<Verbosity::error>("Missing symbol zeKernelSetIndirectAccess in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelGetIndirectAccess = reinterpret_cast<decltype(zeKernelGetIndirectAccess)>(dlsym(libraryHandle, "zeKernelGetIndirectAccess"));
    if(nullptr == zeKernelGetIndirectAccess){
        log<Verbosity::error>("Missing symbol zeKernelGetIndirectAccess in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelGetSourceAttributes = reinterpret_cast<decltype(zeKernelGetSourceAttributes)>(dlsym(libraryHandle, "zeKernelGetSourceAttributes"));
    if(nullptr == zeKernelGetSourceAttributes){
        log<Verbosity::error>("Missing symbol zeKernelGetSourceAttributes in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelSetCacheConfig = reinterpret_cast<decltype(zeKernelSetCacheConfig)>(dlsym(libraryHandle, "zeKernelSetCacheConfig"));
    if(nullptr == zeKernelSetCacheConfig){
        log<Verbosity::error>("Missing symbol zeKernelSetCacheConfig in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelGetProperties = reinterpret_cast<decltype(zeKernelGetProperties)>(dlsym(libraryHandle, "zeKernelGetProperties"));
    if(nullptr == zeKernelGetProperties){
        log<Verbosity::error>("Missing symbol zeKernelGetProperties in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeKernelGetName = reinterpret_cast<decltype(zeKernelGetName)>(dlsym(libraryHandle, "zeKernelGetName"));
    if(nullptr == zeKernelGetName){
        log<Verbosity::error>("Missing symbol zeKernelGetName in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendLaunchKernel = reinterpret_cast<decltype(zeCommandListAppendLaunchKernel)>(dlsym(libraryHandle, "zeCommandListAppendLaunchKernel"));
    if(nullptr == zeCommandListAppendLaunchKernel){
        log<Verbosity::error>("Missing symbol zeCommandListAppendLaunchKernel in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendLaunchCooperativeKernel = reinterpret_cast<decltype(zeCommandListAppendLaunchCooperativeKernel)>(dlsym(libraryHandle, "zeCommandListAppendLaunchCooperativeKernel"));
    if(nullptr == zeCommandListAppendLaunchCooperativeKernel){
        log<Verbosity::error>("Missing symbol zeCommandListAppendLaunchCooperativeKernel in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendLaunchKernelIndirect = reinterpret_cast<decltype(zeCommandListAppendLaunchKernelIndirect)>(dlsym(libraryHandle, "zeCommandListAppendLaunchKernelIndirect"));
    if(nullptr == zeCommandListAppendLaunchKernelIndirect){
        log<Verbosity::error>("Missing symbol zeCommandListAppendLaunchKernelIndirect in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListAppendLaunchMultipleKernelsIndirect = reinterpret_cast<decltype(zeCommandListAppendLaunchMultipleKernelsIndirect)>(dlsym(libraryHandle, "zeCommandListAppendLaunchMultipleKernelsIndirect"));
    if(nullptr == zeCommandListAppendLaunchMultipleKernelsIndirect){
        log<Verbosity::error>("Missing symbol zeCommandListAppendLaunchMultipleKernelsIndirect in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeCommandListHostSynchronize = reinterpret_cast<decltype(zeCommandListHostSynchronize)>(dlsym(libraryHandle, "zeCommandListHostSynchronize"));
    if(nullptr == zeCommandListHostSynchronize){
        log<Verbosity::error>("Missing symbol zeCommandListHostSynchronize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeDevicePciGetPropertiesExt = reinterpret_cast<decltype(zeDevicePciGetPropertiesExt)>(dlsym(libraryHandle, "zeDevicePciGetPropertiesExt"));
    if(nullptr == zeDevicePciGetPropertiesExt){
        log<Verbosity::error>("Missing symbol zeDevicePciGetPropertiesExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextMakeMemoryResident = reinterpret_cast<decltype(zeContextMakeMemoryResident)>(dlsym(libraryHandle, "zeContextMakeMemoryResident"));
    if(nullptr == zeContextMakeMemoryResident){
        log<Verbosity::error>("Missing symbol zeContextMakeMemoryResident in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeContextEvictMemory = reinterpret_cast<decltype(zeContextEvictMemory)>(dlsym(libraryHandle, "zeContextEvictMemory"));
    if(nullptr == zeContextEvictMemory){
        log<Verbosity::error>("Missing symbol zeContextEvictMemory in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemReserve = reinterpret_cast<decltype(zeVirtualMemReserve)>(dlsym(libraryHandle, "zeVirtualMemReserve"));
    if(nullptr == zeVirtualMemReserve){
        log<Verbosity::error>("Missing symbol zeVirtualMemReserve in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemFree = reinterpret_cast<decltype(zeVirtualMemFree)>(dlsym(libraryHandle, "zeVirtualMemFree"));
    if(nullptr == zeVirtualMemFree){
        log<Verbosity::error>("Missing symbol zeVirtualMemFree in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemQueryPageSize = reinterpret_cast<decltype(zeVirtualMemQueryPageSize)>(dlsym(libraryHandle, "zeVirtualMemQueryPageSize"));
    if(nullptr == zeVirtualMemQueryPageSize){
        log<Verbosity::error>("Missing symbol zeVirtualMemQueryPageSize in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zePhysicalMemCreate = reinterpret_cast<decltype(zePhysicalMemCreate)>(dlsym(libraryHandle, "zePhysicalMemCreate"));
    if(nullptr == zePhysicalMemCreate){
        log<Verbosity::error>("Missing symbol zePhysicalMemCreate in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zePhysicalMemDestroy = reinterpret_cast<decltype(zePhysicalMemDestroy)>(dlsym(libraryHandle, "zePhysicalMemDestroy"));
    if(nullptr == zePhysicalMemDestroy){
        log<Verbosity::error>("Missing symbol zePhysicalMemDestroy in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemMap = reinterpret_cast<decltype(zeVirtualMemMap)>(dlsym(libraryHandle, "zeVirtualMemMap"));
    if(nullptr == zeVirtualMemMap){
        log<Verbosity::error>("Missing symbol zeVirtualMemMap in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemUnmap = reinterpret_cast<decltype(zeVirtualMemUnmap)>(dlsym(libraryHandle, "zeVirtualMemUnmap"));
    if(nullptr == zeVirtualMemUnmap){
        log<Verbosity::error>("Missing symbol zeVirtualMemUnmap in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemSetAccessAttribute = reinterpret_cast<decltype(zeVirtualMemSetAccessAttribute)>(dlsym(libraryHandle, "zeVirtualMemSetAccessAttribute"));
    if(nullptr == zeVirtualMemSetAccessAttribute){
        log<Verbosity::error>("Missing symbol zeVirtualMemSetAccessAttribute in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    zeVirtualMemGetAccessAttribute = reinterpret_cast<decltype(zeVirtualMemGetAccessAttribute)>(dlsym(libraryHandle, "zeVirtualMemGetAccessAttribute"));
    if(nullptr == zeVirtualMemGetAccessAttribute){
        log<Verbosity::error>("Missing symbol zeVirtualMemGetAccessAttribute in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    return true;
}

void unloadLevelZeroLibrary() {
    zetMetricGroupGet = nullptr;
    zetMetricGroupGetProperties = nullptr;
    zetMetricGroupGetGlobalTimestampsExp = nullptr;
    zetMetricGroupGetExportDataExp = nullptr;
    zetMetricGroupCalculateMetricValues = nullptr;
    zetMetricGroupCalculateMultipleMetricValuesExp = nullptr;
    zetMetricGet = nullptr;
    zetMetricGetProperties = nullptr;
    zetContextActivateMetricGroups = nullptr;
    zetMetricStreamerOpen = nullptr;
    zetMetricStreamerReadData = nullptr;
    zetMetricStreamerClose = nullptr;
    zetMetricQueryPoolCreate = nullptr;
    zetMetricQueryPoolDestroy = nullptr;
    zetMetricQueryCreate = nullptr;
    zetMetricQueryDestroy = nullptr;
    zetMetricQueryReset = nullptr;
    zetMetricQueryGetData = nullptr;
    zetCommandListAppendMetricQueryBegin = nullptr;
    zetCommandListAppendMetricQueryEnd = nullptr;
    zetCommandListAppendMetricMemoryBarrier = nullptr;
    zetCommandListAppendMetricStreamerMarker = nullptr;
    zetTracerExpCreate = nullptr;
    zetTracerExpDestroy = nullptr;
    zetTracerExpSetPrologues = nullptr;
    zetTracerExpSetEpilogues = nullptr;
    zetTracerExpSetEnabled = nullptr;
    zetDeviceGetDebugProperties = nullptr;
    zetDebugAttach = nullptr;
    zetDebugDetach = nullptr;
    zetKernelGetProfileInfo = nullptr;
    zesDeviceReset = nullptr;
    zesDeviceResetExt = nullptr;
    zesDeviceEnumPowerDomains = nullptr;
    zesDeviceGetCardPowerDomain = nullptr;
    zesPowerGetProperties = nullptr;
    zesPowerGetEnergyCounter = nullptr;
    zesPowerGetLimits = nullptr;
    zesPowerSetLimits = nullptr;
    zesPowerGetLimitsExt = nullptr;
    zesPowerSetLimitsExt = nullptr;
    zesPowerGetEnergyThreshold = nullptr;
    zesPowerSetEnergyThreshold = nullptr;
    zesDeviceEventRegister = nullptr;
    zesDriverEventListen = nullptr;
    zesDriverEventListenEx = nullptr;
    zesDeviceEnumTemperatureSensors = nullptr;
    zesTemperatureGetProperties = nullptr;
    zesTemperatureGetConfig = nullptr;
    zesTemperatureSetConfig = nullptr;
    zesTemperatureGetState = nullptr;
    zesDeviceEnumRasErrorSets = nullptr;
    zesRasGetProperties = nullptr;
    zesRasGetConfig = nullptr;
    zesRasSetConfig = nullptr;
    zesRasGetState = nullptr;
    zesDeviceEnumFrequencyDomains = nullptr;
    zesFrequencyGetProperties = nullptr;
    zesFrequencyGetAvailableClocks = nullptr;
    zesFrequencyGetRange = nullptr;
    zesFrequencySetRange = nullptr;
    zesFrequencyGetState = nullptr;
    zesFrequencyGetThrottleTime = nullptr;
    zesFrequencyOcGetCapabilities = nullptr;
    zesFrequencyOcGetVoltageTarget = nullptr;
    zesFrequencyOcSetVoltageTarget = nullptr;
    zesFrequencyOcSetMode = nullptr;
    zesFrequencyOcGetMode = nullptr;
    zesFrequencyOcGetIccMax = nullptr;
    zesFrequencyOcSetIccMax = nullptr;
    zesFrequencyOcGetTjMax = nullptr;
    zesFrequencyOcSetTjMax = nullptr;
    zesDeviceEnumEngineGroups = nullptr;
    zesDeviceEnumSchedulers = nullptr;
    zesSchedulerGetProperties = nullptr;
    zesSchedulerGetCurrentMode = nullptr;
    zesSchedulerGetTimeoutModeProperties = nullptr;
    zesSchedulerGetTimesliceModeProperties = nullptr;
    zesSchedulerSetTimeoutMode = nullptr;
    zesSchedulerSetTimesliceMode = nullptr;
    zesSchedulerSetExclusiveMode = nullptr;
    zesSchedulerSetComputeUnitDebugMode = nullptr;
    zesEngineGetProperties = nullptr;
    zesEngineGetActivity = nullptr;
    zesDeviceGetState = nullptr;
    zesDeviceProcessesGetState = nullptr;
    zesDevicePciGetProperties = nullptr;
    zesDevicePciGetState = nullptr;
    zesDevicePciGetBars = nullptr;
    zesDevicePciGetStats = nullptr;
    zesDeviceGetProperties = nullptr;
    zesDeviceEnumMemoryModules = nullptr;
    zesMemoryGetProperties = nullptr;
    zesMemoryGetState = nullptr;
    zesMemoryGetBandwidth = nullptr;
    zesDeviceEnumPerformanceFactorDomains = nullptr;
    zesPerformanceFactorGetProperties = nullptr;
    zesPerformanceFactorGetConfig = nullptr;
    zesPerformanceFactorSetConfig = nullptr;
    zesDeviceEnumStandbyDomains = nullptr;
    zesStandbyGetProperties = nullptr;
    zesStandbyGetMode = nullptr;
    zesStandbySetMode = nullptr;
    zeInit = nullptr;
    zeCommandListAppendMemoryRangesBarrier = nullptr;
    zeContextSystemBarrier = nullptr;
    zeCommandListCreate = nullptr;
    zeCommandListCreateImmediate = nullptr;
    zeCommandListDestroy = nullptr;
    zeCommandListClose = nullptr;
    zeCommandListReset = nullptr;
    zeCommandListAppendWriteGlobalTimestamp = nullptr;
    zeCommandQueueCreate = nullptr;
    zeCommandQueueDestroy = nullptr;
    zeCommandQueueExecuteCommandLists = nullptr;
    zeCommandQueueSynchronize = nullptr;
    zeContextCreate = nullptr;
    zeContextCreateEx = nullptr;
    zeContextDestroy = nullptr;
    zeContextGetStatus = nullptr;
    zeCommandListAppendMemoryCopy = nullptr;
    zeCommandListAppendMemoryFill = nullptr;
    zeCommandListAppendMemoryCopyRegion = nullptr;
    zeCommandListAppendMemoryCopyFromContext = nullptr;
    zeCommandListAppendMemoryPrefetch = nullptr;
    zeCommandListAppendMemAdvise = nullptr;
    zeDeviceGet = nullptr;
    zeDeviceGetSubDevices = nullptr;
    zeDeviceGetProperties = nullptr;
    zeDeviceGetComputeProperties = nullptr;
    zeDeviceGetModuleProperties = nullptr;
    zeDeviceGetCommandQueueGroupProperties = nullptr;
    zeDeviceGetMemoryProperties = nullptr;
    zeDeviceGetMemoryAccessProperties = nullptr;
    zeDeviceGetCacheProperties = nullptr;
    zeDeviceGetImageProperties = nullptr;
    zeDeviceGetExternalMemoryProperties = nullptr;
    zeDeviceGetP2PProperties = nullptr;
    zeDeviceCanAccessPeer = nullptr;
    zeDeviceGetStatus = nullptr;
    zeDeviceGetGlobalTimestamps = nullptr;
    zeDeviceReserveCacheExt = nullptr;
    zeDeviceSetCacheAdviceExt = nullptr;
    zeDriverGet = nullptr;
    zeDriverGetApiVersion = nullptr;
    zeDriverGetProperties = nullptr;
    zeDriverGetIpcProperties = nullptr;
    zeDriverGetExtensionProperties = nullptr;
    zeDriverGetExtensionFunctionAddress = nullptr;
    zeDriverGetLastErrorDescription = nullptr;
    zeEventPoolCreate = nullptr;
    zeEventPoolDestroy = nullptr;
    zeEventCreate = nullptr;
    zeEventDestroy = nullptr;
    zeEventPoolGetIpcHandle = nullptr;
    zeEventPoolOpenIpcHandle = nullptr;
    zeEventPoolCloseIpcHandle = nullptr;
    zeEventPoolPutIpcHandle = nullptr;
    zeCommandListAppendBarrier = nullptr;
    zeCommandListAppendSignalEvent = nullptr;
    zeCommandListAppendWaitOnEvents = nullptr;
    zeEventHostSignal = nullptr;
    zeEventHostSynchronize = nullptr;
    zeEventQueryStatus = nullptr;
    zeCommandListAppendEventReset = nullptr;
    zeEventHostReset = nullptr;
    zeEventQueryKernelTimestamp = nullptr;
    zeCommandListAppendQueryKernelTimestamps = nullptr;
    zeEventQueryTimestampsExp = nullptr;
    zeEventQueryKernelTimestampsExt = nullptr;
    zeFabricVertexGetExp = nullptr;
    zeFabricVertexGetSubVerticesExp = nullptr;
    zeFabricVertexGetPropertiesExp = nullptr;
    zeFabricVertexGetDeviceExp = nullptr;
    zeDeviceGetFabricVertexExp = nullptr;
    zeFabricEdgeGetExp = nullptr;
    zeFabricEdgeGetVerticesExp = nullptr;
    zeFabricEdgeGetPropertiesExp = nullptr;
    zeFenceCreate = nullptr;
    zeFenceDestroy = nullptr;
    zeFenceHostSynchronize = nullptr;
    zeFenceQueryStatus = nullptr;
    zeFenceReset = nullptr;
    zeKernelSetGlobalOffsetExp = nullptr;
    zeImageGetProperties = nullptr;
    zeImageCreate = nullptr;
    zeImageDestroy = nullptr;
    zeKernelSchedulingHintExp = nullptr;
    zeModuleInspectLinkageExt = nullptr;
    zeMemAllocShared = nullptr;
    zeMemAllocDevice = nullptr;
    zeMemAllocHost = nullptr;
    zeMemFree = nullptr;
    zeMemGetAllocProperties = nullptr;
    zeMemGetAddressRange = nullptr;
    zeMemGetIpcHandle = nullptr;
    zeMemOpenIpcHandle = nullptr;
    zeMemCloseIpcHandle = nullptr;
    zeMemPutIpcHandle = nullptr;
    zeMemFreeExt = nullptr;
    zeMemGetIpcHandleFromFileDescriptorExp = nullptr;
    zeMemGetFileDescriptorFromIpcHandleExp = nullptr;
    zeModuleCreate = nullptr;
    zeModuleDestroy = nullptr;
    zeModuleDynamicLink = nullptr;
    zeModuleBuildLogDestroy = nullptr;
    zeModuleBuildLogGetString = nullptr;
    zeModuleGetNativeBinary = nullptr;
    zeModuleGetGlobalPointer = nullptr;
    zeModuleGetKernelNames = nullptr;
    zeModuleGetProperties = nullptr;
    zeKernelCreate = nullptr;
    zeKernelDestroy = nullptr;
    zeModuleGetFunctionPointer = nullptr;
    zeKernelSetGroupSize = nullptr;
    zeKernelSuggestGroupSize = nullptr;
    zeKernelSuggestMaxCooperativeGroupCount = nullptr;
    zeKernelSetArgumentValue = nullptr;
    zeKernelSetIndirectAccess = nullptr;
    zeKernelGetIndirectAccess = nullptr;
    zeKernelGetSourceAttributes = nullptr;
    zeKernelSetCacheConfig = nullptr;
    zeKernelGetProperties = nullptr;
    zeKernelGetName = nullptr;
    zeCommandListAppendLaunchKernel = nullptr;
    zeCommandListAppendLaunchCooperativeKernel = nullptr;
    zeCommandListAppendLaunchKernelIndirect = nullptr;
    zeCommandListAppendLaunchMultipleKernelsIndirect = nullptr;
    zeCommandListHostSynchronize = nullptr;
    zeDevicePciGetPropertiesExt = nullptr;
    zeContextMakeMemoryResident = nullptr;
    zeContextEvictMemory = nullptr;
    zeVirtualMemReserve = nullptr;
    zeVirtualMemFree = nullptr;
    zeVirtualMemQueryPageSize = nullptr;
    zePhysicalMemCreate = nullptr;
    zePhysicalMemDestroy = nullptr;
    zeVirtualMemMap = nullptr;
    zeVirtualMemUnmap = nullptr;
    zeVirtualMemSetAccessAttribute = nullptr;
    zeVirtualMemGetAccessAttribute = nullptr;
    if(libraryHandle){
        dlclose(libraryHandle);
    }
    libraryHandle = nullptr;
}

bool isLevelZeroLibraryLoaded() {
    return nullptr != libraryHandle;
}

} // namespace Standard

namespace Extensions {
namespace LazyLoad {
ze_result_t zexMemGetIpcHandlesLoad(ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles){
    using ExtFuncT = decltype(zexMemGetIpcHandlesLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::LevelZero::getExtensionFuncAddress("zexMemGetIpcHandles"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : zexMemGetIpcHandles");
        assert(false);
        return {};
    }
    Cal::Service::Apis::LevelZero::Extensions::zexMemGetIpcHandles = extAddr;
    return extAddr(hContext, ptr, numIpcHandles, pIpcHandles);
}
ze_result_t zexMemOpenIpcHandlesLoad(ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr){
    using ExtFuncT = decltype(zexMemOpenIpcHandlesLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::LevelZero::getExtensionFuncAddress("zexMemOpenIpcHandles"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : zexMemOpenIpcHandles");
        assert(false);
        return {};
    }
    Cal::Service::Apis::LevelZero::Extensions::zexMemOpenIpcHandles = extAddr;
    return extAddr(hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
}
ze_result_t zexDriverImportExternalPointerLoad(ze_driver_handle_t hDriver, void* ptr, size_t size){
    using ExtFuncT = decltype(zexDriverImportExternalPointerLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::LevelZero::getExtensionFuncAddress("zexDriverImportExternalPointer"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : zexDriverImportExternalPointer");
        assert(false);
        return {};
    }
    Cal::Service::Apis::LevelZero::Extensions::zexDriverImportExternalPointer = extAddr;
    return extAddr(hDriver, ptr, size);
}
ze_result_t zexDriverReleaseImportedPointerLoad(ze_driver_handle_t hDriver, void* ptr){
    using ExtFuncT = decltype(zexDriverReleaseImportedPointerLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::LevelZero::getExtensionFuncAddress("zexDriverReleaseImportedPointer"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : zexDriverReleaseImportedPointer");
        assert(false);
        return {};
    }
    Cal::Service::Apis::LevelZero::Extensions::zexDriverReleaseImportedPointer = extAddr;
    return extAddr(hDriver, ptr);
}
ze_result_t zexDriverGetHostPointerBaseAddressLoad(ze_driver_handle_t hDriver, void* ptr, void** baseAddress){
    using ExtFuncT = decltype(zexDriverGetHostPointerBaseAddressLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::LevelZero::getExtensionFuncAddress("zexDriverGetHostPointerBaseAddress"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : zexDriverGetHostPointerBaseAddress");
        assert(false);
        return {};
    }
    Cal::Service::Apis::LevelZero::Extensions::zexDriverGetHostPointerBaseAddress = extAddr;
    return extAddr(hDriver, ptr, baseAddress);
}
} // namespace Lazy Load
ze_result_t (*zexMemGetIpcHandles)(ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) = Cal::Service::Apis::LevelZero::Extensions::LazyLoad::zexMemGetIpcHandlesLoad;
ze_result_t (*zexMemOpenIpcHandles)(ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr) = Cal::Service::Apis::LevelZero::Extensions::LazyLoad::zexMemOpenIpcHandlesLoad;
ze_result_t (*zexDriverImportExternalPointer)(ze_driver_handle_t hDriver, void* ptr, size_t size) = Cal::Service::Apis::LevelZero::Extensions::LazyLoad::zexDriverImportExternalPointerLoad;
ze_result_t (*zexDriverReleaseImportedPointer)(ze_driver_handle_t hDriver, void* ptr) = Cal::Service::Apis::LevelZero::Extensions::LazyLoad::zexDriverReleaseImportedPointerLoad;
ze_result_t (*zexDriverGetHostPointerBaseAddress)(ze_driver_handle_t hDriver, void* ptr, void** baseAddress) = Cal::Service::Apis::LevelZero::Extensions::LazyLoad::zexDriverGetHostPointerBaseAddressLoad;
} // namespace Extensions

} // namespace LevelZero
} // namespace Apis
} // namespace Service
} // namespace Cal
// #### Generated code -- end ####
