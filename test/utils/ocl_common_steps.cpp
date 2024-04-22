/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test/utils/ocl_common_steps.h"

cl_platform_id getPlatform(int platformOrd) {
    cl_platform_id platform{};
    if (platformOrd >= 0) {
        log<Verbosity::info>("Looking for OCL platform with ordinal %d", platformOrd);
        platform = Cal::Utils::OclApiWrapper::getPlatformByOrdinal(platformOrd);
        if (Cal::Utils::OclApiWrapper::invalidPlatform == platform) {
            log<Verbosity::critical>("Could not find OCL platform with ordinal %d", platformOrd);
            std::abort();
        }
        log<Verbosity::info>("Found OCL platform with ordinal %d", platformOrd);
    } else {
        setenv(calUseCustomOCLPlatformName.data(), "1", true);
        platform = Cal::Utils::OclApiWrapper::getPlatformByName(calPlatformName.data(), false);
        if (Cal::Utils::OclApiWrapper::invalidPlatform == platform) {
            log<Verbosity::critical>("Could not find Compute Aggregation Layer OCL platform");
            std::abort();
        }
        log<Verbosity::info>("Found Compute Aggregation Layer OCL platform");
    }

    Cal::Utils::OclApiWrapper::PlatformInfo platformInfo;
    if (false == platformInfo.read(platform)) {
        log<Verbosity::error>("Could not read platform info");
        std::abort();
    }
    log<Verbosity::info>("Platform info : \n%s\n", platformInfo.str().c_str());

    return platform;
}

std::vector<cl_device_id> getDevices(cl_platform_id platform, cl_device_type deviceType) {
    std::vector<cl_device_id> devices = Cal::Utils::OclApiWrapper::getDevicesForPlatform(platform, deviceType);
    if (devices.empty()) {
        log<Verbosity::info>("No devices in platform");
        std::abort();
    }
    log<Verbosity::info>("Num devices : %zu", devices.size());
    for (auto device : devices) {
        Cal::Utils::OclApiWrapper::DeviceInfo deviceInfo;
        if (false == deviceInfo.read(device)) {
            log<Verbosity::error>("Could not read device info for device %p", device);
            std::abort();
        }
        log<Verbosity::info>("Device %p info : \n%s\n", device, deviceInfo.str().c_str());
        Cal::Utils::OclApiWrapper::DeviceInfo deviceInfoCached;
        if (false == deviceInfoCached.read(device)) {
            log<Verbosity::error>("Could not read cached device info for device %p", device);
            std::abort();
        }
        if (deviceInfo != deviceInfoCached) {
            log<Verbosity::error>("Mismatch on cached device info for device %p", device);
            std::abort();
        }
        log<Verbosity::info>("cached device info OK for device %p", device);
    }

    return devices;
}

cl_context createContext(cl_platform_id platform, const std::vector<cl_device_id> &devices, size_t device_index) {
    log<Verbosity::info>("Creating context for devices[%zu]: %p", device_index, devices[device_index]);
    cl_context_properties properties[3] = {};
    properties[0] = CL_CONTEXT_PLATFORM;
    properties[1] = reinterpret_cast<cl_context_properties>(platform);
    properties[2] = 0;
    cl_int cl_err{};
    cl_context context = clCreateContext(properties, 1, &devices[device_index], nullptr, nullptr, &cl_err);
    if ((nullptr == context) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create context with error : %d", cl_err);
        std::abort();
    };

    Cal::Utils::OclApiWrapper::ContextInfo contextInfo;
    Cal::Utils::OclApiWrapper::ContextInfo contextInfoCached;
    if (false == contextInfo.read(context)) {
        log<Verbosity::error>("Could not read context info");
        std::abort();
    }
    log<Verbosity::info>("Context info : \n%s\n", contextInfo.str().c_str());
    if (false == contextInfoCached.read(context)) {
        log<Verbosity::error>("Could not read cached context info for context %p", context);
        std::abort();
    }
    if (contextInfo != contextInfoCached) {
        log<Verbosity::error>("Mismatch on cached context info for context %p", context);
        std::abort();
    }
    log<Verbosity::info>("cached context info OK for context %p", context);

    return context;
}

cl_program createProgramWithSource(cl_context context, uint32_t numSources, const char **sources) {
    log<Verbosity::info>("Creating program object with source");
    cl_int cl_err{};
    auto program = clCreateProgramWithSource(context, numSources, sources, nullptr, &cl_err);
    if ((nullptr == program) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create program with error : %d", cl_err);
        std::abort();
    };

    log<Verbosity::info>("Succesfully created program : %p", program);
    return program;
}

cl_program createProgramWithBinary(cl_context context, cl_device_id device, const size_t *lengths, unsigned char **binaries) {
    log<Verbosity::info>("Creating a program from retrieved binary!");

    cl_int binaryStatus{};
    cl_int createFromBinaryResult{};
    const auto programFromBinary = clCreateProgramWithBinary(context, 1, &device, lengths, const_cast<const unsigned char **>(binaries), &binaryStatus, &createFromBinaryResult);
    if (binaryStatus != CL_SUCCESS || createFromBinaryResult != CL_SUCCESS || programFromBinary == nullptr) {
        log<Verbosity::error>("Could not create program from retrieved binary! binaryStatus = %d, errorCode = %d",
                              static_cast<int>(binaryStatus),
                              static_cast<int>(createFromBinaryResult));
        std::abort();
    }

    log<Verbosity::info>("Program created successfuly!");
    return programFromBinary;
}

void compileProgram(cl_program program, cl_device_id device) {
    auto cl_err = clCompileProgram(program, 1, &device, "-cl-std=CL2.0", 0, nullptr, nullptr, nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Compilation of program failed with error : %d", cl_err);
        std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, device);
        log<Verbosity::info>("Build log %s", buildLog.c_str());
        std::abort();
    }
    log<Verbosity::info>("Succesfully compiled program : %p", program);
    auto buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, device);
    log<Verbosity::info>("Build log %s", buildLog.c_str());
}

cl_program linkProgram(cl_context context, cl_device_id device, cl_program program) {
    cl_int cl_err{};
    auto linkedProgram = clLinkProgram(context, 1, &device, "-cl-take-global-address", 1, &program, nullptr, nullptr, &cl_err);
    if (CL_SUCCESS != cl_err || linkedProgram == nullptr) {
        log<Verbosity::error>("Link failed with error : %d", cl_err);
        auto buildLog = (linkedProgram ? Cal::Utils::OclApiWrapper::getBuildLog(linkedProgram, device) : "NULL linkedProgram\n");
        log<Verbosity::info>("Build log %s", buildLog.c_str());
        std::abort();
    }
    log<Verbosity::info>("Succesfully linked program : %p", linkedProgram);
    auto buildLog = Cal::Utils::OclApiWrapper::getBuildLog(linkedProgram, device);
    log<Verbosity::info>("Build log %s", buildLog.c_str());

    return linkedProgram;
}

void buildProgram(cl_program program, cl_device_id device) {
    auto cl_err = clBuildProgram(program, 1, &device, "-cl-std=CL2.0", nullptr, nullptr);
    if (CL_SUCCESS != cl_err) {
        log<Verbosity::error>("Build failed with error : %d", cl_err);
        std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, device);
        log<Verbosity::info>("Build log %s", buildLog.c_str());
        std::abort();
    }
    log<Verbosity::info>("Succesfully built program : %p", program);
    std::string buildLog = Cal::Utils::OclApiWrapper::getBuildLog(program, device);
    log<Verbosity::info>("Build log %s", buildLog.c_str());
}

cl_kernel createKernel(cl_program program, const char *kernelName) {
    log<Verbosity::info>("Creating kernel object");
    cl_int cl_err{};
    auto kernel = clCreateKernel(program, kernelName, &cl_err);
    if ((nullptr == kernel) || (CL_SUCCESS != cl_err)) {
        log<Verbosity::error>("Failed to create kernel with error : %d", cl_err);
        std::abort();
    }

    log<Verbosity::info>("Succesfully created kernel : %p", kernel);
    return kernel;
}
