/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "service/service.h"

#include "generated_rpc_messages_level_zero.h"
#include "generated_rpc_messages_ocl.h"
#include "generated_service_level_zero.h"
#include "generated_service_ocl.h"

#include <cstddef>
#include <dlfcn.h>
#include <fstream>
#include <functional>
#include <regex>
#include <string>
#include <wait.h>

using namespace std::string_literals;

namespace Cal {

namespace Service {

namespace Apis {

static const char *intelGpuPlatformName = "Intel.*Graphics";

namespace Ocl {
cl_platform_id globalOclPlatform = {};

bool OclSharedObjects::init() {
    if (false == Cal::Service::Apis::Ocl::Standard::loadOclLibrary(std::nullopt)) {
        log<Verbosity::info>("Could not load OpenCL ICD loader library (libOpenCL.so) - OpenCL API will not be available");
        return false;
    }

    intelGpuPlatform = this->getPlatformByName(intelGpuPlatformName);
    if (nullptr == intelGpuPlatform) {
        return false;
    }
    globalOclPlatform = intelGpuPlatform;
    return true;
}

cl_platform_id OclSharedObjects::getPlatformByName(const char *regex) {
    cl_uint numPlatforms = {};

    auto err = Cal::Service::Apis::Ocl::Standard::clGetPlatformIDs(0, nullptr, &numPlatforms);
    if (err) {
        log<Verbosity::error>("clGetPlatformIDS failed with %d", err);
        return nullptr;
    }

    if (0 == numPlatforms) {
        log<Verbosity::info>("clGetPlatformIDS returned 0 platforms");
        return nullptr;
    }

    std::vector<cl_platform_id> platforms(4, 0);
    platforms.resize(numPlatforms);
    err = Cal::Service::Apis::Ocl::Standard::clGetPlatformIDs(numPlatforms, platforms.data(), nullptr);
    if (err) {
        log<Verbosity::error>("clGetPlatformIDS failed with %d", err);
        return nullptr;
    }

    cl_platform_id foundPlatformId = nullptr;
    std::vector<char> platformName(256, 0);
    std::regex matcher{regex};
    for (auto p : platforms) {
        size_t nameLen = 0U;
        if (CL_SUCCESS != (err = Cal::Service::Apis::Ocl::Standard::clGetPlatformInfo(p, CL_PLATFORM_NAME, 0, nullptr, &nameLen))) {
            log<Verbosity::error>("clGetPlatformInfo(..., CL_PLATFORM_NAME, ...) failed with %d", err);
        }
        platformName.resize(nameLen);
        if (CL_SUCCESS != (err = Cal::Service::Apis::Ocl::Standard::clGetPlatformInfo(p, CL_PLATFORM_NAME, platformName.size(), platformName.data(), nullptr))) {
            log<Verbosity::error>("clGetPlatformInfo(..., CL_PLATFORM_NAME, ...) failed with %d", err);
            continue;
        }

        if (std::regex_search(platformName.data(), matcher)) {
            foundPlatformId = p;
            break;
        }
    }

    if (nullptr == foundPlatformId) {
        platformName.resize(platformName.capacity());
        std::string platformNamesFound = "";
        for (auto p : platforms) {
            if (CL_SUCCESS != (err = Cal::Service::Apis::Ocl::Standard::clGetPlatformInfo(p, CL_PLATFORM_NAME, platformName.size(), platformName.data(), nullptr))) {
                log<Verbosity::error>("clGetPlatformInfo(..., CL_PLATFORM_NAME, ...) failed with %d", err);
                continue;
            }
            platformNamesFound += std::string("[") + platformName.data() + "], ";
        }
        log<Verbosity::debug>("Could not find requested platform, found (%d platforms) : %s was looking for [%s]",
                              static_cast<uint32_t>(platforms.size()), platformNamesFound.data(), regex);
        return nullptr;
    }

    return foundPlatformId;
}

bool clGetPlatformIDsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetPlatformIDsRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetPlatformIDs(apiCommand->args.num_entries,
                                                                                   apiCommand->args.platforms ? apiCommand->captures.platforms : nullptr,
                                                                                   apiCommand->args.num_platforms ? &apiCommand->captures.num_platforms : nullptr);
    auto platformId = service.getOclSharedObjects().getIntelGpuPlatform();
    if (nullptr == platformId) {
        if (apiCommand->args.num_platforms) {
            apiCommand->captures.num_platforms = 0U;
            apiCommand->captures.ret = CL_SUCCESS;
        }
        return true;
    }
    if (apiCommand->args.num_platforms) {
        apiCommand->captures.num_platforms = 1U;
    }
    if (apiCommand->args.platforms && (apiCommand->args.num_entries >= 1)) {
        apiCommand->captures.platforms[0] = platformId;
    }
    apiCommand->captures.ret = CL_SUCCESS;
    return true;
};

bool clGetProgramInfoGetBinariesRpcHelperHandler(Cal::Service::Provider &service, Cal::Rpc::ChannelServer &channel, Cal::Service::ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetProgramInfoGetBinariesRpcHelperRpcM *>(command);

    const auto binariesCount = apiCommand->args.binaries_count;
    const auto binariesLengths = apiCommand->captures.getBinaries_lengths();

    auto concatenatedBinaries = apiCommand->captures.getConcatenated_binaries();
    auto offset = 0u;

    std::vector<unsigned char *> binaries(apiCommand->args.binaries_count, nullptr);
    for (auto i = 0u; i < binariesCount; ++i) {
        if (binariesLengths[i] == 0) {
            continue;
        }

        binaries[i] = concatenatedBinaries + offset;
        offset += binariesLengths[i];
    }

    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetProgramInfo(
        apiCommand->args.program,
        CL_PROGRAM_BINARIES,
        binaries.size() * sizeof(unsigned char *),
        binaries.data(),
        apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr);
    return true;
}

void *getExtensionFuncAddress(const char *funcname) {
    return Cal::Service::Apis::Ocl::Standard::clGetExtensionFunctionAddressForPlatform(globalOclPlatform, funcname);
}

void gpuDestructorUsm(void *ctx, void *ptr) {
    if (CL_SUCCESS != Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(static_cast<cl_context>(ctx), ptr)) {
        log<Verbosity::error>("clMemFreeINTEL failed for %p", ptr);
    }
}

void gpuDestructorClMem(void *ctx, void *ptr) {
    if (CL_SUCCESS != Cal::Service::Apis::Ocl::Standard::clReleaseMemObject(static_cast<cl_mem>(ctx))) {
        log<Verbosity::error>("clReleaseMemObject failed for %p", ctx);
    }
}

bool clHostMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM *>(command);
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for clHostMemAllocINTEL");
        return false;
    }
    std::vector<cl_mem_properties_intel> properties;
#define CL_MEM_ALLOC_USE_HOST_PTR_INTEL 0x1000F
    cl_mem_properties_intel propertiesToInject[] = {CL_MEM_ALLOC_USE_HOST_PTR_INTEL, 0};
    auto numPropertiesToInject = sizeof(propertiesToInject) / sizeof(propertiesToInject[0]);
    properties.reserve(numPropertiesToInject + apiCommand->captures.countProperties + (apiCommand->args.properties ? 0 : 1));
    properties.assign(propertiesToInject, propertiesToInject + numPropertiesToInject);
    if (apiCommand->args.properties) {
        properties.insert(properties.end(), apiCommand->captures.properties, apiCommand->captures.properties + apiCommand->captures.countProperties - 1);
    }

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    properties.push_back(0);
    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        auto shmem = heap.allocate(alignedSize, Cal::Utils::pageSize64KB);
        if (false == shmem.isValid()) {
            continue;
        }
        void *cpuAddress = shmem.getSubAllocationPtr();
        properties[1] = reinterpret_cast<uintptr_t>(cpuAddress);
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clHostMemAllocINTEL(apiCommand->args.context,
                                                                                            properties.data(),
                                                                                            apiCommand->args.size,
                                                                                            apiCommand->args.alignment,
                                                                                            apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::error>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU",
                                  apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end);
            heap.free(shmem);
            continue; // try different heap
        }
        if (apiCommand->captures.ret == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU",
                                  apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->args.context, shmem, ApiType::OpenCL, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.getSourceAllocation()->getShmemId();
            apiCommand->implicitArgs.offset_within_resource = shmem.getSubAllocationOffset();
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in clHostMemAllocINTEL - would break USM agreements on client side (expected!=got , %p != %p)",
                                  cpuAddress, apiCommand->captures.ret);
            Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->captures.ret);
            heap.free(shmem);
            apiCommand->captures.ret = nullptr;
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
            return true;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::error>("None of USM shared/host heaps could acommodate new USM host allocation for GPU");
        if (CL_SUCCESS == apiCommand->captures.errcode_ret) {
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
        }
    }

    return true;
}

bool clSharedMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSharedMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM *>(command);
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for clSharedMemAllocINTEL");
        return false;
    }
    std::vector<cl_mem_properties_intel> properties;
#define CL_MEM_ALLOC_USE_HOST_PTR_INTEL 0x1000F
    cl_mem_properties_intel propertiesToInject[] = {CL_MEM_ALLOC_USE_HOST_PTR_INTEL, 0};
    auto numPropertiesToInject = sizeof(propertiesToInject) / sizeof(propertiesToInject[0]);
    properties.reserve(numPropertiesToInject + apiCommand->captures.countProperties + (apiCommand->args.properties ? 0 : 1));
    properties.assign(propertiesToInject, propertiesToInject + numPropertiesToInject);
    if (apiCommand->args.properties) {
        properties.insert(properties.end(), apiCommand->captures.properties, apiCommand->captures.properties + apiCommand->captures.countProperties - 1);
    }

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    properties.push_back(0);
    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        auto shmem = heap.allocate(alignedSize, Cal::Utils::pageSize64KB);
        if (false == shmem.isValid()) {
            continue;
        }
        void *cpuAddress = shmem.getSubAllocationPtr();
        properties[1] = reinterpret_cast<uintptr_t>(cpuAddress);
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clSharedMemAllocINTEL(apiCommand->args.context,
                                                                                              apiCommand->args.device,
                                                                                              properties.data(),
                                                                                              apiCommand->args.size,
                                                                                              apiCommand->args.alignment,
                                                                                              apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end);
            heap.free(shmem);
            continue; // try different heap
        }
        if (apiCommand->captures.ret == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->args.context, shmem, ApiType::OpenCL, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.getSourceAllocation()->getShmemId();
            apiCommand->implicitArgs.offset_within_resource = shmem.getSubAllocationOffset();
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in clHostMemAllocINTEL - would break USM agreements on client side (expected!=got , %p != %p)",
                                  cpuAddress, apiCommand->captures.ret);
            Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->captures.ret);
            heap.free(shmem);
            apiCommand->captures.ret = nullptr;
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
            return true;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::error>("None of USM shared/host heaps could acommodate new USM host allocation for GPU");
        if (CL_SUCCESS == apiCommand->captures.errcode_ret) {
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
        }
    }

    return true;
}

bool clSVMAllocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSVMAlloc");
    log<Verbosity::performance>("WARNING : clSVMAlloc is implemented using clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSVMAllocRpcM *>(command);
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for clSVMAlloc");
        return false;
    }
#define CL_MEM_ALLOC_USE_HOST_PTR_INTEL 0x1000F
    cl_mem_properties_intel properties[] = {CL_MEM_ALLOC_USE_HOST_PTR_INTEL, 0, 0};

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        auto shmem = heap.allocate(alignedSize, Cal::Utils::pageSize64KB);
        if (false == shmem.isValid()) {
            continue;
        }
        void *cpuAddress = shmem.getSubAllocationPtr();
        properties[1] = reinterpret_cast<uintptr_t>(cpuAddress);
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clHostMemAllocINTEL(apiCommand->args.context,
                                                                                            properties,
                                                                                            apiCommand->args.size,
                                                                                            apiCommand->args.alignment,
                                                                                            nullptr);
        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end);
            heap.free(shmem);
            continue; // try different heap
        }
        if (apiCommand->captures.ret == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->args.context, shmem, ApiType::OpenCL, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.getSourceAllocation()->getShmemId();
            apiCommand->implicitArgs.offset_within_resource = shmem.getSubAllocationOffset();
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in clHostMemAllocINTEL - would break USM agreements on client side (expected!=got , %p != %p)",
                                  cpuAddress, apiCommand->captures.ret);
            Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->captures.ret);
            heap.free(shmem);
            apiCommand->captures.ret = nullptr;
            return true;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::error>("None of USM shared/host heaps could acommodate new SVM allocation for GPU");
    }

    return true;
}

bool clSVMFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSVMFree");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSVMFreeRpcM *>(command);
    auto ptr = apiCommand->args.ptr;
    Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(ptr, false);
    }
    return true;
}

bool clEnqueueSVMMapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMap");
    log<Verbosity::performance>("WARNING : clSVMAlloc is implemented using clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMapRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(apiCommand->args.command_queue,
                                                                                               apiCommand->args.num_events_in_wait_list,
                                                                                               apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr,
                                                                                               apiCommand->args.event ? &apiCommand->captures.event : nullptr);
    if ((CL_SUCCESS == apiCommand->captures.ret) && (CL_TRUE == apiCommand->args.blocking_map)) {
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clFinish(apiCommand->args.command_queue);
    }
    return true;
}

bool clEnqueueSVMUnmapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMUnmap");
    log<Verbosity::performance>("WARNING : clSVMAlloc is implemented using clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMUnmapRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(apiCommand->args.command_queue,
                                                                                               apiCommand->args.num_events_in_wait_list,
                                                                                               apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr,
                                                                                               apiCommand->args.event ? &apiCommand->captures.event : nullptr);
    return true;
}

bool clMemFreeINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clMemFreeINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClMemFreeINTELRpcM *>(command);
    auto ptr = apiCommand->args.ptr;
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context,
                                                                                   apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(ptr, false);
    }
    return true;
}

bool clMemBlockingFreeINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clMemBlockingFreeINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClMemBlockingFreeINTELRpcM *>(command);
    auto ptr = apiCommand->args.ptr;
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clMemBlockingFreeINTEL(apiCommand->args.context,
                                                                                           apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(ptr, false);
    }
    return true;
}

bool clReleaseMemObjectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseMemObjectHandler");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseMemObjectRpcM *>(command);
    cl_uint refCount = 0;
    Cal::Service::Apis::Ocl::Standard::clGetMemObjectInfo(apiCommand->args.memobj, CL_MEM_REFERENCE_COUNT, sizeof(refCount), &refCount, nullptr);
    void *hostPtr = nullptr;
    if (refCount == 1) {
        cl_mem parentClMem = {};
        Cal::Service::Apis::Ocl::Standard::clGetMemObjectInfo(apiCommand->args.memobj, CL_MEM_ASSOCIATED_MEMOBJECT, sizeof(parentClMem), &parentClMem, nullptr);
        if (nullptr == parentClMem) {
            Cal::Service::Apis::Ocl::Standard::clGetMemObjectInfo(apiCommand->args.memobj, CL_MEM_HOST_PTR, sizeof(hostPtr), &hostPtr, nullptr);
        }
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseMemObject(apiCommand->args.memobj);
    if (hostPtr && (false == ctx.isImportedClientMallocPtr(hostPtr))) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(hostPtr, false);
    }
    return true;
}

void CL_CALLBACK clCreateContextCallbackWrapper(const char *errinfo, const void *private_info, size_t cb, void *user_data) {
    auto *cctx = reinterpret_cast<Apis::Ocl::OclCallbackContextForContextNotify *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    std::strncpy(cctx->errorInfo, errinfo, 256);

    log<Verbosity::debug>("Pushed callback notification from clCreateContext to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clCreateContextHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateContext");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateContextRpcM *>(command);

    std::unique_ptr<Apis::Ocl::OclCallbackContextForContextNotify> notify;
    if (apiCommand->args.pfn_notify) {
        notify.reset(new Apis::Ocl::OclCallbackContextForContextNotify{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify), 0, reinterpret_cast<uintptr_t>(apiCommand->args.user_data), apiCommand->header, 0},
                                                                       channel.decodeLocalPtrFromHeapOffset(apiCommand->implicitArgs.error_info)});
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateContext(
        apiCommand->args.properties ? apiCommand->captures.getProperties() : nullptr,
        apiCommand->args.num_devices,
        apiCommand->args.devices ? apiCommand->captures.getDevices() : nullptr,
        notify ? clCreateContextCallbackWrapper : nullptr,
        notify.get(),
        apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
    if (notify) {
        notify->callbackId.handle = reinterpret_cast<uintptr_t>(apiCommand->captures.ret);
    }
    ctx.assignToCallbackContextForContextNotify(std::move(notify));

    return true;
}

bool clCreateContextFromTypeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateContextFromType");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateContextFromTypeRpcM *>(command);

    std::unique_ptr<Apis::Ocl::OclCallbackContextForContextNotify> notify;
    if (apiCommand->args.pfn_notify) {
        notify.reset(new Apis::Ocl::OclCallbackContextForContextNotify{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify), 0, reinterpret_cast<uintptr_t>(apiCommand->args.user_data), apiCommand->header, 0},
                                                                       channel.decodeLocalPtrFromHeapOffset(apiCommand->implicitArgs.error_info)});
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateContextFromType(
        apiCommand->args.properties ? apiCommand->captures.properties : nullptr,
        apiCommand->args.device_type,
        notify ? clCreateContextCallbackWrapper : nullptr,
        notify.get(),
        apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
    if (notify) {
        notify->callbackId.handle = reinterpret_cast<uintptr_t>(apiCommand->captures.ret);
    }
    ctx.assignToCallbackContextForContextNotify(std::move(notify));

    return true;
}

struct CallbackContext {
    Cal::Rpc::ChannelServer &channel;
    Cal::Rpc::CallbackIdT callbackId;
};

void CL_CALLBACK clSetEventCallbackCallbackWrapper(cl_event event, cl_int event_command_status, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clSetEventCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clSetEventCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetEventCallback");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetEventCallbackRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetEventCallback(
        apiCommand->args.event,
        apiCommand->args.command_exec_callback_type,
        clSetEventCallbackCallbackWrapper,
        new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.event),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                      apiCommand->header,
                                                      static_cast<uint32_t>(apiCommand->args.command_exec_callback_type)}});
    return true;
}

void CL_CALLBACK clSetContextDestructorCallbackWrapper(cl_context context, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clSetContextDestructorCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clSetContextDestructorCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetContextDestructorCallback");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetContextDestructorCallbackRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetContextDestructorCallback(
        apiCommand->args.context,
        clSetContextDestructorCallbackWrapper,
        new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.context),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                      apiCommand->header,
                                                      0}});
    return true;
}

void CL_CALLBACK clSetMemObjectDestructorCallbackWrapper(cl_mem memobj, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clSetMemObjectDestructorCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clSetMemObjectDestructorCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetMemObjectDestructorCallback");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetMemObjectDestructorCallbackRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetMemObjectDestructorCallback(
        apiCommand->args.memobj,
        clSetMemObjectDestructorCallbackWrapper,
        new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.memobj),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                      apiCommand->header,
                                                      0}});
    return true;
}

void CL_CALLBACK clBuildProgramCallbackWrapper(cl_program program, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clBuildProgramCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clBuildProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clBuildProgram");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClBuildProgramRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clBuildProgram(
        apiCommand->args.program,
        apiCommand->args.num_devices,
        apiCommand->args.device_list ? apiCommand->captures.getDevice_list() : nullptr,
        apiCommand->args.options ? apiCommand->captures.getOptions() : nullptr,
        apiCommand->args.pfn_notify ? clBuildProgramCallbackWrapper : nullptr,
        apiCommand->args.user_data ? new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                                                   reinterpret_cast<uintptr_t>(apiCommand->args.program),
                                                                                   reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                                                   apiCommand->header,
                                                                                   0}}
                                   : nullptr);
    return true;
}

void CL_CALLBACK clCompileProgramCallbackWrapper(cl_program program, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clCompileProgramCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clCompileProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCompileProgram");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCompileProgramRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCompileProgram(
        apiCommand->args.program,
        apiCommand->args.num_devices,
        apiCommand->args.device_list ? apiCommand->captures.getDevice_list() : nullptr,
        apiCommand->args.options ? apiCommand->captures.getOptions() : nullptr,
        apiCommand->args.num_input_headers,
        apiCommand->args.input_headers ? apiCommand->captures.getInput_headers() : nullptr,
        apiCommand->args.header_include_names ? apiCommand->captures.getHeader_include_names().data() : nullptr,
        apiCommand->args.pfn_notify ? clCompileProgramCallbackWrapper : nullptr,
        apiCommand->args.user_data ? new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                                                   reinterpret_cast<uintptr_t>(apiCommand->args.program),
                                                                                   reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                                                   apiCommand->header,
                                                                                   0}}
                                   : nullptr);
    return true;
}

void CL_CALLBACK clLinkProgramCallbackWrapper(cl_program program, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    callbackId.handle = reinterpret_cast<uintptr_t>(program);
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clCompileProgramCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clLinkProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clLinkProgram");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClLinkProgramRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clLinkProgram(
        apiCommand->args.context,
        apiCommand->args.num_devices,
        apiCommand->args.device_list ? apiCommand->captures.getDevice_list() : nullptr,
        apiCommand->args.options ? apiCommand->captures.getOptions() : nullptr,
        apiCommand->args.num_input_programs,
        apiCommand->args.input_programs ? apiCommand->captures.getInput_programs() : nullptr,
        apiCommand->args.pfn_notify ? clLinkProgramCallbackWrapper : nullptr,
        apiCommand->args.user_data ? new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                                                   0,
                                                                                   reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                                                   apiCommand->header,
                                                                                   0}}
                                   : nullptr,
        apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
    return true;
}

void CL_CALLBACK clSetProgramReleaseCallbackWrapper(cl_program program, void *user_data) {
    auto *cctx = reinterpret_cast<CallbackContext *>(user_data);
    Cal::Rpc::ChannelServer &channel = cctx->channel;
    Cal::Rpc::CallbackIdT callbackId = cctx->callbackId;
    delete cctx;

    log<Verbosity::debug>("Pushed callback notification from clSetProgramReleaseCallback to the ring - fptr : 0x%llx, handle : 0x%llx, subType : %u", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
    channel.pushCompletedCallbackId(callbackId);
}

bool clSetProgramReleaseCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetProgramReleaseCallback");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetProgramReleaseCallbackRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetProgramReleaseCallback(
        apiCommand->args.program,
        clSetProgramReleaseCallbackWrapper,
        new CallbackContext{channel, Rpc::CallbackIdT{reinterpret_cast<uintptr_t>(apiCommand->args.pfn_notify),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.program),
                                                      reinterpret_cast<uintptr_t>(apiCommand->args.user_data),
                                                      apiCommand->header,
                                                      0}});
    return true;
}

} // namespace Ocl

namespace LevelZero {

bool updateHostptrCopies(Cal::Rpc::ChannelServer &channel, ClientContext &ctx) {
    auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
    std::vector<Cal::Utils::AddressRange> finishedCopies;
    copiesManager.acquireFinishedCopies(ctx.getArtificialEventsManager(), finishedCopies);
    std::vector<Cal::Rpc::TransferDesc> transferDescs;
    transferDescs.reserve(finishedCopies.size());
    for (const auto &fc : finishedCopies) {
        ctx.getMemoryBlocksManager().getRequiredTransferDescs(fc, transferDescs);
    }
    for (const auto &copyDescription : transferDescs) {
        if (false == channel.pushHostptrCopyToUpdate(copyDescription)) {
            log<Verbosity::error>("Could not notify client about update of hostptr copies!");
            return false;
        }
    }

    return true;
}

bool zeInitHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeInit");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeInitRpcM *>(command);
    apiCommand->captures.ret = service.getL0SharedObjects().getZeInitReturnValue();

    return true;
}

bool zeDriverGetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGet");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetRpcM *>(command);

    auto driverHandle = service.getL0SharedObjects().getIntelGpuDriver();
    if (!driverHandle) {
        if (apiCommand->args.pCount) {
            apiCommand->captures.pCount = 0U;
            apiCommand->captures.ret = ZE_RESULT_SUCCESS;
        }
        return true;
    }

    if (apiCommand->args.pCount) {
        apiCommand->captures.pCount = 1U;

        if (apiCommand->args.phDrivers) {
            apiCommand->captures.phDrivers[0] = driverHandle;
        }

        apiCommand->captures.ret = ZE_RESULT_SUCCESS;
    }

    return true;
}

void gpuDestructorUsm(void *ctx, void *ptr) {
    if (Cal::Service::Apis::LevelZero::Standard::zeMemFree(static_cast<ze_context_handle_t>(ctx), ptr) != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemFree failed for %p", ptr);
    }
}

bool zeMemAllocHostHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemAllocHost");

    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocHostRpcM *>(command);
    apiCommand->captures.reassembleNestedStructs();

    if (!apiCommand->args.host_desc || !apiCommand->args.pptr) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_NULL_POINTER;
        return true;
    }

    constexpr uint32_t ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR = 1 << 30;
    apiCommand->captures.host_desc.flags |= ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR;

    auto minAlignment = apiCommand->args.alignment ? Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.alignment) : Cal::Utils::pageSize64KB;
    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);

    static bool useStandaloneAllocations = Utils::getCalEnvFlag(calUseStandaloneAllocationsForZeMemAllocHost, false);

    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        Cal::Allocators::ArenaSubAllocation<Cal::Ipc::MmappedShmemAllocationT, void> shmem;
        if (useStandaloneAllocations) {
            shmem = heap.allocateAsStandalone(alignedSize, minAlignment);
        } else {
            shmem = heap.allocate(alignedSize, minAlignment);
        }
        if (false == shmem.isValid()) {
            continue;
        }
        void *cpuAddress = shmem.getSubAllocationPtr();

        // Set host pointer to be used.
        apiCommand->captures.pptr = cpuAddress;
        apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocHost(apiCommand->args.hContext,
                                                                                           &apiCommand->captures.host_desc,
                                                                                           apiCommand->args.size,
                                                                                           apiCommand->args.alignment,
                                                                                           &apiCommand->captures.pptr);
        if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end);
            apiCommand->captures.pptr = nullptr;
            heap.free(shmem);
            continue; // try different heap
        }

        if (apiCommand->captures.ret == ZE_RESULT_SUCCESS && apiCommand->captures.pptr == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end, apiCommand->captures.pptr);

            ctx.addUsmSharedHostAlloc(apiCommand->args.hContext, shmem, ApiType::LevelZero, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.getSourceAllocation()->getShmemId();
            apiCommand->implicitArgs.offset_within_resource = shmem.getSubAllocationOffset();
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in zeMemAllocHost - would break USM agreements on client side (expected!=got , %p != %p)",
                                  cpuAddress, apiCommand->captures.pptr);

            Cal::Service::Apis::LevelZero::Standard::zeMemFree(apiCommand->args.hContext, apiCommand->captures.pptr);
            heap.free(shmem);

            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
            apiCommand->captures.pptr = nullptr;

            return true;
        }
    }

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS || nullptr == apiCommand->captures.pptr) {
        log<Verbosity::error>("None of USM shared/host heaps could accommodate new USM host allocation for GPU");

        if (ZE_RESULT_SUCCESS == apiCommand->captures.ret) {
            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        apiCommand->captures.pptr = nullptr;
    }

    return true;
}

bool zeMemAllocSharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemAllocShared");

    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM *>(command);
    apiCommand->captures.reassembleNestedStructs();

    if (!apiCommand->args.host_desc || !apiCommand->args.device_desc || !apiCommand->args.pptr) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_NULL_POINTER;
        return true;
    }

    constexpr uint32_t ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR = 1 << 30;
    apiCommand->captures.host_desc.flags |= ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR;

    auto minAlignment = apiCommand->args.alignment ? Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.alignment) : Cal::Utils::pageSize64KB;
    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        auto shmem = heap.allocate(alignedSize, minAlignment);
        if (false == shmem.isValid()) {
            continue;
        }
        void *cpuAddress = shmem.getSubAllocationPtr();

        // Set host pointer to be used.
        apiCommand->captures.pptr = cpuAddress;
        apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocShared(apiCommand->args.hContext,
                                                                                             &apiCommand->captures.device_desc,
                                                                                             &apiCommand->captures.host_desc,
                                                                                             apiCommand->args.size,
                                                                                             apiCommand->args.alignment,
                                                                                             apiCommand->args.hDevice,
                                                                                             &apiCommand->captures.pptr);
        if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end);
            apiCommand->captures.pptr = nullptr;
            heap.free(shmem);
            continue; // try different heap
        }

        if (apiCommand->captures.ret == ZE_RESULT_SUCCESS && apiCommand->captures.pptr == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getUnderlyingAllocator().getMmapRange().start, heap.getUnderlyingAllocator().getMmapRange().end, apiCommand->captures.pptr);

            ctx.addUsmSharedHostAlloc(apiCommand->args.hContext, shmem, ApiType::LevelZero, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.getSourceAllocation()->getShmemId();
            apiCommand->implicitArgs.offset_within_resource = shmem.getSubAllocationOffset();
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in zeMemAllocShared - would break USM agreements on client side (expected!=got , %p != %p)",
                                  cpuAddress, apiCommand->captures.pptr);

            Cal::Service::Apis::LevelZero::Standard::zeMemFree(apiCommand->args.hContext, apiCommand->captures.pptr);
            heap.free(shmem);

            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
            apiCommand->captures.pptr = nullptr;

            return true;
        }
    }

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS || nullptr == apiCommand->captures.pptr) {
        log<Verbosity::error>("None of USM shared/host heaps could acommodate new USM host allocation for GPU");

        if (ZE_RESULT_SUCCESS == apiCommand->captures.ret) {
            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        apiCommand->captures.pptr = nullptr;
    }

    return true;
}

bool zeMemFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemFree");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemFreeRpcM *>(command);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemFree(apiCommand->args.hContext, apiCommand->args.ptr);

    if (service.getCpuInfo().isAccessibleByApplication(apiCommand->args.ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(apiCommand->args.ptr, false);
    }

    return true;
}

bool zeMemFreeExtHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemFreeExt");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemFreeExtRpcM *>(command);
    apiCommand->captures.reassembleNestedStructs();
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemFreeExt(
        apiCommand->args.hContext,
        apiCommand->args.pMemFreeDesc ? &apiCommand->captures.pMemFreeDesc : nullptr,
        apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(apiCommand->args.ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(apiCommand->args.ptr, false);
    }

    return true;
}

bool zeModuleGetKernelNamesRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleGetKernelNamesRpcHelper");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleGetKernelNamesRpcHelperRpcM *>(command);

    uint32_t count{0};
    auto ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetKernelNames(apiCommand->args.hModule, &count, nullptr);
    if (ret != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve count of kernel names!");
        apiCommand->captures.ret = ret;
        return true;
    }

    std::vector<const char *> kernelNames{};
    kernelNames.resize(count);

    ret = Cal::Service::Apis::LevelZero::Standard::zeModuleGetKernelNames(apiCommand->args.hModule, &count, kernelNames.data());
    if (ret != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve kernel names!");
        apiCommand->captures.ret = ret;
        return true;
    }

    size_t totalLength = 0;
    for (const auto &kernelName : kernelNames) {
        totalLength += strlen(kernelName) + 1;
    }

    if (apiCommand->captures.totalLength == 0) {
        apiCommand->captures.totalLength = totalLength;
        apiCommand->captures.ret = ZE_RESULT_SUCCESS;
        return true;
    }

    if (apiCommand->captures.totalLength < totalLength) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_SIZE;
        return true;
    }

    auto i = 0;
    for (const auto &kernelName : kernelNames) {
        const auto len = strlen(kernelName);
        std::memcpy(apiCommand->captures.namesBuffer + i, kernelName, len);
        apiCommand->captures.namesBuffer[i + len] = '\0';

        i += (len + 1);
    }

    apiCommand->captures.totalLength = totalLength;
    apiCommand->captures.ret = ZE_RESULT_SUCCESS;
    return true;
}

bool zeModuleCreateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeModuleCreate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeModuleCreateRpcM *>(command);
    apiCommand->captures.reassembleNestedStructs();
    const auto desc = apiCommand->args.desc ? &apiCommand->captures.desc : nullptr;
    auto module = apiCommand->args.phModule ? &apiCommand->captures.phModule : nullptr;
    auto buildLog = apiCommand->args.phBuildLog ? &apiCommand->captures.phBuildLog : nullptr;
    auto lock = service.moduleCache.obtainOwnership();
    if (auto cacheEntry = service.moduleCache.find(apiCommand->args.hContext, apiCommand->args.hDevice, desc)) {
        ze_module_desc_t nativeDesc{};
        nativeDesc.stype = ZE_STRUCTURE_TYPE_MODULE_DESC;
        nativeDesc.format = ZE_MODULE_FORMAT_NATIVE;
        nativeDesc.inputSize = cacheEntry.value()->nativeSize;
        nativeDesc.pInputModule = cacheEntry.value()->pNativeBinary;
        apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleCreate(apiCommand->args.hContext, apiCommand->args.hDevice, &nativeDesc, module, buildLog);
    } else {
        apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeModuleCreate(
            apiCommand->args.hContext,
            apiCommand->args.hDevice,
            desc,
            module,
            buildLog);
        if (isSuccessful(apiCommand->captures.ret)) {
            size_t nativeSize = 0;
            Cal::Service::Apis::LevelZero::Standard::zeModuleGetNativeBinary(*module, &nativeSize, nullptr);
            auto pNativeBinary = new uint8_t[nativeSize];
            Cal::Service::Apis::LevelZero::Standard::zeModuleGetNativeBinary(*module, &nativeSize, pNativeBinary);
            service.moduleCache.store(apiCommand->args.hContext, apiCommand->args.hDevice, desc, nativeSize, pNativeBinary);
        }
    }

    if (isSuccessful(apiCommand->captures.ret)) {
        const auto &resource = apiCommand->args.phModule ? &apiCommand->captures.phModule : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    {
        const auto &resource = apiCommand->args.phBuildLog ? &apiCommand->captures.phBuildLog : nullptr;
        if (resource) {
            ctx.trackAllocatedResource(*resource);
        }
    }
    return true;
}

// acquire internal event suitable for given cmdList
ze_event_handle_t getInternalEvent(ClientContext &calClientCtx, ze_command_list_handle_t cmdList) {
    auto l0Ctx = calClientCtx.getContextMappingsTracker().getAssociatedContext(cmdList);
    return calClientCtx.getArtificialEventsManager().obtainEventReplacement(l0Ctx);
}

// trigger one event using different event
bool addRelay(ze_result_t &status, ze_event_handle_t action, ze_event_handle_t trigger, ze_command_list_handle_t cmdList) {
    if (status != ZE_RESULT_SUCCESS) {
        return false;
    }

    if (nullptr == action) {
        return true;
    }

    if (nullptr == trigger) {
        return false;
    }

    status = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendBarrier(cmdList, action, 1u, &trigger);
    return ZE_RESULT_SUCCESS == status;
}

bool synchronizeOnEventAndRequestClientMemoryUpdate(ze_result_t &status, ze_event_handle_t event, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, void *ptr, size_t size) {
    if (status != ZE_RESULT_SUCCESS) {
        return false;
    }
    status = Cal::Service::Apis::LevelZero::Standard::zeEventHostSynchronize(event, -1);
    std::vector<Cal::Rpc::TransferDesc> transferDescs;
    ctx.getMemoryBlocksManager().getRequiredTransferDescs({ptr, size}, transferDescs);
    for (const auto &td : transferDescs) {
        if (false == channel.pushHostptrCopyToUpdate(td)) {
            log<Verbosity::error>("Could not notify client about required memory update!");
            return false;
        }
    }
    return true;
}

bool zeCommandListAppendMemoryFillRpcHelperUsm2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperUsm2Malloc");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM *>(command);

    auto remappedDstPtr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.ptr, apiCommand->args.size);
    auto updateClientMemoryMarkerEvent = getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!updateClientMemoryMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return true;
    }

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
        apiCommand->args.hCommandList,
        remappedDstPtr,
        apiCommand->args.pattern,
        apiCommand->args.pattern_size,
        apiCommand->args.size,
        updateClientMemoryMarkerEvent,
        apiCommand->args.numWaitEvents,
        apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr);

    addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, updateClientMemoryMarkerEvent, apiCommand->args.hCommandList);

    if (apiCommand->captures.ret == ZE_RESULT_SUCCESS) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, updateClientMemoryMarkerEvent, apiCommand->args.ptr, apiCommand->args.size, true);
    }

    return true;
}

bool zeCommandListAppendMemoryFillRpcHelperMalloc2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM *>(command);

    auto remappedDstPtr = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.ptr, apiCommand->args.size);

    auto updateClientMemoryMarkerEvent = getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!updateClientMemoryMarkerEvent) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return true;
    }

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
        apiCommand->args.hCommandList,
        remappedDstPtr,
        apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr,
        apiCommand->args.pattern_size,
        apiCommand->args.size,
        updateClientMemoryMarkerEvent,
        apiCommand->args.numWaitEvents,
        apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr);

    addRelay(apiCommand->captures.ret, apiCommand->args.hSignalEvent, updateClientMemoryMarkerEvent, apiCommand->args.hCommandList);

    if (apiCommand->captures.ret == ZE_RESULT_SUCCESS) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, updateClientMemoryMarkerEvent, apiCommand->args.ptr, apiCommand->args.size, true);
    }

    return true;
}

bool zeCommandQueueExecuteCommandListsCopyMemoryRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM *>(command);

    // Nothing to be done.
    if (apiCommand->args.chunksCount == 0) {
        apiCommand->captures.ret = ZE_RESULT_SUCCESS;
        return true;
    }

    // Invalid input from the client.
    if (apiCommand->args.transferDescsCount == nullptr || apiCommand->args.chunks == nullptr) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_NULL_POINTER;
        return true;
    }

    // Querying size.
    if (apiCommand->captures.transferDescsCount == 0) {
        auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
        const auto wasCountRetrieved = memoryBlocksManager.getCountOfRequiredTransferDescs(apiCommand->captures.transferDescsCount,
                                                                                           apiCommand->args.chunksCount,
                                                                                           apiCommand->captures.getChunks());

        apiCommand->captures.ret = wasCountRetrieved ? ZE_RESULT_SUCCESS : ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return true;
    }

    // Invalid destination pointer.
    if (apiCommand->args.transferDescs == nullptr) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_NULL_POINTER;
        return true;
    }

    // Fetching the transfers.
    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    const auto wereTransfersRetrieved = memoryBlocksManager.getRequiredTransferDescs(apiCommand->captures.transferDescsCount,
                                                                                     apiCommand->captures.getTransferDescs(),
                                                                                     apiCommand->args.chunksCount,
                                                                                     apiCommand->captures.getChunks());

    apiCommand->captures.ret = wereTransfersRetrieved ? ZE_RESULT_SUCCESS : ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    return true;
}

bool zeContextDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeContextDestroy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeContextDestroyRpcM *>(command);

    log<Verbosity::bloat>("Destroying artificial events belonging to the context (%p)", static_cast<void *>(apiCommand->args.hContext));
    ctx.getArtificialEventsManager().clearDataForContext(apiCommand->args.hContext);

    log<Verbosity::bloat>("Calling zeContextDestroy() for the context (%p)", static_cast<void *>(apiCommand->args.hContext));
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeContextDestroy(
        apiCommand->args.hContext);
    if (isSuccessful(apiCommand->captures.ret)) {
        const auto &resource = apiCommand->args.hContext;
        if (resource) {
            ctx.removeResourceTracking(resource);
        }
    }
    return true;
}

bool zeEventHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventHostSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventHostSynchronize(
        apiCommand->args.hEvent,
        apiCommand->args.timeout);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeEventQueryStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventQueryStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryStatus(
        apiCommand->args.hEvent);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeFenceHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceHostSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceHostSynchronize(
        apiCommand->args.hFence,
        apiCommand->args.timeout);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeFenceQueryStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeFenceQueryStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeFenceQueryStatus(
        apiCommand->args.hFence);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeCommandListHostSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListHostSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListHostSynchronizeRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListHostSynchronize(
        apiCommand->args.hCommandList,
        apiCommand->args.timeout);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeCommandQueueSynchronizeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueSynchronize");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueSynchronize(
        apiCommand->args.hCommandQueue,
        apiCommand->args.timeout);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeCommandListResetHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListReset");

    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListResetRpcM *>(command);
    ctx.getOngoingHostptrCopiesManager().freeOperationsOfCommandList(apiCommand->args.hCommandList, ctx.getArtificialEventsManager());

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListReset(apiCommand->args.hCommandList);
    return true;
}

bool zeCommandListDestroyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListDestroy");

    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM *>(command);
    ctx.getOngoingHostptrCopiesManager().freeOperationsOfCommandList(apiCommand->args.hCommandList, ctx.getArtificialEventsManager());

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListDestroy(apiCommand->args.hCommandList);

    if (isSuccessful(apiCommand->captures.ret)) {
        const auto &resource = apiCommand->args.hCommandList;
        if (resource) {
            ctx.removeResourceTracking(resource);
            ctx.getContextMappingsTracker().deregisterCommandListMapping(resource);
        }
    }
    return true;
}

bool zeCommandQueueExecuteCommandListsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandQueueExecuteCommandLists");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandQueueExecuteCommandLists(
        apiCommand->args.hCommandQueue,
        apiCommand->args.numCommandLists,
        apiCommand->args.phCommandLists ? apiCommand->captures.phCommandLists : nullptr,
        apiCommand->args.hFence);

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
        return true;
    }

    auto &ongoingHostptrCopiesManager = ctx.getOngoingHostptrCopiesManager();
    for (size_t i = 0; i < apiCommand->args.numCommandLists; ++i) {
        ongoingHostptrCopiesManager.resubmitOperationsOfCommandList(apiCommand->captures.phCommandLists[i]);
    }

    return updateHostptrCopies(channel, ctx);
}

bool zeEventQueryKernelTimestampsExtRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeEventQueryKernelTimestampsExtRpcHelper");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampsExtRpcHelperRpcM *>(command);

    ze_event_query_kernel_timestamps_results_ext_properties_t tsProperties{};
    tsProperties.pNext = nullptr;
    tsProperties.stype = ZE_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_RESULTS_EXT_PROPERTIES;
    tsProperties.pKernelTimestampsBuffer = apiCommand->args.pResultsTimestamps ? apiCommand->captures.getPResultsTimestamps() : nullptr;
    tsProperties.pSynchronizedTimestampsBuffer = apiCommand->args.pResultsSynchronizedTimestamps ? apiCommand->captures.getPResultsSynchronizedTimestamps() : nullptr;

    ze_event_query_kernel_timestamps_results_ext_properties_t *tsPropertiesPtr = apiCommand->args.pResultsTimestamps ? &tsProperties : nullptr;

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeEventQueryKernelTimestampsExt(
        apiCommand->args.hEvent,
        apiCommand->args.hDevice,
        apiCommand->args.pCount ? &apiCommand->captures.pCount : nullptr,
        tsPropertiesPtr);
    return true;
}

bool zeKernelGetSourceAttributesRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeKernelGetSourceAttributes");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeKernelGetSourceAttributesRpcHelperRpcM *>(command);
    char *pString = apiCommand->args.pString ? apiCommand->captures.pString : nullptr;

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeKernelGetSourceAttributes(
        apiCommand->args.hKernel,
        apiCommand->args.pSize ? &apiCommand->captures.pSize : nullptr,
        apiCommand->args.pString ? &pString : nullptr);
    return true;
}

bool zeDriverGetLastErrorDescriptionRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeDriverGetLastErrorDescription");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeDriverGetLastErrorDescriptionRpcHelperRpcM *>(command);
    const char *pString = nullptr;

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeDriverGetLastErrorDescription(apiCommand->args.hDriver, &pString);
    if (apiCommand->captures.ret == ZE_RESULT_SUCCESS && pString != nullptr) {
        std::string receievedLastErrorDescription(pString);
        if (receievedLastErrorDescription.length() > apiCommand->captures.countPString) {
            log<Verbosity::error>("Usupported length for zeDriverGetLastErrorDescriptionRpcHelperHandler %d", receievedLastErrorDescription.length());
            return false;
        }
        std::strncpy(apiCommand->captures.pString, pString, receievedLastErrorDescription.length());
        return true;
    }
    return false;
}

} // namespace LevelZero
} // namespace Apis

Provider::Provider(std::unique_ptr<ChoreographyLibrary> knownChoreographies, ServiceConfig &&serviceConfig)
    : serviceConfig(std::move(serviceConfig)),
      knownChoreographies(std::move(knownChoreographies)) {
    if (nullptr == this->knownChoreographies) {
        this->knownChoreographies = std::make_unique<ChoreographyLibrary>();
    }
    this->globalShmemAllocators = std::make_unique<Cal::Ipc::GlobalShmemAllocators>(Cal::Ipc::getCalShmemPathBase(getpid()));
    auto requestedDefaultRpcChannelSizeMB = Cal::Utils::getCalEnvI64(calDefaultRpcChannelSizeEnvName, 0);
    if (requestedDefaultRpcChannelSizeMB > 0) {
        log<Verbosity::info>("Changing default rpc message channel size from %dMB to %dMB", this->defaultRpcMessageChannelSizeMB, requestedDefaultRpcChannelSizeMB);
        this->defaultRpcMessageChannelSizeMB = requestedDefaultRpcChannelSizeMB;
    }
    auto requestedDefaultSharedVaSizeGB = Cal::Utils::getCalEnvI64(calDefaultSharedVaSizeEnvName, 0);
    if (requestedDefaultSharedVaSizeGB > 0) {
        log<Verbosity::info>("Changing default shared VA windows size per client from %dGB to %dGB", this->defaultSharedVaSizeInGB, requestedDefaultSharedVaSizeGB);
        this->defaultSharedVaSizeInGB = requestedDefaultSharedVaSizeGB;
    }
    auto requestedSharedVaArenaSizeMB = Cal::Utils::getCalEnvI64(calSharedVaArenaSizeEnvName, 0);
    if (requestedSharedVaArenaSizeMB > 0) {
        log<Verbosity::info>("Changing default shared VA arena size from %dMB to %dMB", this->sharedVaArenaSizeMB, requestedSharedVaArenaSizeMB);
        this->sharedVaArenaSizeMB = requestedSharedVaArenaSizeMB;
    }

    this->rpcHandlers.resize(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero + 1);
    this->directCallCallbacks.resize(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero + 1);

    Cal::Service::Apis::Ocl::registerAllGeneratedHandlersOcl(this->rpcHandlers[Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl]);
    this->rpcHandlers[Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl][Cal::Rpc::Ocl::ClGetPlatformIDsRpcM::messageSubtype] = Cal::Service::Apis::Ocl::clGetPlatformIDsHandler;
    this->directCallCallbacks[Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl] = Cal::Service::Apis::Ocl::callDirectly;

    Cal::Service::Apis::LevelZero::registerAllGeneratedHandlersLevelZero(this->rpcHandlers[Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero]);
    this->directCallCallbacks[Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero] = Cal::Service::Apis::LevelZero::callDirectly;

    this->yieldThreads = Cal::Utils::getCalEnvFlag(calYieldThreadsEnvName, this->yieldThreads);
    this->commandQueueGroups.copyRoundRobinEnabled = Cal::Utils::getCalEnvFlag(calUseCopyRoundRobin, this->commandQueueGroups.copyRoundRobinEnabled);
    this->commandQueueGroups.computeRoundRobinEnabled = Cal::Utils::getCalEnvFlag(calUseComputeRoundRobin, this->commandQueueGroups.computeRoundRobinEnabled);
    this->syncMallocCopy = Cal::Utils::getCalEnvFlag(calSyncMallocCopy, this->syncMallocCopy);
    this->batchedService = Cal::Utils::getCalEnvFlag(calBatchedService, this->batchedService);
}

std::unique_ptr<Cal::Ipc::ConnectionListener> Provider::createConnectionListener() {
    log<Verbosity::debug>("Creating connection listener based on local named socket");
    return std::make_unique<Cal::Ipc::NamedSocketConnectionListener>();
}

void checkForRequiredFiles() {
    auto calDir = Cal::Utils::getProcessPath().parent_path();
    bool enableOcl = Cal::Utils::getCalEnvFlag(calEnableOclInCalrunEnvName, true);
    bool enableL0 = Cal::Utils::getCalEnvFlag(calEnableL0InCalrunEnvName, true);
    bool overrideMalloc = Cal::Utils::getCalEnvFlag(calOverrideMallocEnvName, false);
    std::filesystem::path libCalPath;
    std::string fullCalLibPath;

    if (auto handle = dlopen("libcal.so", RTLD_LAZY); handle) {
        fullCalLibPath = Cal::Utils::getLibraryPath(handle);
        dlclose(handle);
        libCalPath = "libcal.so";
    } else if (handle = dlopen((calDir / "libcal.so").c_str(), RTLD_LAZY); handle) {
        fullCalLibPath = Cal::Utils::getLibraryPath(handle);
        dlclose(handle);
        libCalPath = calDir / "libcal.so";

        auto oldLdPath = getenv("LD_LIBRARY_PATH");
        if (oldLdPath) {
            std::string newLdPath;
            newLdPath.reserve(strlen(calDir.c_str()) + 1 + strlen(oldLdPath));
            newLdPath.append(calDir.c_str());
            newLdPath.append(":");
            newLdPath.append(oldLdPath);
            Cal::Sys::setenv("LD_LIBRARY_PATH", newLdPath.c_str(), 1);
        } else {
            Cal::Sys::setenv("LD_LIBRARY_PATH", calDir.c_str(), 1);
        }
    } else {
        log<Verbosity::critical>("libcal.so not available");
        exit(EXIT_FAILURE);
    }
    log<Verbosity::info>("CAL library: %s", fullCalLibPath.c_str());

    if (enableOcl) {
        std::filesystem::path calIcdPath = Utils::getPathForTempFiles();
        bool isInOpt = std::filesystem::exists(calIcdPath / "cal.icd");
        bool isInCalDir = std::filesystem::exists(calDir / "cal.icd");
        if (isInOpt) {
            Cal::Sys::setenv("OCL_ICD_VENDORS", calIcdPath.c_str(), 1);
        } else if (isInCalDir) {
            Cal::Sys::setenv("OCL_ICD_VENDORS", calDir.c_str(), 1);
        } else {
            auto icdEntryFd = open((calIcdPath / "cal.icd"s).c_str(), O_EXCL | O_CREAT | O_WRONLY, 0600);
            bool entryAvailable = false;
            if (icdEntryFd >= 0) {
                const char *icdEntry = "libcal.so";
                auto len = static_cast<ssize_t>(strlen(icdEntry));
                if (len == write(icdEntryFd, icdEntry, len)) {
                    entryAvailable = true;
                }
                close(icdEntryFd);
            } else if (errno == EEXIST) {
                entryAvailable = true;
            }

            if (entryAvailable) {
                Cal::Sys::setenv("OCL_ICD_VENDORS", calIcdPath.c_str(), 1);
            } else {
                log<Verbosity::critical>("Fallback path for creating cal.icd file has failed. Please create cal.icd in working directory or set OCL_ICD_VENDORS environment variable");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (enableL0) {
        Cal::Sys::setenv("ZE_ENABLE_ALT_DRIVERS", libCalPath.c_str(), 1);
        if (Cal::Sys::getenv(calClientZeEnableAltDriversEnvName.data())) {
            Cal::Sys::setenv("ZE_ENABLE_ALT_DRIVERS", Cal::Sys::getenv(calClientZeEnableAltDriversEnvName.data()), 1);
        }
    }

    if (overrideMalloc) {
        log<Verbosity::info>("CAL Malloc override enabled, using malloc implementation from : %s", fullCalLibPath.c_str());
        Cal::Sys::setenv("LD_PRELOAD", fullCalLibPath.c_str(), 1);
    }
}

void spawnProcessAndWait(const ServiceConfig::RunnerConfig &config) {
    unsetenv("ZE_AFFINITY_MASK");
    auto childPid = fork();
    if (childPid == -1) {
        log<Verbosity::error>("Failed to create fork");
        exit(EXIT_FAILURE);
    } else if (childPid == 0) {
        execv(config.command.c_str(), const_cast<char *const *>(config.args.data()));
        log<Verbosity::error>("Failed to execute %s", config.command.c_str());
        exit(EXIT_FAILURE);
    } else {
        int status{};
        waitpid(childPid, &status, 0);
        if (WIFEXITED(status)) {
            const int errorCode = WEXITSTATUS(status);
            if (errorCode != EXIT_SUCCESS) {
                log<Verbosity::error>("Child process has failed! Exit code = %d", errorCode);
                exit(errorCode);
            }
        } else {
            log<Verbosity::error>("Abnormal termination of child process!");
            exit(EXIT_FAILURE);
        }
    }
}

bool Provider::runCommand(const ServiceConfig::RunnerConfig &config) {
    runnerConfig.subprocess = std::async(std::launch::async, [&] {
        checkForRequiredFiles();
        spawnProcessAndWait(config);

        this->runInLoop = false;
        this->listener->shutdown();
    });

    return true;
}

template <typename TrackingT, typename DestroyFunctionT>
void destroyResources(const char *resourceName, TrackingT &tracking, const DestroyFunctionT &destroyFunction) {
    log<Verbosity::debug>("Performing cleanup of %s (leaked handles : %zu)", resourceName, tracking.size());

    for (const auto &handle : tracking) {
        const auto result = std::invoke(destroyFunction, handle);
        if (result != ZE_RESULT_SUCCESS) {
            log<Verbosity::debug>("Could not clean up %s. Handle: %p", resourceName, static_cast<void *>(handle));
        }
    }

    tracking.clear();
}

void ClientContext::l0SpecificCleanup() {
    if (automaticCleanupOfApiHandles) {
        log<Verbosity::info>("Automatic cleanup of API handles is disabled. Skipping cleanup of API handles.");
        return;
    }

    destroyResources("ze_fence_handle_t", getTracking<ze_fence_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeFenceDestroy);
    destroyResources("ze_command_list_handle_t", getTracking<ze_command_list_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeCommandListDestroy);
    destroyResources("ze_command_queue_handle_t", getTracking<ze_command_queue_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeCommandQueueDestroy);
    destroyResources("ze_kernel_handle_t", getTracking<ze_kernel_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeKernelDestroy);
    destroyResources("ze_module_build_log_handle_t", getTracking<ze_module_build_log_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeModuleBuildLogDestroy);
    destroyResources("ze_module_handle_t", getTracking<ze_module_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeModuleDestroy);
    destroyResources("ze_event_handle_t", getTracking<ze_event_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeEventDestroy);
    destroyResources("ze_event_pool_handle_t", getTracking<ze_event_pool_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeEventPoolDestroy);
    destroyResources("ze_image_handle_t", getTracking<ze_image_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeImageDestroy);
    destroyResources("zet_metric_streamer_handle_t", getTracking<zet_metric_streamer_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zetMetricStreamerClose);
    destroyResources("ze_context_handle_t", getTracking<ze_context_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeContextDestroy);
}

} // namespace Service
} // namespace Cal
