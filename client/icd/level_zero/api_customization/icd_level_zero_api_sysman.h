/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/zes_api.h"

namespace Cal::Client::Icd::LevelZero {
ze_result_t zesDeviceGetProperties(zes_device_handle_t hDevice, zes_device_properties_t *pProperties);
ze_result_t zesDeviceProcessesGetState(zes_device_handle_t hDevice, uint32_t *pCount, zes_process_state_t *pProcesses);
} // namespace Cal::Client::Icd::LevelZero
