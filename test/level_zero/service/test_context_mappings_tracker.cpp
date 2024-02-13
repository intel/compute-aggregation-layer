/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "service/level_zero/context_mappings_tracker.h"
#include "test/mocks/log_mock.h"

#include <array>
#include <cstddef>

using Cal::Service::LevelZero::ContextMappingsTracker;

namespace Cal::Test::LevelZero::Service {

TEST(ContextMappingsTrackerTest, GivenEmptyTrackerWhenRegisteringMappingAndTryingToGetItThenRegisteredValuesAreReturned) {
    auto metricStreamer = reinterpret_cast<zet_metric_streamer_handle_t>(0x1234);
    auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    ContextMappingsTracker tracker{};

    tracker.registerMetricStreamerToContextMapping(metricStreamer, context);
    tracker.registerCommandListToContextMapping(commandList, context);

    EXPECT_EQ(context, tracker.getAssociatedContext(commandList));
    EXPECT_TRUE(logs.empty());
}

TEST(ContextMappingsTrackerTest, GivenTrackerWhenRegisteringAndUnregisteringMappingAndGettingItThenNullptrIsReturnedAndErrorIsPrinted) {
    auto metricStreamer = reinterpret_cast<zet_metric_streamer_handle_t>(0x1234);
    auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    ContextMappingsTracker tracker{};
    Cal::Mocks::LogCaptureContext logs;

    tracker.registerMetricStreamerToContextMapping(metricStreamer, context);
    EXPECT_EQ(context, tracker.getAssociatedContext(metricStreamer));
    tracker.registerCommandListToContextMapping(commandList, context);
    EXPECT_EQ(context, tracker.getAssociatedContext(commandList));

    tracker.deregisterMetricStreamerMapping(metricStreamer);
    tracker.deregisterCommandListMapping(commandList);

    EXPECT_EQ(nullptr, tracker.getAssociatedContext(metricStreamer));
    EXPECT_EQ(nullptr, tracker.getAssociatedContext(commandList));
    EXPECT_FALSE(logs.empty());
}

TEST(ContextMappingsTrackerTest, GivenEmptyTrackerWhenTryingToGetAssociatedMappingsThenNullptrIsReturnedAndErrorIsPrinted) {
    auto metricStreamer = reinterpret_cast<zet_metric_streamer_handle_t>(0x1234);
    auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x2345);

    ContextMappingsTracker tracker{};
    Cal::Mocks::LogCaptureContext logs;

    EXPECT_EQ(nullptr, tracker.getAssociatedContext(metricStreamer));
    EXPECT_EQ(nullptr, tracker.getAssociatedContext(commandList));
}

TEST(ContextMappingsTrackerTest, GivenRegisteredMappingsWhenTryingToGetNonregisteredOneThenNullptrIsReturnedAndErrorIsPrinted) {
    // 0. Given registered mappings.
    ContextMappingsTracker tracker{};

    constexpr size_t mappingsCount{16u};

    std::array<ze_command_list_handle_t, mappingsCount> commandLists{};
    std::array<zet_metric_streamer_handle_t, mappingsCount> metricStreamers{};
    std::array<ze_context_handle_t, mappingsCount> contexts{};

    for (auto i = 0u; i < mappingsCount; ++i) {
        commandLists[i] = reinterpret_cast<ze_command_list_handle_t>(0x3000 + 8 * i);
        metricStreamers[i] = reinterpret_cast<zet_metric_streamer_handle_t>(0x4000 + 8 * i);
        contexts[i] = reinterpret_cast<ze_context_handle_t>(0x5000 + 8 * i);

        tracker.registerCommandListToContextMapping(commandLists[i], contexts[i]);
        tracker.registerMetricStreamerToContextMapping(metricStreamers[i], contexts[i]);
    }

    for (auto i = 0u; i < mappingsCount; ++i) {
        EXPECT_EQ(contexts[i], tracker.getAssociatedContext(commandLists[i]));
        EXPECT_EQ(contexts[i], tracker.getAssociatedContext(metricStreamers[i]));
    }

    // 1. When nonregistered is queried.
    auto nonregisteredCommandList = reinterpret_cast<ze_command_list_handle_t>(0x1111);
    auto nonregisteredMetricStreamer = reinterpret_cast<zet_metric_streamer_handle_t>(0x2222);

    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(nullptr, tracker.getAssociatedContext(nonregisteredCommandList));
    EXPECT_FALSE(logs.empty());
    logs.clear();
    EXPECT_EQ(nullptr, tracker.getAssociatedContext(nonregisteredMetricStreamer));
    EXPECT_FALSE(logs.empty());
}

} // namespace Cal::Test::LevelZero::Service
