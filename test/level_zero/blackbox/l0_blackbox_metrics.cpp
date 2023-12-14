/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "level_zero/zet_api.h"
#include "shared/log.h"
#include "shared/sys.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

using namespace Cal::Testing::Utils::LevelZero;

bool getMetricGroup(ze_device_handle_t hDevice, std::vector<zet_metric_group_handle_t> &metricGroups) {
    uint32_t groupCount = 0;
    auto zetMetricGroupGetResult = zetMetricGroupGet(hDevice, &groupCount, nullptr);
    if (zetMetricGroupGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zetMetricGroupGet() call has failed! Error code = %d", static_cast<int>(zetMetricGroupGetResult));
        return false;
    }

    if (groupCount == 0) {
        log<Verbosity::error>("zetMetricGroupGet() returned group count equals 0!");
        return false;
    } else {
        log<Verbosity::info>("Number of available metric groups: %d", static_cast<int>(groupCount));
    }

    metricGroups.resize(groupCount);
    zetMetricGroupGetResult = zetMetricGroupGet(hDevice, &groupCount, metricGroups.data());
    if (zetMetricGroupGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zetMetricGroupGet() call has failed! Error code = %d", static_cast<int>(zetMetricGroupGetResult));
        return false;
    }

    return !metricGroups.empty();
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    if (false == Cal::Utils::getCalEnvFlag("ZET_ENABLE_METRICS")) {
        Cal::Sys::setenv("ZET_ENABLE_METRICS", "1", true);
    }

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    std::vector<zet_metric_group_handle_t> metricGroups;
    RUN_REQUIRED_STEP(getMetricGroup(devices[0], metricGroups));

    return 0;
}
