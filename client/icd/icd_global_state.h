/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/client_connection.h"
#include "shared/api_types.h"
#include "shared/log.h"

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>

namespace Cal::Client::Icd {

class PageFaultManager;

namespace Ocl {
class IcdOclPlatform;
}

namespace LevelZero {
class IcdL0Platform;
}

struct IcdGlobalsRegistryAtExitWatcher {
    ~IcdGlobalsRegistryAtExitWatcher();
};
extern IcdGlobalsRegistryAtExitWatcher icdGlobalsRegistryAtExitWatcher;

class IcdGlobalState : public Cal::Client::ClientConnection {
  public:
    struct AtExitNotification {
        using KeyT = const void *;
        using CallbackT = std::function<void(KeyT key)>;
    };

    void registerAtExit(AtExitNotification::KeyT key, AtExitNotification::CallbackT &&callback) {
        std::unique_lock<std::mutex> lock(atExit.mutex);
        atExit.callbacks[key] = std::move(callback);
    }

    void unregisterAtExit(AtExitNotification::KeyT key) {
        std::unique_lock<std::mutex> lock(atExit.mutex);
        auto it = atExit.callbacks.find(key);
        if (it == atExit.callbacks.end()) {
            log<Verbosity::error>("Trying to unregister callback for unknown key : %p", key);
            return;
        }
        atExit.callbacks.erase(it);
    }

    void connect() override;

    IcdGlobalState();
    Cal::Client::Icd::Ocl::IcdOclPlatform *getOclPlatform();
    Cal::Client::Icd::LevelZero::IcdL0Platform *getL0Platform();
    bool isCacheEnabled() { return this->enableCache; };
    ~IcdGlobalState();

    Cal::Client::Icd::PageFaultManager &getPageFaultManager() const {
        return *this->pageFaultManager;
    }

  protected:
    friend struct IcdGlobalsRegistryAtExitWatcher;
    void notifyAtExit() {
        std::unique_lock<std::mutex> lock(atExit.mutex);
        for (auto &callback : atExit.callbacks) {
            callback.second(callback.first);
        }
    }

    bool ensureApiIsAvailable(ApiType api);

    struct {
        std::unique_ptr<Cal::Client::Icd::Ocl::IcdOclPlatform> platform;
        std::once_flag onceFlag;
    } oclPlatform;

    struct {
        std::unique_ptr<Cal::Client::Icd::LevelZero::IcdL0Platform> platform;
        std::once_flag onceFlag;
    } l0Platform;

    bool enableCache = false;
    std::unique_ptr<Cal::Client::Icd::PageFaultManager> pageFaultManager;

    struct AtExit {
        std::mutex mutex;
        std::unordered_map<AtExitNotification::KeyT, AtExitNotification::CallbackT> callbacks;
    } atExit;
};

extern IcdGlobalState &icdGlobalState;

inline IcdGlobalsRegistryAtExitWatcher::~IcdGlobalsRegistryAtExitWatcher() {
    icdGlobalState.notifyAtExit();
}

} // namespace Cal::Client::Icd
