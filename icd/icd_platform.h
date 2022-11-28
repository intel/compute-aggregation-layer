/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/ipc.h"
#include "shared/rpc.h"
#include "shared/shmem_transfer_desc.h"
#include "shared/usm.h"

#include <atomic>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <mutex>
#include <sys/mman.h>
#include <unordered_map>

namespace Cal {
namespace Icd {

class PageFaultManager {
  public:
    enum class Placement : uint32_t {
        DEVICE,
        HOST
    };

    PageFaultManager(Cal::Ipc::Connection &connection) : connection(connection) {
        this->sharedAllocationsEnabled = Cal::Utils::getCalEnvFlag(calSharedAllocations, this->sharedAllocationsEnabled);
        if (!this->sharedAllocationsEnabled) {
            return;
        }

        this->pageFaultHandler = [&](int signal, siginfo_t *info, void *context) {
            this->pageFaultHandlerImpl(signal, info, context);
        };

        struct sigaction pageFaultManagerHandlerSigaction = {};
        pageFaultManagerHandlerSigaction.sa_flags = SA_SIGINFO;
        pageFaultManagerHandlerSigaction.sa_sigaction = pageFaultHandlerWrapper;

        sigaction(SIGSEGV, &pageFaultManagerHandlerSigaction, &this->previousPageFaultHandler);
        this->previousHandlerRestored = false;
    }

    ~PageFaultManager() {
        if (!this->previousHandlerRestored) {
            sigaction(SIGSEGV, &previousPageFaultHandler, nullptr);
        }
    }

    const bool getSharedAllocationsEnabled() const {
        return this->sharedAllocationsEnabled;
    }

    void registerSharedAlloc(void *hostPtr, uint64_t size, Placement placement) {
        if (!this->sharedAllocationsEnabled) {
            return;
        }
        log<Verbosity::debug>("New shared alloc %p", hostPtr);
        std::lock_guard<std::mutex> lock(this->mtx);
        this->sharedAllocMap.emplace(std::piecewise_construct, std::forward_as_tuple(hostPtr), std::forward_as_tuple(size, placement));
        if (placement == Placement::DEVICE) {
            mprotect(hostPtr, size, PROT_NONE);
        }
    }

    void unregisterSharedAlloc(void *hostPtr) {
        if (!this->sharedAllocationsEnabled || hostPtr == nullptr) {
            return;
        }
        log<Verbosity::debug>("Removing shared alloc %p", hostPtr);
        std::lock_guard<std::mutex> lock(this->mtx);
        auto sharedAllocDesc = this->findSharedAlloc(hostPtr);
        if (sharedAllocDesc == this->sharedAllocMap.end()) {
            return;
        }
        mprotect(sharedAllocDesc->first, sharedAllocDesc->second.size, PROT_READ | PROT_WRITE);
        this->sharedAllocMap.erase(sharedAllocDesc->first);
    }

    template <typename... Args>
    void moveAllocationToGpu(Args... args) {
        if (!this->sharedAllocationsEnabled) {
            return;
        }
        std::lock_guard<std::mutex> lock(this->mtx);
        (moveAllocationToGpuImpl(args), ...);
    }

    void moveAllAllocationsToGpu() {
        if (!this->sharedAllocationsEnabled) {
            return;
        }
        std::lock_guard<std::mutex> lock(this->mtx);
        for (auto it = this->sharedAllocMap.begin(); it != this->sharedAllocMap.end(); ++it) {
            this->moveAllocationToGpuImplIt(it);
        }
    }

    static void pageFaultHandlerWrapper(int signal, siginfo_t *info, void *context) {
        pageFaultHandler(signal, info, context);
    }

  protected:
    struct SharedAllocDesc {
        uint64_t size = 0;
        Placement placement = Placement::HOST;
        SharedAllocDesc(uint64_t size, Placement placement) : size(size), placement(placement) {}
    };

    void moveAllocationToGpuImpl(const void *hostPtr) {
        if (hostPtr == nullptr) {
            return;
        }
        auto sharedAllocDesc = this->findSharedAlloc(hostPtr);
        moveAllocationToGpuImplIt(sharedAllocDesc);
    }

    void moveAllocationToGpuImplIt(std::unordered_map<void *, SharedAllocDesc>::iterator &it) {
        if (it == this->sharedAllocMap.end() ||
            it->second.placement == Placement::DEVICE) {
            return;
        }
        log<Verbosity::debug>("Moving to GPU placement alloc %p", it->first);
        mprotect(it->first, it->second.size, PROT_NONE);
        it->second.placement = Placement::DEVICE;
    }

    void pageFaultHandlerImpl(int signal, siginfo_t *info, void *context) {
        auto ptr = info->si_addr;
        auto neoPageFault = this->verifyPageFault(ptr);
        if (neoPageFault) {
            return;
        }

        if (previousPageFaultHandler.sa_flags & SA_SIGINFO) {
            previousPageFaultHandler.sa_sigaction(signal, info, context);
        } else {
            if (previousPageFaultHandler.sa_handler == SIG_DFL) {
                sigaction(SIGSEGV, &previousPageFaultHandler, nullptr);
                previousHandlerRestored = true;
            } else if (previousPageFaultHandler.sa_handler == SIG_IGN) {
                return;
            } else {
                previousPageFaultHandler.sa_handler(signal);
            }
        }
    }

    bool verifyPageFault(void *ptr) {
        std::lock_guard<std::mutex> lock(this->mtx);
        log<Verbosity::debug>("Verifying page fault on address %p", ptr);

        auto sharedAllocDesc = this->findSharedAlloc(ptr);
        if (sharedAllocDesc == this->sharedAllocMap.end()) {
            log<Verbosity::error>("Page fault on non shared memory address: %p", ptr);
            return false;
        }

        if (sharedAllocDesc->second.placement == Placement::HOST) {
            log<Verbosity::debug>("Memory already accessible by host");
            return true;
        }

        {
            auto connectionLock = this->connection.lock();

            Cal::Messages::ReqPageFault reqPageFault(ptr);
            if (this->connection.send(reqPageFault) == false) {
                log<Verbosity::error>("Error while sending page fault request on address %p", ptr);
                return false;
            }

            Cal::Messages::RespPageFault respPageFault;
            if (this->connection.receive(respPageFault) == false || respPageFault.isInvalid()) {
                log<Verbosity::error>("Error while receiving page fault respond on address %p", ptr);
                return false;
            }
        }

        sharedAllocDesc->second.placement = Placement::HOST;
        mprotect(sharedAllocDesc->first, sharedAllocDesc->second.size, PROT_READ | PROT_WRITE);
        log<Verbosity::debug>("Page fault verified successfully on address %p", ptr);
        return true;
    }

    bool previousHandlerRestored = true;
    struct sigaction previousPageFaultHandler = {};
    inline static std::function<void(int signal, siginfo_t *info, void *context)> pageFaultHandler;

    std::unordered_map<void *, SharedAllocDesc> sharedAllocMap;
    std::mutex mtx;

    std::unordered_map<void *, SharedAllocDesc>::iterator findSharedAlloc(const void *hostPtr) {
        return std::find_if(this->sharedAllocMap.begin(), this->sharedAllocMap.end(), [&hostPtr](auto &other) {
            return hostPtr >= other.first && hostPtr < reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(other.first) + other.second.size);
        });
    }

    Cal::Ipc::Connection &connection;
    bool sharedAllocationsEnabled = true;
};

class IcdPlatform {
    using UsmRangeIterator = std::map<const void *, const void *>::iterator;

  public:
    IcdPlatform(Cal::Ipc::ShmemImporter &shmemManager, Cal::Ipc::MallocShmemZeroCopyManager &mallocShmemZeroCopyManager) : shmemManager(shmemManager), mallocShmemZeroCopyManager(mallocShmemZeroCopyManager) {
        auto cpuInfoOpt = cpuInfo.read();
        if (cpuInfoOpt) {
            this->cpuInfo = cpuInfoOpt.value();
            log<Verbosity::debug>("Cpu virtual address bits : %d", this->cpuInfo.virtual_);
        } else {
            log<Verbosity::error>("Could note information about the CPU virtual address bits - will have impact on USM device memory");
        }
        initializeConnection();
        this->pageFaultManager = std::make_unique<Cal::Icd::PageFaultManager>(*this->connection);
    }

    virtual ~IcdPlatform() {
        log<Verbosity::debug>("Performing USM heaps cleanup (num heaps : %zu)", usmHeaps.heaps.size());
        for (const auto &usmHeap : usmHeaps.heaps) {
            if (-1 == Cal::Sys::munmap(usmHeap.base(), usmHeap.size())) {
                log<Verbosity::error>("Failed to munamp USM heap (base : %p, size : %zu)", usmHeap.base(), usmHeap.size());
            }
        }
    }

    bool valid() {
        return nullptr != connection;
    }

    Cal::Rpc::ChannelClient &getRpcChannel() {
        return *rpcChannel;
    }

    Cal::Ipc::Connection &getConnection() {
        return *connection;
    }

    Cal::Ipc::MallocShmemZeroCopyManager &getMallocShmemZeroCopyManager() {
        return mallocShmemZeroCopyManager;
    }

    bool openNewUsmHostOrSharedPointer(void *ctx, void *newUsmAlloc, int shmem_resource, size_t offset_within_resource, size_t aligned_size) {
        if (nullptr == newUsmAlloc) {
            return true;
        }
        auto heapsLock = usmHeaps.lock();
        for (size_t i = 0; i < usmHeaps.heaps.size(); ++i) {
            const auto &usmHeap = this->usmHeaps.heaps[i];
            if (usmHeap.contains(newUsmAlloc)) {
                log<Verbosity::debug>("Opening new USM host/shared allocation %p from heap %d", newUsmAlloc, i);
                Cal::Ipc::RemoteShmem shmemFromServer = {};
                shmemFromServer.id = shmem_resource;
                shmemFromServer.size = aligned_size;
                auto shmem = shmemManager.open(shmemFromServer, newUsmAlloc);
                if (false == shmem.isValid()) {
                    log<Verbosity::error>("Failed to open shmem for USM host/shared allocation %p from heap %d", newUsmAlloc, i);
                    return false;
                }
                usmHeaps.allocations[newUsmAlloc] = Cal::Usm::UsmSharedHostAlloc{ctx, newUsmAlloc, aligned_size, shmem};
                return true;
            }
        }
        log<Verbosity::error>("New USM host/shared allocation does not belong to any known USM heap - overwriting with nullptr");
        return false;
    }

    void *validateNewUsmDevicePointer(void *newUsmAlloc, size_t allocationSize) {
        if (nullptr == newUsmAlloc) {
            return newUsmAlloc;
        }

        if (cpuInfo.isAccessibleByApplication(newUsmAlloc)) {
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
        if (!cpuInfo.isAccessibleByApplication(usmPtr)) {
            return true;
        }

        // Check global pointer list
        auto globalPtrLock = globalPointers.lock();
        if (std::find(globalPointers.ptrList.begin(), globalPointers.ptrList.end(), usmPtr) != globalPointers.ptrList.end()) {
            log<Verbosity::debug>("Found usmPtr %lx in global pointer list. Returning true", usmPtr);
            return true;
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

        if (!cpuInfo.isAccessibleByApplication(usmPtr)) {
            return; // device USM - no local representation
        }

        const auto rangeIt = getUserModeAccessibleUsmDeviceRangeFromMap(usmPtr);
        if (rangeIt != userModeAccessibleUsmDeviceAddresses.end()) {
            userModeAccessibleUsmDeviceAddresses.erase(rangeIt);
            return;
        }

        Cal::Usm::UsmSharedHostAlloc descriptor;
        {
            auto heapsLock = usmHeaps.lock();
            auto it = usmHeaps.allocations.find(usmPtr);
            if (usmHeaps.allocations.end() == it) {
                log<Verbosity::error>("Can't destroy descriptor of usm host/shared ptr:%p - not found in registry");
                return;
            }
            descriptor = it->second;
            usmHeaps.allocations.erase(it);
        }

        Cal::Usm::resetUsmCpuRange(descriptor.ptr, descriptor.alignedSize);
        descriptor.shmem.ptr = nullptr;
        shmemManager.release(descriptor.shmem);
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
            auto usmHeapsLock = usmHeaps.lock();
            for (int i = 0; i < count; ++i) {
                if (result[i]) {
                    continue; // already confirmed as device USM
                }
                if (isUsmHostOrSharedUnsafe(ptr[i])) {
                    result[i] = true;
                } else {
                    allUsm = false;
                }
            }
        }
        return allUsm;
    }

    bool isUsmHostOrShared(const void *ptr) {
        auto usmHeapsLock = usmHeaps.lock();
        return isUsmHostOrSharedUnsafe(ptr);
    }

    bool isZeroCopyForMallocShmemEnabled() const {
        return allowedToUseZeroCopyForMallocShmem;
    }

    bool recordGlobalPointer(void *ptr) {
        log<Verbosity::debug>("Adding global pointer:%lx to global pointer cache to list", ptr);
        auto globalPtrLock = globalPointers.lock();
        globalPointers.ptrList.push_back(ptr);
        return true;
    }

    bool removeGlobalPointer(void *ptr) {
        log<Verbosity::debug>("Removing global pointer:%lx from global pointer cache", ptr);
        auto globalPtrLock = globalPointers.lock();
        auto it = std::find(globalPointers.ptrList.begin(), globalPointers.ptrList.end(), ptr);
        if (it == globalPointers.ptrList.end()) {
            log<Verbosity::debug>("Pointer:%lx not found in global pointer cache ", ptr);
            return true;
        }

        globalPointers.ptrList.erase(it);
        return true;
    }

    bool writeRequiredMemory(const std::vector<Cal::Rpc::ShmemTransferDesc> &transferDescs) {
        for (const auto &transfer : transferDescs) {
            Cal::Ipc::RemoteShmem remoteShmem{};
            remoteShmem.id = transfer.shmemId;
            remoteShmem.size = transfer.underlyingSize;

            auto shmem = shmemManager.open(remoteShmem, nullptr);
            if (!shmem.isValid()) {
                log<Verbosity::error>("Cannot map shared memory to perform transfer from client to service!");
                return false;
            }

            const auto destinationAddress = reinterpret_cast<uintptr_t>(shmem.ptr) + transfer.offsetFromMapping;
            const auto source = reinterpret_cast<const void *>(transfer.transferStart);
            auto destination = reinterpret_cast<void *>(destinationAddress);

            std::memcpy(destination, source, transfer.bytesCountToCopy);
            shmemManager.release(shmem);
        }

        return true;
    }

    bool readRequiredMemory(const std::vector<Cal::Rpc::ShmemTransferDesc> &transferDescs) {
        for (const auto &transfer : transferDescs) {
            Cal::Ipc::RemoteShmem remoteShmem{};
            remoteShmem.id = transfer.shmemId;
            remoteShmem.size = transfer.underlyingSize;

            auto shmem = shmemManager.open(remoteShmem, nullptr);
            if (!shmem.isValid()) {
                log<Verbosity::error>("Cannot map shared memory to perform transfer from service to client!");
                return false;
            }

            const auto sourceAddress = reinterpret_cast<uintptr_t>(shmem.ptr) + transfer.offsetFromMapping;
            const auto source = reinterpret_cast<const void *>(sourceAddress);
            const auto destination = reinterpret_cast<void *>(transfer.transferStart);

            std::memcpy(destination, source, transfer.bytesCountToCopy);
            shmemManager.release(shmem);
        }

        return true;
    }

    PageFaultManager *getPageFaultManager() {
        return this->pageFaultManager.get();
    }

  protected:
    Cal::Utils::CpuInfo cpuInfo;

    Cal::Ipc::ShmemImporter &shmemManager;
    Cal::Ipc::MallocShmemZeroCopyManager &mallocShmemZeroCopyManager;
    bool allowedToUseZeroCopyForMallocShmem = false;
    std::unique_ptr<Cal::Icd::PageFaultManager> pageFaultManager;
    std::unique_ptr<Cal::Ipc::Connection> connection;
    std::unique_ptr<Cal::Rpc::ChannelClient> rpcChannel;
    std::map<const void *, const void *> userModeAccessibleUsmDeviceAddresses;
    std::string socketPath;

    struct {
        std::unique_lock<std::mutex> lock() { return std::unique_lock<std::mutex>(criticalSection); }
        std::mutex criticalSection;
        std::vector<void *> ptrList{};
    } globalPointers;

    struct {
        std::unique_lock<std::mutex> lock() { return std::unique_lock<std::mutex>(criticalSection); }
        std::mutex criticalSection;
        std::unordered_map<void *, Cal::Usm::UsmSharedHostAlloc> allocations;
        std::vector<Cal::Utils::AddressRange> heaps;
    } usmHeaps;

    std::unique_ptr<Cal::Ipc::ClientConnectionFactory> createConnectionFactory() {
        log<Verbosity::debug>("Creating connection listener based on local named socket");
        return std::make_unique<Cal::Ipc::NamedSocketClientConnectionFactory>();
    }

    void initializeConnection();

    bool isUsmHostOrSharedUnsafe(const void *ptr) {
        for (auto heap : usmHeaps.heaps) {
            if (heap.contains({ptr})) {
                return true;
            }
        }
        return false;
    }

    const char *getSocketPath();
};

} // namespace Icd
} // namespace Cal
