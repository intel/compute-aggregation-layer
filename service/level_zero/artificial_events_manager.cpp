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

ArtificialEventsManager::~ArtificialEventsManager() {
    for (auto &entry : eventPools) {
        for (auto &eventPool : entry.second) {
            destroyEventPool(eventPool);
        }
    }

    events.clear();
    eventPools.clear();
    eventsAllocator.reset();
}

void ArtificialEventsManager::destroyEventPool(ze_event_pool_handle_t eventPool) {
    if (events.count(eventPool) != 0u) {
        for (auto &artificialEvent : events[eventPool]) {
            if (!artificialEvent.eventHandle) {
                break;
            }

            eventsAllocator->destroyEvent(artificialEvent.eventHandle);
        }
    }

    eventsAllocator->destroyEventPool(eventPool);
}

void ArtificialEventsManager::clearDataForContext(ze_context_handle_t context) {
    if (eventPools.count(context) == 0u) {
        return;
    }

    for (auto &eventPool : eventPools[context]) {
        destroyEventPool(eventPool);
        events.erase(eventPool);
    }

    eventPools.erase(context);
}

ze_event_handle_t ArtificialEventsManager::obtainEventReplacement(ze_context_handle_t context) {
    auto eventPool = getEventPoolWithFreeEntries(context);
    if (!eventPool) {
        log<Verbosity::error>("ArtificialEventsManager: could not get event pool for context (%p)!", static_cast<void *>(context));
        return nullptr;
    }

    auto event = getFreeEvent(eventPool);
    if (!event) {
        log<Verbosity::error>("ArtificialEventsManager: could not get free event from event pool (%p)!", static_cast<void *>(eventPool));
        return nullptr;
    }

    return event;
}

ze_event_pool_handle_t ArtificialEventsManager::getEventPoolWithFreeEntries(ze_context_handle_t context) {
    if (eventPools.count(context) != 0u) {
        for (auto &eventPool : eventPools[context]) {
            if (getIndexOfFirstFreeEvent(eventPool) != -1) {
                return eventPool;
            }
        }
    }

    auto eventPool = eventsAllocator->createEventPool(context, eventsCountPerPool);
    if (!eventPool) {
        log<Verbosity::error>("ArtificialEventsManager: Could not create event pool for context (%p)!", static_cast<void *>(context));
        return nullptr;
    }

    eventPools[context].push_back(eventPool);
    events[eventPool].resize(eventsCountPerPool);

    return eventPool;
}

int ArtificialEventsManager::getIndexOfFirstFreeEvent(ze_event_pool_handle_t eventPool) {
    if (events.count(eventPool) == 0u) {
        return -1;
    }

    auto &eventsContainer = events[eventPool];
    for (auto i = 0u; i < eventsContainer.size(); ++i) {
        if (eventsContainer[i].isFree) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

ze_event_handle_t ArtificialEventsManager::getFreeEvent(ze_event_pool_handle_t eventPool) {
    auto freeEventIndex = getIndexOfFirstFreeEvent(eventPool);
    if (freeEventIndex == -1) {
        log<Verbosity::error>("ArtificialEventsManager: Tried to get event from full event pool! This should not happen!");
        return nullptr;
    }

    auto index = static_cast<uint32_t>(freeEventIndex);
    auto &freeEvent = events[eventPool][index];

    if (!freeEvent.eventHandle) {
        freeEvent.eventHandle = eventsAllocator->createEvent(eventPool, index);
    }

    if (!freeEvent.eventHandle) {
        log<Verbosity::error>("ArtificialEventsManager: Could not create new event!");
        return nullptr;
    }

    freeEvent.isFree = false;
    return freeEvent.eventHandle;
}

void ArtificialEventsManager::returnObtainedEvent(ze_event_handle_t artificialEvent) {
    for (auto &entry : events) {
        auto &eventsContainer = entry.second;

        for (auto &event : eventsContainer) {
            if (event.eventHandle == artificialEvent) {
                event.isFree = true;
                eventsAllocator->resetEvent(event.eventHandle);
                return;
            }
        }
    }

    log<Verbosity::error>("ArtificialEventsManager: Could not return event that was not obtained from manager! Event (%p)!", static_cast<void *>(artificialEvent));
}

} // namespace Cal::Service::LevelZero
