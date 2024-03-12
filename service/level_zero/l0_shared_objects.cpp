/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "l0_shared_objects.h"

#include "generated_service_level_zero.h"
#include "shared/utils.h"

namespace Cal::Service::Apis::LevelZero {

static const char *intelGpuPlatformName = "Intel.*Graphics";
static const char *intelGpuDeviceName = "Intel.*GPU";

bool isRecursiveCalL0() {
    auto *altDrivers = Cal::Sys::getenv("ZE_ENABLE_ALT_DRIVERS");
    if (nullptr == altDrivers) {
        return false;
    }
    if (strstr(altDrivers, ",")) {
        return false;
    }

    bool isRedirectToCalLib = (nullptr != strstr(altDrivers, "libcal.so"));
    return isRedirectToCalLib;
}

void warnIfRecursiveCalL0() {
    if (isRecursiveCalL0()) {
        log<Verbosity::error>("Detected that ZE_ENABLE_ALT_DRIVER redirects to libcal.so for calrun service process! This forbids CAL service from loading L0 GPU driver. Please rerun calrun with \"ZE_ENABLE_ALT_DRIVERS=\" (i.e. unset).");
    }
}

bool L0SharedObjects::init() {
    warnIfRecursiveCalL0();

    Cal::Sys::setenv("ZES_ENABLE_SYSMAN", "1", true);
    if (!Cal::Service::Apis::LevelZero::Standard::loadLevelZeroLibrary(std::nullopt)) {
        log<Verbosity::info>("Could not load LevelZero ICD loader library (libze_loader.so.1) - LevelZero API will not be available");
        return false;
    }

    Cal::Sys::setenv("ZES_ENABLE_SYSMAN", "1", true);
    zeInitReturnValue = Cal::Service::Apis::LevelZero::Standard::zeInit(0);
    if (zeInitReturnValue != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zeInit() call has failed! LevelZero API will always return failure on zeInit() to clients");
        return false;
    }

    const char *regexes[2] = {intelGpuPlatformName, intelGpuDeviceName};
    intelGpuDriver = getDriverByName(regexes, 2u);
    if (nullptr == intelGpuDriver) {
        return false;
    }

    return true;
}

ze_driver_handle_t L0SharedObjects::getDriverByName(const char **regexes, size_t count) {
    const auto drivers = getDrivers();
    if (!drivers.has_value()) {
        return nullptr;
    }

    for (const auto driver : *drivers) {
        const auto devices = getDevices(driver);
        if (!devices.has_value()) {
            continue;
        }

        for (const auto device : *devices) {
            ze_device_properties_t deviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
            ze_result_t result = Cal::Service::Apis::LevelZero::Standard::zeDeviceGetProperties(device, &deviceProperties);
            if (result != ZE_RESULT_SUCCESS) {
                log<Verbosity::debug>("Could not get device properties from L0 device!");
                continue;
            }

            for (size_t i = 0u; i < count; ++i) {
                Cal::Utils::Regex r{regexes[i]};
                if (r.matches(deviceProperties.name)) {
                    return driver;
                }
            }
        }
    }

    log<Verbosity::debug>("None of drivers matches given L0 driver name!");
    return nullptr;
}

std::optional<std::vector<ze_driver_handle_t>> L0SharedObjects::getDrivers() {
    uint32_t driversCount{0};
    ze_result_t result = Cal::Service::Apis::LevelZero::Standard::zeDriverGet(&driversCount, nullptr);

    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve count of L0 drivers!");
        return std::nullopt;
    }

    if (driversCount == 0u) {
        log<Verbosity::debug>("There are no L0 drivers!");
        return std::vector<ze_driver_handle_t>{};
    }

    std::vector<ze_driver_handle_t> drivers;
    drivers.resize(driversCount);

    result = Cal::Service::Apis::LevelZero::Standard::zeDriverGet(&driversCount, drivers.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve L0 drivers!");
        return std::nullopt;
    }

    return drivers;
}

std::optional<std::vector<ze_device_handle_t>> L0SharedObjects::getDevices(ze_driver_handle_t driverHandle) {
    uint32_t devicesCount{0};
    ze_result_t result = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(driverHandle, &devicesCount, nullptr);

    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve count of L0 devices!");
        return std::nullopt;
    }

    if (devicesCount == 0u) {
        log<Verbosity::debug>("There are no L0 devices!");
        return std::vector<ze_device_handle_t>{};
    }

    std::vector<ze_device_handle_t> devices;
    devices.resize(devicesCount);

    result = Cal::Service::Apis::LevelZero::Standard::zeDeviceGet(driverHandle, &devicesCount, devices.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not retrieve L0 devices!");
        return std::nullopt;
    }

    return devices;
}

void *getExtensionFuncAddress(const char *funcname) {
    auto driver = L0SharedObjects::getIntelGpuDriver();
    void *functionAddress{};

    const auto zeDriverGetExtensionFunctionAddressResult = Cal::Service::Apis::LevelZero::Standard::zeDriverGetExtensionFunctionAddress(driver, funcname, &functionAddress);
    if (zeDriverGetExtensionFunctionAddressResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionFunctionAddress() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionFunctionAddressResult));
        return nullptr;
    }

    return functionAddress;
}

} // namespace Cal::Service::Apis::LevelZero
