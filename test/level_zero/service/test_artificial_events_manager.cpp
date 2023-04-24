/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "service/level_zero/artificial_events_manager.h"
#include "test/mocks/artificial_events_allocator_mock.h"
#include "test/mocks/artificial_events_manager_mock.h"
#include "test/mocks/log_mock.h"

#include <array>
#include <memory>
#include <utility>

namespace Cal::Test::LevelZero::Service {

class ArtificialEventsManagerTest : public ::testing::Test {
  public:
    void SetUp() override {
        auto allocatorOwner = std::make_unique<Cal::Mocks::MockArtificialEventsAllocator>();
        this->allocator = allocatorOwner.get();

        eventsManager.eventsAllocator = std::move(allocatorOwner);
    }

    Cal::Mocks::MockArtificialEventsAllocator *allocator{};
    Cal::Mocks::MockArtificialEventsManager eventsManager{};
};

TEST_F(ArtificialEventsManagerTest, GivenCreatedEventPoolsForContextsWhenTryingToGetEventPoolsThenTheyAreReturnedAndNoErrorIsReported) {
    EXPECT_EQ(eventsManager.eventPools.size(), 0u);

    auto firstContext = reinterpret_cast<ze_context_handle_t>(0x3456);
    auto secondContext = reinterpret_cast<ze_context_handle_t>(0x5456);
    auto thirdContext = reinterpret_cast<ze_context_handle_t>(0x7899);

    allocator->eventPoolsToCreate[firstContext].resize(2);
    allocator->eventPoolsToCreate[secondContext].resize(2);
    allocator->eventPoolsToCreate[thirdContext].resize(2);
    for (auto &context : {firstContext, secondContext, thirdContext}) {
        for (size_t i = 0; i < 2; ++i) {
            allocator->eventPoolsToCreate[context].push_back(reinterpret_cast<ze_event_pool_handle_t>(i));
        }
    }
    for (auto &context : allocator->eventPoolsToCreate) {
        for (auto &pool : context.second) {
            for (size_t i = 0u; i < 128; ++i) {
                allocator->eventsToCreate[pool].push_back(reinterpret_cast<ze_event_handle_t>(i));
            }
        }
    }

    auto event1FromContext1 = eventsManager.obtainEventReplacement(firstContext);

    EXPECT_EQ(eventsManager.eventPools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);

    auto event1FromContext2 = eventsManager.obtainEventReplacement(secondContext);
    EXPECT_EQ(eventsManager.eventPools.size(), 2u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[1].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[1].context, secondContext);
    EXPECT_EQ(eventsManager.eventPools[1].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[1].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].events[0].eventHandle, event1FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[0].isFree);

    auto event1FromContext3 = eventsManager.obtainEventReplacement(thirdContext);
    EXPECT_EQ(eventsManager.eventPools.size(), 3u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[1].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[1].context, secondContext);
    EXPECT_EQ(eventsManager.eventPools[1].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[1].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].events[0].eventHandle, event1FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[2].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[2].context, thirdContext);
    EXPECT_EQ(eventsManager.eventPools[2].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[2].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].events[0].eventHandle, event1FromContext3);
    EXPECT_FALSE(eventsManager.eventPools[2].events[0].isFree);

    std::array<ze_event_handle_t, Cal::Service::LevelZero::ArtificialEventsManager::eventsCountPerPool - 1> eventsFromContext2;
    for (size_t i = 0; i < eventsFromContext2.size(); ++i) {
        eventsFromContext2[i] = eventsManager.obtainEventReplacement(secondContext);
    }
    EXPECT_EQ(eventsManager.eventPools.size(), 3u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[1].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[1].context, secondContext);
    EXPECT_EQ(eventsManager.eventPools[1].events.size(), Cal::Service::LevelZero::ArtificialEventsManager::eventsCountPerPool);
    EXPECT_EQ(eventsManager.eventPools[1].eventsFromCurrentPool, Cal::Service::LevelZero::ArtificialEventsManager::eventsCountPerPool);
    EXPECT_EQ(eventsManager.eventPools[1].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].events[0].eventHandle, event1FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[0].isFree);
    for (size_t i = 1; i < eventsManager.eventPools[1].events.size(); ++i) {
        EXPECT_EQ(eventsManager.eventPools[1].events[i].eventHandle, eventsFromContext2[i - 1]);
        EXPECT_FALSE(eventsManager.eventPools[1].events[i].isFree);
    }
    EXPECT_EQ(eventsManager.eventPools[2].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[2].context, thirdContext);
    EXPECT_EQ(eventsManager.eventPools[2].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[2].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].events[0].eventHandle, event1FromContext3);
    EXPECT_FALSE(eventsManager.eventPools[2].events[0].isFree);

    auto event2FromContext2 = eventsManager.obtainEventReplacement(secondContext);
    EXPECT_EQ(eventsManager.eventPools.size(), 3u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[1].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[1].context, secondContext);
    EXPECT_EQ(eventsManager.eventPools[1].events.size(), Cal::Service::LevelZero::ArtificialEventsManager::eventsCountPerPool + 1u);
    EXPECT_EQ(eventsManager.eventPools[1].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[1].pools.size(), 2u);
    EXPECT_EQ(eventsManager.eventPools[1].events[0].eventHandle, event1FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[0].isFree);
    for (size_t i = 1; i < eventsManager.eventPools[1].events.size() - 1; ++i) {
        EXPECT_EQ(eventsManager.eventPools[1].events[i].eventHandle, eventsFromContext2[i - 1]);
        EXPECT_FALSE(eventsManager.eventPools[1].events[i].isFree);
    }
    EXPECT_EQ(eventsManager.eventPools[1].events[eventsManager.eventPools[1].events.size() - 1].eventHandle, event2FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[eventsManager.eventPools[1].events.size() - 1].isFree);
    EXPECT_EQ(eventsManager.eventPools[2].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[2].context, thirdContext);
    EXPECT_EQ(eventsManager.eventPools[2].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[2].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].events[0].eventHandle, event1FromContext3);
    EXPECT_FALSE(eventsManager.eventPools[2].events[0].isFree);

    eventsManager.returnObtainedEvent(eventsFromContext2[47]);
    EXPECT_TRUE(eventsManager.eventPools[1].events[48].isFree);

    auto firstFreeEventFromContext2 = eventsManager.obtainEventReplacement(secondContext);
    EXPECT_EQ(firstFreeEventFromContext2, eventsFromContext2[47]);
    EXPECT_EQ(eventsManager.eventPools.size(), 3u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[1].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[1].context, secondContext);
    EXPECT_EQ(eventsManager.eventPools[1].events.size(), Cal::Service::LevelZero::ArtificialEventsManager::eventsCountPerPool + 1u);
    EXPECT_EQ(eventsManager.eventPools[1].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[1].pools.size(), 2u);
    EXPECT_EQ(eventsManager.eventPools[1].events[0].eventHandle, event1FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[0].isFree);
    for (size_t i = 1; i < eventsManager.eventPools[1].events.size() - 1; ++i) {
        EXPECT_EQ(eventsManager.eventPools[1].events[i].eventHandle, eventsFromContext2[i - 1]);
        EXPECT_FALSE(eventsManager.eventPools[1].events[i].isFree);
    }
    EXPECT_EQ(eventsManager.eventPools[1].events[eventsManager.eventPools[1].events.size() - 1].eventHandle, event2FromContext2);
    EXPECT_FALSE(eventsManager.eventPools[1].events[eventsManager.eventPools[1].events.size() - 1].isFree);
    EXPECT_EQ(eventsManager.eventPools[2].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[2].context, thirdContext);
    EXPECT_EQ(eventsManager.eventPools[2].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[2].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[2].events[0].eventHandle, event1FromContext3);
    EXPECT_FALSE(eventsManager.eventPools[2].events[0].isFree);

    eventsManager.clearDataForContext(secondContext);
    EXPECT_EQ(eventsManager.eventPools.size(), 2u);
    EXPECT_EQ(eventsManager.eventPools[0].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[0].context, firstContext);
    EXPECT_EQ(eventsManager.eventPools[0].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[0].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[0].events[0].eventHandle, event1FromContext1);
    EXPECT_FALSE(eventsManager.eventPools[0].events[0].isFree);
    EXPECT_EQ(eventsManager.eventPools[1].allocator, eventsManager.eventsAllocator.get());
    EXPECT_EQ(eventsManager.eventPools[1].context, thirdContext);
    EXPECT_EQ(eventsManager.eventPools[1].events.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].eventsFromCurrentPool, 1u);
    EXPECT_EQ(eventsManager.eventPools[1].pools.size(), 1u);
    EXPECT_EQ(eventsManager.eventPools[1].events[0].eventHandle, event1FromContext3);
    EXPECT_FALSE(eventsManager.eventPools[1].events[0].isFree);
}

TEST_F(ArtificialEventsManagerTest, GivenErrorOnEventPoolCreationWhenTryingToObtainEventReplacementThenNullptrIsReturnedAndErrorIsPrinted) {
    auto contextOfOriginalEvent = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    auto event = eventsManager.obtainEventReplacement(contextOfOriginalEvent);

    EXPECT_EQ(nullptr, event);
    EXPECT_FALSE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenErrorOnEventCreationWhenTryingToObtainEventReplacementThenNullptrIsReturnedAndErrorIsPrinted) {
    auto contextOfOriginalEvent = reinterpret_cast<ze_context_handle_t>(0x3456);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    allocator->eventPoolsToCreate[contextOfOriginalEvent].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;
    auto event = eventsManager.obtainEventReplacement(contextOfOriginalEvent);

    EXPECT_EQ(nullptr, event);
    EXPECT_FALSE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenNonRegisteredContextWhenTryingToClearItsDataThenNothingHappensAndErrorIsNotPrinted) {
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    eventsManager.clearDataForContext(context);

    EXPECT_TRUE(logs.empty());
}

} // namespace Cal::Test::LevelZero::Service
