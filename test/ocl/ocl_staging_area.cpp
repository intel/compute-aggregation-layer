/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test/utils/ocl_common_steps.h"

#include <array>

constexpr size_t NUM_ELEMENTS_TO_COPY = 1024;
constexpr size_t BUFFER_SIZE = NUM_ELEMENTS_TO_COPY * sizeof(int);

template <typename T, size_t N>
bool validateOutput(const std::array<T, N> &x, const std::array<T, N> &y) {
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

bool enqueueMemcpyINTEL(Cal::Utils::OclApiWrapper::Extensions::Usm &usmExt, cl_context context, std::vector<cl_device_id> &devices,
                        size_t deviceIndex, cl_command_queue queue) {
    cl_int cl_err{};
    auto usmDevice = usmExt.clDeviceMemAllocINTEL(context, devices[deviceIndex], nullptr, BUFFER_SIZE, 0, &cl_err);
    if ((nullptr == usmDevice) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create usm device memory with error : %d", cl_err);
        return false;
    }
    log<Verbosity::info>("Successfully created USM device memory: %p", usmDevice);

    std::array<int, NUM_ELEMENTS_TO_COPY> sourceBuffer;
    sourceBuffer.fill(1);
    log<Verbosity::info>("Copying data allocated on host to usm device via clEnqueueMemcpyINTEL");
    auto result = usmExt.clEnqueueMemcpyINTEL(queue, CL_TRUE, usmDevice, sourceBuffer.data(), sizeof(sourceBuffer), 0,
                                              nullptr, nullptr);
    if (CL_SUCCESS != result) {
        log<Verbosity::error>("clEnqueueMemcpyINTEL failed");
        return false;
    }
    log<Verbosity::info>("Copy of host data to usm device was successful");

    log<Verbosity::info>("Copying usm device data to host allocation via clEnqueueMemcpyINTEL");
    std::array<int, NUM_ELEMENTS_TO_COPY> destinationBuffer{0};
    if (CL_SUCCESS != usmExt.clEnqueueMemcpyINTEL(queue, CL_TRUE, destinationBuffer.data(), usmDevice, BUFFER_SIZE, 0,
                                                  nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBuffer failed");
        return false;
    }
    log<Verbosity::info>("Copy of usm device data to host allocation was successful");

    usmExt.clMemFreeINTEL(context, usmDevice);
    return validateOutput(sourceBuffer, destinationBuffer);
}

bool enqueueBuffer(cl_context context, cl_command_queue queue) {
    cl_int cl_err{};
    auto bufferObject = clCreateBuffer(context, CL_MEM_READ_WRITE, BUFFER_SIZE, nullptr, &cl_err);
    if ((nullptr == bufferObject) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create buffer object with error : %d", cl_err);
        return false;
    };
    log<Verbosity::info>("successfully created buffer object : %p", bufferObject);

    std::array<int, NUM_ELEMENTS_TO_COPY> sourceBuffer;
    sourceBuffer.fill(1);
    log<Verbosity::info>("Copying data allocated on host to buffer object via clEnqueueWriteBuffer");
    if (CL_SUCCESS != clEnqueueWriteBuffer(queue, bufferObject, CL_TRUE, 0, sizeof(sourceBuffer), sourceBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueWriteBuffer failed");
        return false;
    }
    log<Verbosity::info>("Copy of host data to buffer object was successful");

    log<Verbosity::info>("Copying data from buffer object to memory allocated on host via clEnqueueReadBuffer");
    std::array<int, NUM_ELEMENTS_TO_COPY> destinationBuffer{0};
    if (CL_SUCCESS != clEnqueueReadBuffer(queue, bufferObject, CL_TRUE, 0, sizeof(destinationBuffer), destinationBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBuffer failed");
        return false;
    }
    log<Verbosity::info>("Copy of data from buffer object to host was successful");

    clReleaseMemObject(bufferObject);
    return validateOutput(sourceBuffer, destinationBuffer);
}

bool enqueueBufferRect(cl_context context, cl_command_queue queue) {
    size_t buffOrigin[] = {0, 0, 0};
    size_t hostOrigin[] = {0, 0, 0};
    size_t region[] = {NUM_ELEMENTS_TO_COPY, NUM_ELEMENTS_TO_COPY, 1};
    cl_int cl_err{};

    auto bufferObject = clCreateBuffer(context, CL_MEM_READ_WRITE, NUM_ELEMENTS_TO_COPY * NUM_ELEMENTS_TO_COPY, nullptr, &cl_err);
    if ((nullptr == bufferObject) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create buffer object with error : %d", cl_err);
        return false;
    };
    log<Verbosity::info>("successfully created buffer object : %p", bufferObject);

    std::array<char, NUM_ELEMENTS_TO_COPY * NUM_ELEMENTS_TO_COPY> sourceBufferRect;
    sourceBufferRect.fill(1);
    log<Verbosity::info>("Copying data allocated on host to buffer object via clEnqueueWriteBufferRect");
    if (CL_SUCCESS != clEnqueueWriteBufferRect(queue, bufferObject, CL_TRUE, buffOrigin, hostOrigin, region, NUM_ELEMENTS_TO_COPY, 0, NUM_ELEMENTS_TO_COPY, 0, sourceBufferRect.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueWriteBufferRect failed");
        return false;
    }
    log<Verbosity::info>("Copy of host data to buffer object was successful");

    std::array<char, NUM_ELEMENTS_TO_COPY * NUM_ELEMENTS_TO_COPY> destinationBufferRect{0};
    log<Verbosity::info>("Copying data from buffer object to memory allocated on host via clEnqueueReadBufferRect");
    if (CL_SUCCESS != clEnqueueReadBufferRect(queue, bufferObject, CL_TRUE, buffOrigin, hostOrigin, region, NUM_ELEMENTS_TO_COPY, 0, NUM_ELEMENTS_TO_COPY, 0, destinationBufferRect.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadBufferRect failed");
        return false;
    }
    log<Verbosity::info>("Copy of data from buffer object to host was successful");

    clReleaseMemObject(bufferObject);
    return validateOutput(sourceBufferRect, destinationBufferRect);
}

bool enqueueImage(cl_context context, cl_command_queue queue) {
    cl_image_format imageFormat{CL_R, CL_UNSIGNED_INT8};
    constexpr size_t WIDTH = 100;
    cl_image_desc imageDescriptor{CL_MEM_OBJECT_IMAGE1D, WIDTH, 1, 1, 1, 0, 0, 0, 0, {nullptr}};
    cl_int cl_err{};
    log<Verbosity::info>("Creating image via clCreateImage");
    auto image = clCreateImage(context, CL_MEM_READ_WRITE, &imageFormat, &imageDescriptor, nullptr, &cl_err);
    if (image == nullptr || cl_err != CL_SUCCESS) {
        log<Verbosity::critical>("clCreateImage failed: %d", cl_err);
    }
    log<Verbosity::info>("Successfully created image");

    const size_t origin[]{0, 0, 0};
    const size_t region[]{WIDTH, 1, 1};
    std::array<char, WIDTH> sourceBuffer{};
    sourceBuffer.fill(1);
    log<Verbosity::info>("Copying data allocated on host to image object via clEnqueueWriteImage");
    if (CL_SUCCESS != clEnqueueWriteImage(queue, image, CL_TRUE, origin, region, WIDTH, 0, sourceBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueWriteImage failed");
        return false;
    }
    log<Verbosity::info>("Copy of host data to image object was successful");

    std::array<char, WIDTH> destinationBuffer{0};
    log<Verbosity::info>("Copying data from image object to memory allocated on host via clEnqueueReadImage");
    if (CL_SUCCESS != clEnqueueReadImage(queue, image, CL_TRUE, origin, region, WIDTH, 0, destinationBuffer.data(), 0, nullptr, nullptr)) {
        log<Verbosity::error>("clEnqueueReadImage failed");
        return false;
    }
    log<Verbosity::info>("Copy of data from image object to host was successful");

    clReleaseMemObject(image);
    return validateOutput(sourceBuffer, destinationBuffer);
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

    if (false == enqueueMemcpyINTEL(usmExt, context, devices, deviceIndex, queue)) {
        log<Verbosity::error>("enqueueMemcpyINTEL scenario has failed");
        return -1;
    }

    if (false == enqueueBuffer(context, queue)) {
        log<Verbosity::error>("enqueueBuffer scenario has failed");
        return -1;
    }

    if (false == enqueueBufferRect(context, queue)) {
        log<Verbosity::error>("enqueueBufferRect scenario has failed");
        return -1;
    }

    if (false == enqueueImage(context, queue)) {
        log<Verbosity::error>("enqueueImage scenario has failed");
        return -1;
    }

    clReleaseContext(context);
    for (const auto &device : devices) {
        clReleaseDevice(device);
    }
}
