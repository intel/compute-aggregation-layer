/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero_api_sysman.h"

#include "generated_icd_level_zero.h"
#include "icd/level_zero/api_type_wrapper/device_wrapper.h"
#include "icd/level_zero/logic/properties_cache.h"

namespace Cal::Icd::LevelZero {
ze_result_t zesDeviceGetProperties(zes_device_handle_t hDevice, zes_device_properties_t *pProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Device *>(hDevice), pProperties, zesDeviceGetPropertiesRpcHelper);
}
} // namespace Cal::Icd::LevelZero
