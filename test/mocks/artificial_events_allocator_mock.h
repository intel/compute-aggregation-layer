/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "service/level_zero/artificial_events_allocator.h"

#include <unordered_map>
#include <vector>

namespace Cal::Mocks {

class MockArtificialEventsAllocator : public Cal::Service::LevelZero::ArtificialEventsAllocator {
  public:
    ~MockArtificialEventsAllocator() override = default;

    ze_result_t l0DestroyEvent(ze_event_handle_t event) override;
    ze_result_t l0DestroyEventPool(ze_event_pool_handle_t eventPool) override;
    ze_result_t l0ResetEvent(ze_event_handle_t event) override;

    ze_result_t l0CreateEventPool(ze_context_handle_t context,
                                  const ze_event_pool_desc_t &desc,
                                  ze_event_pool_handle_t &eventPool) override;

    ze_result_t l0CreateEvent(ze_event_pool_handle_t eventPool,
                              const ze_event_desc_t &desc,
                              ze_event_handle_t &event) override;

    std::unordered_map<ze_context_handle_t, std::vector<ze_event_pool_handle_t>> eventPoolsToCreate{};
    std::unordered_map<ze_event_pool_handle_t, std::vector<ze_event_handle_t>> eventsToCreate{};
    std::unordered_map<ze_event_pool_handle_t, std::vector<ze_event_handle_t>> alreadyCreatedEvents{};
};

} // namespace Cal::Mocks
