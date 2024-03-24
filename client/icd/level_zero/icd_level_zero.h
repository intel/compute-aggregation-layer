/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "boost/container/flat_map.hpp"
#include "client/client_platform.h"
#include "client/icd/icd_global_state.h"
#include "client/icd/level_zero/api_customization/icd_level_zero_api.h"
#include "client/icd/level_zero/api_type_wrapper/device_wrapper.h"
#include "client/icd/level_zero/api_type_wrapper/handles_definitions.h"
#include "client/icd/level_zero/api_type_wrapper/kernel_wrapper.h"
#include "client/icd/level_zero/api_type_wrapper/module_wrapper.h"
#include "client/icd/level_zero/logic/hostptr_copies_reader.h"
#include "client/icd/level_zero/logic/properties_cache.h"
#include "client/icd/level_zero/logic/types_printer.h"
#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"
#include "level_zero/zes_api.h"
#include "level_zero/zes_ddi.h"
#include "level_zero/zet_api.h"
#include "level_zero/zet_ddi.h"
#include "shared/ref_counted.h"
#include "shared/shmem_transfer_desc.h"
#include "shared/staging_area_manager.h"

#include <atomic>
#include <cstdlib>
#include <limits>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <utility>

namespace Cal {
namespace Client::Icd {
namespace LevelZero {

extern uint32_t calCommandQueueSynchronizePollingTimeoutDivisor;

extern void *l0RedirectLibary;
void initializeL0RedirectionLibraryIfNeeded();

template <typename RemoteL0ObjectT, typename LocalL0ObjectT>
void objectCleanup(void *remote, void *local);

struct IcdL0Context : Cal::Shared::RefCountedWithParent<_ze_context_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;

    IcdL0Context(ze_context_handle_t remoteObject, Cal::Shared::SingleReference &&parent, CleanupFuncT cleanupFunc);

    struct AllocPropertiesCache {
        struct CacheEntry {
            const void *ptr;
            ze_memory_allocation_properties_t memAllocProperties;
            ze_device_handle_t device;
        };

        std::vector<CacheEntry> cache;
        std::shared_mutex mtx;

        bool obtainProperties(const void *ptr, ze_memory_allocation_properties_t *pMemAllocProperties, ze_device_handle_t *phDevice) {
            std::shared_lock lock(mtx);
            auto propIt = std::find_if(this->cache.begin(), this->cache.end(), [&](CacheEntry &el) {
                return el.ptr == ptr;
            });
            if (propIt == this->cache.end()) {
                return false;
            }
            memcpy(pMemAllocProperties, &propIt->memAllocProperties, sizeof(ze_memory_allocation_properties_t));
            if (phDevice) {
                phDevice[0] = propIt->device;
            }
            return true;
        }
        void cacheProperties(const void *ptr, ze_memory_allocation_properties_t *pMemAllocProperties, ze_device_handle_t *phDevice) {
            std::lock_guard<std::shared_mutex> lock(mtx);
            auto &propIt = this->cache.emplace_back();
            propIt.device = phDevice[0];
            propIt.ptr = ptr;
            memcpy(&propIt.memAllocProperties, pMemAllocProperties, sizeof(ze_memory_allocation_properties_t));
        }
        void invalidateAllocPropertiesCache() {
            std::lock_guard<std::shared_mutex> lock(mtx);
            this->cache.clear();
        }
    } allocPropertiesCache;

    void beforeReleaseCallback();

    StagingAreaManager<std::function<void *(size_t)>,
                       std::function<void(void *)>> &
    getStagingAreaManager() { return stagingAreaManager; }

  private:
    StagingAreaManager<std::function<void *(size_t)>,
                       std::function<void(void *)>>
        stagingAreaManager;
    void *allocateStagingArea(size_t size);
    void deallocateStagingAreas(void *ptr);
};

class IcdL0CommandList : public Cal::Shared::RefCountedWithParent<_ze_command_list_handle_t, Logic::IcdL0TypePrinter> {
  protected:
    using ChunkEntry = Cal::Utils::AddressRange;

  public:
    enum class CommandListType {
        Regular = 0,
        Immediate = 1,
        ImmediateSynchronous = 2,
    };

    using RefCountedWithParent::RefCountedWithParent;

    static CommandListType selectImmediateType(const ze_command_queue_desc_t *altdesc);

    bool isImmediate() const {
        return commandListType != CommandListType::Regular;
    }

    bool isImmediateSynchronous() const {
        return commandListType == CommandListType::ImmediateSynchronous;
    }

    bool isImmediateAsynchronous() const {
        return commandListType == CommandListType::Immediate;
    }

    void registerMemoryToWrite(const void *srcPtr, size_t srcSize);

    static bool rangesOverlap(const void *srcPtr, const void *dstPtr, size_t size);
    static bool rangesOverlap(const void *srcPtr, size_t srcSize, const void *dstPtr, size_t dstSize);

    ze_result_t writeRequiredMemory();

    void clearRequiredMemoryTransfers() {
        std::lock_guard lock{memoryToWriteMutex};
        memoryToWrite.clear();
    }

    bool sharedIndirectAccessSet = false;

    std::vector<const void *> &getUsedAllocations() {
        return this->usedAllocations;
    }

    template <typename... Args>
    void moveSharedAllocationsToGpu(Args... args) {
        (moveSharedAllocationsToGpuImpl(args), ...);
    }
    void moveKernelArgsToGpu(IcdL0Kernel *kernel);

    void registerTemporaryAllocation(const void *ptr, size_t size, std::unique_ptr<void, std::function<void(void *)>> alloc);
    void cleanTemporaryAllocations();
    void *getTemporaryAllocationForReuse(const void *ptr, size_t size);

    IcdL0Context *context{};

  protected:
    friend IcdL0Platform;

    void setCommandListType(CommandListType type) {
        commandListType = type;
    }

    void moveSharedAllocationsToGpuImpl(const void *ptr);

    void registerMemoryToContainer(const void *ptr, size_t size, std::vector<ChunkEntry> &memory);
    ChunkEntry mergeChunks(const ChunkEntry &first, const ChunkEntry &second);

    struct {
        std::mutex mutex;
        boost::container::flat_map<const void *, std::pair<size_t, std::unique_ptr<void, std::function<void(void *)>>>> allocations;
    } temporaryStagingAreas;

    CommandListType commandListType{CommandListType::Regular};
    std::mutex memoryToWriteMutex{};
    std::vector<ChunkEntry> memoryToWrite{};

    std::vector<const void *> usedAllocations{};
};

class IcdL0CommandQueue : public Cal::Shared::RefCountedWithParent<_ze_command_queue_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    [[nodiscard]] std::unique_lock<std::mutex> lock() {
        return std::unique_lock<std::mutex>{queueMutex};
    }

    void moveSharedAllocationsToGpu(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists);

    ze_command_queue_mode_t getCommandQueueMode();
    void setEmulatedSynchronousMode(bool onOff) {
        emulatedSynchronousMode = onOff;
    }
    bool isEmulatedSynchronousMode() const {
        return emulatedSynchronousMode;
    }

  private:
    friend IcdL0Platform;
    void setCommandQueueType(ze_command_queue_mode_t mode) {
        this->mode = mode;
    }

    std::mutex queueMutex{};
    ze_command_queue_mode_t mode{};
    bool emulatedSynchronousMode = false;
};

struct IcdL0ModuleBuildLog : Cal::Shared::RefCountedWithParent<_ze_module_build_log_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0EventPool : Cal::Shared::RefCountedWithParent<_ze_event_pool_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0Event : Cal::Shared::RefCountedWithParent<_ze_event_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
    enum State : uint32_t {
        STATE_UNKOWN = 0u,
        STATE_SIGNALED = 1u,
        STATE_CLEARED = 2u
    } state = STATE_CLEARED;
    ze_kernel_timestamp_result_t timestamp = {};

    void setAllowIcdState(const ze_command_list_handle_t commandList, bool isBeingAppendedForGpuModification) {
        this->allowIcdState &= static_cast<IcdL0CommandList *>(commandList)->isImmediate();
        if (isBeingAppendedForGpuModification) {
            this->state = State::STATE_UNKOWN;
        }
    }
    void signal() {
        this->state = State::STATE_SIGNALED;
    }
    void clear() {
        this->state = State::STATE_CLEARED;
        memset(&timestamp, 0u, sizeof(ze_kernel_timestamp_result_t));
    }
    bool isSignaled() const {
        return this->allowIcdState && this->state == State::STATE_SIGNALED;
    }
    bool isCleared() const {
        return this->allowIcdState && this->state == State::STATE_CLEARED;
    }
    void getTimestamp(ze_kernel_timestamp_result_t *queriedTimestamp) const {
        memcpy(queriedTimestamp, &timestamp, sizeof(ze_kernel_timestamp_result_t));
    }
    void storeTimestamp(const ze_kernel_timestamp_result_t *queriedTimestamp) {
        memcpy(&timestamp, queriedTimestamp, sizeof(ze_kernel_timestamp_result_t));
    }
    bool isTimestamp() {
        return this->allowIcdState && timestamp.context.kernelStart != 0u;
    }

  protected:
    bool allowIcdState = true;
};

struct IcdL0Image : Cal::Shared::RefCountedWithParent<_ze_image_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0MetricGroup : Cal::Shared::RefCountedWithParent<_zet_metric_group_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0Metric : Cal::Shared::RefCountedWithParent<_zet_metric_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0MetricStreamer : Cal::Shared::RefCountedWithParent<_zet_metric_streamer_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    IcdL0Context *context{};
};

class IcdL0Fence : public Cal::Shared::RefCountedWithParent<_ze_fence_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;
};

class IcdL0Platform : public Cal::Client::Icd::IcdPlatform, public _ze_driver_handle_t {
  public:
    IcdL0Platform(Cal::Client::Icd::IcdGlobalState &globalState)
        : IcdPlatform(globalState, Cal::ApiType::LevelZero) {
        if (0 != Cal::Utils::getCalEnvI64(calCommandQueueSynchronizePollingTimeoutDivisorEnvName, 0)) {
            calCommandQueueSynchronizePollingTimeoutDivisor = Cal::Utils::getCalEnvI64(calCommandQueueSynchronizePollingTimeoutDivisorEnvName, 0);
        }
    }

    ze_driver_handle_t asRemoteObject() {
        return calDriverHandle;
    }

    void setRemoteObject(ze_driver_handle_t newCalDriverHandle) {
        calDriverHandle = newCalDriverHandle;
    }

    ze_device_handle_t translateNewRemoteObjectToLocalObject(ze_device_handle_t remoteDeviceHandle, ze_device_handle_t parent) {
        return translateNewRemoteObjectToLocalObject<IcdL0Device>(remoteDeviceHandle, parent, devicesMap, devicesMapMutex);
    }

    ze_device_handle_t translateNewRemoteObjectToLocalObject(ze_device_handle_t remoteDeviceHandle, ze_driver_handle_t parent) {
        return translateNewRemoteObjectToLocalObject(remoteDeviceHandle, static_cast<ze_device_handle_t>(nullptr));
    }

    void removeObjectFromMap(ze_device_handle_t remoteDeviceHandle, IcdL0Device *localDeviceHandle) {
        removeObjectFromMap(remoteDeviceHandle, localDeviceHandle, devicesMap, devicesMapMutex);
    }

    ze_context_handle_t translateNewRemoteObjectToLocalObject(ze_context_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Context>(remoteHandle, static_cast<ze_context_handle_t>(nullptr), contextsMap, contextsMapMutex);
    }

    void removeObjectFromMap(ze_context_handle_t remoteHandle, IcdL0Context *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, contextsMap, contextsMapMutex);
    }

    ze_command_queue_handle_t translateNewRemoteObjectToLocalObject(ze_command_queue_handle_t remoteHandle, ze_command_queue_mode_t mode) {
        auto commandQueue = translateNewRemoteObjectToLocalObject<IcdL0CommandQueue>(remoteHandle, static_cast<ze_command_queue_handle_t>(nullptr), commandQueuesMap, commandQueuesMapMutex);
        if (commandQueue) {
            auto icdCommandQueue = static_cast<IcdL0CommandQueue *>(commandQueue);
            icdCommandQueue->setCommandQueueType(mode);
        }

        return commandQueue;
    }

    void removeObjectFromMap(ze_command_queue_handle_t remoteHandle, IcdL0CommandQueue *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, commandQueuesMap, commandQueuesMapMutex);
    }

    ze_command_list_handle_t translateNewRemoteObjectToLocalObject(ze_command_list_handle_t remoteHandle, IcdL0CommandList::CommandListType cmdListType) {
        auto commandList = translateNewRemoteObjectToLocalObject<IcdL0CommandList>(remoteHandle, static_cast<ze_command_list_handle_t>(nullptr), commandListsMap, commandListsMapMutex);
        if (commandList) {
            auto icdCommandList = static_cast<IcdL0CommandList *>(commandList);
            icdCommandList->setCommandListType(cmdListType);
        }

        return commandList;
    }

    void removeObjectFromMap(ze_command_list_handle_t remoteHandle, IcdL0CommandList *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, commandListsMap, commandListsMapMutex);
    }

    ze_module_handle_t translateNewRemoteObjectToLocalObject(ze_module_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Module>(remoteHandle, static_cast<ze_module_handle_t>(nullptr), modulesMap, modulesMapMutex);
    }

    void removeObjectFromMap(ze_module_handle_t remoteHandle, IcdL0Module *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, modulesMap, modulesMapMutex);
    }

    ze_module_build_log_handle_t translateNewRemoteObjectToLocalObject(ze_module_build_log_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0ModuleBuildLog>(remoteHandle,
                                                                          static_cast<ze_module_build_log_handle_t>(nullptr),
                                                                          moduleBuildLogsMap,
                                                                          moduleBuildLogsMapMutex);
    }

    void removeObjectFromMap(ze_module_build_log_handle_t remoteHandle, IcdL0ModuleBuildLog *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, moduleBuildLogsMap, moduleBuildLogsMapMutex);
    }

    ze_kernel_handle_t translateNewRemoteObjectToLocalObject(ze_kernel_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Kernel>(remoteHandle, static_cast<ze_kernel_handle_t>(nullptr), kernelsMap, kernelsMapMutex);
    }

    void removeObjectFromMap(ze_kernel_handle_t remoteHandle, IcdL0Kernel *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, kernelsMap, kernelsMapMutex);
    }

    ze_event_handle_t translateNewRemoteObjectToLocalObject(ze_event_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Event>(remoteHandle, static_cast<ze_event_handle_t>(nullptr), eventsMap, eventsMapMutex);
    }

    void removeObjectFromMap(ze_event_handle_t remoteHandle, IcdL0Event *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, eventsMap, eventsMapMutex);
    }

    ze_event_pool_handle_t translateNewRemoteObjectToLocalObject(ze_event_pool_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0EventPool>(remoteHandle, static_cast<ze_event_pool_handle_t>(nullptr), eventPoolsMap, eventPoolsMapMutex);
    }

    void removeObjectFromMap(ze_event_pool_handle_t remoteHandle, IcdL0EventPool *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, eventPoolsMap, eventPoolsMapMutex);
    }

    ze_image_handle_t translateNewRemoteObjectToLocalObject(ze_image_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Image>(remoteHandle, static_cast<ze_image_handle_t>(nullptr), imagesMap, imagesMapMutex);
    }

    void removeObjectFromMap(ze_image_handle_t remoteHandle, IcdL0Image *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, imagesMap, imagesMapMutex);
    }

    zet_metric_group_handle_t translateNewRemoteObjectToLocalObject(zet_metric_group_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0MetricGroup>(remoteHandle, static_cast<zet_metric_group_handle_t>(nullptr), metricGroupsMap, metricGroupsMapMutex);
    }

    void removeObjectFromMap(zet_metric_group_handle_t remoteHandle, IcdL0MetricGroup *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, metricGroupsMap, metricGroupsMapMutex);
    }

    zet_metric_handle_t translateNewRemoteObjectToLocalObject(zet_metric_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Metric>(remoteHandle, static_cast<zet_metric_handle_t>(nullptr), metricsMap, metricsMapMutex);
    }

    void removeObjectFromMap(zet_metric_handle_t remoteHandle, IcdL0Metric *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, metricsMap, metricsMapMutex);
    }

    zet_metric_streamer_handle_t translateNewRemoteObjectToLocalObject(zet_metric_streamer_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0MetricStreamer>(remoteHandle, static_cast<zet_metric_streamer_handle_t>(nullptr), metricStreamersMap, metricStreamersMapMutex);
    }

    void removeObjectFromMap(zet_metric_streamer_handle_t remoteHandle, IcdL0MetricStreamer *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, metricStreamersMap, metricStreamersMapMutex);
    }

    ze_fence_handle_t translateNewRemoteObjectToLocalObject(ze_fence_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Fence>(remoteHandle, static_cast<ze_fence_handle_t>(nullptr), fencesMap, fencesMapMutex);
    }

    void removeObjectFromMap(ze_fence_handle_t remoteHandle, IcdL0Fence *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, fencesMap, fencesMapMutex);
    }

    bool isZeAffinityMaskPresent();
    const std::vector<ze_device_handle_t> &getFilteredDevices() const { return filteredDevices; };

    void invalidateAllKernelArgCaches() {
        std::lock_guard<std::mutex> lock(this->kernelsMapMutex);
        for (auto &kernel : this->kernelsMap) {
            kernel.second->zeKernelSetArgumentValueCache.invalidateCache();
        }
    }

    void updateLastErrorDescription(std::thread::id tid, const std::string &errorDescription) {
        std::lock_guard<std::mutex> lock(this->lastErrorDescriptionMapMutex);
        this->lastErrorDescriptionMap[tid] = errorDescription;
    }

    std::string &getLastErrorDescription(std::thread::id tid) {
        std::lock_guard<std::mutex> lock(this->lastErrorDescriptionMapMutex);
        return lastErrorDescriptionMap[tid];
    }

    void *openUsmDevicePointerFromIpcHandle(ze_context_handle_t context, void *newUsmPtr) {
        if (!newUsmPtr || !globalState.getCpuInfo().isAccessibleByApplication(newUsmPtr)) {
            return newUsmPtr;
        }

        Cal::Utils::signalAbort("Service returned an address, which is not USM device!");

        return nullptr;
    }

    Logic::HostptrCopiesReader &getHostptrCopiesReader() {
        return hostptrCopiesReader;
    }

    Logic::PropertiesCache::VectorTuple<ze_driver_properties_t,
                                        ze_driver_ipc_properties_t,
                                        ze_driver_extension_properties_t,
                                        zes_device_properties_t>
        properties;

    struct PropertiesCount {
        uint32_t extensionCount = 0;
    } propertiesCount;

    template <typename T>
    constexpr uint32_t &getPropertiesCount() {
        if constexpr (std::is_same_v<T, ze_driver_extension_properties_t>) {
            return this->propertiesCount.extensionCount;
        }
        return Logic::PropertiesCache::defaultPropertiesCount;
    }

  private:
    template <typename LocalT, typename RemoteT, typename MapT>
    RemoteT translateNewRemoteObjectToLocalObject(RemoteT remoteHandle, RemoteT parent, MapT &mapping, std::mutex &mapMutex) {
        if (remoteHandle == nullptr) {
            return nullptr;
        }

        std::lock_guard lock{mapMutex};
        const auto it = mapping.find(remoteHandle);
        if (it != mapping.end()) {
            log<Verbosity::bloat>("Translating %s %p to %p", Logic::IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, it->second);
            return it->second;
        }

        auto localHandle = new LocalT{remoteHandle,
                                      Cal::Shared::SingleReference::wrap(parent ? parent->asLocalObject() : nullptr),
                                      &objectCleanup<RemoteT, LocalT *>};
        mapping[remoteHandle] = localHandle;

        log<Verbosity::bloat>("Translating %s %p to %p", Logic::IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, localHandle);
        return localHandle;
    }

    template <typename RemoteT, typename LocalT, typename MapT>
    void removeObjectFromMap(RemoteT remoteHandle, LocalT localHandle, MapT &mapping, std::mutex &mapMutex) {
        std::lock_guard lock{mapMutex};
        const auto it = mapping.find(remoteHandle);
        if (it == mapping.end()) {
            log<Verbosity::bloat>("Cannot remove mapping of %s [%p to %p]", Logic::IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, localHandle);
            return;
        }

        mapping.erase(it);
        log<Verbosity::bloat>("Removed mapping of %s [%p to %p]", Logic::IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, localHandle);
    }

    ze_driver_handle_t calDriverHandle{nullptr};

    std::mutex devicesMapMutex;
    std::map<ze_device_handle_t, IcdL0Device *> devicesMap;

    std::mutex contextsMapMutex;
    std::map<ze_context_handle_t, IcdL0Context *> contextsMap;

    std::mutex commandQueuesMapMutex;
    std::map<ze_command_queue_handle_t, IcdL0CommandQueue *> commandQueuesMap;

    std::mutex commandListsMapMutex;
    std::map<ze_command_list_handle_t, IcdL0CommandList *> commandListsMap;

    std::mutex modulesMapMutex;
    std::map<ze_module_handle_t, IcdL0Module *> modulesMap;

    std::mutex moduleBuildLogsMapMutex;
    std::map<ze_module_build_log_handle_t, IcdL0ModuleBuildLog *> moduleBuildLogsMap;

    std::mutex kernelsMapMutex;
    std::map<ze_kernel_handle_t, IcdL0Kernel *> kernelsMap;

    std::mutex eventsMapMutex;
    std::map<ze_event_handle_t, IcdL0Event *> eventsMap;

    std::mutex eventPoolsMapMutex;
    std::map<ze_event_pool_handle_t, IcdL0EventPool *> eventPoolsMap;

    std::mutex imagesMapMutex;
    std::map<ze_image_handle_t, IcdL0Image *> imagesMap;

    std::mutex metricGroupsMapMutex;
    std::map<zet_metric_group_handle_t, IcdL0MetricGroup *> metricGroupsMap;

    std::mutex metricsMapMutex;
    std::map<zet_metric_handle_t, IcdL0Metric *> metricsMap;

    std::mutex metricStreamersMapMutex;
    std::map<zet_metric_streamer_handle_t, IcdL0MetricStreamer *> metricStreamersMap;

    std::mutex fencesMapMutex;
    std::map<ze_fence_handle_t, IcdL0Fence *> fencesMap;

    bool zeAffinityMaskPresent = false;
    std::vector<ze_device_handle_t> filteredDevices;
    std::once_flag parseZeAffinityMaskOnce;

    std::mutex lastErrorDescriptionMapMutex;
    std::map<std::thread::id, std::string> lastErrorDescriptionMap;

    Logic::HostptrCopiesReader hostptrCopiesReader;
};

} // namespace LevelZero
} // namespace Client::Icd
} // namespace Cal
