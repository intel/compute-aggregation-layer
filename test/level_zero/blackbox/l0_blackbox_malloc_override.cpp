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

    constexpr size_t memSize = 5555;
    void *mallocedPtr = malloc(memSize);
    memset(mallocedPtr, 0x42, memSize);

    void *destMemory{nullptr};
    RUN_REQUIRED_STEP(allocateHostMemory(context, memSize, 8, destMemory));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(destMemory, 0xCD, memSize));

    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, destMemory, mallocedPtr, memSize));
    RUN_REQUIRED_STEP(closeCommandList(cmdList));

    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyMemoryCopyResults(mallocedPtr, destMemory, memSize));

    free(mallocedPtr);
    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));
    RUN_REQUIRED_STEP(destroyContext(context));
    return 0;
}
