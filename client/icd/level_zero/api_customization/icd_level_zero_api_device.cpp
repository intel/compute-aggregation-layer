/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/icd_global_state.h"
#include "client/icd/level_zero/icd_level_zero.h"
#include "client/icd/level_zero/logic/properties_cache.h"
#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"

#include <algorithm>
#include <cstring>

namespace Cal::Client::Icd::LevelZero {

ze_result_t zeDeviceGet(ze_driver_handle_t hDriver, uint32_t *pCount, ze_device_handle_t *phDevices) {
    auto platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    if (!platform || hDriver != static_cast<ze_driver_handle_t>(platform)) {
        return Cal::Client::Icd::LevelZero::zeDeviceGetRpcHelper(hDriver, pCount, phDevices);
    }

    if (platform->isZeAffinityMaskPresent()) {
        auto &availableDevices = platform->getFilteredDevices();
        auto numAvailableDevices = static_cast<uint32_t>(availableDevices.size());
        if (phDevices == nullptr) {
            *pCount = numAvailableDevices;
            log<Verbosity::debug>("Returning pCount = %d", numAvailableDevices);
        } else {
            auto numDevicesToReport = std::min(*pCount, numAvailableDevices);

            for (auto i = 0u; i < numDevicesToReport; i++) {
                auto icdDevice = static_cast<IcdL0Device *>(availableDevices[i]);
                bool deviceAffinityPresent = icdDevice->isZeAffinityMaskPresent();
                auto &filteredSubDevices = icdDevice->getFilteredDevices();
                auto numFilteredSubDevices = static_cast<uint32_t>(filteredSubDevices.size());

                // For sub-device filter provided by user
                if (deviceAffinityPresent && (numFilteredSubDevices == 1)) {
                    // Num filtered sub-devices = 1, only add sub-device
                    log<Verbosity::debug>("Parsing affinity mask for dev handle:%p, filtered sub-devices count = 1. Adding sub-dev handle:%p",
                                          availableDevices[i], filteredSubDevices[0]);
                    phDevices[i] = filteredSubDevices[0];
                } else {
                    // If num filtered sub-devices is 1 or only root device specified in affinity mask,
                    // add root device to output vector
                    log<Verbosity::debug>("Adding root device handle: %p",
                                          availableDevices[i]);
                    phDevices[i] = availableDevices[i];
                }
            }
        }

        return ZE_RESULT_SUCCESS;
    }
    return Cal::Client::Icd::LevelZero::zeDeviceGetRpcHelper(hDriver, pCount, phDevices);
}

ze_result_t zeDeviceGetSubDevices(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_handle_t *phDevices) {
    auto device = static_cast<IcdL0Device *>(hDevice);
    if (!device) {
        return Cal::Client::Icd::LevelZero::zeDeviceGetSubDevicesRpcHelper(hDevice, pCount, phDevices);
    }
    device->ensureIsLocalObject();

    if (device->isZeAffinityMaskPresent()) {
        auto &availableDevices = device->getFilteredDevices();
        auto numAvailableDevices = static_cast<uint32_t>(availableDevices.size());
        if (numAvailableDevices == 1u) {
            numAvailableDevices = 0u;
        }
        if (phDevices == nullptr) {
            *pCount = numAvailableDevices;
        } else {
            auto numDevices = std::min(*pCount, numAvailableDevices);
            memcpy(phDevices, availableDevices.data(), numDevices * sizeof(ze_device_handle_t));
        }
        return ZE_RESULT_SUCCESS;
    }
    return Cal::Client::Icd::LevelZero::zeDeviceGetSubDevicesRpcHelper(hDevice, pCount, phDevices);
}

ze_result_t zeDeviceGetProperties(ze_device_handle_t hDevice, ze_device_properties_t *pDeviceProperties) {
    static bool usePnext = Cal::Utils::getCalEnvFlag(calUsePnextInZeDeviceGetProperties, false);
    if (usePnext == false) {
        log<Verbosity::debug>("Ignoring pNext in zeDeviceGetProperties. To use this value, set %s", calUsePnextInZeDeviceGetProperties.data());
        pDeviceProperties->pNext = nullptr;
    }

    if (pDeviceProperties->stype == ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2) {
        return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), static_cast<ze_device_properties_1_2_t *>(pDeviceProperties), zeDeviceGetPropertiesRpcHelper);
    } else {
        return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pDeviceProperties, zeDeviceGetPropertiesRpcHelper);
    }
}

ze_result_t zeDeviceGetComputeProperties(ze_device_handle_t hDevice, ze_device_compute_properties_t *pComputeProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pComputeProperties, zeDeviceGetComputePropertiesRpcHelper);
}

ze_result_t zeDeviceGetModuleProperties(ze_device_handle_t hDevice, ze_device_module_properties_t *pModuleProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pModuleProperties, zeDeviceGetModulePropertiesRpcHelper);
}

ze_result_t zeDeviceGetMemoryAccessProperties(ze_device_handle_t hDevice, ze_device_memory_access_properties_t *pMemAccessProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pMemAccessProperties, zeDeviceGetMemoryAccessPropertiesRpcHelper);
}

ze_result_t zeDeviceGetImageProperties(ze_device_handle_t hDevice, ze_device_image_properties_t *pImageProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pImageProperties, zeDeviceGetImagePropertiesRpcHelper);
}

ze_result_t zeDeviceGetExternalMemoryProperties(ze_device_handle_t hDevice, ze_device_external_memory_properties_t *pExternalMemoryProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pExternalMemoryProperties, zeDeviceGetExternalMemoryPropertiesRpcHelper);
}

ze_result_t zeDeviceGetCacheProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_cache_properties_t *pCacheProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pCount, pCacheProperties, zeDeviceGetCachePropertiesRpcHelper);
}

ze_result_t zeDeviceGetCommandQueueGroupProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_command_queue_group_properties_t *pCommandQueueGroupProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pCount, pCommandQueueGroupProperties, zeDeviceGetCommandQueueGroupPropertiesRpcHelper);
}

ze_result_t zeDeviceGetMemoryProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_memory_properties_t *pMemProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pCount, pMemProperties, zeDeviceGetMemoryPropertiesRpcHelper);
}

} // namespace Cal::Client::Icd::LevelZero
