/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####
#include "service/service.h"
#include "shared/rpc.h"
#include "shared/utils.h"
#include "generated_rpc_messages_level_zero.h"

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

namespace Cal {
namespace Service {
namespace Apis {
namespace LevelZero {

namespace Standard {
bool loadLevelZeroLibrary(std::optional<std::string> path);
void unloadLevelZeroLibrary();
bool isLevelZeroLibraryLoaded();
    
extern ze_result_t (*zeInit)(ze_init_flags_t flags);
extern ze_result_t (*zeCommandListCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList);
extern ze_result_t (*zeCommandListCreateImmediate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList);
extern ze_result_t (*zeCommandListDestroy)(ze_command_list_handle_t hCommandList);
extern ze_result_t (*zeCommandListClose)(ze_command_list_handle_t hCommandList);
extern ze_result_t (*zeCommandListReset)(ze_command_list_handle_t hCommandList);
extern ze_result_t (*zeCommandQueueCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue);
extern ze_result_t (*zeCommandQueueDestroy)(ze_command_queue_handle_t hCommandQueue);
extern ze_result_t (*zeCommandQueueExecuteCommandLists)(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
extern ze_result_t (*zeCommandQueueSynchronize)(ze_command_queue_handle_t hCommandQueue, uint64_t timeout);
extern ze_result_t (*zeContextCreate)(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext);
extern ze_result_t (*zeContextCreateEx)(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext);
extern ze_result_t (*zeContextDestroy)(ze_context_handle_t hContext);
extern ze_result_t (*zeContextGetStatus)(ze_context_handle_t hContext);
extern ze_result_t (*zeCommandListAppendMemoryCopy)(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendMemoryFill)(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeDeviceGet)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
extern ze_result_t (*zeDeviceGetSubDevices)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
extern ze_result_t (*zeDeviceGetProperties)(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties);
extern ze_result_t (*zeDeviceGetComputeProperties)(ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties);
extern ze_result_t (*zeDeviceGetModuleProperties)(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties);
extern ze_result_t (*zeDeviceGetCommandQueueGroupProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
extern ze_result_t (*zeDeviceGetMemoryProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
extern ze_result_t (*zeDeviceGetMemoryAccessProperties)(ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties);
extern ze_result_t (*zeDeviceGetCacheProperties)(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
extern ze_result_t (*zeDeviceGetImageProperties)(ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties);
extern ze_result_t (*zeDeviceGetExternalMemoryProperties)(ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties);
extern ze_result_t (*zeDeviceGetP2PProperties)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties);
extern ze_result_t (*zeDeviceCanAccessPeer)(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value);
extern ze_result_t (*zeDeviceGetStatus)(ze_device_handle_t hDevice);
extern ze_result_t (*zeDeviceGetGlobalTimestamps)(ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp);
extern ze_result_t (*zeDriverGet)(uint32_t* pCount, ze_driver_handle_t* phDrivers);
extern ze_result_t (*zeDriverGetApiVersion)(ze_driver_handle_t hDriver, ze_api_version_t* version);
extern ze_result_t (*zeDriverGetProperties)(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties);
extern ze_result_t (*zeDriverGetIpcProperties)(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties);
extern ze_result_t (*zeDriverGetExtensionProperties)(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
extern ze_result_t (*zeDriverGetExtensionFunctionAddress)(ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress);
extern ze_result_t (*zeEventPoolCreate)(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
extern ze_result_t (*zeEventPoolDestroy)(ze_event_pool_handle_t hEventPool);
extern ze_result_t (*zeEventCreate)(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent);
extern ze_result_t (*zeEventDestroy)(ze_event_handle_t hEvent);
extern ze_result_t (*zeEventPoolGetIpcHandle)(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc);
extern ze_result_t (*zeEventPoolOpenIpcHandle)(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool);
extern ze_result_t (*zeEventPoolCloseIpcHandle)(ze_event_pool_handle_t hEventPool);
extern ze_result_t (*zeCommandListAppendBarrier)(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendSignalEvent)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
extern ze_result_t (*zeCommandListAppendWaitOnEvents)(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
extern ze_result_t (*zeEventHostSignal)(ze_event_handle_t hEvent);
extern ze_result_t (*zeEventHostSynchronize)(ze_event_handle_t hEvent, uint64_t timeout);
extern ze_result_t (*zeEventQueryStatus)(ze_event_handle_t hEvent);
extern ze_result_t (*zeCommandListAppendEventReset)(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent);
extern ze_result_t (*zeEventHostReset)(ze_event_handle_t hEvent);
extern ze_result_t (*zeEventQueryKernelTimestamp)(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr);
extern ze_result_t (*zeFenceCreate)(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence);
extern ze_result_t (*zeFenceDestroy)(ze_fence_handle_t hFence);
extern ze_result_t (*zeFenceHostSynchronize)(ze_fence_handle_t hFence, uint64_t timeout);
extern ze_result_t (*zeFenceQueryStatus)(ze_fence_handle_t hFence);
extern ze_result_t (*zeFenceReset)(ze_fence_handle_t hFence);
extern ze_result_t (*zeKernelSetGlobalOffsetExp)(ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
extern ze_result_t (*zeImageGetProperties)(ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties);
extern ze_result_t (*zeImageCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage);
extern ze_result_t (*zeImageDestroy)(ze_image_handle_t hImage);
extern ze_result_t (*zeMemAllocShared)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
extern ze_result_t (*zeMemAllocDevice)(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr);
extern ze_result_t (*zeMemAllocHost)(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr);
extern ze_result_t (*zeMemFree)(ze_context_handle_t hContext, void* ptr);
extern ze_result_t (*zeMemGetAllocProperties)(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice);
extern ze_result_t (*zeMemGetAddressRange)(ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize);
extern ze_result_t (*zeMemGetIpcHandle)(ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle);
extern ze_result_t (*zeMemOpenIpcHandle)(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr);
extern ze_result_t (*zeMemCloseIpcHandle)(ze_context_handle_t hContext, const void* ptr);
extern ze_result_t (*zeModuleCreate)(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
extern ze_result_t (*zeModuleDestroy)(ze_module_handle_t hModule);
extern ze_result_t (*zeModuleDynamicLink)(uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog);
extern ze_result_t (*zeModuleBuildLogDestroy)(ze_module_build_log_handle_t hModuleBuildLog);
extern ze_result_t (*zeModuleBuildLogGetString)(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
extern ze_result_t (*zeModuleGetNativeBinary)(ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary);
extern ze_result_t (*zeModuleGetGlobalPointer)(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
extern ze_result_t (*zeModuleGetKernelNames)(ze_module_handle_t hModule, uint32_t* pCount, const char** pNames);
extern ze_result_t (*zeModuleGetProperties)(ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties);
extern ze_result_t (*zeKernelCreate)(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
extern ze_result_t (*zeKernelDestroy)(ze_kernel_handle_t hKernel);
extern ze_result_t (*zeModuleGetFunctionPointer)(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
extern ze_result_t (*zeKernelSetGroupSize)(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ);
extern ze_result_t (*zeKernelSuggestGroupSize)(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ);
extern ze_result_t (*zeKernelSuggestMaxCooperativeGroupCount)(ze_kernel_handle_t hKernel, uint32_t* totalGroupCount);
extern ze_result_t (*zeKernelSetArgumentValue)(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
extern ze_result_t (*zeKernelSetIndirectAccess)(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags);
extern ze_result_t (*zeKernelGetIndirectAccess)(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags);
extern ze_result_t (*zeKernelSetCacheConfig)(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags);
extern ze_result_t (*zeKernelGetProperties)(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties);
extern ze_result_t (*zeKernelGetName)(ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
extern ze_result_t (*zeCommandListAppendLaunchKernel)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeCommandListAppendLaunchKernelIndirect)(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
extern ze_result_t (*zeDevicePciGetPropertiesExt)(ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties);
} // Standard

namespace Extensions {
extern ze_result_t (*zexMemGetIpcHandles)(ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles);
extern ze_result_t (*zexMemOpenIpcHandles)(ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr);
} // Extensions

bool isSuccessful(ze_result_t result);

bool zeInitHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeCommandListCreateImmediateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListCreateImmediate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreateImmediate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.altdesc ? &apiCommand->captures.altdesc : nullptr, 
                                                apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phCommandList ? &apiCommand->captures.phCommandList : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeCommandListDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListDestroy(
                                                apiCommand->args.hCommandList
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hCommandList;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeCommandListCloseHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListClose");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCloseRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListClose(
                                                apiCommand->args.hCommandList
                                                );
    return true;
}
inline bool zeCommandListResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListReset(
                                                apiCommand->args.hCommandList
                                                );
    return true;
}
inline bool zeCommandQueueCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phCommandQueue ? &apiCommand->captures.phCommandQueue : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phCommandQueue ? &apiCommand->captures.phCommandQueue : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeCommandQueueDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueDestroy(
                                                apiCommand->args.hCommandQueue
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hCommandQueue;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeCommandQueueExecuteCommandListsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueExecuteCommandLists");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueExecuteCommandLists(
                                                apiCommand->args.hCommandQueue, 
                                                apiCommand->args.numCommandLists, 
                                                apiCommand->args.phCommandLists ? apiCommand->captures.phCommandLists : nullptr, 
                                                apiCommand->args.hFence
                                                );
    return true;
}
bool zeCommandQueueExecuteCommandListsCopyMemoryRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandQueueSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueSynchronize(
                                                apiCommand->args.hCommandQueue, 
                                                apiCommand->args.timeout
                                                );
    return true;
}
inline bool zeContextCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreate(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeContextCreateExHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextCreateEx");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateExRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreateEx(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.numDevices, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr, 
                                                apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phContext ? &apiCommand->captures.phContext : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeContextDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextDestroy(
                                                apiCommand->args.hContext
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hContext;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeContextGetStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextGetStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextGetStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextGetStatus(
                                                apiCommand->args.hContext
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyRpcHelperUsm2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperUsm2Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
bool zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronous");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr ? apiCommand->captures.getDstptr() : nullptr, 
                                                apiCommand->args.srcptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronous");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.dstptr ? apiCommand->captures.getDstptr() : nullptr, 
                                                apiCommand->args.srcptr ? apiCommand->captures.getSrcptr() : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
bool zeCommandListAppendMemoryCopyRpcHelperUsm2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendMemoryFillRpcHelperUsm2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperUsm2Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pattern, 
                                                apiCommand->args.pattern_size, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
bool zeCommandListAppendMemoryFillRpcHelperUsm2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeCommandListAppendMemoryFillRpcHelperMalloc2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperMalloc2Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr, 
                                                apiCommand->args.pattern_size, 
                                                apiCommand->args.size, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr
                                                );
    return true;
}
bool zeCommandListAppendMemoryFillRpcHelperMalloc2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeDeviceGetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGet");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetSubDevicesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetSubDevices");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetSubDevices(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.phSubdevices ? apiCommand->captures.phSubdevices : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pDeviceProperties ? &apiCommand->captures.pDeviceProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetComputePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetComputeProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetComputeProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pComputeProperties ? &apiCommand->captures.pComputeProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetModulePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetModuleProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetModuleProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pModuleProperties ? &apiCommand->captures.pModuleProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetCommandQueueGroupPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetCommandQueueGroupProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCommandQueueGroupProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pCommandQueueGroupProperties ? apiCommand->captures.pCommandQueueGroupProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetMemoryPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetMemoryProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pMemProperties ? apiCommand->captures.pMemProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetMemoryAccessPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetMemoryAccessProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryAccessProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pMemAccessProperties ? &apiCommand->captures.pMemAccessProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetCachePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetCacheProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCacheProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pCacheProperties ? apiCommand->captures.pCacheProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetImagePropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetImageProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetImageProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pImageProperties ? &apiCommand->captures.pImageProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetExternalMemoryPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetExternalMemoryProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetExternalMemoryProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pExternalMemoryProperties ? &apiCommand->captures.pExternalMemoryProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetP2PPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetP2PProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetP2PProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.hPeerDevice, 
                                                apiCommand->args.pP2PProperties ? &apiCommand->captures.pP2PProperties : nullptr
                                                );
    return true;
}
inline bool zeDeviceCanAccessPeerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceCanAccessPeer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceCanAccessPeer(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.hPeerDevice, 
                                                apiCommand->args.value ? &apiCommand->captures.value : nullptr
                                                );
    return true;
}
inline bool zeDeviceGetStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetStatus(
                                                apiCommand->args.hDevice
                                                );
    return true;
}
inline bool zeDeviceGetGlobalTimestampsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDeviceGetGlobalTimestamps");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetGlobalTimestamps(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.hostTimestamp ? &apiCommand->captures.hostTimestamp : nullptr, 
                                                apiCommand->args.deviceTimestamp ? &apiCommand->captures.deviceTimestamp : nullptr
                                                );
    return true;
}
bool zeDriverGetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeDriverGetApiVersionHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetApiVersion");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetApiVersion(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.version ? &apiCommand->captures.version : nullptr
                                                );
    return true;
}
inline bool zeDriverGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetProperties(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pDriverProperties ? &apiCommand->captures.pDriverProperties : nullptr
                                                );
    return true;
}
inline bool zeDriverGetIpcPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetIpcProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetIpcProperties(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pIpcProperties ? &apiCommand->captures.pIpcProperties : nullptr
                                                );
    return true;
}
inline bool zeDriverGetExtensionPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetExtensionProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetExtensionProperties(
                                                apiCommand->args.hDriver, 
                                                apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr, 
                                                apiCommand->args.pExtensionProperties ? apiCommand->captures.pExtensionProperties : nullptr
                                                );
    return true;
}
inline bool zeEventPoolCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.numDevices, 
                                                apiCommand->args.phDevices ? apiCommand->captures.phDevices : nullptr, 
                                                apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeEventPoolDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolDestroy(
                                                apiCommand->args.hEventPool
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hEventPool;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeEventCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventCreate(
                                                apiCommand->args.hEventPool, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phEvent ? &apiCommand->captures.phEvent : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phEvent ? &apiCommand->captures.phEvent : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeEventDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventDestroy(
                                                apiCommand->args.hEvent
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hEvent;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeEventPoolGetIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolGetIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolGetIpcHandle(
                                                apiCommand->args.hEventPool, 
                                                apiCommand->args.phIpc ? &apiCommand->captures.phIpc : nullptr
                                                );
    return true;
}
inline bool zeEventPoolOpenIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolOpenIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolOpenIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hIpc, 
                                                apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phEventPool ? &apiCommand->captures.phEventPool : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeEventPoolCloseIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventPoolCloseIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCloseIpcHandle(
                                                apiCommand->args.hEventPool
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hEventPool;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeCommandListAppendBarrierHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendBarrier");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendBarrier(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendSignalEventHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendSignalEvent");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendSignalEvent(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hEvent
                                                );
    return true;
}
inline bool zeCommandListAppendWaitOnEventsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendWaitOnEvents");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendWaitOnEvents(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.numEvents, 
                                                apiCommand->args.phEvents ? apiCommand->captures.phEvents : nullptr
                                                );
    return true;
}
inline bool zeEventHostSignalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventHostSignal");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSignalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSignal(
                                                apiCommand->args.hEvent
                                                );
    return true;
}
inline bool zeEventHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventHostSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSynchronize(
                                                apiCommand->args.hEvent, 
                                                apiCommand->args.timeout
                                                );
    return true;
}
inline bool zeEventQueryStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventQueryStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryStatus(
                                                apiCommand->args.hEvent
                                                );
    return true;
}
inline bool zeCommandListAppendEventResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendEventReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendEventReset(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hEvent
                                                );
    return true;
}
inline bool zeEventHostResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventHostReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostReset(
                                                apiCommand->args.hEvent
                                                );
    return true;
}
inline bool zeEventQueryKernelTimestampHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventQueryKernelTimestamp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryKernelTimestamp(
                                                apiCommand->args.hEvent, 
                                                apiCommand->args.dstptr ? &apiCommand->captures.dstptr : nullptr
                                                );
    return true;
}
inline bool zeFenceCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceCreate(
                                                apiCommand->args.hCommandQueue, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phFence ? &apiCommand->captures.phFence : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phFence ? &apiCommand->captures.phFence : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeFenceDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceDestroy(
                                                apiCommand->args.hFence
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hFence;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeFenceHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceHostSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceHostSynchronize(
                                                apiCommand->args.hFence, 
                                                apiCommand->args.timeout
                                                );
    return true;
}
inline bool zeFenceQueryStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceQueryStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceQueryStatus(
                                                apiCommand->args.hFence
                                                );
    return true;
}
inline bool zeFenceResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceReset");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceResetRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceReset(
                                                apiCommand->args.hFence
                                                );
    return true;
}
inline bool zeKernelSetGlobalOffsetExpHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetGlobalOffsetExp");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGlobalOffsetExp(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.offsetX, 
                                                apiCommand->args.offsetY, 
                                                apiCommand->args.offsetZ
                                                );
    return true;
}
inline bool zeImageGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeImageGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageGetProperties(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.pImageProperties ? &apiCommand->captures.pImageProperties : nullptr
                                                );
    return true;
}
inline bool zeImageCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeImageCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeImageCreateRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phImage ? &apiCommand->captures.phImage : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phImage ? &apiCommand->captures.phImage : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeImageDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeImageDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeImageDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageDestroy(
                                                apiCommand->args.hImage
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hImage;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
bool zeMemAllocSharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeMemAllocDeviceHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemAllocDevice");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocDevice(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.device_desc ? &apiCommand->captures.device_desc : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.alignment, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
bool zeMemAllocHostHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool zeMemFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeMemGetAllocPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemGetAllocProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAllocProperties(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pMemAllocProperties ? &apiCommand->captures.pMemAllocProperties : nullptr, 
                                                apiCommand->args.phDevice ? &apiCommand->captures.phDevice : nullptr
                                                );
    return true;
}
inline bool zeMemGetAddressRangeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemGetAddressRange");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAddressRange(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pBase ? &apiCommand->captures.pBase : nullptr, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr
                                                );
    return true;
}
inline bool zeMemGetIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemGetIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.pIpcHandle ? &apiCommand->captures.pIpcHandle : nullptr
                                                );
    return true;
}
inline bool zeMemOpenIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemOpenIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemOpenIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.handle, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
inline bool zeMemCloseIpcHandleHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemCloseIpcHandle");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemCloseIpcHandle(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr
                                                );
    return true;
}
inline bool zexMemGetIpcHandlesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexMemGetIpcHandles");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemGetIpcHandles(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.numIpcHandles ? &apiCommand->captures.numIpcHandles : nullptr, 
                                                apiCommand->args.pIpcHandles ? apiCommand->captures.pIpcHandles : nullptr
                                                );
    return true;
}
inline bool zexMemOpenIpcHandlesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zexMemOpenIpcHandles");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemOpenIpcHandles(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.numIpcHandles, 
                                                apiCommand->args.pIpcHandles ? apiCommand->captures.pIpcHandles : nullptr, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
inline bool zeModuleCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleCreateRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleCreate(
                                                apiCommand->args.hContext, 
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phModule ? &apiCommand->captures.phModule : nullptr, 
                                                apiCommand->args.phBuildLog ? &apiCommand->captures.phBuildLog : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phModule ? &apiCommand->captures.phModule : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    {
        const auto& resource = apiCommand->args.phBuildLog ? &apiCommand->captures.phBuildLog : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeModuleDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDestroy(
                                                apiCommand->args.hModule
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hModule;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeModuleDynamicLinkHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleDynamicLink");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDynamicLink(
                                                apiCommand->args.numModules, 
                                                apiCommand->args.phModules ? apiCommand->captures.phModules : nullptr, 
                                                apiCommand->args.phLinkLog ? &apiCommand->captures.phLinkLog : nullptr
                                                );
    {
        const auto& resource = apiCommand->args.phLinkLog ? &apiCommand->captures.phLinkLog : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeModuleBuildLogDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleBuildLogDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogDestroy(
                                                apiCommand->args.hModuleBuildLog
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hModuleBuildLog;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeModuleBuildLogGetStringHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleBuildLogGetString");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogGetString(
                                                apiCommand->args.hModuleBuildLog, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pBuildLog ? apiCommand->captures.pBuildLog : nullptr
                                                );
    return true;
}
inline bool zeModuleGetNativeBinaryHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetNativeBinary");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetNativeBinary(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pModuleNativeBinary ? apiCommand->captures.pModuleNativeBinary : nullptr
                                                );
    return true;
}
inline bool zeModuleGetGlobalPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetGlobalPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetGlobalPointer(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pGlobalName ? apiCommand->captures.pGlobalName : nullptr, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pptr ? &apiCommand->captures.pptr : nullptr
                                                );
    return true;
}
bool zeModuleGetKernelNamesRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool zeModuleGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetProperties(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pModuleProperties ? &apiCommand->captures.pModuleProperties : nullptr
                                                );
    return true;
}
inline bool zeKernelCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelCreateRpcM*>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelCreate(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.desc ? &apiCommand->captures.desc : nullptr, 
                                                apiCommand->args.phKernel ? &apiCommand->captures.phKernel : nullptr
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.phKernel ? &apiCommand->captures.phKernel : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}
inline bool zeKernelDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelDestroyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelDestroy(
                                                apiCommand->args.hKernel
                                                );
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = apiCommand->args.hKernel;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}
inline bool zeModuleGetFunctionPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetFunctionPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetFunctionPointer(
                                                apiCommand->args.hModule, 
                                                apiCommand->args.pFunctionName ? apiCommand->captures.pFunctionName : nullptr, 
                                                apiCommand->args.pfnFunction ? &apiCommand->captures.pfnFunction : nullptr
                                                );
    return true;
}
inline bool zeKernelSetGroupSizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetGroupSize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGroupSize(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.groupSizeX, 
                                                apiCommand->args.groupSizeY, 
                                                apiCommand->args.groupSizeZ
                                                );
    return true;
}
inline bool zeKernelSuggestGroupSizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSuggestGroupSize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestGroupSize(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.globalSizeX, 
                                                apiCommand->args.globalSizeY, 
                                                apiCommand->args.globalSizeZ, 
                                                apiCommand->args.groupSizeX ? &apiCommand->captures.groupSizeX : nullptr, 
                                                apiCommand->args.groupSizeY ? &apiCommand->captures.groupSizeY : nullptr, 
                                                apiCommand->args.groupSizeZ ? &apiCommand->captures.groupSizeZ : nullptr
                                                );
    return true;
}
inline bool zeKernelSuggestMaxCooperativeGroupCountHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSuggestMaxCooperativeGroupCount");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestMaxCooperativeGroupCount(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.totalGroupCount ? &apiCommand->captures.totalGroupCount : nullptr
                                                );
    return true;
}
inline bool zeKernelSetArgumentValueHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetArgumentValue");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetArgumentValue(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.argIndex, 
                                                apiCommand->args.argSize, 
                                                apiCommand->args.pArgValue ? apiCommand->captures.pArgValue : nullptr
                                                );
    return true;
}
inline bool zeKernelSetIndirectAccessHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetIndirectAccess");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetIndirectAccess(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.flags
                                                );
    return true;
}
inline bool zeKernelGetIndirectAccessHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetIndirectAccess");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetIndirectAccess(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pFlags ? &apiCommand->captures.pFlags : nullptr
                                                );
    return true;
}
inline bool zeKernelSetCacheConfigHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelSetCacheConfig");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetCacheConfig(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.flags
                                                );
    return true;
}
inline bool zeKernelGetPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetProperties(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pKernelProperties ? &apiCommand->captures.pKernelProperties : nullptr
                                                );
    return true;
}
inline bool zeKernelGetNameHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetName");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetNameRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetName(
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr, 
                                                apiCommand->args.pName ? apiCommand->captures.pName : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendLaunchKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendLaunchKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernel(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pLaunchFuncArgs ? &apiCommand->captures.pLaunchFuncArgs : nullptr, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeCommandListAppendLaunchKernelIndirectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendLaunchKernelIndirect");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernelIndirect(
                                                apiCommand->args.hCommandList, 
                                                apiCommand->args.hKernel, 
                                                apiCommand->args.pLaunchArgumentsBuffer, 
                                                apiCommand->args.hSignalEvent, 
                                                apiCommand->args.numWaitEvents, 
                                                apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr
                                                );
    return true;
}
inline bool zeDevicePciGetPropertiesExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDevicePciGetPropertiesExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDevicePciGetPropertiesExt(
                                                apiCommand->args.hDevice, 
                                                apiCommand->args.pPciProperties ? &apiCommand->captures.pPciProperties : nullptr
                                                );
    return true;
}

inline void registerGeneratedHandlersLevelZero(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
    using namespace Cal::Rpc::LevelZero;
    outHandlers.resize(ZeDevicePciGetPropertiesExtRpcM::messageSubtype + 1);
    outHandlers[ZeInitRpcM::messageSubtype] = zeInitHandler;
    outHandlers[ZeCommandListCreateRpcM::messageSubtype] = zeCommandListCreateHandler;
    outHandlers[ZeCommandListCreateImmediateRpcM::messageSubtype] = zeCommandListCreateImmediateHandler;
    outHandlers[ZeCommandListDestroyRpcM::messageSubtype] = zeCommandListDestroyHandler;
    outHandlers[ZeCommandListCloseRpcM::messageSubtype] = zeCommandListCloseHandler;
    outHandlers[ZeCommandListResetRpcM::messageSubtype] = zeCommandListResetHandler;
    outHandlers[ZeCommandQueueCreateRpcM::messageSubtype] = zeCommandQueueCreateHandler;
    outHandlers[ZeCommandQueueDestroyRpcM::messageSubtype] = zeCommandQueueDestroyHandler;
    outHandlers[ZeCommandQueueExecuteCommandListsRpcM::messageSubtype] = zeCommandQueueExecuteCommandListsHandler;
    outHandlers[ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::messageSubtype] = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelperHandler;
    outHandlers[ZeCommandQueueSynchronizeRpcM::messageSubtype] = zeCommandQueueSynchronizeHandler;
    outHandlers[ZeContextCreateRpcM::messageSubtype] = zeContextCreateHandler;
    outHandlers[ZeContextCreateExRpcM::messageSubtype] = zeContextCreateExHandler;
    outHandlers[ZeContextDestroyRpcM::messageSubtype] = zeContextDestroyHandler;
    outHandlers[ZeContextGetStatusRpcM::messageSubtype] = zeContextGetStatusHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperUsm2UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperUsm2MallocHandler;
    outHandlers[ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM::messageSubtype] = zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperUsm2UsmHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperUsm2MallocHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperMalloc2UsmHandler;
    outHandlers[ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::messageSubtype] = zeCommandListAppendMemoryFillRpcHelperMalloc2MallocHandler;
    outHandlers[ZeDeviceGetRpcM::messageSubtype] = zeDeviceGetHandler;
    outHandlers[ZeDeviceGetSubDevicesRpcM::messageSubtype] = zeDeviceGetSubDevicesHandler;
    outHandlers[ZeDeviceGetPropertiesRpcM::messageSubtype] = zeDeviceGetPropertiesHandler;
    outHandlers[ZeDeviceGetComputePropertiesRpcM::messageSubtype] = zeDeviceGetComputePropertiesHandler;
    outHandlers[ZeDeviceGetModulePropertiesRpcM::messageSubtype] = zeDeviceGetModulePropertiesHandler;
    outHandlers[ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype] = zeDeviceGetCommandQueueGroupPropertiesHandler;
    outHandlers[ZeDeviceGetMemoryPropertiesRpcM::messageSubtype] = zeDeviceGetMemoryPropertiesHandler;
    outHandlers[ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype] = zeDeviceGetMemoryAccessPropertiesHandler;
    outHandlers[ZeDeviceGetCachePropertiesRpcM::messageSubtype] = zeDeviceGetCachePropertiesHandler;
    outHandlers[ZeDeviceGetImagePropertiesRpcM::messageSubtype] = zeDeviceGetImagePropertiesHandler;
    outHandlers[ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype] = zeDeviceGetExternalMemoryPropertiesHandler;
    outHandlers[ZeDeviceGetP2PPropertiesRpcM::messageSubtype] = zeDeviceGetP2PPropertiesHandler;
    outHandlers[ZeDeviceCanAccessPeerRpcM::messageSubtype] = zeDeviceCanAccessPeerHandler;
    outHandlers[ZeDeviceGetStatusRpcM::messageSubtype] = zeDeviceGetStatusHandler;
    outHandlers[ZeDeviceGetGlobalTimestampsRpcM::messageSubtype] = zeDeviceGetGlobalTimestampsHandler;
    outHandlers[ZeDriverGetRpcM::messageSubtype] = zeDriverGetHandler;
    outHandlers[ZeDriverGetApiVersionRpcM::messageSubtype] = zeDriverGetApiVersionHandler;
    outHandlers[ZeDriverGetPropertiesRpcM::messageSubtype] = zeDriverGetPropertiesHandler;
    outHandlers[ZeDriverGetIpcPropertiesRpcM::messageSubtype] = zeDriverGetIpcPropertiesHandler;
    outHandlers[ZeDriverGetExtensionPropertiesRpcM::messageSubtype] = zeDriverGetExtensionPropertiesHandler;
    outHandlers[ZeEventPoolCreateRpcM::messageSubtype] = zeEventPoolCreateHandler;
    outHandlers[ZeEventPoolDestroyRpcM::messageSubtype] = zeEventPoolDestroyHandler;
    outHandlers[ZeEventCreateRpcM::messageSubtype] = zeEventCreateHandler;
    outHandlers[ZeEventDestroyRpcM::messageSubtype] = zeEventDestroyHandler;
    outHandlers[ZeEventPoolGetIpcHandleRpcM::messageSubtype] = zeEventPoolGetIpcHandleHandler;
    outHandlers[ZeEventPoolOpenIpcHandleRpcM::messageSubtype] = zeEventPoolOpenIpcHandleHandler;
    outHandlers[ZeEventPoolCloseIpcHandleRpcM::messageSubtype] = zeEventPoolCloseIpcHandleHandler;
    outHandlers[ZeCommandListAppendBarrierRpcM::messageSubtype] = zeCommandListAppendBarrierHandler;
    outHandlers[ZeCommandListAppendSignalEventRpcM::messageSubtype] = zeCommandListAppendSignalEventHandler;
    outHandlers[ZeCommandListAppendWaitOnEventsRpcM::messageSubtype] = zeCommandListAppendWaitOnEventsHandler;
    outHandlers[ZeEventHostSignalRpcM::messageSubtype] = zeEventHostSignalHandler;
    outHandlers[ZeEventHostSynchronizeRpcM::messageSubtype] = zeEventHostSynchronizeHandler;
    outHandlers[ZeEventQueryStatusRpcM::messageSubtype] = zeEventQueryStatusHandler;
    outHandlers[ZeCommandListAppendEventResetRpcM::messageSubtype] = zeCommandListAppendEventResetHandler;
    outHandlers[ZeEventHostResetRpcM::messageSubtype] = zeEventHostResetHandler;
    outHandlers[ZeEventQueryKernelTimestampRpcM::messageSubtype] = zeEventQueryKernelTimestampHandler;
    outHandlers[ZeFenceCreateRpcM::messageSubtype] = zeFenceCreateHandler;
    outHandlers[ZeFenceDestroyRpcM::messageSubtype] = zeFenceDestroyHandler;
    outHandlers[ZeFenceHostSynchronizeRpcM::messageSubtype] = zeFenceHostSynchronizeHandler;
    outHandlers[ZeFenceQueryStatusRpcM::messageSubtype] = zeFenceQueryStatusHandler;
    outHandlers[ZeFenceResetRpcM::messageSubtype] = zeFenceResetHandler;
    outHandlers[ZeKernelSetGlobalOffsetExpRpcM::messageSubtype] = zeKernelSetGlobalOffsetExpHandler;
    outHandlers[ZeImageGetPropertiesRpcM::messageSubtype] = zeImageGetPropertiesHandler;
    outHandlers[ZeImageCreateRpcM::messageSubtype] = zeImageCreateHandler;
    outHandlers[ZeImageDestroyRpcM::messageSubtype] = zeImageDestroyHandler;
    outHandlers[ZeMemAllocSharedRpcM::messageSubtype] = zeMemAllocSharedHandler;
    outHandlers[ZeMemAllocDeviceRpcM::messageSubtype] = zeMemAllocDeviceHandler;
    outHandlers[ZeMemAllocHostRpcM::messageSubtype] = zeMemAllocHostHandler;
    outHandlers[ZeMemFreeRpcM::messageSubtype] = zeMemFreeHandler;
    outHandlers[ZeMemGetAllocPropertiesRpcM::messageSubtype] = zeMemGetAllocPropertiesHandler;
    outHandlers[ZeMemGetAddressRangeRpcM::messageSubtype] = zeMemGetAddressRangeHandler;
    outHandlers[ZeMemGetIpcHandleRpcM::messageSubtype] = zeMemGetIpcHandleHandler;
    outHandlers[ZeMemOpenIpcHandleRpcM::messageSubtype] = zeMemOpenIpcHandleHandler;
    outHandlers[ZeMemCloseIpcHandleRpcM::messageSubtype] = zeMemCloseIpcHandleHandler;
    outHandlers[ZexMemGetIpcHandlesRpcM::messageSubtype] = zexMemGetIpcHandlesHandler;
    outHandlers[ZexMemOpenIpcHandlesRpcM::messageSubtype] = zexMemOpenIpcHandlesHandler;
    outHandlers[ZeModuleCreateRpcM::messageSubtype] = zeModuleCreateHandler;
    outHandlers[ZeModuleDestroyRpcM::messageSubtype] = zeModuleDestroyHandler;
    outHandlers[ZeModuleDynamicLinkRpcM::messageSubtype] = zeModuleDynamicLinkHandler;
    outHandlers[ZeModuleBuildLogDestroyRpcM::messageSubtype] = zeModuleBuildLogDestroyHandler;
    outHandlers[ZeModuleBuildLogGetStringRpcM::messageSubtype] = zeModuleBuildLogGetStringHandler;
    outHandlers[ZeModuleGetNativeBinaryRpcM::messageSubtype] = zeModuleGetNativeBinaryHandler;
    outHandlers[ZeModuleGetGlobalPointerRpcM::messageSubtype] = zeModuleGetGlobalPointerHandler;
    outHandlers[ZeModuleGetKernelNamesRpcHelperRpcM::messageSubtype] = zeModuleGetKernelNamesRpcHelperHandler;
    outHandlers[ZeModuleGetPropertiesRpcM::messageSubtype] = zeModuleGetPropertiesHandler;
    outHandlers[ZeKernelCreateRpcM::messageSubtype] = zeKernelCreateHandler;
    outHandlers[ZeKernelDestroyRpcM::messageSubtype] = zeKernelDestroyHandler;
    outHandlers[ZeModuleGetFunctionPointerRpcM::messageSubtype] = zeModuleGetFunctionPointerHandler;
    outHandlers[ZeKernelSetGroupSizeRpcM::messageSubtype] = zeKernelSetGroupSizeHandler;
    outHandlers[ZeKernelSuggestGroupSizeRpcM::messageSubtype] = zeKernelSuggestGroupSizeHandler;
    outHandlers[ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype] = zeKernelSuggestMaxCooperativeGroupCountHandler;
    outHandlers[ZeKernelSetArgumentValueRpcM::messageSubtype] = zeKernelSetArgumentValueHandler;
    outHandlers[ZeKernelSetIndirectAccessRpcM::messageSubtype] = zeKernelSetIndirectAccessHandler;
    outHandlers[ZeKernelGetIndirectAccessRpcM::messageSubtype] = zeKernelGetIndirectAccessHandler;
    outHandlers[ZeKernelSetCacheConfigRpcM::messageSubtype] = zeKernelSetCacheConfigHandler;
    outHandlers[ZeKernelGetPropertiesRpcM::messageSubtype] = zeKernelGetPropertiesHandler;
    outHandlers[ZeKernelGetNameRpcM::messageSubtype] = zeKernelGetNameHandler;
    outHandlers[ZeCommandListAppendLaunchKernelRpcM::messageSubtype] = zeCommandListAppendLaunchKernelHandler;
    outHandlers[ZeCommandListAppendLaunchKernelIndirectRpcM::messageSubtype] = zeCommandListAppendLaunchKernelIndirectHandler;
    outHandlers[ZeDevicePciGetPropertiesExtRpcM::messageSubtype] = zeDevicePciGetPropertiesExtHandler;
}

inline void callDirectly(Cal::Rpc::LevelZero::ZeInitRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeInit(
                                                apiCommand.args.flags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListCreateImmediate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.altdesc, 
                                                apiCommand.args.phCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListDestroy(
                                                apiCommand.args.hCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListCloseRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListClose(
                                                apiCommand.args.hCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListReset(
                                                apiCommand.args.hCommandList
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phCommandQueue
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueDestroy(
                                                apiCommand.args.hCommandQueue
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueExecuteCommandLists(
                                                apiCommand.args.hCommandQueue, 
                                                apiCommand.args.numCommandLists, 
                                                apiCommand.args.phCommandLists, 
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueSynchronize(
                                                apiCommand.args.hCommandQueue, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreate(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextCreateExRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextCreateEx(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.numDevices, 
                                                apiCommand.args.phDevices, 
                                                apiCommand.args.phContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextDestroy(
                                                apiCommand.args.hContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeContextGetStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextGetStatus(
                                                apiCommand.args.hContext
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.dstptr, 
                                                apiCommand.args.srcptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.pattern_size, 
                                                apiCommand.args.size, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phDevices
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetSubDevices(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phSubdevices
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pDeviceProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetComputeProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pComputeProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetModuleProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pModuleProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCommandQueueGroupProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pCommandQueueGroupProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pMemProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetMemoryAccessProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pMemAccessProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetCacheProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pCacheProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetImageProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pImageProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetExternalMemoryProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pExternalMemoryProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetP2PProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.hPeerDevice, 
                                                apiCommand.args.pP2PProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceCanAccessPeer(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.hPeerDevice, 
                                                apiCommand.args.value
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetStatus(
                                                apiCommand.args.hDevice
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetGlobalTimestamps(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.hostTimestamp, 
                                                apiCommand.args.deviceTimestamp
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGet(
                                                apiCommand.args.pCount, 
                                                apiCommand.args.phDrivers
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetApiVersion(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.version
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetProperties(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pDriverProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetIpcProperties(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pIpcProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetExtensionProperties(
                                                apiCommand.args.hDriver, 
                                                apiCommand.args.pCount, 
                                                apiCommand.args.pExtensionProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.numDevices, 
                                                apiCommand.args.phDevices, 
                                                apiCommand.args.phEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolDestroy(
                                                apiCommand.args.hEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventCreate(
                                                apiCommand.args.hEventPool, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventDestroy(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolGetIpcHandle(
                                                apiCommand.args.hEventPool, 
                                                apiCommand.args.phIpc
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolOpenIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hIpc, 
                                                apiCommand.args.phEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventPoolCloseIpcHandle(
                                                apiCommand.args.hEventPool
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendBarrier(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendSignalEvent(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendWaitOnEvents(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.numEvents, 
                                                apiCommand.args.phEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventHostSignalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSignal(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSynchronize(
                                                apiCommand.args.hEvent, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryStatus(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendEventReset(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventHostResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostReset(
                                                apiCommand.args.hEvent
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryKernelTimestamp(
                                                apiCommand.args.hEvent, 
                                                apiCommand.args.dstptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceCreate(
                                                apiCommand.args.hCommandQueue, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceDestroy(
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceHostSynchronize(
                                                apiCommand.args.hFence, 
                                                apiCommand.args.timeout
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceQueryStatus(
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeFenceResetRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceReset(
                                                apiCommand.args.hFence
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGlobalOffsetExp(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.offsetX, 
                                                apiCommand.args.offsetY, 
                                                apiCommand.args.offsetZ
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageGetProperties(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.pImageProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeImageCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phImage
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeImageDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeImageDestroy(
                                                apiCommand.args.hImage
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocShared(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.device_desc, 
                                                apiCommand.args.host_desc, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocDevice(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.device_desc, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemAllocHostRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocHost(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.host_desc, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemFreeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemFree(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAllocProperties(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pMemAllocProperties, 
                                                apiCommand.args.phDevice
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetAddressRange(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pBase, 
                                                apiCommand.args.pSize
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemGetIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.pIpcHandle
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemOpenIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.handle, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemCloseIpcHandle(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemGetIpcHandles(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.numIpcHandles, 
                                                apiCommand.args.pIpcHandles
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Extensions::zexMemOpenIpcHandles(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.numIpcHandles, 
                                                apiCommand.args.pIpcHandles, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleCreate(
                                                apiCommand.args.hContext, 
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phModule, 
                                                apiCommand.args.phBuildLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDestroy(
                                                apiCommand.args.hModule
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleDynamicLink(
                                                apiCommand.args.numModules, 
                                                apiCommand.args.phModules, 
                                                apiCommand.args.phLinkLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogDestroy(
                                                apiCommand.args.hModuleBuildLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogGetString(
                                                apiCommand.args.hModuleBuildLog, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pBuildLog
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetNativeBinary(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pModuleNativeBinary
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetGlobalPointer(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pGlobalName, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pptr
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetProperties(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pModuleProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelCreateRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelCreate(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.desc, 
                                                apiCommand.args.phKernel
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelDestroyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelDestroy(
                                                apiCommand.args.hKernel
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetFunctionPointer(
                                                apiCommand.args.hModule, 
                                                apiCommand.args.pFunctionName, 
                                                apiCommand.args.pfnFunction
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetGroupSize(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.groupSizeX, 
                                                apiCommand.args.groupSizeY, 
                                                apiCommand.args.groupSizeZ
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestGroupSize(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.globalSizeX, 
                                                apiCommand.args.globalSizeY, 
                                                apiCommand.args.globalSizeZ, 
                                                apiCommand.args.groupSizeX, 
                                                apiCommand.args.groupSizeY, 
                                                apiCommand.args.groupSizeZ
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSuggestMaxCooperativeGroupCount(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.totalGroupCount
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetArgumentValue(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.argIndex, 
                                                apiCommand.args.argSize, 
                                                apiCommand.args.pArgValue
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetIndirectAccess(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.flags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetIndirectAccess(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pFlags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelSetCacheConfig(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.flags
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetProperties(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pKernelProperties
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeKernelGetNameRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetName(
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pSize, 
                                                apiCommand.args.pName
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernel(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pLaunchFuncArgs, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendLaunchKernelIndirect(
                                                apiCommand.args.hCommandList, 
                                                apiCommand.args.hKernel, 
                                                apiCommand.args.pLaunchArgumentsBuffer, 
                                                apiCommand.args.hSignalEvent, 
                                                apiCommand.args.numWaitEvents, 
                                                apiCommand.args.phWaitEvents
                                                );
}
inline void callDirectly(Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDevicePciGetPropertiesExt(
                                                apiCommand.args.hDevice, 
                                                apiCommand.args.pPciProperties
                                                );
}

inline bool callDirectly(Cal::Rpc::RpcMessageHeader *command) {
    if(nullptr == command){
        log<Verbosity::debug>("Tried to call directly with empty command message header");
        return false;
    }
    if(command->type != Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero){
        log<Verbosity::debug>("Tried to call directly %d message type as LevelZero", command->type);
        return false;
    }
    switch(command->subtype){
        default:
            log<Verbosity::debug>("Tried to call directly unknown message subtype %d", command->subtype);
            return false;
        case Cal::Rpc::LevelZero::ZeInitRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeInitRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListCloseRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListCloseRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextCreateExRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextCreateExRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeContextGetStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeContextGetStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventHostSignalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSignalRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventHostResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeFenceResetRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceResetRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeImageCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeImageCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeImageDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeImageDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemAllocHostRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocHostRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemFreeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemFreeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelCreateRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelCreateRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelDestroyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelDestroyRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeKernelGetNameRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetNameRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM*>(command)); break;
        case Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM*>(command)); break;
    }
    return true;
}

} // namespae LevelZero
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
