/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/utils.h"

#include <atomic>
#include <chrono>
#include <thread>

namespace Cal {

namespace Utils {

template <typename TimeoutT, typename ReturnT, typename ContextT>
ReturnT waitForCompletionWithTimeout(ContextT ctx, std::chrono::nanoseconds timeout, ReturnT (*waitFunc)(ContextT, uint64_t),
                                     ReturnT success, ReturnT notReady) {
    using namespace std::literals::chrono_literals;
    static constexpr auto pollingThreshold = std::chrono::nanoseconds{100ms}; // poll vs waitFunc
    static constexpr auto pollWaitTime = std::chrono::nanoseconds{1ms};       // time between polling iterations

    static constexpr auto maxFirstWaitTime = std::chrono::nanoseconds{500ms};         // maximum timeout for first check with waitFunct
    static constexpr auto minFirstWaitTime = std::chrono::nanoseconds{100us};         // minimum timeout for first check with waitFunct
    static std::atomic<std::chrono::nanoseconds> adaptiveFirstWait{maxFirstWaitTime}; // adaptive timeout for first check with waitFunct

    auto increaseFirstWaitAdaptiveTimout = [&](std::chrono::nanoseconds from, std::chrono::nanoseconds to) {
        if (to > maxFirstWaitTime) {
            to = maxFirstWaitTime;
        }
        if (to < from) {
            return;
        }

        if (adaptiveFirstWait.compare_exchange_weak(from, to, std::memory_order::memory_order_relaxed, std::memory_order_relaxed)) {
            log<Verbosity::debug>("Increased first wait time from %lluns to %lluns", from.count(), to.count());
        }
    };

    auto decreaseFirstWaitAdaptiveTimout = [&](std::chrono::nanoseconds from, std::chrono::nanoseconds to) {
        if (to < minFirstWaitTime) {
            to = minFirstWaitTime;
        }
        if (to > from) {
            return;
        }

        if (adaptiveFirstWait.compare_exchange_weak(from, to, std::memory_order::memory_order_relaxed, std::memory_order_relaxed)) {
            log<Verbosity::debug>("Decreased first wait time from %lluns to %lluns", from.count(), to.count());
        }
    };

    bool endlessTimeoutMode = timeout.count() < 0;
    if (endlessTimeoutMode) {
        timeout = std::chrono::nanoseconds::max();
    }

    if (timeout < pollingThreshold) {
        // Direct wait instead of polling
        auto ret = waitFunc(ctx, std::chrono::duration_cast<TimeoutT>(timeout).count());
        if (success == ret) {
            // use provided timeout as suggested timeout
            increaseFirstWaitAdaptiveTimout(adaptiveFirstWait.load(), timeout);
        }
        return ret;
    }

    // Polling
    // 1. Direct wait for limited amount of time
    std::chrono::nanoseconds totalWaited = 0ns;
    auto firstWaitTime = endlessTimeoutMode ? adaptiveFirstWait.load() : pollingThreshold;
    auto beforeWaitFuncTimestamp = std::chrono::high_resolution_clock::now();
    auto result = waitFunc(ctx, std::chrono::duration_cast<TimeoutT>(firstWaitTime).count());
    auto afterWaitFuncTimestamp = std::chrono::high_resolution_clock::now();
    auto waitFuncTime = afterWaitFuncTimestamp - beforeWaitFuncTimestamp;
    totalWaited += waitFuncTime;
    if (result == success) {
        log<Verbosity::debug>("Wait function returned success - totalWaited %lluns", totalWaited.count());

        // Direct wait was productive - wait at least as much next time
        increaseFirstWaitAdaptiveTimout(firstWaitTime, waitFuncTime * 2);
        return success;
    }

    // Direct wait was a waste of time - wait less next time
    decreaseFirstWaitAdaptiveTimout(firstWaitTime, firstWaitTime / 4);

    // 2. Polling until timeout reached
    while (true) {
        log<Verbosity::debug>("Waiting for completion with timeout %lluns - polling timeout %lluns, totalWaited %lluns", timeout, pollWaitTime, totalWaited);
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
        std::this_thread::sleep_for(pollWaitTime);
        totalWaited += pollWaitTime;
    }
}

} // namespace Utils
} // namespace Cal
