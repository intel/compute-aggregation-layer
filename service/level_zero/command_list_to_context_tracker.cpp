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
    const auto contextIt = commandListToContextMapping.find(commandList);
    if (contextIt == commandListToContextMapping.end()) {
        log<Verbosity::error>("Could not retrieve context for command list (%p)", static_cast<void *>(commandList));
        return nullptr;
    }

    return contextIt->second;
}

void CommandListToContextTracker::registerCommandListToContextMapping(ze_command_list_handle_t commandList, ze_context_handle_t context) {
    if (commandListToContextMapping.count(commandList) != 0u) {
        log<Verbosity::error>("Cannot insert mapping between command list and context! "
                              "Mapping already exists! CommandList (%p), Context (%p)",
                              static_cast<void *>(commandList), static_cast<void *>(context));
    } else {
        commandListToContextMapping[commandList] = context;
    }
}

void CommandListToContextTracker::deregisterCommandListMapping(ze_command_list_handle_t commandList) {
    commandListToContextMapping.erase(commandList);
}

} // namespace Cal::Service::LevelZero
