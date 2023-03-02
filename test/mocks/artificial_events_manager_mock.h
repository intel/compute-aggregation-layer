/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "service/level_zero/artificial_events_manager.h"

namespace Cal::Mocks {

class MockArtificialEventsManager : public Cal::Service::LevelZero::ArtificialEventsManager {
  public:
    using ArtificialEventsManager::destroyEventPool;
    using ArtificialEventsManager::eventPools;
    using ArtificialEventsManager::events;
    using ArtificialEventsManager::eventsAllocator;
    using ArtificialEventsManager::eventsCountPerPool;
    using ArtificialEventsManager::getEventPoolWithFreeEntries;
    using ArtificialEventsManager::getFreeEvent;
    using ArtificialEventsManager::getIndexOfFirstFreeEvent;
};

} // namespace Cal::Mocks
