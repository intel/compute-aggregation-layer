/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/icd_global_state.h"
#include "shared/api_types.h"
#include "shared/ipc.h"
#include "shared/shmem_transfer_desc.h"
#include "shared/usm.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <mutex>
#include <sys/mman.h>
#include <unordered_map>

namespace Cal::Rpc {
class ChannelClient;
} // namespace Cal::Rpc

namespace Cal {
namespace Icd {

class PageFaultManager;

struct UsmSharedHostAlloc {
    void *ctx = nullptr;
    void *ptr = nullptr;
    size_t alignedSize = 0;
    Cal::Ipc::MmappedShmemSubAllocationT shmem;

    void (*gpuDestructor)(void *ctx, void *ptr) = nullptr;
};

class IcdPlatform {
    using UsmRangeIterator = std::map<const void *, const void *>::iterator;

  public:
    IcdPlatform(Cal::Icd::IcdGlobalState &globalState, Cal::ApiType apiType)
        : globalState(globalState), apiType(apiType) {
    }

    virtual ~IcdPlatform() {
    }

    Cal::Rpc::ChannelClient &getRpcChannel() const {
        return globalState.getRpcChannel();
    }

    Cal::Ipc::Connection &getConnection() const {
        return globalState.getConnection();
    }

    Cal::Ipc::MallocShmemZeroCopyManager &getMallocShmemZeroCopyManager() {
        return globalState.getMallocShmemZeroCopyManager();
    }

    bool openNewUsmHostOrSharedPointer(void *ctx, void *assignedUsmPtr, int shmemResource, size_t offsetWithinResource, size_t size) {
        if (nullptr == assignedUsmPtr) {
            return true;
        }

        const auto &usmHeap = globalState.getInitialUsmHeap();
        if (usmHeap.contains(assignedUsmPtr)) {
            log<Verbosity::debug>("Opening new USM host/shared allocation %p ");
            auto shmem = globalState.getUsmShmemImporter().open(shmemResource, offsetWithinResource, size, assignedUsmPtr);
            if (false == shmem.isValid()) {
                log<Verbosity::error>("Failed to open shmem for USM host/shared allocation %p using shmemId %d and offset %zu", assignedUsmPtr, shmemResource, offsetWithinResource);
                return false;
            }
            auto usmAllocsLock = usmAllocs.lock();
            (*usmAllocs)[assignedUsmPtr] = UsmSharedHostAlloc{ctx, assignedUsmPtr, size, shmem};
            return true;
        }
        log<Verbosity::error>("New USM host/shared allocation does not belong to any known USM heap - overwriting with nullptr");
        return false;
    }

    void *validateNewUsmDevicePointer(void *newUsmAlloc, size_t allocationSize) {
        if (nullptr == newUsmAlloc) {
            return newUsmAlloc;
        }

        if (globalState.getCpuInfo().isAccessibleByApplication(newUsmAlloc)) {
            log<Verbosity::debug>("New USM device allocation has address accessible by the CPU user mode. Trying to store it in internal map.");

            const auto rangeBegin = reinterpret_cast<std::uintptr_t>(newUsmAlloc);
            const auto rangeEnd = reinterpret_cast<void *>(rangeBegin + allocationSize);
            const auto emplaceResult = userModeAccessibleUsmDeviceAddresses.emplace(newUsmAlloc, rangeEnd);

            if (!emplaceResult.second) {
                log<Verbosity::error>("Couldn't insert USM device allocation to internal map! Returning nullptr.");
                return nullptr;
            }
        }
        return newUsmAlloc;
    }

    bool isDeviceUsm(const void *usmPtr) {
        if (!globalState.getCpuInfo().isAccessibleByApplication(usmPtr)) {
            return true;
        }

        // Check global pointer list
        auto globalPtrLock = globalPointers.lock();
        for (auto &pointersEntry : *globalPointers) {
            auto &pointers = pointersEntry.second;
            if (std::find(pointers.begin(), pointers.end(), usmPtr) != pointers.end()) {
                log<Verbosity::debug>("Found usmPtr %lx in global pointer list. Returning true", usmPtr);
                return true;
            }
        }

        return getUserModeAccessibleUsmDeviceRangeFromMap(usmPtr) != userModeAccessibleUsmDeviceAddresses.end();
    }

    UsmRangeIterator getUserModeAccessibleUsmDeviceRangeFromMap(const void *usmPtr) {
        if (userModeAccessibleUsmDeviceAddresses.empty()) {
            return userModeAccessibleUsmDeviceAddresses.end();
        }

        // We are looking for the first greater or equal beginning address.
        auto rangeIt = userModeAccessibleUsmDeviceAddresses.lower_bound(usmPtr);
        if (rangeIt == userModeAccessibleUsmDeviceAddresses.end() || rangeIt->first != usmPtr) {
            // usmPtr may point inside the range and be greater than its beginning. If possible check earlier range.
            if (rangeIt != userModeAccessibleUsmDeviceAddresses.begin()) {
                std::advance(rangeIt, -1);
            } else {
                return userModeAccessibleUsmDeviceAddresses.end();
            }
        }

        std::less isLess{};
        std::less_equal isLessEqual{};
        const auto &[rangeBegin, rangeEnd] = *rangeIt;

        if (isLessEqual(rangeBegin, usmPtr) && isLess(usmPtr, rangeEnd)) {
            return rangeIt;
        } else {
            return userModeAccessibleUsmDeviceAddresses.end();
        }
    }

    void destroyUsmDescriptor(void *usmPtr) {
        if (nullptr == usmPtr) {
            return;
        }

        if (!globalState.getCpuInfo().isAccessibleByApplication(usmPtr)) {
            return; // device USM - no local representation
        }

        const auto rangeIt = getUserModeAccessibleUsmDeviceRangeFromMap(usmPtr);
        if (rangeIt != userModeAccessibleUsmDeviceAddresses.end()) {
            userModeAccessibleUsmDeviceAddresses.erase(rangeIt);
            return;
        }

        UsmSharedHostAlloc descriptor;
        {
            auto heapsLock = usmAllocs.lock();
            auto it = usmAllocs->find(usmPtr);
            if (usmAllocs->end() == it) {
                log<Verbosity::error>("Can't destroy descriptor of usm host/shared ptr:%p - not found in registry");
                return;
            }
            descriptor = it->second;
            usmAllocs->erase(it);
        }

        globalState.getUsmShmemImporter().release(descriptor.shmem);
    }

    bool areUsm(int count, const void *ptr[], bool result[]) {
        bool allDeviceUsm = true;
        for (int i = 0; i < count; ++i) {
            if (!ptr[i] || !isDeviceUsm(ptr[i])) {
                allDeviceUsm = false;
            } else {
                result[i] = true;
            }
        }
        if (allDeviceUsm) {
            return true;
        }

        bool allUsm = true;
        if (false == allDeviceUsm) {
            for (int i = 0; i < count; ++i) {
                if (result[i]) {
                    continue; // already confirmed as device USM
                }
                if (globalState.getInitialUsmHeap().contains(ptr[i])) {
                    result[i] = true;
                } else {
                    allUsm = false;
                }
            }
        }
        return allUsm;
    }

    bool isUsmHostOrShared(const void *ptr) {
        return globalState.getInitialUsmHeap().contains(ptr);
    }

    bool isZeroCopyForMallocShmemEnabled() const {
        return globalState.isZeroCopyForMallocShmemEnabled();
    }

    bool recordGlobalPointer(void *handle, void *ptr) {
        if (!handle || !ptr) {
            log<Verbosity::debug>("Could not record global pointer! Handle or pointer is nullptr!");
            return false;
        }

        log<Verbosity::debug>("For handle (%p) adding global pointer (%p) to global pointer lookup!", handle, ptr);

        auto globalPtrLock = globalPointers.lock();
        auto &pointers = (*globalPointers)[handle];

        const auto pointerAlreadyRegistered = std::find(pointers.begin(), pointers.end(), ptr) != pointers.end();
        if (!pointerAlreadyRegistered) {
            pointers.push_back(ptr);
        }

        return true;
    }

    bool removeGlobalPointers(void *handle) {
        log<Verbosity::debug>("Removing global pointers for handle (%p) from global pointer lookup!", handle);

        auto globalPtrLock = globalPointers.lock();
        globalPointers->erase(handle);

        return true;
    }

    bool writeRequiredMemory(const std::vector<Cal::Rpc::ShmemTransferDesc> &transferDescs) {
        for (const auto &transfer : transferDescs) {
            auto shmem = globalState.getGlobalShmemImporter().open(transfer.shmemId, transfer.underlyingSize, nullptr);
            if (!shmem.isValid()) {
                log<Verbosity::error>("Cannot map shared memory to perform transfer from client to service!");
                return false;
            }

            const auto destinationAddress = reinterpret_cast<uintptr_t>(shmem.getMmappedPtr()) + transfer.offsetFromMapping;
            const auto source = reinterpret_cast<const void *>(transfer.transferStart);
            auto destination = reinterpret_cast<void *>(destinationAddress);

            std::memcpy(destination, source, transfer.bytesCountToCopy);
            globalState.getGlobalShmemImporter().release(shmem);
        }

        return true;
    }

    bool readRequiredMemory(const std::vector<Cal::Rpc::ShmemTransferDesc> &transferDescs) {
        for (const auto &transfer : transferDescs) {
            auto shmem = globalState.getGlobalShmemImporter().open(transfer.shmemId, transfer.underlyingSize, nullptr);
            if (!shmem.isValid()) {
                log<Verbosity::error>("Cannot map shared memory to perform transfer from service to client!");
                return false;
            }

            const auto sourceAddress = reinterpret_cast<uintptr_t>(shmem.getMmappedPtr()) + transfer.offsetFromMapping;
            const auto source = reinterpret_cast<const void *>(sourceAddress);
            const auto destination = reinterpret_cast<void *>(transfer.transferStart);

            std::memcpy(destination, source, transfer.bytesCountToCopy);
            globalState.getGlobalShmemImporter().release(shmem);
        }

        return true;
    }

    PageFaultManager &getPageFaultManager() {
        return globalState.getPageFaultManager();
    }

  protected:
    Cal::Icd::IcdGlobalState &globalState;
    const Cal::ApiType apiType;
    std::map<const void *, const void *> userModeAccessibleUsmDeviceAddresses;
    Cal::Utils::Lockable<std::unordered_map<void *, std::vector<void *>>> globalPointers;
    Cal::Utils::Lockable<std::unordered_map<void *, UsmSharedHostAlloc>> usmAllocs;
};

} // namespace Icd
} // namespace Cal
