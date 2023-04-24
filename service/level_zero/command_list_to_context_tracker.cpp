/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "command_list_to_context_tracker.h"

#include "shared/log.h"

namespace Cal::Service::LevelZero {

ze_context_handle_t CommandListToContextTracker::getAssociatedContext(ze_command_list_handle_t commandList) const {
    const auto contextIt = std::find_if(commandListToContextMapping.begin(), commandListToContextMapping.end(), [&commandList](const auto &other) { return other.first == commandList; });
    if (contextIt == commandListToContextMapping.end()) {
        log<Verbosity::error>("Could not retrieve context for command list (%p)", static_cast<void *>(commandList));
        return nullptr;
    }

    return contextIt->second;
}

void CommandListToContextTracker::registerCommandListToContextMapping(ze_command_list_handle_t commandList, ze_context_handle_t context) {
    commandListToContextMapping.emplace_back(commandList, context);
}

void CommandListToContextTracker::deregisterCommandListMapping(ze_command_list_handle_t commandList) {
    commandListToContextMapping.erase(std::remove_if(commandListToContextMapping.begin(), commandListToContextMapping.end(), [&commandList](const auto &other) { return other.first == commandList; }));
}

} // namespace Cal::Service::LevelZero
