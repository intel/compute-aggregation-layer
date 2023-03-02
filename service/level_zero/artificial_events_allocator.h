/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"

#include <cstdint>

namespace Cal::Service::LevelZero {

class ArtificialEventsAllocator {
  public:
    mockable ~ArtificialEventsAllocator() = default;

    mockable ze_event_pool_handle_t createEventPool(ze_context_handle_t context, uint32_t eventsCount);
    mockable ze_event_handle_t createEvent(ze_event_pool_handle_t eventPool, uint32_t index);

    mockable void destroyEventPool(ze_event_pool_handle_t eventPool);
    mockable void destroyEvent(ze_event_handle_t event);
    mockable void resetEvent(ze_event_handle_t event);

  protected:
    mockable ze_result_t l0DestroyEvent(ze_event_handle_t event);
    mockable ze_result_t l0DestroyEventPool(ze_event_pool_handle_t eventPool);
    mockable ze_result_t l0ResetEvent(ze_event_handle_t event);
    mockable ze_result_t l0CreateEventPool(ze_context_handle_t context, const ze_event_pool_desc_t &desc, ze_event_pool_handle_t &eventPool);
    mockable ze_result_t l0CreateEvent(ze_event_pool_handle_t eventPool, const ze_event_desc_t &desc, ze_event_handle_t &event);
};

} // namespace Cal::Service::LevelZero
