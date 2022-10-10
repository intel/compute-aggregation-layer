/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "cal.h"
#include "level_zero/ze_api.h"
#include "service/cochoreographer.h"
#include "shared/control_messages.h"
#include "shared/ipc.h"
#include "shared/log.h"
#include "shared/ocl_fat_def.h"
#include "shared/rpc.h"
#include "shared/shmem.h"
#include "shared/usm.h"
#include "shared/utils.h"

#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Cal {

namespace Service {

struct ServiceConfig {
    struct RunnerConfig {
        std::string command;
        std::vector<const char *> args;
    };

    std::optional<RunnerConfig> runner;

    struct ListenerConfig {
        ListenerConfig() {
            socketPath = Utils::getPathForTempFiles();
        }
        std::string socketPath;
    } listener;
};

namespace Apis {

static const char *intelGpuPlatformName = "Intel.*Graphics";

namespace Ocl {

extern cl_platform_id globalOclPlatform;
std::vector<std::string> getListOfUnimplementedFunctionNames();

class OclSharedObjects {
  public:
    bool init();

    cl_platform_id getIntelGpuPlatform() const {
        return intelGpuPlatform;
    }

  protected:
    cl_platform_id getPlatformByName(const char *regex);

    cl_platform_id intelGpuPlatform;
    std::vector<cl_device_id> devices;
};

void *getExtensionFuncAddress(const char *funcname);

} // namespace Ocl

namespace LevelZero {

class LevelZeroSharedObjects {
  public:
    bool init();

    ze_driver_handle_t getIntelGpuDriver() const {
        return intelGpuDriver;
    }

    ze_result_t getZeInitReturnValue() const {
        return zeInitReturnValue;
    }

  private:
    ze_driver_handle_t getDriverByName(const char *regex);
    std::optional<std::vector<ze_driver_handle_t>> getDrivers();
    std::optional<std::vector<ze_device_handle_t>> getDevices(ze_driver_handle_t driverHandle);

    ze_result_t zeInitReturnValue{};
    ze_driver_handle_t intelGpuDriver{};
};

} // namespace LevelZero

} // namespace Apis

class ClientContext {
  public:
    int32_t mutexIndex = -1;
    int32_t subDeviceIndex = 0u;
    bool isPersistentMode;

    struct ChoreographyAssignment {
        ISpectacle *spectacle = nullptr;
        IMember *member = nullptr;
    };

    ClientContext(bool isPersistentMode) : isPersistentMode(isPersistentMode) {}

    std::unique_lock<std::mutex> lock() {
        return std::unique_lock<std::mutex>(criticalSection);
    }

    void registerShmem(const Cal::Ipc::Shmem &shmem) {
        shmemMap[shmem.id] = shmem;
    }

    void registerRpcChannel(std::future<void> worker, std::unique_ptr<Cal::Rpc::ChannelServer> channel) {
        rpcChannels.push_back(std::make_pair(std::move(worker), std::move(channel)));
    }

    Cal::Ipc::Shmem getShmemById(int id) {
        auto it = shmemMap.find(id);
        if (it == shmemMap.end()) {
            log<Verbosity::debug>("Asked for unknown shmem id %d (this context knows %zu shmems)", id, shmemMap.size());
            return {};
        }
        return it->second;
    }

    void cleanup(Cal::Ipc::ShmemAllocator &shmemManager) {
        isStopping = true;
        log<Verbosity::debug>("Performing client RPC channels cleanup (num channels : %zu)", rpcChannels.size());
        for (auto &rpcChannel : rpcChannels) {
            rpcChannel.second->stop();
            rpcChannel.first.wait();
        }
        rpcChannels.clear();

        log<Verbosity::debug>("Performing USM shared/host allocations cleanup (num allocations leaked by client : %zu)", usmSharedHostMap.size());
        std::vector<Cal::Ipc::Shmem> usmShmemToRelease;
        for (const auto &alloc : usmSharedHostMap) {
            if (alloc.second.gpuDestructor) {
                alloc.second.gpuDestructor(alloc.second.ctx, alloc.second.ptr);
            }
            Cal::Usm::resetUsmCpuRange(alloc.second.ptr, alloc.second.alignedSize);
            usmShmemToRelease.push_back(alloc.second.shmem);
        }
        usmSharedHostMap.clear();

        log<Verbosity::debug>("Performing USM heaps cleanup (num heaps : %zu)", usmHeaps.size());
        for (const auto &heap : usmHeaps) {
            if (-1 == Cal::Sys::munmap(heap.getRange().base(), heap.getRange().size())) {
                log<Verbosity::error>("Failed to munamp USM heap (base : %p, size : %zu)", heap.getRange().base(), heap.getRange().size());
            }
        }

        log<Verbosity::debug>("Performing client shmem cleanup (num allocs : %zu)", shmemMap.size());
        {
            auto shmemManagerLock = shmemManager.lock();
            for (const auto shmemIt : shmemMap) {
                shmemManager.release(shmemIt.second);
            }
            for (auto &shmem : usmShmemToRelease) {
                shmemManager.release(shmem);
            }
        }
        shmemMap.clear();
        usmShmemToRelease.clear();

        l0SpecificCleanup();
    }

    void l0SpecificCleanup();

    bool isClientStopping() {
        return isStopping;
    }

    void addUsmHeap(const Cal::Utils::AddressRange &newRange) {
        usmHeaps.push_back({newRange});
    }

    std::vector<Cal::Utils::Heap> &getUsmHeaps() {
        return usmHeaps;
    }

    void addUsmSharedHostAlloc(void *ctx, void *ptr, size_t alignedSize, Cal::Ipc::Shmem shmem, void (*gpuDestructor)(void *ctx, void *ptr)) {
        usmSharedHostMap[ptr] = Cal::Usm::UsmSharedHostAlloc{ctx, ptr, alignedSize, shmem, gpuDestructor};
    }

    void reapUsmSharedHostAlloc(void *ptr, Cal::Ipc::ShmemAllocator &shmemManager, bool callGpuDestructor = true) {
        auto it = usmSharedHostMap.find(ptr);
        if (usmSharedHostMap.end() == it) {
            log<Verbosity::error>("Asked to reap an unknown pointer %p given as USM shared/host allocation", ptr);
            return;
        }
        auto &alloc = it->second;
        if (callGpuDestructor && alloc.gpuDestructor) {
            alloc.gpuDestructor(alloc.ctx, alloc.ptr);
        }
        Cal::Usm::resetUsmCpuRange(alloc.ptr, alloc.alignedSize);
        auto shmemManagerLock = shmemManager.lock();
        shmemManager.release(alloc.shmem);
        usmSharedHostMap.erase(it);
    }

    void assignToSpectacle(IMember *assignment) {
        spectacleAssignment = assignment;
    }

    IMember *getSpectacleAssignment() {
        return spectacleAssignment;
    }

    Cal::Ipc::MemoryBlocksManager &getMemoryBlocksManager() {
        return memoryBlocksManager;
    }

    void setMallocShmemZeroCopyHandler(std::unique_ptr<Cal::Ipc::MallocShmemZeroCopyManager::MallocShmemZeroCopyImportHandler> handler) {
        mallocShmemZeroCopyHandler = std::move(handler);
    }

    Cal::Ipc::MallocShmemZeroCopyManager::MallocShmemZeroCopyImportHandler *getMallocShmemZeroCopyHandler() const {
        return mallocShmemZeroCopyHandler.get();
    }

    template <typename HandleT>
    void trackAllocatedResource(HandleT handle) {
        if (isPersistentMode) {
            trackAllocatedResource(handle, getTracking<HandleT>());
        }
    }

    template <typename HandleT>
    void removeResourceTracking(HandleT handle) {
        if (isPersistentMode) {
            removeResourceTracking(handle, getTracking<HandleT>());
        }
    }

  protected:
    template <typename HandleT>
    std::unordered_set<HandleT> &getTracking() {
        if constexpr (std::is_same_v<HandleT, ze_context_handle_t>) {
            return l0ContextsTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_command_queue_handle_t>) {
            return l0CommandQueuesTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_command_list_handle_t>) {
            return l0CommandListsTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_module_handle_t>) {
            return l0ModulesTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_module_build_log_handle_t>) {
            return l0ModuleBuildLogsTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_kernel_handle_t>) {
            return l0KernelsTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_event_handle_t>) {
            return l0EventsTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_event_pool_handle_t>) {
            return l0EventPoolsTracking;
        } else if constexpr (std::is_same_v<HandleT, ze_fence_handle_t>) {
            return l0FencesTracking;
        } else {
            struct AlwaysFalse;
            constexpr bool alwaysFalse = std::is_same_v<HandleT, AlwaysFalse>;
            static_assert(alwaysFalse, "Please add specialization for the new type!");
        }
    }

    template <typename HandleT>
    void trackAllocatedResource(HandleT handle, std::unordered_set<HandleT> &tracking) {
        if (handle) {
            tracking.insert(handle);
        }
    }

    template <typename HandleT>
    void removeResourceTracking(HandleT handle, std::unordered_set<HandleT> &tracking) {
        if (!handle) {
            return;
        }

        const auto it = tracking.find(handle);
        if (it != tracking.end()) {
            tracking.erase(it);
        }
    }

    std::atomic_bool isStopping = false;
    std::mutex criticalSection;
    std::vector<Cal::Utils::Heap> usmHeaps;
    std::unordered_map<int, Cal::Ipc::Shmem> shmemMap;
    std::unordered_map<void *, Cal::Usm::UsmSharedHostAlloc> usmSharedHostMap;
    std::vector<std::pair<std::future<void>, std::unique_ptr<Cal::Rpc::ChannelServer>>> rpcChannels;
    std::unique_ptr<Cal::Ipc::MallocShmemZeroCopyManager::MallocShmemZeroCopyImportHandler> mallocShmemZeroCopyHandler;

    IMember *spectacleAssignment = nullptr;

    std::unordered_set<ze_context_handle_t> l0ContextsTracking{};
    std::unordered_set<ze_command_queue_handle_t> l0CommandQueuesTracking{};
    std::unordered_set<ze_command_list_handle_t> l0CommandListsTracking{};
    std::unordered_set<ze_module_handle_t> l0ModulesTracking{};
    std::unordered_set<ze_module_build_log_handle_t> l0ModuleBuildLogsTracking{};
    std::unordered_set<ze_kernel_handle_t> l0KernelsTracking{};
    std::unordered_set<ze_event_handle_t> l0EventsTracking{};
    std::unordered_set<ze_event_pool_handle_t> l0EventPoolsTracking{};
    std::unordered_set<ze_fence_handle_t> l0FencesTracking{};

    Cal::Ipc::MemoryBlocksManager memoryBlocksManager{};
};

class Provider {
  public:
    using RpcHandler = bool (*)(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize);
    using RpcSubtypeHandlers = std::vector<RpcHandler>;
    static constexpr size_t defaultUsmAddressRangeSizePerClient = 16 * Cal::Utils::GB;
    static constexpr int32_t staticDefaultRpcMessageChannelSizeMB = 256;

    enum ErrorCode : int {
        Success = 0,
        FailedToRunSubprocess = 1,
    };

    Provider(std::unique_ptr<ChoreographyLibrary> knownChoreographies, ServiceConfig &&serviceConfig);

    int run(bool isPersistentMode) {
        if (this->isRunning) {
            log<Verbosity::critical>("Service is already running");
            return -1;
        }
        this->isRunning = true;
        log<Verbosity::info>("Starting Compute Aggregation Layer service from PID : %d", getpid());
        this->config.init();
        this->mallocShmemZeroCopyManager.loadLibrary();
        if (this->mallocShmemZeroCopyManager.isAvailable()) {
            strncpy(this->config.mallocShmemLibraryPath, this->mallocShmemZeroCopyManager.getLibrarySoPath().c_str(), sizeof(this->config.mallocShmemLibraryPath));
            this->config.mallocShmemLibraryPath[sizeof(this->config.mallocShmemLibraryPath) - 1] = '\0';
        }

        std::vector<std::future<void>> clients;
        log<Verbosity::info>("Initializing OCL");
        systemInfo.availableApis.ocl = sharedObjects.ocl.init();
        if (false == systemInfo.availableApis.ocl) {
            log<Verbosity::info>("OpenCL API is not available in the system");
        }

        log<Verbosity::info>("Initializing L0");
        systemInfo.availableApis.l0 = sharedObjects.l0.init();
        if (false == systemInfo.availableApis.l0) {
            log<Verbosity::info>("Level Zero API is not available in the system");
        }

        if (systemInfo.availableApis.none()) {
            log<Verbosity::error>("None of supported APIs is available in the system. Shutting down.");
            return -1;
        }

        auto cpuInfoOpt = Cal::Utils::CpuInfo::read();
        if (cpuInfoOpt) {
            this->systemInfo.cpuInfo = cpuInfoOpt.value();
            log<Verbosity::debug>("Cpu virtual address bits : %d", this->systemInfo.cpuInfo.virtual_);
        } else {
            log<Verbosity::error>("Could note information about the CPU virtual address bits - will have impact on USM device memory");
        }

        listener = createConnectionListener();
        if (nullptr == listener) {
            log<Verbosity::critical>("Failed to create connection listener");
            return -1;
        }
        log<Verbosity::debug>("Starting listening");
        if (0 != listener->listen(serviceConfig.listener.socketPath.c_str())) {
            log<Verbosity::critical>("Failed to start connection listener");
            return -1;
        }
        this->runInLoop = true;
        if (this->serviceConfig.runner.has_value()) {
            if (false == this->runCommand(this->serviceConfig.runner.value())) {
                return FailedToRunSubprocess;
            }
        }
        while (this->runInLoop) {
            log<Verbosity::debug>("Waiting for new connection");
            auto newConnection = listener->accept();
            if ((false == this->runInLoop) && (nullptr == newConnection)) {
                break;
            }
            log<Verbosity::info>("New connection detected");
            if (nullptr == newConnection) {
                log<Verbosity::error>("Newly detected connection is broken - skipping");
                continue;
            }
            log<Verbosity::debug>("Spawning thread for new client (number of asynchronous client threads : %d)", static_cast<uint32_t>(clients.size() + 1));
            clients.push_back(std::async(std::launch::async, Provider::serviceSingleClient, std::move(newConnection), std::ref(*this), isPersistentMode));
        }
        listener->close();
        this->isStopping = true;
        log<Verbosity::info>("Stopped Compute Aggregation Layer service");
        log<Verbosity::debug>("Joining all worker threads");
        for (auto &c : clients) {
            c.wait();
        }
        return Success;
    }

    bool isServiceStopping() {
        return isStopping;
    }

    const Cal::Messages::RespHandshake &getConfig() const {
        return config;
    }

    Cal::Ipc::ShmemAllocator &getShmemManager() {
        return shmemManager;
    }

    Cal::Service::Apis::Ocl::OclSharedObjects &getOclSharedObjects() {
        return sharedObjects.ocl;
    }

    Cal::Service::Apis::LevelZero::LevelZeroSharedObjects &getL0SharedObjects() {
        return sharedObjects.l0;
    }

    const Cal::Utils::CpuInfo &getCpuInfo() const {
        return systemInfo.cpuInfo;
    }

    const bool getYieldThreads() const {
        return yieldThreads;
    }

    void assignToSpectacle(pid_t ppid, pid_t pid, const char *name, ClientContext &recruit) {
        auto spectaclesLock = spectacles.lock();
        auto sharedSpectacleIt = spectacles.recrutingByPpid.find(ppid); // try recruiter of sibling if it was first
        if (sharedSpectacleIt == spectacles.recrutingByPpid.end()) {
            sharedSpectacleIt = spectacles.recrutingByPpid.find(pid); // try recruiter of child processess if it was first
        }

        if (sharedSpectacleIt == spectacles.recrutingByPpid.end()) {
            auto parentToGrandparentIt = spectacles.pidToPpidMapForNewSpectacles.find(ppid); // try recruiter of parent if it was first
            if (parentToGrandparentIt != spectacles.pidToPpidMapForNewSpectacles.end()) {
                sharedSpectacleIt = spectacles.recrutingByPpid.find(parentToGrandparentIt->second);
                assert(sharedSpectacleIt != spectacles.recrutingByPpid.end());
            }
        }

        auto sharedSpectacleByNameIt = spectacles.recrutingByName.end();
        if (sharedSpectacleIt == spectacles.recrutingByPpid.end()) {
            sharedSpectacleByNameIt = spectacles.recrutingByName.find(std::string(name));
        }

        if ((sharedSpectacleIt != spectacles.recrutingByPpid.end()) || (sharedSpectacleByNameIt != spectacles.recrutingByName.end())) {
            auto &spectacle = (sharedSpectacleIt != spectacles.recrutingByPpid.end()) ? sharedSpectacleIt->second : sharedSpectacleByNameIt->second;
            IMember *newMember = nullptr;
            if (spectacle->isStillRecruting()) {
                newMember = spectacle->addNewMember();
            }

            if (newMember) {
                recruit.assignToSpectacle(newMember);
                log<Verbosity::bloat>("Found a spectacle that's actively recruting for ppid %d (matches %s ppid)", ppid, name);
                return;
            } else {
                bool wasRecrutingByPpid = spectacle->getChoreography().recruitByPpid();
                spectacles.active.push_back(std::move(spectacle));
                if (wasRecrutingByPpid) {
                    spectacles.recrutingByPpid.erase(sharedSpectacleIt);
                    auto it = spectacles.pidToPpidMapForNewSpectacles.find(ppid);
                    if (it != spectacles.pidToPpidMapForNewSpectacles.end()) {
                        spectacles.pidToPpidMapForNewSpectacles.erase(it);
                    }

                    log<Verbosity::bloat>("Found a spectacle that was recruting for ppid %d (matches %s ppid) but is not any more", ppid, name);
                } else {
                    spectacles.recrutingByName.erase(sharedSpectacleByNameIt);
                    log<Verbosity::bloat>("Found a spectacle that was recruting for name %s but is not any more", name);
                }
            }
        }
        auto *choreography = knownChoreographies->get(name);
        if (nullptr == choreography) {
            log<Verbosity::bloat>("No choreography for : %s", name);
            return;
        }
        log<Verbosity::bloat>("Found choreography %s for %s, creating new spectacle", choreography->getName().c_str(), name);
        auto spectacle = choreography->createSpectacle(directCallCallbacks);
        auto newMember = spectacle->addNewMember();
        recruit.assignToSpectacle(newMember);
        if (choreography->recruitByPpid()) {
            spectacles.pidToPpidMapForNewSpectacles[pid] = ppid;
            spectacles.recrutingByPpid[ppid] = std::move(spectacle);
        } else if (choreography->recruitByName()) {
            spectacles.recrutingByName[name] = std::move(spectacle);
        } else {
            spectacles.active.push_back(std::move(spectacle));
        }
    }

  protected:
    ServiceConfig serviceConfig;
    struct {
        std::string commandLine;
        std::future<void> subprocess;
    } runnerConfig;
    std::unique_ptr<Cal::Ipc::ConnectionListener> listener;
    int32_t defaultRpcMessageChannelSizeMB = staticDefaultRpcMessageChannelSizeMB;
    std::atomic_bool runInLoop = false;
    std::atomic_bool isRunning = false;
    std::atomic_bool isStopping = false;
    struct {
        Cal::Service::Apis::Ocl::OclSharedObjects ocl;
        Cal::Service::Apis::LevelZero::LevelZeroSharedObjects l0;
    } sharedObjects;
    Cal::Messages::RespHandshake config;
    Cal::Ipc::ShmemAllocator shmemManager;
    Cal::Ipc::MallocShmemZeroCopyManager mallocShmemZeroCopyManager;
    std::vector<RpcSubtypeHandlers> rpcHandlers;
    std::vector<Cal::Rpc::DirectCallCallbackT> directCallCallbacks;
    struct {
        struct {
            bool l0 = false;
            bool ocl = false;
            bool any() const {
                return l0 || ocl;
            }
            bool none() const {
                return false == any();
            }
        } availableApis;
        Cal::Utils::CpuInfo cpuInfo = {};
    } systemInfo;
    bool yieldThreads = false;
    std::unique_ptr<ChoreographyLibrary> knownChoreographies;
    struct {
        std::unique_lock<std::mutex> lock() {
            return std::unique_lock<std::mutex>(mutex);
        }
        std::mutex mutex;

        std::unordered_map<pid_t, std::unique_ptr<ISpectacle>> recrutingByPpid;
        std::unordered_map<std::string, std::unique_ptr<ISpectacle>> recrutingByName;
        std::unordered_map<pid_t, pid_t> pidToPpidMapForNewSpectacles;
        std::vector<std::unique_ptr<ISpectacle>> active;
    } spectacles;

    std::unique_ptr<Cal::Ipc::ConnectionListener> createConnectionListener();

    bool isClientSupported(uint32_t clientType) {
        return ((clientType == Cal::Messages::ReqHandshake::ocl) && systemInfo.availableApis.ocl) || ((clientType == Cal::Messages::ReqHandshake::l0) && systemInfo.availableApis.l0);
    }

    static void serviceSingleClient(std::unique_ptr<Cal::Ipc::Connection> clientConnection, Provider &service, bool isPersistentMode) {
        log<Verbosity::debug>("Starting to service client : %d", clientConnection->getId());
        Cal::Messages::ReqHandshake handshake;
        log<Verbosity::debug>("Performing handshake with client #%d", clientConnection->getId());
        if ((false == clientConnection->receive(handshake)) || handshake.isInvalid()) {
            log<Verbosity::error>("Handshake with client #%d has FAILED", clientConnection->getId());
            return;
        }
        if (false == service.isClientSupported(handshake.clientType)) {
            log<Verbosity::error>("Client #%d requested %s API which is not available in the system (missing loader)", clientConnection->getId(), handshake.clientTypeStr());
            return;
        }
        if ((false == clientConnection->send(service.getConfig()))) {
            log<Verbosity::error>("Failed to send service config to client #%d", clientConnection->getId());
            return;
        }
        log<Verbosity::info>("Handshake with client #%d has SUCCEEDED (pid:%d, ppid:%d, api:%s, process:%s)", clientConnection->getId(), handshake.pid, handshake.ppid, handshake.clientTypeStr(), handshake.clientProcessName);
        ClientContext ctx(isPersistentMode);
        service.assignToSpectacle(handshake.ppid, handshake.pid, handshake.clientProcessName, ctx);
        if (ctx.getSpectacleAssignment()) {
            log<Verbosity::debug>("Client #%d was assigned to a spectacle %p", clientConnection->getId(), ctx.getSpectacleAssignment());
        }
        bool brokenConnection = false;
        while (false == (brokenConnection || service.isServiceStopping())) {
            Cal::Ipc::ControlMessageHeader messageHeader;
            if (false == clientConnection->peek(messageHeader)) {
                log<Verbosity::debug>("Client : %d terminated connection", clientConnection->getId(), handshake.pid, handshake.clientTypeStr());
                brokenConnection = true;
                break;
            }
            log<Verbosity::debug>("Client : %d sent new message", clientConnection->getId());
            switch (messageHeader.type) {
            default:
                log<Verbosity::error>("Client : %d sent broken message (unknown type:%u, subtype:%u)", clientConnection->getId(), messageHeader.type, messageHeader.subtype);
                brokenConnection = true;
                break;

            case Cal::Ipc::ControlMessageHeader::messageTypeHeartbeat:
                log<Verbosity::debug>("Client : %d sent heartbeat", clientConnection->getId());
                break;

            case Cal::Ipc::ControlMessageHeader::messageTypeRequest:
                brokenConnection = (false == service.serviceRequestMessage(messageHeader, *clientConnection, ctx));
                break;
            }
        }
        log<Verbosity::debug>("Stopped servicing client : %d (reason : %s)", clientConnection->getId(), brokenConnection ? "broken connection" : "service shutdown");
        log<Verbosity::debug>("Reaping resources after client : %d", clientConnection->getId());
        ctx.cleanup(service.getShmemManager());
    }

    bool serviceRequestMessage(const Cal::Ipc::ControlMessageHeader &messageHeader, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        switch (messageHeader.subtype) {
        default:
            log<Verbosity::error>("Client : %d sent broken CAL request message (type:%u, unknown subtype:%u)", clientConnection.getId(), messageHeader.type, messageHeader.subtype);
            return false;
        case Cal::Messages::ReqAllocateShmem::messageSubtype: {
            Cal::Messages::ReqAllocateShmem request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqAllocateShmem)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqLaunchRpcShmemRingBuffer::messageSubtype: {
            Cal::Messages::ReqLaunchRpcShmemRingBuffer request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqLaunchRpcShmemRingBuffer)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqNegotiateUsmAddressRange::messageSubtype: {
            Cal::Messages::ReqNegotiateUsmAddressRange request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqNegotiateUsmAddressSpace)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqImportAddressSpace::messageSubtype: {
            Cal::Messages::ReqImportAddressSpace request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqImportAddressSpace)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        }
    }

    bool service(const Cal::Messages::ReqAllocateShmem &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested shmem (purpose : %s, size : %zu)", clientConnection.getId(), request.purposeStr(), request.size);
        auto size = request.size;
        if (0 == size) {
            switch (request.purpose) {
            default:
                log<Verbosity::error>("Client : %d requested ambigous shmem size", clientConnection.getId());
                return false;
            case Cal::Messages::ReqAllocateShmem::rpcMessageChannel:
                log<Verbosity::debug>("Client : %d requested shmem for RPC message channel, size suggested by service is : %dMB", clientConnection.getId(), defaultRpcMessageChannelSizeMB);
                size = Cal::Utils::MB * defaultRpcMessageChannelSizeMB;
                break;
            }
        }

        Cal::Ipc::Shmem shmem;
        {
            auto lock = shmemManager.lock();
            shmem = shmemManager.create(size, false);
        }

        if (nullptr == shmem.ptr) {
            return false;
        }

        Cal::Messages::RespAllocateShmem shmemResponse;
        shmemResponse.id = shmem.id;
        shmemResponse.size = shmem.underlyingSize;
        clientConnection.send(shmemResponse);

        {
            auto lock = ctx.lock();
            ctx.registerShmem(shmem);
        }
        return true;
    }

    bool service(const Cal::Messages::ReqLaunchRpcShmemRingBuffer &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested RPC ring buffer", clientConnection.getId());

        auto serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::activePolling;
        if (Cal::Utils::getCalEnvFlag(calUseSemaphoresInChannelServerEnvName)) {
            serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores;
        }

        auto clientCtxLock = ctx.lock();
        auto shmem = ctx.getShmemById(request.ringbufferShmemId);
        if (false == shmem.isValid()) {
            log<Verbosity::error>("Client : %d requested RPC ring buffer on invalid shmem", clientConnection.getId());
            return false;
        }

        auto channelServer = std::make_unique<Cal::Rpc::ChannelServer>(clientConnection, shmemManager);
        if (false == channelServer->init(shmem, request, serviceSynchronizationMethod)) {
            log<Verbosity::error>("Failed to initialize channel server for client : %d", clientConnection.getId());
            return false;
        }

        log<Verbosity::debug>("Initialized RPC ring buffer for client : %d", clientConnection.getId());
        Cal::Messages::RespLaunchRpcShmemRingBuffer response;
        response.serviceSynchronizationMethod = serviceSynchronizationMethod;
        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response RespLaunchRpcShmemRingBuffer to client : %d", clientConnection.getId());
            return false;
        }

        log<Verbosity::debug>("Spawning thread for new RPC ring buffer %d  of client %d", shmem.id, clientConnection.getId());
        auto worker = std::async(std::launch::async, Provider::serviceSingleRpcChannel, channelServer.get(), std::ref(ctx), std::ref(*this));
        ctx.registerRpcChannel(std::move(worker),
                               std::move(channelServer));

        return true;
    }

    bool service(const Cal::Messages::ReqNegotiateUsmAddressRange &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested usm address range (proposed base : %p, proposed size : %zu)", clientConnection.getId(), request.proposedUsmBase, request.proposedUsmSize);
        auto lock = ctx.lock();
        static std::mutex mmapBloatGuardMutex;
        std::unique_lock<std::mutex> mmapBloatGuardMutexLock(mmapBloatGuardMutex);

        size_t usmSize = request.proposedUsmSize ? request.proposedUsmSize : defaultUsmAddressRangeSizePerClient;
        auto negotiatedUsmRangeOpt = Cal::Usm::negotiateUsmRangeWithClient(clientConnection, request.proposedUsmBase, usmSize);
        if (!negotiatedUsmRangeOpt) {
            log<Verbosity::critical>("Failed to negotatie initial USM heap");
            return false;
        }

        mmapBloatGuardMutexLock.unlock();
        ctx.addUsmHeap({negotiatedUsmRangeOpt.value()});

        return true;
    }

    bool service(const Cal::Messages::ReqImportAddressSpace &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d sent an address space handle to be imported : %ld", clientConnection.getId(), request.addressSpace);

        auto clientCtxLock = ctx.lock();

        Cal::Messages::RespImportAddressSpace response;
        auto zeroCopyHandler = this->mallocShmemZeroCopyManager.importUserAddressSpace(request.addressSpace);
        if (nullptr == zeroCopyHandler) {
            response.allowedToUseZeroCopyForMallocShmem = false;
        } else {
            response.allowedToUseZeroCopyForMallocShmem = true;
            ctx.setMallocShmemZeroCopyHandler(std::move(zeroCopyHandler));
        }

        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response RespImportAddressSpace to client : %d", clientConnection.getId());
            return false;
        }

        return true;
    }

    static void serviceSingleRpcChannel(Cal::Rpc::ChannelServer *channel, ClientContext &ctx, Provider &service) {
        log<Verbosity::debug>("Starting to service RPC channel : %d", channel->getId());
        while (false == ctx.isClientStopping()) {
            auto newCommand = channel->wait(service.getYieldThreads());
            if (nullptr == newCommand.command) {
                log<Verbosity::debug>("Received empty RPC command on channel : %d", channel->getId());
                continue;
            }

            auto *header = reinterpret_cast<Cal::Rpc::RpcMessageHeader *>(newCommand.command);
            log<Verbosity::debug>("Received new RPC command request on channel : %d (type : %u, subtype %u)", channel->getId(), header->type, header->subtype);

            service.serviceSingleRpcCommand(*channel, ctx, header, newCommand.commandMaxSize);

            channel->signalCompletion(newCommand.completionStamp, header->flags);

            if (service.getYieldThreads()) {
                std::this_thread::yield();
            }
        }
        log<Verbosity::debug>("Stopping servicing RPC channel : %d", channel->getId());
    }

    bool serviceSingleRpcCommand(Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize) {
        if (command->type >= rpcHandlers.size()) {
            log<Verbosity::error>("Unhandled RPC command type : %d", command->type);
            return false;
        }

        auto &subtypeHandlers = rpcHandlers[command->type];
        if ((command->subtype >= subtypeHandlers.size()) || (nullptr == subtypeHandlers[command->subtype])) {
            log<Verbosity::error>("Unhandled RPC command subtype : %d for type : %d", command->subtype, command->type);
            return false;
        }

        auto spectacleAssignment = ctx.getSpectacleAssignment();
        if (spectacleAssignment) {
            spectacleAssignment->makeStepBefore(*command);
        }

        auto ret = subtypeHandlers[command->subtype](*this, channel, ctx, command, commandMaxSize);

        if (spectacleAssignment) {
            spectacleAssignment->makeStepAfter(*command);
        }

        return ret;
    }

    bool runCommand(const ServiceConfig::RunnerConfig &config);

    void spawnProcessAndWait(const ServiceConfig::RunnerConfig &config);
};

} // namespace Service

} // namespace Cal
