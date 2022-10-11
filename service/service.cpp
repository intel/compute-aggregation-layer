/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "service/service.h"

#include "generated_rpc_messages_level_zero.h"
#include "generated_rpc_messages_ocl.h"
#include "generated_service_level_zero.h"
#include "generated_service_ocl.h"

#include <dlfcn.h>
#include <fstream>
#include <functional>
#include <regex>
#include <wait.h>

using namespace std::string_literals;

namespace Cal {

namespace Service {

void *getUsmMemoryFromHeap(Cal::Utils::Heap &heap, size_t alignedSize, Cal::Ipc::Shmem shmem) {
    void *cpuAddress = heap.alloc(alignedSize, Cal::Utils::pageSize64KB);
    if (nullptr == cpuAddress) {
        return nullptr;
    }
    log<Verbosity::debug>("Trying to map %zu bytes of shmem memory to USM shared/host heap : %zx-%zx at offset %zu (ptr : %p)",
                          alignedSize, heap.getRange().start, heap.getRange().end, Cal::Utils::byteDistanceAbs(heap.getRange().base(), cpuAddress), cpuAddress);
    auto ptr = Cal::Usm::mapUsmCpuRangeToFd(cpuAddress, alignedSize, shmem.fd);
    if ((MAP_FAILED == ptr) || (cpuAddress != ptr)) {
        log<Verbosity::debug>("Failed to map %zu bytes of shmem memory to USM shared/host heap : %zx-%zx at offset %zu",
                              alignedSize, heap.getRange().start, heap.getRange().end, Cal::Utils::byteDistanceAbs(heap.getRange().base(), cpuAddress), cpuAddress);
        heap.free(cpuAddress);
        return nullptr;
    }
    log<Verbosity::debug>("Succesfully mapped %zu bytes of shmem memory to USM shared/host heap : %zx-%zx at offset %zu",
                          alignedSize, heap.getRange().start, heap.getRange().end, Cal::Utils::byteDistanceAbs(heap.getRange().base(), cpuAddress), cpuAddress);
    return cpuAddress;
}

namespace Apis {

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

inline bool clHostMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM *>(command);
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for clHostMemAllocINTEL");
        return false;
    }
    std::vector<cl_mem_properties_intel> properties;
    static constexpr cl_mem_properties_intel propertiesToAdd = 2;
#define CL_MEM_ALLOC_USE_HOST_PTR_INTEL 0x1000F
    cl_mem_properties_intel propertiesToInject[] = {CL_MEM_ALLOC_USE_HOST_PTR_INTEL, 0};
    auto numPropertiesToInject = sizeof(propertiesToInject) / sizeof(propertiesToInject[0]);
    properties.reserve(numPropertiesToInject + apiCommand->captures.countProperties + (apiCommand->args.properties ? 0 : 1));
    properties.assign(propertiesToInject, propertiesToInject + numPropertiesToInject);
    if (apiCommand->args.properties) {
        properties.insert(properties.end(), apiCommand->captures.properties, apiCommand->captures.properties + apiCommand->captures.countProperties - 1);
    }

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto &shmemManager = service.getShmemManager();
    Cal::Ipc::Shmem shmem;
    {
        auto shmemManagerlock = shmemManager.lock();
        shmem = shmemManager.create(alignedSize, true);
    }
    if (false == shmem.isValid()) {
        log<Verbosity::error>("Failed to create shmem for clHostMemAllocINTEL");
        apiCommand->captures.ret = nullptr;
        apiCommand->captures.errcode_ret = CL_OUT_OF_HOST_MEMORY;
        return true;
    }

    properties.push_back(0);
    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        void *cpuAddress = getUsmMemoryFromHeap(heap, alignedSize, shmem);
        if (nullptr == cpuAddress) {
            continue;
        }
        properties[1] = reinterpret_cast<uintptr_t>(cpuAddress);
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clHostMemAllocINTEL(apiCommand->args.context,
                                                                                            properties.data(),
                                                                                            apiCommand->args.size,
                                                                                            apiCommand->args.alignment,
                                                                                            apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU",
                                  apiCommand->args.size, heap.getRange().start, heap.getRange().end);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            continue; // try different heap
        }
        if (apiCommand->captures.ret == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU",
                                  apiCommand->args.size, heap.getRange().start, heap.getRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->args.context, cpuAddress, alignedSize, shmem, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.id;
            apiCommand->implicitArgs.offset_within_resource = 0U;
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in clHostMemAllocINTEL - would break USM agreements on client side (expected!=requested , %p != %p)",
                                  cpuAddress, apiCommand->captures.ret);
            Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->captures.ret);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            apiCommand->captures.ret = nullptr;
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
            return true;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::debug>("None of USM shared/host heaps could acommodate new USM host allocation for GPU");
        if (CL_SUCCESS == apiCommand->captures.errcode_ret) {
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
        }
        auto shmemManagerlock = shmemManager.lock();
        shmemManager.release(shmem);
    }

    return true;
}

inline bool clSharedMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSharedMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM *>(command);
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for clSharedMemAllocINTEL");
        return false;
    }
    std::vector<cl_mem_properties_intel> properties;
    static constexpr cl_mem_properties_intel propertiesToAdd = 2;
#define CL_MEM_ALLOC_USE_HOST_PTR_INTEL 0x1000F
    cl_mem_properties_intel propertiesToInject[] = {CL_MEM_ALLOC_USE_HOST_PTR_INTEL, 0};
    auto numPropertiesToInject = sizeof(propertiesToInject) / sizeof(propertiesToInject[0]);
    properties.reserve(numPropertiesToInject + apiCommand->captures.countProperties + (apiCommand->args.properties ? 0 : 1));
    properties.assign(propertiesToInject, propertiesToInject + numPropertiesToInject);
    if (apiCommand->args.properties) {
        properties.insert(properties.end(), apiCommand->captures.properties, apiCommand->captures.properties + apiCommand->captures.countProperties - 1);
    }

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto &shmemManager = service.getShmemManager();
    Cal::Ipc::Shmem shmem;
    {
        auto shmemManagerlock = shmemManager.lock();
        shmem = shmemManager.create(alignedSize, true);
    }
    if (false == shmem.isValid()) {
        log<Verbosity::error>("Failed to create shmem for clSharedMemAllocINTEL");
        apiCommand->captures.ret = nullptr;
        apiCommand->captures.errcode_ret = CL_OUT_OF_HOST_MEMORY;
        return true;
    }

    properties.push_back(0);
    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        void *cpuAddress = getUsmMemoryFromHeap(heap, alignedSize, shmem);
        if (nullptr == cpuAddress) {
            continue;
        }
        properties[1] = reinterpret_cast<uintptr_t>(cpuAddress);
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clSharedMemAllocINTEL(apiCommand->args.context,
                                                                                              apiCommand->args.device,
                                                                                              properties.data(),
                                                                                              apiCommand->args.size,
                                                                                              apiCommand->args.alignment,
                                                                                              apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr);
        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            continue; // try different heap
        }
        if (apiCommand->captures.ret == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->args.context, cpuAddress, alignedSize, shmem, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.id;
            apiCommand->implicitArgs.offset_within_resource = 0U;
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in clHostMemAllocINTEL - would break USM agreements on client side (expected!=requested , %p != %p)",
                                  cpuAddress, apiCommand->captures.ret);
            Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->captures.ret);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            apiCommand->captures.ret = nullptr;
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
            return true;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::debug>("None of USM shared/host heaps could acommodate new USM host allocation for GPU");
        if (CL_SUCCESS == apiCommand->captures.errcode_ret) {
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
        }
        auto shmemManagerlock = shmemManager.lock();
        shmemManager.release(shmem);
    }

    return true;
}

inline bool clSVMAllocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
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
    auto &shmemManager = service.getShmemManager();
    Cal::Ipc::Shmem shmem;
    {
        auto shmemManagerlock = shmemManager.lock();
        shmem = shmemManager.create(alignedSize, true);
    }
    if (false == shmem.isValid()) {
        log<Verbosity::error>("Failed to create shmem for clSVMAlloc");
        apiCommand->captures.ret = nullptr;
        return true;
    }

    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        void *cpuAddress = getUsmMemoryFromHeap(heap, alignedSize, shmem);
        if (nullptr == cpuAddress) {
            continue;
        }
        properties[1] = reinterpret_cast<uintptr_t>(cpuAddress);
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clHostMemAllocINTEL(apiCommand->args.context,
                                                                                            properties,
                                                                                            apiCommand->args.size,
                                                                                            apiCommand->args.alignment,
                                                                                            nullptr);
        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            continue; // try different heap
        }
        if (apiCommand->captures.ret == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->args.context, cpuAddress, alignedSize, shmem, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.id;
            apiCommand->implicitArgs.offset_within_resource = 0U;
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in clHostMemAllocINTEL - would break USM agreements on client side (expected!=requested , %p != %p)",
                                  cpuAddress, apiCommand->captures.ret);
            Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->captures.ret);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            apiCommand->captures.ret = nullptr;
            return true;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::debug>("None of USM shared/host heaps could acommodate new SVM allocation for GPU");
        auto shmemManagerlock = shmemManager.lock();
        shmemManager.release(shmem);
    }

    return true;
}

inline bool clSVMFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSVMFree");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSVMFreeRpcM *>(command);
    auto ptr = apiCommand->args.ptr;
    Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context, apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(ptr, service.getShmemManager(), false);
    }
    return true;
}

inline bool clEnqueueSVMMapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
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

inline bool clEnqueueSVMUnmapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMUnmap");
    log<Verbosity::performance>("WARNING : clSVMAlloc is implemented using clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMUnmapRpcM *>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(apiCommand->args.command_queue,
                                                                                               apiCommand->args.num_events_in_wait_list,
                                                                                               apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr,
                                                                                               apiCommand->args.event ? &apiCommand->captures.event : nullptr);
    return true;
}

inline bool clEnqueueSVMMigrateMemHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMigrateMem");
    log<Verbosity::performance>("WARNING : clSVMAlloc is implemented using clHostMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMigrateMemRpcM *>(command);
    if (0 == apiCommand->args.num_svm_pointers) {
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(apiCommand->args.command_queue,
                                                                                                   apiCommand->args.num_events_in_wait_list,
                                                                                                   apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr,
                                                                                                   apiCommand->args.event ? &apiCommand->captures.event : nullptr);
    } else if (1 == apiCommand->args.num_svm_pointers) {
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMigrateMemINTEL(apiCommand->args.command_queue,
                                                                                                 apiCommand->args.svm_pointers[0],
                                                                                                 apiCommand->args.sizes ? apiCommand->args.sizes[0] : 0,
                                                                                                 apiCommand->args.flags,
                                                                                                 apiCommand->args.num_events_in_wait_list,
                                                                                                 apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr,
                                                                                                 apiCommand->args.event ? &apiCommand->captures.event : nullptr);
    } else {
        for (size_t i = 0; i < apiCommand->args.num_svm_pointers; ++i) {
            apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMigrateMemINTEL(apiCommand->args.command_queue,
                                                                                                     apiCommand->args.svm_pointers[i],
                                                                                                     apiCommand->args.sizes ? apiCommand->args.sizes[i] : 0,
                                                                                                     apiCommand->args.flags,
                                                                                                     apiCommand->args.num_events_in_wait_list,
                                                                                                     apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr,
                                                                                                     nullptr);
            if (CL_SUCCESS != apiCommand->captures.ret) {
                break;
            }
        }
        if ((CL_SUCCESS == apiCommand->captures.ret) && apiCommand->args.event) {
            apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(apiCommand->args.command_queue,
                                                                                                       0,
                                                                                                       nullptr,
                                                                                                       &apiCommand->captures.event);
        }
    }
    return true;
}

inline bool clCreateBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcM *>(command);

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto &shmemManager = service.getShmemManager();
    Cal::Ipc::Shmem shmem;
    {
        auto shmemManagerlock = shmemManager.lock();
        shmem = shmemManager.create(alignedSize, true);
    }
    if (false == shmem.isValid()) {
        log<Verbosity::error>("Failed to create shmem for host ptr of clCreateBuffer");
        apiCommand->captures.ret = nullptr;
        apiCommand->captures.errcode_ret = CL_OUT_OF_HOST_MEMORY;
        return true;
    }

    auto flags = apiCommand->args.flags;
    flags = flags & (~(CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR));
    flags |= CL_MEM_USE_HOST_PTR;

    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        void *cpuAddress = getUsmMemoryFromHeap(heap, alignedSize, shmem);
        if (nullptr == cpuAddress) {
            continue;
        }
        if (apiCommand->args.host_ptr && (apiCommand->args.flags & (CL_MEM_USE_HOST_PTR | CL_MEM_COPY_HOST_PTR))) {
            memcpy(cpuAddress, apiCommand->captures.host_ptr, apiCommand->args.size);
        }
        apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(apiCommand->args.context, flags, alignedSize,
                                                                                     cpuAddress, &apiCommand->captures.errcode_ret);

        if (nullptr == apiCommand->captures.ret) {
            log<Verbosity::debug>("Failed to create buffer out of host memory of size %zu bytes from USM shared/host heap :%zx-%zx", apiCommand->args.size, heap.getRange().start, heap.getRange().end);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            continue; // try different heap
        }
        if (apiCommand->captures.ret != nullptr) {
            log<Verbosity::debug>("Succesfully created buffer out of host memory of size %zu bytes out of USM shared/host memory from heap : %zx-%zx as %p ", apiCommand->args.size, heap.getRange().start, heap.getRange().end, apiCommand->captures.ret);
            ctx.addUsmSharedHostAlloc(apiCommand->captures.ret, cpuAddress, alignedSize, shmem, gpuDestructorClMem);
            apiCommand->implicitArgs.hostptr = cpuAddress;
            apiCommand->implicitArgs.hostptr_shmem_resource = shmem.id;
            apiCommand->implicitArgs.hostptr_offset_within_resource = 0U;
            apiCommand->implicitArgs.hostptr_aligned_size = alignedSize;
            break;
        }
    }
    if (nullptr == apiCommand->captures.ret) {
        log<Verbosity::debug>("None of USM shared/host heaps could acommodate new host ptr for clCreateBuffer");
        if (CL_SUCCESS == apiCommand->captures.errcode_ret) {
            apiCommand->captures.errcode_ret = CL_OUT_OF_RESOURCES;
        }
        auto shmemManagerlock = shmemManager.lock();
        shmemManager.release(shmem);
    }

    return true;
}

inline bool clMemFreeINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clMemFreeINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClMemFreeINTELRpcM *>(command);
    auto ptr = apiCommand->args.ptr;
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(apiCommand->args.context,
                                                                                   apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(ptr, service.getShmemManager(), false);
    }
    return true;
}

inline bool clMemBlockingFreeINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clMemBlockingFreeINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClMemBlockingFreeINTELRpcM *>(command);
    auto ptr = apiCommand->args.ptr;
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clMemBlockingFreeINTEL(apiCommand->args.context,
                                                                                           apiCommand->args.ptr);
    if (service.getCpuInfo().isAccessibleByApplication(ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(ptr, service.getShmemManager(), false);
    }
    return true;
}

inline bool clReleaseMemObjectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
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
    if (hostPtr && false == (ctx.getMallocShmemZeroCopyHandler() && ctx.getMallocShmemZeroCopyHandler()->isImportedPointer(hostPtr))) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(hostPtr, service.getShmemManager(), false);
    }
    return true;
}

} // namespace Ocl

namespace LevelZero {

bool LevelZeroSharedObjects::init() {
    if (!Cal::Service::Apis::LevelZero::Standard::loadLevelZeroLibrary(std::nullopt)) {
        log<Verbosity::info>("Could not load LevelZero ICD loader library (libze_loader.so.1) - LevelZero API will not be available");
        return false;
    }

    zeInitReturnValue = Cal::Service::Apis::LevelZero::Standard::zeInit(0);
    if (zeInitReturnValue != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zeInit() call has failed! LevelZero API will always return failure on zeInit() to clients");
        return false;
    }

    intelGpuDriver = getDriverByName(intelGpuPlatformName);
    if (nullptr == intelGpuDriver) {
        return false;
    }

    return true;
}

ze_driver_handle_t LevelZeroSharedObjects::getDriverByName(const char *regex) {
    const auto drivers = getDrivers();
    if (!drivers.has_value()) {
        return nullptr;
    }

    for (const auto driver : *drivers) {
        const auto devices = getDevices(driver);
        if (!devices.has_value()) {
            continue;
        }

        for (const auto device : *devices) {
            ze_device_properties_t deviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
            ze_result_t result = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetProperties(device, &deviceProperties);
            if (result != ZE_RESULT_SUCCESS) {
                log<Verbosity::debug>("Could not get device properties from L0 device!");
                continue;
            }

            Cal::Utils::Regex r{regex};
            if (r.matches(deviceProperties.name)) {
                return driver;
            }
        }
    }

    log<Verbosity::debug>("None of drivers matches given L0 driver name!");
    return nullptr;
}

std::optional<std::vector<ze_driver_handle_t>> LevelZeroSharedObjects::getDrivers() {
    uint32_t driversCount{0};
    ze_result_t result = Cal::Service::Apis::LevelZero::Standard::zeDriverGet(&driversCount, nullptr);

    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve count of L0 drivers!");
        return std::nullopt;
    }

    if (driversCount == 0u) {
        log<Verbosity::debug>("There are no L0 drivers!");
        return std::vector<ze_driver_handle_t>{};
    }

    std::vector<ze_driver_handle_t> drivers;
    drivers.resize(driversCount);

    result = Cal::Service::Apis::LevelZero::Standard::zeDriverGet(&driversCount, drivers.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve L0 drivers!");
        return std::nullopt;
    }

    return drivers;
}

std::optional<std::vector<ze_device_handle_t>> LevelZeroSharedObjects::getDevices(ze_driver_handle_t driverHandle) {
    uint32_t devicesCount{0};
    ze_result_t result = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(driverHandle, &devicesCount, nullptr);

    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve count of L0 devices!");
        return std::nullopt;
    }

    if (devicesCount == 0u) {
        log<Verbosity::debug>("There are no L0 devices!");
        return std::vector<ze_device_handle_t>{};
    }

    std::vector<ze_device_handle_t> devices;
    devices.resize(devicesCount);

    result = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(driverHandle, &devicesCount, devices.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve L0 devices!");
        return std::nullopt;
    }

    return devices;
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
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for zeMemAllocHost");
        return false;
    }

    if (!apiCommand->args.host_desc || !apiCommand->args.pptr) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_NULL_POINTER;
        return true;
    }

    constexpr uint32_t ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR = 1 << 30;
    apiCommand->captures.host_desc.flags |= ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR;

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto &shmemManager = service.getShmemManager();
    Cal::Ipc::Shmem shmem;
    {
        auto shmemManagerlock = shmemManager.lock();
        shmem = shmemManager.create(alignedSize, true);
    }

    if (false == shmem.isValid()) {
        log<Verbosity::error>("Failed to create shmem for zeMemAllocHost");
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return true;
    }

    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        void *cpuAddress = getUsmMemoryFromHeap(heap, alignedSize, shmem);
        if (nullptr == cpuAddress) {
            continue;
        }

        // Set host pointer to be used.
        apiCommand->captures.pptr = cpuAddress;
        apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemAllocHost(apiCommand->args.hContext,
                                                                                           &apiCommand->captures.host_desc,
                                                                                           apiCommand->args.size,
                                                                                           apiCommand->args.alignment,
                                                                                           &apiCommand->captures.pptr);
        if (apiCommand->captures.ret != ZE_RESULT_SUCCESS) {
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end);
            apiCommand->captures.pptr = nullptr;
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            continue; // try different heap
        }

        if (apiCommand->captures.ret == ZE_RESULT_SUCCESS && apiCommand->captures.pptr == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end, apiCommand->captures.pptr);

            ctx.addUsmSharedHostAlloc(apiCommand->args.hContext, cpuAddress, alignedSize, shmem, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.id;
            apiCommand->implicitArgs.offset_within_resource = 0U;
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in zeMemAllocHost - would break USM agreements on client side (expected!=requested , %p != %p)",
                                  cpuAddress, apiCommand->captures.pptr);

            Cal::Service::Apis::LevelZero::Standard::zeMemFree(apiCommand->args.hContext, apiCommand->captures.pptr);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);

            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
            apiCommand->captures.pptr = nullptr;

            return true;
        }
    }

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS || nullptr == apiCommand->captures.pptr) {
        log<Verbosity::debug>("None of USM shared/host heaps could accommodate new USM host allocation for GPU");

        if (ZE_RESULT_SUCCESS == apiCommand->captures.ret) {
            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        apiCommand->captures.pptr = nullptr;

        auto shmemManagerlock = shmemManager.lock();
        shmemManager.release(shmem);
    }

    return true;
}

bool zeMemAllocSharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemAllocShared");

    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM *>(command);
    if (apiCommand->args.alignment > Cal::Utils::pageSize64KB) {
        log<Verbosity::error>("Unhandled alignment for zeMemAllocShared");
        return false;
    }

    if (!apiCommand->args.host_desc || !apiCommand->args.device_desc || !apiCommand->args.pptr) {
        apiCommand->captures.ret = ZE_RESULT_ERROR_INVALID_NULL_POINTER;
        return true;
    }

    constexpr uint32_t ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR = 1 << 30;
    apiCommand->captures.host_desc.flags |= ZEX_HOST_MEM_ALLOC_FLAG_USE_HOST_PTR;

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize64KB>(apiCommand->args.size);
    auto &shmemManager = service.getShmemManager();
    Cal::Ipc::Shmem shmem;
    {
        auto shmemManagerlock = shmemManager.lock();
        shmem = shmemManager.create(alignedSize, true);
    }

    if (false == shmem.isValid()) {
        log<Verbosity::error>("Failed to create shmem for zeMemAllocShared");
        apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        return true;
    }

    auto ctxLock = ctx.lock();
    for (auto &heap : ctx.getUsmHeaps()) {
        void *cpuAddress = getUsmMemoryFromHeap(heap, alignedSize, shmem);
        if (nullptr == cpuAddress) {
            continue;
        }

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
            log<Verbosity::debug>("Failed to map %zu bytes of USM shared/host memory from heap :%zx-%zx on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end);
            apiCommand->captures.pptr = nullptr;
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);
            continue; // try different heap
        }

        if (apiCommand->captures.ret == ZE_RESULT_SUCCESS && apiCommand->captures.pptr == cpuAddress) {
            log<Verbosity::debug>("Succesfully mapped %zu bytes of USM shared/host memory from heap : %zx-%zx as %p on the GPU", apiCommand->args.size, heap.getRange().start, heap.getRange().end, apiCommand->captures.pptr);

            ctx.addUsmSharedHostAlloc(apiCommand->args.hContext, cpuAddress, alignedSize, shmem, gpuDestructorUsm);
            apiCommand->implicitArgs.shmem_resource = shmem.id;
            apiCommand->implicitArgs.offset_within_resource = 0U;
            apiCommand->implicitArgs.aligned_size = alignedSize;
            break;
        } else {
            log<Verbosity::error>("ICD ignored request to use given host memory in zeMemAllocShared - would break USM agreements on client side (expected!=requested , %p != %p)",
                                  cpuAddress, apiCommand->captures.pptr);

            Cal::Service::Apis::LevelZero::Standard::zeMemFree(apiCommand->args.hContext, apiCommand->captures.pptr);
            Cal::Usm::resetUsmCpuRange(cpuAddress, alignedSize);
            heap.free(cpuAddress);

            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
            apiCommand->captures.pptr = nullptr;

            return true;
        }
    }

    if (apiCommand->captures.ret != ZE_RESULT_SUCCESS || nullptr == apiCommand->captures.pptr) {
        log<Verbosity::debug>("None of USM shared/host heaps could acommodate new USM host allocation for GPU");

        if (ZE_RESULT_SUCCESS == apiCommand->captures.ret) {
            apiCommand->captures.ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        apiCommand->captures.pptr = nullptr;

        auto shmemManagerlock = shmemManager.lock();
        shmemManager.release(shmem);
    }

    return true;
}

bool zeMemFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeMemFree");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeMemFreeRpcM *>(command);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeMemFree(apiCommand->args.hContext, apiCommand->args.ptr);

    if (service.getCpuInfo().isAccessibleByApplication(apiCommand->args.ptr)) {
        auto ctxLock = ctx.lock();
        ctx.reapUsmSharedHostAlloc(apiCommand->args.ptr, service.getShmemManager(), false);
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

bool zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM *>(command);

    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    auto &memoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.srcptr, apiCommand->args.size);
    auto mappedSrcPtr = memoryBlock.translate(apiCommand->args.srcptr);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(apiCommand->args.hCommandList,
                                                                                                      apiCommand->args.dstptr,
                                                                                                      mappedSrcPtr,
                                                                                                      apiCommand->args.size,
                                                                                                      apiCommand->args.hSignalEvent,
                                                                                                      apiCommand->args.numWaitEvents,
                                                                                                      apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr);
    return true;
}

bool zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediate");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM *>(command);

    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    auto &memoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.srcptr, apiCommand->args.size);
    auto mappedSrcPtr = memoryBlock.translate(apiCommand->args.srcptr);

    std::memcpy(mappedSrcPtr, apiCommand->captures.getSrcptr(), apiCommand->args.size);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(apiCommand->args.hCommandList,
                                                                                                      apiCommand->args.dstptr,
                                                                                                      mappedSrcPtr,
                                                                                                      apiCommand->args.size,
                                                                                                      apiCommand->args.hSignalEvent,
                                                                                                      apiCommand->args.numWaitEvents,
                                                                                                      apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr);
    return true;
}

bool zeCommandListAppendMemoryCopyRpcHelperUsm2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperUsm2Malloc");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM *>(command);

    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    auto &memoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.dstptr, apiCommand->args.size);
    auto mappedDstPtr = memoryBlock.translate(apiCommand->args.dstptr);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(apiCommand->args.hCommandList,
                                                                                                      mappedDstPtr,
                                                                                                      apiCommand->args.srcptr,
                                                                                                      apiCommand->args.size,
                                                                                                      apiCommand->args.hSignalEvent,
                                                                                                      apiCommand->args.numWaitEvents,
                                                                                                      apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr);
    return true;
}

bool zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryCopyRpcHelperMalloc2Malloc");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM *>(command);

    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    auto &srcMemoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.srcptr, apiCommand->args.size);
    auto mappedSrcPtr = srcMemoryBlock.translate(apiCommand->args.srcptr);

    auto &dstMemoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.dstptr, apiCommand->args.size);
    auto mappedDstPtr = dstMemoryBlock.translate(apiCommand->args.dstptr);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryCopy(apiCommand->args.hCommandList,
                                                                                                      mappedDstPtr,
                                                                                                      mappedSrcPtr,
                                                                                                      apiCommand->args.size,
                                                                                                      apiCommand->args.hSignalEvent,
                                                                                                      apiCommand->args.numWaitEvents,
                                                                                                      apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr);
    return true;
}

bool zeCommandListAppendMemoryFillRpcHelperUsm2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperUsm2Malloc");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM *>(command);

    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    auto &dstMemoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.ptr, apiCommand->args.size);
    auto mappedDstPtr = dstMemoryBlock.translate(apiCommand->args.ptr);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
        apiCommand->args.hCommandList,
        mappedDstPtr,
        apiCommand->args.pattern,
        apiCommand->args.pattern_size,
        apiCommand->args.size,
        apiCommand->args.hSignalEvent,
        apiCommand->args.numWaitEvents,
        apiCommand->args.phWaitEvents ? apiCommand->captures.phWaitEvents : nullptr);
    return true;
}

bool zeCommandListAppendMemoryFillRpcHelperMalloc2MallocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc");
    auto apiCommand = reinterpret_cast<Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM *>(command);

    auto &memoryBlocksManager = ctx.getMemoryBlocksManager();
    auto &dstMemoryBlock = memoryBlocksManager.registerMemoryBlock(service.getShmemManager(), apiCommand->args.ptr, apiCommand->args.size);
    auto mappedDstPtr = dstMemoryBlock.translate(apiCommand->args.ptr);

    apiCommand->captures.ret = Cal::Service::Apis::LevelZero::Standard::zeCommandListAppendMemoryFill(
        apiCommand->args.hCommandList,
        mappedDstPtr,
        apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr,
        apiCommand->args.pattern_size,
        apiCommand->args.size,
        apiCommand->args.hSignalEvent,
        apiCommand->args.numWaitEvents,
        apiCommand->args.phWaitEvents ? apiCommand->captures.getPhWaitEvents() : nullptr);
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

} // namespace LevelZero
} // namespace Apis

Provider::Provider(std::unique_ptr<ChoreographyLibrary> knownChoreographies, ServiceConfig &&serviceConfig) : knownChoreographies(std::move(knownChoreographies)), serviceConfig(std::move(serviceConfig)) {
    if (nullptr == this->knownChoreographies) {
        this->knownChoreographies = std::make_unique<ChoreographyLibrary>();
    }
    this->shmemManager.setShmemPathBase(Cal::Ipc::getCalShmemPathBase(getpid()));
    auto requestedDefaultRpcChannelSize = Cal::Utils::getCalEnvI64(calDefaultRpcChannelSizeEnvName, 0);
    if (requestedDefaultRpcChannelSize > 0) {
        log<Verbosity::info>("Changing default rpc message channel size from %dMB to %dMB", this->defaultRpcMessageChannelSizeMB, requestedDefaultRpcChannelSize);
        this->defaultRpcMessageChannelSizeMB = requestedDefaultRpcChannelSize;
    }

    this->rpcHandlers.resize(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero + 1);
    this->directCallCallbacks.resize(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero + 1);

    Cal::Service::Apis::Ocl::registerGeneratedHandlersOcl(this->rpcHandlers[Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl]);
    this->rpcHandlers[Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl][Cal::Rpc::Ocl::ClGetPlatformIDsRpcM::messageSubtype] = Cal::Service::Apis::Ocl::clGetPlatformIDsHandler;
    this->directCallCallbacks[Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl] = Cal::Service::Apis::Ocl::callDirectly;

    Cal::Service::Apis::LevelZero::registerGeneratedHandlersLevelZero(this->rpcHandlers[Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero]);
    this->directCallCallbacks[Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero] = Cal::Service::Apis::LevelZero::callDirectly;

    this->yieldThreads = Cal::Utils::getCalEnvFlag(calYieldThreadsEnvName);
}

std::unique_ptr<Cal::Ipc::ConnectionListener> Provider::createConnectionListener() {
    log<Verbosity::debug>("Creating connection listener based on local named socket");
    return std::make_unique<Cal::Ipc::NamedSocketConnectionListener>();
}

void checkForRequiredFiles() {
    auto calDir = Cal::Utils::getProcessPath().parent_path();
    bool enableOcl = Cal::Utils::getCalEnvFlag(calEnableOclInCalrunEnvName, true);
    bool enableL0 = Cal::Utils::getCalEnvFlag(calEnableL0InCalrunEnvName, true);
    std::filesystem::path libCalPath;

    if (auto handle = dlopen("libcal.so", RTLD_LAZY); handle) {
        dlclose(handle);
        libCalPath = "libcal.so";
    } else if (handle = dlopen((calDir / "libcal.so").c_str(), RTLD_LAZY); handle) {
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

    if (enableOcl) {
        std::filesystem::path calIcdPath = "/opt/compute-aggregation-layer";
        bool isInOpt = std::filesystem::exists(calIcdPath / "cal.icd");
        bool isInCalDir = std::filesystem::exists(calDir / "cal.icd");
        if (isInOpt) {
            Cal::Sys::setenv("OCL_ICD_VENDORS", calIcdPath.c_str(), 1);
        } else if (isInCalDir) {
            Cal::Sys::setenv("OCL_ICD_VENDORS", calDir.c_str(), 1);
        } else {
            std::ofstream calIcdFile(calTempFilesDefaultPath.data() + "cal.icd"s);
            if (calIcdFile.is_open()) {
                calIcdFile << "libcal.so";
                Cal::Sys::setenv("OCL_ICD_VENDORS", calTempFilesDefaultPath.data(), 1);
            } else {
                log<Verbosity::critical>("Fallback path for creating cal.icd file has failed. Please create cal.icd in working directory or set OCL_ICD_VENDORS environment variable");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (enableL0) {
        Cal::Sys::setenv("ZE_ENABLE_ALT_DRIVERS", libCalPath.c_str(), 1);
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

void Provider::spawnProcessAndWait(const ServiceConfig::RunnerConfig &config) {

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
        int status;
        waitpid(childPid, &status, 0);
        if (WIFEXITED(status) == false) {
            log<Verbosity::error>("Failed to terminate child process");
            exit(EXIT_FAILURE);
        }
    }
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
    if (isPersistentMode) {
        log<Verbosity::info>("Resource tracking is disabled. Skipping resource cleaning.");
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
    destroyResources("ze_context_handle_t", getTracking<ze_context_handle_t>(), Cal::Service::Apis::LevelZero::Standard::zeContextDestroy);
}

} // namespace Service
} // namespace Cal
