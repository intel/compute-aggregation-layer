/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/utils.h"

#include <chrono>
#include <thread>

namespace Cal {

namespace Utils {

template <typename TimeoutT, typename ReturnT, typename ContextT>
ReturnT waitForCompletionWithTimeout(ContextT ctx, std::chrono::nanoseconds timeout, ReturnT (*waitFunc)(ContextT, uint64_t),
                                     ReturnT success, ReturnT notReady) {
    using namespace std::literals::chrono_literals;
    std::chrono::nanoseconds pollingThreshold = 100ms;
    bool endlessTimeoutMode = timeout.count() < 0;
    if (endlessTimeoutMode) {
        timeout = std::chrono::nanoseconds::max();
    }

    if (timeout < pollingThreshold) {
        return waitFunc(ctx, std::chrono::duration_cast<TimeoutT>(timeout).count());
    }

    std::chrono::nanoseconds totalWaited = 0ns;
    auto result = waitFunc(ctx, std::chrono::duration_cast<TimeoutT>(pollingThreshold).count());
    totalWaited += pollingThreshold;
    if (result == success) {
        log<Verbosity::debug>("Wait function returned success - totalWaited %lluns", totalWaited.count());
        return success;
    }

    while (true) {
        log<Verbosity::debug>("Waiting for completion with timeout %lluns - polling timeout %lluns, totalWaited %lluns", timeout, pollingThreshold, totalWaited);
        auto result = waitFunc(ctx, 0);
        if (result == success) {
            log<Verbosity::debug>("Wait function returned success - totalWaited %lluns", totalWaited.count());
            return success;
        }
        if (result != notReady) {
            log<Verbosity::debug>("Wait function failed with error code %d", static_cast<int>(result));
            return result;
        }
        if ((false == endlessTimeoutMode) && (totalWaited >= timeout)) {
            log<Verbosity::debug>("Wait for completion with timeout has timed out - totalWaited %lluns >= timeout %lluns", totalWaited.count(), timeout.count());
            return notReady;
        }
        std::this_thread::sleep_for(pollingThreshold);
        totalWaited += pollingThreshold;
    }
}

} // namespace Utils
} // namespace Cal
