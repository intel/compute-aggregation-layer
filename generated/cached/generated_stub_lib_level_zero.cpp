/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "level_zero/ze_api.h"
#include "level_zero/zes_api.h"
#include "level_zero/zet_ddi.h"

ze_result_t zetMetricGroupGet(zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups){
   return {};
}

ze_result_t zetMetricGroupGetProperties(zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties){
   return {};
}

ze_result_t zetMetricGroupGetGlobalTimestampsExp(zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp){
   return {};
}

ze_result_t zetMetricGroupGetExportDataExp(zet_metric_group_handle_t hMetricGroup, const uint8_t * pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t* pExportData){
   return {};
}

ze_result_t zetMetricGroupCalculateMetricValues(zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues){
   return {};
}

ze_result_t zetMetricGroupCalculateMultipleMetricValuesExp(zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues){
   return {};
}

ze_result_t zetMetricGet(zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics){
   return {};
}

ze_result_t zetMetricGetProperties(zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties){
   return {};
}

ze_result_t zetContextActivateMetricGroups(zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups){
   return {};
}

ze_result_t zetMetricStreamerOpen(zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer){
   return {};
}

ze_result_t zetMetricStreamerReadData(zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData){
   return {};
}

ze_result_t zetMetricStreamerClose(zet_metric_streamer_handle_t hMetricStreamer){
   return {};
}

ze_result_t zetMetricQueryPoolCreate(zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t * desc, zet_metric_query_pool_handle_t* phMetricQueryPool){
   return {};
}

ze_result_t zetMetricQueryPoolDestroy(zet_metric_query_pool_handle_t hMetricQueryPool){
   return {};
}

ze_result_t zetMetricQueryCreate(zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery){
   return {};
}

ze_result_t zetMetricQueryDestroy(zet_metric_query_handle_t hMetricQuery){
   return {};
}

ze_result_t zetMetricQueryReset(zet_metric_query_handle_t hMetricQuery){
   return {};
}

ze_result_t zetMetricQueryGetData(zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData){
   return {};
}

ze_result_t zetCommandListAppendMetricQueryBegin(zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery){
   return {};
}

ze_result_t zetCommandListAppendMetricQueryEnd(zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zetCommandListAppendMetricMemoryBarrier(zet_command_list_handle_t hCommandList){
   return {};
}

ze_result_t zetCommandListAppendMetricStreamerMarker(zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value){
   return {};
}

ze_result_t zetTracerExpCreate(zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer){
   return {};
}

ze_result_t zetTracerExpDestroy(zet_tracer_exp_handle_t hTracer){
   return {};
}

ze_result_t zetTracerExpSetPrologues(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs){
   return {};
}

ze_result_t zetTracerExpSetEpilogues(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs){
   return {};
}

ze_result_t zetTracerExpSetEnabled(zet_tracer_exp_handle_t hTracer, ze_bool_t enable){
   return {};
}

ze_result_t zetDeviceGetDebugProperties(ze_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties){
   return {};
}

ze_result_t zetDebugAttach(ze_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug){
   return {};
}

ze_result_t zetDebugDetach(zet_debug_session_handle_t hDebug){
   return {};
}

ze_result_t zetKernelGetProfileInfo(ze_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties){
   return {};
}

ze_result_t zesDeviceReset(zes_device_handle_t hDevice, ze_bool_t force){
   return {};
}

ze_result_t zesDeviceResetExt(zes_device_handle_t hDevice, zes_reset_properties_t* pProperties){
   return {};
}

ze_result_t zesDeviceEnumPowerDomains(zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower){
   return {};
}

ze_result_t zesDeviceGetCardPowerDomain(zes_device_handle_t hDevice, zes_pwr_handle_t* phPower){
   return {};
}

ze_result_t zesPowerGetProperties(zes_pwr_handle_t hPower, zes_power_properties_t* pProperties){
   return {};
}

ze_result_t zesPowerGetEnergyCounter(zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy){
   return {};
}

ze_result_t zesPowerGetLimits(zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak){
   return {};
}

ze_result_t zesPowerSetLimits(zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak){
   return {};
}

ze_result_t zesPowerGetLimitsExt(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained){
   return {};
}

ze_result_t zesPowerSetLimitsExt(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained){
   return {};
}

ze_result_t zesPowerGetEnergyThreshold(zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold){
   return {};
}

ze_result_t zesPowerSetEnergyThreshold(zes_pwr_handle_t hPower, double pThreshold){
   return {};
}

ze_result_t zesDeviceEventRegister(zes_device_handle_t hDevice, zes_event_type_flags_t events){
   return {};
}

ze_result_t zesDriverEventListen(ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents){
   return {};
}

ze_result_t zesDriverEventListenEx(ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents){
   return {};
}

ze_result_t zesDeviceEnumTemperatureSensors(zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature){
   return {};
}

ze_result_t zesTemperatureGetProperties(zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties){
   return {};
}

ze_result_t zesTemperatureGetConfig(zes_temp_handle_t hTemperature, zes_temp_config_t * pConfig){
   return {};
}

ze_result_t zesTemperatureSetConfig(zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig){
   return {};
}

ze_result_t zesTemperatureGetState(zes_temp_handle_t hTemperature, double* pTemperature){
   return {};
}

ze_result_t zesDeviceEnumRasErrorSets(zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas){
   return {};
}

ze_result_t zesRasGetProperties(zes_ras_handle_t hRas, zes_ras_properties_t* pProperties){
   return {};
}

ze_result_t zesRasGetConfig(zes_ras_handle_t hRas, zes_ras_config_t * pConfig){
   return {};
}

ze_result_t zesRasSetConfig(zes_ras_handle_t hRas, const zes_ras_config_t* pConfig){
   return {};
}

ze_result_t zesRasGetState(zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState){
   return {};
}

ze_result_t zesDeviceEnumFrequencyDomains(zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency){
   return {};
}

ze_result_t zesFrequencyGetProperties(zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties){
   return {};
}

ze_result_t zesFrequencyGetAvailableClocks(zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency){
   return {};
}

ze_result_t zesFrequencyGetRange(zes_freq_handle_t hFrequency, zes_freq_range_t* pConfig){
   return {};
}

ze_result_t zesFrequencySetRange(zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits){
   return {};
}

ze_result_t zesFrequencyGetState(zes_freq_handle_t hFrequency, zes_freq_state_t* pState){
   return {};
}

ze_result_t zesFrequencyGetThrottleTime(zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime){
   return {};
}

ze_result_t zesFrequencyOcGetCapabilities(zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities){
   return {};
}

ze_result_t zesFrequencyOcGetVoltageTarget(zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset){
   return {};
}

ze_result_t zesFrequencyOcSetVoltageTarget(zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset){
   return {};
}

ze_result_t zesFrequencyOcSetMode(zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode){
   return {};
}

ze_result_t zesFrequencyOcGetMode(zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode){
   return {};
}

ze_result_t zesFrequencyOcGetIccMax(zes_freq_handle_t hFrequency, double* pOcIccMax){
   return {};
}

ze_result_t zesFrequencyOcSetIccMax(zes_freq_handle_t hFrequency, double ocIccMax){
   return {};
}

ze_result_t zesFrequencyOcGetTjMax(zes_freq_handle_t hFrequency, double* pOcTjMax){
   return {};
}

ze_result_t zesFrequencyOcSetTjMax(zes_freq_handle_t hFrequency, double ocTjMax){
   return {};
}

ze_result_t zesDeviceEnumEngineGroups(zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine){
   return {};
}

ze_result_t zesDeviceEnumSchedulers(zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler){
   return {};
}

ze_result_t zesSchedulerGetProperties(zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties){
   return {};
}

ze_result_t zesSchedulerGetCurrentMode(zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode){
   return {};
}

ze_result_t zesSchedulerGetTimeoutModeProperties(zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig){
   return {};
}

ze_result_t zesSchedulerGetTimesliceModeProperties(zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig){
   return {};
}

ze_result_t zesSchedulerSetTimeoutMode(zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload){
   return {};
}

ze_result_t zesSchedulerSetTimesliceMode(zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload){
   return {};
}

ze_result_t zesSchedulerSetExclusiveMode(zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload){
   return {};
}

ze_result_t zesSchedulerSetComputeUnitDebugMode(zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload){
   return {};
}

ze_result_t zesEngineGetProperties(zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties){
   return {};
}

ze_result_t zesEngineGetActivity(zes_engine_handle_t hEngine, zes_engine_stats_t* pStats){
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

ze_result_t zesMemoryGetProperties(zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties){
   return {};
}

ze_result_t zesMemoryGetState(zes_mem_handle_t hMemory, zes_mem_state_t* pState){
   return {};
}

ze_result_t zesMemoryGetBandwidth(zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth){
   return {};
}

ze_result_t zesDeviceEnumPerformanceFactorDomains(zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf){
   return {};
}

ze_result_t zesPerformanceFactorGetProperties(zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties){
   return {};
}

ze_result_t zesPerformanceFactorGetConfig(zes_perf_handle_t hPerf, double* pFactor){
   return {};
}

ze_result_t zesPerformanceFactorSetConfig(zes_perf_handle_t hPerf, double pFactor){
   return {};
}

ze_result_t zesDeviceEnumStandbyDomains(zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby){
   return {};
}

ze_result_t zesStandbyGetProperties(zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties){
   return {};
}

ze_result_t zesStandbyGetMode(zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode){
   return {};
}

ze_result_t zesStandbySetMode(zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode){
   return {};
}

ze_result_t zeInit(ze_init_flags_t flags){
   return {};
}

ze_result_t zeCommandListAppendMemoryRangesBarrier(ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeContextSystemBarrier(ze_context_handle_t hContext, ze_device_handle_t hDevice){
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

ze_result_t zeCommandListAppendMemoryCopyRegion(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendMemoryCopyFromContext(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
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

ze_result_t zeCommandListAppendQueryKernelTimestamps(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeEventQueryTimestampsExp(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps){
   return {};
}

ze_result_t zeEventQueryKernelTimestampsExt(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults){
   return {};
}

ze_result_t zeFabricVertexGetExp(ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices){
   return {};
}

ze_result_t zeFabricVertexGetSubVerticesExp(ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices){
   return {};
}

ze_result_t zeFabricVertexGetPropertiesExp(ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties){
   return {};
}

ze_result_t zeFabricVertexGetDeviceExp(ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* pDevice){
   return {};
}

ze_result_t zeDeviceGetFabricVertexExp(ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* pVertex){
   return {};
}

ze_result_t zeFabricEdgeGetExp(ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges){
   return {};
}

ze_result_t zeFabricEdgeGetVerticesExp(ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB){
   return {};
}

ze_result_t zeFabricEdgeGetPropertiesExp(ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties){
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

ze_result_t zeModuleInspectLinkageExt(ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog){
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

ze_result_t zeMemFreeExt(ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr){
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

ze_result_t zeCommandListAppendLaunchCooperativeKernel(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendLaunchKernelIndirect(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
   return {};
}

ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirect(ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents){
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
