/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1
#include "cal.h"
#include "shared/ocl_wrapper.h"
#include "test/utils/ocl_common_steps.h"

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
    auto context = createContext(platform, devices, deviceIndex);
    cl_int cl_err{};

    const char *f0 = "int f0(int a) { return a + 5; }";
    const char *f1 = "int f1(int a) { return a*5; }";
    const char *k = "__kernel void k(__global int *x, int y) { *x = f0(*x)*f1(*x) + y; }";
    const char *src[] = {f0, f1, k};
    auto program = createProgramWithSource(context, 3, src);
    buildProgram(program, devices[deviceIndex]);
    auto kernel = createKernel(program, "k");

    Cal::Utils::OclApiWrapper::KernelInfo kernelInfo;
    if (false == kernelInfo.read(kernel)) {
        log<Verbosity::error>("Could not read kernel info");
        return 1;
    }

    log<Verbosity::info>("Creating cl_mem object #1 using host ptr");
    int initData = 3;
    std::unique_ptr<int> hostPtr = std::unique_ptr<int>(new int);
    *hostPtr = initData;

    cl_mem mem = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(int), hostPtr.get(), &cl_err);
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
    return 1;
    log<Verbosity::info>("Succesfully released cl_mem : %p", mem);
    mem = nullptr;

    initData = 7;
    *hostPtr = initData;
    mem = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(int), hostPtr.get(), &cl_err);
    if ((nullptr == mem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to recreate cl_mem object #1 with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully recreated cl_mem : %p", mem);

    log<Verbosity::info>("Creating cl_mem object with CL_MEM_COPY_HOST_PTR");
    int initData2 = 23;
    cl_mem mem2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &initData2, &cl_err);
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
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, devices[deviceIndex], nullptr, &cl_err);
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
    std::unique_ptr<int> readBackHeap = std::unique_ptr<int>(new int);
    int readBack = 3;
    log<Verbosity::info>("Reading results back to host");
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, mem, CL_TRUE, 0, sizeof(readBack), readBackHeap.get(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("Failed to read results back to the host (clEnqueueReadBuffer failed)");
        return 1;
    }
    readBack = *readBackHeap;
    log<Verbosity::info>("Succesfully read back data to host");
    auto expected = (initData + 5) * (initData * 5) + y;
    if (readBack != expected) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

    log<Verbosity::info>("Mapping buffer with USE_HOST_PTR");
    auto mappedPtr = clEnqueueMapBuffer(queue, mem, CL_TRUE, CL_MEM_READ_WRITE, 0, sizeof(int), 0, nullptr, nullptr, &cl_err);
    if ((nullptr == mappedPtr) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to clEnqueueMapBuffer with error : %d", cl_err);
        return 1;
    }
    log<Verbosity::info>("Sucessfully mapped buffer %p to pointer %p", mem, mappedPtr);
    if (mappedPtr != hostPtr.get()) {
        log<Verbosity::error>("Mapped ptr does not match host ptr (got:%p, expected:%p)", mappedPtr, hostPtr.get());
    } else {
        log<Verbosity::info>("Mapped pointer %p matches host ptr from USE_HOST_PTR", mem, mappedPtr);
    }
    readBack = *reinterpret_cast<int *>(mappedPtr);
    if (expected != *reinterpret_cast<int *>(mappedPtr)) {
        log<Verbosity::error>("Results are incorrect (got:%d, expected:%d)", readBack, expected);
        return 1;
    }
    log<Verbosity::info>("Results are correct (got:%d, expected:%d)", readBack, expected);

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
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseCommandQueue(queue));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem2sub));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseMemObject(mem2));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseKernel(kernel));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(program));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseContext(context));
    if (false == succesfullyReleasedAllObjects) {
        log<Verbosity::info>("Failed to release one of objects");
        return 1;
    }
    log<Verbosity::info>("Succesfully released all objects");

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

    return 0;
}
