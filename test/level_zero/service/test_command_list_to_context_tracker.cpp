/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "service/level_zero/command_list_to_context_tracker.h"
#include "test/mocks/log_mock.h"

#include <array>
#include <cstddef>

using Cal::Service::LevelZero::CommandListToContextTracker;

namespace Cal::Test::LevelZero::Service {

TEST(CommandListToContextTrackerTest, GivenEmptyTrackerWhenRegisteringMappingAndTryingToGetItThenRegisteredValuesAreReturned) {
    auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    Cal::Mocks::LogCaptureContext logs;
    CommandListToContextTracker tracker{};

    tracker.registerCommandListToContextMapping(commandList, context);

    EXPECT_EQ(context, tracker.getAssociatedContext(commandList));
    EXPECT_TRUE(logs.empty());
}

TEST(CommandListToContextTrackerTest, GivenTrackerWhenRegisteringAndUnregisteringMappingAndGettingItThenNullptrIsReturnedAndErrorIsPrinted) {
    auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x2345);
    auto context = reinterpret_cast<ze_context_handle_t>(0x3456);

    CommandListToContextTracker tracker{};
    Cal::Mocks::LogCaptureContext logs;

    tracker.registerCommandListToContextMapping(commandList, context);
    EXPECT_EQ(context, tracker.getAssociatedContext(commandList));

    tracker.deregisterCommandListMapping(commandList);

    EXPECT_EQ(nullptr, tracker.getAssociatedContext(commandList));
    EXPECT_FALSE(logs.empty());
}

TEST(CommandListToContextTrackerTest, GivenEmptyTrackerWhenTryingToGetAssociatedMappingsThenNullptrIsReturnedAndErrorIsPrinted) {
    auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x2345);

    CommandListToContextTracker tracker{};
    Cal::Mocks::LogCaptureContext logs;

    EXPECT_EQ(nullptr, tracker.getAssociatedContext(commandList));
}

TEST(CommandListToContextTrackerTest, GivenRegisteredMappingsWhenTryingToGetNonregisteredOneThenNullptrIsReturnedAndErrorIsPrinted) {
    // 0. Given registered mappings.
    CommandListToContextTracker tracker{};

    constexpr size_t mappingsCount{16u};

    std::array<ze_command_list_handle_t, mappingsCount> commandLists{};
    std::array<ze_context_handle_t, mappingsCount> contexts{};

    for (auto i = 0u; i < mappingsCount; ++i) {
        commandLists[i] = reinterpret_cast<ze_command_list_handle_t>(0x2000 + 8 * i);
        contexts[i] = reinterpret_cast<ze_context_handle_t>(0x3000 + 8 * i);

        tracker.registerCommandListToContextMapping(commandLists[i], contexts[i]);
    }

    for (auto i = 0u; i < mappingsCount; ++i) {
        EXPECT_EQ(contexts[i], tracker.getAssociatedContext(commandLists[i]));
    }

    // 1. When nonregistered is queried.
    auto nonregisteredCommandList = reinterpret_cast<ze_command_list_handle_t>(0x1111);

    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(nullptr, tracker.getAssociatedContext(nonregisteredCommandList));
    EXPECT_FALSE(logs.empty());
}

} // namespace Cal::Test::LevelZero::Service
