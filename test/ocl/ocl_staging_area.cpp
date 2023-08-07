/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test/utils/ocl_common_steps.h"

#include <array>

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
    log<Verbosity::info>("Succesfully created cl_command_queue : %p", queue);

    constexpr size_t NUM_ELEMENTS_TO_COPY = 1024;
    auto bufferObject = clCreateBuffer(context, CL_MEM_READ_WRITE, NUM_ELEMENTS_TO_COPY * sizeof(int), nullptr, &cl_err);
    if ((nullptr == bufferObject) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create buffer object with error : %d", cl_err);
        return 1;
    };
    log<Verbosity::info>("Succesfully created buffer object : %p", bufferObject);

    std::array<int, NUM_ELEMENTS_TO_COPY> sourceBuffer;
    sourceBuffer.fill(1);
    if (CL_SUCCESS != clEnqueueWriteBuffer(queue, bufferObject, CL_TRUE, 0, sizeof(sourceBuffer), sourceBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueWriteBuffer failed");
        return 1;
    }

    std::array<int, NUM_ELEMENTS_TO_COPY> destinationBuffer{0};
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, bufferObject, CL_TRUE, 0, sizeof(destinationBuffer), destinationBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBuffer failed");
        return 1;
    }

    for (size_t i = 0; i < NUM_ELEMENTS_TO_COPY; i++) {
        if (sourceBuffer[i] != destinationBuffer[i]) {
            log<Verbosity::error>("Mismatch between source and destination data");
            return -1;
        }
    }
    log<Verbosity::info>("Source and destination data is correct");
}
