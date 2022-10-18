/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/dynamic_library.h"
#include "test/utils/l0_common_steps.h"

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

bool fillBufferOnHostViaMemcpy(void *buffer, int value, size_t bufferSize) {
    log<Verbosity::info>("Filling buffer (%p) of size (%zd) with value (%d)", buffer, bufferSize, value);
    std::memset(buffer, value, bufferSize);

    log<Verbosity::info>("Fill operation was successful!");
    return true;
}

bool getAllocationProperties(ze_context_handle_t context, void *buffer, ze_memory_allocation_properties_t &outProperties, ze_device_handle_t &outDevice) {
    const auto zeMemGetAllocPropertiesResult = zeMemGetAllocProperties(context, buffer, &outProperties, &outDevice);
    if (zeMemGetAllocPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemGetAllocProperties() call has failed! Error code: %d", static_cast<int>(zeMemGetAllocPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Got allocation properties! pageSize=%d, type=%d, id=%d",
                         static_cast<int>(outProperties.pageSize),
                         static_cast<int>(outProperties.type),
                         static_cast<int>(outProperties.id));
    return true;
}

bool ensureMemoryType(ze_memory_type_t expected, ze_memory_type_t actual) {
    if (expected != actual) {
        log<Verbosity::error>("Memory types are different! Expected: %d, Actual: %d", static_cast<int>(expected), static_cast<int>(actual));
        return false;
    }

    log<Verbosity::info>("Memory types are the same!");
    return true;
}

bool getAddressRange(ze_context_handle_t context, void *ptr, void *&outBasePtr, size_t &outSize) {
    const auto zeMemGetAddressRangeResult = zeMemGetAddressRange(context, ptr, &outBasePtr, &outSize);
    if (zeMemGetAddressRangeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemGetAddressRange() call has failed! Error code: %d", static_cast<int>(zeMemGetAddressRangeResult));
        return false;
    }

    log<Verbosity::info>("zeMemGetAddressRange() has been successful! For USM pointer %p base address is %p. Allocation size is %zd", ptr, outBasePtr, outSize);
    return true;
}

bool ensureSizesEqual(size_t expected, size_t actual) {
    if (expected != actual) {
        log<Verbosity::error>("Sizes are different! Expected: %zd, Actual: %zd", expected, actual);
        return false;
    }

    log<Verbosity::info>("Sizes are the same!");
    return true;
}

int main(int argc, const char *argv[]) {
    using namespace Cal::Testing::Utils::LevelZero;

    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    ze_context_handle_t context{};
    RUN_REQUIRED_STEP(createContext(drivers[0], context));

    constexpr size_t bufferSize{1024};
    constexpr size_t alignment{8};

    void *usmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, usmHostBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemcpy(usmHostBuffer, 0xAA, bufferSize));

    ze_memory_allocation_properties_t usmHostBufferAllocProps{};
    ze_device_handle_t usmHostBufferDeviceHandle{};

    RUN_REQUIRED_STEP(getAllocationProperties(context, usmHostBuffer, usmHostBufferAllocProps, usmHostBufferDeviceHandle));
    RUN_REQUIRED_STEP(ensureMemoryType(ZE_MEMORY_TYPE_HOST, usmHostBufferAllocProps.type));
    RUN_REQUIRED_STEP(ensureNullptr(usmHostBufferDeviceHandle));

    void *usmSharedBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateSharedMemory(context, bufferSize, alignment, devices[0], usmSharedBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemcpy(usmSharedBuffer, 0xBB, bufferSize));

    ze_memory_allocation_properties_t usmSharedBufferAllocProps{};
    ze_device_handle_t usmSharedBufferDeviceHandle{};

    RUN_REQUIRED_STEP(getAllocationProperties(context, usmSharedBuffer, usmSharedBufferAllocProps, usmSharedBufferDeviceHandle));
    RUN_REQUIRED_STEP(ensureMemoryType(ZE_MEMORY_TYPE_SHARED, usmSharedBufferAllocProps.type));
    RUN_OPTIONAL_STEP(ensurePointersEqual(devices[0], usmSharedBufferDeviceHandle));

    void *usmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], usmDeviceBuffer));

    ze_memory_allocation_properties_t usmDeviceBufferAllocProps{};
    ze_device_handle_t usmDeviceBufferDeviceHandle{};

    RUN_REQUIRED_STEP(getAllocationProperties(context, usmDeviceBuffer, usmDeviceBufferAllocProps, usmDeviceBufferDeviceHandle));
    RUN_REQUIRED_STEP(ensureMemoryType(ZE_MEMORY_TYPE_DEVICE, usmDeviceBufferAllocProps.type));
    RUN_REQUIRED_STEP(ensurePointersEqual(devices[0], usmDeviceBufferDeviceHandle));

    void *basePtrToQuery{nullptr};
    size_t sizeOfUsmDeviceBuffer{};
    auto usmDeviceBufferWithOffset = static_cast<char *>(usmDeviceBuffer) + 32;

    RUN_REQUIRED_STEP(getAddressRange(context, usmDeviceBufferWithOffset, basePtrToQuery, sizeOfUsmDeviceBuffer));
    RUN_REQUIRED_STEP(ensurePointersEqual(usmDeviceBuffer, basePtrToQuery));
    RUN_REQUIRED_STEP(ensureSizesEqual(bufferSize, sizeOfUsmDeviceBuffer));

    RUN_REQUIRED_STEP(freeMemory(context, usmDeviceBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmSharedBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmHostBuffer));

    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
