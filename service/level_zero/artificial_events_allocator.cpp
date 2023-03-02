/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "artificial_events_allocator.h"

#include "generated_service_level_zero.h"
#include "shared/log.h"

namespace Cal::Service::LevelZero {

ze_event_pool_handle_t ArtificialEventsAllocator::createEventPool(ze_context_handle_t context, uint32_t eventsCount) {
    ze_event_pool_handle_t eventPool{};

    ze_event_pool_desc_t eventPoolDesc{ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
    eventPoolDesc.count = eventsCount;
    eventPoolDesc.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;

    const auto result = l0CreateEventPool(context, eventPoolDesc, eventPool);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("ArtificialEventsAllocator: could not create event pool for context (%p)! Error code: %d",
                              static_cast<void *>(context),
                              static_cast<int>(result));
        return nullptr;
    }

    return eventPool;
}

ze_result_t ArtificialEventsAllocator::l0CreateEventPool(ze_context_handle_t context, const ze_event_pool_desc_t &desc, ze_event_pool_handle_t &eventPool) {
    return Cal::Service::Apis::LevelZero::Standard::zeEventPoolCreate(context, &desc, 0u, nullptr, &eventPool);
}

ze_event_handle_t ArtificialEventsAllocator::createEvent(ze_event_pool_handle_t eventPool, uint32_t index) {
    ze_event_handle_t event{};

    ze_event_desc_t eventDesc{ZE_STRUCTURE_TYPE_EVENT_DESC};
    eventDesc.index = index;
    eventDesc.wait = ZE_EVENT_SCOPE_FLAG_HOST;
    eventDesc.signal = ZE_EVENT_SCOPE_FLAG_HOST;

    const auto result = l0CreateEvent(eventPool, eventDesc, event);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("ArtificialEventsAllocator: could not create event for event pool (%p)! Error code: %d",
                              static_cast<void *>(eventPool),
                              static_cast<int>(result));
        return nullptr;
    }

    return event;
}

ze_result_t ArtificialEventsAllocator::l0CreateEvent(ze_event_pool_handle_t eventPool, const ze_event_desc_t &desc, ze_event_handle_t &event) {
    return Cal::Service::Apis::LevelZero::Standard::zeEventCreate(eventPool, &desc, &event);
}

void ArtificialEventsAllocator::destroyEventPool(ze_event_pool_handle_t eventPool) {
    const auto result = l0DestroyEventPool(eventPool);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("ArtificialEventsAllocator: could not destroy event pool (%p)! Error code: %d",
                              static_cast<void *>(eventPool),
                              static_cast<int>(result));
    }
}

ze_result_t ArtificialEventsAllocator::l0DestroyEventPool(ze_event_pool_handle_t eventPool) {
    return Cal::Service::Apis::LevelZero::Standard::zeEventPoolDestroy(eventPool);
}

void ArtificialEventsAllocator::destroyEvent(ze_event_handle_t event) {
    const auto result = l0DestroyEvent(event);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("ArtificialEventsAllocator: could not destroy event (%p)! Error code: %d",
                              static_cast<void *>(event),
                              static_cast<int>(result));
    }
}

ze_result_t ArtificialEventsAllocator::l0DestroyEvent(ze_event_handle_t event) {
    return Cal::Service::Apis::LevelZero::Standard::zeEventDestroy(event);
}

void ArtificialEventsAllocator::resetEvent(ze_event_handle_t event) {
    const auto result = l0ResetEvent(event);
    if (result != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("ArtificialEventsAllocator: could not reset event (%p)! Error code: %d",
                              static_cast<void *>(event),
                              static_cast<int>(result));
    }
}

ze_result_t ArtificialEventsAllocator::l0ResetEvent(ze_event_handle_t event) {
    return Cal::Service::Apis::LevelZero::Standard::zeEventHostReset(event);
}

} // namespace Cal::Service::LevelZero
