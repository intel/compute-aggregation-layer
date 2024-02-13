/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "context_mappings_tracker.h"

#include "shared/log.h"

namespace Cal::Service::LevelZero {

ze_context_handle_t ContextMappingsTracker::getAssociatedContext(ze_command_list_handle_t commandList) const {
    auto it = commandListToContextMapping.find(commandList);
    if (it == commandListToContextMapping.end()) {
        log<Verbosity::error>("Could not find context associated with commandlist %p", commandList);
        return nullptr;
    }
    return it->second;
}

void ContextMappingsTracker::registerCommandListToContextMapping(ze_command_list_handle_t commandList, ze_context_handle_t context) {
    log<Verbosity::bloat>("Registering commandlist %p to context %p", commandList, context);
    commandListToContextMapping.insert(std::make_pair(commandList, context));
}

void ContextMappingsTracker::deregisterCommandListMapping(ze_command_list_handle_t commandList) {
    log<Verbosity::bloat>("Deregistering commandlist %p", commandList);
    commandListToContextMapping.erase(commandList);
}

ze_context_handle_t ContextMappingsTracker::getAssociatedContext(zet_metric_streamer_handle_t metricStreamer) const {
    auto it = metricStreamerToContextMappings.find(metricStreamer);
    if (it == metricStreamerToContextMappings.end()) {
        log<Verbosity::error>("Could not find context associated with metricStreamer %p", metricStreamer);
        return nullptr;
    }
    return it->second;
}

void ContextMappingsTracker::registerMetricStreamerToContextMapping(zet_metric_streamer_handle_t metricStreamer, ze_context_handle_t context) {
    log<Verbosity::bloat>("Registering metricStreamer %p to context %p", metricStreamer, context);
    metricStreamerToContextMappings.insert(std::make_pair(metricStreamer, context));
}

void ContextMappingsTracker::deregisterMetricStreamerMapping(zet_metric_streamer_handle_t metricStreamer) {
    log<Verbosity::bloat>("Deregistering metricStreamer %p", metricStreamer);
    metricStreamerToContextMappings.erase(metricStreamer);
}

} // namespace Cal::Service::LevelZero
