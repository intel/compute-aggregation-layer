/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/log.h"

#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Cal {
namespace Ipc {
class ShmemImporter;
class MallocShmemZeroCopyManager;
} // namespace Ipc

namespace Icd {

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

class IcdGlobalState final {
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

    IcdGlobalState();
    Cal::Icd::Ocl::IcdOclPlatform *getOclPlatform();
    Cal::Icd::LevelZero::IcdL0Platform *getL0Platform();
    bool isCacheEnabled() { return this->enableCache; };
    ~IcdGlobalState();

    struct CacheBase {};

    template <typename ArgsT, typename CapturesT>
    struct Cache : public CacheBase {
        struct Pair {
            CapturesT *getCaptures() {
                return std::launder(reinterpret_cast<CapturesT *>(capturesMem.get()));
            }

            ArgsT args;
            std::unique_ptr<char[]> capturesMem;
        };
        std::vector<Pair> cache;

        auto find(ArgsT &args) {
            return std::find_if(cache.begin(), cache.end(), [&args](Pair &el) {
                return args.shallowCompareEquals(el.args);
            });
        }
    };

    template <typename CommandT>
    bool isCommandReturnValueCached(CommandT &command) {
        std::lock_guard<std::mutex> lock(this->cacheMutex);
        using CommandCacheT = Cache<typename CommandT::Args, typename CommandT::Captures>;

        if (!this->enableCache) {
            return false;
        }

        if (this->cache.size() < CommandT::messageSubtype + 1) {
            cache.resize(CommandT::messageSubtype + 1);
        }

        if (this->cache[CommandT::messageSubtype].get() == nullptr) {
            this->cache[CommandT::messageSubtype] = std::make_unique<CommandCacheT>();
            return false;
        }

        auto commandCache = static_cast<CommandCacheT *>(this->cache[CommandT::messageSubtype].get());
        auto cachedCommandRet = commandCache->find(command.args);
        if (cachedCommandRet != commandCache->cache.end()) {
            if (!command.captures.assignFrom(*cachedCommandRet->getCaptures())) {
                log<Verbosity::bloat>("Tried to assign cached value, which has different dynamic memory size!");
                return false;
            }

            return true;
        }

        return false;
    }

    template <typename CommandT>
    void cacheReturnValue(CommandT &command) {
        std::lock_guard<std::mutex> lock(this->cacheMutex);
        using CommandCacheT = Cache<typename CommandT::Args, typename CommandT::Captures>;

        if (!this->enableCache) {
            return;
        }

        auto commandCache = static_cast<CommandCacheT *>(this->cache[CommandT::messageSubtype].get());
        commandCache->cache.push_back({command.args, command.captures.clone()});
    }

  protected:
    friend struct IcdGlobalsRegistryAtExitWatcher;
    void notifyAtExit() {
        std::unique_lock<std::mutex> lock(atExit.mutex);
        for (auto &callback : atExit.callbacks) {
            callback.second(callback.first);
        }
    }

    struct {
        std::unique_ptr<Cal::Icd::Ocl::IcdOclPlatform> platform;
        std::once_flag onceFlag;
    } oclPlatform;
    struct {
        std::unique_ptr<Cal::Icd::LevelZero::IcdL0Platform> platform;
        std::once_flag onceFlag;
    } l0Platform;
    std::unique_ptr<Cal::Ipc::ShmemImporter> shmemManager;
    std::unique_ptr<Cal::Ipc::MallocShmemZeroCopyManager> mallocShmemZeroCopyManager;

    std::mutex cacheMutex;
    std::vector<std::unique_ptr<IcdGlobalState::CacheBase>> cache;
    bool enableCache = false;

    struct AtExit {
        std::mutex mutex;
        std::unordered_map<AtExitNotification::KeyT, AtExitNotification::CallbackT> callbacks;
    } atExit;
};

extern IcdGlobalState &icdGlobalState;

inline IcdGlobalsRegistryAtExitWatcher::~IcdGlobalsRegistryAtExitWatcher() {
    icdGlobalState.notifyAtExit();
}

} // namespace Icd

} // namespace Cal
