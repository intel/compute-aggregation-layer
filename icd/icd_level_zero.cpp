/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd/icd_level_zero.h"

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd/icd_global_state.h"
#include "include/cal.h"
#include "shared/log.h"
#include "shared/usm.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <level_zero/layers/zel_tracing_api.h>
#include <level_zero/layers/zel_tracing_ddi.h>
#include <level_zero/zes_api.h>
#include <level_zero/zes_ddi.h>
#include <level_zero/zet_api.h>
#include <level_zero/zet_ddi.h>

extern char *__progname;

ze_dditable_t l0Dddi = {};
ze_api_version_t supportedL0ApiVersion = ZE_API_VERSION_CURRENT;

template <typename DdiT>
ze_result_t validateTable(ze_api_version_t version, DdiT *ddi) {
    if (nullptr == ddi)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_MAJOR_VERSION(supportedL0ApiVersion) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(supportedL0ApiVersion) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetDriverProcAddrTable(
    ze_api_version_t version,
    ze_driver_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Driver;
    }
    return err;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemProcAddrTable(
    ze_api_version_t version,
    ze_mem_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Mem;
    }
    return err;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetContextProcAddrTable(
    ze_api_version_t version,
    ze_context_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Context;
    }
    return err;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetPhysicalMemProcAddrTable(
    ze_api_version_t version,
    ze_physical_mem_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.PhysicalMem;
    }
    return err;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetVirtualMemProcAddrTable(
    ze_api_version_t version,
    ze_virtual_mem_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.VirtualMem;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetGlobalProcAddrTable(
    ze_api_version_t version,
    ze_global_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        pDdiTable->pfnInit = Cal::Icd::LevelZero::zeInit;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetDeviceProcAddrTable(
    ze_api_version_t version,
    ze_device_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Device;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,
    ze_command_queue_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.CommandQueue;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetCommandListProcAddrTable(
    ze_api_version_t version,
    ze_command_list_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.CommandList;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetFenceProcAddrTable(
    ze_api_version_t version,
    ze_fence_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Fence;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,
    ze_event_pool_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.EventPool;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetEventProcAddrTable(
    ze_api_version_t version,
    ze_event_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Event;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetEventExpProcAddrTable(
    ze_api_version_t version,
    ze_event_exp_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.EventExp;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetImageProcAddrTable(
    ze_api_version_t version,
    ze_image_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Image;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetModuleProcAddrTable(
    ze_api_version_t version,
    ze_module_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Module;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,
    ze_module_build_log_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.ModuleBuildLog;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetKernelProcAddrTable(
    ze_api_version_t version,
    ze_kernel_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Kernel;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetSamplerProcAddrTable(
    ze_api_version_t version,
    ze_sampler_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.Sampler;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetKernelExpProcAddrTable(
    ze_api_version_t version,
    ze_kernel_exp_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.KernelExp;
    }
    return err;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetImageExpProcAddrTable(
    ze_api_version_t version,
    ze_image_exp_dditable_t *pDdiTable) {
    ze_result_t err = validateTable(version, pDdiTable);
    if (err == ZE_RESULT_SUCCESS) {
        *pDdiTable = l0Dddi.ImageExp;
    }
    return err;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDeviceExpProcAddrTable(
    ze_api_version_t version,
    ze_device_exp_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricEdgeExpProcAddrTable(
    ze_api_version_t version,
    ze_fabric_edge_exp_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricVertexExpProcAddrTable(
    ze_api_version_t version,
    ze_fabric_vertex_exp_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDeviceProcAddrTable(
    ze_api_version_t version,
    zet_device_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetContextProcAddrTable(
    ze_api_version_t version,
    zet_context_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetCommandListProcAddrTable(
    ze_api_version_t version,
    zet_command_list_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetKernelProcAddrTable(
    ze_api_version_t version,
    zet_kernel_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetModuleProcAddrTable(
    ze_api_version_t version,
    zet_module_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDebugProcAddrTable(
    ze_api_version_t version,
    zet_debug_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProcAddrTable(
    ze_api_version_t version,
    zet_metric_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,
    zet_metric_group_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupExpProcAddrTable(
    ze_api_version_t version,
    zet_metric_group_exp_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,
    zet_metric_query_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,
    zet_metric_query_pool_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricStreamerProcAddrTable(
    ze_api_version_t version,
    zet_metric_streamer_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetTracerExpProcAddrTable(
    ze_api_version_t version,
    zet_tracer_exp_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDeviceProcAddrTable(
    ze_api_version_t version,
    zes_device_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDriverProcAddrTable(
    ze_api_version_t version,
    zes_driver_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDiagnosticsProcAddrTable(
    ze_api_version_t version,
    zes_diagnostics_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetEngineProcAddrTable(
    ze_api_version_t version,
    zes_engine_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFabricPortProcAddrTable(
    ze_api_version_t version,
    zes_fabric_port_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFanProcAddrTable(
    ze_api_version_t version,
    zes_fan_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFirmwareProcAddrTable(
    ze_api_version_t version,
    zes_firmware_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFrequencyProcAddrTable(
    ze_api_version_t version,
    zes_frequency_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetLedProcAddrTable(
    ze_api_version_t version,
    zes_led_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetMemoryProcAddrTable(
    ze_api_version_t version,
    zes_memory_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPerformanceFactorProcAddrTable(
    ze_api_version_t version,
    zes_performance_factor_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPowerProcAddrTable(
    ze_api_version_t version,
    zes_power_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPsuProcAddrTable(
    ze_api_version_t version,
    zes_psu_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetRasProcAddrTable(
    ze_api_version_t version,
    zes_ras_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetSchedulerProcAddrTable(
    ze_api_version_t version,
    zes_scheduler_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetStandbyProcAddrTable(
    ze_api_version_t version,
    zes_standby_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetTemperatureProcAddrTable(
    ze_api_version_t version,
    zes_temperature_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zelGetTracerApiProcAddrTable(
    ze_api_version_t version,
    zel_tracer_dditable_t *pDdiTable) {
    return ZE_RESULT_SUCCESS;
}

namespace Cal {
namespace Icd {
namespace LevelZero {

ze_result_t zeInit(ze_init_flags_t flags) {
    const auto platform = Cal::Icd::icdGlobalState.getL0Platform();
    if (!platform || !platform->valid()) {
        log<Verbosity::error>("CAL service not available. zeInit() cannot be performed!");
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    log<Verbosity::info>("Initializing LevelZero! Flags argument used with zeInit() will be ignored by Compute Aggregation Layer service.");
    return Cal::Icd::LevelZero::zeInitRpcHelper(flags);
}

ze_result_t zeDriverGet(uint32_t *pCount, ze_driver_handle_t *phDrivers) {
    const auto platform = Cal::Icd::icdGlobalState.getL0Platform();
    if (!platform || !platform->valid()) {
        log<Verbosity::debug>("CAL service not available. Trying to return zero available drivers!");
        if (pCount) {
            *pCount = 0;
        }
        return ZE_RESULT_SUCCESS;
    }

    if (nullptr == platform->asRemoteObject()) {
        log<Verbosity::debug>("Getting driver from deamon via zeDriverGet()");
        ze_driver_handle_t calDriverHandle{};

        uint32_t handleDriversArraySize{1};
        auto ret = Cal::Icd::LevelZero::zeDriverGetRpcHelper(&handleDriversArraySize, &calDriverHandle);
        if ((ZE_RESULT_SUCCESS != ret) || (nullptr == calDriverHandle)) {
            log<Verbosity::debug>("Failed to get ze_driver_handle_t from service");
            if (pCount) {
                *pCount = 0;
            }
            return ZE_RESULT_SUCCESS;
        }

        log<Verbosity::debug>("Got ze_driver_handle_t from service : %p", calDriverHandle);
        platform->setRemoteObject(calDriverHandle);
    }

    if (pCount) {
        if (*pCount > 0) {
            phDrivers[0] = platform;
        }

        *pCount = 1;
    }

    return ZE_RESULT_SUCCESS;
}

ze_result_t zeMemAllocHost(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, void **pptr) {
    Cal::Rpc::LevelZero::ZeMemAllocHostRpcM::ImplicitArgs implicitArgs;
    auto result = Cal::Icd::LevelZero::zeMemAllocHostRpcHelper(hContext, host_desc, size, alignment, pptr, implicitArgs);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    if (false == Cal::Icd::icdGlobalState.getL0Platform()->openNewUsmHostOrSharedPointer(hContext, *pptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Icd::LevelZero::zeMemFree(hContext, *pptr);
        *pptr = nullptr;
    }
    return result;
}

ze_result_t zeMemAllocShared(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void **pptr) {
    Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::ImplicitArgs implicitArgs;
    auto result = Cal::Icd::LevelZero::zeMemAllocSharedRpcHelper(hContext, device_desc, host_desc, size, alignment, hDevice, pptr, implicitArgs);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    if (false == Cal::Icd::icdGlobalState.getL0Platform()->openNewUsmHostOrSharedPointer(hContext, *pptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Icd::LevelZero::zeMemFree(hContext, *pptr);
        *pptr = nullptr;
    }
    return result;
}

ze_result_t zeCommandListAppendMemoryFill(ze_command_list_handle_t hCommandList,
                                          void *ptr,
                                          const void *pattern,
                                          size_t pattern_size,
                                          size_t size,
                                          ze_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          ze_event_handle_t *phWaitEvents) {
    auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (ptr == nullptr || pattern == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();

    const void *ptrs[] = {ptr, pattern};
    bool testResults[2] = {};
    globalL0Platform->areUsm(2, ptrs, testResults);

    const auto &[dstIsUsm, srcIsUsm] = testResults;
    if (dstIsUsm && srcIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperUsm2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (dstIsUsm) {
        return zeCommandListAppendMemoryFillRpcHelperMalloc2Usm(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (srcIsUsm) {
        log<Verbosity::debug>("zeCommandListAppendMemoryFill() from USM to host's heap/stack is not supported yet!");
    } else {
        if (IcdL0CommandList::rangesOverlap(pattern, pattern_size, ptr, size)) {
            log<Verbosity::debug>("zeCommandListAppendMemoryFill(): host's heap/stack memory blocks overlap!");
            return ZE_RESULT_ERROR_OVERLAPPING_REGIONS;
        }

        log<Verbosity::debug>("zeCommandListAppendMemoryFill() from host's heap/stack to host's heap/stack is not supported yet!");
    }

    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

ze_result_t zeCommandListAppendMemoryCopy(ze_command_list_handle_t hCommandList,
                                          void *dstptr,
                                          const void *srcptr,
                                          size_t size,
                                          ze_event_handle_t hSignalEvent,
                                          uint32_t numWaitEvents,
                                          ze_event_handle_t *phWaitEvents) {

    auto icdCommandList = static_cast<IcdL0CommandList *>(hCommandList);
    if (icdCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (dstptr == nullptr || srcptr == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();

    const void *ptrs[] = {dstptr, srcptr};
    bool testResults[2] = {};
    globalL0Platform->areUsm(2, ptrs, testResults);

    const auto &[dstIsUsm, srcIsUsm] = testResults;
    if (dstIsUsm && srcIsUsm) {
        return zeCommandListAppendMemoryCopyRpcHelperUsm2Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (dstIsUsm) {
        icdCommandList->registerMemoryToWrite(srcptr, size);
        return zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    } else if (srcIsUsm) {
        log<Verbosity::debug>("zeCommandListAppendMemoryCopy() from USM to host's heap/stack is not supported yet!");
    } else {
        if (IcdL0CommandList::rangesOverlap(srcptr, dstptr, size)) {
            log<Verbosity::debug>("zeCommandListAppendMemoryCopy(): host's heap/stack memory blocks overlap!");
            return ZE_RESULT_ERROR_OVERLAPPING_REGIONS;
        }

        log<Verbosity::debug>("zeCommandListAppendMemoryCopy() from host's heap/stack to host's heap/stack is not supported yet!");
    }

    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

void IcdL0CommandList::registerMemoryToWrite(const void *srcPtr, size_t srcSize) {
    const auto overlaps = [srcPtr, srcSize](const auto &chunk) {
        return IcdL0CommandList::rangesOverlap(chunk.address, chunk.size, srcPtr, srcSize);
    };

    const auto overlappingCount = std::count_if(std::begin(memoryToWrite), std::end(memoryToWrite), overlaps);
    if (overlappingCount == 0) {
        memoryToWrite.emplace_back(srcPtr, srcSize);
        return;
    }

    if (overlappingCount == 1) {
        auto overlappingChunkIt = std::find_if(std::begin(memoryToWrite), std::end(memoryToWrite), overlaps);
        *overlappingChunkIt = mergeChunks(ChunkEntry{srcPtr, srcSize}, *overlappingChunkIt);

        return;
    }

    std::vector<ChunkEntry> newChunks{};
    newChunks.reserve(memoryToWrite.size());

    ChunkEntry currentChunk{srcPtr, srcSize};
    for (auto &chunk : memoryToWrite) {
        if (!rangesOverlap(chunk.address, chunk.size, srcPtr, srcSize)) {
            newChunks.push_back(chunk);
            continue;
        }

        currentChunk = mergeChunks(currentChunk, chunk);
    }

    newChunks.push_back(currentChunk);
    memoryToWrite = std::move(newChunks);
}

bool IcdL0CommandList::rangesOverlap(const void *srcPtr, const void *dstPtr, size_t size) {
    return rangesOverlap(srcPtr, size, dstPtr, size);
}

bool IcdL0CommandList::rangesOverlap(const void *srcPtr, size_t srcSize, const void *dstPtr, size_t dstSize) {
    const auto srcBegin = reinterpret_cast<uintptr_t>(srcPtr);
    const auto srcEnd = srcBegin + srcSize;

    const auto dstBegin = reinterpret_cast<uintptr_t>(dstPtr);
    const auto dstEnd = dstBegin + dstSize;

    return (srcBegin <= dstBegin && dstBegin < srcEnd) || (dstBegin <= srcBegin && srcBegin < dstEnd);
}

auto IcdL0CommandList::mergeChunks(const ChunkEntry &first, const ChunkEntry &second) -> ChunkEntry {
    const auto firstBegin = reinterpret_cast<uintptr_t>(first.address);
    const auto firstEnd = firstBegin + first.size;

    const auto secondBegin = reinterpret_cast<uintptr_t>(second.address);
    const auto secondEnd = secondBegin + second.size;

    const auto mergedBegin = std::min(firstBegin, secondBegin);
    const auto mergedEnd = std::max(firstEnd, secondEnd);

    const auto mergedAddress = reinterpret_cast<const void *>(mergedBegin);
    const auto mergedSize = static_cast<size_t>(mergedEnd - mergedBegin);

    return ChunkEntry{mergedAddress, mergedSize};
}

ze_result_t zeCommandQueueExecuteCommandLists(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t hFence) {
    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();

    for (uint32_t i = 0u; i < numCommandLists; ++i) {
        const auto icdCommandList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        const auto &memoryToWrite = icdCommandList->getMemoryToWrite();

        uint32_t transferDescsCount{0};
        const auto queryCountResult = zeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelper(static_cast<uint32_t>(memoryToWrite.size()),
                                                                                                 memoryToWrite.data(),
                                                                                                 &transferDescsCount,
                                                                                                 nullptr);
        if (queryCountResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("Could not get total count of memory blocks to write from service! Execution of command list would be invalid!");
            return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        std::vector<Cal::Rpc::ShmemTransferDesc> transferDescs;
        transferDescs.resize(transferDescsCount);

        const auto queryTransferDescs = zeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelper(static_cast<uint32_t>(memoryToWrite.size()),
                                                                                                   memoryToWrite.data(),
                                                                                                   &transferDescsCount,
                                                                                                   transferDescs.data());
        if (queryTransferDescs != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("Could not get memory blocks to write from service! Execution of command list would be invalid!");
            return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        if (!globalL0Platform->writeRequiredMemory(transferDescs)) {
            log<Verbosity::error>("Could not write required memory from user's stack/heap! Execution of command list would be invalid!");
            return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
    }

    return zeCommandQueueExecuteCommandListsRpcHelper(hCommandQueue, numCommandLists, phCommandLists, hFence);
}

ze_result_t zeModuleGetKernelNames(ze_module_handle_t hModule, uint32_t *pCount, const char **pNames) {
    auto icdModule = static_cast<IcdL0Module *>(hModule);
    if (!icdModule) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    if (!pCount) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if (*pCount == 0) {
        return icdModule->getKernelNamesCount(pCount);
    }

    return icdModule->getKernelNames(pCount, pNames);
}

ze_result_t zeDriverGetExtensionFunctionAddress(ze_driver_handle_t hDriver, const char *name, void **ppFunctionAddress) {
    if (ppFunctionAddress) {
        *ppFunctionAddress = nullptr;
    }

    return ZE_RESULT_ERROR_INVALID_ARGUMENT;
}

ze_result_t IcdL0Module::getKernelNames(uint32_t *pCount, const char **pNames) {
    if (!wasKernelNamesQueried && !queryKernelNames()) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    const auto count = std::min(*pCount, static_cast<uint32_t>(kernelNames.size()));
    for (uint32_t i = 0; i < count; ++i) {
        pNames[i] = kernelNames[i].c_str();
    }

    *pCount = count;
    return ZE_RESULT_SUCCESS;
}

ze_result_t IcdL0Module::getKernelNamesCount(uint32_t *pCount) {
    if (!wasKernelNamesQueried && !queryKernelNames()) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    *pCount = static_cast<uint32_t>(kernelNames.size());
    return ZE_RESULT_SUCCESS;
}

bool IcdL0Module::queryKernelNames() {
    uint32_t totalLength{0};
    auto ret = Cal::Icd::LevelZero::zeModuleGetKernelNamesRpcHelper(this, &totalLength, nullptr);
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::debug>("Failed to get total length of names of kernels from module from service!");
        return false;
    }

    std::vector<char> concatenatedNames;
    concatenatedNames.resize(totalLength);

    ret = Cal::Icd::LevelZero::zeModuleGetKernelNamesRpcHelper(this, &totalLength, concatenatedNames.data());
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::debug>("Failed to get concatenated names of kernels from module from service!");
        return false;
    }

    populateKernelNames(concatenatedNames);

    wasKernelNamesQueried = true;
    return true;
}

void IcdL0Module::populateKernelNames(const std::vector<char> &buffer) {
    const auto data = buffer.data();

    auto lastBegin = 0u;
    for (auto i = 0u; i < buffer.size(); ++i) {
        if (buffer[i] == '\0') {
            kernelNames.emplace_back(data + lastBegin, data + i);
            lastBegin = i + 1;
        }
    }
}

bool IcdL0Device::patchDeviceName(ze_device_properties_t &properties) {
    const auto nullTerminator = std::find(std::begin(properties.name), std::end(properties.name), '\0');
    if (nullTerminator == std::begin(properties.name)) {
        log<Verbosity::critical>("Cannot patch device name! It is empty!");
        return false;
    }

    static constexpr char deviceNameSuffix[] = " (aggregated)";
    static constexpr auto requiredSpace = std::distance(std::begin(deviceNameSuffix), std::end(deviceNameSuffix));

    const auto availableSpace = std::distance(nullTerminator, std::end(properties.name));
    if (availableSpace < requiredSpace) {
        log<Verbosity::critical>("Cannot patch device name with '(aggregated)' suffix! Not enough space!");
        return false;
    }

    std::copy(std::begin(deviceNameSuffix), std::end(deviceNameSuffix), nullTerminator);
    return true;
}

template <typename RemoteL0ObjectT, typename LocalL0ObjectT>
void objectCleanup(void *remote, void *local) {
    Cal::Icd::icdGlobalState.getL0Platform()->removeObjectFromMap(static_cast<RemoteL0ObjectT>(remote), static_cast<LocalL0ObjectT>(local));
}

template void objectCleanup<ze_device_handle_t, IcdL0Device *>(void *, void *);
template void objectCleanup<ze_context_handle_t, IcdL0Context *>(void *, void *);
template void objectCleanup<ze_command_queue_handle_t, IcdL0CommandQueue *>(void *, void *);
template void objectCleanup<ze_command_list_handle_t, IcdL0CommandList *>(void *, void *);
template void objectCleanup<ze_module_handle_t, IcdL0Module *>(void *, void *);
template void objectCleanup<ze_module_build_log_handle_t, IcdL0ModuleBuildLog *>(void *, void *);
template void objectCleanup<ze_kernel_handle_t, IcdL0Kernel *>(void *, void *);
template void objectCleanup<ze_event_handle_t, IcdL0Event *>(void *, void *);
template void objectCleanup<ze_event_pool_handle_t, IcdL0EventPool *>(void *, void *);
template void objectCleanup<ze_fence_handle_t, IcdL0Fence *>(void *, void *);

struct GlobalL0DdiConstructor {
    GlobalL0DdiConstructor() {
        initL0Ddi(l0Dddi);
    }
};

GlobalL0DdiConstructor globalL0DdiConstructor;

} // namespace LevelZero
} // namespace Icd
} // namespace Cal
