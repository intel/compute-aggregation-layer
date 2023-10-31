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
} // namespace Ipc

namespace Usm {
class UsmShmemImporter;
}

namespace Rpc {
class ChannelClient;
}

namespace Client {

namespace MallocOverride {
class MallocShmemExporter;
}

class ClientConnection {
  public:
    ClientConnection();
    virtual ~ClientConnection();

    Cal::Ipc::ShmemImporter &getGlobalShmemImporter() const {
        return *this->globalShmemImporter;
    }

    Cal::Usm::UsmShmemImporter &getUsmShmemImporter() const {
        return *this->usmShmemImporter;
    }

    Cal::Client::MallocOverride::MallocShmemExporter &getMallocShmemExporter() const {
        return *this->mallocShmemExporter;
    }

    Cal::Ipc::Connection &getConnection() const {
        return *this->connection;
    }

    Cal::Rpc::ChannelClient &getRpcChannel() const {
        return *this->rpcChannel;
    }

    const Cal::Utils::CpuInfo &getCpuInfo() const {
        return this->cpuInfo;
    }

    const Cal::Utils::AddressRange &getInitialUsmHeap() const {
        return initialUsmHeap;
    }

  protected:
    bool ensureServiceIsAvailable();
    bool ensureApiIsAvailable(ApiType api);

    virtual void connect();
    const char *getSocketPath();

    std::unique_ptr<Cal::Ipc::ClientConnectionFactory> createConnectionFactory();

    struct {
        std::once_flag onceFlag;
        bool isConnected = false;

        std::string socketPath;
        bool isZeroCopyForMallocShmemAllowed = false;
    } connectionTraits;

    std::unique_ptr<Cal::Ipc::ShmemImporter> globalShmemImporter;
    std::unique_ptr<Cal::Usm::UsmShmemImporter> usmShmemImporter;
    std::unique_ptr<Cal::Client::MallocOverride::MallocShmemExporter> mallocShmemExporter;
    std::unique_ptr<Cal::Ipc::Connection> connection;
    std::unique_ptr<Cal::Rpc::ChannelClient> rpcChannel;
    Cal::Utils::AddressRange initialUsmHeap;
    Cal::Utils::CpuInfo cpuInfo;

    bool usesSharedVaForRpcChannel = false;
};

} // namespace Client

} // namespace Cal
