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
#include <chrono>
#include <cstdio>
#include <getopt.h>
#include <numeric>
#include <string_view>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

template <typename T>
inline std::string asMillisecondsStr(const T &d) {
    auto micro = std::chrono::duration_cast<std::chrono::microseconds>(d);
    std::stringstream str;
    str << static_cast<double>(micro.count()) / 1000.0f << "[ms]";
    return str.str();
}

template <typename T>
inline std::string asSecondsStr(const T &d) {
    auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(d);
    std::stringstream str;
    str << static_cast<double>(milli.count()) / 1000.0f << "[s]";
    return str.str();
}

constexpr option options[] = {
    {"platform_ordinal", required_argument, nullptr, 'p'},
    {"fork", required_argument, nullptr, 'f'},
    {"alloc_size_MB", required_argument, nullptr, 's'},
    {"loop_count", required_argument, nullptr, 'l'},
    {"enqueue_write_count", required_argument, nullptr, 'w'},
    {"ndrange_count", required_argument, nullptr, 'n'},
    {"ndrange_size", required_argument, nullptr, 'k'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, 0, nullptr, 0}};

inline std::string generateHelp() {
    std::stringstream stream;
    stream << "Valid arguments : \n";
    for (const auto &opt : options) {
        if (0 == opt.val) {
            break;
        }
        stream << "   -" << static_cast<char>(opt.val);
        stream << "   --" << opt.name;
        if (required_argument == opt.has_arg) {
            stream << " VALUE";
        }
        stream << "\n";
    }
    return stream.str();
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::bloat);
    int platformOrd = -1;
    int forkNum = 0;

    int loopCount = 64;
    int copyCount = 4;
    size_t copyDataSizeMB = 32;
    size_t ndRangeDispatchSize = 8192;
    int ndRangesCount = 2;

    int option;
    while ((option = getopt_long(argc, const_cast<char *const *>(argv), "p:f:s:l:w:n:k:h", options, nullptr)) != -1) {
        switch (option) {
        case 'p':
            platformOrd = atoi(optarg);
            break;
        case 'f':
            forkNum = atoi(optarg);
            break;
        case 's':
            copyDataSizeMB = atoi(optarg);
            break;
        case 'l':
            loopCount = atoi(optarg);
            break;
        case 'w':
            copyCount = atoi(optarg);
            break;
        case 'n':
            ndRangesCount = atoi(optarg);
            break;
        case 'k':
            ndRangeDispatchSize = atoi(optarg);
            break;
        case 'h':
            fprintf(stderr, "%s", generateHelp().c_str());
            return 0;
        default:
            fprintf(stderr, "Invalid arg, \n%s\n", generateHelp().c_str());
            return 1;
        }
    }

    ++loopCount; // warmup
    static constexpr size_t MB = 1024 * 1024;
    size_t copyDataSize = copyDataSizeMB * MB;

    std::vector<pid_t> childProcesses;

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

    const char *k = "__kernel void k(__global int *x) { *x = *x * *x; }";
    const char *src[] = {k};
    auto program = createProgramWithSource(context, 5, src);
    compileProgram(program, devices[deviceIndex]);
    auto linkedProgram = linkProgram(context, devices[deviceIndex], program);
    auto kernel = createKernel(linkedProgram, "K");

    log<Verbosity::info>("Creating cl_command_queue object");
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, devices[deviceIndex], nullptr, &cl_err);
    if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create command queue with error : %d", cl_err);
        return 1;
    };

    bool isParent = ((0 == forkNum) || (false == childProcesses.empty()));
    if (isParent) {
        log<Verbosity::info>("Test outer loop count : %d (+1 warmup)", loopCount);
        log<Verbosity::info>("Test inner loop copies count (malloc -> device mem) : %d", copyCount);
        log<Verbosity::info>("Test inner loop copy data size (malloc mem) : %d MB", copyDataSize);
        log<Verbosity::info>("Test inner loop NDRangeKernel dispatch size : %d", ndRangeDispatchSize);
        log<Verbosity::info>("Test inner loop NDRangeKernel count : %d", ndRangesCount);
    }

    std::vector<char> testData;
    testData.resize(copyDataSize);

    log<Verbosity::info>("Getting USM extension");
    auto usmExtLoad = Cal::Utils::OclApiWrapper::Extensions::Usm::load(platform);
    if (!usmExtLoad) {
        log<Verbosity::error>("Could not load USM extension");
        return 1;
    }
    log<Verbosity::info>("Sucesfully loaded USM extension");
    auto usmExt = usmExtLoad.value();
    log<Verbosity::info>("Creating USM device memory");
    void *usmDeviceMem = usmExt.clDeviceMemAllocINTEL(context, devices[deviceIndex], nullptr, copyDataSize, 0, &cl_err);
    if ((nullptr == usmDeviceMem) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to allocated USM device memory");
        return 1;
    }
    log<Verbosity::info>("Succesfully allocated USM device memory, ptr : %p", usmDeviceMem);

    auto getTimepoint = []() -> auto{ return std::chrono::steady_clock::now(); };
    using timepoint_t = decltype(getTimepoint());
    std::vector<timepoint_t> timepoints;
    timepoints.reserve(loopCount * 2);

    auto overallStart = getTimepoint();

    for (int i = 0; i < loopCount; ++i) {
        log<Verbosity::info>("Iteration #%d", i);
        timepoints.push_back(getTimepoint());
        for (int j = 0; j < copyCount; ++j) {
            if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, false, usmDeviceMem, testData.data(), copyDataSize, 0, nullptr, nullptr)) {
                log<Verbosity::error>("Failed to clEnqueueMemcpyINTEL");
                return 1;
            }
        }

        if (CL_SUCCESS != usmExt.clSetKernelArgMemPointerINTEL(kernel, 0, usmDeviceMem)) {
            log<Verbosity::error>("Failed to set kernel arg (0 - USM host memory)");
            return 1;
        }

        size_t lws = 64;
        size_t gws = ndRangeDispatchSize;
        for (int i = 0; i < ndRangesCount; ++i) {
            if (CL_SUCCESS != clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr)) {
                log<Verbosity::error>("Failed to enqueue the kernel");
                return 1;
            }
        }
        if (CL_SUCCESS != clFinish(queue)) {
            log<Verbosity::error>("Failed to synchronize the queue");
            return 1;
        }
        timepoints.push_back(getTimepoint());
    }

    auto overallEnd = getTimepoint();

    log<Verbosity::info>("Releasing opencl objects");
    bool succesfullyReleasedAllObjects = true;
    succesfullyReleasedAllObjects &= (CL_SUCCESS == usmExt.clMemFreeINTEL(context, usmDeviceMem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseCommandQueue(queue));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseKernel(kernel));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(linkedProgram));
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

    log<Verbosity::info>("End of test %s", argv[0]);

    using diff_t = decltype(timepoints[1] - timepoints[0]);
    std::vector<diff_t> timeDiffs;
    timeDiffs.reserve(loopCount);
    for (int i = 0; i < loopCount; ++i) {
        timeDiffs.push_back(timepoints[i * 2 + 1] - timepoints[i * 2]);
    }

    auto allExceptFirst = std::accumulate(std::next(timeDiffs.begin()), timeDiffs.end(), diff_t{});

    std::stringstream perfRes;
    perfRes << "Warmup : " << asMillisecondsStr(timeDiffs[0]) << "\n";
    perfRes << "First iter : " << asMillisecondsStr(timeDiffs[1]) << "\n";
    if (loopCount > 2) {
        perfRes << "Total : " << asMillisecondsStr(allExceptFirst) << "\n";
        perfRes << "Average : " << asMillisecondsStr(allExceptFirst / (loopCount - 1)) << "\n";
        std::sort(timeDiffs.begin(), timeDiffs.end());
        perfRes << "Median : " << asMillisecondsStr(timeDiffs[timeDiffs.size() / 2]) << "\n";
        perfRes << "Min : " << asMillisecondsStr(timeDiffs[0]) << "\n";
        perfRes << "Max : " << asMillisecondsStr(*timeDiffs.rbegin()) << "\n";
    }
    log<Verbosity::info>("Perf results :\n%s", perfRes.str().c_str());

    if (isParent) {
        log<Verbosity::info>("Overall time : %s", asSecondsStr(overallEnd - overallStart).c_str());
    }

    return 0;
}
