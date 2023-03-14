/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/api_types.h"
#include "shared/log.h"

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>

namespace Cal {
namespace Ipc {
class ClientConnectionFactory;
class Connection;
class ShmemImporter;
class MallocShmemZeroCopyManager;
} // namespace Ipc

namespace Usm {
class UsmShmemImporter;
}

namespace Rpc {
class ChannelClient;
}

namespace Icd {
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

    Cal::Ipc::ShmemImporter &getGlobalShmemImporter() const {
        return *this->globalShmemImporter;
    }

    Cal::Usm::UsmShmemImporter &getUsmShmemImporter() const {
        return *this->usmShmemImporter;
    }

    Cal::Ipc::MallocShmemZeroCopyManager &getMallocShmemZeroCopyManager() const {
        return *this->mallocShmemZeroCopyManager;
    }

    Cal::Icd::PageFaultManager &getPageFaultManager() const {
        return *this->pageFaultManager;
    }

    Cal::Ipc::Connection &getConnection() const {
        return *this->connection;
    }

    Cal::Rpc::ChannelClient &getRpcChannel() const {
        return *this->rpcChannel;
    }

    bool isZeroCopyForMallocShmemEnabled() const {
        return this->connectionTraits.isZeroCopyForMallocShmemAllowed;
    }

    const Cal::Utils::CpuInfo &getCpuInfo() const {
        return this->cpuInfo;
    }

    const Cal::Utils::AddressRange &getInitialUsmHeap() const {
        return initialUsmHeap;
    }

  protected:
    friend struct IcdGlobalsRegistryAtExitWatcher;
    void notifyAtExit() {
        std::unique_lock<std::mutex> lock(atExit.mutex);
        for (auto &callback : atExit.callbacks) {
            callback.second(callback.first);
        }
    }

    bool ensureServiceIsAvailable();
    bool ensureApiIsAvailable(ApiType api);

    void connect();
    const char *getSocketPath();

    std::unique_ptr<Cal::Ipc::ClientConnectionFactory> createConnectionFactory();

    struct {
        std::unique_ptr<Cal::Icd::Ocl::IcdOclPlatform> platform;
        std::once_flag onceFlag;
    } oclPlatform;

    struct {
        std::unique_ptr<Cal::Icd::LevelZero::IcdL0Platform> platform;
        std::once_flag onceFlag;
    } l0Platform;

    struct {
        std::once_flag onceFlag;
        bool isConnected = false;

        std::string socketPath;
        bool isZeroCopyForMallocShmemAllowed = false;
    } connectionTraits;

    std::unique_ptr<Cal::Ipc::ShmemImporter> globalShmemImporter;
    std::unique_ptr<Cal::Usm::UsmShmemImporter> usmShmemImporter;
    std::unique_ptr<Cal::Ipc::MallocShmemZeroCopyManager> mallocShmemZeroCopyManager;
    std::unique_ptr<Cal::Icd::PageFaultManager> pageFaultManager;
    std::unique_ptr<Cal::Ipc::Connection> connection;
    std::unique_ptr<Cal::Rpc::ChannelClient> rpcChannel;
    Cal::Utils::AddressRange initialUsmHeap;
    Cal::Utils::CpuInfo cpuInfo;

    bool enableCache = false;
    bool usesSharedVaForRpcChannel = false;

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
