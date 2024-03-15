/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_ocl.h"

#include "client/client_malloc_override.h"
#include "client/icd/get_all_extension_function_address.h"
#include "client/icd/icd_page_fault_manager.h"
#include "generated_icd_ocl.h"
#include "generated_rpc_messages_ocl.h"
#include "include/cal.h"
#include "shared/log.h"
#include "shared/usm.h"
#include "shared/utils.h"

#include <CL/cl_ext.h>
#include <memory>
#include <numeric>

extern char *__progname;

cl_icd_dispatch clIcdDispatchTable;

namespace Cal {
namespace Client::Icd {
namespace Ocl {

cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms) {
    if (0 == strcmp(__progname, calServiceProcessName.data())) {
        log<Verbosity::debug>("Skipping CAL OCL platform for OCL ICD loader used from within CAL service");
        if (num_platforms) {
            *num_platforms = 0U;
        }
        return CL_SUCCESS;
    }
    auto platform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    if (nullptr == platform) {
        if (num_platforms) {
            log<Verbosity::debug>("CAL service not available - returning num_platforms=0");
            *num_platforms = 0U;
        }
        return CL_SUCCESS;
    }

    if (nullptr == platform->asRemoteObject()) {
        log<Verbosity::debug>("Getting cl_platform_id from service");
        cl_platform_id calPlatformId{};
        auto ret = Cal::Client::Icd::Ocl::clGetPlatformIDsRpcHelper(1, &calPlatformId, nullptr);
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
        auto platform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
        platforms[0] = platform;
    }

    return CL_SUCCESS;
}

cl_int clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    if (nullptr == platform) {
        return CL_INVALID_PLATFORM;
    }
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
    if (param_name == CL_PLATFORM_NAME && Utils::getCalEnvFlag(calUseCustomOCLPlatformName, false)) {
        return getParamString(calPlatformName.data());
    }

    return clGetPlatformInfoRpcHelper(platform, param_name, param_value_size, param_value, param_value_size_ret);
}

cl_int clGetDeviceInfo(cl_device_id device, cl_device_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    if (param_name == CL_DEVICE_IMAGE_SUPPORT && param_value_size == sizeof(cl_bool) && param_value != nullptr) {
        log<Verbosity::info>("Note: CAL does not support images.");
        *reinterpret_cast<cl_bool *>(param_value) = false;
        if (param_value_size_ret) {
            *param_value_size_ret = sizeof(cl_bool);
        }
        return CL_SUCCESS;
    }

    return clGetDeviceInfoRpcHelper(device, param_name, param_value_size, param_value, param_value_size_ret);
}

cl_int clGetEventInfo(cl_event event, cl_event_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    if (param_name == CL_EVENT_COMMAND_TYPE && param_value_size == sizeof(cl_command_type) && param_value != nullptr) {
        auto commandType = static_cast<IcdOclEvent *>(event)->getCommandType();
        if (commandType != 0) {
            log<Verbosity::debug>("clGetEventInfo(CL_EVENT_COMMAND_TYPE) - overriding commandType %d associated with event %p", event, commandType);
            *reinterpret_cast<cl_command_type *>(param_value) = commandType;
            if (param_value_size_ret) {
                *param_value_size_ret = sizeof(cl_command_type);
            }
            return CL_SUCCESS;
        }
    }
    return clGetEventInfoRpcHelper(event, param_name, param_value_size, param_value, param_value_size_ret);
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
    if (outputBinaries == nullptr) {
        return CL_SUCCESS;
    }

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

    auto ret = clGetProgramInfoRpcHelper(program, param_name, param_value_size, param_value, param_value_size_ret);
    if ((param_name == CL_PROGRAM_NUM_DEVICES) && param_value && (param_value_size == 8)) {
        cl_uint *secondDwordInQword = reinterpret_cast<cl_uint *>(param_value) + 1;
        std::memset(secondDwordInQword, 0x0, sizeof(cl_uint));
    }
    return ret;
}

void *clGetExtensionFunctionAddress(const char *funcname) {
    if (0 == strcmp(funcname, "clIcdGetPlatformIDsKHR")) {
        return reinterpret_cast<void *>(Cal::Client::Icd::Ocl::clIcdGetPlatformIDsKHR);
    }
    return Cal::Client::Icd::Ocl::getAllExtensionFunctionAddress(funcname);
}

void *clGetExtensionFunctionAddressForPlatform(cl_platform_id platform, const char *funcname) {
    return Cal::Client::Icd::Ocl::clGetExtensionFunctionAddress(funcname);
}

cl_context clCreateContext(const cl_context_properties *properties, cl_uint num_devices, const cl_device_id *devices, void(CL_CALLBACK *pfn_notify)(const char *errinfo, const void *private_info, size_t cb, void *user_data), void *user_data, cl_int *errcode_ret) {
    Cal::Rpc::Ocl::ClCreateContextRpcMImplicitArgs implicitArgs = {};
    return Cal::Client::Icd::Ocl::clCreateContextRpcHelper(properties, num_devices, devices, pfn_notify, user_data, errcode_ret, implicitArgs);
}

cl_context clCreateContextFromType(const cl_context_properties *properties, cl_device_type device_type, void(CL_CALLBACK *pfn_notify)(const char *errinfo, const void *private_info, size_t cb, void *user_data), void *user_data, cl_int *errcode_ret) {
    Cal::Rpc::Ocl::ClCreateContextFromTypeRpcMImplicitArgs implicitArgs = {};
    return Cal::Client::Icd::Ocl::clCreateContextFromTypeRpcHelper(properties, device_type, pfn_notify, user_data, errcode_ret, implicitArgs);
}

cl_kernel clCreateKernel(cl_program program, const char *kernel_name, cl_int *errcode_ret) {
    auto kernel = clCreateKernelRpcHelper(program, kernel_name, errcode_ret);
    if (nullptr == kernel) {
        return kernel;
    }
    if (false == static_cast<Cal::Client::Icd::Ocl::IcdOclKernel *>(kernel)->initTraits()) { // need to be called out of RPC handler in order to use RPC
        log<Verbosity::critical>("Failed to initialize kernel traits");
        delete static_cast<Cal::Client::Icd::Ocl::IcdOclKernel *>(kernel);
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
            if (false == static_cast<Cal::Client::Icd::Ocl::IcdOclKernel *>(kernels[i])->initTraits()) { // need to be called out of RPC handler in order to use RPC
                log<Verbosity::critical>("Failed to initialize kernel traits for kernel %d", i);
                for (cl_uint j = 0; j < kernelsToInitialize; ++j) {
                    delete static_cast<Cal::Client::Icd::Ocl::IcdOclKernel *>(kernels[j]);
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
    Cal::Rpc::Ocl::ClSVMAllocRpcMImplicitArgs implicitArgs;
    auto ptr = Cal::Client::Icd::Ocl::clSVMAllocRpcHelper(context, flags, size, alignment, implicitArgs);
    if (nullptr == ptr) {
        return nullptr;
    }
    if (false == Cal::Client::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, ptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open SVM shmem");
        Cal::Client::Icd::Ocl::clMemFreeINTEL(context, ptr);
        ptr = nullptr;
    }
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().registerSharedAlloc(ptr, size, PageFaultManager::Placement::HOST);
    return ptr;
}

void *clHostMemAllocINTEL(cl_context context, const cl_mem_properties_intel *properties, size_t size, cl_uint alignment, cl_int *errcode_ret) {
    Cal::Rpc::Ocl::ClHostMemAllocINTELRpcMImplicitArgs implicitArgs;
    auto ptr = Cal::Client::Icd::Ocl::clHostMemAllocINTELRpcHelper(context, properties, size, alignment, errcode_ret, implicitArgs);
    if (nullptr == ptr) {
        return nullptr;
    }
    if (false == Cal::Client::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, ptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Client::Icd::Ocl::clMemFreeINTEL(context, ptr);
        ptr = nullptr;
        if (errcode_ret) {
            *errcode_ret = CL_OUT_OF_HOST_MEMORY;
        }
    }
    return ptr;
}
void *clSharedMemAllocINTEL(cl_context context, cl_device_id device, const cl_mem_properties_intel *properties, size_t size, cl_uint alignment, cl_int *errcode_ret) {
    if (!Cal::Client::Icd::icdGlobalState.getPageFaultManager().getSharedAllocationsEnabled()) {
        return Cal::Client::Icd::Ocl::clHostMemAllocINTEL(context, properties, size, alignment, errcode_ret);
    }

    Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcMImplicitArgs implicitArgs;
    auto ptr = Cal::Client::Icd::Ocl::clSharedMemAllocINTELRpcHelper(context, device, properties, size, alignment, errcode_ret, implicitArgs);
    if (nullptr == ptr) {
        return nullptr;
    }
    if (false == Cal::Client::Icd::icdGlobalState.getOclPlatform()->openNewUsmHostOrSharedPointer(context, ptr, implicitArgs.shmem_resource, implicitArgs.offset_within_resource, implicitArgs.aligned_size)) {
        log<Verbosity::error>("Failed to open USM shared/host shmem");
        Cal::Client::Icd::Ocl::clMemFreeINTEL(context, ptr);
        ptr = nullptr;
        if (errcode_ret) {
            *errcode_ret = CL_OUT_OF_HOST_MEMORY;
        }
        return ptr;
    }
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().registerSharedAlloc(ptr, size, getSharedAllocationPlacement(properties));
    return ptr;
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
    if ((flags & CL_MEM_USE_HOST_PTR) && Cal::Client::Icd::icdGlobalState.getMallocShmemExporter().isRegionSharable(host_ptr, size)) {
        retMem = clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem(context, flags, size, host_ptr, errcode_ret);
    } else {
        auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
        auto host_ptr_pointer_type = globalPlatform->getPointerType(host_ptr);
        if (host_ptr_pointer_type == PointerType::usm) {
            retMem = clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem(context, flags, size, host_ptr, errcode_ret);
        } else {
            std::unique_ptr<void, std::function<void(void *)>> standaloneHostPtrAlloc{static_cast<IcdOclContext *>(context)->getStagingAreaManager().allocateStagingArea(size), [context](void *ptrToMarkAsUnused) { static_cast<IcdOclContext *>(context)->getStagingAreaManager().deallocateStagingArea(ptrToMarkAsUnused); }};
            void *standaloneHostPtr = standaloneHostPtrAlloc.get();
            memcpy(Cal::Utils::toAddress(standaloneHostPtr), host_ptr, host_ptr ? size : 0u);
            auto useHostPtrFlags = flags & (~(CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR));
            useHostPtrFlags |= CL_MEM_USE_HOST_PTR;
            retMem = clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem(context, useHostPtrFlags, size, standaloneHostPtr, errcode_ret);
            retMem->asLocalObject()->standaloneHostPtrAllocation = std::move(standaloneHostPtrAlloc);
        }
    }
    retMem->asLocalObject()->apiHostPtr = host_ptr;
    retMem->asLocalObject()->size = size;
    retMem->asLocalObject()->flags = flags;
    retMem->asLocalObject()->parent = context->asLocalObject();
    return retMem;
}

cl_mem clCreateSubBuffer(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info, cl_int *errcode_ret) {
    auto retMem = clCreateSubBufferRpcHelper(buffer, flags, buffer_create_type, buffer_create_info, errcode_ret);
    retMem->asLocalObject()->size = reinterpret_cast<const cl_buffer_region *>(buffer_create_info)->size;
    /* Inherit some flags if we do not set. */
    auto parentFlags = buffer->asLocalObject()->flags;
    if ((flags & (CL_MEM_WRITE_ONLY | CL_MEM_READ_ONLY | CL_MEM_READ_WRITE)) == 0) {
        flags |= parentFlags & (CL_MEM_WRITE_ONLY | CL_MEM_READ_ONLY | CL_MEM_READ_WRITE);
    }
    if ((flags & (CL_MEM_HOST_WRITE_ONLY | CL_MEM_HOST_READ_ONLY | CL_MEM_HOST_NO_ACCESS)) == 0) {
        flags |= parentFlags & (CL_MEM_HOST_WRITE_ONLY | CL_MEM_HOST_READ_ONLY |
                                CL_MEM_HOST_NO_ACCESS);
    }
    flags |= parentFlags & (CL_MEM_USE_HOST_PTR | CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR);
    auto parentHostPtr = buffer->asLocalObject()->apiHostPtr;
    auto origin = static_cast<const cl_buffer_region *>(buffer_create_info)->origin;
    retMem->asLocalObject()->apiHostPtr = Cal::Utils::moveByBytes(parentHostPtr, origin);
    retMem->asLocalObject()->flags = flags;
    retMem->asLocalObject()->parentMemObj = buffer->asLocalObject();
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

    if (Cal::Client::Icd::icdGlobalState.isCacheEnabled()) {
        cacheRet = oclKernel->clSetKernelArgCache.findCachedKernelArg(arg_index, arg_size, arg_value);
    }

    cl_int ret = CL_SUCCESS;

    if (cacheRet == oclKernel->clSetKernelArgCache.cache.end()) {
        ret = CL_INVALID_ARG_VALUE;
        auto argTrait = oclKernel->getArgumentTrait(arg_index);
        if (argTrait && argTrait->isPointer) {
            if ((arg_value != nullptr) && (sizeof(arg_size) == sizeof(cl_mem))) {
                auto oclMemObj = static_cast<IcdOclMem *>(*reinterpret_cast<const cl_mem *>(arg_value));
                if (oclMemObj != nullptr) {
                    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
                    if (globalPlatform->getPointerType(oclMemObj->apiHostPtr) == PointerType::usm) {
                        log<Verbosity::debug>("clSetKernelArg called on buffer with USM ptr %p -> falling back to clSetKernelArgMemPointerINTEL", oclMemObj->apiHostPtr);
                        ret = Cal::Client::Icd::Ocl::clSetKernelArgMemPointerINTELRpcHelper(kernel, arg_index, oclMemObj->apiHostPtr);
                    }
                }
            }
        }
        if (ret != CL_SUCCESS) {
            ret = Cal::Client::Icd::Ocl::clSetKernelArgRpcHelper(kernel, arg_index, arg_size, arg_value);
        }

        if (Cal::Client::Icd::icdGlobalState.isCacheEnabled()) {
            oclKernel->clSetKernelArgCache.cacheKernelArg(arg_index, arg_size, arg_value);
        }
    }

    return ret;
}

cl_int clWaitForEvents(cl_uint num_events, const cl_event *event_list) {
    if (!Cal::Client::Icd::icdGlobalState.getOclPlatform()->hasCallbacksHandler()) {
        log<Verbosity::debug>("clWaitForEvents - callbacks handler is not enabled");
        return Cal::Client::Icd::Ocl::clWaitForEventsRpcHelper(num_events, event_list);
    } else {
        log<Verbosity::debug>("clWaitForEvents - callbacks handler is enabled, will poll event status with clGetEventInfo");
        log<Verbosity::performance>("clWaitForEvents - will use busy polling with clGetEventInfo for callbacks support");
        bool eventStatusError = false;
        for (cl_uint i = 0; i < num_events;) {
            cl_int eventStatus = CL_COMPLETE;
            cl_int ret = Cal::Client::Icd::Ocl::clGetEventInfo(event_list[i], CL_EVENT_COMMAND_EXECUTION_STATUS, sizeof(eventStatus), &eventStatus, nullptr);
            if (ret != CL_SUCCESS) {
                log<Verbosity::error>("clWaitForEvent - failed to get event[%d] status with clGetEventInfo : err=%d", i, ret);
                return ret;
            }
            if (eventStatus < 0) {
                log<Verbosity::bloat>("clWaitForEvents - event[%d] is in error state", i);
                eventStatusError = true;
            } else if (eventStatus != CL_COMPLETE) {
                log<Verbosity::bloat>("clWaitForEvents - event[%d] is not complete", i);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            } else {
                log<Verbosity::bloat>("clWaitForEvents - event[%d] is complete", i);
            }
            ++i;
        }
        log<Verbosity::bloat>("clWaitForEvents - all events are complete (%d)", num_events);
        return eventStatusError ? CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST : CL_SUCCESS;
    }
}

cl_int clSetKernelArgMemPointerINTEL(cl_kernel kernel, cl_uint argIndex, const void *argValue) {
    log<Verbosity::bloat>("Establishing RPC for clSetKernelArgMemPointerINTEL");
    auto oclKernel = static_cast<IcdOclKernel *>(kernel);
    oclKernel->storeKernelArg(argValue, argIndex);
    auto cacheRet = oclKernel->clSetKernelArgCache.cache.end();

    if (Cal::Client::Icd::icdGlobalState.isCacheEnabled()) {
        cacheRet = oclKernel->clSetKernelArgCache.findCachedKernelArg(argIndex, 0u, argValue);
    }

    cl_int ret = CL_SUCCESS;

    if (cacheRet == oclKernel->clSetKernelArgCache.cache.end()) {
        ret = Cal::Client::Icd::Ocl::clSetKernelArgMemPointerINTELRpcHelper(kernel, argIndex, argValue);

        if (Cal::Client::Icd::icdGlobalState.isCacheEnabled()) {
            oclKernel->clSetKernelArgCache.cacheKernelArg(argIndex, 0u, argValue);
        }
    } else {
        ret = CL_SUCCESS;
    }
    return ret;
}

cl_int clSetKernelArgSVMPointer(cl_kernel kernel, cl_uint argIndex, const void *argValue) {
    return Cal::Client::Icd::Ocl::clSetKernelArgMemPointerINTEL(kernel, argIndex, argValue);
}

cl_int clGetMemObjectInfo(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
    switch (param_name) {
    case CL_MEM_FLAGS:
        if (param_value_size_ret) {
            *param_value_size_ret = sizeof(cl_mem_flags);
        }
        if (param_value) {
            *static_cast<cl_mem_flags *>(param_value) = memobj->asLocalObject()->flags;
        }
        return CL_SUCCESS;
    case CL_MEM_SIZE:
        if (param_value_size_ret) {
            *param_value_size_ret = sizeof(size_t);
        }
        if (param_value) {
            *static_cast<size_t *>(param_value) = memobj->asLocalObject()->size;
        }
        return CL_SUCCESS;
    case CL_MEM_HOST_PTR:
        if (param_value_size_ret) {
            *param_value_size_ret = sizeof(void *);
        }
        if (param_value) {
            *static_cast<uintptr_t *>(param_value) = reinterpret_cast<uintptr_t>(memobj->asLocalObject()->apiHostPtr);
        }
        return CL_SUCCESS;
    default:
        break;
    }

    return Cal::Client::Icd::Ocl::clGetMemObjectInfoRpcHelper(memobj, param_name, param_value_size, param_value, param_value_size_ret);
}

void *IcdOclPlatform::translateMappedPointer(cl_mem buffer, void *ptr, size_t offset) {
    if (isUsmHostOrShared(ptr)) {
        auto apiHostPtr = buffer->asLocalObject()->apiHostPtr;
        if (apiHostPtr && (buffer->asLocalObject()->flags & CL_MEM_USE_HOST_PTR)) {
            auto parentMemObj = buffer->asLocalObject()->parentMemObj;
            if (parentMemObj) {
                auto standaloneHostPtr = parentMemObj->asLocalObject()->standaloneHostPtrAllocation.get();
                if (standaloneHostPtr) {
                    memcpy(parentMemObj->asLocalObject()->apiHostPtr, standaloneHostPtr, parentMemObj->asLocalObject()->size);
                    return Cal::Utils::moveByBytes(apiHostPtr, offset);
                }
            } else {
                auto standaloneHostPtr = buffer->asLocalObject()->standaloneHostPtrAllocation.get();
                if (standaloneHostPtr) {
                    memcpy(apiHostPtr, standaloneHostPtr, buffer->asLocalObject()->size);
                    return Cal::Utils::moveByBytes(apiHostPtr, offset);
                }
            }
        }
        return ptr;
    }

    if (globalState.getMallocShmemExporter().isRegionSharable(ptr, 4)) {
        return reinterpret_cast<char *>(buffer->asLocalObject()->apiHostPtr) + offset;
    }
    return nullptr;
}

void *IcdOclPlatform::translateUnMappedPointer(cl_mem buffer, void *ptr) {
    auto apiHostPtr = buffer->asLocalObject()->apiHostPtr;
    if (apiHostPtr && (buffer->asLocalObject()->flags & CL_MEM_USE_HOST_PTR)) {
        auto parentMemObj = buffer->asLocalObject()->parentMemObj;
        if (parentMemObj) {
            auto standaloneHostPtr = parentMemObj->asLocalObject()->standaloneHostPtrAllocation.get();
            if (standaloneHostPtr) {
                memcpy(standaloneHostPtr, parentMemObj->asLocalObject()->apiHostPtr, parentMemObj->asLocalObject()->size);
                auto offset = Cal::Utils::byteDistanceAbs(ptr, parentMemObj->asLocalObject()->apiHostPtr);
                return Cal::Utils::moveByBytes(standaloneHostPtr, offset);
            }
        } else {
            auto standaloneHostPtr = buffer->asLocalObject()->standaloneHostPtrAllocation.get();
            if (standaloneHostPtr) {
                memcpy(standaloneHostPtr, apiHostPtr, buffer->asLocalObject()->size);
                auto offset = Cal::Utils::byteDistanceAbs(ptr, apiHostPtr);
                return Cal::Utils::moveByBytes(standaloneHostPtr, offset);
            }
        }
    }
    return ptr;
}

void IcdOclPlatform::handleCallbacks(IcdOclPlatform *platform) {
    log<Verbosity::debug>("Starting callbacks handler");
    auto &channel = platform->getRpcChannel();
    while (true) {
        log<Verbosity::debug>("Waiting for callbacks");
        auto status = channel.waitForCallbacks();
        if (!status) {
            auto callbackId = channel.peekCompletedCallbackId();
            log<Verbosity::debug>("Terminating callbacks handler - fptr : 0x%llx, handle : 0x%llx, subType : %d", callbackId.fptr, callbackId.handle, callbackId.src.subtype);
        }

        auto callbackId = channel.popCompletedCallbackId();
        if (0 == callbackId.fptr) {
            log<Verbosity::debug>("Received null callback notification for message subType : %d", callbackId.src.subtype);
            break;
        }
        switch (callbackId.src.subtype) {
        default:
            log<Verbosity::error>("Unknown callback signature for message subType : %d", callbackId.src.subtype);
            break;
        case Cal::Rpc::Ocl::ClCreateContextRpcM::messageSubtype:
        case Cal::Rpc::Ocl::ClCreateContextFromTypeRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto context = reinterpret_cast<cl_context>(callbackId.handle);
            platform->translateRemoteObjectToLocalObject(context);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(const char *errinfo, const void *private_info, size_t cb, void *user_data)>(callbackId.fptr);
            auto oclContext = static_cast<IcdOclContext *>(context);
            auto errorInfo = reinterpret_cast<const char *>(oclContext->notifyErrInfoMem.get());
            fptr(errorInfo, nullptr, 0, userData);
            break;
        }
        case Cal::Rpc::Ocl::ClSetEventCallbackRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto event = reinterpret_cast<cl_event>(callbackId.handle);
            platform->translateRemoteObjectToLocalObject(event);
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(cl_event event, cl_int event_command_status, void *user_data)>(callbackId.fptr);
            auto commandExecCallbackType = static_cast<cl_int>(callbackId.notificationFlags);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            fptr(event, commandExecCallbackType, userData);
            break;
        }
        case Cal::Rpc::Ocl::ClLinkProgramRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto program = reinterpret_cast<cl_program>(callbackId.handle);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            auto wrappedData = reinterpret_cast<UserDataLinkProgram *>(userData);
            platform->translateNewRemoteObjectToLocalObject(program, wrappedData->parentContext->asLocalObject());
            void *originalUserData = wrappedData->originalUserData;
            delete wrappedData;
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(cl_program program, void *user_data)>(callbackId.fptr);
            fptr(program, originalUserData);
            break;
        }
        case Cal::Rpc::Ocl::ClSetContextDestructorCallbackRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto context = reinterpret_cast<cl_context>(callbackId.handle);
            platform->translateRemoteObjectToLocalObject(context);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(cl_context context, void *user_data)>(callbackId.fptr);
            fptr(context, userData);
            context->asLocalObject()->dec();
            break;
        }
        case Cal::Rpc::Ocl::ClSetMemObjectDestructorCallbackRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto memobj = reinterpret_cast<cl_mem>(callbackId.handle);
            platform->translateRemoteObjectToLocalObject(memobj);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(cl_mem memobj, void *user_data)>(callbackId.fptr);
            fptr(memobj, userData);
            memobj->asLocalObject()->dec();
            break;
        }
        case Cal::Rpc::Ocl::ClBuildProgramRpcM::messageSubtype:
        case Cal::Rpc::Ocl::ClCompileProgramRpcM::messageSubtype:
        case Cal::Rpc::Ocl::ClSetProgramReleaseCallbackRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto program = reinterpret_cast<cl_program>(callbackId.handle);
            platform->translateRemoteObjectToLocalObject(program);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(cl_program program, void *user_data)>(callbackId.fptr);
            fptr(program, userData);
            break;
        }
        case Cal::Rpc::Ocl::ClEnqueueSVMFreeRpcM::messageSubtype: {
            log<Verbosity::debug>("Received callback notification for message subType : %d", callbackId.src.subtype);
            auto commandQueue = reinterpret_cast<cl_command_queue>(callbackId.handle);
            auto userData = reinterpret_cast<void *>(callbackId.data);
            auto wrappedData = reinterpret_cast<UserDataClEnqueueSVMFree *>(userData);
            platform->translateRemoteObjectToLocalObject(commandQueue);
            void *originalUserData = wrappedData->originalUserData;
            auto numSvmPointers = wrappedData->numSvmPointers;
            auto svmPointers = wrappedData->svmPointers;
            delete wrappedData;
            auto fptr = reinterpret_cast<void(CL_CALLBACK *)(cl_command_queue queue, cl_uint num_svm_pointers, void *svm_pointers[], void *user_data)>(callbackId.fptr);
            fptr(commandQueue, numSvmPointers, svmPointers, originalUserData);
            break;
        }
        }
    }
    log<Verbosity::debug>("Finished callbacks handler");
}

void IcdOclPlatform::enableCallbacksHandler() {
    static std::once_flag initialized = {};

    std::call_once(initialized, [this]() {
        log<Verbosity::debug>("Enabling callbacks handler");
        log<Verbosity::performance>("Enabling callbacks handler");
        this->hasCallbacksFlag.store(true);
        this->callbacksHandler = std::async(std::launch::async, IcdOclPlatform::handleCallbacks, this);
    });
}

void IcdOclPlatform::terminateCallbacksHandler() {
    log<Verbosity::debug>("Terminating callbacks handler");
    callbacksHandler.wait();
    this->hasCallbacksFlag.store(false);
}

bool IcdOclPlatform::hasCallbacksHandler() {
    return hasCallbacksFlag.load();
}

IcdOclContext::IcdOclContext(cl_context remoteObject, Cal::Shared::SingleReference &&parent,
                             Cal::Shared::RefCounted<_cl_context, IcdOclTypePrinter>::CleanupFuncT cleanupFunc)
    : Cal::Shared::RefCountedWithParent<_cl_context, IcdOclTypePrinter>(remoteObject, std::move(parent), cleanupFunc),
      stagingAreaManager([this](size_t size) { return this->allocateStagingArea(size); }, [this](void *ptr) { return this->deallocateStagingAreas(ptr); }) {
    Cal::Client::Icd::icdGlobalState.registerAtExit(this, [this](const void *key) { this->globalReleaseCallback(); });
    this->skipTransferOnHostPtrMatch = Cal::Utils::getCalEnvFlag(calIcdBufferRecycleEnvName);
}

void IcdOclContext::beforeReleaseCallback() {
    if (1 == this->peekRefCount()) {
        this->getStagingAreaManager().clearStagingAreaAllocations();
        clBufferRecycler.cleanup();
        if (implicitQueue) {
            Cal::Client::Icd::Ocl::clReleaseCommandQueue(implicitQueue);
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
            auto err = Cal::Client::Icd::Ocl::clEnqueueWriteBuffer(implicitQueue, recycledBuffer, CL_TRUE, 0, size, host_ptr, 0U, nullptr, nullptr);
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
            implicitQueue = Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], properties, nullptr);
            if (implicitQueue != nullptr) {
                log<Verbosity::debug>("Created implicit command queue with family: %d and index %d", queueFamily, queueIndex);
            }
        } while (implicitQueue == nullptr && signedQueueIndex >= 0);
        if (implicitQueue == nullptr) {
            queueFamily = 2u;
            queueIndex = 0u;
            implicitQueue = Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], properties, nullptr);
            if (implicitQueue != nullptr) {
                log<Verbosity::debug>("Created implicit command queue with family: %d and index %d", queueFamily, queueIndex);
            }
        }
        if (implicitQueue == nullptr) {
            queueFamily = 0u;
            signedQueueIndex = 3u;
            do {
                queueIndex = signedQueueIndex--;
                implicitQueue = Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], properties, nullptr);
                if (implicitQueue != nullptr) {
                    log<Verbosity::debug>("Created implicit command queue with family: %d and index %d", queueFamily, queueIndex);
                }
            } while (implicitQueue == nullptr && signedQueueIndex >= 0);
        }
        if (implicitQueue == nullptr) {
            implicitQueue = Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties(this, devices[0], nullptr, nullptr);
            if (implicitQueue != nullptr) {
                log<Verbosity::debug>("Created implicit command queue without properties");
            }
        }
        if (nullptr == implicitQueue) {
            log<Verbosity::error>("Could not create implicit queue");
        }
    }
}

void *IcdOclContext::allocateStagingArea(size_t size) {
    cl_int cl_err{};
    void *usmHostMem = Cal::Client::Icd::Ocl::clHostMemAllocINTEL(this->asLocalObject(), nullptr, size, 0, &cl_err);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::critical>("Failed to allocate staging buffer via clHostMemAllocINTEL of size %zu", size);
        return nullptr;
    }

    return usmHostMem;
}

void IcdOclContext::deallocateStagingAreas(void *ptr) {
    Cal::Client::Icd::Ocl::clMemFreeINTEL(this->asLocalObject(), ptr);
}

bool IcdOclKernel::initTraits() {
    cl_uint numArgs = 0;
    if (CL_SUCCESS != Cal::Client::Icd::Ocl::clGetKernelInfo(this, CL_KERNEL_NUM_ARGS, sizeof(numArgs), &numArgs, 0)) {
        return false;
    }
    this->argsTraits.reserve(numArgs);
    std::vector<char> argType(128);
    // note : taking advantage that NEO exposes kernel arg info even without -cl-kernel-arg-info build option
    for (cl_uint i = 0; i < numArgs; ++i) {
        ArgTraits argTraits;
        size_t typeLen = 0;
        auto err = Cal::Client::Icd::Ocl::clGetKernelArgInfo(this, i, CL_KERNEL_ARG_TYPE_NAME, argType.size(), argType.data(), &typeLen);
        if ((CL_SUCCESS != err) && (typeLen < argType.size())) {
            if (typeLen <= argType.size()) {
                return false;
            }
            argType.resize(typeLen);
            err = Cal::Client::Icd::Ocl::clGetKernelArgInfo(this, i, CL_KERNEL_ARG_TYPE_NAME, argType.size(), argType.data(), &typeLen);
            if (CL_SUCCESS != err) {
                return false;
            }
        }

        if (strstr(argType.data(), "*") || strstr(argType.data(), "__opaque_ptr")) {
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
        Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllAllocationsToGpu();
    } else {
        for (auto &alloc : this->allocationsToMigrate) {
            Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(alloc);
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

template <typename OclObjectT>
void objectCleanup(void *remote, void *local) {
    Cal::Client::Icd::icdGlobalState.getOclPlatform()->removeObjectFromMap(static_cast<OclObjectT>(remote), static_cast<OclObjectT>(local));
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
} // namespace Client::Icd
} // namespace Cal
