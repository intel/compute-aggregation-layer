/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "include/cal.h"
#include "shared/log.h"

#include <algorithm>
#include <cstring>

namespace Cal::Icd::LevelZero {

ze_result_t zeDeviceGet(ze_driver_handle_t hDriver, uint32_t *pCount, ze_device_handle_t *phDevices) {
    auto platform = Cal::Icd::icdGlobalState.getL0Platform();
    if (!platform || !platform->valid() || hDriver != static_cast<ze_driver_handle_t>(platform)) {
        return Cal::Icd::LevelZero::zeDeviceGetRpcHelper(hDriver, pCount, phDevices);
    }

    if (platform->isZeAffinityMaskPresent()) {
        auto &availableDevices = platform->getFilteredDevices();
        auto numAvailableDevices = static_cast<uint32_t>(availableDevices.size());
        if (phDevices == nullptr) {
            *pCount = numAvailableDevices;
        } else {
            auto numDevices = std::min(*pCount, numAvailableDevices);
            memcpy(phDevices, availableDevices.data(), numDevices * sizeof(ze_device_handle_t));
        }
        return ZE_RESULT_SUCCESS;
    }
    return Cal::Icd::LevelZero::zeDeviceGetRpcHelper(hDriver, pCount, phDevices);
}

ze_result_t zeDeviceGetSubDevices(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_handle_t *phDevices) {
    auto device = static_cast<IcdL0Device *>(hDevice);
    if (!device) {
        return Cal::Icd::LevelZero::zeDeviceGetSubDevicesRpcHelper(hDevice, pCount, phDevices);
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
    return Cal::Icd::LevelZero::zeDeviceGetSubDevicesRpcHelper(hDevice, pCount, phDevices);
}

ze_result_t zeDeviceGetProperties(ze_device_handle_t hDevice, ze_device_properties_t *pDeviceProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pDeviceProperties, zeDeviceGetPropertiesRpcHelper);
}

ze_result_t zeDeviceGetComputeProperties(ze_device_handle_t hDevice, ze_device_compute_properties_t *pComputeProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pComputeProperties, zeDeviceGetComputePropertiesRpcHelper);
}

ze_result_t zeDeviceGetModuleProperties(ze_device_handle_t hDevice, ze_device_module_properties_t *pModuleProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pModuleProperties, zeDeviceGetModulePropertiesRpcHelper);
}

ze_result_t zeDeviceGetMemoryAccessProperties(ze_device_handle_t hDevice, ze_device_memory_access_properties_t *pMemAccessProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pMemAccessProperties, zeDeviceGetMemoryAccessPropertiesRpcHelper);
}

ze_result_t zeDeviceGetImageProperties(ze_device_handle_t hDevice, ze_device_image_properties_t *pImageProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pImageProperties, zeDeviceGetImagePropertiesRpcHelper);
}

ze_result_t zeDeviceGetExternalMemoryProperties(ze_device_handle_t hDevice, ze_device_external_memory_properties_t *pExternalMemoryProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pExternalMemoryProperties, zeDeviceGetExternalMemoryPropertiesRpcHelper);
}

ze_result_t zeDeviceGetCacheProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_cache_properties_t *pCacheProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pCount, pCacheProperties, zeDeviceGetCachePropertiesRpcHelper);
}

ze_result_t zeDeviceGetCommandQueueGroupProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_command_queue_group_properties_t *pCommandQueueGroupProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pCount, pCommandQueueGroupProperties, zeDeviceGetCommandQueueGroupPropertiesRpcHelper);
}

ze_result_t zeDeviceGetMemoryProperties(ze_device_handle_t hDevice, uint32_t *pCount, ze_device_memory_properties_t *pMemProperties) {
    return PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pCount, pMemProperties, zeDeviceGetMemoryPropertiesRpcHelper);
}

} // namespace Cal::Icd::LevelZero
