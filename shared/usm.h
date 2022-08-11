/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

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

inline void *reserveUsmCpuRange(void *base, size_t size) {
    int flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE;
    if (base) {
        flags |= MAP_FIXED_NOREPLACE;
    }
    return Cal::Sys::mmap(base, size, PROT_NONE, flags, -1, 0);
}

inline void *forceReserveUsmCpuRange(void *base, size_t size) {
    int flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE;
    if (base) {
        flags |= MAP_FIXED;
    }
    return Cal::Sys::mmap(base, size, PROT_NONE, flags, -1, 0);
}

inline void *commitUsmCpuRange(void *base, size_t size) {
    int flags = MAP_PRIVATE | MAP_ANONYMOUS;
    if (base) {
        flags |= MAP_FIXED;
    }
    return Cal::Sys::mmap(base, size, PROT_READ | PROT_WRITE, flags, -1, 0);
}

inline void *mapUsmCpuRangeToFd(void *base, size_t size, int fd) {
    int flags = MAP_SHARED;
    if (base) {
        flags |= MAP_FIXED;
    }
    return Cal::Sys::mmap(base, size, PROT_READ | PROT_WRITE, flags, fd, 0);
}

inline void resetUsmCpuRange(void *base, size_t size) {
    int flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED;
    auto ret = Cal::Sys::mmap(base, size, PROT_NONE, flags, -1, 0);
    if ((MAP_FAILED == ret) || (base != ret)) {
        log<Verbosity::error>("Failed to resetUsmCpuRange, ptr : %p, size : %zu", base, size);
    }
}

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
    Cal::Ipc::Shmem shmem;

    void (*gpuDestructor)(void *ctx, void *ptr) = nullptr;
};

} // namespace Usm

} // namespace Cal
