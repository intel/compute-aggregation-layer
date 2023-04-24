/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "artificial_events_manager.h"

#include "shared/log.h"

#include <algorithm>
#include <functional>
#include <iterator>

namespace Cal::Service::LevelZero {

ArtificialEventsManager::~ArtificialEventsManager() = default;

ArtificialEventsManager::ArtificialEventsManager() {
    eventPools.reserve(2);
}

void ArtificialEventsManager::clearDataForContext(ze_context_handle_t context) {
    auto pos = std::remove_if(eventPools.begin(), eventPools.end(), [&context](const auto &other) { return other.context == context; });
    if (pos == eventPools.end()) {
        return;
    }
    eventPools.erase(pos);
}

ze_event_handle_t ArtificialEventsManager::obtainEventReplacement(ze_context_handle_t context) {
    auto pool = std::find_if(eventPools.begin(), eventPools.end(), [&context](const auto &other) { return other.context == context; });
    if (pool == eventPools.end()) {
        eventPools.emplace_back(eventsAllocator.get(), context);
        pool = std::prev(eventPools.end());
    }

    for (auto &event : pool->events) {
        if (event.isFree) {
            event.isFree = false;
            return event.eventHandle;
        }
    }

    if (pool->pools.empty() || pool->eventsFromCurrentPool >= ArtificialEventsManager::eventsCountPerPool) {
        pool->pools.push_back(eventsAllocator->createEventPool(context, ArtificialEventsManager::eventsCountPerPool));
        pool->eventsFromCurrentPool = 0u;
    }

    auto eventPool = pool->pools.back();
    auto event = eventsAllocator->createEvent(eventPool, pool->eventsFromCurrentPool++);
    pool->events.emplace_back(false, event);

    return event;
}

void ArtificialEventsManager::returnObtainedEvent(ze_event_handle_t artificialEvent) {
    for (auto &eventPool : eventPools) {
        for (auto &event : eventPool.events) {
            if (event.eventHandle == artificialEvent) {
                event.isFree = true;
                eventsAllocator->resetEvent(event.eventHandle);
                return;
            }
        }
    }

    log<Verbosity::error>("ArtificialEventsManager: Could not return event that was not obtained from manager! Event (%p)!", static_cast<void *>(artificialEvent));
}

void ArtificialEventsManager::resetObtainedEvent(ze_event_handle_t artificialEvent) {
    eventsAllocator->resetEvent(artificialEvent);
}

ArtificialEventsManager::EventPool::~EventPool() {
    for (auto &event : events) {
        allocator->destroyEvent(event.eventHandle);
    }
    events.clear();
    for (auto &pool : pools) {
        allocator->destroyEventPool(pool);
    }
    pools.clear();
}

} // namespace Cal::Service::LevelZero
