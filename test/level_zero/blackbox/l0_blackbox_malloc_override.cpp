/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "shared/log.h"
#include "shared/sys.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

using namespace Cal::Testing::Utils::LevelZero;

int main() {
    if (false == Cal::Utils::getEnvFlag("CAL_OVERRIDE_MALLOC")) {
        log<Cal::Utils::Log::Verbosity::warning>("This test is intended to be run with CAL_OVERRIDE_MALLOC set.");
    }

    size_t mallocOverrideThreshold = Cal::Utils::getCalEnvI64(calOverrideMallocThresholdEnvName, Cal::Utils::pageSize4KB);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    ze_context_handle_t context{};
    RUN_REQUIRED_STEP(createContext(drivers[0], context));

    uint32_t ordinal{};
    RUN_REQUIRED_STEP(getComputeQueueOrdinal(devices[0], ordinal));
    ze_command_queue_handle_t queue{};
    RUN_REQUIRED_STEP(createCommandQueue(context, devices[0], ordinal, queue, ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_DEFAULT))
    ze_command_list_handle_t cmdList{};
    RUN_REQUIRED_STEP(createCommandList(context, devices[0], ordinal, cmdList));

    size_t smallAllocationMemSize = mallocOverrideThreshold / 2;
    size_t largeAllocationMemSize = mallocOverrideThreshold + 1024;
    log<Verbosity::info>("Allocating malloc memory smaller than threshold - size = %zu", smallAllocationMemSize);
    void *smallAllocationPtr = malloc(smallAllocationMemSize);
    log<Verbosity::info>("Allocating malloc memory larger than threshold - size = %zu", largeAllocationMemSize);
    void *largeAllocationPtr = malloc(largeAllocationMemSize);

    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(smallAllocationPtr, 0x42, smallAllocationMemSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(largeAllocationPtr, 0xCD, largeAllocationMemSize));

    void *usmMemory{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(context, largeAllocationMemSize, 8, usmMemory));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(usmMemory, 0x42, largeAllocationMemSize));

    // copy from unoverriden malloc ptr to overriden malloc ptr
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, largeAllocationPtr, smallAllocationPtr, smallAllocationMemSize));
    RUN_REQUIRED_STEP(closeCommandList(cmdList));

    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(largeAllocationPtr, smallAllocationPtr, smallAllocationMemSize));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    // copy from usm ptr to overriden malloc ptr
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, largeAllocationPtr, usmMemory, largeAllocationMemSize));
    RUN_REQUIRED_STEP(closeCommandList(cmdList));

    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(usmMemory, largeAllocationPtr, largeAllocationMemSize));

    RUN_REQUIRED_STEP(freeMemory(context, usmMemory));
    free(largeAllocationPtr);
    free(smallAllocationPtr);
    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));
    RUN_REQUIRED_STEP(destroyContext(context));
    return 0;
}
