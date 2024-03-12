/*
 * Copyright (C) 2023-2024 Intel Corporation
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

bool getMetricGroups(ze_device_handle_t hDevice, std::vector<zet_metric_group_handle_t> &metricGroups) {
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

bool getMetricGroupProperties(zet_metric_group_handle_t metricGroup) {
    zet_metric_group_properties_t properties{};
    properties.stype = ZET_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES;
    auto zetMetricGroupGetPropertiesResult = zetMetricGroupGetProperties(metricGroup, &properties);
    if (zetMetricGroupGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zetMetricGroupGetProperties() call has failed! Error code = %d",
                              static_cast<int>(zetMetricGroupGetPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Successfully got properties of metric group name: %s metricCount: %d",
                         properties.name, static_cast<int>(properties.metricCount));
    return true;
}

bool getMetrics(zet_metric_group_handle_t metricGroup, std::vector<zet_metric_handle_t> &metrics) {
    uint32_t count = 0;
    auto zetMetricGetResult = zetMetricGet(metricGroup, &count, nullptr);
    if (zetMetricGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zetMetricGet() call has failed! Error code = %d", static_cast<int>(zetMetricGetResult));
        return false;
    }

    if (count == 0) {
        log<Verbosity::error>("zetMetricGet() returned count equals 0!");
        return false;
    } else {
        log<Verbosity::info>("Number of available metrics: %d", static_cast<int>(count));
    }

    metrics.resize(count);
    zetMetricGetResult = zetMetricGet(metricGroup, &count, metrics.data());
    if (zetMetricGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zetMetricGet() call has failed! Error code = %d", static_cast<int>(zetMetricGetResult));
        return false;
    }

    return !metrics.empty();
}

bool getMetricProperties(zet_metric_handle_t metric) {
    zet_metric_properties_t properties{};
    properties.stype = ZET_STRUCTURE_TYPE_METRIC_PROPERTIES;
    auto zetMetricGetPropertiesResult = zetMetricGetProperties(metric, &properties);
    if (zetMetricGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zetMetricGetProperties() call has failed! Error code = %d",
                              static_cast<int>(zetMetricGetPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Successfully got properties of metric name: %s", properties.name);
    return true;
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    if (false == Cal::Utils::getEnvFlag("ZET_ENABLE_METRICS")) {
        Cal::Sys::setenv("ZET_ENABLE_METRICS", "1", true);
    }

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    std::vector<zet_metric_group_handle_t> metricGroups;
    RUN_REQUIRED_STEP(getMetricGroups(devices[0], metricGroups));

    for (auto metricGroup : metricGroups) {
        RUN_REQUIRED_STEP(getMetricGroupProperties(metricGroup));
        std::vector<zet_metric_handle_t> metrics;
        RUN_REQUIRED_STEP(getMetrics(metricGroup, metrics));
        RUN_REQUIRED_STEP(getMetricProperties(metrics[0]));
    }

    return 0;
}
