/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "event_to_context_tracker.h"

#include "shared/log.h"

namespace Cal::Service::LevelZero {

ze_context_handle_t EventToContextTracker::getAssociatedContext(ze_event_handle_t event) const {
    const auto eventPool = getAssociatedEventPool(event);
    return getAssociatedContext(eventPool);
}

ze_event_pool_handle_t EventToContextTracker::getAssociatedEventPool(ze_event_handle_t event) const {
    const auto eventPoolIt = eventToEventPoolMapping.find(event);
    if (eventPoolIt == eventToEventPoolMapping.end()) {
        log<Verbosity::error>("Could not retrieve event pool for event (%p)", static_cast<void *>(event));
        return nullptr;
    }

    return eventPoolIt->second;
}

ze_context_handle_t EventToContextTracker::getAssociatedContext(ze_event_pool_handle_t eventPool) const {
    const auto contextIt = eventPoolToContextMapping.find(eventPool);
    if (contextIt == eventPoolToContextMapping.end()) {
        log<Verbosity::error>("Could not retrieve context for event pool (%p)", static_cast<void *>(eventPool));
        return nullptr;
    }

    return contextIt->second;
}

void EventToContextTracker::registerEventToEventPoolMapping(ze_event_handle_t event, ze_event_pool_handle_t eventPool) {
    if (eventToEventPoolMapping.count(event) != 0u) {
        log<Verbosity::error>("Cannot insert mapping between event and event pool! "
                              "Mapping already exists! Event (%p), EventPool (%p)",
                              static_cast<void *>(event), static_cast<void *>(eventPool));
    } else {
        eventToEventPoolMapping[event] = eventPool;
    }
}

void EventToContextTracker::registerEventPoolToContextMapping(ze_event_pool_handle_t eventPool, ze_context_handle_t context) {
    if (eventPoolToContextMapping.count(eventPool) != 0u) {
        log<Verbosity::error>("Cannot insert mapping between event pool and context! "
                              "Mapping already exists! EventPool (%p), Context (%p)",
                              static_cast<void *>(eventPool), static_cast<void *>(context));
    } else {
        eventPoolToContextMapping[eventPool] = context;
    }
}

void EventToContextTracker::deregisterEventMapping(ze_event_handle_t event) {
    eventToEventPoolMapping.erase(event);
}

void EventToContextTracker::deregisterEventPoolMapping(ze_event_pool_handle_t eventPool) {
    eventPoolToContextMapping.erase(eventPool);
}

} // namespace Cal::Service::LevelZero
