/*
 * Copyright (C) 2022-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "cal.h"
#include "level_zero/ze_api.h"
#include "level_zero/zet_api.h"
#include "service/cochoreographer.h"
#include "service/level_zero/artificial_events_manager.h"
#include "service/level_zero/context_mappings_tracker.h"
#include "service/level_zero/l0_shared_objects.h"
#include "service/level_zero/ongoing_hostptr_copies_manager.h"
#include "service/service_malloc_override.h"
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
#include <shared_mutex>
#include <sys/file.h>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Cal {

namespace Service {

bool getNeoKmdShimEnvEnabled();
void setNeoKmdShimEnvEnabled(bool value);

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

    enum class Mode : uint32_t {
        persistent,
        runner,
        sharedRunner
    };

    Mode mode = Mode::persistent;
    int sharedRunnerLockFd = -1;

    bool isAnyRunnerMode() const {
        return (this->mode == Mode::runner) || (this->mode == Mode::sharedRunner);
    }

    bool kmdShimEnabled = false;

    inline static const char *neoCalEnabledEnvName = "NEO_CAL_ENABLED";
    inline static const char *neoCalEnabledEnvValue = "1";

    ServiceConfig(bool kmdShimEnabled) : kmdShimEnabled(kmdShimEnabled) {
        if (!kmdShimEnabled) {
            Cal::Sys::setenv(neoCalEnabledEnvName, neoCalEnabledEnvValue, 1);
        }
    }
    ~ServiceConfig() {
        if (!kmdShimEnabled) {
            Cal::Sys::unsetenv(neoCalEnabledEnvName);
        }
    }
};

struct ClientConfig {
    virtual ~ClientConfig() {}
};

namespace Apis {

namespace Ocl {

extern cl_platform_id globalOclPlatform;
std::vector<std::string> getListOfUnimplementedFunctionNames();

struct OclCallbackContextForContextNotify {
    Cal::Rpc::ChannelServer &channel;
    Cal::Rpc::CallbackIdT callbackId;
    char *errorInfo;
};

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
} // namespace Apis

struct UsmSharedHostAlloc {
    void *ctx = nullptr;
    Cal::Usm::UsmMmappedShmemArenaAllocator::AllocationT shmem;
    ApiType apiType;

    void (*gpuDestructor)(void *ctx, void *ptr) = nullptr;
};

class ClientContext {
  public:
    struct ChoreographyAssignment {
        ISpectacle *spectacle = nullptr;
        IMember *member = nullptr;
    };

    ClientContext(Cal::Ipc::GlobalShmemAllocators &globalShmemAllocators, bool automaticCleanupOfApiHandles)
        : globalShmemAllocators(globalShmemAllocators), automaticCleanupOfApiHandles(automaticCleanupOfApiHandles) {
        this->usmHeaps.reserve(4);
    }

    std::unique_lock<std::mutex> lock() {
        return std::unique_lock<std::mutex>(criticalSection);
    }

    void registerShmem(const Cal::Ipc::MmappedShmemAllocationT &shmem) {
        globalShmemsMap[shmem.getShmemId()] = shmem;
    }

    void registerRpcChannel(std::future<void> worker, std::unique_ptr<Cal::Rpc::ChannelServer> channel) {
        rpcChannels.push_back(std::make_pair(std::move(worker), std::move(channel)));
    }

    Cal::Ipc::MmappedShmemAllocationT getShmemById(int id) const {
        auto it = globalShmemsMap.find(id);
        if (it == globalShmemsMap.end()) {
            log<Verbosity::debug>("Asked for unknown shmem id %d (this context knows %zu shmems)", id, globalShmemsMap.size());
            return {};
        }
        return it->second;
    }

    void cleanup() {
        isStopping = true;
        log<Verbosity::debug>("Performing client RPC channels cleanup (num channels : %zu)", rpcChannels.size());
        for (auto &rpcChannel : rpcChannels) {
            rpcChannel.second->stop();
            rpcChannel.first.wait();
        }
        rpcChannels.clear();

        log<Verbosity::debug>("Performing USM shared/host allocations cleanup (num allocations leaked by client : %zu)", usmSharedHostMap.size());
        for (const auto &alloc : usmSharedHostMap) {
            if (alloc.second.gpuDestructor) {
                if (alloc.second.apiType == ApiType::LevelZero) {
                    if (l0ContextsTracking.count(static_cast<ze_context_handle_t>(alloc.second.ctx)) > 0) {
                        alloc.second.gpuDestructor(alloc.second.ctx, alloc.second.shmem.getSubAllocationPtr());
                    } else {
                        log<Verbosity::debug>("USM allocation leaked for context that is already released");
                    }
                }
            }
            for (auto &heap : usmHeaps) {
                if (heap.getUnderlyingAllocator().getMmapRange().contains(alloc.second.shmem.getSubAllocationPtr())) {
                    heap.free(alloc.second.shmem);
                }
            }
        }
        usmSharedHostMap.clear();

        log<Verbosity::debug>("Performing USM heaps cleanup (num heaps : %zu)", usmHeaps.size());
        for (const auto &heap : usmHeaps) {
            auto heapRange = heap.getUnderlyingAllocator().getMmapRange();
            if (-1 == Cal::Sys::munmap(heapRange.base(), heapRange.size())) {
                log<Verbosity::error>("Failed to munamp USM heap (base : %p, size : %zu)", heapRange.base(), heapRange.size());
            }
        }

        log<Verbosity::debug>("Performing client global shmem cleanup (num allocs : %zu)", globalShmemsMap.size());
        {
            for (const auto shmemIt : globalShmemsMap) {
                bool wasSharedVaShmem = false;
                for (auto &heap : usmHeaps) {
                    if (heap.getUnderlyingAllocator().getMmapRange().contains(shmemIt.second.getMmappedPtr())) {
                        globalShmemAllocators.getBaseAllocator().free(shmemIt.second); // already unmapped along with whole heap
                        wasSharedVaShmem = true;
                        break;
                    }
                }
                if (false == wasSharedVaShmem) {
                    globalShmemAllocators.getNonUsmMmappedAllocator().free(shmemIt.second);
                }
            }
        }
        globalShmemsMap.clear();

        l0SpecificCleanup();
    }

    void l0SpecificCleanup();

    bool isClientStopping() {
        return isStopping;
    }

    void addUsmHeap(Cal::Usm::UsmMmappedShmemArenaAllocator &&usmHeap) {
        usmHeaps.push_back(std::move(usmHeap));
    }

    const std::vector<Cal::Usm::UsmMmappedShmemArenaAllocator> &getUsmHeaps() const {
        return usmHeaps;
    }

    std::vector<Cal::Usm::UsmMmappedShmemArenaAllocator> &getUsmHeaps() {
        return usmHeaps;
    }

    bool isAddressFromUsmHeap(void *address) const {
        bool foundAddress = false;
        for (auto &heap : usmHeaps) {
            auto heapRange = heap.getUnderlyingAllocator().getMmapRange();
            if (heapRange.contains(address)) {
                foundAddress = true;
                break;
            }
        }
        return foundAddress;
    }

    void addUsmSharedHostAlloc(void *ctx, const Cal::Usm::UsmMmappedShmemArenaAllocator::AllocationT &shmem, ApiType apiType, void (*gpuDestructor)(void *ctx, void *ptr)) {
        usmSharedHostMap[shmem.getSubAllocationPtr()] = UsmSharedHostAlloc{ctx, shmem, apiType, gpuDestructor};
    }

    void reapUsmSharedHostAlloc(void *ptr, bool callGpuDestructor = true) {
        auto it = usmSharedHostMap.find(ptr);
        if (usmSharedHostMap.end() == it) {
            log<Verbosity::debug>("Asked to reap an unknown pointer %p given as USM shared/host allocation", ptr);
            return;
        }
        auto &alloc = it->second;
        if (callGpuDestructor && alloc.gpuDestructor) {
            alloc.gpuDestructor(alloc.ctx, alloc.shmem.getSubAllocationPtr());
        }

        for (auto &heap : usmHeaps) {
            if (heap.getUnderlyingAllocator().getMmapRange().contains(alloc.shmem.getSubAllocationPtr())) {
                heap.free(alloc.shmem);
            }
        }
        usmSharedHostMap.erase(it);
    }

    void assignToSpectacle(IMember *assignment) {
        spectacleAssignment = assignment;
    }

    IMember *getSpectacleAssignment() {
        return spectacleAssignment;
    }

    void assignToCallbackContextForContextNotify(std::unique_ptr<Apis::Ocl::OclCallbackContextForContextNotify> notify) {
        oclCallbackContextForContextNotify = std::move(notify);
    }

    Cal::Ipc::MemoryBlocksManager &getMemoryBlocksManager() {
        return memoryBlocksManager;
    }

    void *remapPointer(Cal::Ipc::NonUsmMmappedShmemAllocator &nonUsmShmemAllocator, const void *clientAddress, size_t memorySize) {
        auto &memoryBlock = memoryBlocksManager.registerMemoryBlock(nonUsmShmemAllocator, clientAddress, memorySize);
        auto remappedPtr = memoryBlock.translate(clientAddress);
        return remappedPtr;
    }

    Cal::Service::LevelZero::ContextMappingsTracker &getContextMappingsTracker() {
        return contextMappingsTracker;
    }

    Cal::Service::LevelZero::ArtificialEventsManager &getArtificialEventsManager() {
        return artificialEventsManager;
    }

    Cal::Service::LevelZero::OngoingHostptrCopiesManager &getOngoingHostptrCopiesManager() {
        return hostptrCopiesManager;
    }

    void *importClientAddressSpace(std::string_view resourcePath, size_t capacity, uintptr_t clientBaseAddress) {
        auto succesfullyOpened = mallocShmemImporter.open(resourcePath, capacity, clientBaseAddress);
        return succesfullyOpened ? mallocShmemImporter.getLocalBaseAddress() : nullptr;
    }

    void *importClientMallocPtr(uintptr_t clientPtr, size_t size, size_t exporterCurrentHeapSizeHint) {
        if (mallocOverrideData) {
            return MallocOverride::importPtr(reinterpret_cast<void *>(clientPtr), *mallocOverrideData);
        }
        return mallocShmemImporter.import(clientPtr, size, exporterCurrentHeapSizeHint);
    }

    bool isImportableClientMallocPtr(void *ptr) {
        bool isImportable = mallocShmemImporter.isImportable(ptr);
        log<Verbosity::bloat>("isImportableClientMallocPtr (ptr=%p) : %s", ptr, isImportable ? "yes" : "no");
        return isImportable;
    }

    void setMallocOverrideData(std::unique_ptr<MallocOverride::ClientData> &data) { mallocOverrideData = std::move(data); }

    uint32_t getCopyCommandQueueGroupIndex() const { return this->copyCommandQueueGroupIndex; }
    void setCopyCommandQueueGroupIndex(uint32_t value) { this->copyCommandQueueGroupIndex = value; }
    uint32_t getComputeCommandQueueGroupIndex() const { return this->computeCommandQueueGroupIndex; }
    void setComputeCommandQueueGroupIndex(uint32_t value) { this->computeCommandQueueGroupIndex = value; }
    [[nodiscard]] std::unique_lock<std::mutex> obtainCommandQueueGroupsLock() { return std::unique_lock<std::mutex>(this->commandQueueGroupsMtx); }

    template <typename HandleT>
    void trackAllocatedResource(HandleT handle) {
        if (automaticCleanupOfApiHandles) {
            trackAllocatedResource(handle, getTracking<HandleT>());
        }
    }

    template <typename HandleT>
    void removeResourceTracking(HandleT handle) {
        if (automaticCleanupOfApiHandles) {
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
        } else if constexpr (std::is_same_v<HandleT, ze_image_handle_t>) {
            return l0ImagesTracking;
        } else if constexpr (std::is_same_v<HandleT, zet_metric_streamer_handle_t>) {
            return l0MetricStreamersTracking;
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

    Cal::Ipc::GlobalShmemAllocators &globalShmemAllocators;
    bool automaticCleanupOfApiHandles = false;
    uint32_t copyCommandQueueGroupIndex = std::numeric_limits<uint32_t>::max();
    uint32_t computeCommandQueueGroupIndex = std::numeric_limits<uint32_t>::max();
    std::mutex commandQueueGroupsMtx;
    std::atomic_bool isStopping = false;
    std::mutex criticalSection;
    std::vector<Cal::Usm::UsmMmappedShmemArenaAllocator> usmHeaps;
    std::unordered_map<int, Cal::Ipc::MmappedShmemAllocationT> globalShmemsMap;
    std::unordered_map<void *, UsmSharedHostAlloc> usmSharedHostMap;
    std::vector<std::pair<std::future<void>, std::unique_ptr<Cal::Rpc::ChannelServer>>> rpcChannels;

    IMember *spectacleAssignment = nullptr;

    std::unique_ptr<Apis::Ocl::OclCallbackContextForContextNotify> oclCallbackContextForContextNotify;

    std::unordered_set<ze_context_handle_t> l0ContextsTracking{};
    std::unordered_set<ze_command_queue_handle_t> l0CommandQueuesTracking{};
    std::unordered_set<ze_command_list_handle_t> l0CommandListsTracking{};
    std::unordered_set<ze_module_handle_t> l0ModulesTracking{};
    std::unordered_set<ze_module_build_log_handle_t> l0ModuleBuildLogsTracking{};
    std::unordered_set<ze_kernel_handle_t> l0KernelsTracking{};
    std::unordered_set<ze_event_handle_t> l0EventsTracking{};
    std::unordered_set<ze_event_pool_handle_t> l0EventPoolsTracking{};
    std::unordered_set<ze_fence_handle_t> l0FencesTracking{};
    std::unordered_set<ze_image_handle_t> l0ImagesTracking{};
    std::unordered_set<zet_metric_streamer_handle_t> l0MetricStreamersTracking{};

    Cal::Ipc::MemoryBlocksManager memoryBlocksManager{};
    Cal::Service::LevelZero::ContextMappingsTracker contextMappingsTracker{};
    Cal::Service::LevelZero::ArtificialEventsManager artificialEventsManager{};
    Cal::Service::LevelZero::OngoingHostptrCopiesManager hostptrCopiesManager{};
    Cal::Ipc::MallocShmemImporter mallocShmemImporter = {};
    std::unique_ptr<MallocOverride::ClientData> mallocOverrideData{};
};

struct DeviceFdByPathCache {
    using RefCountedFd = std::pair<int /*cachedFd*/, int /*refCount*/>;
    using FdCallback = std::function<void(const std::string &devicePath, int fd)>;

    FdCallback onOpenFd = nullptr;
    FdCallback onCloseFd = nullptr;

    void setOnOpenCallback(FdCallback callback) {
        onOpenFd = std::move(callback);
    }

    void setOnCloseCallback(FdCallback callback) {
        onCloseFd = std::move(callback);
    }

    int getRefCountedFd(const std::string &devicePath) {
        auto mapLock = refCountedFdByDevicePath.lock();
        auto iter = (*refCountedFdByDevicePath).find(devicePath);
        if (iter == (*refCountedFdByDevicePath).end()) {
            auto openedFd = open(devicePath.c_str(), O_RDWR | O_CLOEXEC);
            if (openedFd < 0) {
                auto err = errno;
                log<Verbosity::error>("Failed to open file for devicePath=%s : errno=%d=%s", devicePath.c_str(), err, strerror(err));
                return -1;
            }
            (*refCountedFdByDevicePath)[devicePath] = {openedFd, 1};
            log<Verbosity::debug>("File opened successfully for devicePath=%s : openedFd=%d refCount=1", devicePath.c_str(), openedFd);
            if (onOpenFd) {
                onOpenFd(devicePath, openedFd);
            }
            return openedFd;
        } else {
            auto &[cachedFd, refCount] = (*iter).second;
            ++refCount;
            log<Verbosity::debug>("File already open for devicePath=%s : cachedFd=%d refCount=%d", devicePath.c_str(), cachedFd, refCount);
            return cachedFd;
        }
    }

    int closeRefCountedFd(const std::string &devicePath) {
        auto mapLock = refCountedFdByDevicePath.lock();
        auto iter = (*refCountedFdByDevicePath).find(devicePath);
        if (iter == (*refCountedFdByDevicePath).end()) {
            log<Verbosity::debug>("Couldn't find file for devicePath=%s", devicePath.c_str());
            return -1;
        }
        auto &[cachedFd, refCount] = (*iter).second;
        if (refCount <= 0) {
            log<Verbosity::error>("Found incorrect refcount for devicePath=%s : refCount=%d", devicePath.c_str(), refCount);
            return -1;
        }
        if (refCount == 1) {
            if (onCloseFd) {
                onCloseFd(devicePath, cachedFd);
            }
            auto ret = close(cachedFd);
            if (ret != 0) {
                auto err = errno;
                log<Verbosity::error>("Failed to close file for devicePath=%s : cachedFd=%d errno=%d=%s", devicePath.c_str(), cachedFd, err, strerror(err));
                return ret;
            }
            log<Verbosity::debug>("File closed successfully for devicePath=%s : cachedFd=%d refCount=%d", devicePath.c_str(), cachedFd, refCount);
            (*refCountedFdByDevicePath).erase(devicePath);
            return 0;
        } else {
            log<Verbosity::debug>("File not closed yet for devicePath=%s : cachedFd=%d refCount=%d", devicePath.c_str(), cachedFd, refCount);
            --refCount;
            return 0;
        }
    }

    Cal::Utils::Lockable<std::unordered_map<std::string /*devicePath*/, RefCountedFd>> refCountedFdByDevicePath{};
};

class Provider {
  public:
    using RpcHandler = bool (*)(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader *command, size_t commandMaxSize);
    using RpcSubtypeHandlers = std::vector<RpcHandler>;
    static constexpr int32_t staticDefaultSharedVaSizeGB = 256;
    static constexpr int32_t staticDefaultRpcMessageChannelSizeMB = 256;
    static constexpr int32_t staticSharedVaArenaSizeMB = 256;

    enum ErrorCode : int {
        Success = 0,
        FailedToRunSubprocess = 1,
    };

    Provider(std::unique_ptr<ChoreographyLibrary> knownChoreographies, ServiceConfig &&serviceConfig);

    struct ModuleCache {
        struct Entry {
            ze_context_handle_t hContext = {};
            ze_device_handle_t hDevice = {};
            ze_module_format_t format = {};
            ze_module_constants_t constants = {};
            size_t inputSize = {};
            size_t binaryHash = {};
            size_t buildOptionsHash = {};
            uint8_t *pNativeBinary;
            size_t nativeSize = 0u;
        };
        using Cache = std::vector<Entry>;

        bool compareDesc(const ze_module_desc_t *desc, const Entry &entry) {
            auto ret = desc->format == entry.format;
            ret &= desc->pNext == nullptr;
            ret &= desc->inputSize == entry.inputSize;
            if (!ret) {
                return false;
            }

            ret &= std::hash<std::string>{}(std::string(reinterpret_cast<const char *>(desc->pInputModule), desc->inputSize)) == entry.binaryHash;
            if (!ret) {
                return false;
            }

            if (desc->pBuildFlags) {
                ret &= std::hash<std::string>{}(desc->pBuildFlags) == entry.buildOptionsHash;
            } else {
                ret &= entry.buildOptionsHash == 0;
            }
            if (!ret) {
                return false;
            }

            if (desc->pConstants) {
                ret &= desc->pConstants->numConstants == entry.constants.numConstants;
                if (ret && (desc->pConstants->numConstants > 0u)) {
                    ret &= memcmp(desc->pConstants->pConstantIds, entry.constants.pConstantIds, desc->pConstants->numConstants * sizeof(uint32_t)) == 0;
                    auto values = reinterpret_cast<uint64_t *>(entry.constants.pConstantValues);
                    for (uint32_t i = 0; i < desc->pConstants->numConstants; ++i) {
                        ret &= *static_cast<const uint64_t *>(desc->pConstants->pConstantValues[i]) == values[i];
                    }
                }
            } else {
                ret &= entry.constants.numConstants == 0;
            }
            return ret;
        }

        std::optional<Cache::iterator> find(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t *desc) {
            if (desc == nullptr) {
                return std::nullopt;
            }
            for (auto entry = cache.begin(); entry != cache.end(); ++entry) {
                if (hDevice == entry->hDevice &&
                    compareDesc(desc, *entry)) {
                    return entry;
                }
            }
            return std::nullopt;
        }

        void store(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t *desc, size_t nativeSize, uint8_t *pNativeBinary) {
            if (desc == nullptr || desc->pNext) {
                return;
            }
            auto &entry = cache.emplace_back();
            entry.hContext = hContext;
            entry.hDevice = hDevice;
            if (desc->pBuildFlags) {
                entry.buildOptionsHash = std::hash<std::string>{}(desc->pBuildFlags);
            }
            entry.binaryHash = std::hash<std::string>{}(std::string(reinterpret_cast<const char *>(desc->pInputModule), desc->inputSize));
            entry.nativeSize = nativeSize;
            entry.pNativeBinary = pNativeBinary;
            entry.format = desc->format;
            entry.inputSize = desc->inputSize;
            if (desc->pConstants && desc->pConstants->numConstants > 0u) {
                entry.constants.numConstants = desc->pConstants->numConstants;
                auto ids = new uint32_t[desc->pConstants->numConstants];
                memcpy(ids, desc->pConstants->pConstantIds, desc->pConstants->numConstants * sizeof(uint32_t));
                entry.constants.pConstantIds = ids;
                auto values = new uint64_t[desc->pConstants->numConstants];
                for (uint32_t i = 0; i < desc->pConstants->numConstants; ++i) {
                    values[i] = *static_cast<const uint64_t *>(desc->pConstants->pConstantValues[i]);
                }
                entry.constants.pConstantValues = reinterpret_cast<const void **>(values);
            }
        }

        [[nodiscard]] auto obtainOwnership() {
            return std::unique_lock<std::mutex>(mtx);
        }

        ~ModuleCache() {
            for (auto &entry : cache) {
                delete[] entry.pNativeBinary;
                delete[] entry.constants.pConstantIds;
                auto values = reinterpret_cast<uint64_t *>(entry.constants.pConstantValues);
                delete[] values;
            }
        }

      protected:
        Cache cache;
        std::mutex mtx;
    } moduleCache;

    int run() {
        if (this->isRunning) {
            log<Verbosity::critical>("Service is already running");
            return -1;
        }
        this->isRunning = true;
        log<Verbosity::info>("Starting Compute Aggregation Layer service from PID : %d", getpid());

        std::vector<std::future<void>> clients;

        bool calEnableOclInCalrunEnvDefaultValue = this->serviceConfig.kmdShimEnabled ? false : true;
        if (Cal::Utils::getCalEnvFlag(calEnableOclInCalrunEnvName, calEnableOclInCalrunEnvDefaultValue)) {
            log<Verbosity::info>("Initializing OCL API");
            if (this->serviceConfig.kmdShimEnabled) {
                setNeoKmdShimEnvEnabled(false);
            }
            systemInfo.availableApis.ocl = sharedObjects.ocl.init();
            if (this->serviceConfig.kmdShimEnabled) {
                setNeoKmdShimEnvEnabled(true);
            }
            if (false == systemInfo.availableApis.ocl) {
                log<Verbosity::warning>("OpenCL API is not available in the system");
            }
        } else {
            log<Verbosity::debug>("OpenCL API disabled with %s=0", calEnableOclInCalrunEnvName.data());
        }

        bool calEnableL0InCalrunEnvDefaultValue = this->serviceConfig.kmdShimEnabled ? false : true;
        if (Cal::Utils::getCalEnvFlag(calEnableL0InCalrunEnvName, calEnableL0InCalrunEnvDefaultValue)) {
            log<Verbosity::info>("Initializing L0 API");
            if (this->serviceConfig.kmdShimEnabled) {
                setNeoKmdShimEnvEnabled(false);
            }
            systemInfo.availableApis.l0 = sharedObjects.l0.init();
            if (this->serviceConfig.kmdShimEnabled) {
                setNeoKmdShimEnvEnabled(true);
            }
            if (false == systemInfo.availableApis.l0) {
                log<Verbosity::warning>("Level Zero API is not available in the system");
            }
        } else {
            log<Verbosity::debug>("Level Zero API disabled with %s=0", calEnableL0InCalrunEnvName.data());
        }

        if (this->serviceConfig.kmdShimEnabled) {
            log<Verbosity::info>("Initializing IOCTL API");
            systemInfo.availableApis.ioctl = true;
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
            log<Verbosity::error>("Could not read information about the CPU virtual address bits - will have impact on USM device memory");
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
        if (-1 != serviceConfig.sharedRunnerLockFd) {
            if ((0 != Cal::Sys::flock(serviceConfig.sharedRunnerLockFd, LOCK_UN)) || (0 != Cal::Sys::close(serviceConfig.sharedRunnerLockFd))) {
                log<Verbosity::error>("Could not unlock shared runner lock for socket %s\n", serviceConfig.listener.socketPath.c_str());
            }
        }
        this->runInLoop = true;
        if (this->serviceConfig.runner.has_value()) {
            if (false == this->runCommand(this->serviceConfig.runner.value())) {
                return FailedToRunSubprocess;
            }
        }
        uint64_t clientOrdinal = 0U;
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
            clients.push_back(std::async(std::launch::async, Provider::serviceSingleClient, std::move(newConnection),
                                         clientOrdinal++, std::ref(*this), ServiceConfig::Mode::persistent == this->serviceConfig.mode));
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

    void setClientConfig(ClientConfig *config) {
        clientConfig.reset(config);
    }

    const ClientConfig *getClientConfig() const {
        return clientConfig.get();
    }

    Cal::Ipc::GlobalShmemAllocators &getGlobalShmemAllocators() {
        return *globalShmemAllocators;
    }

    Cal::Service::Apis::Ocl::OclSharedObjects &getOclSharedObjects() {
        return sharedObjects.ocl;
    }

    Cal::Service::Apis::LevelZero::L0SharedObjects &getL0SharedObjects() {
        return sharedObjects.l0;
    }

    const Cal::Utils::CpuInfo &getCpuInfo() const {
        return systemInfo.cpuInfo;
    }

    bool getYieldThreads() const {
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

    void parseCommandQueueGroups(uint32_t *count, ze_command_queue_group_properties_t *properties) {
        if (count == nullptr || properties == nullptr) {
            return;
        }
        if (this->commandQueueGroups.initialized) {
            return;
        }
        for (uint32_t i = 0u; i < *count; ++i) {
            if ((properties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY) &&
                !(properties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE)) {
                if (properties[i].numQueues == 1u) {
                    this->commandQueueGroups.copyGroupIndex = i;
                } else {
                    this->commandQueueGroups.linkedCopyGroupIndex = i;
                    this->commandQueueGroups.numLinkedCopyEngines = properties[i].numQueues;
                    log<Verbosity::debug>("Num Linked Copy Engines found: %d", properties[i].numQueues);
                }
            }
            if (properties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE) {
                this->commandQueueGroups.computeGroupindex = i;
                this->commandQueueGroups.numComputeEngines = properties[i].numQueues;
                log<Verbosity::debug>("Num Compute Engines found: %d", this->commandQueueGroups.numComputeEngines);
            }
        }
        if (this->commandQueueGroups.copyGroupIndex != std::numeric_limits<uint32_t>::max() &&
            this->commandQueueGroups.linkedCopyGroupIndex != std::numeric_limits<uint32_t>::max() &&
            this->commandQueueGroups.numLinkedCopyEngines != std::numeric_limits<uint32_t>::max() &&
            this->commandQueueGroups.computeGroupindex != std::numeric_limits<uint32_t>::max() &&
            this->commandQueueGroups.numComputeEngines != std::numeric_limits<uint32_t>::max()) {
            this->commandQueueGroups.initialized = true;
        }
    }

    void overrideCommandQueueDesc(ze_command_queue_desc_t *desc, ClientContext &ctx) {
        if (desc == nullptr) {
            return;
        }
        if (!this->commandQueueGroups.initialized) {
            return;
        }
        if ((desc->ordinal == this->commandQueueGroups.copyGroupIndex || desc->ordinal == this->commandQueueGroups.linkedCopyGroupIndex) && this->commandQueueGroups.copyRoundRobinEnabled) {
            auto index = ctx.getCopyCommandQueueGroupIndex();
            if (index == std::numeric_limits<uint32_t>::max()) {
                auto lock = ctx.obtainCommandQueueGroupsLock();
                if (index == std::numeric_limits<uint32_t>::max()) {
                    index = this->commandQueueGroups.selector.fetch_add(1u) % (this->commandQueueGroups.numLinkedCopyEngines + 1);
                    ctx.setCopyCommandQueueGroupIndex(index);
                }
            }
            if (index == 0u) {
                desc->ordinal = this->commandQueueGroups.copyGroupIndex;
                desc->index = 0u;
            } else {
                desc->ordinal = this->commandQueueGroups.linkedCopyGroupIndex;
                desc->index = index - 1;
            }
            log<Verbosity::debug>("Overriding Copy Queue index: %d", index);
        } else if (desc->ordinal == this->commandQueueGroups.computeGroupindex && this->commandQueueGroups.computeRoundRobinEnabled) {
            auto index = ctx.getComputeCommandQueueGroupIndex();
            if (index == std::numeric_limits<uint32_t>::max()) {
                auto lock = ctx.obtainCommandQueueGroupsLock();
                if (index == std::numeric_limits<uint32_t>::max()) {
                    index = this->commandQueueGroups.computeSelector.fetch_add(1u) % this->commandQueueGroups.numComputeEngines;
                    ctx.setComputeCommandQueueGroupIndex(index);
                }
            }
            log<Verbosity::debug>("Overriding Compute Queue index: %d", index);
            desc->index = index;
        }
    }

    void overrideCommandListDesc(ze_command_list_desc_t *desc, ClientContext &ctx) {
        if (desc == nullptr) {
            return;
        }
        if (!this->commandQueueGroups.initialized) {
            return;
        }
        if (desc->commandQueueGroupOrdinal != this->commandQueueGroups.copyGroupIndex && desc->commandQueueGroupOrdinal != this->commandQueueGroups.linkedCopyGroupIndex) {
            return;
        }
        if (!this->commandQueueGroups.copyRoundRobinEnabled) {
            return;
        }
        auto index = ctx.getCopyCommandQueueGroupIndex();
        if (index == std::numeric_limits<uint32_t>::max()) {
            auto lock = ctx.obtainCommandQueueGroupsLock();
            if (index == std::numeric_limits<uint32_t>::max()) {
                index = this->commandQueueGroups.selector.fetch_add(1u) % (this->commandQueueGroups.numLinkedCopyEngines + 1);
                ctx.setCopyCommandQueueGroupIndex(index);
            }
        }
        if (index == 0u) {
            desc->commandQueueGroupOrdinal = this->commandQueueGroups.copyGroupIndex;
        } else {
            desc->commandQueueGroupOrdinal = this->commandQueueGroups.linkedCopyGroupIndex;
        }
    }

    bool useSyncMallocCopy() const {
        return this->syncMallocCopy;
    }

    bool useBatched() const {
        return this->batchedService;
    }

    DeviceFdByPathCache &getDeviceFdByPathCache() {
        return deviceFdByPathCache;
    }

  protected:
    ServiceConfig serviceConfig;
    DeviceFdByPathCache deviceFdByPathCache{};
    struct {
        std::string commandLine;
        std::future<void> subprocess;
    } runnerConfig;
    std::unique_ptr<Cal::Ipc::ConnectionListener> listener;
    int32_t defaultSharedVaSizeInGB = staticDefaultSharedVaSizeGB;
    int32_t defaultRpcMessageChannelSizeMB = staticDefaultRpcMessageChannelSizeMB;
    int32_t sharedVaArenaSizeMB = staticSharedVaArenaSizeMB;
    std::atomic_bool runInLoop = false;
    std::atomic_bool isRunning = false;
    std::atomic_bool isStopping = false;
    std::atomic_int activeClients = 0;
    bool syncMallocCopy = false;
    bool batchedService = false;
    struct {
        Cal::Service::Apis::Ocl::OclSharedObjects ocl;
        Cal::Service::Apis::LevelZero::L0SharedObjects l0;
    } sharedObjects;
    Cal::Messages::RespHandshake config;
    std::unique_ptr<Cal::Service::ClientConfig> clientConfig;
    std::unique_ptr<Cal::Ipc::GlobalShmemAllocators> globalShmemAllocators;
    std::vector<RpcSubtypeHandlers> rpcHandlers;
    std::vector<Cal::Rpc::DirectCallCallbackT> directCallCallbacks;
    struct {
        struct {
            bool l0 = false;
            bool ocl = false;
            bool ioctl = false;
            bool any() const {
                return l0 || ocl || ioctl;
            }
            bool none() const {
                return false == any();
            }
        } availableApis;
        Cal::Utils::CpuInfo cpuInfo = {};
    } systemInfo;
    bool yieldThreads = true;
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

    struct CommandQueueGroups {
        bool copyRoundRobinEnabled = false;
        std::atomic_uint32_t selector{0u};

        uint32_t copyGroupIndex = std::numeric_limits<uint32_t>::max();
        uint32_t linkedCopyGroupIndex = std::numeric_limits<uint32_t>::max();
        uint32_t numLinkedCopyEngines = std::numeric_limits<uint32_t>::max();

        bool computeRoundRobinEnabled = true;
        std::atomic_uint32_t computeSelector{0u};

        uint32_t computeGroupindex = std::numeric_limits<uint32_t>::max();
        uint32_t numComputeEngines = std::numeric_limits<uint32_t>::max();

        bool initialized = false;
    } commandQueueGroups;

    std::unique_ptr<Cal::Ipc::ConnectionListener> createConnectionListener();

    bool isClientSupported(Cal::ApiType clientApiType) {
        return ((clientApiType == Cal::ApiType::OpenCL) && systemInfo.availableApis.ocl) || ((clientApiType == Cal::ApiType::LevelZero) && systemInfo.availableApis.l0);
    }

    static void serviceSingleClient(std::unique_ptr<Cal::Ipc::Connection> clientConnection, uint64_t clientOrdinal, Provider &service, bool isPersistentMode) {
        ++service.activeClients;
        struct ActiveClientGuard {
            ~ActiveClientGuard() {
                if (0 == service.activeClients--) {
                    if (ServiceConfig::Mode::sharedRunner == service.serviceConfig.mode) {
                        if (service.runInLoop) {
                            service.runInLoop = false;
                            service.listener->shutdown();
                        }
                    }
                }
            }
            Provider &service;
        } activeClientGuard{service};
        log<Verbosity::debug>("Starting to service client : %d (assigned ordinal : %lld)", clientConnection->getId(), clientOrdinal);

        Cal::Ipc::ControlMessageHeader prologueMessageHeader;
        while (clientConnection->peek(prologueMessageHeader) && (Cal::Ipc::ControlMessageHeader::messageTypePing == prologueMessageHeader.type)) {
            clientConnection->receive(prologueMessageHeader);
            log<Verbosity::debug>("Client : %d sent ping request", clientConnection->getId());
            if (false == clientConnection->send(prologueMessageHeader)) {
                log<Verbosity::error>("Could not send ping response to client : %d", clientConnection->getId());
            }
        }

        if (clientConnection->peekEof()) {
            log<Verbosity::info>("Client : #%d detected socket shutdown", clientConnection->getId());
            return;
        }

        if (clientConnection->peek(prologueMessageHeader) && (Cal::Ipc::ControlMessageHeader::messageTypeStop == prologueMessageHeader.type)) {
            clientConnection->receive(prologueMessageHeader);
            log<Verbosity::info>("Client : %d requested service to stop", clientConnection->getId());
            service.runInLoop = false;
            service.listener->shutdown();
            if (false == clientConnection->send(prologueMessageHeader)) {
                log<Verbosity::error>("Could not send stop response to client : %d", clientConnection->getId());
            }
            return;
        }

        Cal::Messages::ReqHandshake handshake{false};
        log<Verbosity::debug>("Performing handshake with client #%d", clientConnection->getId());
        if ((false == clientConnection->receive(handshake)) || handshake.isInvalid()) {
            log<Verbosity::error>("Handshake with client #%d has FAILED", clientConnection->getId());
            return;
        }

        auto handshakeResp = service.getConfig();
        handshakeResp.assignedClientOrdinal = clientOrdinal;
        if (false == clientConnection->send(handshakeResp)) {
            log<Verbosity::error>("Failed to send service config to client #%d", clientConnection->getId());
            return;
        }
        log<Verbosity::info>("Handshake with client #%d has SUCCEEDED (pid:%d, ppid:%d, process:%s)", clientConnection->getId(), handshake.pid, handshake.ppid, handshake.clientProcessName);
        ClientContext ctx(service.getGlobalShmemAllocators(), isPersistentMode);
        service.assignToSpectacle(handshake.ppid, handshake.pid, handshake.clientProcessName, ctx);
        if (ctx.getSpectacleAssignment()) {
            log<Verbosity::debug>("Client #%d was assigned to a spectacle %p", clientConnection->getId(), ctx.getSpectacleAssignment());
        }
        bool brokenConnection = false;
        while (false == (brokenConnection || service.isServiceStopping())) {
            Cal::Ipc::ControlMessageHeader messageHeader;
            if (false == clientConnection->peek(messageHeader)) {
                log<Verbosity::debug>("Client : %d (pid : %d) terminated connection", clientConnection->getId(), handshake.pid);
                brokenConnection = true;
                break;
            }
            log<Verbosity::debug>("Client : %d sent new message", clientConnection->getId());
            switch (messageHeader.type) {
            default:
                log<Verbosity::error>("Client : %d sent broken message (unknown type:%u, subtype:%u)", clientConnection->getId(), messageHeader.type, messageHeader.subtype);
                brokenConnection = true;
                break;

            case Cal::Ipc::ControlMessageHeader::messageTypePing:
                log<Verbosity::debug>("Client : %d sent ping request", clientConnection->getId());
                if (false == clientConnection->send(messageHeader)) {
                    log<Verbosity::error>("Could not send response ping response to client : %d", clientConnection->getId());
                }
                break;

            case Cal::Ipc::ControlMessageHeader::messageTypeStop:
                log<Verbosity::info>("Client : %d requested service to stop", clientConnection->getId());
                service.runInLoop = false;
                service.listener->shutdown();
                if (false == clientConnection->send(messageHeader)) {
                    log<Verbosity::error>("Could not send stop response to client : %d", clientConnection->getId());
                }
                break;

            case Cal::Ipc::ControlMessageHeader::messageTypeRequest:
                brokenConnection = (false == service.serviceRequestMessage(messageHeader, *clientConnection, ctx));
                break;
            }
        }
        log<Verbosity::debug>("Stopped servicing client : %d (reason : %s)", clientConnection->getId(), brokenConnection ? "broken connection" : "service shutdown");
        log<Verbosity::debug>("Reaping resources after client : %d", clientConnection->getId());
        ctx.cleanup();
    }

    bool serviceRequestMessageExt(const Cal::Ipc::ControlMessageHeader &messageHeader, Cal::Ipc::Connection &clientConnection, ClientContext &ctx);

    bool serviceRequestMessage(const Cal::Ipc::ControlMessageHeader &messageHeader, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        switch (messageHeader.subtype) {
        default:
            return serviceRequestMessageExt(messageHeader, clientConnection, ctx);
        case Cal::Messages::ReqHandshake::messageSubtype:
            log<Verbosity::error>("Client : %d unxpectedly sent handshake request (ReqHandshake)", clientConnection.getId());
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
        case Cal::Messages::ReqPageFault::messageSubtype: {
            Cal::Messages::ReqPageFault request(nullptr);
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqPageFault)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqTransferFd::messageSubtype: {
            Cal::Messages::ReqTransferFd request{0};
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqTransferFd)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqReverseTransferFd::messageSubtype: {
            Cal::Messages::ReqReverseTransferFd request{0};
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqReverseTransferFd)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqCheckApiAvailability::messageSubtype: {
            Cal::Messages::ReqCheckApiAvailability request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqCheckApiAvailability)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqRemoteMmap::messageSubtype: {
            Cal::Messages::ReqRemoteMmap request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqRemoteMmap)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqOpenGpuDevice::messageSubtype: {
            Cal::Messages::ReqOpenGpuDevice request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqOpenGpuDevice)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqCloseGpuDevice::messageSubtype: {
            Cal::Messages::ReqCloseGpuDevice request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqCloseGpuDevice)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        case Cal::Messages::ReqConfigMallocOverride::messageSubtype: {
            Cal::Messages::ReqConfigMallocOverride request;
            if ((false == clientConnection.receive(request)) || request.isInvalid()) {
                log<Verbosity::error>("Client : %d sent broken CAL request message (subtype:ReqConfigMallocOverride)", clientConnection.getId());
                return false;
            }
            return service(request, clientConnection, ctx);
        }
        }
    }

    bool service(const Cal::Messages::ReqReverseTransferFd &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested reverse transfer of FDs!", clientConnection.getId());

        std::vector<int> fds(request.numOfFds);
        if (false == clientConnection.receiveFds(fds.data(), request.numOfFds)) {
            log<Verbosity::error>("Could not receive FDs from the client!");
            return false;
        }

        Cal::Messages::RespReverseTransferFd response{};
        for (auto i = 0u; i < request.numOfFds; ++i) {
            response.remoteFds[i] = fds[i];
        }

        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response for ReqReverseTransferFd!");
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqTransferFd &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested transfer of FDs!", clientConnection.getId());
        if (false == clientConnection.sendFds(request.remoteFds, request.usedFdsCount)) {
            log<Verbosity::error>("Could not send FD to the client!");
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqPageFault &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested page fault on address: %p", clientConnection.getId(), request.ptr);
        auto ptr = reinterpret_cast<const char *>(request.ptr);
        [[maybe_unused]] auto volatile pageFaultRead = ptr[0];

        Cal::Messages::RespPageFault resp;
        clientConnection.send(resp);
        return true;
    }

    bool service(const Cal::Messages::ReqAllocateShmem &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested shmem (purpose : %s, size : %zu, shared : %s)", clientConnection.getId(), request.purposeStr(), request.size, request.sharedVa ? "TRUE" : "FALSE");
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

        Cal::Ipc::MmappedShmemAllocationT shmem;
        if (request.sharedVa) {
            auto ctxLock = ctx.lock();
            for (auto &heap : ctx.getUsmHeaps()) {
                shmem = *heap.allocateAsStandalone(size).getSourceAllocation();
                if (shmem.isValid()) {
                    break;
                }
            }
        } else {
            shmem = globalShmemAllocators->getNonUsmMmappedAllocator().allocate(size);
        }

        if (false == shmem.isValid()) {
            Cal::Messages::RespAllocateShmem shmemResponse;
            log<Verbosity::debug>("Client : %d requested shmem (purpose : %s, size : %zu, shared : %s) could not be allocated", clientConnection.getId(), request.purposeStr(), request.size, request.sharedVa ? "TRUE" : "FALSE");
            return clientConnection.send(shmemResponse);
        }

        Cal::Messages::RespAllocateShmem shmemResponse;
        shmemResponse.id = shmem.getShmemId();
        shmemResponse.size = shmem.getFileSize();
        if (request.sharedVa) {
            shmemResponse.sharedVa = shmem.getMmappedPtr();
        }
        {
            auto lock = ctx.lock();
            ctx.registerShmem(shmem);
        }
        return clientConnection.send(shmemResponse);
    }

    bool service(const Cal::Messages::ReqLaunchRpcShmemRingBuffer &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested RPC ring buffer", clientConnection.getId());

        auto serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::activePolling;
        if (Cal::Utils::getCalEnvFlag(calUseSemaphoresInChannelServerEnvName, true)) {
            serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores;
        }

        auto clientCtxLock = ctx.lock();
        auto shmem = ctx.getShmemById(request.ringbufferShmemId);
        if (false == shmem.isValid()) {
            log<Verbosity::error>("Client : %d requested RPC ring buffer on invalid shmem", clientConnection.getId());
            return false;
        }

        auto channelServer = std::make_unique<Cal::Rpc::ChannelServer>(clientConnection, globalShmemAllocators->getNonUsmMmappedAllocator());
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

        log<Verbosity::debug>("Spawning thread for new RPC ring buffer %d  of client %d", shmem.getShmemId(), clientConnection.getId());
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

        size_t usmSize = request.proposedUsmSize ? request.proposedUsmSize : (this->defaultSharedVaSizeInGB * Cal::Utils::GB);
        auto negotiatedUsmRangeOpt = Cal::Usm::negotiateUsmRangeWithClient(clientConnection, request.proposedUsmBase, usmSize);
        if (!negotiatedUsmRangeOpt) {
            log<Verbosity::critical>("Failed to negotatie initial USM heap");
            return false;
        }

        mmapBloatGuardMutexLock.unlock();
        ctx.addUsmHeap(Cal::Usm::UsmMmappedShmemArenaAllocator{this->globalShmemAllocators->getBaseAllocator(), negotiatedUsmRangeOpt.value(), this->sharedVaArenaSizeMB * Cal::Utils::MB});

        return true;
    }

    bool service(const Cal::Messages::ReqImportAddressSpace &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d sent an address space handle to be imported : %s, client address: %p, address space size %zu",
                              clientConnection.getId(), request.mallocShmemResourcePath, request.clientAddressSpaceBaseAddress, request.clientAddressSpaceSize);

        auto clientCtxLock = ctx.lock();

        Cal::Messages::RespImportAddressSpace response;
        response.serviceBaseAddressForClientAddressSpace = reinterpret_cast<uintptr_t>(ctx.importClientAddressSpace(std::string_view{request.mallocShmemResourcePath, sizeof(request.mallocShmemResourcePath)},
                                                                                                                    request.clientAddressSpaceSize, request.clientAddressSpaceBaseAddress));
        response.successfullyImported = (0 != response.serviceBaseAddressForClientAddressSpace);

        if (response.successfullyImported) {
            log<Verbosity::debug>("Succesfully imported client %d's address space handle (resource : %s, client address: %p, address space size %zu) as local address : %p",
                                  clientConnection.getId(), request.mallocShmemResourcePath, request.clientAddressSpaceBaseAddress, request.clientAddressSpaceSize, response.serviceBaseAddressForClientAddressSpace);
            log<Verbosity::debug>("Zero copy malloc for client %d's - ALLOWED", clientConnection.getId());
        } else {
            log<Verbosity::error>("Failed to import client %d's address space handle (resource : %s, client address: %p, address space size %zu) as local address : %p",
                                  clientConnection.getId(), request.mallocShmemResourcePath, request.clientAddressSpaceBaseAddress, request.clientAddressSpaceSize, response.serviceBaseAddressForClientAddressSpace);
            log<Verbosity::error>("Zero copy malloc for client %d's - DISABLED", clientConnection.getId());
        }

        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response RespImportAddressSpace to client : %d", clientConnection.getId());
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqCheckApiAvailability &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        bool available = false;
        switch (request.api) {
        default:
            log<Verbosity::error>("Client : %d requested unknown API : %s (%d)", clientConnection.getId(), Cal::asStr(request.api), static_cast<uint32_t>(request.api));
            break;
        case Cal::ApiType::OpenCL:
            available = systemInfo.availableApis.ocl;
            break;
        case Cal::ApiType::LevelZero:
            available = systemInfo.availableApis.l0;
            break;
        }

        log<Verbosity::debug>("Client : %d is checking availability of %s API which is %savailable", clientConnection.getId(), Cal::asStr(request.api), available ? " " : "NOT ");
        Cal::Messages::RespCheckApiAvailability response = {};
        response.available = available;

        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response for ReqReverseTransferFd!");
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqRemoteMmap &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested remote mmap : address=%p, lenght=%zu, prot=0x%x, flags=0x%x, fd=%d, offset=%zu", clientConnection.getId(), request.address, request.length, request.prot, request.flags, request.fd, request.offset);
        auto lock = ctx.lock();

        if (!ctx.isAddressFromUsmHeap(request.address)) {
            log<Verbosity::error>("Client : %d requested remote mmap for address %p beyond shared address space range", clientConnection.getId(), request.address);
            return false;
        }

        void *mappedPtr = Cal::Sys::mmap(request.address, request.length, request.prot, request.flags, request.fd, request.offset);
        if (mappedPtr == MAP_FAILED) {
            log<Verbosity::error>("Failed to call mmap in service memory : address=%p, lenght=%zu, fd=%d", request.address, request.length, request.fd);
            return false;
        }

        Cal::Messages::RespRemoteMmap response;
        response.mappedPtr = mappedPtr;
        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response for remote mmap : address=%p, lenght=%zu, fd=%d", request.address, request.length, request.fd);
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqOpenGpuDevice &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested service to open GPU device : devicePath=%s", clientConnection.getId(), request.devicePath);
        auto lock = ctx.lock();

        int refCountedFd = deviceFdByPathCache.getRefCountedFd(request.devicePath);
        if (refCountedFd < 0) {
            log<Verbosity::error>("Failed to open GPU device in service : devicePath=%s refCountedFd=%d", request.devicePath, refCountedFd);
            return false;
        }

        Cal::Messages::RespOpenGpuDevice response(refCountedFd);
        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response from service to open GPU device : devicePath=%s refCountedFd=%d", request.devicePath, refCountedFd);
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqCloseGpuDevice &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested service to close GPU device : devicePath=%s", clientConnection.getId(), request.devicePath);
        auto lock = ctx.lock();

        int result = deviceFdByPathCache.closeRefCountedFd(request.devicePath);
        if (result != 0) {
            log<Verbosity::error>("Failed to close GPU device in service : devicePath=%s result=%d", request.devicePath, result);
            return false;
        }

        Cal::Messages::RespCloseGpuDevice response(result);
        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response from service to close GPU device : devicePath=%s result=%d", request.devicePath, result);
            return false;
        }

        return true;
    }

    bool service(const Cal::Messages::ReqConfigMallocOverride &request, Cal::Ipc::Connection &clientConnection, ClientContext &ctx) {
        log<Verbosity::debug>("Client : %d requested service to config malloc override", clientConnection.getId());

        auto clientCtxLock = ctx.lock();

        bool isMallocOverridenInCal = MallocOverride::isOverridenInCAL();
        if (!isMallocOverridenInCal) {
            auto data = MallocOverride::initializeClientData();
            if (!data) {
                return false;
            }
            ctx.setMallocOverrideData(data);
        }

        Cal::Messages::RespConfigMallocOverride response(isMallocOverridenInCal);
        if (false == clientConnection.send(response)) {
            log<Verbosity::error>("Could not send response from service to config malloc override : isMallocOverridenInCAL=%s", (response.isMallocOverridenInCAL ? "true" : "false"));
            return false;
        }

        return true;
    }

    static void serviceSingleRpcChannel(Cal::Rpc::ChannelServer *channel, ClientContext &ctx, Provider &service) {
        log<Verbosity::debug>("Starting to service RPC channel : %d", channel->getId());
        static std::shared_mutex batchedMtx;
        static std::thread::id mtxOwner{};
        bool sharedLock = false;
        bool brokenChannel = false;
        while (false == ctx.isClientStopping()) {
            auto newCommand = channel->wait(service.getYieldThreads());
            if (nullptr == newCommand.command) {
                log<Verbosity::debug>("Received empty RPC command on channel : %d", channel->getId());
                continue;
            }

            auto *header = reinterpret_cast<Cal::Rpc::RpcMessageHeader *>(newCommand.command);
            log<Verbosity::debug>("Received new RPC command request on channel : %d (type : %u, subtype %u)", channel->getId(), header->type, header->subtype);

            if (service.useBatched()) {
                if (header->flags & Cal::Rpc::RpcMessageHeader::batched) {
                    if (mtxOwner != std::this_thread::get_id()) {
                        batchedMtx.lock();
                        mtxOwner = std::this_thread::get_id();
                    }
                } else {
                    if (mtxOwner == std::this_thread::get_id()) {
                        mtxOwner = std::thread::id{};
                        batchedMtx.unlock();
                    } else {
                        batchedMtx.lock_shared();
                        sharedLock = true;
                    }
                }
            }

            if (false == brokenChannel) {
                if (false == service.serviceSingleRpcCommand(*channel, ctx, header, newCommand.commandMaxSize)) {
                    log<Verbosity::error>("Channel : %d is broken", channel->getId(), header->type, header->subtype);
                    brokenChannel = true;
                }
            } else {
                log<Verbosity::error>("Ignoring new RPC command request on broken channel : %d (type : %u, subtype %u)", channel->getId(), header->type, header->subtype);
            }

            if (newCommand.completionStamp) {
                channel->signalCompletion(newCommand.completionStamp, header->flags);
            }

            if (sharedLock) {
                sharedLock = false;
                batchedMtx.unlock_shared();
            }

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
};

void checkForRequiredFilesLibrary(std::filesystem::path &calDir, std::string &libCalName, std::filesystem::path &libCalPath, std::string &fullCalLibPath);
void checkForRequiredFilesOcl(std::filesystem::path &calDir);
void checkForRequiredFilesL0(std::filesystem::path &libCalPath);
void checkForRequiredFiles(bool kmdShimEnabled);
void spawnProcessAndWait(const ServiceConfig::RunnerConfig &config);

namespace Apis::Ocl {
void registerAllGeneratedHandlersOcl(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers);
}

namespace Apis::LevelZero {
void registerAllGeneratedHandlersLevelZero(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers);
ze_event_handle_t getInternalEvent(ClientContext &calClientCtx, ze_command_list_handle_t cmdList);
bool addRelay(ze_result_t &status, ze_event_handle_t action, ze_event_handle_t trigger, ze_command_list_handle_t cmdList);
bool synchronizeOnEventAndRequestClientMemoryUpdate(ze_result_t &status, ze_event_handle_t event, Cal::Rpc::ChannelServer &channel, ClientContext &calClientCtx, void *ptr, size_t size);
} // namespace Apis::LevelZero

namespace Apis::DrmIoctl {
void registerAllHandlersDrmIoctl(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers);
}

} // namespace Service

} // namespace Cal
