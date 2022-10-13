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
#include "test/utils/l0_common_steps.h"

#include <cstdint>
#include <vector>

bool getContextStatus(ze_context_handle_t context) {
    const auto zeContextGetStatusResult = zeContextGetStatus(context);
    log<Verbosity::info>("L0 context status is: %d", static_cast<int>(zeContextGetStatusResult));

    return true;
}

bool createContextEx(ze_driver_handle_t driver, std::vector<ze_device_handle_t> &devices, ze_context_handle_t &contextEx) {
    ze_context_desc_t contextDescription{};
    contextDescription.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;

    const auto numDevices = static_cast<uint32_t>(devices.size());
    const auto zeContextCreateExResult = zeContextCreateEx(driver, &contextDescription, numDevices, devices.data(), &contextEx);
    if (zeContextCreateExResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextCreateEx() call has failed! Error code = %d", static_cast<int>(zeContextCreateExResult));
        return false;
    }

    log<Verbosity::info>("L0 context has been created! contextEx = %p", static_cast<void *>(contextEx));
    return true;
}

int main(int argc, const char *argv[]) {
    using Cal::Testing::Utils::LevelZero::createContext;
    using Cal::Testing::Utils::LevelZero::destroyContext;
    using Cal::Testing::Utils::LevelZero::getDevices;
    using Cal::Testing::Utils::LevelZero::getDrivers;
    using Cal::Testing::Utils::LevelZero::initL0;

    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    ze_context_handle_t context{};
    ze_context_handle_t contextEx{};

    RUN_REQUIRED_STEP(createContext(drivers[0], context));
    RUN_REQUIRED_STEP(getContextStatus(context));
    RUN_REQUIRED_STEP(destroyContext(context));

    RUN_REQUIRED_STEP(createContextEx(drivers[0], devices, contextEx));
    RUN_REQUIRED_STEP(getContextStatus(contextEx));
    RUN_REQUIRED_STEP(destroyContext(contextEx));

    return 0;
}
