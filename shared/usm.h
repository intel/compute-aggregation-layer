/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/allocators.h"
#include "shared/control_messages.h"
#include "shared/ipc.h"
#include "shared/log.h"
#include "shared/shmem.h"
#include "shared/sys.h"
#include "shared/utils.h"

#include <memory>
#include <optional>
#include <sys/mman.h>
#include <vector>

namespace Cal {

namespace Usm {

static constexpr int maxTriesWhenNegotiatingUsmRange = 64U;
std::optional<Cal::Utils::AddressRange> negotiateUsmRangeWithService(Cal::Ipc::Connection &remoteConnection, void *proposedUsmBase, size_t proposedUsmSize, int maxTries);
std::optional<Cal::Utils::AddressRange> negotiateUsmRangeWithClient(Cal::Ipc::Connection &remoteConnection, void *requestedUsmBase, size_t requestedUsmSize, int maxTries);

inline std::optional<Cal::Utils::AddressRange> negotiateUsmRangeWithService(Cal::Ipc::Connection &remoteConnection, void *proposedUsmBase, size_t proposedUsmSize) {
    return negotiateUsmRangeWithService(remoteConnection, proposedUsmBase, proposedUsmSize, maxTriesWhenNegotiatingUsmRange);
}

inline std::optional<Cal::Utils::AddressRange> negotiateUsmRangeWithClient(Cal::Ipc::Connection &remoteConnection, void *requestedUsmBase, size_t requestedUsmSize) {
    return negotiateUsmRangeWithClient(remoteConnection, requestedUsmBase, requestedUsmSize, maxTriesWhenNegotiatingUsmRange);
}

struct UsmSharedHostAlloc {
    void *ctx = nullptr;
    void *ptr = nullptr;
    size_t alignedSize = 0;
    Cal::Ipc::MmappedShmemAllocationT shmem;

    void (*gpuDestructor)(void *ctx, void *ptr) = nullptr;
};

// thread-safe
using UsmMmappedShmemAllocatorBaseT = Cal::Allocators::AllocatorWithBoundedMmapToFd<Cal::Ipc::ShmemAllocator, true>;
class UsmMmappedShmemAllocator : public UsmMmappedShmemAllocatorBaseT {
  public:
    static_assert(UsmMmappedShmemAllocatorBaseT::isThreadSafe);

    static constexpr Cal::Allocators::MmapConfig mmapConfig = {
        PROT_READ | PROT_WRITE, // prot
        MAP_SHARED              // flags;
    };

    static constexpr Cal::Allocators::UnmapConfig unmapConfig = {
        true, // useResetInsteadOfMunamp
        {
            PROT_NONE,                                  // prot
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE // flags;
        }                                               // resetConfig
    };

    static void *reserveUsmCpuRange(void *base, size_t size) {
        int flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE;
        if (base) {
            flags |= MAP_FIXED_NOREPLACE;
        }
        return Cal::Sys::mmap(base, size, PROT_NONE, flags, -1, 0);
    }

    static void *forceReserveUsmCpuRange(void *base, size_t size) {
        int flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE;
        if (base) {
            flags |= MAP_FIXED;
        }
        return Cal::Sys::mmap(base, size, PROT_NONE, flags, -1, 0);
    }

    UsmMmappedShmemAllocator(Cal::Ipc::ShmemAllocator &shmemAllocator, Cal::Utils::AddressRange bounds)
        : UsmMmappedShmemAllocatorBaseT(shmemAllocator, mmapConfig, unmapConfig, bounds) {
    }
};

// thread-safe
class UsmShmemImporter {
  public:
    static constexpr bool isThreadSafe = true;
    static_assert(Cal::Ipc::ShmemImporter::isThreadSafe); // requirement

    using AllocationT = Cal::Ipc::ShmemImporter::AllocationT;

    UsmShmemImporter(Cal::Ipc::ShmemImporter &base) : base(base) {
    }

    AllocationT open(Cal::Ipc::ShmemIdT id, size_t size, void *enforcedVaForMmap) {
        return base.open(id, size, enforcedVaForMmap);
    }

    AllocationT open(const Cal::Ipc::RemoteShmemDesc &desc, void *enforcedVaForMmap) {
        return this->open(desc.id, desc.size, enforcedVaForMmap);
    }

    AllocationT open(const Cal::Ipc::RemoteShmemDesc &desc) {
        return this->open(desc, nullptr);
    }

    void release(const AllocationT &shmem) {
        bool unmapSucesful = true;
        if (nullptr != shmem.getMmappedPtr()) {
            auto ret = Cal::Sys::mmap(shmem.getMmappedPtr(), shmem.getMmappedSize(), PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED, -1, 0);
            if (MAP_FAILED == ret) {
                log<Verbosity::error>("Failed to reset range, ptr : %p, size : %zu", shmem.getMmappedPtr(), shmem.getMmappedSize());
                unmapSucesful = false;
            } else {
                log<Verbosity::debug>("Succesfully reset usm range ptr : %p, size : %zu", shmem.getMmappedPtr(), shmem.getMmappedSize());
            }
        }

        if (unmapSucesful) {
            if (shmem.isOwnerOfFd()) {
                auto path = base.getBasePath() + std::to_string(shmem.getShmemId());
                if (-1 == Cal::Sys::close(shmem.getFd())) {
                    auto err = errno;
                    log<Verbosity::error>("Failed to close shmem FD %d for path : %s (errno=%d=%s)", shmem.getFd(), path.c_str(), err, strerror(err));
                } else {
                    log<Verbosity::debug>("Closed FD %d for shmem %s of size : %zu", shmem.getFd(), path.c_str(), shmem.getMmappedSize());
                }
            }
        } else {
            log<Verbosity::debug>("Leaking FD %d because %p failed to unmap", shmem.getFd(), shmem.getMmappedPtr());
        }
    }

  protected:
    Cal::Ipc::ShmemImporter &base;
};

} // namespace Usm

} // namespace Cal
