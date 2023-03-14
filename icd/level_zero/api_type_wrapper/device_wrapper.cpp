/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd/level_zero/api_type_wrapper/device_wrapper.h"

namespace Cal::Icd::LevelZero {
ze_result_t zeDeviceGetSubDevicesRpcHelper(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_handle_t *phSubdevices);
ze_result_t zeDeviceGetRpcHelper(ze_driver_handle_t hDriver, uint32_t *pCount, ze_device_handle_t *phDevices);

void IcdL0Device::addSubDeviceToFilter(uint32_t subDeviceIndex) {
    if (selectedDevices.size() < subDeviceIndex + 1) {
        selectedDevices.resize(subDeviceIndex + 1);
    }
    selectedDevices[subDeviceIndex] = true;
}
bool IcdL0Device::isZeAffinityMaskPresent() {
    std::call_once(parseZeAffinityMaskOnce, [this]() {
        if (!selectedDevices.empty()) {
            uint32_t numAllDevices = 0;
            std::vector<ze_device_handle_t> allDevices;
            auto status = zeDeviceGetSubDevicesRpcHelper(this, &numAllDevices, nullptr);
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }

            allDevices.resize(numAllDevices);
            status = zeDeviceGetSubDevicesRpcHelper(this, &numAllDevices, allDevices.data());
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }

            selectedDevices.resize(numAllDevices);

            for (auto i = 0u; i < numAllDevices; i++) {

                if (selectedDevices[i]) {
                    filteredDevices.push_back(allDevices[i]);
                }
            }
            zeAffinityMaskPresent = true;
        }
    });

    return zeAffinityMaskPresent;
}

bool IcdL0Device::patchDeviceName(ze_device_properties_t &properties) {
    const auto nullTerminator = std::find(std::begin(properties.name), std::end(properties.name), '\0');
    if (nullTerminator == std::begin(properties.name)) {
        log<Verbosity::critical>("Cannot patch device name! It is empty!");
        return false;
    }

    static constexpr char deviceNameSuffix[] = " (aggregated)";
    static constexpr auto requiredSpace = std::distance(std::begin(deviceNameSuffix), std::end(deviceNameSuffix));

    const auto availableSpace = std::distance(nullTerminator, std::end(properties.name));
    if (availableSpace < requiredSpace) {
        log<Verbosity::critical>("Cannot patch device name with '(aggregated)' suffix! Not enough space!");
        return false;
    }

    std::copy(std::begin(deviceNameSuffix), std::end(deviceNameSuffix), nullTerminator);
    return true;
}
} // namespace Cal::Icd::LevelZero
