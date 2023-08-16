/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test/utils/ocl_common_steps.h"

#include <array>

template <size_t N>
bool validateOutput(const std::array<int, N> &x, const std::array<int, N> &y) {
    for (size_t i = 0; i < N; i++) {
        if (x[i] != y[i]) {
            log<Verbosity::error>("Mismatch between source and destination data on index %zu. Expected value: %d, actual value: %d",
                                  i, x[i], y[i]);
            return false;
        }
    }
    log<Verbosity::info>("Source and destination data is correct");
    return true;
}

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

    log<Verbosity::info>("Creating cl_command_queue object");
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, devices[deviceIndex], nullptr, &cl_err);
    if ((nullptr == queue) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create command queue with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("successfully created cl_command_queue : %p", queue);

    log<Verbosity::info>("Getting USM extension");
    auto usmExtLoad = Cal::Utils::OclApiWrapper::Extensions::Usm::load(platform);
    if (!usmExtLoad) {
        log<Verbosity::error>("Could not load USM extension");
        return 1;
    }
    log<Verbosity::info>("Sucesfully loaded USM extension");
    auto usmExt = usmExtLoad.value();

    constexpr size_t NUM_ELEMENTS_TO_COPY = 1024;
    constexpr size_t BUFFER_SIZE = NUM_ELEMENTS_TO_COPY * sizeof(int);

    // ----- clEnqueueMemcpyINTEL -----
    auto usmDevice = usmExt.clDeviceMemAllocINTEL(context, devices[deviceIndex], nullptr, BUFFER_SIZE, 0, &cl_err);
    if ((nullptr == usmDevice) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create usm device memory with error : %d", cl_err);
        return 1;
    }
    log<Verbosity::info>("Successfully created USM device memory: %p", usmDevice);

    std::array<int, NUM_ELEMENTS_TO_COPY> sourceBuffer;
    sourceBuffer.fill(1);
    log<Verbosity::info>("Copying data allocated on host to usm device via clEnqueueMemcpyINTEL");
    auto result = usmExt.clEnqueueMemcpyINTEL(queue, CL_TRUE, usmDevice, sourceBuffer.data(), sizeof(sourceBuffer), 0, nullptr, nullptr);
    if (CL_SUCCESS != result) {
        log<Verbosity::error>("clEnqueueMemcpyINTEL failed");
        return 1;
    }
    log<Verbosity::info>("Copy of host data to usm device was successful");

    log<Verbosity::info>("Copying usm device data to host allocation via clEnqueueMemcpyINTEL");
    std::array<int, NUM_ELEMENTS_TO_COPY> destinationBuffer{0};
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, CL_TRUE, destinationBuffer.data(), usmDevice, BUFFER_SIZE, 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBuffer failed");
        return 1;
    }
    log<Verbosity::info>("Copy of usm device data to host allocation was successful");
    validateOutput(sourceBuffer, destinationBuffer);

    // ----- clEnqueueMemcpyINTEL -----
    auto bufferObject = clCreateBuffer(context, CL_MEM_READ_WRITE, BUFFER_SIZE, nullptr, &cl_err);
    if ((nullptr == bufferObject) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create buffer object with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("successfully created buffer object : %p", bufferObject);

    log<Verbosity::info>("Copying data allocated on host to buffer object via clEnqueueWriteBuffer");
    if (CL_SUCCESS != clEnqueueWriteBuffer(queue, bufferObject, CL_TRUE, 0, sizeof(sourceBuffer), sourceBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueWriteBuffer failed");
        return 1;
    }
    log<Verbosity::info>("Copy of host data to buffer object was successful");

    log<Verbosity::info>("Copying data from buffer object to memory allocated on host via clEnqueueWriteBuffer");
    destinationBuffer.fill(0);
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, bufferObject, CL_TRUE, 0, sizeof(destinationBuffer), destinationBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBuffer failed");
        return 1;
    }
    log<Verbosity::info>("Copy of data from buffer object to host was successful");

    validateOutput(sourceBuffer, destinationBuffer);
}
