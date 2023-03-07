/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "icd_level_zero_ipc_helpers.h"
#include "shared/log.h"
#include "shared/usm.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeMemAllocHost(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, void **pptr) {
    Cal::Rpc::LevelZero::ZeMemAllocHostRpcMImplicitArgs implicitArgs;
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
    if (!Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().getSharedAllocationsEnabled()) {
        return Cal::Icd::LevelZero::zeMemAllocHost(hContext, host_desc, size, alignment, pptr);
    }

    Cal::Rpc::LevelZero::ZeMemAllocSharedRpcMImplicitArgs implicitArgs;
    auto result = Cal::Icd::LevelZero::zeMemAllocSharedRpcHelper(hContext, device_desc, host_desc, size, alignment, hDevice, pptr, implicitArgs);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    if (false == Cal::Icd::icdGlobalState.getL0Platform()->openNewUsmHostOrSharedPointer(hContext, *pptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Icd::LevelZero::zeMemFree(hContext, *pptr);
        *pptr = nullptr;
        return result;
    }
    Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().registerSharedAlloc(*pptr, size, getSharedAllocationPlacement(device_desc, host_desc));
    return result;
}

static ze_result_t zeMemGetAllocPropertiesWithExtensions(ze_context_handle_t hContext,
                                                         const void *ptr,
                                                         ze_memory_allocation_properties_t *pMemAllocProperties,
                                                         ze_device_handle_t *phDevice) {
    struct FdIpcHandleWrapper {
        int *data{};
    };

    const auto result = zeMemGetAllocPropertiesRpcHelper(hContext, ptr, pMemAllocProperties, phDevice);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    auto current = pMemAllocProperties->pNext;
    while (current) {
        auto baseDesc = static_cast<ze_base_desc_t *>(current);
        if (baseDesc->stype == ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD) {
            auto exportFdExt = static_cast<ze_external_memory_export_fd_t *>(current);
            FdIpcHandleWrapper ipcHandle{&exportFdExt->fd};

            const auto translationResult = Cal::Icd::LevelZero::Ipc::translateIpcHandles("ze_external_memory_export_fd_t", 1u, &ipcHandle);
            if (translationResult != ZE_RESULT_SUCCESS) {
                return translationResult;
            }
        }

        current = const_cast<void *>(baseDesc->pNext);
    }

    return ZE_RESULT_SUCCESS;
}

ze_result_t zeMemGetAllocProperties(ze_context_handle_t hContext, const void *ptr, ze_memory_allocation_properties_t *pMemAllocProperties, ze_device_handle_t *phDevice) {
    if (pMemAllocProperties->pNext) {
        return zeMemGetAllocPropertiesWithExtensions(hContext, ptr, pMemAllocProperties, phDevice);
    }

    auto l0Context = static_cast<IcdL0Context *>(hContext);
    auto found = l0Context->allocPropertiesCache.obtainProperties(ptr, pMemAllocProperties, phDevice);
    if (found) {
        return ZE_RESULT_SUCCESS;
    }
    ze_device_handle_t localDeviceHandle;
    auto ret = zeMemGetAllocPropertiesRpcHelper(hContext, ptr, pMemAllocProperties, &localDeviceHandle);
    l0Context->allocPropertiesCache.cacheProperties(ptr, pMemAllocProperties, &localDeviceHandle);
    if (phDevice) {
        phDevice[0] = localDeviceHandle;
    }
    return ret;
}

ze_result_t zeMemGetIpcHandle(ze_context_handle_t hContext, const void *ptr, ze_ipc_mem_handle_t *pIpcHandle) {
    const auto rpcCommandResult = zeMemGetIpcHandleRpcHelper(hContext, ptr, pIpcHandle);
    if (rpcCommandResult != ZE_RESULT_SUCCESS) {
        return rpcCommandResult;
    }

    return Cal::Icd::LevelZero::Ipc::translateIpcHandles("zeMemGetIpcHandle", 1u, pIpcHandle);
}

ze_result_t zeMemOpenIpcHandle(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void **pptr) {
    const auto reverseTranslationResult = Cal::Icd::LevelZero::Ipc::reverseTranslateIpcHandles("zeMemOpenIpcHandle", 1u, &handle);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    return zeMemOpenIpcHandleRpcHelper(hContext, hDevice, handle, flags, pptr);
}

} // namespace Cal::Icd::LevelZero
