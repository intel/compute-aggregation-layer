/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1
#include "cal.h"
#include "shared/log.h"
#include "shared/ocl_wrapper.h"

#include <algorithm>
#include <cstdio>
#include <string_view>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

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

    cl_platform_id platform = {};
    if (platformOrd >= 0) {
        log<Verbosity::info>("Looking for OCL platform with ordinal %d", platformOrd);
        platform = Cal::Utils::OclApiWrapper::getPlatformByOrdinal(platformOrd);
        if (Cal::Utils::OclApiWrapper::invalidPlatform == platform) {
            log<Verbosity::critical>("Could not find OCL platform with ordinal %d", platformOrd);
            return 1;
        }
        log<Verbosity::info>("Found OCL platform with ordinal %d", platformOrd);
    } else {
        platform = Cal::Utils::OclApiWrapper::getPlatformByName(calPlatformName.data(), false);
        if (Cal::Utils::OclApiWrapper::invalidPlatform == platform) {
            log<Verbosity::critical>("Could not find Compute Aggregation Layer OCL platform");
            return 1;
        }
        log<Verbosity::info>("Found Compute Aggregation Layer OCL platform");
    }

    Cal::Utils::OclApiWrapper::PlatformInfo platformInfo;
    if (false == platformInfo.read(platform)) {
        log<Verbosity::error>("Could not read platform info");
        return 1;
    }
    log<Verbosity::info>("Platform info : \n%s\n", platformInfo.str().c_str());

    std::vector<cl_device_id> devices = Cal::Utils::OclApiWrapper::getDevicesForPlatform(platform, CL_DEVICE_TYPE_ALL);
    if (devices.empty()) {
        log<Verbosity::info>("No devices in platform");
        return 1;
    }
    log<Verbosity::info>("Num devices : %zu", devices.size());
    for (auto device : devices) {
        Cal::Utils::OclApiWrapper::DeviceInfo deviceInfo;
        if (false == deviceInfo.read(device)) {
            log<Verbosity::error>("Could not read device info for device %p", device);
            return 1;
        }
        log<Verbosity::info>("Device %p info : \n%s\n", device, deviceInfo.str().c_str());
        Cal::Utils::OclApiWrapper::DeviceInfo deviceInfoCached;
        if (false == deviceInfoCached.read(device)) {
            log<Verbosity::error>("Could not read cached device info for device %p", device);
            return 1;
        }
        if (deviceInfo != deviceInfoCached) {
            log<Verbosity::error>("Mismatch on cached device info for device %p", device);
            return 1;
        }
        log<Verbosity::info>("cached device info OK for device %p", device);
    }

    log<Verbosity::info>("Creating context for first device : %p", devices[0]);
    cl_context_properties properties[3] = {};
    properties[0] = CL_CONTEXT_PLATFORM;
    properties[1] = reinterpret_cast<cl_context_properties>(platform);
    properties[2] = 0;
    cl_int cl_err = 0;
    cl_context ctx = clCreateContext(properties, 1, &devices[0], nullptr, nullptr, &cl_err);
    if ((nullptr == ctx) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create context with error : %d", cl_err);
        return 1;
    };

    Cal::Utils::OclApiWrapper::ContextInfo contextInfo;
    Cal::Utils::OclApiWrapper::ContextInfo contextInfoCached;
    if (false == contextInfo.read(ctx)) {
        log<Verbosity::error>("Could not read context info");
        return 1;
    }
    log<Verbosity::info>("Context info : \n%s\n", contextInfo.str().c_str());
    if (false == contextInfoCached.read(ctx)) {
        log<Verbosity::error>("Could not read cached context info for context %p", ctx);
        return 1;
    }
    if (contextInfo != contextInfoCached) {
        log<Verbosity::error>("Mismatch on cached context info for context %p", ctx);
        return 1;
    }
    log<Verbosity::info>("cached context info OK for context %p", ctx);

    log<Verbosity::info>("Creating program object with source");
    const char *f0 = "int f0(int a) { return a + 5; }";
    const char *f1 = "int f1(int a) { return a*5; }";
    const char *k = "__kernel void k(__global int *x, int y) { *x = f0(*x)*f1(*x) + y; }";
    const char *src[] = {f0, f1, k};
    cl_program program = clCreateProgramWithSource(ctx, 3, src, nullptr, &cl_err);
    if ((nullptr == program) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create program with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created program : %p", program);

    cl_err = clBuildProgram(program, 1, &devices[0], "-cl-std=CL2.0", nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Build failed with error : %d", cl_err);
        std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, devices[0]);
        log<Verbosity::info>("Build log %s", buildLog.c_str());
        return 1;
    }
    log<Verbosity::info>("Succesfully built program : %p", program);
    std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, devices[0]);
    log<Verbosity::info>("Build log %s", buildLog.c_str());

    log<Verbosity::info>("Creating kernel object");
    cl_kernel kernel = clCreateKernel(program, "k", &cl_err);
    if ((nullptr == kernel) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create kernel with error : %d", cl_err);
        return 1;
    };

    log<Verbosity::info>("Succesfully created kernel : %p", kernel);
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
    cl_mem mem = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData, &cl_err);
    if ((nullptr == mem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create cl_mem object #1 with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_mem : %p", mem);

    log<Verbosity::info>("Releasing cl_mem for reuse : %p", mem);
    if (CL_SUCCESS != clReleaseMemObject(mem)) {
        log<Verbosity::error>("Failed to released cl_mem : %p", mem);
        return 1;
    }
    log<Verbosity::info>("Succesfully released cl_mem : %p", mem);
    mem = nullptr;

    initData = 7;
    mem = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData, &cl_err);
    if ((nullptr == mem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create cl_mem object #1 with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_mem : %p", mem);

    log<Verbosity::info>("Creating cl_mem object");
    int initData2 = 23;
    cl_mem mem2 = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData2, &cl_err);
    if ((nullptr == mem) || (CL_SUCCESS != cl_err)) {
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
    cl_command_queue queue = clCreateCommandQueueWithProperties(ctx, devices[0], nullptr, &cl_err);
    if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create command queue with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created cl_command_queue : %p", queue);

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
    void *usmDeviceMem = usmExt.clDeviceMemAllocINTEL(ctx, devices[0], nullptr, 4, 0, &cl_err);
    if ((nullptr == usmDeviceMem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to allocated USM device memory");
        return 1;
    }
    log<Verbosity::info>("Succesfully allocated USM device memory, ptr : %p", usmDeviceMem);

    log<Verbosity::info>("Creating USM host memory");
    void *usmHostMem = usmExt.clHostMemAllocINTEL(ctx, nullptr, 4, 0, &cl_err);
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
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, false, usmHostMem, &usmInitData, sizeof(usmInitData), 0, nullptr, nullptr)) {
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
    expected = usmInitData;
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
    void *svmMem = clSVMAlloc(ctx, 0, 4, 0);
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
    clSVMFree(ctx, svmMem);

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
    clRetainContext(ctx);
    clReleaseContext(ctx);
    clRetainDevice(devices[0]);
    clReleaseDevice(devices[0]);

    bool succesfullyReleasedAllObjects = true;
    succesfullyReleasedAllObjects &= (CL_SUCCESS == usmExt.clMemFreeINTEL(ctx, usmHostMem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == usmExt.clMemFreeINTEL(ctx, usmDeviceMem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseCommandQueue(queue));

    clGetEventInfo(event, CL_EVENT_COMMAND_QUEUE, sizeof(cl_command_queue), &queue, nullptr);
    cl_uint refCount;
    clGetCommandQueueInfo(queue, CL_QUEUE_REFERENCE_COUNT, sizeof(cl_uint), &refCount, nullptr);

    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseEvent(event));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem2sub));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem2));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseKernel(kernel));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(program));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseContext(ctx));
    if (false == succesfullyReleasedAllObjects) {
        log<Verbosity::info>("Failed to release one of objects");
        return 1;
    }
    log<Verbosity::info>("Succesfully released all objects");

    log<Verbosity::info>("Memory stress test - number of host mem allocations");
    ctx = clCreateContext(properties, 1, &devices[0], nullptr, nullptr, &cl_err);
    if ((nullptr == ctx) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create context with error : %d", cl_err);
        return 1;
    };

    if (false == skipStressTests) {
        int hostMemMaxAllocs = 512 / (childProcesses.size() + 1);
        log<Verbosity::info>("Creating-destroying USM host memory - number of allocations : %d", hostMemMaxAllocs);
        for (int i = 0; i < hostMemMaxAllocs; ++i) {
            void *usmHostMem = usmExt.clHostMemAllocINTEL(ctx, nullptr, 32 * 4096, 0, &cl_err);
            if ((nullptr == usmHostMem) || (CL_SUCCESS != cl_err)) {
                log<Verbosity::error>("Failed to allocate (create-destroy test) USM host memory for allocation #%d", i);
                return 1;
            }
            if (CL_SUCCESS != usmExt.clMemFreeINTEL(ctx, usmHostMem)) {
                log<Verbosity::error>("Failed to free (create-destroy test) USM host memory");
                return 1;
            }
        }
        log<Verbosity::info>("Succesfully created-destroyed %d USM host memory allocations", hostMemMaxAllocs);

        log<Verbosity::info>("Creating USM host memory - number of allocations : %d", hostMemMaxAllocs);
        std::vector<void *> hostMems;
        for (int i = 0; i < hostMemMaxAllocs; ++i) {
            void *usmHostMem = usmExt.clHostMemAllocINTEL(ctx, nullptr, 32 * 4096, 0, &cl_err);
            if ((nullptr == usmHostMem) || (CL_SUCCESS != cl_err)) {
                log<Verbosity::error>("Failed to allocate (create test) USM host memory for allocation #%d", i);
                return 1;
            }
            hostMems.push_back(usmHostMem);
        }
        log<Verbosity::info>("Succesfully created %d USM host memory allocations", hostMemMaxAllocs);

        log<Verbosity::info>("Freeing USM host memory - number of allocations : %d", hostMemMaxAllocs);
        for (void *ptr : hostMems) {
            if (CL_SUCCESS != usmExt.clMemFreeINTEL(ctx, ptr)) {
                log<Verbosity::error>("Failed to free (destroy test) USM host memory");
                return 1;
            }
        }
        log<Verbosity::info>("Succesfully destroyed %d USM host memory allocations", hostMemMaxAllocs);
    } else {
        log<Verbosity::debug>("Skipped memory stress tests");
    }

    if (CL_SUCCESS != clReleaseContext(ctx)) {
        log<Verbosity::error>("Failed to free OCL context");
    }

    clReleaseDevice(devices[0]);

    if (childProcesses.size()) {
        log<Verbosity::info>("Waiting for child processes");
        for (auto pid : childProcesses) {
            log<Verbosity::info>("Waiting for child process : %d", pid);
            waitpid(pid, nullptr, 0);
        }
        log<Verbosity::info>("Child processes finished");
        log<Verbosity::info>("Exiting parent process");
    }

    return 0;
}
