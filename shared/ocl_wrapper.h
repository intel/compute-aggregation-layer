/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "log.h"
#include "shared/ocl_fat_def.h"

#include <cinttypes>
#include <cstring>
#include <optional>
#include <regex>
#include <string>

namespace Cal {

namespace Utils {

namespace OclApiWrapper {

static constexpr cl_platform_id invalidPlatform = {};

inline cl_platform_id getPlatformByName(const char *matcher, bool matcherIsRegex) {
    cl_uint numPlatforms = {};

    auto err = clGetPlatformIDs(0, nullptr, &numPlatforms);
    if (err) {
        log<Verbosity::error>("clGetPlatformIDS failed with %d", err);
        return invalidPlatform;
    }

    if (0 == numPlatforms) {
        log<Verbosity::info>("clGetPlatformIDS returned 0 platforms");
        return invalidPlatform;
    }

    std::vector<cl_platform_id> platforms(4, 0);
    platforms.resize(numPlatforms);
    err = clGetPlatformIDs(numPlatforms, platforms.data(), nullptr);
    if (err) {
        log<Verbosity::error>("clGetPlatformIDS failed with %d", err);
        return invalidPlatform;
    }

    cl_platform_id foundPlatformId = invalidPlatform;
    std::vector<char> platformName(256, 0);
    std::regex regexMatcher;
    if (matcherIsRegex) {
        regexMatcher = matcher;
    }
    for (auto p : platforms) {
        size_t nameLen = 0U;
        if (CL_SUCCESS != (err = clGetPlatformInfo(p, CL_PLATFORM_NAME, 0, nullptr, &nameLen))) {
            log<Verbosity::error>("clGetPlatformInfo(..., CL_PLATFORM_NAME, ...) failed with %d", err);
        }
        platformName.resize(nameLen);
        if (CL_SUCCESS != (err = clGetPlatformInfo(p, CL_PLATFORM_NAME, platformName.size(), platformName.data(), nullptr))) {
            log<Verbosity::error>("clGetPlatformInfo(..., CL_PLATFORM_NAME, ...) failed with %d", err);
            continue;
        }

        bool matched = matcherIsRegex ? std::regex_search(platformName.data(), regexMatcher) : (0 == strcmp(platformName.data(), matcher));

        if (matched) {
            foundPlatformId = p;
            break;
        }
    }

    if (invalidPlatform == foundPlatformId) {
        platformName.resize(platformName.capacity());
        std::string platformNamesFound = "";
        for (auto p : platforms) {
            if (CL_SUCCESS != (err = clGetPlatformInfo(p, CL_PLATFORM_NAME, platformName.size(), platformName.data(), nullptr))) {
                log<Verbosity::error>("clGetPlatformInfo(..., CL_PLATFORM_NAME, ...) failed with %d", err);
                continue;
            }
            platformNamesFound += std::string("[") + platformName.data() + "], ";
        }
        log<Verbosity::debug>("Could not find requested platform, found (%d platforms) : %s was looking for [%s] (%s)",
                              static_cast<uint32_t>(platforms.size()), platformNamesFound.data(), matcher, (matcherIsRegex ? "regular expression" : "exact string match"));
        return invalidPlatform;
    }

    return foundPlatformId;
}

inline cl_platform_id getPlatformByOrdinal(int ordinal) {
    cl_uint numPlatforms = {};

    auto err = clGetPlatformIDs(0, nullptr, &numPlatforms);
    if (err) {
        log<Verbosity::error>("clGetPlatformIDS failed with %d", err);
        return invalidPlatform;
    }

    if (0 == numPlatforms) {
        log<Verbosity::info>("clGetPlatformIDS returned 0 platforms");
        return invalidPlatform;
    }

    if ((ordinal < 0) || (static_cast<cl_uint>(ordinal + 1) > numPlatforms)) {
        log<Verbosity::info>("Platform with ordinal %d does not exist", ordinal);
        return invalidPlatform;
    }

    std::vector<cl_platform_id> platforms(numPlatforms, 0);
    platforms.resize(numPlatforms);
    err = clGetPlatformIDs(numPlatforms, platforms.data(), nullptr);
    if (err) {
        log<Verbosity::error>("clGetPlatformIDS failed with %d", err);
        return invalidPlatform;
    }

    log<Verbosity::debug>("Returning platform with ordinal %d", ordinal);
    return platforms[ordinal];
}

inline std::vector<cl_device_id> getDevicesForPlatform(cl_platform_id platform, cl_device_type deviceType = CL_DEVICE_TYPE_ALL) {
    cl_uint numDevices = 0;
    if (CL_SUCCESS != clGetDeviceIDs(platform, deviceType, 0, nullptr, &numDevices)) {
        log<Verbosity::error>("clGetDeviceIDs(...., &numDevices) failed");
        return {};
    }

    std::vector<cl_device_id> ret;
    ret.resize(numDevices);
    if (CL_SUCCESS != clGetDeviceIDs(platform, deviceType, numDevices, ret.data(), nullptr)) {
        log<Verbosity::error>("clGetDeviceIDs(...., numDevices, &deviceIDs, ....) failed");
        return {};
    }
    return ret;
}

inline std::string getBuildLog(cl_program program, cl_device_id device) {
    size_t logSize = 0;
    auto ret = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0U, nullptr, &logSize);
    if (CL_SUCCESS != ret) {
        log<Verbosity::error>("clGetProgramBuildInfo(...., CL_PROGRAM_BUILD_LOG ...., logSize) failed with %d", ret);
        return {};
    }
    std::vector<char> logRaw(logSize);
    ret = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logRaw.size(), logRaw.data(), nullptr);
    if (CL_SUCCESS != ret) {
        log<Verbosity::error>("clGetProgramBuildInfo(...., CL_PROGRAM_BUILD_LOG, logRaw, logRaw.size() ....) failed with %d", ret);
        return {};
    }
    return logRaw.data();
}

namespace Extensions {
struct Usm {
    Usm() {
    }

    static std::optional<Usm> load(cl_platform_id platform) {
        Usm usm = {};
        usm.clEnqueueMemFillINTEL = reinterpret_cast<decltype(clEnqueueMemFillINTEL)>(clGetExtensionFunctionAddressForPlatform(platform, "clEnqueueMemFillINTEL"));
        usm.clEnqueueMemcpyINTEL = reinterpret_cast<decltype(clEnqueueMemcpyINTEL)>(clGetExtensionFunctionAddressForPlatform(platform, "clEnqueueMemcpyINTEL"));
        usm.clSetKernelArgMemPointerINTEL = reinterpret_cast<decltype(clSetKernelArgMemPointerINTEL)>(clGetExtensionFunctionAddressForPlatform(platform, "clSetKernelArgMemPointerINTEL"));
        usm.clDeviceMemAllocINTEL = reinterpret_cast<decltype(clDeviceMemAllocINTEL)>(clGetExtensionFunctionAddressForPlatform(platform, "clDeviceMemAllocINTEL"));
        usm.clHostMemAllocINTEL = reinterpret_cast<decltype(clHostMemAllocINTEL)>(clGetExtensionFunctionAddressForPlatform(platform, "clHostMemAllocINTEL"));
        usm.clMemFreeINTEL = reinterpret_cast<decltype(clMemFreeINTEL)>(clGetExtensionFunctionAddressForPlatform(platform, "clMemFreeINTEL"));
        bool valid = true;
        if (nullptr == usm.clEnqueueMemFillINTEL) {
            log<Verbosity::info>("Could not load clEnqueueMemFillINTEL");
            valid = false;
        }
        if (nullptr == usm.clEnqueueMemcpyINTEL) {
            log<Verbosity::info>("Could not load clEnqueueMemcpyINTEL");
            valid = false;
        }
        if (nullptr == usm.clSetKernelArgMemPointerINTEL) {
            log<Verbosity::info>("Could not load clSetKernelArgMemPointerINTEL");
            valid = false;
        }
        if (nullptr == usm.clDeviceMemAllocINTEL) {
            log<Verbosity::info>("Could not load clDeviceMemAllocINTEL");
            valid = false;
        }
        if (nullptr == usm.clHostMemAllocINTEL) {
            log<Verbosity::info>("Could not load clHostMemAllocINTEL");
            valid = false;
        }
        if (nullptr == usm.clMemFreeINTEL) {
            log<Verbosity::info>("Could not load clMemFreeINTEL");
            valid = false;
        }
        return valid ? std::optional<Usm>(usm) : std::nullopt;
    }

    cl_int (*clEnqueueMemFillINTEL)(
        cl_command_queue commandQueue,
        void *dstPtr,
        const void *pattern,
        size_t patternSize,
        size_t size,
        cl_uint numEventsInWaitList,
        const cl_event *eventWaitList,
        cl_event *event) = nullptr;

    cl_int (*clEnqueueMemcpyINTEL)(
        cl_command_queue commandQueue,
        cl_bool blocking,
        void *dstPtr,
        const void *srcPtr,
        size_t size,
        cl_uint numEventsInWaitList,
        const cl_event *eventWaitList,
        cl_event *event) = nullptr;

    cl_int (*clSetKernelArgMemPointerINTEL)(
        cl_kernel kernel,
        cl_uint argIndex,
        const void *argValue) = nullptr;

    void *(*clDeviceMemAllocINTEL)(
        cl_context context,
        cl_device_id device,
        const cl_mem_properties_intel *properties,
        size_t size,
        cl_uint alignment,
        cl_int *errcodeRet) = nullptr;

    void *(*clHostMemAllocINTEL)(
        cl_context context,
        const cl_mem_properties_intel *properties,
        size_t size,
        cl_uint alignment,
        cl_int *errcodeRet) = nullptr;

    cl_int (*clMemFreeINTEL)(
        cl_context context,
        void *ptr) = nullptr;
};
} // namespace Extensions

template <typename T>
inline std::string as_str(const T v) {
    return std::to_string(v);
}

inline std::string as_str(const cl_device_id v) {
    char buff[1024];
    std::sprintf(buff, "%p", v);
    return buff;
}

inline std::string as_str(const unsigned int v) {
    char buff[1024];
    std::sprintf(buff, "%x", v);
    return buff;
}

inline std::string as_str(const uint64_t v) {
    char buff[1024];
    std::sprintf(buff, "0x%" PRIx64, v);
    return buff;
}

struct StringInfo {
    std::string value;
    std::string str() { return value; }
    template <int Key, typename FReadSize, typename FReadValue>
    bool readImpl(const FReadSize &readSize, const FReadValue &readValue) {
        auto size = readSize(Key);
        value.resize(size);
        if (false == readValue(Key, value.data(), size)) {
            return false;
        }
        value.resize(value.size() - 1);
        return true;
    }

    bool operator==(const StringInfo &rhs) const {
        return value == rhs.value;
    }
};
struct ClUlongInfo {
    cl_ulong value;
    std::string str() { return as_str(value); }
    template <int Key, typename FReadSize, typename FReadValue>
    bool readImpl(const FReadSize &readSize, const FReadValue &readValue) {
        value = {};
        return readValue(Key, &value, sizeof(value));
    }

    bool operator==(const ClUlongInfo &rhs) const {
        return value == rhs.value;
    }
};

struct ClUintInfo {
    cl_uint value;
    std::string str() { return as_str(value); }
    template <int Key, typename FReadSize, typename FReadValue>
    bool readImpl(const FReadSize &readSize, const FReadValue &readValue) {
        value = {};
        return readValue(Key, &value, sizeof(value));
    }

    bool operator==(const ClUintInfo &rhs) const {
        return value == rhs.value;
    }
};

template <typename T>
struct ClInfoArray {
    std::vector<T> value;
    std::string str() {
        std::string ret = "{";
        for (const auto &v : value) {
            ret += as_str(v) + ", ";
        }
        ret += "}";
        return ret;
    }
    template <int Key, typename FReadSize, typename FReadValue>
    bool readImpl(const FReadSize &readSize, const FReadValue &readValue) {
        auto size = readSize(Key);
        value.resize(size / sizeof(T));
        if (false == readValue(Key, value.data(), size)) {
            return false;
        }
        return true;
    }

    bool operator==(const ClInfoArray<T> &rhs) const {
        return value == rhs.value;
    }
};

template <template <int Key> class Generator, int... Keys>
struct Infos : Generator<Keys>... {
    template <typename... FormatStringsT>
    std::string format(FormatStringsT... formatStrings) {
        std::string ret = ((formatStrings + std::string(" : ") + Generator<Keys>::str() + "\n") + ...);
        return ret;
    }

    template <int Key>
    auto info() -> decltype(this->Generator<Key>::value) & {
        return this->Generator<Key>::value;
    }

    template <typename FReadSize, typename FReadValue>
    bool readImpl(const FReadSize &readSize, const FReadValue &readValue) {
        return (Generator<Keys>::template readImpl<Keys>(readSize, readValue) && ...);
    }

    bool operator==(const Infos &rhs) const {
        return (Generator<Keys>::operator==(static_cast<Generator<Keys>>(rhs)) && ...);
    }

    bool operator!=(const Infos &rhs) const {
        return false == (*this == rhs);
    }
};

template <int Key>
struct PlatfomInfoC : StringInfo {};
template <>
struct PlatfomInfoC<CL_PLATFORM_HOST_TIMER_RESOLUTION> : ClUlongInfo {};

struct PlatformInfo : Infos<PlatfomInfoC, CL_PLATFORM_PROFILE, CL_PLATFORM_VERSION, CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
                            CL_PLATFORM_EXTENSIONS, CL_PLATFORM_HOST_TIMER_RESOLUTION> {
    std::string str() {
        return this->format("CL_PLATFORM_PROFILE", "CL_PLATFORM_VERSION", "CL_PLATFORM_NAME", "CL_PLATFORM_VENDOR",
                            "CL_PLATFORM_EXTENSIONS", "CL_PLATFORM_HOST_TIMER_RESOLUTION");
    }

    bool read(cl_platform_id platform) {
        auto readSize = [=](cl_platform_info param_name) { size_t ret; return CL_SUCCESS == clGetPlatformInfo(platform, param_name, 0, nullptr, &ret) ? ret : 0ul; };
        auto readVal = [=](cl_platform_info param_name, void *dst, size_t dstSize) { return CL_SUCCESS == clGetPlatformInfo(platform, param_name, dstSize, dst, nullptr); };
        return this->readImpl(readSize, readVal);
    }
};

template <int Key>
struct DeviceInfoC : ClUlongInfo {};

template <typename InfoT = Infos<DeviceInfoC, CL_DEVICE_TYPE, CL_DEVICE_VENDOR_ID, CL_DEVICE_MAX_COMPUTE_UNITS, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>>
struct DeviceInfo : InfoT {
    std::string str() {
        return this->format("CL_DEVICE_TYPE", "CL_DEVICE_VENDOR_ID", "CL_DEVICE_MAX_COMPUTE_UNITS", "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS") + "\n (not all device_info is presented)";
    }

    bool read(cl_device_id device) {
        auto readSize = [=](cl_device_info param_name) { size_t ret; clGetDeviceInfo(device, param_name, 0, nullptr, &ret); return ret; };
        auto readVal = [=](cl_device_info param_name, void *dst, size_t dstSize) { return CL_SUCCESS == clGetDeviceInfo(device, param_name, dstSize, dst, nullptr); };
        return this->readImpl(readSize, readVal);
    }
};

template <int Key>
struct ContextInfoC : ClUintInfo {};
template <>
struct ContextInfoC<CL_CONTEXT_DEVICES> : ClInfoArray<cl_device_id> {};
template <>
struct ContextInfoC<CL_CONTEXT_PROPERTIES> : ClInfoArray<cl_context_properties> {};

struct ContextInfo : Infos<ContextInfoC, CL_CONTEXT_REFERENCE_COUNT, CL_CONTEXT_NUM_DEVICES, CL_CONTEXT_DEVICES, CL_CONTEXT_PROPERTIES> {
    std::string str() {
        return this->format("CL_CONTEXT_REFERENCE_COUNT", "CL_CONTEXT_NUM_DEVICES", "CL_CONTEXT_DEVICES", "CL_CONTEXT_PROPERTIES");
    }

    bool read(cl_context ctx) {
        auto readSize = [=](cl_context_info param_name) { size_t ret; clGetContextInfo(ctx, param_name, 0, nullptr, &ret); return ret; };
        auto readVal = [=](cl_context_info param_name, void *dst, size_t dstSize) { return CL_SUCCESS == clGetContextInfo(ctx, param_name, dstSize, dst, nullptr); };
        return this->readImpl(readSize, readVal);
    }
};

template <int Key>
struct KernelInfoC : ClUintInfo {};
template <>
struct KernelInfoC<CL_KERNEL_FUNCTION_NAME> : StringInfo {};
template <>
struct KernelInfoC<CL_KERNEL_ATTRIBUTES> : StringInfo {};
template <>
struct KernelInfoC<CL_KERNEL_CONTEXT> : ClUlongInfo {};
template <>
struct KernelInfoC<CL_KERNEL_PROGRAM> : ClUlongInfo {};

struct KernelInfo : Infos<KernelInfoC, CL_KERNEL_FUNCTION_NAME, CL_KERNEL_NUM_ARGS, CL_KERNEL_REFERENCE_COUNT, CL_KERNEL_CONTEXT, CL_KERNEL_PROGRAM, CL_KERNEL_ATTRIBUTES> {
    std::string str() {
        return this->format("CL_KERNEL_FUNCTION_NAME", "CL_KERNEL_NNUM_ARGS", "CL_KERNEL_REFERENCE_COUNT", "CL_KERNEL_CONTEXT", "CL_KERNEL_PROGRAM", "CL_KERNEL_ATTRIBUTES");
    }

    bool read(cl_kernel kernel) {
        auto readSize = [=](cl_kernel_info param_name) { size_t ret; clGetKernelInfo(kernel, param_name, 0, nullptr, &ret); return ret; };
        auto readVal = [=](cl_kernel_info param_name, void *dst, size_t dstSize) { return CL_SUCCESS == clGetKernelInfo(kernel, param_name, dstSize, dst, nullptr); };
        return this->readImpl(readSize, readVal);
    }
};

template <int Key>
struct KernelArgInfoC : ClUintInfo {};
template <>
struct KernelArgInfoC<CL_KERNEL_ARG_TYPE_NAME> : StringInfo {};
template <>
struct KernelArgInfoC<CL_KERNEL_ARG_NAME> : StringInfo {};
template <>
struct KernelArgInfoC<CL_KERNEL_ARG_TYPE_QUALIFIER> : ClUlongInfo {};

struct KernelArgInfo : Infos<KernelArgInfoC, CL_KERNEL_ARG_ADDRESS_QUALIFIER, CL_KERNEL_ARG_ACCESS_QUALIFIER, CL_KERNEL_ARG_TYPE_NAME, CL_KERNEL_ARG_TYPE_QUALIFIER, CL_KERNEL_ARG_NAME> {
    std::string str() {
        return this->format("CL_KERNEL_ARG_ADDRESS_QUALIFIER", "CL_KERNEL_ARG_ACCESS_QUALIFIER", "CL_KERNEL_ARG_TYPE_NAME", "CL_KERNEL_ARG_TYPE_QUALIFIER", "CL_KERNEL_ARG_NAME");
    }

    bool read(cl_kernel kernel, uint32_t argIndex) {
        auto readSize = [=](cl_kernel_arg_info param_name) { size_t ret; clGetKernelArgInfo(kernel, argIndex, param_name, 0, nullptr, &ret); return ret; };
        auto readVal = [=](cl_kernel_arg_info param_name, void *dst, size_t dstSize) { return CL_SUCCESS == clGetKernelArgInfo(kernel, argIndex, param_name, dstSize, dst, nullptr); };
        return this->readImpl(readSize, readVal);
    }
};

} // namespace OclApiWrapper

} // namespace Utils

} // namespace Cal
