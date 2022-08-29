/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/icd_global_state.h"
#include "icd/icd_platform.h"
#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"
#include "shared/ipc.h"
#include "shared/ref_counted.h"
#include "shared/rpc.h"
#include "shared/shmem_transfer_desc.h"
#include "shared/usm.h"

#include <cstdlib>
#include <limits>
#include <optional>
#include <string>

extern ze_dditable_t l0Dddi;
extern ze_api_version_t supportedL0ApiVersion;

struct l0_icd_base {
    ze_dditable_t *dt = &l0Dddi;
};

template <typename LocalObjectType>
struct l0_icd_base_mapped : l0_icd_base {
    using LocalObjectT = LocalObjectType;

    LocalObjectT *asLocalObject() {
        ensureIsLocalObject();
        return static_cast<LocalObjectT *>(this);
    }

    const LocalObjectT *asLocalObject() const {
        ensureIsLocalObject();
        return static_cast<LocalObjectT *>(this);
    }

    void ensureIsLocalObject() {
        if (this->isRemote()) {
            log<Verbosity::critical>("Attempted to use remote object as local object");
            std::abort();
        }
    }

    bool isLocal() const {
        return this->dt == &l0Dddi;
    }

    bool isRemote() const {
        return false == this->isLocal();
    }
};

namespace Cal {
namespace Icd {
namespace LevelZero {

class IcdL0Platform;
class IcdL0Module;
class IcdL0CommandList;
class IcdL0Device;
struct IcdL0Context;
struct IcdL0CommandQueue;
struct IcdL0ModuleBuildLog;
struct IcdL0Kernel;
struct IcdL0EventPool;
struct IcdL0Event;
struct IcdL0Fence;

} // namespace LevelZero
} // namespace Icd
} // namespace Cal

struct _ze_driver_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Platform> {};
struct _ze_device_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Device> {};
struct _ze_context_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Context> {};
struct _ze_command_queue_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0CommandQueue> {};
struct _ze_command_list_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0CommandList> {};
struct _ze_module_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Module> {};
struct _ze_module_build_log_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0ModuleBuildLog> {};
struct _ze_kernel_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Kernel> {};
struct _ze_event_pool_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0EventPool> {};
struct _ze_event_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Event> {};
struct _ze_fence_handle_t : l0_icd_base_mapped<Cal::Icd::LevelZero::IcdL0Fence> {};

namespace Cal {
namespace Icd {
namespace LevelZero {

ze_result_t zeCommandQueueExecuteCommandLists(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t hFence);
ze_result_t zeDriverGet(uint32_t *pCount, ze_driver_handle_t *phDrivers);
ze_result_t zeInit(ze_init_flags_t flags);
ze_result_t zeMemAllocHost(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, void **pptr);
ze_result_t zeMemAllocShared(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void **pptr);

template <typename RemoteL0ObjectT, typename LocalL0ObjectT>
void objectCleanup(void *remote, void *local);

struct IcdL0TypePrinter {
    template <typename ZeObjT>
    static const char *getObjectTypeAsStr() {
        if constexpr (std::is_same_v<ZeObjT, ze_driver_handle_t>) {
            return "ze_driver_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_driver_handle_t>) {
            return "_ze_driver_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_device_handle_t>) {
            return "ze_device_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_device_handle_t>) {
            return "_ze_device_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_context_handle_t>) {
            return "ze_context_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_context_handle_t>) {
            return "_ze_context_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_command_queue_handle_t>) {
            return "ze_command_queue_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_command_queue_handle_t>) {
            return "_ze_command_queue_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_command_list_handle_t>) {
            return "ze_command_list_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_command_list_handle_t>) {
            return "_ze_command_list_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_module_handle_t>) {
            return "ze_module_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_module_handle_t>) {
            return "_ze_module_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_module_build_log_handle_t>) {
            return "ze_module_build_log_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_module_build_log_handle_t>) {
            return "_ze_module_build_log_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_kernel_handle_t>) {
            return "ze_kernel_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_kernel_handle_t>) {
            return "_ze_kernel_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_event_pool_handle_t>) {
            return "ze_event_pool_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_event_pool_handle_t>) {
            return "_ze_event_pool_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_event_handle_t>) {
            return "ze_event_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_event_handle_t>) {
            return "_ze_event_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, ze_fence_handle_t>) {
            return "ze_fence_handle_t";
        }

        if constexpr (std::is_same_v<ZeObjT, _ze_fence_handle_t>) {
            return "_ze_fence_handle_t";
        }

        return "unknown";
    }
};

class IcdL0Device : public Cal::Shared::RefCountedWithParent<_ze_device_handle_t, IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    bool patchDeviceName(ze_device_properties_t &properties);
};

struct IcdL0Context : Cal::Shared::RefCountedWithParent<_ze_context_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0CommandQueue : Cal::Shared::RefCountedWithParent<_ze_command_queue_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

class IcdL0CommandList : public Cal::Shared::RefCountedWithParent<_ze_command_list_handle_t, IcdL0TypePrinter> {
  protected:
    using ChunkEntry = Cal::Rpc::MemChunk;

  public:
    using RefCountedWithParent::RefCountedWithParent;

    void registerMemoryToWrite(const void *srcPtr, size_t srcSize);

    static bool rangesOverlap(const void *srcPtr, const void *dstPtr, size_t size);
    static bool rangesOverlap(const void *srcPtr, size_t srcSize, const void *dstPtr, size_t dstSize);

    const std::vector<ChunkEntry> &getMemoryToWrite() const {
        return memoryToWrite;
    }

    void clearRequiredMemoryTransfers() {
        memoryToWrite.clear();
    }

  protected:
    ChunkEntry mergeChunks(const ChunkEntry &first, const ChunkEntry &second);

    std::vector<ChunkEntry> memoryToWrite{};
};

class IcdL0Module : public Cal::Shared::RefCountedWithParent<_ze_module_handle_t, IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    ze_result_t getKernelNames(uint32_t *pCount, const char **pNames);
    ze_result_t getKernelNamesCount(uint32_t *pCount);

  private:
    bool queryKernelNames();
    void populateKernelNames(const std::vector<char> &buffer);

    bool wasKernelNamesQueried{false};
    std::vector<std::string> kernelNames{};
};

struct IcdL0ModuleBuildLog : Cal::Shared::RefCountedWithParent<_ze_module_build_log_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0Kernel : Cal::Shared::RefCountedWithParent<_ze_kernel_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0EventPool : Cal::Shared::RefCountedWithParent<_ze_event_pool_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0Event : Cal::Shared::RefCountedWithParent<_ze_event_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdL0Fence : Cal::Shared::RefCountedWithParent<_ze_fence_handle_t, IcdL0TypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

class IcdL0Platform : public Cal::Icd::IcdPlatform, public _ze_driver_handle_t {
  public:
    using IcdPlatform::IcdPlatform;

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

    ze_command_queue_handle_t translateNewRemoteObjectToLocalObject(ze_command_queue_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0CommandQueue>(remoteHandle, static_cast<ze_command_queue_handle_t>(nullptr), commandQueuesMap, commandQueuesMapMutex);
    }

    void removeObjectFromMap(ze_command_queue_handle_t remoteHandle, IcdL0CommandQueue *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, commandQueuesMap, commandQueuesMapMutex);
    }

    ze_command_list_handle_t translateNewRemoteObjectToLocalObject(ze_command_list_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0CommandList>(remoteHandle, static_cast<ze_command_list_handle_t>(nullptr), commandListsMap, commandListsMapMutex);
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

    ze_fence_handle_t translateNewRemoteObjectToLocalObject(ze_fence_handle_t remoteHandle) {
        return translateNewRemoteObjectToLocalObject<IcdL0Fence>(remoteHandle, static_cast<ze_fence_handle_t>(nullptr), fencesMap, fencesMapMutex);
    }

    void removeObjectFromMap(ze_fence_handle_t remoteHandle, IcdL0Fence *localHandle) {
        removeObjectFromMap(remoteHandle, localHandle, fencesMap, fencesMapMutex);
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
            log<Verbosity::bloat>("Translating %s %p to %p", IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, it->second);
            return it->second;
        }

        auto localHandle = new LocalT{remoteHandle,
                                      Cal::Shared::SingleReference::wrap(parent ? parent->asLocalObject() : nullptr),
                                      &objectCleanup<RemoteT, LocalT *>};
        mapping[remoteHandle] = localHandle;

        log<Verbosity::bloat>("Translating %s %p to %p", IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, localHandle);
        return localHandle;
    }

    template <typename RemoteT, typename LocalT, typename MapT>
    void removeObjectFromMap(RemoteT remoteHandle, LocalT localHandle, MapT &mapping, std::mutex &mapMutex) {
        std::lock_guard lock{mapMutex};
        const auto it = mapping.find(remoteHandle);
        if (it == mapping.end()) {
            log<Verbosity::bloat>("Cannot remove mapping of %s [%p to %p]", IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, localHandle);
            return;
        }

        mapping.erase(it);
        log<Verbosity::bloat>("Removed mapping of %s [%p to %p]", IcdL0TypePrinter::getObjectTypeAsStr<RemoteT>(), remoteHandle, localHandle);
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

    std::mutex fencesMapMutex;
    std::map<ze_fence_handle_t, IcdL0Fence *> fencesMap;
};

} // namespace LevelZero
} // namespace Icd
} // namespace Cal