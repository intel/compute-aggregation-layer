/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <level_zero/ze_api.h>

namespace Cal::Client::Icd::LevelZero {

ze_result_t zeModuleCreateTracing(ze_context_handle_t hContext,
                                  ze_device_handle_t hDevice,
                                  const ze_module_desc_t *desc,
                                  ze_module_handle_t *phModule,
                                  ze_module_build_log_handle_t *phBuildLog);

} // namespace Cal::Client::Icd::LevelZero
