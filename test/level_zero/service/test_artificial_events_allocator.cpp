/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "service/level_zero/artificial_events_allocator.h"
#include "test/mocks/artificial_events_allocator_mock.h"
#include "test/mocks/log_mock.h"

#include <cstdint>

using Cal::Mocks::MockArtificialEventsAllocator;

namespace Cal::Test::LevelZero::Service {

TEST(ArtificialEventsAllocatorTest, GivenFailingL0EventPoolCreationWhenTryingToCreateEventPoolThenNullptrIsReturnedAndErrorIsPrinted) {
    const uint32_t eventsCount{64};
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    MockArtificialEventsAllocator allocator;

    Cal::Mocks::LogCaptureContext logs;
    auto eventPool = allocator.createEventPool(context, eventsCount);

    EXPECT_EQ(nullptr, eventPool);
    EXPECT_FALSE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenSuccessfulL0EventPoolCreationWhenTryingToCreateEventPoolThenValidEventPoolIsReturned) {
    const uint32_t eventsCount{32};
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    MockArtificialEventsAllocator allocator;
    allocator.eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;
    auto createdEventPool = allocator.createEventPool(context, eventsCount);

    EXPECT_EQ(eventPool, createdEventPool);
    EXPECT_TRUE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenFailingL0EventPoolDestructionWhenTryingToDestroyEventPoolThenErrorIsPrinted) {
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    MockArtificialEventsAllocator allocator;

    Cal::Mocks::LogCaptureContext logs;
    allocator.destroyEventPool(eventPool);

    EXPECT_FALSE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenSuccessfulL0EventPoolDestructionWhenTryingToDestroyEventPoolThenNoErrorsArePrinted) {
    const uint32_t eventsCount{32};
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    MockArtificialEventsAllocator allocator;
    allocator.eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;

    auto createdEventPool = allocator.createEventPool(context, eventsCount);
    EXPECT_EQ(eventPool, createdEventPool);

    allocator.destroyEventPool(createdEventPool);
    EXPECT_TRUE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenFailingL0EventCreationWhenTryingToCreateEventThenNullptrIsReturnedAndErrorIsPrinted) {
    const uint32_t index{5};
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    MockArtificialEventsAllocator allocator;

    Cal::Mocks::LogCaptureContext logs;
    auto createdEvent = allocator.createEvent(eventPool, index);

    EXPECT_EQ(nullptr, createdEvent);
    EXPECT_FALSE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenSuccessfulL0EventCreationWhenTryingToCreateEventThenValidEventIsReturned) {
    const uint32_t eventsCount{16};
    const uint32_t index{5};

    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    MockArtificialEventsAllocator allocator;

    allocator.eventsToCreate[eventPool].resize(16);
    allocator.eventsToCreate[eventPool][5] = event;
    allocator.eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;

    auto createdEventPool = allocator.createEventPool(context, eventsCount);
    EXPECT_EQ(eventPool, createdEventPool);

    auto createdEvent = allocator.createEvent(eventPool, index);
    EXPECT_EQ(event, createdEvent);

    EXPECT_TRUE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenFailingL0EventDestructionWhenTryingToDestroyEventThenErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);

    MockArtificialEventsAllocator allocator;

    Cal::Mocks::LogCaptureContext logs;
    allocator.destroyEvent(event);

    EXPECT_FALSE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenSuccessfulL0EventDestructionWhenTryingToDestroyEventThenItIsDestroyedAndNoErrorsArePrinted) {
    const uint32_t eventsCount{64};
    const uint32_t index{5};

    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    MockArtificialEventsAllocator allocator;

    allocator.eventsToCreate[eventPool].resize(16);
    allocator.eventsToCreate[eventPool][5] = event;
    allocator.eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;

    auto createdEventPool = allocator.createEventPool(context, eventsCount);
    EXPECT_EQ(eventPool, createdEventPool);

    auto createdEvent = allocator.createEvent(eventPool, index);
    EXPECT_EQ(event, createdEvent);

    allocator.destroyEvent(event);

    EXPECT_TRUE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenFailingL0EventResetWhenTryingToResetEventThenErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);

    MockArtificialEventsAllocator allocator;

    Cal::Mocks::LogCaptureContext logs;
    allocator.resetEvent(event);

    EXPECT_FALSE(logs.empty());
}

TEST(ArtificialEventsAllocatorTest, GivenSuccessfulL0EventResetWhenTryingToResetEventThenItIsResetAndNoErrorsArePrinted) {
    const uint32_t eventsCount{64};
    const uint32_t index{5};

    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    MockArtificialEventsAllocator allocator;

    allocator.eventsToCreate[eventPool].resize(16);
    allocator.eventsToCreate[eventPool][5] = event;
    allocator.eventPoolsToCreate[context].push_back(eventPool);

    Cal::Mocks::LogCaptureContext logs;

    auto createdEventPool = allocator.createEventPool(context, eventsCount);
    EXPECT_EQ(eventPool, createdEventPool);

    auto createdEvent = allocator.createEvent(eventPool, index);
    EXPECT_EQ(event, createdEvent);

    allocator.resetEvent(event);

    EXPECT_TRUE(logs.empty());
}

} // namespace Cal::Test::LevelZero::Service
