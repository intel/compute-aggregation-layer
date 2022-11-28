/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####
#include <string>
#include <vector>

namespace Cal {
namespace Service {
namespace Apis {
namespace LevelZero {

inline std::vector<std::string> getListOfUnimplementedFunctionNames(){
    std::vector<std::string> ret;
    ret.push_back("CommandList.zeCommandListAppendMemoryRangesBarrier");
    ret.push_back("Context.zeContextSystemBarrier");
    ret.push_back("Device.zeDeviceReserveCacheExt");
    ret.push_back("Device.zeDeviceSetCacheAdviceExt");
    ret.push_back("CommandList.zeCommandListAppendWriteGlobalTimestamp");
    ret.push_back("CommandList.zeCommandListAppendMemoryCopyRegion");
    ret.push_back("CommandList.zeCommandListAppendMemoryCopyFromContext");
    ret.push_back("CommandList.zeCommandListAppendImageCopy");
    ret.push_back("CommandList.zeCommandListAppendImageCopyRegion");
    ret.push_back("CommandList.zeCommandListAppendImageCopyToMemory");
    ret.push_back("CommandList.zeCommandListAppendImageCopyFromMemory");
    ret.push_back("CommandList.zeCommandListAppendMemoryPrefetch");
    ret.push_back("CommandList.zeCommandListAppendMemAdvise");
    ret.push_back("CommandList.zeCommandListAppendQueryKernelTimestamps");
    ret.push_back("EventExp.zeEventQueryTimestampsExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetSubVerticesExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetPropertiesExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetDeviceExp");
    ret.push_back("DeviceExp.zeDeviceGetFabricVertexExp");
    ret.push_back("FabricEdgeExp.zeFabricEdgeGetExp");
    ret.push_back("FabricEdgeExp.zeFabricEdgeGetVerticesExp");
    ret.push_back("FabricEdgeExp.zeFabricEdgeGetPropertiesExp");
    ret.push_back("CommandList.zeCommandListAppendImageCopyToMemoryExt");
    ret.push_back("CommandList.zeCommandListAppendImageCopyFromMemoryExt");
    ret.push_back("ImageExp.zeImageGetMemoryPropertiesExp");
    ret.push_back("Image.zeImageGetAllocPropertiesExt");
    ret.push_back("ImageExp.zeImageViewCreateExp");
    ret.push_back("KernelExp.zeKernelSchedulingHintExp");
    ret.push_back("Module.zeModuleInspectLinkageExt");
    ret.push_back("Mem.zeMemFreeExt");
    ret.push_back("Kernel.zeKernelGetSourceAttributes");
    ret.push_back("CommandList.zeCommandListAppendLaunchCooperativeKernel");
    ret.push_back("CommandList.zeCommandListAppendLaunchMultipleKernelsIndirect");
    ret.push_back("Context.zeContextMakeMemoryResident");
    ret.push_back("Context.zeContextEvictMemory");
    ret.push_back("Context.zeContextMakeImageResident");
    ret.push_back("Context.zeContextEvictImage");
    ret.push_back("Sampler.zeSamplerCreate");
    ret.push_back("Sampler.zeSamplerDestroy");
    ret.push_back("VirtualMem.zeVirtualMemReserve");
    ret.push_back("VirtualMem.zeVirtualMemFree");
    ret.push_back("VirtualMem.zeVirtualMemQueryPageSize");
    ret.push_back("PhysicalMem.zePhysicalMemCreate");
    ret.push_back("PhysicalMem.zePhysicalMemDestroy");
    ret.push_back("VirtualMem.zeVirtualMemMap");
    ret.push_back("VirtualMem.zeVirtualMemUnmap");
    ret.push_back("VirtualMem.zeVirtualMemSetAccessAttribute");
    ret.push_back("VirtualMem.zeVirtualMemGetAccessAttribute");
    ret.push_back("Device.zesDeviceEnumRasErrorSets");
    ret.push_back("Ras.zesRasGetProperties");
    ret.push_back("Ras.zesRasGetConfig");
    ret.push_back("Ras.zesRasSetConfig");
    ret.push_back("Ras.zesRasGetState");
    ret.push_back("Device.zesDeviceGetProperties");
    ret.push_back("Device.zesDeviceGetState");
    ret.push_back("Device.zesDeviceReset");
    ret.push_back("Device.zesDeviceProcessesGetState");
    ret.push_back("Device.zesDevicePciGetProperties");
    ret.push_back("Device.zesDevicePciGetState");
    ret.push_back("Device.zesDevicePciGetBars");
    ret.push_back("Device.zesDevicePciGetStats");
    ret.push_back("Device.zesDeviceEnumFans");
    ret.push_back("Fan.zesFanGetProperties");
    ret.push_back("Fan.zesFanGetConfig");
    ret.push_back("Fan.zesFanSetDefaultMode");
    ret.push_back("Fan.zesFanSetFixedSpeedMode");
    ret.push_back("Fan.zesFanSetSpeedTableMode");
    ret.push_back("Fan.zesFanGetState");
    ret.push_back("Device.zesDeviceEnumFirmwares");
    ret.push_back("Firmware.zesFirmwareGetProperties");
    ret.push_back("Firmware.zesFirmwareFlash");
    ret.push_back("Power.zesPowerGetLimitsExt");
    ret.push_back("Power.zesPowerSetLimitsExt");
    ret.push_back("Device.zesDeviceEnumStandbyDomains");
    ret.push_back("Standby.zesStandbyGetProperties");
    ret.push_back("Standby.zesStandbyGetMode");
    ret.push_back("Standby.zesStandbySetMode");
    ret.push_back("Device.zesDeviceEnumTemperatureSensors");
    ret.push_back("Temperature.zesTemperatureGetProperties");
    ret.push_back("Temperature.zesTemperatureGetConfig");
    ret.push_back("Temperature.zesTemperatureSetConfig");
    ret.push_back("Temperature.zesTemperatureGetState");
    ret.push_back("Device.zesDeviceEccAvailable");
    ret.push_back("Device.zesDeviceEccConfigurable");
    ret.push_back("Device.zesDeviceGetEccState");
    ret.push_back("Device.zesDeviceSetEccState");
    ret.push_back("Device.zesDeviceEnumEngineGroups");
    ret.push_back("Engine.zesEngineGetProperties");
    ret.push_back("Engine.zesEngineGetActivity");
    ret.push_back("Device.zesDeviceEnumSchedulers");
    ret.push_back("Scheduler.zesSchedulerGetProperties");
    ret.push_back("Scheduler.zesSchedulerGetCurrentMode");
    ret.push_back("Scheduler.zesSchedulerGetTimeoutModeProperties");
    ret.push_back("Scheduler.zesSchedulerGetTimesliceModeProperties");
    ret.push_back("Scheduler.zesSchedulerSetTimeoutMode");
    ret.push_back("Scheduler.zesSchedulerSetTimesliceMode");
    ret.push_back("Scheduler.zesSchedulerSetExclusiveMode");
    ret.push_back("Scheduler.zesSchedulerSetComputeUnitDebugMode");
    ret.push_back("Device.zesDeviceEnumMemoryModules");
    ret.push_back("Memory.zesMemoryGetProperties");
    ret.push_back("Memory.zesMemoryGetState");
    ret.push_back("Memory.zesMemoryGetBandwidth");
    ret.push_back("Device.zesDeviceEnumPerformanceFactorDomains");
    ret.push_back("PerformanceFactor.zesPerformanceFactorGetProperties");
    ret.push_back("PerformanceFactor.zesPerformanceFactorGetConfig");
    ret.push_back("PerformanceFactor.zesPerformanceFactorSetConfig");
    ret.push_back("Device.zesDeviceEnumLeds");
    ret.push_back("Led.zesLedGetProperties");
    ret.push_back("Led.zesLedGetState");
    ret.push_back("Led.zesLedSetState");
    ret.push_back("Led.zesLedSetColor");
    ret.push_back("Device.zesDeviceEnumPowerDomains");
    ret.push_back("Device.zesDeviceGetCardPowerDomain");
    ret.push_back("Power.zesPowerGetProperties");
    ret.push_back("Power.zesPowerGetEnergyCounter");
    ret.push_back("Power.zesPowerGetLimits");
    ret.push_back("Power.zesPowerSetLimits");
    ret.push_back("Power.zesPowerGetEnergyThreshold");
    ret.push_back("Power.zesPowerSetEnergyThreshold");
    ret.push_back("Device.zesDeviceEnumFabricPorts");
    ret.push_back("FabricPort.zesFabricPortGetProperties");
    ret.push_back("FabricPort.zesFabricPortGetLinkType");
    ret.push_back("FabricPort.zesFabricPortGetConfig");
    ret.push_back("FabricPort.zesFabricPortSetConfig");
    ret.push_back("FabricPort.zesFabricPortGetState");
    ret.push_back("FabricPort.zesFabricPortGetThroughput");
    ret.push_back("Device.zesDeviceEventRegister");
    ret.push_back("Driver.zesDriverEventListen");
    ret.push_back("Driver.zesDriverEventListenEx");
    ret.push_back("Device.zesDeviceEnumDiagnosticTestSuites");
    ret.push_back("Diagnostics.zesDiagnosticsGetProperties");
    ret.push_back("Diagnostics.zesDiagnosticsGetTests");
    ret.push_back("Diagnostics.zesDiagnosticsRunTests");
    ret.push_back("Device.zesDeviceEnumPsus");
    ret.push_back("Psu.zesPsuGetProperties");
    ret.push_back("Psu.zesPsuGetState");
    ret.push_back("Device.zesDeviceEnumFrequencyDomains");
    ret.push_back("Frequency.zesFrequencyGetProperties");
    ret.push_back("Frequency.zesFrequencyGetAvailableClocks");
    ret.push_back("Frequency.zesFrequencyGetRange");
    ret.push_back("Frequency.zesFrequencySetRange");
    ret.push_back("Frequency.zesFrequencyGetState");
    ret.push_back("Frequency.zesFrequencyGetThrottleTime");
    ret.push_back("Frequency.zesFrequencyOcGetCapabilities");
    ret.push_back("Frequency.zesFrequencyOcGetVoltageTarget");
    ret.push_back("Frequency.zesFrequencyOcSetVoltageTarget");
    ret.push_back("Frequency.zesFrequencyOcSetMode");
    ret.push_back("Frequency.zesFrequencyOcGetMode");
    ret.push_back("Frequency.zesFrequencyOcGetIccMax");
    ret.push_back("Frequency.zesFrequencyOcSetIccMax");
    ret.push_back("Frequency.zesFrequencyOcGetTjMax");
    ret.push_back("Frequency.zesFrequencyOcSetTjMax");
    ret.push_back("Kernel.zetKernelGetProfileInfo");
    ret.push_back("MetricGroupExp.zetMetricGroupCalculateMultipleMetricValuesExp");
    ret.push_back("Device.zetDeviceGetDebugProperties");
    ret.push_back("Debug.zetDebugAttach");
    ret.push_back("Debug.zetDebugDetach");
    ret.push_back("Debug.zetDebugReadEvent");
    ret.push_back("Debug.zetDebugAcknowledgeEvent");
    ret.push_back("Debug.zetDebugInterrupt");
    ret.push_back("Debug.zetDebugResume");
    ret.push_back("Debug.zetDebugReadMemory");
    ret.push_back("Debug.zetDebugWriteMemory");
    ret.push_back("Debug.zetDebugGetRegisterSetProperties");
    ret.push_back("Debug.zetDebugReadRegisters");
    ret.push_back("Debug.zetDebugWriteRegisters");
    ret.push_back("Module.zetModuleGetDebugInfo");
    ret.push_back("MetricGroup.zetMetricGroupGet");
    ret.push_back("MetricGroup.zetMetricGroupGetProperties");
    ret.push_back("MetricGroup.zetMetricGroupCalculateMetricValues");
    ret.push_back("Metric.zetMetricGet");
    ret.push_back("Metric.zetMetricGetProperties");
    ret.push_back("Context.zetContextActivateMetricGroups");
    ret.push_back("MetricStreamer.zetMetricStreamerOpen");
    ret.push_back("CommandList.zetCommandListAppendMetricStreamerMarker");
    ret.push_back("MetricStreamer.zetMetricStreamerClose");
    ret.push_back("MetricStreamer.zetMetricStreamerReadData");
    ret.push_back("MetricQueryPool.zetMetricQueryPoolCreate");
    ret.push_back("MetricQueryPool.zetMetricQueryPoolDestroy");
    ret.push_back("MetricQuery.zetMetricQueryCreate");
    ret.push_back("MetricQuery.zetMetricQueryDestroy");
    ret.push_back("MetricQuery.zetMetricQueryReset");
    ret.push_back("CommandList.zetCommandListAppendMetricQueryBegin");
    ret.push_back("CommandList.zetCommandListAppendMetricQueryEnd");
    ret.push_back("CommandList.zetCommandListAppendMetricMemoryBarrier");
    ret.push_back("MetricQuery.zetMetricQueryGetData");
    ret.push_back("TracerExp.zetTracerExpCreate");
    ret.push_back("TracerExp.zetTracerExpDestroy");
    ret.push_back("TracerExp.zetTracerExpSetPrologues");
    ret.push_back("TracerExp.zetTracerExpSetEpilogues");
    ret.push_back("TracerExp.zetTracerExpSetEnabled");
    return ret;
}

} // namespae LevelZero
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
