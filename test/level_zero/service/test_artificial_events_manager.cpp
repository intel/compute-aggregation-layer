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
    auto firstEventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto firstContext = reinterpret_cast<ze_context_handle_t>(0x3456);
    eventsManager.eventPools[firstContext].push_back(firstEventPool);
    eventsManager.events[firstEventPool].resize(64u);

    auto secondEventPool = reinterpret_cast<ze_event_pool_handle_t>(0x4345);
    auto secondContext = reinterpret_cast<ze_context_handle_t>(0x5456);
    eventsManager.eventPools[secondContext].push_back(secondEventPool);
    eventsManager.events[secondEventPool].resize(64u);

    Cal::Mocks::LogCaptureContext logs;
    auto firstRetrievedEventPool = eventsManager.getEventPoolWithFreeEntries(firstContext);
    auto secondRetrievedEventPool = eventsManager.getEventPoolWithFreeEntries(secondContext);

    EXPECT_EQ(firstEventPool, firstRetrievedEventPool);
    EXPECT_EQ(secondEventPool, secondRetrievedEventPool);

    EXPECT_TRUE(logs.empty());

    eventsManager.events.erase(firstEventPool);
    eventsManager.eventPools.erase(firstContext);

    eventsManager.events.erase(secondEventPool);
    eventsManager.eventPools.erase(secondContext);
}

TEST_F(ArtificialEventsManagerTest, GivenNotCreatedEventPoolForContextWhenTryingToGetEventPoolAndCreationSucceedsThenReturnNewlyCreatedEventPoolAndUpdateContainer) {
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    allocator->eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);

    EXPECT_EQ(eventPool, retrievedEventPool);

    ASSERT_EQ(1u, eventsManager.eventPools.count(context));
    EXPECT_EQ(1u, eventsManager.eventPools[context].size());
    ASSERT_EQ(1u, eventsManager.events.count(eventPool));
    EXPECT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest,
       GivenCreatedEventPoolForContextButWithoutFreeEventsWhenTryingToGetEventPoolForThatContextAndCreationSucceedsThenReturnNewlyCreatedEventPoolAndUpdateContainer) {
    // 0. Given.
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto anotherEventPool = reinterpret_cast<ze_event_pool_handle_t>(0x7745);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    allocator->eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);

    EXPECT_EQ(eventPool, retrievedEventPool);

    ASSERT_EQ(1u, eventsManager.eventPools.count(context));
    EXPECT_EQ(1u, eventsManager.eventPools[context].size());
    ASSERT_EQ(1u, eventsManager.events.count(eventPool));
    EXPECT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    for (auto &artificialEvent : eventsManager.events[eventPool]) {
        artificialEvent.isFree = false;
    }

    allocator->eventPoolsToCreate[context].push_back(anotherEventPool);

    // 1. When.
    auto anotherRetrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);

    // 2. Then.
    EXPECT_EQ(anotherEventPool, anotherRetrievedEventPool);

    ASSERT_EQ(1u, eventsManager.eventPools.count(context));
    EXPECT_EQ(2u, eventsManager.eventPools[context].size());
    ASSERT_EQ(1u, eventsManager.events.count(anotherEventPool));
    EXPECT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[anotherEventPool].size());

    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenNotCreatedEventPoolForContextWhenTryingToGetEventPoolAndCreationFailsThenReturnNullptrAndPrintError) {
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);

    EXPECT_EQ(nullptr, retrievedEventPool);
    EXPECT_FALSE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenNotCreatedEventPoolWhenTryingToGetFreeEventFromItThenNullptrIsReturnedAndErrorIsPrinted) {
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEvent = eventsManager.getFreeEvent(eventPool);

    EXPECT_EQ(nullptr, retrievedEvent);
    EXPECT_FALSE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenCreatedEventPoolWithNoFreeEntriesWhenTryingToGetFreeEventFromItThenNullptrIsReturnedAndErrorIsPrinted) {
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    // 0. Given.
    allocator->eventPoolsToCreate[context].push_back(eventPool);
    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);

    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    for (auto &artificialEvent : eventsManager.events[eventPool]) {
        artificialEvent.isFree = false;
    }

    // 1. When.
    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEvent = eventsManager.getFreeEvent(eventPool);

    // 2. Then.
    EXPECT_EQ(nullptr, retrievedEvent);
    EXPECT_FALSE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenCreatedEventPoolWithFreeEntriesWhenTryingToGetFreeEventFromItThenEventIsMarkedAsUsedAndReturnedAndNoLogsArePrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    // 0. Given.
    allocator->eventsToCreate[eventPool].resize(eventsManager.eventsCountPerPool);
    allocator->eventsToCreate[eventPool][0] = event;
    allocator->eventPoolsToCreate[context].push_back(eventPool);

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    // 1. When.
    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEvent = eventsManager.getFreeEvent(eventPool);

    // 2. Then.
    EXPECT_EQ(event, retrievedEvent);
    EXPECT_EQ(event, eventsManager.events[eventPool][0].eventHandle);
    EXPECT_FALSE(eventsManager.events[eventPool][0].isFree);
    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenCreatedEventPoolWithFreeEntriesWhenTryingToGetFreeEventFromItAndFreeEventWasCreatedThenEventIsMarkedAsUsedAndReturnedAndNoLogsArePrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    // 0. Given.
    allocator->eventsToCreate[eventPool].resize(eventsManager.eventsCountPerPool);
    allocator->eventsToCreate[eventPool][0] = event;
    allocator->eventPoolsToCreate[context].push_back(eventPool);

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEvent = eventsManager.getFreeEvent(eventPool);

    EXPECT_EQ(event, retrievedEvent);
    EXPECT_EQ(event, eventsManager.events[eventPool][0].eventHandle);
    EXPECT_FALSE(eventsManager.events[eventPool][0].isFree);

    eventsManager.events[eventPool][0].isFree = true;

    // 1. When.
    auto retrievedEvent2 = eventsManager.getFreeEvent(eventPool);

    // 2. Then.
    EXPECT_EQ(event, retrievedEvent2);
    EXPECT_TRUE(logs.empty());
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

TEST_F(ArtificialEventsManagerTest, GivenCreatedEventPoolAndEventWhenTryingToReturnItThenIsMarkedAsUnusedAndNoLogsArePrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    // 0. Given.
    allocator->eventsToCreate[eventPool].resize(eventsManager.eventsCountPerPool);
    allocator->eventsToCreate[eventPool][0] = event;
    allocator->eventPoolsToCreate[context].push_back(eventPool);

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEvent = eventsManager.getFreeEvent(eventPool);

    EXPECT_EQ(event, retrievedEvent);
    EXPECT_EQ(event, eventsManager.events[eventPool][0].eventHandle);
    EXPECT_FALSE(eventsManager.events[eventPool][0].isFree);

    // 1. When.
    eventsManager.returnObtainedEvent(event);

    // 2. Then.
    EXPECT_TRUE(eventsManager.events[eventPool][0].isFree);
    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenCreatedEventPoolAndEventWhenTryingToReturnUnknownEventThenNothingHappensAndErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    // 0. Given.
    allocator->eventsToCreate[eventPool].resize(eventsManager.eventsCountPerPool);
    allocator->eventsToCreate[eventPool][0] = event;
    allocator->eventPoolsToCreate[context].push_back(eventPool);

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(eventsManager.eventsCountPerPool, eventsManager.events[eventPool].size());

    Cal::Mocks::LogCaptureContext logs;
    auto retrievedEvent = eventsManager.getFreeEvent(eventPool);

    EXPECT_EQ(event, retrievedEvent);
    EXPECT_EQ(event, eventsManager.events[eventPool][0].eventHandle);
    EXPECT_FALSE(eventsManager.events[eventPool][0].isFree);

    // 1. When.
    auto unknownEvent = reinterpret_cast<ze_event_handle_t>(0x7777);
    eventsManager.returnObtainedEvent(unknownEvent);

    // 2. Then.
    EXPECT_FALSE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenNonRegisteredContextWhenTryingToClearItsDataThenNothingHappensAndErrorIsNotPrinted) {
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    eventsManager.clearDataForContext(context);

    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenRegisteredContextWhenTryingToClearItsDataThenItIsClearedAndErrorIsNotPrinted) {
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    // 0. Given.
    allocator->eventPoolsToCreate[context].push_back(eventPool);
    Cal::Mocks::LogCaptureContext logs;

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(1u, eventsManager.eventPools.count(context));
    ASSERT_EQ(1u, eventsManager.events.count(eventPool));

    // 1. When.
    eventsManager.clearDataForContext(context);

    // 2. Then.
    EXPECT_EQ(0u, eventsManager.eventPools.count(context));
    ASSERT_EQ(0u, eventsManager.events.count(eventPool));
    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenNonRegisteredEventPoolWhenTryingToGetFreeEventIndexThenReturnInvalidIndex) {
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto index = eventsManager.getIndexOfFirstFreeEvent(eventPool);

    constexpr auto invalidIndex = -1;
    EXPECT_EQ(invalidIndex, index);
}

TEST_F(ArtificialEventsManagerTest, GivenRegisteredEventPoolWithoutFreeEntriesWhenTryingToGetFreeEventIndexThenReturnInvalidIndex) {
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    // 0. Given.
    allocator->eventPoolsToCreate[context].push_back(eventPool);
    Cal::Mocks::LogCaptureContext logs;

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(1u, eventsManager.eventPools.count(context));
    ASSERT_EQ(1u, eventsManager.events.count(eventPool));

    for (auto &artificialEvent : eventsManager.events[eventPool]) {
        artificialEvent.isFree = false;
    }

    // 1. When.
    auto index = eventsManager.getIndexOfFirstFreeEvent(eventPool);

    // 2. Then.
    constexpr auto invalidIndex = -1;
    EXPECT_EQ(invalidIndex, index);

    EXPECT_TRUE(logs.empty());
}

TEST_F(ArtificialEventsManagerTest, GivenRegisteredEventPoolWithLastFreeEntryWhenTryingToGetFreeEventIndexThenReturnLastFreeEntryIndex) {
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    // 0. Given.
    allocator->eventPoolsToCreate[context].push_back(eventPool);
    Cal::Mocks::LogCaptureContext logs;

    auto retrievedEventPool = eventsManager.getEventPoolWithFreeEntries(context);
    ASSERT_EQ(eventPool, retrievedEventPool);
    ASSERT_EQ(1u, eventsManager.eventPools.count(context));
    ASSERT_EQ(1u, eventsManager.events.count(eventPool));

    for (auto &artificialEvent : eventsManager.events[eventPool]) {
        artificialEvent.isFree = false;
    }

    constexpr auto freeEntryIndex = 7;
    eventsManager.events[eventPool][freeEntryIndex].isFree = true;

    // 1. When.
    auto index = eventsManager.getIndexOfFirstFreeEvent(eventPool);

    // 2. Then.
    EXPECT_EQ(freeEntryIndex, index);
    EXPECT_TRUE(logs.empty());
}

} // namespace Cal::Test::LevelZero::Service
