/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/dynamic_library.h"
#include "test/utils/l0_common_steps.h"

#include <cinttypes>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

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

    auto baseDescExt = static_cast<const ze_base_desc_t *>(outProperties.pNext);
    if (baseDescExt && baseDescExt->stype == ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD) {
        auto exportFdExtension = static_cast<const ze_external_memory_export_fd_t *>(outProperties.pNext);
        log<Verbosity::info>("Received exported file descriptor of allocation = %d!", exportFdExtension->fd);
    }

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

bool getIpcHandleOfNonUsmDeviceMemory(ze_context_handle_t context, void *nonUsmDeviceBuffer) {
    log<Verbosity::info>("Trying to get ze_ipc_mem_handle_t of nonUsmDeviceBuffer!");

    ze_ipc_mem_handle_t ipcHandle{};

    const auto zeMemGetIpcHandleResult = zeMemGetIpcHandle(context, nonUsmDeviceBuffer, &ipcHandle);
    if (zeMemGetIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zeMemGetIpcHandle() failed as expected for non USM device buffer!");
        return true;
    }

    log<Verbosity::error>("Unexpectedly, zeMemGetIpcHandle() returned ZE_RESULT_SUCCESS for non USM device buffer!");
    return false;
}

bool getIpcHandle(ze_context_handle_t context, void *usmDeviceBuffer, ze_ipc_mem_handle_t &ipcHandleOfUsmDeviceBuffer) {
    const auto zeMemGetIpcHandleResult = zeMemGetIpcHandle(context, usmDeviceBuffer, &ipcHandleOfUsmDeviceBuffer);
    if (zeMemGetIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zeMemGetIpcHandle() has failed! Error code: %d", static_cast<int>(zeMemGetIpcHandleResult));
        return false;
    }

    uint64_t firstBytes{};
    std::memcpy(&firstBytes, ipcHandleOfUsmDeviceBuffer.data, sizeof(firstBytes));

    log<Verbosity::info>("Successfully got IPC handle of %p! First bytes of handle as u64 = " PRIu64, usmDeviceBuffer, firstBytes);
    return true;
}

bool openIpcHandle(ze_context_handle_t context, ze_device_handle_t device, const ze_ipc_mem_handle_t &ipcHandle, void *&outPtr) {
    ze_ipc_memory_flags_t flags{0};

    const auto zeMemOpenIpcHandleResult = zeMemOpenIpcHandle(context, device, ipcHandle, flags, &outPtr);
    if (zeMemOpenIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zeMemOpenIpcHandle() has failed! Error code: %d", static_cast<int>(zeMemOpenIpcHandleResult));
        return false;
    }

    log<Verbosity::info>("Successfully opened IPC handle! Returned pointer: %p", outPtr);
    return true;
}

bool closeIpcHandle(ze_context_handle_t context, void *ptr) {
    const auto zeMemCloseIpcHandleResult = zeMemCloseIpcHandle(context, ptr);
    if (zeMemCloseIpcHandleResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemCloseIpcHandle() failed! Error code: %d", static_cast<int>(zeMemCloseIpcHandleResult));
        return false;
    }

    log<Verbosity::info>("Successfully closed the opened IPC handle!");
    return true;
}

bool parseSkipIpcHandlesTests(int argc, const char **argv) {
    for (int i = 0; i < argc; ++i) {
        if (0 == strcmp(argv[i], "--skip-ipc-handles-tests")) {
            return true;
        }
    }

    return false;
}

bool contextMakeMemoryResident(ze_context_handle_t context, ze_device_handle_t device, void *ptr, size_t size) {
    const auto zeContextMakeMemoryResidentResult = zeContextMakeMemoryResident(context, device, ptr, size);
    if (zeContextMakeMemoryResidentResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextMakeMemoryResident() failed! Error code: %d", static_cast<int>(zeContextMakeMemoryResidentResult));
        return false;
    }

    return true;
}

bool contextEvictMemory(ze_context_handle_t context, ze_device_handle_t device, void *ptr, size_t size) {
    const auto zeContextEvictMemoryResult = zeContextEvictMemory(context, device, ptr, size);
    if (zeContextEvictMemoryResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextEvictMemory() failed! Error code: %d", static_cast<int>(zeContextEvictMemoryResult));
        return false;
    }

    return true;
}

int main(int argc, const char *argv[]) {
    using namespace Cal::Testing::Utils::LevelZero;

    bool skipIpcHandlesTests = parseSkipIpcHandlesTests(argc, argv);
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

    const ze_relaxed_allocation_limits_exp_desc_t descExtension = {
        ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC, // stype
        nullptr,                                              // pNext
        ZE_RELAXED_ALLOCATION_LIMITS_EXP_FLAG_MAX_SIZE        // flags
    };

    void *usmHostBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, usmHostBuffer, &descExtension));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0xAA, bufferSize));

    ze_memory_allocation_properties_t usmHostBufferAllocProps{};
    ze_device_handle_t usmHostBufferDeviceHandle{};

    RUN_REQUIRED_STEP(getAllocationProperties(context, usmHostBuffer, usmHostBufferAllocProps, usmHostBufferDeviceHandle));
    RUN_REQUIRED_STEP(ensureMemoryType(ZE_MEMORY_TYPE_HOST, usmHostBufferAllocProps.type));
    RUN_REQUIRED_STEP(ensureNullptr(usmHostBufferDeviceHandle));

    void *usmSharedBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateSharedMemory(context, bufferSize, alignment, devices[0], usmSharedBuffer));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmSharedBuffer, 0xBB, bufferSize));

    ze_memory_allocation_properties_t usmSharedBufferAllocProps{};
    ze_device_handle_t usmSharedBufferDeviceHandle{};

    RUN_REQUIRED_STEP(getAllocationProperties(context, usmSharedBuffer, usmSharedBufferAllocProps, usmSharedBufferDeviceHandle));
    RUN_REQUIRED_STEP(ensureMemoryType(ZE_MEMORY_TYPE_SHARED, usmSharedBufferAllocProps.type));
    RUN_OPTIONAL_STEP(ensurePointersEqual(devices[0], usmSharedBufferDeviceHandle));

    void *usmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], usmDeviceBuffer));

    ze_memory_allocation_properties_t usmDeviceBufferAllocProps = {ZE_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES};
    ze_device_handle_t usmDeviceBufferDeviceHandle{};

    RUN_REQUIRED_STEP(getAllocationProperties(context, usmDeviceBuffer, usmDeviceBufferAllocProps, usmDeviceBufferDeviceHandle));
    RUN_REQUIRED_STEP(ensureMemoryType(ZE_MEMORY_TYPE_DEVICE, usmDeviceBufferAllocProps.type));
    RUN_REQUIRED_STEP(ensurePointersEqual(devices[0], usmDeviceBufferDeviceHandle));

    RUN_REQUIRED_STEP(contextMakeMemoryResident(context, devices[0], usmDeviceBuffer, bufferSize));
    RUN_REQUIRED_STEP(contextEvictMemory(context, devices[0], usmDeviceBuffer, bufferSize));

    void *basePtrToQuery{nullptr};
    size_t sizeOfUsmDeviceBuffer{};
    auto usmDeviceBufferWithOffset = static_cast<char *>(usmDeviceBuffer) + 32;

    RUN_REQUIRED_STEP(getAddressRange(context, usmDeviceBufferWithOffset, basePtrToQuery, sizeOfUsmDeviceBuffer));
    RUN_REQUIRED_STEP(ensurePointersEqual(usmDeviceBuffer, basePtrToQuery));
    RUN_REQUIRED_STEP(ensureSizesEqual(bufferSize, sizeOfUsmDeviceBuffer));

    if (!skipIpcHandlesTests) {
        RUN_REQUIRED_STEP(getIpcHandleOfNonUsmDeviceMemory(context, usmHostBuffer));

        ze_external_memory_export_fd_t exportFdExtension = {
            ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD, // stype
            nullptr,                                     // pNext
            ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF,        // flags
            0                                            // fd
        };

        usmDeviceBufferAllocProps = {ZE_STRUCTURE_TYPE_MEMORY_ALLOCATION_PROPERTIES, &exportFdExtension};
        RUN_REQUIRED_STEP(getAllocationProperties(context, usmDeviceBuffer, usmDeviceBufferAllocProps, usmDeviceBufferDeviceHandle));

        ze_ipc_mem_handle_t ipcHandleOfUsmDeviceBuffer{};
        RUN_REQUIRED_STEP(getIpcHandle(context, usmDeviceBuffer, ipcHandleOfUsmDeviceBuffer));

        const ze_external_memory_import_fd_t importFdExtension = {
            ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD, // stype
            nullptr,                                     // pNext
            ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF,        // flags
            exportFdExtension.fd                         // fd
        };

        void *reopenedUsmDeviceBufferViaPNext{nullptr};
        RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], reopenedUsmDeviceBufferViaPNext, &importFdExtension));
        RUN_REQUIRED_STEP(freeMemory(context, reopenedUsmDeviceBufferViaPNext));

        void *reopenedUsmDeviceBuffer{};
        RUN_REQUIRED_STEP(openIpcHandle(context, devices[0], ipcHandleOfUsmDeviceBuffer, reopenedUsmDeviceBuffer));
        RUN_REQUIRED_STEP(closeIpcHandle(context, reopenedUsmDeviceBuffer));
    }

    RUN_REQUIRED_STEP(freeMemory(context, usmDeviceBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmSharedBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, usmHostBuffer));

    {
        void *usmHostBuffer{nullptr};
        RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, usmHostBuffer, nullptr));
        RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0xAA, bufferSize));
        RUN_REQUIRED_STEP(freeMemoryExt(context, usmHostBuffer, ZE_DRIVER_MEMORY_FREE_POLICY_EXT_FLAG_BLOCKING_FREE, "BLOCKING"));
    }

    {
        void *usmHostBuffer{nullptr};
        RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, usmHostBuffer, nullptr));
        RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmHostBuffer, 0xAA, bufferSize));
        RUN_REQUIRED_STEP(freeMemoryExt(context, usmHostBuffer, ZE_DRIVER_MEMORY_FREE_POLICY_EXT_FLAG_DEFER_FREE, "DEFER"));
    }

    for (auto memoryAlignment : {0u, 1u << 0, 1u << 3, 1u << 5, 1u << 8, 1u << 10, 1u << 13, 1u << 15, 1u << 18, 1u << 20, 1u << 22}) {
        constexpr size_t memorySize{1024};

        void *usmHostMemory{nullptr};
        RUN_REQUIRED_STEP(allocateHostMemory(context, memorySize, memoryAlignment, usmHostMemory, nullptr));

        void *usmSharedMemory{nullptr};
        RUN_REQUIRED_STEP(allocateSharedMemory(context, memorySize, memoryAlignment, devices[0], usmSharedMemory));

        RUN_REQUIRED_STEP(freeMemory(context, usmHostMemory));
        RUN_REQUIRED_STEP(freeMemory(context, usmSharedMemory));
    }

    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
