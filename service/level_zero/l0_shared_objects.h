/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"

#include <optional>
#include <vector>

namespace Cal::Service::Apis::LevelZero {

class L0SharedObjects {
  public:
    bool init();

    static ze_driver_handle_t getIntelGpuDriver() {
        return intelGpuDriver;
    }

    static ze_result_t getZeInitReturnValue() {
        return zeInitReturnValue;
    }

  private:
    ze_driver_handle_t getDriverByName(const char **regexes, size_t count);
    std::optional<std::vector<ze_driver_handle_t>> getDrivers();
    std::optional<std::vector<ze_device_handle_t>> getDevices(ze_driver_handle_t driverHandle);

    inline static ze_result_t zeInitReturnValue{};
    inline static ze_driver_handle_t intelGpuDriver{};
};

void *getExtensionFuncAddress(const char *funcname);

} // namespace Cal::Service::Apis::LevelZero
