/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "service/level_zero/artificial_events_manager.h"

#include <cstddef>

namespace Cal::Mocks {

class MockArtificialEventsManager : public Cal::Service::LevelZero::ArtificialEventsManager {
  public:
    using ArtificialEventsManager::EventPool;
    using ArtificialEventsManager::eventPools;
    using ArtificialEventsManager::eventsAllocator;
    using ArtificialEventsManager::eventsCountPerPool;

    ~MockArtificialEventsManager() override = default;

    void resetObtainedEvent(ze_event_handle_t artificialEvent) override {
        ++resetObtainedEventCallsCount;

        if (callBaseResetObtainedEvent) {
            ArtificialEventsManager::resetObtainedEvent(artificialEvent);
        }
    }

    void returnObtainedEvent(ze_event_handle_t artificialEvent) override {
        ++returnObtainedEventCallsCount;

        if (callBaseReturnObtainedEvent) {
            ArtificialEventsManager::returnObtainedEvent(artificialEvent);
        }
    }

    bool callBaseReturnObtainedEvent{true};
    size_t returnObtainedEventCallsCount{0};
    bool callBaseResetObtainedEvent{true};
    size_t resetObtainedEventCallsCount{0};
};

} // namespace Cal::Mocks
