/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero_api_sysman.h"

#include "client/icd/level_zero/api_type_wrapper/device_wrapper.h"
#include "client/icd/level_zero/logic/properties_cache.h"
#include "generated_icd_level_zero.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zesDeviceGetProperties(zes_device_handle_t hDevice, zes_device_properties_t *pProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pProperties, zesDeviceGetPropertiesRpcHelper);
}

ze_result_t zesDeviceProcessesGetState(zes_device_handle_t hDevice, uint32_t *pCount, zes_process_state_t *pProcesses) {
    ze_result_t result = ZE_RESULT_SUCCESS;

    if (pCount == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if (*pCount == 0) {
        uint32_t count = 0;
        result = zesDeviceProcessesGetStateRpcHelper(hDevice, &count, nullptr);
        if (result == ZE_RESULT_SUCCESS) {
            *pCount = count + 1;
        }
    } else {
        uint32_t count = *pCount;
        auto result = zesDeviceProcessesGetStateRpcHelper(hDevice, &count, pProcesses);
        if (result == ZE_RESULT_SUCCESS) {
            if (count < *pCount) {
                pProcesses[count].stype = ZES_STRUCTURE_TYPE_PROCESS_STATE;
                pProcesses[count].pNext = nullptr;
                pProcesses[count].processId = getpid();
                pProcesses[count].memSize = 0;
                pProcesses[count].sharedSize = 0;
                pProcesses[count].engines = 0;
            }
        }
    }
    return result;
}

} // namespace Cal::Client::Icd::LevelZero
