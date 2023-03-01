/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "service/level_zero/event_to_context_tracker.h"
#include "test/mocks/log_mock.h"

#include <array>
#include <cstddef>

using Cal::Service::LevelZero::EventToContextTracker;

namespace Cal::Test::LevelZero::Service {

TEST(EventToContextTrackerTest, GivenEmptyTrackerWhenRegisteringMappingAndTryingToGetItThenRegisteredValuesAreReturned) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    EventToContextTracker tracker{};

    tracker.registerEventPoolToContextMapping(eventPool, context);
    tracker.registerEventToEventPoolMapping(event, eventPool);

    EXPECT_EQ(eventPool, tracker.getAssociatedEventPool(event));
    EXPECT_EQ(context, tracker.getAssociatedContext(event));
    EXPECT_EQ(context, tracker.getAssociatedContext(eventPool));

    EXPECT_TRUE(logs.empty());
}

TEST(EventToContextTrackerTest, GivenTrackerWhenRegisteringAndUnregisteringMappingAndGettingItThenNullptrIsReturnedAndErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    EventToContextTracker tracker{};

    {
        Cal::Mocks::LogCaptureContext logs;

        tracker.registerEventToEventPoolMapping(event, eventPool);
        EXPECT_EQ(eventPool, tracker.getAssociatedEventPool(event));

        tracker.deregisterEventMapping(event);

        EXPECT_EQ(nullptr, tracker.getAssociatedEventPool(event));
        EXPECT_FALSE(logs.empty());
    }

    {
        Cal::Mocks::LogCaptureContext logs;

        tracker.registerEventPoolToContextMapping(eventPool, context);
        EXPECT_EQ(context, tracker.getAssociatedContext(eventPool));

        tracker.deregisterEventPoolMapping(eventPool);

        EXPECT_EQ(nullptr, tracker.getAssociatedContext(eventPool));
        EXPECT_FALSE(logs.empty());
    }
}

TEST(EventToContextTrackerTest, GivenTrackerWhenRegisteringOnlyEventToEventPoolMappingAndGettingEventToContextMappingThenNullptrIsReturnedAndErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    Cal::Mocks::LogCaptureContext logs;
    EventToContextTracker tracker{};

    tracker.registerEventToEventPoolMapping(event, eventPool);
    EXPECT_EQ(eventPool, tracker.getAssociatedEventPool(event));

    EXPECT_EQ(nullptr, tracker.getAssociatedContext(event));
    EXPECT_FALSE(logs.empty());
}

TEST(EventToContextTrackerTest, GivenTrackerWhenRegisteringOnlyEventPoolToContextMappingAndGettingEventToContextMappingThenNullptrIsReturnedAndErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    EventToContextTracker tracker{};

    tracker.registerEventPoolToContextMapping(eventPool, context);
    EXPECT_EQ(context, tracker.getAssociatedContext(eventPool));

    EXPECT_EQ(nullptr, tracker.getAssociatedContext(event));
    EXPECT_FALSE(logs.empty());
}

TEST(EventToContextTrackerTest, GivenEmptyTrackerWhenTryingToGetAssociatedMappingsThenNullptrIsReturnedAndErrorIsPrinted) {
    auto event = reinterpret_cast<ze_event_handle_t>(0x1234);
    auto eventPool = reinterpret_cast<ze_event_pool_handle_t>(0x2345);

    EventToContextTracker tracker{};

    {
        Cal::Mocks::LogCaptureContext logs;

        EXPECT_EQ(nullptr, tracker.getAssociatedEventPool(event));
        EXPECT_FALSE(logs.empty());
    }

    {
        Cal::Mocks::LogCaptureContext logs;

        EXPECT_EQ(nullptr, tracker.getAssociatedContext(event));
        EXPECT_FALSE(logs.empty());
    }

    {
        Cal::Mocks::LogCaptureContext logs;

        EXPECT_EQ(nullptr, tracker.getAssociatedContext(eventPool));
        EXPECT_FALSE(logs.empty());
    }
}

TEST(EventToContextTrackerTest, GivenRegisteredMappingsWhenTryingToGetNonregisteredOneThenNullptrIsReturnedAndErrorIsPrinted) {
    // 0. Given registered mappings.
    EventToContextTracker tracker{};

    constexpr size_t mappingsCount{16u};

    std::array<ze_event_handle_t, mappingsCount> events{};
    std::array<ze_event_pool_handle_t, mappingsCount> eventPools{};
    std::array<ze_context_handle_t, mappingsCount> contexts{};

    for (auto i = 0u; i < mappingsCount; ++i) {
        events[i] = reinterpret_cast<ze_event_handle_t>(0x1000 + 8 * i);
        eventPools[i] = reinterpret_cast<ze_event_pool_handle_t>(0x2000 + 8 * i);
        contexts[i] = reinterpret_cast<ze_context_handle_t>(0x3000 + 8 * i);

        tracker.registerEventToEventPoolMapping(events[i], eventPools[i]);
        tracker.registerEventPoolToContextMapping(eventPools[i], contexts[i]);
    }

    for (auto i = 0u; i < mappingsCount; ++i) {
        EXPECT_EQ(contexts[i], tracker.getAssociatedContext(events[i]));
    }

    // 1. When nonregistered is queried.
    auto nonregisteredEvent = reinterpret_cast<ze_event_handle_t>(0x1000 + 8 * (mappingsCount + 1));

    Cal::Mocks::LogCaptureContext logs;
    auto mappedContext = tracker.getAssociatedContext(nonregisteredEvent);

    // 2. Then nullptr is returned and error is printed.
    EXPECT_EQ(nullptr, mappedContext);
    EXPECT_FALSE(logs.empty());
}

} // namespace Cal::Test::LevelZero::Service
