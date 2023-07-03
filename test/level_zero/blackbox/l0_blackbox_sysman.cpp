/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "level_zero/zes_api.h"
#include "shared/log.h"
#include "shared/sys.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

bool getZesDeviceProperties(const ze_device_handle_t device) {
    zes_device_properties_t properties{};
    properties.stype = ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES;
    const auto zesDeviceGetPropertiesResult = zesDeviceGetProperties(device, &properties);
    if (zesDeviceGetPropertiesResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
        log<Verbosity::info>("Feature is unsupported by Compute Runtime");
        return true;
    } else if (zesDeviceGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceGetProperties() call has failed! Error code = %d", static_cast<int>(zesDeviceGetPropertiesResult));
        return false;
    }

    std::stringstream ss;
    ss << "Core device properties: \n"
       << " * name : " << properties.core.name << "\n"
       << " * deviceId : " << properties.core.deviceId << "\n"
       << " * numSlices : " << properties.core.numSlices << "\n"
       << " * numSubslicesPerSlice : " << properties.core.numSubslicesPerSlice << "\n"
       << " * numEUsPerSubslice : " << properties.core.numEUsPerSubslice << "\n"
       << " * numThreadsPerEU : " << properties.core.numThreadsPerEU << "\n"
       << " * numSubdevices : " << properties.numSubdevices << "\n"
       << " * serialNumber : " << properties.serialNumber << "\n"
       << " * boardNumber : " << properties.boardNumber << "\n"
       << " * brandName : " << properties.brandName << "\n"
       << " * modelName : " << properties.modelName << "\n"
       << " * vendorName : " << properties.vendorName << "\n"
       << " * driverVersion : " << properties.driverVersion << "\n";

    const auto zesDeviceInfoStr = ss.str();
    log<Verbosity::info>("%s", zesDeviceInfoStr.c_str());

    return true;
}

int main(int argc, const char *argv[]) {
    using Cal::Testing::Utils::LevelZero::getDevices;
    using Cal::Testing::Utils::LevelZero::getDrivers;
    using Cal::Testing::Utils::LevelZero::initL0;

    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    if (false == Cal::Utils::getCalEnvFlag("ZES_ENABLE_SYSMAN")) {
        Cal::Sys::setenv("ZES_ENABLE_SYSMAN", "1", true);
    }

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    RUN_REQUIRED_STEP(getZesDeviceProperties(devices[0]));
}
