/*
 * Copyright (C) 2022-2023 Intel Corporation
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

struct TransferDesc {
    int32_t shmemId{-1};                // Shmem file ID within CAL. -1 for staging USM transfers
    uint64_t underlyingSize{};          // Underlying size of shared memory file. Ignored for staging USM transfers
    uint64_t bytesCountToCopy{};        // The number of bytes to copy.
    uint64_t offsetFromResourceStart{}; // Offset from the mapped address. For USM it's offset from nullptr (0), i.e. pointer
    uintptr_t clientAddress{};          // Client's VA from/to which the memory should be copied.
    enum Direction {
        ClientToService,
        ServiceToClient,
    } direction{};
};
static_assert(std::is_standard_layout_v<TransferDesc>);

struct MemChunk {
    MemChunk(const void *address, uint64_t size) : address{address}, size{size} {}

    const void *address;
    uint64_t size;
};
static_assert(std::is_standard_layout_v<MemChunk>);

} // namespace Rpc
} // namespace Cal
