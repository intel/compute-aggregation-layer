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

    zes_power_properties_t powerProperties = {ZES_STRUCTURE_TYPE_POWER_PROPERTIES, nullptr};
    zes_power_ext_properties_t powerExtProperties = {ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES, nullptr};
    zes_power_limit_ext_desc_t default_limits = {};
    powerExtProperties.defaultLimit = &default_limits;
    powerProperties.pNext = &powerExtProperties;

    result = zesPowerGetProperties(powerHandles[0], &powerProperties);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesPowerGetProperties() call with default limits has failed! Error code = %x", static_cast<int>(result));
        return false;
    }

    if ((powerExtProperties.defaultLimit->level < ZES_POWER_LEVEL_UNKNOWN) || (powerExtProperties.defaultLimit->level > ZES_POWER_LEVEL_INSTANTANEOUS)) {
        log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for level value = %d", static_cast<int>(powerExtProperties.defaultLimit->level));
        return false;
    }

    if ((powerExtProperties.defaultLimit->source < ZES_POWER_SOURCE_ANY) || (powerExtProperties.defaultLimit->source > ZES_POWER_SOURCE_BATTERY)) {
        log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for source value = %d", static_cast<int>(powerExtProperties.defaultLimit->source));
        return false;
    }

    if ((powerExtProperties.defaultLimit->limitUnit < ZES_LIMIT_UNIT_UNKNOWN) || (powerExtProperties.defaultLimit->limitUnit > ZES_LIMIT_UNIT_POWER)) {
        log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for limit unit value = %d", static_cast<int>(powerExtProperties.defaultLimit->limitUnit));
        return false;
    }

    if (!powerExtProperties.defaultLimit->intervalValueLocked) {
        if (powerExtProperties.defaultLimit->interval < 0) {
            log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for interval value = %d", static_cast<int>(powerExtProperties.defaultLimit->interval));
            return false;
        }
    }
    if (!powerExtProperties.defaultLimit->limitValueLocked) {
        if (powerExtProperties.defaultLimit->limit < 0) {
            log<Verbosity::error>("zesPowerGetProperties() call has returned incorrect default limit for limit value = %d", static_cast<int>(powerExtProperties.defaultLimit->limit));
            return false;
        }
    }

    return true;
}

bool getZesMemProperties(zes_device_handle_t device) {
    zes_device_properties_t deviceProperties = {ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES, nullptr};
    auto result = zesDeviceGetProperties(device, &deviceProperties);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceGetProperties() call has failed! Error code = %x", static_cast<int>(result));
        return false;
    }

    uint32_t count = 0;
    result = zesDeviceEnumMemoryModules(device, &count, nullptr);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceEnumMemoryModules() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }
    if (count == 0) {
        log<Verbosity::info>("zesDeviceEnumMemoryModules() returned no handles");
        return true;
    }

    std::vector<zes_mem_handle_t> memHandles(count);
    result = zesDeviceEnumMemoryModules(device, &count, memHandles.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDeviceEnumMemoryModules() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }

    for (auto memHandle : memHandles) {
        zes_mem_properties_t memProperties = {ZES_STRUCTURE_TYPE_MEM_PROPERTIES, nullptr};
        result = zesMemoryGetProperties(memHandle, &memProperties);
        if (result != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zesMemoryGetProperties() call has failed! Error code = %x", static_cast<int>(result));
            return false;
        }
        if (memProperties.onSubdevice) {
            if (memProperties.subdeviceId >= deviceProperties.numSubdevices) {
                log<Verbosity::error>("zesMemoryGetProperties() call has returned incorrect subdeviceId value = %d", static_cast<int>(memProperties.subdeviceId));
                return false;
            }
        }
        if ((memProperties.location != ZES_MEM_LOC_SYSTEM) && (memProperties.location != ZES_MEM_LOC_DEVICE)) {
            log<Verbosity::error>("zesMemoryGetProperties() call has returned incorrect location value = %d", static_cast<int>(memProperties.location));
            return false;
        }
        if ((memProperties.busWidth != -1) && (memProperties.busWidth == 0)) {
            log<Verbosity::error>("zesMemoryGetProperties() call has returned incorrect busWidth value = %d", static_cast<int>(memProperties.numChannels));
            return false;
        }
        if ((memProperties.numChannels != -1) && (memProperties.numChannels == 0)) {
            log<Verbosity::error>("zesMemoryGetProperties() call has returned incorrect numChannels value = %d", static_cast<int>(memProperties.numChannels));
            return false;
        }

        zes_mem_state_t state = {ZES_STRUCTURE_TYPE_MEM_STATE, nullptr};
        result = zesMemoryGetState(memHandle, &state);
        if (result != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zesMemoryGetState()) call has failed! Error code = %x", static_cast<int>(result));
            return false;
        }
        if ((state.health < ZES_MEM_HEALTH_UNKNOWN) || (state.health > ZES_MEM_HEALTH_REPLACE)) {
            log<Verbosity::error>("zesMemoryGetState() call has returned incorrect health value = %d", static_cast<int>(state.health));
            return false;
        }
        if (memProperties.physicalSize != 0) {
            if (state.size > memProperties.physicalSize) {
                log<Verbosity::error>("zesMemoryGetState() call has returned incorrect size value = %d", static_cast<int>(state.size));
                return false;
            }
        }
        if (state.free > state.size) {
            log<Verbosity::error>("zesMemoryGetState() call has returned incorrect free value = %d", static_cast<int>(state.free));
            return false;
        }
    }

    return true;
}

bool getZesPciBars(zes_device_handle_t device) {
    constexpr auto maxBarsNum = 6u;

    uint32_t count = 0;
    auto result = zesDevicePciGetBars(device, &count, nullptr);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDevicePciGetBars() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }
    if (count == 0) {
        log<Verbosity::info>("zesDevicePciGetBars() returned no handles");
        return true;
    }

    std::vector<zes_pci_bar_properties_t> pciBarProps(count);
    for (uint32_t i = 0; i < count; i++) {
        pciBarProps[i].stype = ZES_STRUCTURE_TYPE_PCI_BAR_PROPERTIES;
        pciBarProps[i].pNext = nullptr;
    }

    result = zesDevicePciGetBars(device, &count, pciBarProps.data());
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zesDevicePciGetBars() with count=%d call has failed! Error code = %x", count, static_cast<int>(result));
        return false;
    }

    for (auto pciBarProp : pciBarProps) {
        if ((pciBarProp.type < ZES_PCI_BAR_TYPE_MMIO) || (pciBarProp.type > ZES_PCI_BAR_TYPE_MEM)) {
            log<Verbosity::error>("zesDevicePciGetBars() call has returned incorrect type value = %d", static_cast<int>(pciBarProp.type));
            return false;
        }
        if (UINT64_MAX - pciBarProp.base < pciBarProp.size) {
            log<Verbosity::error>("zesDevicePciGetBars() call has returned incorrect base value = %d", static_cast<int>(pciBarProp.base));
            return false;
        }
        if (pciBarProp.index > maxBarsNum) {
            log<Verbosity::error>("zesDevicePciGetBars() call has returned incorrect index value = %d", static_cast<int>(pciBarProp.index));
            return false;
        }
        if (pciBarProp.size == 0) {
            log<Verbosity::error>("zesDevicePciGetBars() call has returned incorrect size value = %d", static_cast<int>(pciBarProp.size));
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

    RUN_REQUIRED_STEP(getZesMemProperties(devices[0]));

    RUN_REQUIRED_STEP(getZesPciBars(devices[0]));
}
