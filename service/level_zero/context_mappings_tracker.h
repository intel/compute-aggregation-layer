/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "boost/container/flat_map.hpp"
#include "level_zero/ze_api.h"
#include "level_zero/zet_api.h"

namespace Cal::Service::LevelZero {

class ContextMappingsTracker {
  public:
    ze_context_handle_t getAssociatedContext(ze_command_list_handle_t commandList) const;
    ze_context_handle_t getAssociatedContext(zet_metric_streamer_handle_t commandList) const;

    void registerCommandListToContextMapping(ze_command_list_handle_t commandList, ze_context_handle_t context);
    void deregisterCommandListMapping(ze_command_list_handle_t commandList);

    void registerMetricStreamerToContextMapping(zet_metric_streamer_handle_t metricStreamer, ze_context_handle_t context);
    void deregisterMetricStreamerMapping(zet_metric_streamer_handle_t metricStreamer);

  private:
    boost::container::flat_map<ze_command_list_handle_t, ze_context_handle_t> commandListToContextMapping{};
    boost::container::flat_map<zet_metric_streamer_handle_t, ze_context_handle_t> metricStreamerToContextMappings{};
};

} // namespace Cal::Service::LevelZero
