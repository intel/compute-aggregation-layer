/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "boost/container/flat_map.hpp"
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
        ArtificialEvent(bool isFree, ze_event_handle_t handle) : isFree(isFree), eventHandle(handle){};
    };

  public:
    mockable ~ArtificialEventsManager();
    ArtificialEventsManager();
    ArtificialEventsManager(const ArtificialEventsManager &other) = delete;
    ArtificialEventsManager(ArtificialEventsManager &&other) = delete;
    ArtificialEventsManager &operator=(const ArtificialEventsManager &other) = delete;
    ArtificialEventsManager &operator=(ArtificialEventsManager &&other) = delete;

    ze_event_handle_t obtainEventReplacement(ze_context_handle_t context);
    mockable void returnObtainedEvent(ze_event_handle_t artificialEvent);
    mockable void resetObtainedEvent(ze_event_handle_t artificialEvent);
    void clearDataForContext(ze_context_handle_t context);

    inline static constexpr uint32_t eventsCountPerPool = 64u;

  protected:
    std::unique_ptr<ArtificialEventsAllocator> eventsAllocator{new ArtificialEventsAllocator{}};
    struct EventPool {
        std::vector<ze_event_pool_handle_t> pools;
        std::vector<ArtificialEvent> events;
        uint32_t eventsFromCurrentPool = 0u;
        ArtificialEventsAllocator *allocator = nullptr;

        EventPool(ArtificialEventsAllocator *allocator) : allocator(allocator) {
            pools.reserve(1);
            events.reserve(64);
        };
        ~EventPool();
    };
    boost::container::flat_map<ze_context_handle_t, std::unique_ptr<EventPool>> eventPools;
};

} // namespace Cal::Service::LevelZero
