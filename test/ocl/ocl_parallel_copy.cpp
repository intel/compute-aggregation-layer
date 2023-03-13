/*
 * Copyright (C) 2022-2023 Intel Corporation
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
    bool isParent = ((0 == forkNum) || (false == childProcesses.empty()));
    if (isParent) {
        log<Verbosity::info>("Platform info : \n%s\n", platformInfo.str().c_str());
    }

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
        if (isParent) {
            log<Verbosity::info>("Device %p info : \n%s\n", device, deviceInfo.str().c_str());
        }
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

    log<Verbosity::info>("Creating program object with source");
    const char *k = "__kernel void k(__global int *x) { *x = *x * *x; }";
    const char *src[] = {k};
    cl_program program = clCreateProgramWithSource(ctx, 1, src, nullptr, &cl_err);
    if ((nullptr == program) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create program with error : %d", cl_err);
        return 1;
    };

    cl_err = clCompileProgram(program, 1, &devices[0], "-cl-std=CL2.0", 0, nullptr, nullptr, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Compilation of program failed with error : %d", cl_err);
        std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, devices[0]);
        log<Verbosity::info>("Build log %s", buildLog.c_str());
        return 1;
    }

    auto linkedProgram = clLinkProgram(ctx, 1, &devices[0], "", 1, &program, nullptr, nullptr, &cl_err);
    if (CL_SUCCESS != cl_err || linkedProgram == nullptr) {
        log<Verbosity::error>("Link failed with error : %d", cl_err);
        std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(linkedProgram, devices[0]);
        log<Verbosity::info>("Build log %s", buildLog.c_str());
        return 1;
    }

    log<Verbosity::info>("Creating kernel object");
    cl_kernel kernel = clCreateKernel(linkedProgram, "k", &cl_err);
    if ((nullptr == kernel) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create kernel with error : %d", cl_err);
        return 1;
    };

    log<Verbosity::info>("Creating cl_command_queue object");
    cl_command_queue queue = clCreateCommandQueueWithProperties(ctx, devices[0], nullptr, &cl_err);
    if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create command queue with error : %d", cl_err);
        return 1;
    };

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
    void *usmDeviceMem = usmExt.clDeviceMemAllocINTEL(ctx, devices[0], nullptr, copyDataSize, 0, &cl_err);
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
    succesfullyReleasedAllObjects &= (CL_SUCCESS == usmExt.clMemFreeINTEL(ctx, usmDeviceMem));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseCommandQueue(queue));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseKernel(kernel));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(linkedProgram));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseProgram(program));
    succesfullyReleasedAllObjects &= (CL_SUCCESS == clReleaseContext(ctx));
    if (false == succesfullyReleasedAllObjects) {
        log<Verbosity::info>("Failed to release one of objects");
        return 1;
    }
    log<Verbosity::info>("Succesfully released all objects");

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
