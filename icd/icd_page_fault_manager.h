/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/control_messages.h"
#include "shared/ipc.h"

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <limits>
#include <mutex>
#include <unordered_map>

namespace Cal::Icd {

class PageFaultManager {
  public:
    enum class Placement : uint32_t {
        DEVICE,
        HOST
    };

    PageFaultManager(Cal::Ipc::Connection &connection)
        : PageFaultManager(connection, Cal::Utils::getCalEnvFlag(calSharedAllocations, true)) {}

    PageFaultManager(Cal::Ipc::Connection &connection, bool sharedAllocationsEnabled) : connection(connection) {
        this->sharedAllocationsEnabled = sharedAllocationsEnabled;
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
        this->sharedAllocVec.emplace_back(hostPtr, size, placement);
        if (placement == Placement::DEVICE) {
            Cal::Sys::mprotect(hostPtr, size, PROT_NONE);
        }
    }

    void unregisterSharedAlloc(void *hostPtr) {
        if (!this->sharedAllocationsEnabled || hostPtr == nullptr) {
            return;
        }
        log<Verbosity::debug>("Removing shared alloc %p", hostPtr);
        std::lock_guard<std::mutex> lock(this->mtx);
        auto sharedAllocDesc = this->findSharedAlloc(hostPtr);
        if (sharedAllocDesc == this->sharedAllocVec.end()) {
            return;
        }
        Cal::Sys::mprotect(sharedAllocDesc->ptr, sharedAllocDesc->size, PROT_READ | PROT_WRITE);
        this->sharedAllocVec.erase(sharedAllocDesc);
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
        for (auto it = this->sharedAllocVec.begin(); it != this->sharedAllocVec.end(); ++it) {
            this->moveAllocationToGpuImplIt(it);
        }
    }

    bool isAllocShared(const void *ptr) {
        auto it = this->findSharedAlloc(ptr);
        return it != this->sharedAllocVec.end();
    }

    static void pageFaultHandlerWrapper(int signal, siginfo_t *info, void *context) {
        pageFaultHandler(signal, info, context);
    }

  protected:
    struct SharedAllocDesc {
        void *ptr = nullptr;
        uint64_t size = 0;
        Placement placement = Placement::HOST;

        SharedAllocDesc(void *ptr, uint64_t size, Placement placement) : ptr(ptr), size(size), placement(placement) {}
    };

    void moveAllocationToGpuImpl(const void *hostPtr) {
        if (hostPtr == nullptr) {
            return;
        }
        auto sharedAllocDesc = this->findSharedAlloc(hostPtr);
        moveAllocationToGpuImplIt(sharedAllocDesc);
    }

    void moveAllocationToGpuImplIt(std::vector<SharedAllocDesc>::iterator &it) {
        if (it == this->sharedAllocVec.end() ||
            it->placement == Placement::DEVICE) {
            return;
        }
        log<Verbosity::debug>("Moving to GPU placement alloc %p", it->ptr);
        Cal::Sys::mprotect(it->ptr, it->size, PROT_NONE);
        it->placement = Placement::DEVICE;
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
        if (sharedAllocDesc == this->sharedAllocVec.end()) {
            log<Verbosity::error>("Page fault on non shared memory address: %p", ptr);
            return false;
        }

        if (sharedAllocDesc->placement == Placement::HOST) {
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

        sharedAllocDesc->placement = Placement::HOST;
        Cal::Sys::mprotect(sharedAllocDesc->ptr, sharedAllocDesc->size, PROT_READ | PROT_WRITE);
        log<Verbosity::debug>("Page fault verified successfully on address %p", ptr);
        return true;
    }

    bool previousHandlerRestored = true;
    struct sigaction previousPageFaultHandler = {};
    inline static std::function<void(int signal, siginfo_t *info, void *context)> pageFaultHandler;

    std::vector<SharedAllocDesc> sharedAllocVec;
    std::mutex mtx;

    std::vector<SharedAllocDesc>::iterator findSharedAlloc(const void *hostPtr) {
        return std::find_if(this->sharedAllocVec.begin(), this->sharedAllocVec.end(), [&hostPtr](SharedAllocDesc &other) {
            return hostPtr >= other.ptr && hostPtr < reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(other.ptr) + other.size);
        });
    }

    Cal::Ipc::Connection &connection;
    bool sharedAllocationsEnabled = true;
};

} // namespace Cal::Icd
