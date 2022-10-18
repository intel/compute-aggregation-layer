/*
 * Copyright (C) 2022 Intel Corporation
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
ze_result_t (*zeInit)(ze_init_flags_t flags) = nullptr;
ze_result_t (*zeCommandListCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) = nullptr;
ze_result_t (*zeCommandListCreateImmediate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) = nullptr;
ze_result_t (*zeCommandListDestroy)(ze_command_list_handle_t hCommandList) = nullptr;
ze_result_t (*zeCommandListClose)(ze_command_list_handle_t hCommandList) = nullptr;
ze_result_t (*zeCommandListReset)(ze_command_list_handle_t hCommandList) = nullptr;
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
ze_result_t (*zeDeviceCanAccessPeer)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) = nullptr;
ze_result_t (*zeDeviceGetStatus)(ze_device_handle_t hDevice) = nullptr;
ze_result_t (*zeDeviceGetGlobalTimestamps)(ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) = nullptr;
ze_result_t (*zeDriverGet)(uint32_t* pCount, ze_driver_handle_t* phDrivers) = nullptr;
ze_result_t (*zeDriverGetApiVersion)(ze_driver_handle_t hDriver, ze_api_version_t* version) = nullptr;
ze_result_t (*zeDriverGetProperties)(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) = nullptr;
ze_result_t (*zeDriverGetIpcProperties)(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) = nullptr;
ze_result_t (*zeDriverGetExtensionProperties)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) = nullptr;
ze_result_t (*zeDriverGetExtensionFunctionAddress)(ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress) = nullptr;
ze_result_t (*zeEventPoolCreate)(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) = nullptr;
ze_result_t (*zeEventPoolDestroy)(ze_event_pool_handle_t hEventPool) = nullptr;
ze_result_t (*zeEventCreate)(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) = nullptr;
ze_result_t (*zeEventDestroy)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventPoolGetIpcHandle)(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc) = nullptr;
ze_result_t (*zeEventPoolOpenIpcHandle)(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool) = nullptr;
ze_result_t (*zeEventPoolCloseIpcHandle)(ze_event_pool_handle_t hEventPool) = nullptr;
ze_result_t (*zeCommandListAppendBarrier)(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeCommandListAppendSignalEvent)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeCommandListAppendWaitOnEvents)(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) = nullptr;
ze_result_t (*zeEventHostSignal)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventHostSynchronize)(ze_event_handle_t hEvent, uint64_t timeout) = nullptr;
ze_result_t (*zeEventQueryStatus)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventHostReset)(ze_event_handle_t hEvent) = nullptr;
ze_result_t (*zeEventQueryKernelTimestamp)(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) = nullptr;
ze_result_t (*zeFenceCreate)(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) = nullptr;
ze_result_t (*zeFenceDestroy)(ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeFenceHostSynchronize)(ze_fence_handle_t hFence, uint64_t timeout) = nullptr;
ze_result_t (*zeFenceQueryStatus)(ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeFenceReset)(ze_fence_handle_t hFence) = nullptr;
ze_result_t (*zeKernelSetGlobalOffsetExp)(ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) = nullptr;
ze_result_t (*zeMemAllocShared)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) = nullptr;
ze_result_t (*zeMemAllocDevice)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) = nullptr;
ze_result_t (*zeMemAllocHost)(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) = nullptr;
ze_result_t (*zeMemFree)(ze_context_handle_t hContext, void* ptr) = nullptr;
ze_result_t (*zeMemGetAllocProperties)(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) = nullptr;
ze_result_t (*zeMemGetAddressRange)(ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) = nullptr;
ze_result_t (*zeModuleCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) = nullptr;
ze_result_t (*zeModuleDestroy)(ze_module_handle_t hModule) = nullptr;
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
ze_result_t (*zeKernelSetCacheConfig)(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) = nullptr;
ze_result_t (*zeKernelGetProperties)(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) = nullptr;
ze_result_t (*zeKernelGetName)(ze_kernel_handle_t hKernel, size_t* pSize, char* pName) = nullptr;
ze_result_t (*zeCommandListAppendLaunchKernel)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) = nullptr;
ze_result_t (*zeDevicePciGetPropertiesExt)(ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties) = nullptr;

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
    
    zeInit = reinterpret_cast<decltype(zeInit)>(dlsym(libraryHandle, "zeInit"));
    if(nullptr == zeInit){
        log<Verbosity::error>("Missing symbol zeInit in %s", loadPath.c_str());
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
    zeDevicePciGetPropertiesExt = reinterpret_cast<decltype(zeDevicePciGetPropertiesExt)>(dlsym(libraryHandle, "zeDevicePciGetPropertiesExt"));
    if(nullptr == zeDevicePciGetPropertiesExt){
        log<Verbosity::error>("Missing symbol zeDevicePciGetPropertiesExt in %s", loadPath.c_str());
        unloadLevelZeroLibrary();
        return false;
    }
    return true;
}

void unloadLevelZeroLibrary() {
    zeInit = nullptr;
    zeCommandListCreate = nullptr;
    zeCommandListCreateImmediate = nullptr;
    zeCommandListDestroy = nullptr;
    zeCommandListClose = nullptr;
    zeCommandListReset = nullptr;
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
    zeDeviceCanAccessPeer = nullptr;
    zeDeviceGetStatus = nullptr;
    zeDeviceGetGlobalTimestamps = nullptr;
    zeDriverGet = nullptr;
    zeDriverGetApiVersion = nullptr;
    zeDriverGetProperties = nullptr;
    zeDriverGetIpcProperties = nullptr;
    zeDriverGetExtensionProperties = nullptr;
    zeDriverGetExtensionFunctionAddress = nullptr;
    zeEventPoolCreate = nullptr;
    zeEventPoolDestroy = nullptr;
    zeEventCreate = nullptr;
    zeEventDestroy = nullptr;
    zeEventPoolGetIpcHandle = nullptr;
    zeEventPoolOpenIpcHandle = nullptr;
    zeEventPoolCloseIpcHandle = nullptr;
    zeCommandListAppendBarrier = nullptr;
    zeCommandListAppendSignalEvent = nullptr;
    zeCommandListAppendWaitOnEvents = nullptr;
    zeEventHostSignal = nullptr;
    zeEventHostSynchronize = nullptr;
    zeEventQueryStatus = nullptr;
    zeEventHostReset = nullptr;
    zeEventQueryKernelTimestamp = nullptr;
    zeFenceCreate = nullptr;
    zeFenceDestroy = nullptr;
    zeFenceHostSynchronize = nullptr;
    zeFenceQueryStatus = nullptr;
    zeFenceReset = nullptr;
    zeKernelSetGlobalOffsetExp = nullptr;
    zeMemAllocShared = nullptr;
    zeMemAllocDevice = nullptr;
    zeMemAllocHost = nullptr;
    zeMemFree = nullptr;
    zeMemGetAllocProperties = nullptr;
    zeMemGetAddressRange = nullptr;
    zeModuleCreate = nullptr;
    zeModuleDestroy = nullptr;
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
    zeKernelSetCacheConfig = nullptr;
    zeKernelGetProperties = nullptr;
    zeKernelGetName = nullptr;
    zeCommandListAppendLaunchKernel = nullptr;
    zeDevicePciGetPropertiesExt = nullptr;
    if(libraryHandle){
        dlclose(libraryHandle);
    }
    libraryHandle = nullptr;
}

bool isLevelZeroLibraryLoaded() {
    return nullptr != libraryHandle;
}

} // namespace Standard


bool isSuccessful(ze_result_t result) {
    return result == ZE_RESULT_SUCCESS;
}

} // namespace LevelZero
} // namespace Apis
} // namespace Service
} // namespace Cal
// #### Generated code -- end ####
