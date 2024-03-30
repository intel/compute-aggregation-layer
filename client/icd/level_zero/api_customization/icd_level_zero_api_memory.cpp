/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/icd_global_state.h"
#include "client/icd/icd_page_fault_manager.h"
#include "client/icd/level_zero/icd_level_zero.h"
#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd_level_zero_api.h"
#include "icd_level_zero_ipc_helpers.h"
#include "shared/log.h"
#include "shared/usm.h"

namespace Cal::Client::Icd::LevelZero {

inline static PageFaultManager::Placement getSharedAllocationPlacement(const ze_device_mem_alloc_desc_t *deviceDesc, const ze_host_mem_alloc_desc_t *hostDesc) {
    auto placement = PageFaultManager::Placement::HOST;
    if (deviceDesc->flags & ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_INITIAL_PLACEMENT) {
        placement = PageFaultManager::Placement::DEVICE;
    }
    if (hostDesc->flags & ZE_HOST_MEM_ALLOC_FLAG_BIAS_INITIAL_PLACEMENT) {
        placement = PageFaultManager::Placement::HOST;
    }
    return placement;
}

ze_result_t zeMemAllocHost(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, void **pptr) {
    Cal::Rpc::LevelZero::ZeMemAllocHostRpcMImplicitArgs implicitArgs;
    auto result = Cal::Client::Icd::LevelZero::zeMemAllocHostRpcHelper(hContext, host_desc, size, alignment, pptr, implicitArgs);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    if (false == Cal::Client::Icd::icdGlobalState.getL0Platform()->openNewUsmHostOrSharedPointer(hContext, *pptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Client::Icd::LevelZero::zeMemFree(hContext, *pptr);
        *pptr = nullptr;
    }
    return result;
}

ze_result_t zeMemAllocShared(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void **pptr) {
    if (!Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().getSharedAllocationsEnabled()) {
        return Cal::Client::Icd::LevelZero::zeMemAllocHost(hContext, host_desc, size, alignment, pptr);
    }

    Cal::Rpc::LevelZero::ZeMemAllocSharedRpcMImplicitArgs implicitArgs;
    auto result = Cal::Client::Icd::LevelZero::zeMemAllocSharedRpcHelper(hContext, device_desc, host_desc, size, alignment, hDevice, pptr, implicitArgs);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    if (false == Cal::Client::Icd::icdGlobalState.getL0Platform()->openNewUsmHostOrSharedPointer(hContext, *pptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Client::Icd::LevelZero::zeMemFree(hContext, *pptr);
        *pptr = nullptr;
        return result;
    }
    Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().registerSharedAlloc(*pptr, size, getSharedAllocationPlacement(device_desc, host_desc));
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
            const auto translationResult = Cal::Client::Icd::LevelZero::Ipc::toLocalFds("ze_external_memory_export_fd_t", 1u, &ipcHandle);
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

    auto ret = Cal::Client::Icd::LevelZero::Ipc::toLocalFds("zeMemGetIpcHandle", 1u, pIpcHandle);
    return ret;
}

ze_result_t zeMemOpenIpcHandle(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void **pptr) {
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::toRemoteFds("zeMemOpenIpcHandle", 1u, &handle);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    auto *globalL0Platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    globalL0Platform->addPtrToIpcMap(*pptr, Cal::Utils::RemoteFd(*reinterpret_cast<int *>(handle.data)));

    return zeMemOpenIpcHandleRpcHelper(hContext, hDevice, handle, flags, pptr);
}

ze_result_t zeMemPutIpcHandle(ze_context_handle_t hContext, ze_ipc_mem_handle_t handle) {
    Cal::Utils::LocalFd localFd{*(int *)handle.data};
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::toRemoteFds("zeMemPutIpcHandle", 1u, &handle);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    auto *globalL0Platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    if (globalL0Platform->decreaseRefcountForIpcFd(Cal::Utils::RemoteFd(*reinterpret_cast<int *>(handle.data)))) {
        Cal::Sys::close(localFd.fd);
    }

    return zeMemPutIpcHandleRpcHelper(hContext, handle);
}

ze_result_t zeMemCloseIpcHandle(ze_context_handle_t hContext, const void *ptr) {
    auto *globalL0Platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto remoteFdToClose = globalL0Platform->removePtrFromIpcMap(ptr);

    Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcMImplicitArgs iargs;
    iargs.handle_to_close = remoteFdToClose.fd;
    return zeMemCloseIpcHandleRpcHelper(hContext, ptr, iargs);
}

ze_result_t zeMemGetIpcHandleFromFileDescriptorExp(ze_context_handle_t hContext, uint64_t handle, ze_ipc_mem_handle_t *pIpcHandle) {
    struct FdIpcHandleWrapper {
        uint64_t *data{};
    };
    FdIpcHandleWrapper fdWrapper{&handle};
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::toRemoteFds("zeMemGetIpcHandleFromFileDescriptorExp", 1u, &fdWrapper);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    const auto rpcCommandResult = zeMemGetIpcHandleFromFileDescriptorExpRpcHelper(hContext, handle, pIpcHandle);
    if (rpcCommandResult != ZE_RESULT_SUCCESS) {
        return rpcCommandResult;
    }

    return Cal::Client::Icd::LevelZero::Ipc::toLocalFds("zeMemGetIpcHandleFromFileDescriptorExp", 1u, pIpcHandle);
}

ze_result_t zeMemGetFileDescriptorFromIpcHandleExp(ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t *pHandle) {
    const auto reverseTranslationResult = Cal::Client::Icd::LevelZero::Ipc::toRemoteFds("zeMemGetFileDescriptorFromIpcHandleExp", 1u, &ipcHandle);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        return reverseTranslationResult;
    }

    const auto rpcCommandResult = zeMemGetFileDescriptorFromIpcHandleExpRpcHelper(hContext, ipcHandle, pHandle);
    if (rpcCommandResult != ZE_RESULT_SUCCESS) {
        return rpcCommandResult;
    }

    struct FdIpcHandleWrapper {
        uint64_t *data{};
    };
    FdIpcHandleWrapper fdWrapper{pHandle};
    return Cal::Client::Icd::LevelZero::Ipc::toLocalFds("zeMemGetFileDescriptorFromIpcHandleExp", 1u, &fdWrapper);
}

} // namespace Cal::Client::Icd::LevelZero
