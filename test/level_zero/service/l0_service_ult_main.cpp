/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "test/utils/cli_utils.h"
#include "test/utils/custom_event_listener.h"
#include "test/utils/signal_utils.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    auto options = parseArguments(argc, argv);

    if (int result = enableSignals(options.enableAlarm, options.enableSegv, options.enableAbrt); result != 0) {
        return result;
    }

    if (options.useCustomListener) {
        auto &listeners = ::testing::UnitTest::GetInstance()->listeners();
        auto defaultListener = listeners.default_result_printer();
        auto customEventListener = new CCustomEventListener(defaultListener);
        listeners.Release(defaultListener);
        listeners.Append(customEventListener);
    }

    return RUN_ALL_TESTS();
}
