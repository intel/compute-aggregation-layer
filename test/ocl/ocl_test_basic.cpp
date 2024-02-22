/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "shared/log.h"
#include "shared/ocl_wrapper.h"
#include "test/utils/ocl_common_steps.h"

#include <algorithm>
#include <cstdio>
#include <string_view>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>

bool testCreateCommandQueueWithProperties(cl_context context, cl_device_id dev) {
    auto testAndFreeQueue = [](cl_command_queue queue, cl_command_queue_properties properties, cl_int cl_err) -> bool {
        if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
            log<Verbosity::error>("Failed to create command queue with error : %d", cl_err);
            return false;
        };
        cl_command_queue_properties queriedProps = 0;
        cl_err = clGetCommandQueueInfo(queue, CL_QUEUE_PROPERTIES, sizeof(queriedProps), &queriedProps, nullptr);
        if (CL_SUCCESS != cl_err) {
            log<Verbosity::error>("Failed to clGetCommandQueueInfo with error : %d", cl_err);
            return false;
        }

        if ((0 != (properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)) && (0 == (queriedProps & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE))) {
            log<Verbosity::error>("CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE missing in queue properties");
        }

        if ((0 != (properties & CL_QUEUE_PROFILING_ENABLE)) && (0 == (queriedProps & CL_QUEUE_PROFILING_ENABLE))) {
            log<Verbosity::error>("CL_QUEUE_PROFILING_ENABLE missing in queue properties");
        }

        cl_err = clReleaseCommandQueue(queue);
        if (CL_SUCCESS != cl_err) {
            log<Verbosity::error>("Failed to release command queue with error : %d", cl_err);
            return false;
        }
        return true;
    };

    cl_int cl_err = CL_SUCCESS;
    cl_command_queue_properties configs[] = {0, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, CL_QUEUE_PROFILING_ENABLE, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE};

    for (auto c : configs) {
        log<Verbosity::info>("Creating cl_command_queue object with properties : %llu", c);

        log<Verbosity::info>(" * clCreateCommandQueue");
        cl_command_queue queue = clCreateCommandQueue(context, dev, c, &cl_err);
        if (false == testAndFreeQueue(queue, c, cl_err)) {
            return false;
        }

        log<Verbosity::info>(" * clCreateCommandQueueWithProperties+queuePropertiesStringSingle");
        cl_command_queue_properties queuePropertiesStringSingle[] = {CL_QUEUE_PROPERTIES, c, 0};
        queue = clCreateCommandQueueWithProperties(context, dev, queuePropertiesStringSingle, &cl_err);
        if (false == testAndFreeQueue(queue, c, cl_err)) {
            return false;
        }

        log<Verbosity::info>(" * clCreateCommandQueueWithProperties+queuePropertiesStringMultipleBefore");
        cl_command_queue_properties queuePropertiesStringMultipleBefore[] = {CL_QUEUE_PROPERTIES, c, CL_QUEUE_THROTTLE_KHR, CL_QUEUE_THROTTLE_HIGH_KHR, 0};
        queue = clCreateCommandQueueWithProperties(context, dev, queuePropertiesStringMultipleBefore, &cl_err);
        if (false == testAndFreeQueue(queue, c, cl_err)) {
            return false;
        }

        log<Verbosity::info>(" * clCreateCommandQueueWithProperties+queuePropertiesStringMultipleAfter");
        cl_command_queue_properties queuePropertiesStringMultipleAfter[] = {CL_QUEUE_THROTTLE_KHR, CL_QUEUE_THROTTLE_HIGH_KHR, CL_QUEUE_PROPERTIES, c, 0};
        queue = clCreateCommandQueueWithProperties(context, dev, queuePropertiesStringMultipleAfter, &cl_err);
        if (false == testAndFreeQueue(queue, c, cl_err)) {
            return false;
        }
    }

    log<Verbosity::info>("Succesfully tested testCreateCommandQueueWithProperties");
    return true;
}

struct CallbackMessage {
    bool wasCalled = false;
    cl_event ev = nullptr;
    cl_int eventCommandStatus = -1;
    void *userData = nullptr;
    std::mutex lock;
};

void CL_CALLBACK callback(cl_event event, cl_int eventCommandStatus, void *userData) {
    auto message = reinterpret_cast<CallbackMessage *>(userData);
    auto lock = std::lock_guard<std::mutex>(message->lock);
    message->wasCalled = true;
    message->eventCommandStatus = eventCommandStatus;
    message->userData = userData;
    message->ev = event;
}

bool testEventProfiling(cl_context context, cl_device_id dev) {
    log<Verbosity::info>("Creating cl_command_queue object with profiling enabled ");
    cl_int cl_err = CL_SUCCESS;
    cl_command_queue_properties queueProperties[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
    auto queue = clCreateCommandQueueWithProperties(context, dev, queueProperties, &cl_err);
    if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create command queue with profiling enabled. Error : %d", cl_err);
        return false;
    };

    cl_event ev = {};

    if (CL_SUCCESS != clEnqueueBarrierWithWaitList(queue, 0, nullptr, &ev)) {
        log<Verbosity::error>("Failed to enqueue barrier with waitlist");
        return false;
    }
    log<Verbosity::info>("Succesfully enqueued barrier with waitlist");
    if (nullptr == ev) {
        log<Verbosity::error>("Returned event is empty");
        return false;
    }

    CallbackMessage message;
    if (CL_SUCCESS != clSetEventCallback(ev, CL_COMPLETE, callback, &message)) {
        log<Verbosity::error>("Failed to set callback");
        return false;
    }
    log<Verbosity::info>("Succesfully set-up callback");

    clWaitForEvents(1, &ev);

    cl_ulong info = std::numeric_limits<cl_ulong>::max();
    cl_err = clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &info, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to clGetEventProfilingInfo with error : %d", cl_err);
        return false;
    }
    if (std::numeric_limits<cl_ulong>::max() == info) {
        log<Verbosity::info>("Event profiling info, CL_PROFILING_COMMAND_QUEUED is invalid : %lu", info);
        return false;
    }
    log<Verbosity::info>("Event profiling info, CL_PROFILING_COMMAND_QUEUED : %lu", info);

    {
        log<Verbosity::info>("Checking for callback on event : %p", ev);
        bool callbackReceived = false;
        for (int i = 0; i < 5; ++i) {
            {
                auto lock = std::unique_lock<std::mutex>(message.lock);
                if (false == message.wasCalled) {
                    lock.unlock();
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1s);
                    log<Verbosity::info>("Checking for callback on event : %p (retry #%d)", ev, i + 1);
                    continue; // retry
                }
            }
            log<Verbosity::info>("Callback received for event : %p", ev);
            if ((ev != message.ev) || (CL_COMPLETE != message.eventCommandStatus) || (&message != message.userData)) {
                log<Verbosity::error>("Callback payload is invalid");
                return false;
            }

            log<Verbosity::info>("Callback was successful after %ds", i);
            callbackReceived = true;
        }
        if (false == callbackReceived) {
            log<Verbosity::error>("Failed to receive callback");
            return false;
        }
    }

    if (CL_SUCCESS != clReleaseEvent(ev)) {
        log<Verbosity::error>("Failed to release event");
        return false;
    }

    if (CL_SUCCESS != clReleaseCommandQueue(queue)) {
        log<Verbosity::error>("Failed to release command queue");
        return false;
    }

    log<Verbosity::info>("Succesfully tested testEventProfiling");
    return true;
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::bloat);

    int platformOrd = -1;
    int forkNum = 0;
    bool skipStressTests = false;
    std::vector<pid_t> childProcesses;
    for (int i = 0; i < argc; ++i) {
        if (0 == strcmp(argv[i], "--platform_ordinal")) {
            if (i + 1 == argc) {
                log<Verbosity::info>("Expected integer parameter after --platform_ordinal");
                return -1;
            }
            platformOrd = atoi(argv[i + 1]);
            i++;
        } else if (0 == strcmp(argv[i], "--fork")) {
            if (i + 1 == argc) {
                log<Verbosity::info>("Expected integer parameter after --fork");
                return -1;
            }
            forkNum = atoi(argv[i + 1]);
            i++;
        } else if (0 == strcmp(argv[i], "--skip_stress")) {
            skipStressTests = true;
        }
    }

    if (forkNum) {
        log<Verbosity::info>("Forking (requested fork num : %d) ...\n", forkNum);
        for (int i = 0; i < forkNum; ++i) {
            pid_t childPid = fork();
            if (0 == childPid) {
                childProcesses.clear();
                break;
            }
            if (-1 == childPid) {
                log<Verbosity::error>("Fork #%d/%d failed", i + 1, forkNum);
            } else {
                log<Verbosity::info>("Fork #%d/%d successful, child : %d", i + 1, forkNum, childPid);
                childProcesses.push_back(childPid);
            }
        }
    }

    auto platform = getPlatform(platformOrd);
    auto devices = getDevices(platform, CL_DEVICE_TYPE_ALL);
    size_t deviceIndex = 0;

    cl_bool imageSupport = true;
    auto clGetDeviceInfoForImageSupportResult = clGetDeviceInfo(devices[deviceIndex], CL_DEVICE_IMAGE_SUPPORT, sizeof(imageSupport), &imageSupport, NULL);
    if (clGetDeviceInfoForImageSupportResult != CL_SUCCESS) {
        log<Verbosity::error>("Failed to get device info for image support");
        return -1;
    }
    if (imageSupport) {
        if (-1 == platformOrd) {
            log<Verbosity::error>("CAL support for images should be disabled.");
            return -1;
        }
    }

    auto context = createContext(platform, devices, deviceIndex);
    cl_int cl_err{};

    const char *f0 = "int f0(int a) { return a + 5; }";
    const char *f1 = "int f1(int a) { return a*5; }";
    const char *k = "__kernel void k(__global int *x, int y) { *x = f0(*x)*f1(*x) + y; }";
    const char *g = "__global int my_special_global_var = 5;";
    const char *h = "__kernel void exchange_special_global_var(__global int* old_ret, int new_val) { *old_ret = my_special_global_var; my_special_global_var = new_val; }";
    const char *src[] = {f0, f1, k, g, h};
    auto program = createProgramWithSource(context, 5, src);
    compileProgram(program, devices[deviceIndex]);
    auto linkedProgram = linkProgram(context, devices[deviceIndex], program);

    log<Verbosity::info>("Trying to get an address of 'clGetDeviceGlobalVariablePointerINTEL' extension!");
    void *clGetDeviceGlobalVariablePointerINTELAddress = clGetExtensionFunctionAddress("clGetDeviceGlobalVariablePointerINTEL");
    if (!clGetDeviceGlobalVariablePointerINTELAddress) {
        log<Verbosity::error>("Could not get an address of 'clGetDeviceGlobalVariablePointerINTEL' extension!");
        return -1;
    }
    log<Verbosity::info>("Successfuly got an address of 'clGetDeviceGlobalVariablePointerINTEL' extension!");

    using ClGetDeviceGlobalVariablePointerINTELFun = cl_int(cl_device_id, cl_program, const char *, size_t *, void **);
    const auto clGetDeviceGlobalVariablePointerINTEL = reinterpret_cast<ClGetDeviceGlobalVariablePointerINTELFun *>(clGetDeviceGlobalVariablePointerINTELAddress);

    log<Verbosity::info>("Trying to get an address of a global variable with name 'my_special_global_var'");
    size_t globalVarSize{};
    void *globalVarPtr{};
    cl_int clGetDeviceGlobalVariablePointerINTELResult = clGetDeviceGlobalVariablePointerINTEL(devices[deviceIndex], linkedProgram, "my_special_global_var", &globalVarSize, &globalVarPtr);
    if (clGetDeviceGlobalVariablePointerINTELResult != CL_SUCCESS) {
        log<Verbosity::error>("Could not get a global pointer for 'my_special_global_var' variable!");
        return -1;
    }

    log<Verbosity::info>("Got global pointer for 'my_special_global_var' variable. Size: %d, Addres: %p", globalVarSize, globalVarPtr);

    log<Verbosity::info>("Getting compiled program binaries from service!");

    std::vector<std::vector<unsigned char>> programBinariesStorage(devices.size(), std::vector<unsigned char>{});
    std::vector<unsigned char *> programBinaries(devices.size(), nullptr);
    std::vector<size_t> binariesSizes(devices.size(), 0);

    auto clGetProgramInfoResult = clGetProgramInfo(linkedProgram, CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * devices.size(), binariesSizes.data(), nullptr);
    if (clGetProgramInfoResult != CL_SUCCESS) {
        log<Verbosity::error>("Could not get sizes of compiled program binaries from the service!");
        return -1;
    }

    for (auto i = 0u; i < binariesSizes.size(); ++i) {
        programBinariesStorage[i].resize(binariesSizes[i], 'F');
        programBinaries[i] = programBinariesStorage[i].data();
    }

    size_t size = 0;
    clGetProgramInfoResult = clGetProgramInfo(linkedProgram, CL_PROGRAM_BINARIES, 0, nullptr, &size);
    if (clGetProgramInfoResult != CL_SUCCESS) {
        log<Verbosity::error>("Sanity check for getting program binaries with null param value failed!");
        return -1;
    }

    clGetProgramInfoResult = clGetProgramInfo(linkedProgram, CL_PROGRAM_BINARIES, sizeof(char *) * devices.size(), programBinaries.data(), nullptr);
    if (clGetProgramInfoResult != CL_SUCCESS) {
        log<Verbosity::error>("Could not get compiled program binaries from the service!");
        return -1;
    }

    log<Verbosity::info>("clGetProgramInfo(..., CL_PROGRAM_BINARIES, ...) was successful! Checking binaries...");

    if (programBinaries[0] != programBinariesStorage[0].data()) {
        log<Verbosity::info>("CAL modified program binaries pointers. This should not be done!");
        return -1;
    }

    const std::vector<unsigned char> junkBinaryMem(binariesSizes[0], 'F');
    if (programBinariesStorage[0] == junkBinaryMem) {
        log<Verbosity::info>("Binary was not written to its storage!");
        return -1;
    }

    log<Verbosity::info>("Binaries passed validation!");

    const auto programFromBinary = createProgramWithBinary(context, devices[deviceIndex], binariesSizes.data(), programBinaries.data());
    auto kernel = createKernel(linkedProgram, "k");

    Cal::Utils::OclApiWrapper::KernelInfo kernelInfo;
    if (false == kernelInfo.read(kernel)) {
        log<Verbosity::error>("Could not read kernel info");
        return 1;
    }
    log<Verbosity::info>("Kernel arg info : \n%s\n", kernelInfo.str().c_str());
    for (uint32_t i = 0; i < kernelInfo.info<CL_KERNEL_NUM_ARGS>(); ++i) {
        Cal::Utils::OclApiWrapper::KernelArgInfo kernelArgInfo = {};
        if (false == kernelArgInfo.read(kernel, i)) {
            log<Verbosity::error>("Could not read kernel arg info (%d)", i);
            return 1;
        }
        log<Verbosity::info>("Kernel arg info (%d) : \n%s\n", i, kernelArgInfo.str().c_str());
    }

    log<Verbosity::info>("Creating cl_mem object #1");
    int initData = 3;
    cl_mem mem = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData, &cl_err);
    if ((nullptr == mem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create cl_mem object #1 with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_mem : %p", mem);

    log<Verbosity::info>("Releasing cl_mem for reuse : %p", mem);
    if (CL_SUCCESS != clReleaseMemObject(mem)) {
        log<Verbosity::error>("Failed to release cl_mem : %p", mem);
        return 1;
    }
    log<Verbosity::info>("Succesfully released cl_mem : %p", mem);
    mem = nullptr;

    initData = 7;
    mem = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData, &cl_err);
    if ((nullptr == mem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create cl_mem object #1 with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_mem : %p", mem);

    log<Verbosity::info>("Creating cl_mem object");
    int initData2 = 23;
    cl_mem mem2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData2, &cl_err);
    if ((nullptr == mem2) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create cl_mem object #2 with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_mem 2 : %p", mem2);

    cl_buffer_region region = {0, 4};
    cl_mem mem2sub = clCreateSubBuffer(mem2, CL_MEM_READ_WRITE, CL_BUFFER_CREATE_TYPE_REGION, &region, &cl_err);
    if ((nullptr == mem2sub) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create cl_mem subbuffer objectwith error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created subbufer of cl_mem 2 : %p as cl_mem 3 : %p", mem2, mem2sub);

    log<Verbosity::info>("Creating cl_command_queue object");
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, devices[deviceIndex], nullptr, &cl_err);
    if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create command queue with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_command_queue : %p", queue);

    if (false == testCreateCommandQueueWithProperties(context, devices[deviceIndex])) {
        return 1;
    }

    if (false == testEventProfiling(context, devices[deviceIndex])) {
        return 1;
    }

    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");

    log<Verbosity::info>("Setting-up kernel arguments");
    if (CL_SUCCESS != clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem)) {
        log<Verbosity::error>("Failed to set kernel arg (0 - buffer)");
        return 1;
    }
    int y = 30;
    if (CL_SUCCESS != clSetKernelArg(kernel, 1, sizeof(y), &y)) {
        log<Verbosity::error>("Failed to set kernel arg (1 - scalars)");
        return 1;
    }
    log<Verbosity::info>("Kernel arguments set-up properly");
    log<Verbosity::info>("Enqueing kernel to the queue");
    size_t lws = 1;
    size_t gws = 1;
    if (CL_SUCCESS != clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to enqueue the kernel");
        return 1;
    }
    log<Verbosity::info>("Succesfully enqueued kernel to the queue");

    log<Verbosity::info>("Flushing the queue");
    if (CL_SUCCESS != clFlush(queue)) {
        log<Verbosity::error>("Failed to flush the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully flushed the queue");

    log<Verbosity::info>("Synchronizing the queue");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");
    int readBack = 3;
    log<Verbosity::info>("Reading results back to host");
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, mem, CL_TRUE, 0, sizeof(readBack), &readBack, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to read results back to the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully read back data to host");
    auto expected = (initData + 5) * (initData * 5) + y;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Testing non-blocking clEnqueueWriteBuffer");
    if (CL_SUCCESS != clEnqueueWriteBuffer(queue, mem, CL_FALSE, 0, sizeof(initData), &initData, 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueWriteBuffer failed");
        return 1;
    }
    log<Verbosity::info>("clEnqueueWriteBuffer success");

    log<Verbosity::info>("Reading back data to host");
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, mem, CL_TRUE, 0, sizeof(readBack), &readBack, 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBuffer failed");
        return 1;
    }
    log<Verbosity::info>("clEnqueueReadBuffer success");
    expected = initData;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Getting USM extension");
    auto usmExtLoad = Cal::Utils::OclApiWrapper::Extensions::Usm::load(platform);
    if (!usmExtLoad) {
        log<Verbosity::error>("Could not load USM extension");
        return 1;
    }
    log<Verbosity::info>("Sucesfully loaded USM extension");
    auto usmExt = usmExtLoad.value();
    log<Verbosity::info>("Creating USM device memory");
    void *usmDeviceMem = usmExt.clDeviceMemAllocINTEL(context, devices[deviceIndex], nullptr, 4, 0, &cl_err);
    if ((nullptr == usmDeviceMem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to allocated USM device memory");
        return 1;
    }
    log<Verbosity::info>("Succesfully allocated USM device memory, ptr : %p", usmDeviceMem);

    log<Verbosity::info>("Trying to get an address of 'clGetMemAllocInfoINTEL' extension!");
    auto clGetMemAllocInfoINTELAddress = clGetExtensionFunctionAddress("clGetMemAllocInfoINTEL");
    if (!clGetMemAllocInfoINTELAddress) {
        log<Verbosity::error>("Could not get an address of 'clGetMemAllocInfoINTEL' extension!");
        return -1;
    }
    log<Verbosity::info>("Successfuly got an address of 'clGetMemAllocInfoINTEL' extension!");

    using ClGetMemAllocInfoINTELFunction = cl_int(cl_context, const void *, cl_mem_info_intel, size_t, void *, size_t *);
    const auto clGetMemAllocInfoINTEL = reinterpret_cast<ClGetMemAllocInfoINTELFunction *>(clGetMemAllocInfoINTELAddress);

    const auto usmDeviceMemWithOffset = static_cast<const char *>(usmDeviceMem) + 2;
    log<Verbosity::info>("Getting base USM address of usmDeviceMemWithOffset = %p", usmDeviceMemWithOffset);
    void *deviceUsmBaseAddress{};
    size_t outParamSize{};
    const auto clGetMemAllocInfoINTELResult = clGetMemAllocInfoINTEL(context,
                                                                     usmDeviceMemWithOffset,
                                                                     CL_MEM_ALLOC_BASE_PTR_INTEL,
                                                                     sizeof(deviceUsmBaseAddress),
                                                                     &deviceUsmBaseAddress,
                                                                     &outParamSize);
    if (clGetMemAllocInfoINTELResult != CL_SUCCESS) {
        log<Verbosity::error>("Could not get base address of USM allocation for usmDeviceMemWithOffset!");
        return -1;
    }

    log<Verbosity::info>("Successfuly retrieved base address of USM allocation for %p! Base address: %p", usmDeviceMemWithOffset, deviceUsmBaseAddress);

    log<Verbosity::info>("Creating USM host memory");
    void *usmHostMem = usmExt.clHostMemAllocINTEL(context, nullptr, 4, 0, &cl_err);
    if ((nullptr == usmHostMem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to allocated USM host memory");
        return 1;
    }
    log<Verbosity::info>("Succesfully allocated USM host memory, ptr : %p", usmHostMem);
    int usmInitData = 777;
    *reinterpret_cast<int *>(usmHostMem) = usmInitData;
    log<Verbosity::info>("Setting-up kernel arguments using USM host memory");
    if (CL_SUCCESS != usmExt.clSetKernelArgMemPointerINTEL(kernel, 0, usmHostMem)) {
        log<Verbosity::error>("Failed to set kernel arg (0 - USM host memory)");
        return 1;
    }
    log<Verbosity::info>("Kernel arguments set-up properly");
    log<Verbosity::info>("Enqueing kernel to the queue");
    if (CL_SUCCESS != clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to enqueue the kernel");
        return 1;
    }
    log<Verbosity::info>("Succesfully enqueued kernel to the queue");

    log<Verbosity::info>("Synchronizing the queue");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");

    readBack = *reinterpret_cast<int *>(usmHostMem);
    expected = (usmInitData + 5) * (usmInitData * 5) + y;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    usmInitData = 3;
    log<Verbosity::info>("Filling USM host");
    *reinterpret_cast<int *>(usmHostMem) = 9;
    if (CL_SUCCESS != usmExt.clEnqueueMemFillINTEL(queue, usmHostMem, &usmInitData, sizeof(usmInitData), sizeof(usmInitData), 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to clEnqueueMemFillINTEL");
        return 1;
    }
    log<Verbosity::info>("Succesfully enqueue fill memory");

    log<Verbosity::info>("Synchronizing the queue");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");

    readBack = *reinterpret_cast<int *>(usmHostMem);
    expected = usmInitData;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Copying USM host -> USM device");
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, false, usmDeviceMem, usmHostMem, sizeof(usmInitData), 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to clEnqueueMemcpyINTEL");
        return 1;
    }
    log<Verbosity::info>("Succesfully clEnqueueMemcpyINTEL USM host -> USM device");
    log<Verbosity::info>("Setting-up kernel arguments using USM device memory");
    if (CL_SUCCESS != usmExt.clSetKernelArgMemPointerINTEL(kernel, 0, usmDeviceMem)) {
        log<Verbosity::error>("Failed to set kernel arg (0 - USM host memory)");
        return 1;
    }
    log<Verbosity::info>("Kernel arguments set-up properly");
    log<Verbosity::info>("Enqueing kernel to the queue");
    if (CL_SUCCESS != clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to enqueue the kernel");
        return 1;
    }
    log<Verbosity::info>("Succesfully enqueued kernel to the queue");

    log<Verbosity::info>("Copying USM device -> USM host");
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, false, usmHostMem, usmDeviceMem, sizeof(usmInitData), 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to clEnqueueMemcpyINTEL");
        return 1;
    }
    log<Verbosity::info>("Succesfully clEnqueueMemcpyINTEL USM device -> USM host");
    log<Verbosity::info>("Synchronizing the queue");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");
    readBack = *reinterpret_cast<int *>(usmHostMem);
    expected = (usmInitData + 5) * (usmInitData * 5) + y;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Copying malloc ptr -> USM host");
    std::unique_ptr<int> mallocedPtr = std::make_unique<int>();
    *mallocedPtr = usmInitData;
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, false, usmHostMem, mallocedPtr.get(), sizeof(*mallocedPtr), 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to clEnqueueMemcpyINTEL");
        return 1;
    }
    log<Verbosity::info>("Succesfully clEnqueueMemcpyINTEL malloc ptr -> USM host");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");
    readBack = *reinterpret_cast<int *>(usmHostMem);
    expected = *mallocedPtr;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    usmInitData = 13;
    *reinterpret_cast<int *>(usmHostMem) = usmInitData;
    log<Verbosity::info>("Copying USM host -> malloc ptr");
    cl_event event;
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, true, &readBack, usmHostMem, sizeof(readBack), 0, nullptr, &event)) {
        log<Verbosity::error>("Failed to clEnqueueMemcpyINTEL");
        return 1;
    }
    log<Verbosity::info>("Succesfully clEnqueueMemcpyINTEL USM host -> malloc ptr");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");
    expected = usmInitData;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    auto mappedPtr = clEnqueueMapBuffer(queue, mem, CL_TRUE, CL_MEM_READ_WRITE, 0, sizeof(int), 0, nullptr, nullptr, &cl_err);
    if ((nullptr == mappedPtr) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to clEnqueueMapBuffer with error : %d", cl_err);
        return 1;
    }
    log<Verbosity::info>("Sucessfully mapped buffer %p to pointer %p", mem, mappedPtr);
    expected = initData;
    readBack = *reinterpret_cast<int *>(mappedPtr);
    if (expected != *reinterpret_cast<int *>(mappedPtr)) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Reading results back to host using mapped ptr");
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, mem2, CL_TRUE, 0, sizeof(readBack), mappedPtr, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to read results back to the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully read back data to host");
    expected = initData2;
    readBack = *reinterpret_cast<int *>(mappedPtr);
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    expected = 47;
    *reinterpret_cast<int *>(mappedPtr) = expected;
    log<Verbosity::info>("Writing from host using mapped ptr");
    if (CL_SUCCESS != clEnqueueWriteBuffer(queue, mem2, CL_TRUE, 0, sizeof(expected), mappedPtr, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed write from host using mapped ptr");
        return 1;
    }
    log<Verbosity::info>("Succesfully wrote from host using mapped ptr");
    log<Verbosity::info>("Reading results back to host using mapped ptr");
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, mem2, CL_TRUE, 0, sizeof(readBack), &readBack, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to read results back to the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully read back data to host");
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    cl_err = clEnqueueUnmapMemObject(queue, mem, mappedPtr, 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to clEnqueueUnmapMemObject for ptr %p with error : %d", mappedPtr, cl_err);
        return 1;
    }
    log<Verbosity::info>("Sucessfully unmapped buffer %p for pointer %p", mem, mappedPtr);

    log<Verbosity::info>("Creating SVM coarse grain buffer");
    void *svmMem = clSVMAlloc(context, 0, 4, 0);
    if (nullptr == svmMem) {
        log<Verbosity::error>("Failed to allocated SVM memory");
        return 1;
    }
    log<Verbosity::info>("Succesfully allocated SVM memory, ptr : %p", svmMem);

    int svmInitData = 111;
    log<Verbosity::info>("Mapping SVM ptr : %p", svmMem);
    cl_err = clEnqueueSVMMap(queue, CL_TRUE, CL_MEM_READ_WRITE, svmMem, sizeof(int), 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to map SVM ptr %p, error : %d", svmMem, cl_err);
        return 1;
    }
    log<Verbosity::info>("Succesfully mapped SVM ptr : %p", svmMem);

    *reinterpret_cast<int *>(svmMem) = svmInitData;

    log<Verbosity::info>("Unmapping SVM ptr : %p", svmMem);
    cl_err = clEnqueueSVMUnmap(queue, svmMem, 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to unmap SVM ptr %p, error : %d", svmMem, cl_err);
        return 1;
    }
    log<Verbosity::info>("Succesfully unmapped SVM ptr : %p", svmMem);

    log<Verbosity::info>("Setting-up kernel arguments using SVM memory");
    if (CL_SUCCESS != clSetKernelArgSVMPointer(kernel, 0, svmMem)) {
        log<Verbosity::error>("Failed to set kernel arg (0 - SVM memory)");
        return 1;
    }

    log<Verbosity::info>("Kernel arguments set-up properly");
    log<Verbosity::info>("Enqueing kernel to the queue");
    if (CL_SUCCESS != clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to enqueue the kernel");
        return 1;
    }
    log<Verbosity::info>("Succesfully enqueued kernel to the queue");

    log<Verbosity::info>("Synchronizing the queue");
    if (CL_SUCCESS != clFinish(queue)) {
        log<Verbosity::error>("Failed to synchronize the queue");
        return 1;
    }
    log<Verbosity::info>("Succesfully synchronized the queue");

    log<Verbosity::info>("Mapping SVM ptr : %p", svmMem);
    cl_err = clEnqueueSVMMap(queue, CL_TRUE, CL_MEM_READ_WRITE, svmMem, sizeof(int), 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to map SVM ptr %p, error : %d", svmMem, cl_err);
        return 1;
    }
    log<Verbosity::info>("Succesfully mapped SVM ptr : %p", svmMem);

    readBack = *reinterpret_cast<int *>(svmMem);
    expected = (svmInitData + 5) * (svmInitData * 5) + y;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Unmapping SVM ptr : %p", svmMem);
    cl_err = clEnqueueSVMUnmap(queue, svmMem, 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to unmap SVM ptr %p, error : %d", svmMem, cl_err);
        return 1;
    }
    log<Verbosity::info>("Succesfully unmapped SVM ptr : %p", svmMem);

    svmInitData = 13;
    log<Verbosity::info>("Filling SVM memory");
    if (CL_SUCCESS != clEnqueueSVMMemFill(queue, svmMem, &svmInitData, sizeof(svmInitData), sizeof(svmInitData), 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to clEnqueueSVMMemFill");
        return 1;
    }
    log<Verbosity::info>("Succesfully enqueued fill memory");

    log<Verbosity::info>("Mapping SVM ptr : %p", svmMem);
    cl_err = clEnqueueSVMMap(queue, CL_TRUE, CL_MEM_READ_WRITE, svmMem, sizeof(int), 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to map SVM ptr %p, error : %d", svmMem, cl_err);
        return 1;
    }
    log<Verbosity::info>("Succesfully mapped SVM ptr : %p", svmMem);

    readBack = *reinterpret_cast<int *>(svmMem);
    expected = svmInitData;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Unmapping SVM ptr : %p", svmMem);
    cl_err = clEnqueueSVMUnmap(queue, svmMem, 0, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Failed to unmap SVM ptr %p, error : %d", svmMem, cl_err);
        return 1;
    }
    log<Verbosity::info>("Succesfully unmapped SVM ptr : %p", svmMem);

    log<Verbosity::info>("Freeing SVM coarse grain buffer");
    clSVMFree(context, svmMem);

    log<Verbosity::info>("");
    log<Verbosity::info>("Releasing opencl objects");
    log<Verbosity::info>("Testing retain/release");
    clRetainCommandQueue(queue);
    clReleaseCommandQueue(queue);
    clRetainMemObject(mem);
    clReleaseMemObject(mem);
    clRetainKernel(kernel);
    clReleaseKernel(kernel);
    clRetainProgram(program);
    clReleaseProgram(program);
    clRetainContext(context);
    clReleaseContext(context);
    clRetainDevice(devices[deviceIndex]);
    clReleaseDevice(devices[deviceIndex]);

    bool succesfullyReleasedAllObjects = true;
    succesfullyReleasedAllObjects &= (CL_SUCCESS == usmExt.clMemFreeINTEL(context, usmHostMem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == usmExt.clMemFreeINTEL(context, usmDeviceMem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseCommandQueue(queue));

    clGetEventInfo(event, CL_EVENT_COMMAND_QUEUE, sizeof(cl_command_queue), &queue, nullptr);
    cl_uint refCount;
    clGetCommandQueueInfo(queue, CL_QUEUE_REFERENCE_COUNT, sizeof(cl_uint), &refCount, nullptr);

    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseEvent(event));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem2sub));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem2));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseKernel(kernel));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(linkedProgram));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(program));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(programFromBinary));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseContext(context));
    if (false == succesfullyReleasedAllObjects) {
        log<Verbosity::info>("Failed to release one of objects");
        return 1;
    }
    log<Verbosity::info>("Succesfully released all objects");

    log<Verbosity::info>("Memory stress test - number of host mem allocations");
    context = createContext(platform, devices, deviceIndex);

    if (false == skipStressTests) {
        int hostMemMaxAllocs = 512 / (childProcesses.size() + 1);
        log<Verbosity::info>("Creating-destroying USM host memory - number of allocations : %d", hostMemMaxAllocs);
        for (int i = 0; i < hostMemMaxAllocs; ++i) {
            void *usmHostMem = usmExt.clHostMemAllocINTEL(context, nullptr, 32 * 4096, 0, &cl_err);
            if ((nullptr == usmHostMem) || (CL_SUCCESS != cl_err)) {
                log<Verbosity::error>("Failed to allocate (create-destroy test) USM host memory for allocation #%d", i);
                return 1;
            }
            if (CL_SUCCESS != usmExt.clMemFreeINTEL(context, usmHostMem)) {
                log<Verbosity::error>("Failed to free (create-destroy test) USM host memory");
                return 1;
            }
        }
        log<Verbosity::info>("Succesfully created-destroyed %d USM host memory allocations", hostMemMaxAllocs);

        log<Verbosity::info>("Creating USM host memory - number of allocations : %d", hostMemMaxAllocs);
        std::vector<void *> hostMems;
        for (int i = 0; i < hostMemMaxAllocs; ++i) {
            void *usmHostMem = usmExt.clHostMemAllocINTEL(context, nullptr, 32 * 4096, 0, &cl_err);
            if ((nullptr == usmHostMem) || (CL_SUCCESS != cl_err)) {
                log<Verbosity::error>("Failed to allocate (create test) USM host memory for allocation #%d", i);
                return 1;
            }
            hostMems.push_back(usmHostMem);
        }
        log<Verbosity::info>("Succesfully created %d USM host memory allocations", hostMemMaxAllocs);

        log<Verbosity::info>("Freeing USM host memory - number of allocations : %d", hostMemMaxAllocs);
        for (void *ptr : hostMems) {
            if (CL_SUCCESS != usmExt.clMemFreeINTEL(context, ptr)) {
                log<Verbosity::error>("Failed to free (destroy test) USM host memory");
                return 1;
            }
        }
        log<Verbosity::info>("Succesfully destroyed %d USM host memory allocations", hostMemMaxAllocs);
    } else {
        log<Verbosity::debug>("Skipped memory stress tests");
    }

    if (CL_SUCCESS != clReleaseContext(context)) {
        log<Verbosity::error>("Failed to free OCL context");
    }

    clReleaseDevice(devices[deviceIndex]);

    if (childProcesses.size()) {
        log<Verbosity::info>("Waiting for child processes");
        for (auto pid : childProcesses) {
            log<Verbosity::info>("Waiting for child process : %d", pid);
            waitpid(pid, nullptr, 0);
        }
        log<Verbosity::info>("Child processes finished");
        log<Verbosity::info>("Exiting parent process");
    }

    log<Verbosity::info>("End of test %s", argv[0]);

    return 0;
}
