/*
 * Copyright (C) 2022-2024 Intel Corporation
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
#include <sstream>
#include <string>
#include <vector>

bool getDriverApiVersion(ze_driver_handle_t driver) {
    ze_api_version_t version{};

    const auto zeGetDriverApiVersionResult = zeDriverGetApiVersion(driver, &version);
    if (zeGetDriverApiVersionResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeGetDriverApiVersion() call has failed! Error code = %d", static_cast<int>(zeGetDriverApiVersionResult));
        return false;
    }

    log<Verbosity::info>("Supported API version -> (MAJOR: %d, MINOR: %d)", static_cast<int>(ZE_MAJOR_VERSION(version)), static_cast<int>(ZE_MINOR_VERSION(version)));
    return true;
}

bool getDriverProperties(ze_driver_handle_t driver) {
    ze_driver_properties_t driverProperties{ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES};

    const auto zeDriverGetPropertiesResult = zeDriverGetProperties(driver, &driverProperties);
    if (zeDriverGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetPropertiesResult));
        return false;
    }

    std::stringstream driverPropsSs;
    driverPropsSs << "\tDriver version: " << driverProperties.driverVersion << "\n"
                  << "\tUUID:";
    for (const auto uuidByte : driverProperties.uuid.id) {
        driverPropsSs << " " << static_cast<int>(uuidByte);
    }

    const auto driverPropsStr = driverPropsSs.str();
    log<Verbosity::info>("Driver properties: \n%s!", driverPropsStr.c_str());

    return true;
}

bool getDriverExtensionProperties(ze_driver_handle_t driver) {
    uint32_t extensionsCount = 0;

    auto zeDriverGetExtensionPropertiesResult = zeDriverGetExtensionProperties(driver, &extensionsCount, nullptr);
    if (zeDriverGetExtensionPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionPropertiesResult));
        return false;
    }

    if (extensionsCount == 0) {
        log<Verbosity::info>("No extensions supported on this driver");
        return true;
    } else {
        log<Verbosity::info>("Number of supported extensions: %d", static_cast<int>(extensionsCount));
    }

    std::vector<ze_driver_extension_properties_t> extensionsSupported{};
    extensionsSupported.resize(extensionsCount);

    zeDriverGetExtensionPropertiesResult = zeDriverGetExtensionProperties(driver, &extensionsCount, extensionsSupported.data());
    if (zeDriverGetExtensionPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionPropertiesResult));
        return false;
    }

    log<Verbosity::info>("List of driver extensions properties:");
    for (auto i = 0u; i < extensionsSupported.size(); ++i) {
        log<Verbosity::info>("Extension %d: %s", i + 1, extensionsSupported[i].name);
    }

    return true;
}

bool getDriverIpcProperties(ze_driver_handle_t driver) {
    ze_driver_ipc_properties_t ipcProperties{ZE_STRUCTURE_TYPE_DRIVER_IPC_PROPERTIES};

    const auto zeDriverGetIpcPropertiesResult = zeDriverGetIpcProperties(driver, &ipcProperties);
    if (zeDriverGetIpcPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetIpcProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetIpcPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Driver IPC flags: %d", static_cast<int>(ipcProperties.flags));
    return true;
}

bool getLastErrorDescription(ze_driver_handle_t driver) {
    const char *pErrorDescriptionStr = nullptr;

    const auto zeDriverGetLastErrorDescriptionResult = zeDriverGetLastErrorDescription(driver, &pErrorDescriptionStr);
    if (zeDriverGetLastErrorDescriptionResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetLastErrorDescription() call has failed! Error code = %d", static_cast<int>(zeDriverGetLastErrorDescriptionResult));
        return false;
    }
    if (pErrorDescriptionStr == nullptr) {
        log<Verbosity::error>("zeDriverGetLastErrorDescription() call returned invalid nullptr error string");
        return false;
    }

    return true;
}

bool getNonexistentExtensionFunctionAddress(ze_driver_handle_t driver, void **outFunctionAddress, const char *extensionName) {
    const auto zeDriverGetExtensionFunctionAddressResult = zeDriverGetExtensionFunctionAddress(driver, extensionName, outFunctionAddress);
    if (zeDriverGetExtensionFunctionAddressResult == ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionFunctionAddress() call has returned success for '%s' extension! "
                              "It should not happen! outFunctionAddress = %p, Error code = %d",
                              extensionName, *outFunctionAddress, static_cast<int>(zeDriverGetExtensionFunctionAddressResult));
        return false;
    }

    log<Verbosity::info>("zeDriverGetExtensionFunctionAddress() failed as expected for extensionName = '%s'. Checking passed outFunctionAddress...", extensionName);

    if (*outFunctionAddress != nullptr) {
        log<Verbosity::error>("Passed outFunctionAddress should be set to nullptr! Actual value: %p", *outFunctionAddress);
        return false;
    }

    log<Verbosity::info>("*outFunctionAddress is nullptr as expected!");
    return true;
}

int main(int argc, const char *argv[]) {
    using Cal::Testing::Utils::LevelZero::getDrivers;
    using Cal::Testing::Utils::LevelZero::getExtensionFunctionAddress;
    using Cal::Testing::Utils::LevelZero::initL0;

    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDriverApiVersion(drivers[0]));
    RUN_REQUIRED_STEP(getDriverProperties(drivers[0]));
    RUN_REQUIRED_STEP(getDriverExtensionProperties(drivers[0]));
    RUN_REQUIRED_STEP(getDriverIpcProperties(drivers[0]));
    RUN_REQUIRED_STEP(getLastErrorDescription(drivers[0]));

    void *extensionAddress{nullptr};
    RUN_REQUIRED_STEP(getExtensionFunctionAddress(drivers[0], &extensionAddress, "zexDriverImportExternalPointer"));
    RUN_REQUIRED_STEP(getNonexistentExtensionFunctionAddress(drivers[0], &extensionAddress, "someNonexistentStrangeFunction"));

    return 0;
}
