/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"

#include <level_zero/layers/zel_tracing_api.h>
#include <level_zero/layers/zel_tracing_ddi.h>
#include <level_zero/ze_api.h>
#include <level_zero/ze_ddi.h>
#include <level_zero/zes_api.h>
#include <level_zero/zes_ddi.h>
#include <level_zero/zet_api.h>
#include <level_zero/zet_ddi.h>

ze_dditable_t l0Ddi = {};
zet_dditable_t l0ToolsDdi = {};
zes_dditable_t l0SysmanDdi = {};
zel_tracing_dditable_t l0TracingDdi = {};

ze_api_version_t supportedL0ApiVersion = ZE_API_VERSION_CURRENT;

template <typename DdiT>
ze_result_t validateTable(ze_api_version_t version, DdiT *ddi) {
    if (nullptr == ddi) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    if (ZE_MAJOR_VERSION(supportedL0ApiVersion) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(supportedL0ApiVersion) > ZE_MINOR_VERSION(version)) {
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
    }

    return ZE_RESULT_SUCCESS;
}

template <typename DdiT, typename TableT>
ze_result_t getAddressTable(ze_api_version_t version, DdiT *ddi, TableT &table) {
    const auto validationResult = validateTable(version, ddi);
    if (validationResult == ZE_RESULT_SUCCESS) {
        *ddi = table;
    }
    return validationResult;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetDriverProcAddrTable(ze_api_version_t version, ze_driver_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Driver);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetMemProcAddrTable(ze_api_version_t version, ze_mem_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Mem);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetContextProcAddrTable(ze_api_version_t version, ze_context_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Context);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetPhysicalMemProcAddrTable(ze_api_version_t version, ze_physical_mem_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.PhysicalMem);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetVirtualMemProcAddrTable(ze_api_version_t version, ze_virtual_mem_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.VirtualMem);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetGlobalProcAddrTable(ze_api_version_t version, ze_global_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Global);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetDeviceProcAddrTable(ze_api_version_t version, ze_device_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Device);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetCommandQueueProcAddrTable(ze_api_version_t version, ze_command_queue_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.CommandQueue);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetCommandListProcAddrTable(ze_api_version_t version, ze_command_list_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.CommandList);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetFenceProcAddrTable(ze_api_version_t version, ze_fence_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Fence);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetEventPoolProcAddrTable(ze_api_version_t version, ze_event_pool_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.EventPool);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetEventProcAddrTable(ze_api_version_t version, ze_event_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Event);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetEventExpProcAddrTable(ze_api_version_t version, ze_event_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.EventExp);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetImageProcAddrTable(ze_api_version_t version, ze_image_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Image);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetModuleProcAddrTable(ze_api_version_t version, ze_module_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Module);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetModuleBuildLogProcAddrTable(ze_api_version_t version, ze_module_build_log_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.ModuleBuildLog);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetKernelProcAddrTable(ze_api_version_t version, ze_kernel_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Kernel);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetSamplerProcAddrTable(ze_api_version_t version, ze_sampler_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.Sampler);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetKernelExpProcAddrTable(ze_api_version_t version, ze_kernel_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.KernelExp);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetImageExpProcAddrTable(ze_api_version_t version, ze_image_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.ImageExp);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetDeviceExpProcAddrTable(ze_api_version_t version, ze_device_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.DeviceExp);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetFabricEdgeExpProcAddrTable(ze_api_version_t version, ze_fabric_edge_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.FabricEdgeExp);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetFabricVertexExpProcAddrTable(ze_api_version_t version, ze_fabric_vertex_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0Ddi.FabricVertexExp);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetDeviceProcAddrTable(ze_api_version_t version, zet_device_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.Device);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetContextProcAddrTable(ze_api_version_t version, zet_context_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.Context);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetCommandListProcAddrTable(ze_api_version_t version, zet_command_list_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.CommandList);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetKernelProcAddrTable(ze_api_version_t version, zet_kernel_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.Kernel);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetModuleProcAddrTable(ze_api_version_t version, zet_module_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.Module);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetDebugProcAddrTable(ze_api_version_t version, zet_debug_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.Debug);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetMetricProcAddrTable(ze_api_version_t version, zet_metric_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.Metric);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetMetricGroupProcAddrTable(ze_api_version_t version, zet_metric_group_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.MetricGroup);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetMetricGroupExpProcAddrTable(ze_api_version_t version, zet_metric_group_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.MetricGroupExp);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetMetricQueryProcAddrTable(ze_api_version_t version, zet_metric_query_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.MetricQuery);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetMetricQueryPoolProcAddrTable(ze_api_version_t version, zet_metric_query_pool_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.MetricQueryPool);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetMetricStreamerProcAddrTable(ze_api_version_t version, zet_metric_streamer_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.MetricStreamer);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zetGetTracerExpProcAddrTable(ze_api_version_t version, zet_tracer_exp_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0ToolsDdi.TracerExp);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetDeviceProcAddrTable(ze_api_version_t version, zes_device_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Device);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetDriverProcAddrTable(ze_api_version_t version, zes_driver_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Driver);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetDiagnosticsProcAddrTable(ze_api_version_t version, zes_diagnostics_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Diagnostics);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetEngineProcAddrTable(ze_api_version_t version, zes_engine_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Engine);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetFabricPortProcAddrTable(ze_api_version_t version, zes_fabric_port_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.FabricPort);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetFanProcAddrTable(ze_api_version_t version, zes_fan_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Fan);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetFirmwareProcAddrTable(ze_api_version_t version, zes_firmware_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Firmware);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetFrequencyProcAddrTable(ze_api_version_t version, zes_frequency_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Frequency);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetLedProcAddrTable(ze_api_version_t version, zes_led_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Led);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetMemoryProcAddrTable(ze_api_version_t version, zes_memory_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Memory);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetPerformanceFactorProcAddrTable(ze_api_version_t version, zes_performance_factor_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.PerformanceFactor);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetPowerProcAddrTable(ze_api_version_t version, zes_power_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Power);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetPsuProcAddrTable(ze_api_version_t version, zes_psu_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Psu);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetRasProcAddrTable(ze_api_version_t version, zes_ras_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Ras);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetSchedulerProcAddrTable(ze_api_version_t version, zes_scheduler_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Scheduler);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetStandbyProcAddrTable(ze_api_version_t version, zes_standby_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Standby);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zesGetTemperatureProcAddrTable(ze_api_version_t version, zes_temperature_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0SysmanDdi.Temperature);
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zelGetTracerApiProcAddrTable(ze_api_version_t version, zel_tracer_dditable_t *pDdiTable) {
    return getAddressTable(version, pDdiTable, l0TracingDdi.Tracer);
}

namespace Cal::Icd::LevelZero {

// Global constuctor idiom to initialize required symbols.
struct GlobalL0DdiConstructor {
    GlobalL0DdiConstructor() {
        initL0Ddi(l0Ddi);
        initL0ToolsDdi(l0ToolsDdi);
        initL0SysmanDdi(l0SysmanDdi);
    }
} globalL0DdiConstructor;

} // namespace Cal::Icd::LevelZero
