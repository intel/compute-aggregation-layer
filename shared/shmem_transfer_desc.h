/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace Cal {
namespace Rpc {

struct ShmemTransferDesc {
    int32_t shmemId{};            // Shmem file ID within CAL.
    uint32_t underlyingSize{};    // Underlying size of shared memory file.
    uint32_t bytesCountToCopy{};  // The number of bytes to copy.
    uint32_t offsetFromMapping{}; // Offset from the mapped address.
    uintptr_t transferStart{};    // Client's VA from/to which the memory should be copied.
};
static_assert(std::is_standard_layout_v<ShmemTransferDesc>);

struct MemChunk {
    MemChunk(const void *address, uint64_t size) : address{address}, size{size} {}

    const void *address;
    uint64_t size;
};
static_assert(std::is_standard_layout_v<MemChunk>);

} // namespace Rpc
} // namespace Cal
