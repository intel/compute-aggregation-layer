/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"

#include <unordered_map>

namespace Cal::Service::LevelZero {

class EventToContextTracker {
  public:
    ze_context_handle_t getAssociatedContext(ze_event_handle_t event) const;
    ze_event_pool_handle_t getAssociatedEventPool(ze_event_handle_t event) const;
    ze_context_handle_t getAssociatedContext(ze_event_pool_handle_t eventPool) const;

    void registerEventToEventPoolMapping(ze_event_handle_t event, ze_event_pool_handle_t eventPool);
    void registerEventPoolToContextMapping(ze_event_pool_handle_t eventPool, ze_context_handle_t context);

    void deregisterEventMapping(ze_event_handle_t event);
    void deregisterEventPoolMapping(ze_event_pool_handle_t eventPool);

  private:
    std::unordered_map<ze_event_handle_t, ze_event_pool_handle_t> eventToEventPoolMapping{};
    std::unordered_map<ze_event_pool_handle_t, ze_context_handle_t> eventPoolToContextMapping{};
};

} // namespace Cal::Service::LevelZero
