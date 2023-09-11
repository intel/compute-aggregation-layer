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
    auto it = commandListToContextMapping.find(commandList);
    if (it == commandListToContextMapping.end()) {
        log<Verbosity::error>("Could not find context associated with commandlist %p", commandList);
        return nullptr;
    }
    return it->second;
}

void CommandListToContextTracker::registerCommandListToContextMapping(ze_command_list_handle_t commandList, ze_context_handle_t context) {
    log<Verbosity::bloat>("Registering commandlist %p to context %p", commandList, context);
    commandListToContextMapping.insert(std::make_pair(commandList, context));
}

void CommandListToContextTracker::deregisterCommandListMapping(ze_command_list_handle_t commandList) {
    log<Verbosity::bloat>("Deregistering commandlist %p", commandList);
    commandListToContextMapping.erase(commandList);
}

} // namespace Cal::Service::LevelZero
