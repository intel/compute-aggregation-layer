/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/log.h"
#include "shared/utils.h"

#include <algorithm>
#include <atomic>
#include <cctype>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

namespace Cal {

namespace Utils {

class BarrierUserPoly {
  public:
    virtual ~BarrierUserPoly();
    virtual bool alive() const = 0;
    virtual void notifyBrokenBarrier() = 0;

    static bool isAliveCallback(const BarrierUserPoly *user) { return user->alive(); };
    static void notifyBrokenBarrierCallback(BarrierUserPoly *user) { user->notifyBrokenBarrier(); };
};

template <typename BarrierUserT = BarrierUserPoly,
          bool (*IsAliveCallbackF)(const BarrierUserT *) = BarrierUserT::isAliveCallback,
          void (*NotifyBrokenBarrierCallbackF)(BarrierUserT *) = BarrierUserT::notifyBrokenBarrierCallback>
class Barrier {
  public:
    Barrier() {
    }

    virtual ~Barrier() = default;

    void reset(std::vector<BarrierUserT *> *expectedBarrierUsers, std::chrono::microseconds timeout) {
        this->expectedBarrierUsers = expectedBarrierUsers;
        this->timeout = timeout;
        this->waitIndefinitely = (timeout == std::chrono::microseconds::max());
        this->usersInBarrier = 0;
        this->barrierIsBroken = false;
        this->entry.reset();
        this->exit.reset();
    }

    bool recyclable() const {
        return (this->usersInBarrier == this->expectedBarrierUsers->size());
    }

    bool broken() const {
        return this->barrierIsBroken;
    }

    bool hitBarrier(BarrierUserT *user) {
        if (expectedBarrierUsers->size() < 2) {
            log<Verbosity::performance>("Ignoring barrier %p - only one user", this);
            return true;
        }

        if (false == IsAliveCallbackF(user)) {
            log<Verbosity::performance>("User %p is not alive, dropping barrier %p", user, this);
            this->breakBarrier();
            return false;
        }

        if (barrierIsBroken) {
            log<Verbosity::performance>("User %p tried to enter broken barrier %p", user, this);
            return false;
        }

        uint32_t userId = usersInBarrier++;
        if (userId == 0) { // lead - wait on entry, signal exit
            log<Verbosity::performance>("User %p (lead) is entering the barrier #%p", user, this);
            uint32_t waitedCount = 1; // count self
            auto timerStart = std::chrono::high_resolution_clock::now();
            while (waitedCount < expectedBarrierUsers->size()) {
                if (barrierIsBroken) {
                    log<Verbosity::performance>("User %p (lead) %d - failed to synchronize on barrier %p entry (broken barrier)", user, this);
                    return false;
                }
                if (false == areAllAlive()) {
                    log<Verbosity::performance>("User %p (lead) %d - failed to synchronize on barrier %p entry (some users are not alive)", user, this);
                    this->breakBarrier();
                    return false;
                }
                if (waitIndefinitely) {
                    entry.wait();
                    if (barrierIsBroken) {
                        continue;
                    }
                } else {
                    auto waitedUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timerStart);
                    bool overdue = waitedUs > timeout;
                    if (overdue || (false == entry.waitFor(timeout - waitedUs))) {
                        log<Verbosity::performance>("User %p (lead) %d - failed to synchronize on barrier %p entry (timeout)", user, this);
                        this->breakBarrier();
                        return false;
                    }
                }
                ++waitedCount;
            }

            if (barrierIsBroken) {
                log<Verbosity::performance>("User %p failed to synchronize on barrier %p (broken barrier)", user, this);
                return false;
            }

            log<Verbosity::performance>("%d users entered the barrier %p, lead %p is opening the exit", waitedCount + 1, this, user);
            exit.signal(waitedCount);
            return true;
        } else { // non lead - signal entry, wait on exit
            log<Verbosity::performance>("User %p is entering the barrier %p", user, this);
            entry.signal(1);
            if (waitIndefinitely) {
                exit.wait();
            } else {
                if (false == exit.waitFor(std::chrono::microseconds(timeout))) {
                    log<Verbosity::performance>("User %p failed to synchronize on barrier %p", user, this);
                    this->breakBarrier();
                    return false;
                }
            }
            if (barrierIsBroken) {
                log<Verbosity::performance>("User %p failed to synchronize on barrier %p (broken barrier)", user, this);
                return false;
            }
            log<Verbosity::performance>("User %p is exiting the barrier #%p after succesfull synchronization", user, this);
            return true;
        }
    }

  protected:
    void breakBarrier() {
        if (barrierIsBroken) {
            return;
        }
        for (auto user : *expectedBarrierUsers) {
            NotifyBrokenBarrierCallbackF(user);
        }
        exit.signal(expectedBarrierUsers->size()); // all is lost
        barrierIsBroken = true;
    }

    bool areAllAlive() {
        return std::all_of(
            expectedBarrierUsers->begin(), expectedBarrierUsers->end(), +[](const BarrierUserT *user) { return IsAliveCallbackF(user); });
    }

    std::chrono::microseconds timeout{};
    bool waitIndefinitely = false;

    Cal::Utils::CountingSemaphore entry;
    Cal::Utils::CountingSemaphore exit;
    std::vector<BarrierUserT *> *expectedBarrierUsers = nullptr;
    std::atomic_uint32_t usersInBarrier;
    std::atomic_bool barrierIsBroken;
};

} // namespace Utils

} // namespace Cal
