/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/icd_global_state.h"
#include "icd/icd_platform.h"
#include "icd/level_zero/api_customization/icd_level_zero_api.h"
#include "icd/level_zero/api_type_wrapper/handles_definitions.h"
#include "icd/level_zero/api_type_wrapper/module_wrapper.h"
#include "icd/level_zero/logic/properties_cache.h"
#include "icd/level_zero/logic/types_printer.h"
#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"
#include "shared/ref_counted.h"
#include "shared/shmem_transfer_desc.h"

#include <atomic>
#include <cstdlib>
#include <limits>
#include <mutex>
#include <optional>
#include <string>
#include <utility>

namespace Cal {
namespace Icd {
namespace LevelZero {

template <typename RemoteL0ObjectT, typename LocalL0ObjectT>
void objectCleanup(void *remote, void *local);

class IcdL0Device : public Cal::Shared::RefCountedWithParent<_ze_device_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    bool patchDeviceName(ze_device_properties_t &properties);
    void addSubDeviceToFilter(uint32_t subDeviceIndex);
    bool isZeAffinityMaskPresent();
    const std::vector<ze_device_handle_t> &getFilteredDevices() const { return filteredDevices; };

    Logic::PropertiesCache::VectorTuple<ze_device_properties_t,
                                        ze_device_compute_properties_t,
                                        ze_device_module_properties_t,
                                        ze_device_memory_access_properties_t,
                                        ze_device_image_properties_t,
                                        ze_device_external_memory_properties_t,
                                        ze_command_queue_group_properties_t,
                                        ze_device_cache_properties_t,
                                        ze_device_memory_properties_t>
        properties;

    struct PropertiesCount {
        uint32_t commandQueueGroupCount = 0;
        uint32_t cacheCount = 0;
        uint32_t memoryCount = 0;
    } propertiesCount;

    template <typename T>
    constexpr uint32_t &getPropertiesCount() {
        if constexpr (std::is_same_v<T, ze_command_queue_group_properties_t>) {
            return this->propertiesCount.commandQueueGroupCount;
        }
        if constexpr (std::is_same_v<T, ze_device_cache_properties_t>) {
            return this->propertiesCount.cacheCount;
        }
        if constexpr (std::is_same_v<T, ze_device_memory_properties_t>) {
            return this->propertiesCount.memoryCount;
        }
        return Logic::PropertiesCache::defaultPropertiesCount;
    }

  private:
    bool zeAffinityMaskPresent = false;
    std::vector<bool> selectedDevices;
    std::vector<ze_device_handle_t> filteredDevices;
    std::once_flag parseZeAffinityMaskOnce;
};

struct IcdL0Context : Cal::Shared::RefCountedWithParent<_ze_context_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;

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
};

struct IcdL0Kernel : Cal::Shared::RefCountedWithParent<_ze_kernel_handle_t, Logic::IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
    KernelArgCache zeKernelSetArgumentValueCache;

    Logic::PropertiesCache::VectorTuple<ze_kernel_properties_t> properties;

    template <typename T>
    constexpr uint32_t &getPropertiesCount() {
        return Logic::PropertiesCache::defaultPropertiesCount;
    }

    void storeKernelArg(const void *argValue, uint32_t argNum) {
        if (allocationsToMigrate.size() < argNum + 1) {
            allocationsToMigrate.resize(argNum + 1);
        }
        allocationsToMigrate[argNum] = argValue;
    }
    bool sharedIndirectAccessSet = false;
    std::vector<const void *> allocationsToMigrate;
};

class IcdL0CommandList : public Cal::Shared::RefCountedWithParent<_ze_command_list_handle_t, Logic::IcdL0TypePrinter> {
  protected:
    using ChunkEntry = Cal::Rpc::MemChunk;

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

    void registerMemoryToWrite(const void *srcPtr, size_t srcSize);
    void registerMemoryToRead(const void *dstPtr, size_t dstSize);

    static bool rangesOverlap(const void *srcPtr, const void *dstPtr, size_t size);
    static bool rangesOverlap(const void *srcPtr, size_t srcSize, const void *dstPtr, size_t dstSize);

    ze_result_t readRequiredMemory();
    ze_result_t writeRequiredMemory();

    void clearRequiredMemoryTransfers() {
        {
            std::lock_guard lock{memoryToWriteMutex};
            memoryToWrite.clear();
        }

        {
            std::lock_guard lock{memoryToReadMutex};
            memoryToRead.clear();
        }
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

  protected:
    friend IcdL0Platform;

    void setCommandListType(CommandListType type) {
        commandListType = type;
    }

    void moveSharedAllocationsToGpuImpl(const void *ptr);

    void registerMemoryToContainer(const void *ptr, size_t size, std::vector<ChunkEntry> &memory);
    ChunkEntry mergeChunks(const ChunkEntry &first, const ChunkEntry &second);

    CommandListType commandListType{CommandListType::Regular};
    std::mutex memoryToWriteMutex{};
    std::mutex memoryToReadMutex{};
    std::vector<ChunkEntry> memoryToWrite{};
    std::vector<ChunkEntry> memoryToRead{};

    std::vector<const void *> usedAllocations{};
};

class IcdL0CommandQueue : public Cal::Shared::RefCountedWithParent<_ze_command_queue_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    ze_result_t readMemoryRequiredByCurrentlyExecutedCommandLists();
    void storeExecutedCommandListsPointers(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists);
    void removeFromExecutedCommandLists(const std::vector<ze_command_list_handle_t> &commandListsToRemove);

    void clearExecutedCommandListsPointers() {
        currentlyExecutedCommandLists.clear();
    }

    [[nodiscard]] std::unique_lock<std::mutex> lock() {
        return std::unique_lock<std::mutex>{queueMutex};
    }

    void moveSharedAllocationsToGpu(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists);

    ze_command_queue_mode_t getCommandQueueMode();

  private:
    friend IcdL0Platform;
    void setCommandQueueType(ze_command_queue_mode_t mode) {
        this->mode = mode;
    }

    std::mutex queueMutex{};
    std::vector<ze_command_list_handle_t> currentlyExecutedCommandLists{};
    ze_command_queue_mode_t mode{};
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
        STATE_SIGNALED = 0u,
        STATE_CLEARED
    } state = STATE_CLEARED;
    ze_kernel_timestamp_result_t timestamp = {};

    void setAllowIcdState(const ze_command_list_handle_t commandList) {
        this->allowIcdState &= static_cast<IcdL0CommandList *>(commandList)->isImmediate();
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

class IcdL0Fence : public Cal::Shared::RefCountedWithParent<_ze_fence_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    std::vector<ze_command_list_handle_t> clearExecutedCommandListsPointers();
    void storeExecutedCommandListsPointers(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists);

    IcdL0CommandQueue *peekQueue() {
        return icdL0Queue;
    }

  private:
    void setCommandQueue(IcdL0CommandQueue *queue) {
        icdL0Queue = queue;
    }

    friend IcdL0Platform;

    IcdL0CommandQueue *icdL0Queue{};

    std::mutex currentlyExecutedCommandListsMutex{};
    std::vector<ze_command_list_handle_t> currentlyExecutedCommandLists{};
};

class IcdL0Platform : public Cal::Icd::IcdPlatform, public _ze_driver_handle_t {
  public:
    IcdL0Platform(Cal::Icd::IcdGlobalState &globalState)
        : IcdPlatform(globalState, Cal::ApiType::LevelZero) {}

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

    ze_fence_handle_t translateNewRemoteObjectToLocalObject(ze_fence_handle_t remoteHandle, ze_command_queue_handle_t queueHandle) {
        auto fence = translateNewRemoteObjectToLocalObject<IcdL0Fence>(remoteHandle, static_cast<ze_fence_handle_t>(nullptr), fencesMap, fencesMapMutex);
        if (!fence) {
            return nullptr;
        }

        auto icdFence = static_cast<IcdL0Fence *>(fence);
        icdFence->setCommandQueue(static_cast<IcdL0CommandQueue *>(queueHandle));

        return fence;
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

    void *openUsmDevicePointerFromIpcHandle(ze_context_handle_t context, void *newUsmPtr) {
        if (!newUsmPtr || !globalState.getCpuInfo().isAccessibleByApplication(newUsmPtr)) {
            return newUsmPtr;
        }

        log<Verbosity::critical>("Service returned an address, which is not USM device! Aborting...");
        std::abort();

        return nullptr;
    }

    Logic::PropertiesCache::VectorTuple<ze_driver_properties_t,
                                        ze_driver_ipc_properties_t,
                                        ze_driver_extension_properties_t>
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

    std::mutex fencesMapMutex;
    std::map<ze_fence_handle_t, IcdL0Fence *> fencesMap;

    bool zeAffinityMaskPresent = false;
    std::vector<ze_device_handle_t> filteredDevices;
    std::once_flag parseZeAffinityMaskOnce;
};

} // namespace LevelZero
} // namespace Icd
} // namespace Cal
