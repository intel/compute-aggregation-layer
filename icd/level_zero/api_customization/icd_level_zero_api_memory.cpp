/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/log.h"
#include "shared/usm.h"

namespace Cal::Icd::LevelZero {

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
    if (!Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager()->getSharedAllocationsEnabled()) {
        return Cal::Icd::LevelZero::zeMemAllocHost(hContext, host_desc, size, alignment, pptr);
    }

    Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::ImplicitArgs implicitArgs;
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
    Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager()->registerSharedAlloc(*pptr, size, getSharedAllocationPlacement(device_desc, host_desc));
    return result;
}

ze_result_t zeMemGetAllocProperties(ze_context_handle_t hContext, const void *ptr, ze_memory_allocation_properties_t *pMemAllocProperties, ze_device_handle_t *phDevice) {
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

    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &connection = globalL0Platform->getConnection();
    auto lock = connection.lock();

    int remoteFileDescriptor{};
    std::memcpy(&remoteFileDescriptor, pIpcHandle->data, sizeof(remoteFileDescriptor));

    Cal::Messages::ReqTransferFd reqTransferFd{remoteFileDescriptor};
    if (false == connection.send(reqTransferFd)) {
        log<Verbosity::error>("zeMemGetIpcHandle: Could not request transfer of file descriptor!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    int localFileDescriptor = 0;
    if (false == connection.receiveFd(localFileDescriptor)) {
        log<Verbosity::error>("zeMemGetIpcHandle: Could not receive file descriptor from service!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::memcpy(pIpcHandle->data, &localFileDescriptor, sizeof(localFileDescriptor));
    return ZE_RESULT_SUCCESS;
}

ze_result_t zeMemOpenIpcHandle(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void **pptr) {
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &connection = globalL0Platform->getConnection();
    auto lock = connection.lock();

    int localFileDescriptor{};
    std::memcpy(&localFileDescriptor, handle.data, sizeof(localFileDescriptor));

    Cal::Messages::ReqReverseTransferFd reqReverseTransferFd{};
    if (false == connection.send(reqReverseTransferFd)) {
        log<Verbosity::error>("zeMemOpenIpcHandle: Could not request reverse transfer of file descriptor!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    if (false == connection.sendFd(localFileDescriptor)) {
        log<Verbosity::error>("zeMemOpenIpcHandle: Could not send file descriptor to service for reverse transfer!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    Cal::Messages::RespReverseTransferFd respReverseTransferFd{-1};
    if (false == connection.receive(respReverseTransferFd) || respReverseTransferFd.isInvalid()) {
        log<Verbosity::error>("zeMemOpenIpcHandle: Could not receive remote file descriptor from service during reverse transfer!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::memcpy(handle.data, &respReverseTransferFd.remoteFd, sizeof(respReverseTransferFd.remoteFd));
    return zeMemOpenIpcHandleRpcHelper(hContext, hDevice, handle, flags, pptr);
}

} // namespace Cal::Icd::LevelZero
