/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "service/level_zero/artificial_events_allocator.h"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Cal::Service::LevelZero {

class ArtificialEventsManager {
  private:
    struct ArtificialEvent {
        bool isFree{true};
        ze_event_handle_t eventHandle{};
    };

  public:
    mockable ~ArtificialEventsManager();
    ArtificialEventsManager() = default;
    ArtificialEventsManager(const ArtificialEventsManager &other) = delete;
    ArtificialEventsManager(ArtificialEventsManager &&other) = delete;
    ArtificialEventsManager &operator=(const ArtificialEventsManager &other) = delete;
    ArtificialEventsManager &operator=(ArtificialEventsManager &&other) = delete;

    ze_event_handle_t obtainEventReplacement(ze_context_handle_t context);
    mockable void returnObtainedEvent(ze_event_handle_t artificialEvent);
    mockable void resetObtainedEvent(ze_event_handle_t artificialEvent);
    void clearDataForContext(ze_context_handle_t context);

  protected:
    void destroyEventPool(ze_event_pool_handle_t eventPool);

    ze_event_pool_handle_t getEventPoolWithFreeEntries(ze_context_handle_t context);
    ze_event_handle_t getFreeEvent(ze_event_pool_handle_t eventPool);
    int getIndexOfFirstFreeEvent(ze_event_pool_handle_t eventPool);

    uint32_t eventsCountPerPool{64u};
    std::unique_ptr<ArtificialEventsAllocator> eventsAllocator{new ArtificialEventsAllocator{}};
    std::unordered_map<ze_context_handle_t, std::vector<ze_event_pool_handle_t>> eventPools{};
    std::unordered_map<ze_event_pool_handle_t, std::vector<ArtificialEvent>> events{};
};

} // namespace Cal::Service::LevelZero
