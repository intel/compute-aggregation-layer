/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/zes_api.h"

namespace Cal::Client::Icd::LevelZero {
ze_result_t zesDeviceGetProperties(zes_device_handle_t hDevice, zes_device_properties_t *pProperties);
}
