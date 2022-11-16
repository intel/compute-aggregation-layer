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

#include <cinttypes>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

using ZexMemGetIpcHandlesT = ze_result_t(ze_context_handle_t, const void *, uint32_t *, ze_ipc_mem_handle_t *);
using ZexMemOpenIpcHandlesT = ze_result_t(ze_context_handle_t, ze_device_handle_t, uint32_t, ze_ipc_mem_handle_t *, ze_ipc_memory_flags_t, void **);

bool getAllIpcHandles(ZexMemGetIpcHandlesT *zexMemGetIpcHandles, ze_context_handle_t context, void *usmDeviceBuffer, std::vector<ze_ipc_mem_handle_t> &allIpcHandlesOfUsmDeviceBuffer) {
    log<Verbosity::info>("Getting count of IPC handles!");

    uint32_t ipcHandlesCount{};
    auto zexMemGetIpcHandlesResult = zexMemGetIpcHandles(context, usmDeviceBuffer, &ipcHandlesCount, nullptr);
    if (zexMemGetIpcHandlesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zexMemGetIpcHandles() failed! Error code: %d", static_cast<int>(zexMemGetIpcHandlesResult));
        return false;
    }

    if (ipcHandlesCount == 0) {
        log<Verbosity::error>("zexMemGetIpcHandles() returned count equals zero! At least one expected.");
        return false;
    }

    log<Verbosity::info>("Getting IPC handles!");
    allIpcHandlesOfUsmDeviceBuffer.resize(ipcHandlesCount);

    zexMemGetIpcHandlesResult = zexMemGetIpcHandles(context, usmDeviceBuffer, &ipcHandlesCount, allIpcHandlesOfUsmDeviceBuffer.data());
    if (zexMemGetIpcHandlesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zexMemGetIpcHandles() failed! Error code: %d", static_cast<int>(zexMemGetIpcHandlesResult));
        return false;
    }

    log<Verbosity::info>("Successfully got IPC handles of %p!", usmDeviceBuffer);

    for (const auto &ipcHandle : allIpcHandlesOfUsmDeviceBuffer) {
        uint64_t firstBytes{};
        std::memcpy(&firstBytes, ipcHandle.data, sizeof(firstBytes));

        log<Verbosity::info>("First bytes (as u64) of ipcHandle[%d] = " PRIu64, firstBytes);
    }

    return true;
}

bool openAllIpcHandles(ZexMemOpenIpcHandlesT *zexMemOpenIpcHandles, ze_context_handle_t context, ze_device_handle_t device, std::vector<ze_ipc_mem_handle_t> &ipcHandles, void *&outPtr) {
    ze_ipc_memory_flags_t flags{0};

    const auto zexMemOpenIpcHandlesResult = zexMemOpenIpcHandles(context, device, ipcHandles.size(), ipcHandles.data(), flags, &outPtr);
    if (zexMemOpenIpcHandlesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zexMemOpenIpcHandles() has failed! Error code: %d", static_cast<int>(zexMemOpenIpcHandlesResult));
        return false;
    }

    log<Verbosity::info>("Successfully opened memory from all IPC handles! Returned pointer: %p", outPtr);
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

    void *usmDeviceBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, bufferSize, alignment, devices[0], usmDeviceBuffer));

    ZexMemGetIpcHandlesT *zexMemGetIpcHandles{};
    RUN_REQUIRED_STEP(getExtensionFunctionAddress(drivers[0], reinterpret_cast<void **>(&zexMemGetIpcHandles), "zexMemGetIpcHandles"));

    std::vector<ze_ipc_mem_handle_t> allIpcHandlesOfUsmDeviceBuffer{};
    RUN_REQUIRED_STEP(getAllIpcHandles(zexMemGetIpcHandles, context, usmDeviceBuffer, allIpcHandlesOfUsmDeviceBuffer));

    ZexMemOpenIpcHandlesT *zexMemOpenIpcHandles{};
    RUN_REQUIRED_STEP(getExtensionFunctionAddress(drivers[0], reinterpret_cast<void **>(&zexMemOpenIpcHandles), "zexMemOpenIpcHandles"));

    void *reopenedUsmDeviceBufferFromAll{};
    RUN_REQUIRED_STEP(openAllIpcHandles(zexMemOpenIpcHandles, context, devices[0], allIpcHandlesOfUsmDeviceBuffer, reopenedUsmDeviceBufferFromAll));
    RUN_REQUIRED_STEP(closeMemIpcHandle(context, reopenedUsmDeviceBufferFromAll));

    RUN_REQUIRED_STEP(freeMemory(context, usmDeviceBuffer));
    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
