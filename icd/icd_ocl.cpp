/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_ocl.h"

#include "generated_icd_ocl.h"
#include "generated_rpc_messages_ocl.h"
#include "include/cal.h"
#include "shared/log.h"
#include "shared/usm.h"

#include <CL/cl_ext.h>
#include <memory>
#include <numeric>

extern char *__progname;

cl_icd_dispatch clIcdDispatchTable;

namespace Cal {
namespace Icd {
namespace Ocl {

cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms) {
    if (0 == strcmp(__progname, calServiceProcessName.data())) {
        log<Verbosity::debug>("Skipping CAL OCL platform for OCL ICD loader used from within CAL service");
        if (num_platforms) {
            *num_platforms = 0U;
        }
        return CL_SUCCESS;
    }
    auto platform = Cal::Icd::icdGlobalState.getOclPlatform();
    if ((nullptr == platform) || (false == platform->valid())) {
        if (num_platforms) {
            log<Verbosity::debug>("CAL service not available - returning num_platforms=0");
            *num_platforms = 0U;
        }
        return CL_SUCCESS;
    }

    if (nullptr == platform->asRemoteObject()) {
        log<Verbosity::debug>("Getting cl_platform_id from service");
        cl_platform_id calPlatformId{};
        auto ret = Cal::Icd::Ocl::clGetPlatformIDsRpcHelper(1, &calPlatformId, nullptr);
        if ((CL_SUCCESS != ret) || (nullptr == calPlatformId)) {
            log<Verbosity::debug>("Failed to get cl_platform_id from service");
            if (num_platforms) {
                *num_platforms = 0U;
            }
            return CL_SUCCESS;
        }
        log<Verbosity::debug>("Got cl_platform_id from service : %p", calPlatformId);
        platform->setRemoteObject(calPlatformId);
    }

    if (num_platforms) {
        *num_platforms = 1;
    }

    if (num_entries > 0) {
        auto platform = Cal::Icd::icdGlobalState.getOclPlatform();
        platforms[0] = platform;
    }

    return CL_SUCCESS;
}

cl_int clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    auto getParamString = [=](const char *src) {
        auto srcLen = strlen(src) + 1;
        if (param_value_size_ret) {
            *param_value_size_ret = srcLen;
        }
        if ((param_value_size > 0) && param_value) {
            if (param_value_size < srcLen) {
                return CL_OUT_OF_HOST_MEMORY;
            }
            memcpy(param_value, src, srcLen);
        }
        return CL_SUCCESS;
    };
    if (param_name == CL_PLATFORM_NAME) {
        return getParamString(calPlatformName.data());
    }

    return clGetPlatformInfoRpcHelper(platform, param_name, param_value_size, param_value, param_value_size_ret);
}

static cl_int getProgramBinaries(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    auto icdProgram = static_cast<IcdOclProgram *>(program);
    const auto binariesSizes = icdProgram->getBinariesSizes();

    const auto totalSize = std::accumulate(std::begin(binariesSizes), std::end(binariesSizes), std::size_t{0});
    std::vector<unsigned char> concatenatedBinaries(totalSize, '\0');

    const auto result = clGetProgramInfoGetBinariesRpcHelper(program, totalSize, concatenatedBinaries.data(), binariesSizes.size(), binariesSizes.data(), param_value_size_ret);
    if (result != CL_SUCCESS) {
        return result;
    }

    auto outputBinaries = reinterpret_cast<unsigned char **>(param_value);
    auto offset = 0u;

    for (auto i = 0u; i < binariesSizes.size(); ++i) {
        if (outputBinaries[i] == nullptr) {
            continue;
        }

        if (offset >= param_value_size) {
            log<Verbosity::error>("Invalid offset during retrieval of program binaries!");
            return CL_INVALID_VALUE;
        }

        std::memcpy(outputBinaries[i], concatenatedBinaries.data() + offset, binariesSizes[i]);
        offset += binariesSizes[i];
    }

    return CL_SUCCESS;
}

static cl_int getProgramBinariesSizes(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    // Prevent usage of uninitialized values when sizes are stored.
    std::memset(param_value, 0, param_value_size);

    const auto result = clGetProgramInfoRpcHelper(program, param_name, param_value_size, param_value, param_value_size_ret);
    if (result != CL_SUCCESS) {
        return result;
    }

    auto icdProgram = static_cast<IcdOclProgram *>(program);
    icdProgram->storeSizesOfBinaries(param_value, param_value_size);

    return CL_SUCCESS;
}

cl_int clGetProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    if (param_name == CL_PROGRAM_BINARIES) {
        return getProgramBinaries(program, param_name, param_value_size, param_value, param_value_size_ret);
    }

    if (param_name == CL_PROGRAM_BINARY_SIZES) {
        return getProgramBinariesSizes(program, param_name, param_value_size, param_value, param_value_size_ret);
    }

    return clGetProgramInfoRpcHelper(program, param_name, param_value_size, param_value, param_value_size_ret);
}

void *clGetExtensionFunctionAddress(const char *funcname) {
    if (0 == strcmp(funcname, "clIcdGetPlatformIDsKHR")) {
        return reinterpret_cast<void *>(Cal::Icd::Ocl::clIcdGetPlatformIDsKHR);
    }
    return getOclExtensionFuncionAddressRpcHelper(funcname);
}

void *clGetExtensionFunctionAddressForPlatform(cl_platform_id platform, const char *funcname) {
    return Cal::Icd::Ocl::clGetExtensionFunctionAddress(funcname);
}

cl_kernel clCreateKernel(cl_program program, const char *kernel_name, cl_int *errcode_ret) {
    auto kernel = clCreateKernelRpcHelper(program, kernel_name, errcode_ret);
    if (nullptr == kernel) {
        return kernel;
    }
    if (false == static_cast<Cal::Icd::Ocl::IcdOclKernel *>(kernel)->initTraits()) { // need to be called out of RPC handler in order to use RPC
        log<Verbosity::critical>("Failed to initialize kernel traits");
        delete static_cast<Cal::Icd::Ocl::IcdOclKernel *>(kernel);
        if (errcode_ret) {
            *errcode_ret = CL_OUT_OF_HOST_MEMORY;
        }
        return nullptr;
    }
    return kernel;
}

cl_int clCreateKernelsInProgram(cl_program program, cl_uint num_kernels, cl_kernel *kernels, cl_uint *num_kernels_ret) {
    cl_uint numKernelsCreated = 0;
    cl_int err = clCreateKernelsInProgramRpcHelper(program, num_kernels, kernels, &numKernelsCreated);

    if ((CL_SUCCESS == err) && (nullptr != kernels)) {
        cl_uint kernelsToInitialize = (num_kernels < numKernelsCreated) ? num_kernels : numKernelsCreated;
        for (cl_uint i = 0; i < kernelsToInitialize; ++i) {
            if (false == static_cast<Cal::Icd::Ocl::IcdOclKernel *>(kernels[i])->initTraits()) { // need to be called out of RPC handler in order to use RPC
                log<Verbosity::critical>("Failed to initialize kernel traits for kernel %d", i);
                for (cl_uint j = 0; j < kernelsToInitialize; ++j) {
                    delete static_cast<Cal::Icd::Ocl::IcdOclKernel *>(kernels[j]);
                    kernels[j] = nullptr;
                }
                return CL_OUT_OF_HOST_MEMORY;
            }
        }
    }
    if (nullptr != num_kernels_ret) {
        *num_kernels_ret = numKernelsCreated;
    }
    return err;
}

void *clSVMAlloc(cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment) {
    Cal::Rpc::Ocl::ClSVMAllocRpcM::ImplicitArgs implicitArgs;
    auto ptr = Cal::Icd::Ocl::clSVMAllocRpcHelper(context, flags, size, alignment, implicitArgs);
    if (nullptr == ptr) {
        return nullptr;
    }
    if (false == Cal::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, ptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open SVM shmem");
        Cal::Icd::Ocl::clMemFreeINTEL(context, ptr);
        ptr = nullptr;
    }
    return ptr;
}

void *clHostMemAllocINTEL(cl_context context, const cl_mem_properties_intel *properties, size_t size, cl_uint alignment, cl_int *errcode_ret) {
    Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM::ImplicitArgs implicitArgs;
    auto ptr = Cal::Icd::Ocl::clHostMemAllocINTELRpcHelper(context, properties, size, alignment, errcode_ret, implicitArgs);
    if (nullptr == ptr) {
        return nullptr;
    }
    if (false == Cal::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, ptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Icd::Ocl::clMemFreeINTEL(context, ptr);
        ptr = nullptr;
        if (errcode_ret) {
            *errcode_ret = CL_OUT_OF_HOST_MEMORY;
        }
    }
    return ptr;
}
void *clSharedMemAllocINTEL(cl_context context, cl_device_id device, const cl_mem_properties_intel *properties, size_t size, cl_uint alignment, cl_int *errcode_ret) {
    if (!Cal::Icd::icdGlobalState.getOclPlatform()->getPageFaultManager()->getSharedAllocationsEnabled()) {
        return Cal::Icd::Ocl::clHostMemAllocINTEL(context, properties, size, alignment, errcode_ret);
    }

    Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM::ImplicitArgs implicitArgs;
    auto ptr = Cal::Icd::Ocl::clSharedMemAllocINTELRpcHelper(context, device, properties, size, alignment, errcode_ret, implicitArgs);
    if (nullptr == ptr) {
        return nullptr;
    }
    if (false == Cal::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, ptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Icd::Ocl::clMemFreeINTEL(context, ptr);
        ptr = nullptr;
        if (errcode_ret) {
            *errcode_ret = CL_OUT_OF_HOST_MEMORY;
        }
        return ptr;
    }
    Cal::Icd::icdGlobalState.getOclPlatform()->getPageFaultManager()->registerSharedAlloc(ptr, size, getSharedAllocationPlacement(properties));
    return ptr;
}

cl_int clEnqueueMemcpyINTEL(cl_command_queue commandQueue, cl_bool blocking, void *dstPtr, const void *srcPtr, size_t size, cl_uint numEventsInWaitList, const cl_event *eventWaitList, cl_event *event) {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    globalOclPlatform->getPageFaultManager()->moveAllocationToGpu(dstPtr, srcPtr);
    const void *ptrs[] = {dstPtr, srcPtr};
    bool testResults[2] = {};
    globalOclPlatform->areUsm(2, ptrs, testResults);
    bool &dstIsUsm = testResults[0];
    bool &srcIsUsm = testResults[1];
    if (false == (dstIsUsm || srcIsUsm)) {
        log<Verbosity::error>("Unsuported call to clEnqueueMemcpyINTEL using 2 non-USM pointers");
        return CL_INVALID_ARG_VALUE;
    }
    if (dstIsUsm && srcIsUsm) {
        return clEnqueueMemcpyINTELRpcHelperUsm2Usm(commandQueue, blocking, dstPtr, srcPtr, size, numEventsInWaitList, eventWaitList, event);
    } else if (dstIsUsm) {
        return clEnqueueMemcpyINTELRpcHelperMalloc2Usm(commandQueue, blocking, dstPtr, srcPtr, size, numEventsInWaitList, eventWaitList, event);
    } else {
        return clEnqueueMemcpyINTELRpcHelperUsm2Malloc(commandQueue, blocking, dstPtr, srcPtr, size, numEventsInWaitList, eventWaitList, event);
    }
}

cl_int clEnqueueSVMMemcpy(cl_command_queue commandQueue, cl_bool blocking, void *dstPtr, const void *srcPtr, size_t size, cl_uint numEventsInWaitList, const cl_event *eventWaitList, cl_event *event) {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    globalOclPlatform->getPageFaultManager()->moveAllocationToGpu(dstPtr, srcPtr);
    const void *ptrs[] = {dstPtr, srcPtr};
    bool testResults[2] = {};
    globalOclPlatform->areUsm(2, ptrs, testResults);
    bool &dstIsUsm = testResults[0];
    bool &srcIsUsm = testResults[1];
    if (false == (dstIsUsm || srcIsUsm)) {
        log<Verbosity::error>("Unsuported call to clEnqueueSVMMemcpy using 2 non-USM pointers");
        return CL_INVALID_ARG_VALUE;
    }
    if (dstIsUsm && srcIsUsm) {
        return clEnqueueSVMMemcpyRpcHelperUsm2Usm(commandQueue, blocking, dstPtr, srcPtr, size, numEventsInWaitList, eventWaitList, event);
    } else if (dstIsUsm) {
        return clEnqueueSVMMemcpyRpcHelperMalloc2Usm(commandQueue, blocking, dstPtr, srcPtr, size, numEventsInWaitList, eventWaitList, event);
    } else {
        return clEnqueueSVMMemcpyRpcHelperUsm2Malloc(commandQueue, blocking, dstPtr, srcPtr, size, numEventsInWaitList, eventWaitList, event);
    }
}

cl_int clEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event) {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    globalOclPlatform->getPageFaultManager()->moveAllocationToGpu(ptr);
    auto isUsmHostPtr = globalOclPlatform->isUsmHostOrShared(ptr);
    if (isUsmHostPtr) {
        return clEnqueueReadBufferRpcHelperUsmHost(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    } else if (globalOclPlatform->isZeroCopyForMallocShmemEnabled()) {
        return clEnqueueReadBufferRpcHelperZeroCopyMallocShmem(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    } else {
        return clEnqueueReadBufferRpcHelperMallocHost(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}

cl_int clEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event) {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    globalOclPlatform->getPageFaultManager()->moveAllocationToGpu(ptr);
    auto isUsmHostPtr = globalOclPlatform->isUsmHostOrShared(ptr);
    if (isUsmHostPtr) {
        return clEnqueueReadBufferRectRpcHelperUsmHost(command_queue, buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    } else if (globalOclPlatform->isZeroCopyForMallocShmemEnabled()) {
        return clEnqueueReadBufferRectRpcHelperZeroCopyMallocShmem(command_queue, buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    } else {
        return clEnqueueReadBufferRectRpcHelperMallocHost(command_queue, buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}

cl_int clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event) {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    globalOclPlatform->getPageFaultManager()->moveAllocationToGpu(ptr);
    auto isUsmHostPtr = globalOclPlatform->isUsmHostOrShared(ptr);
    if (isUsmHostPtr) {
        return clEnqueueWriteBufferRpcHelperUsmHost(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    } else if (globalOclPlatform->isZeroCopyForMallocShmemEnabled()) {
        return clEnqueueWriteBufferRpcHelperZeroCopyMallocShmem(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    } else {
        return clEnqueueWriteBufferRpcHelperMallocHost(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}

cl_int clEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event) {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    globalOclPlatform->getPageFaultManager()->moveAllocationToGpu(ptr);
    auto isUsmHostPtr = globalOclPlatform->isUsmHostOrShared(ptr);
    if (isUsmHostPtr) {
        return clEnqueueWriteBufferRectRpcHelperUsmHost(command_queue, buffer, blocking_write, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    } else if (globalOclPlatform->isZeroCopyForMallocShmemEnabled()) {
        return clEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmem(command_queue, buffer, blocking_write, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    } else {
        return clEnqueueWriteBufferRectRpcHelperMallocHost(command_queue, buffer, blocking_write, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}

cl_mem clCreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret) {
    if (errcode_ret) {
        *errcode_ret = CL_SUCCESS;
    }

    auto recycledBuffer = context->asLocalObject()->tryGetRecycledClBuffer(context, flags, size, host_ptr, errcode_ret);
    if (recycledBuffer) {
        log<Verbosity::info>("Recycle succesful, size %lu , host_ptr %p ", size, host_ptr);
        return recycledBuffer;
    } else {
        log<Verbosity::performance>("Failed to recycle buffer, size %lu , host_ptr %p ", size, host_ptr);
    }
    cl_mem retMem = nullptr;
    if ((flags & CL_MEM_USE_HOST_PTR) && Cal::Icd::icdGlobalState.getOclPlatform()->isZeroCopyForMallocShmemEnabled()) {
        retMem = clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem(context, flags, size, host_ptr, errcode_ret);
    } else {
        Cal::Rpc::Ocl::ClCreateBufferRpcM::ImplicitArgs implicitArgs = {};
        retMem = clCreateBufferRpcHelper(context, flags, size, host_ptr, errcode_ret, implicitArgs);
        if (nullptr == retMem) {
            return nullptr;
        }
        if (false == Cal::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, implicitArgs.hostptr,
                                                                                              implicitArgs.hostptr_shmem_resource,
                                                                                              implicitArgs.hostptr_offset_within_resource,
                                                                                              implicitArgs.hostptr_aligned_size)) {
            log<Verbosity::error>("Failed to open USM shared/host shmem");
            Cal::Icd::Ocl::clReleaseMemObject(retMem);
            if (errcode_ret) {
                *errcode_ret = CL_OUT_OF_HOST_MEMORY;
            }
        } else {
            retMem->asLocalObject()->hostPtr = implicitArgs.hostptr;
        }
    }
    retMem->asLocalObject()->apiHostPtr = host_ptr;
    retMem->asLocalObject()->size = size;
    retMem->asLocalObject()->flags = flags;
    retMem->asLocalObject()->parent = context->asLocalObject();
    return retMem;
}

const bool useFastClockGetter = true;
#define NSEC_PER_SEC (1000000000ULL)
cl_int clGetHostTimer(cl_device_id device, cl_ulong *host_timestamp) {
    if (useFastClockGetter) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        *host_timestamp = (uint64_t)ts.tv_sec * NSEC_PER_SEC + ts.tv_nsec;
        return CL_SUCCESS;
    } else {
        return clGetHostTimerRpcHelper(device, host_timestamp);
    }
}

cl_int clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value) {
    log<Verbosity::bloat>("Establishing RPC for clSetKernelArg");
    auto oclKernel = static_cast<IcdOclKernel *>(kernel);
    auto cacheRet = oclKernel->clSetKernelArgCache.cache.end();

    if (Cal::Icd::icdGlobalState.isCacheEnabled()) {
        cacheRet = oclKernel->clSetKernelArgCache.findCachedKernelArg(arg_index, arg_size, arg_value);
    }

    cl_int ret = CL_SUCCESS;

    if (cacheRet == oclKernel->clSetKernelArgCache.cache.end()) {
        ret = Cal::Icd::Ocl::clSetKernelArgRpcHelper(kernel, arg_index, arg_size, arg_value);

        if (Cal::Icd::icdGlobalState.isCacheEnabled()) {
            oclKernel->clSetKernelArgCache.cacheKernelArg(arg_index, arg_size, arg_value);
        }
    }

    return ret;
}

cl_int clSetKernelArgMemPointerINTEL(cl_kernel kernel, cl_uint argIndex, const void *argValue) {
    log<Verbosity::bloat>("Establishing RPC for clSetKernelArgMemPointerINTEL");
    auto oclKernel = static_cast<IcdOclKernel *>(kernel);
    oclKernel->storeKernelArg(argValue, argIndex);
    auto cacheRet = oclKernel->clSetKernelArgCache.cache.end();

    if (Cal::Icd::icdGlobalState.isCacheEnabled()) {
        cacheRet = oclKernel->clSetKernelArgCache.findCachedKernelArg(argIndex, 0u, argValue);
    }

    cl_int ret = CL_SUCCESS;

    if (cacheRet == oclKernel->clSetKernelArgCache.cache.end()) {
        ret = Cal::Icd::Ocl::clSetKernelArgMemPointerINTELRpcHelper(kernel, argIndex, argValue);

        if (Cal::Icd::icdGlobalState.isCacheEnabled()) {
            oclKernel->clSetKernelArgCache.cacheKernelArg(argIndex, 0u, argValue);
        }
    } else {
        ret = CL_SUCCESS;
    }
    return ret;
}

cl_int clSetKernelArgSVMPointer(cl_kernel kernel, cl_uint argIndex, const void *argValue) {
    return Cal::Icd::Ocl::clSetKernelArgMemPointerINTEL(kernel, argIndex, argValue);
}

IcdOclContext::IcdOclContext(cl_context remoteObject, Cal::Shared::SingleReference &&parent,
                             Cal::Shared::RefCounted<_cl_context, IcdOclTypePrinter>::CleanupFuncT cleanupFunc)
    : Cal::Shared::RefCountedWithParent<_cl_context, IcdOclTypePrinter>(remoteObject, std::move(parent), cleanupFunc) {
    Cal::Icd::icdGlobalState.registerAtExit(this, [this](const void *key) { this->globalReleaseCallback(); });

    this->skipTransferOnHostPtrMatch = Cal::Utils::getCalEnvFlag(calIcdBufferRecycleEnvName);
    this->skipTransferOnHostPtrMatch |= Cal::Icd::icdGlobalState.getOclPlatform()->isZeroCopyForMallocShmemEnabled();
}

void IcdOclContext::beforeReleaseCallback() {
    if (1 == this->peekRefCount()) {
        clBufferRecycler.cleanup();
        if (implicitQueue) {
            Cal::Icd::Ocl::clReleaseCommandQueue(implicitQueue);
        }
    }
}

cl_mem IcdOclContext::tryGetRecycledClBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret) {
    if (host_ptr && (nullptr == implicitQueue)) {
        return nullptr;
    }
    auto recycledBuffer = clBufferRecycler.tryGetRecycledClBuffer(context, flags, size, host_ptr, errcode_ret);
    if (nullptr != recycledBuffer) {
        bool skipCopy = false;
        if (this->skipTransferOnHostPtrMatch && host_ptr == static_cast<IcdOclMem *>(recycledBuffer)->apiHostPtr) {
            skipCopy = true;
            log<Verbosity::info>("Skipping transfer for recycled buffer %d with host ptr %p", recycledBuffer, host_ptr);
        }
        if (!skipCopy) {
            auto err = Cal::Icd::Ocl::clEnqueueWriteBuffer(implicitQueue, recycledBuffer, CL_TRUE, 0, size, host_ptr, 0U, nullptr, nullptr);
            if (err) {
                log<Verbosity::error>("Could not overwrite recycled buffer");
                tryRecycleClBuffer(recycledBuffer);
                return nullptr;
            }
        }
    }
    return recycledBuffer;
}

bool IcdOclContext::tryRecycleClBuffer(cl_mem mem) {
    return clBufferRecycler.tryRecycleClBuffer(mem);
}

void IcdOclContext::setDevicesList(size_t numDevices, const cl_device_id *devices) {
    this->devices.assign(devices, devices + numDevices);
    for (auto &device : this->devices) {
        if (device) {
            static_cast<IcdOclDevice *>(device)->inc();
        }
    }
    if (numDevices && this->clBufferRecycler.allowedReuseSizeTotal > 0) {
        static constexpr int numPropertiesWithVal = 2; // CL_QUEUE_FAMILY_INTEL + CL_QUEUE_INDEX_INTEL
        static constexpr int entriesPerProperty = 2;   // name + value
        static constexpr int nullterminateSize = 1;
        cl_command_queue_properties properties[numPropertiesWithVal * entriesPerProperty + nullterminateSize] = {};
        cl_command_queue_properties *propertyIt = properties;
        *(propertyIt++) = CL_QUEUE_FAMILY_INTEL;
        cl_command_queue_properties &queueFamily = *(propertyIt++);
        *(propertyIt++) = CL_QUEUE_INDEX_INTEL;
        cl_command_queue_properties &queueIndex = *(propertyIt++);

        queueFamily = 3;
        int signedQueueIndex = 7;

        do {
            queueIndex = signedQueueIndex--;
            implicitQueue = Cal::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], properties, nullptr);
            if (implicitQueue != nullptr) {
                log<Verbosity::debug>("Created implicit command queue with family: %d and index %d", queueFamily, queueIndex);
            }
        } while (implicitQueue == nullptr && signedQueueIndex >= 0);
        if (implicitQueue == nullptr) {
            queueFamily = 2u;
            queueIndex = 0u;
            implicitQueue = Cal::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], properties, nullptr);
            if (implicitQueue != nullptr) {
                log<Verbosity::debug>("Created implicit command queue with family: %d and index %d", queueFamily, queueIndex);
            }
        }
        if (implicitQueue == nullptr) {
            queueFamily = 0u;
            signedQueueIndex = 3u;
            do {
                queueIndex = signedQueueIndex--;
                implicitQueue = Cal::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], properties, nullptr);
                if (implicitQueue != nullptr) {
                    log<Verbosity::debug>("Created implicit command queue with family: %d and index %d", queueFamily, queueIndex);
                }
            } while (implicitQueue == nullptr && signedQueueIndex >= 0);
        }
        if (implicitQueue == nullptr) {
            implicitQueue = Cal::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], nullptr, nullptr);
            if (implicitQueue != nullptr) {
                log<Verbosity::debug>("Created implicit command queue without properties");
            }
        }
        if (nullptr == implicitQueue) {
            log<Verbosity::error>("Could not create implicit queue");
        }
    }
}

bool IcdOclKernel::initTraits() {
    cl_uint numArgs = 0;
    if (CL_SUCCESS != Cal::Icd::Ocl::clGetKernelInfo(this, CL_KERNEL_NUM_ARGS, sizeof(numArgs), &numArgs, 0)) {
        return false;
    }
    this->argsTraits.reserve(numArgs);
    std::vector<char> argType(128);
    // note : taking advantage that NEO exposes kernel arg info even without -cl-kernel-arg-info build option
    for (cl_uint i = 0; i < numArgs; ++i) {
        ArgTraits argTraits;
        size_t typeLen = 0;
        auto err = Cal::Icd::Ocl::clGetKernelArgInfo(this, i, CL_KERNEL_ARG_TYPE_NAME, argType.size(), argType.data(), &typeLen);
        if ((CL_SUCCESS != err) && (typeLen < argType.size())) {
            if (typeLen <= argType.size()) {
                return false;
            }
            argType.resize(typeLen);
            err = Cal::Icd::Ocl::clGetKernelArgInfo(this, i, CL_KERNEL_ARG_TYPE_NAME, argType.size(), argType.data(), &typeLen);
            if (CL_SUCCESS != err) {
                return false;
            }
        }

        if (strstr(argType.data(), "*")) {
            argTraits.isPointer = true;
        }
        log<Verbosity::bloat>("Kernel arg type %s %s of buffer type", argType.data(), argTraits.isPointer ? "IS" : "is NOT");
        argsTraits.push_back(argTraits);
    }
    return true;
}

bool IcdOclKernel::initTraits(const IcdOclKernel *sourceKernel) {
    this->argsTraits = sourceKernel->argsTraits;
    return true;
}

void IcdOclKernel::moveArgsToGpu() {
    if (sharedIndirectAccessSet) {
        Cal::Icd::icdGlobalState.getOclPlatform()->getPageFaultManager()->moveAllAllocationsToGpu();
    } else {
        for (auto &alloc : this->allocationsToMigrate) {
            Cal::Icd::icdGlobalState.getOclPlatform()->getPageFaultManager()->moveAllocationToGpu(alloc);
        }
    }
}

std::vector<size_t> IcdOclProgram::getBinariesSizes() {
    std::lock_guard lock{binariesSizesMutex};
    return binariesSizes;
}

void IcdOclProgram::storeSizesOfBinaries(void *paramValue, size_t paramValueSize) {
    std::lock_guard lock{binariesSizesMutex};

    auto sizes = reinterpret_cast<size_t *>(paramValue);
    auto count = paramValueSize / sizeof(size_t);

    binariesSizes.assign(sizes, sizes + count);
}

void IcdOclProgram::recordGlobalPointer(void *ptr) {
    if (!ptr) {
        return;
    }

    std::lock_guard lock{globalPointersMutex};
    if (std::find(globalPointers.begin(), globalPointers.end(), ptr) != globalPointers.end()) {
        return;
    }

    globalPointers.push_back(ptr);
    Cal::Icd::icdGlobalState.getOclPlatform()->recordGlobalPointer(ptr);
}

void IcdOclProgram::removeGlobalPointer() {
    std::lock_guard lock{globalPointersMutex};
    for (auto &ptr : globalPointers) {
        Cal::Icd::icdGlobalState.getOclPlatform()->removeGlobalPointer(ptr);
    }
    globalPointers.clear();
}

template <typename OclObjectT>
void objectCleanup(void *remote, void *local) {
    Cal::Icd::icdGlobalState.getOclPlatform()->removeObjectFromMap(static_cast<OclObjectT>(remote), static_cast<OclObjectT>(local));
}

template void objectCleanup<cl_kernel>(void *, void *);
template void objectCleanup<cl_program>(void *, void *);
template void objectCleanup<cl_context>(void *, void *);
template void objectCleanup<cl_device_id>(void *, void *);
template void objectCleanup<cl_sampler>(void *, void *);
template void objectCleanup<cl_mem>(void *, void *);
template void objectCleanup<cl_command_queue>(void *, void *);
template void objectCleanup<cl_event>(void *, void *);

} // namespace Ocl
} // namespace Icd
} // namespace Cal
