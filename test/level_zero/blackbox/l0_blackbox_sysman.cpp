/*
 * Copyright (C) 2023-2024 Intel Corporation
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

bool getZesEngineProperties(zes_device_handle_t device) {
    uint32_t count = 0;
    auto result = zesDeviceEnumEngineGroups(device, &count, nullptr);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceEnumEngineGroups() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }
    if (count == 0) {
        log<Verbosity::info>("zesDeviceEnumEngineGroups() returned no handles! Error code = %x", static_cast<int>(result));
        return true;
    }

    std::vector<zes_engine_handle_t> engineHandles(count);
    result = zesDeviceEnumEngineGroups(device, &count, engineHandles.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceEnumEngineGroups() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }

    zes_engine_properties_t properties = {ZES_STRUCTURE_TYPE_ENGINE_PROPERTIES, nullptr};
    result = zesEngineGetProperties(engineHandles[0], &properties);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesEngineGetProperties() call has failed! Error code = %x", static_cast<int>(result));
        return false;
    }

    zes_engine_stats_t stats = {};
    result = zesEngineGetActivity(engineHandles[0], &stats);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesEngineGetActivity() call has failed! Error code = %x", static_cast<int>(result));
        return false;
    }

    return true;
}

bool getZesPowerProperties(zes_device_handle_t device) {
    uint32_t count = 0;
    auto result = zesDeviceEnumPowerDomains(device, &count, nullptr);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceEnumPowerDomains() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }
    if (count == 0) {
        log<Verbosity::info>("zesDeviceEnumPowerDomains() returned no handles");
        return true;
    }

    std::vector<zes_pwr_handle_t> powerHandles(count);
    result = zesDeviceEnumPowerDomains(device, &count, powerHandles.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceEnumPowerDomains() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }

    zes_power_properties_t pProperties = {ZES_STRUCTURE_TYPE_POWER_PROPERTIES, nullptr};
    zes_power_ext_properties_t pExtProperties = {ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES, nullptr};
    zes_power_limit_ext_desc_t default_limits = {};
    pExtProperties.defaultLimit = &default_limits;
    pProperties.pNext = &pExtProperties;

    result = zesPowerGetProperties(powerHandles[0], &pProperties);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesPowerGetProperties() call with default limits has failed! Error code = %x", static_cast<int>(result));
        return false;
    }

    if ((pExtProperties.defaultLimit->level < ZES_POWER_LEVEL_UNKNOWN) || (pExtProperties.defaultLimit->level > ZES_POWER_LEVEL_INSTANTANEOUS)) {
        log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for level value = %d", static_cast<int>(pExtProperties.defaultLimit->level));
        return false;
    }

    if ((pExtProperties.defaultLimit->source < ZES_POWER_SOURCE_ANY) || (pExtProperties.defaultLimit->source > ZES_POWER_SOURCE_BATTERY)) {
        log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for source value = %d", static_cast<int>(pExtProperties.defaultLimit->source));
        return false;
    }

    if ((pExtProperties.defaultLimit->limitUnit < ZES_LIMIT_UNIT_UNKNOWN) || (pExtProperties.defaultLimit->limitUnit > ZES_LIMIT_UNIT_POWER)) {
        log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for limit unit value = %d", static_cast<int>(pExtProperties.defaultLimit->limitUnit));
        return false;
    }

    if (!pExtProperties.defaultLimit->intervalValueLocked) {
        if (pExtProperties.defaultLimit->interval < 0) {
            log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for interval value = %d", static_cast<int>(pExtProperties.defaultLimit->interval));
            return false;
        }
    }
    if (!pExtProperties.defaultLimit->limitValueLocked) {
        if (pExtProperties.defaultLimit->limit < 0) {
            log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for limit value = %d", static_cast<int>(pExtProperties.defaultLimit->limit));
            return false;
        }
    }

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

    RUN_REQUIRED_STEP(getZesEngineProperties(devices[0]));

    RUN_REQUIRED_STEP(getZesPowerProperties(devices[0]));
}
