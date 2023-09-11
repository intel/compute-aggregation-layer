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
    eventPools.erase(context);
}

ze_event_handle_t ArtificialEventsManager::obtainEventReplacement(ze_context_handle_t context) {
    if (nullptr == context) {
        return nullptr;
    }
    auto &pool = this->eventPools[context];
    if (!pool.get()) {
        pool = std::make_unique<EventPool>(this->eventsAllocator.get());
    }

    for (auto &event : pool->events) {
        if (event.isFree) {
            event.isFree = false;
            return event.eventHandle;
        }
    }

    if (pool->pools.empty() || pool->eventsFromCurrentPool >= ArtificialEventsManager::eventsCountPerPool) {
        auto newlyCreatedEventPool = eventsAllocator->createEventPool(context, ArtificialEventsManager::eventsCountPerPool);
        if (nullptr == newlyCreatedEventPool) {
            return nullptr;
        }
        pool->pools.push_back(newlyCreatedEventPool);
        pool->eventsFromCurrentPool = 0u;
    }

    auto eventPool = pool->pools.back();
    auto event = eventsAllocator->createEvent(eventPool, pool->eventsFromCurrentPool++);
    if (nullptr != event) {
        pool->events.emplace_back(false, event);
    }

    return event;
}

void ArtificialEventsManager::returnObtainedEvent(ze_event_handle_t artificialEvent) {
    for (auto &eventPool : eventPools) {
        for (auto &event : eventPool.second->events) {
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
