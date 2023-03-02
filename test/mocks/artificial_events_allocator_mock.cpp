/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "artificial_events_allocator_mock.h"

namespace Cal::Mocks {

ze_result_t MockArtificialEventsAllocator::l0DestroyEvent(ze_event_handle_t event) {
    for (auto &entry : alreadyCreatedEvents) {
        for (auto &eventHandle : entry.second) {
            if (eventHandle == event) {
                eventHandle = nullptr;
                return ZE_RESULT_SUCCESS;
            }
        }
    }

    return ZE_RESULT_ERROR_DEVICE_LOST;
}

ze_result_t MockArtificialEventsAllocator::l0DestroyEventPool(ze_event_pool_handle_t eventPool) {
    if (alreadyCreatedEvents.count(eventPool) == 0u) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    alreadyCreatedEvents.erase(eventPool);
    return ZE_RESULT_SUCCESS;
}

ze_result_t MockArtificialEventsAllocator::l0ResetEvent(ze_event_handle_t event) {
    for (auto &entry : alreadyCreatedEvents) {
        for (auto &eventHandle : entry.second) {
            if (eventHandle == event) {
                return ZE_RESULT_SUCCESS;
            }
        }
    }

    return ZE_RESULT_ERROR_DEVICE_LOST;
}

ze_result_t MockArtificialEventsAllocator::l0CreateEventPool(ze_context_handle_t context,
                                                             const ze_event_pool_desc_t &desc,
                                                             ze_event_pool_handle_t &eventPool) {
    if (eventPoolsToCreate.count(context) == 0u) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    eventPool = eventPoolsToCreate[context].back();
    eventPoolsToCreate[context].pop_back();

    if (eventPoolsToCreate[context].empty()) {
        eventPoolsToCreate.erase(context);
    }

    auto &createdEvents = alreadyCreatedEvents[eventPool];
    createdEvents.resize(desc.count);

    return ZE_RESULT_SUCCESS;
}

ze_result_t MockArtificialEventsAllocator::l0CreateEvent(ze_event_pool_handle_t eventPool,
                                                         const ze_event_desc_t &desc,
                                                         ze_event_handle_t &event) {
    if (eventsToCreate.count(eventPool) == 0u) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    if (eventsToCreate[eventPool].size() <= desc.index) {
        return ZE_RESULT_ERROR_INVALID_SIZE;
    }

    if (eventsToCreate[eventPool][desc.index] == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    event = eventsToCreate[eventPool][desc.index];
    eventsToCreate[eventPool][desc.index] = nullptr;
    alreadyCreatedEvents[eventPool].at(desc.index) = event;

    return ZE_RESULT_SUCCESS;
}

} // namespace Cal::Mocks
