/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/log.h"
#include "shared/utils.h"

namespace Cal::Allocators {

// Thread-safe
template <typename MaskType = uint64_t>
class StaticLengthBitAllocator final {
  public:
    using MaskT = MaskType;
    static constexpr uint32_t capacity = std::numeric_limits<MaskT>::digits;
    using BitOffsetT = uint32_t;
    static constexpr MaskT fullMask = std::numeric_limits<MaskT>::max();
    static constexpr BitOffsetT invalidOffset = std::numeric_limits<BitOffsetT>::max();

    StaticLengthBitAllocator() = default;

    StaticLengthBitAllocator(const StaticLengthBitAllocator &rhs) {
        occupied = rhs.occupied.load();
    }

    StaticLengthBitAllocator(StaticLengthBitAllocator &&rhs) {
        occupied = rhs.occupied.exchange(0);
    }

    BitOffsetT allocate() {
        BitOffsetT offset = invalidOffset;
        auto prev = occupied.load();
        while (true) {
            if (prev == fullMask) {
                break;              // full
            } else if (0 == prev) { // empty
                if (occupied.compare_exchange_weak(prev, 1U)) {
                    offset = 0;
                    break;
                }
            }

            auto inv = ~prev;
            auto firstUnset = __builtin_ffsl(inv) - 1;
            if (occupied.compare_exchange_weak(prev, prev | (static_cast<MaskT>(1) << firstUnset))) {
                offset = firstUnset;
                break;
            }
        }
        return offset;
    }

    void free(BitOffsetT offset) {
        auto mask = ~(static_cast<MaskT>(1) << offset);
        auto prev = occupied.load();
        while (false == occupied.compare_exchange_weak(prev, prev & mask)) {
        }
    }

  protected:
    std::atomic<MaskT> occupied = 0U;
};

// Thread-safe
class BitAllocator final {
  public:
    using NodeT = StaticLengthBitAllocator<uint64_t>;
    using BitOffsetT = NodeT::BitOffsetT;
    static constexpr BitOffsetT invalidOffset = NodeT::invalidOffset;

    BitAllocator() = default;

    BitAllocator(size_t capacity) {
        nodes.resize(capacity / NodeT::capacity);
        if (0 != (capacity % NodeT::capacity)) {
            log<Verbosity::error>("BitAllocator capacity not divisible by node size - %zu elements will be wasted", capacity % NodeT::capacity);
        }
    }

    BitOffsetT allocate() {
        auto offset = invalidOffset;
        constexpr int numTries = 2;
        for (int tryNum = 0; tryNum < numTries; ++tryNum) {
            for (size_t i = 0; i < nodes.size(); ++i) {
                auto localOffset = nodes[i].allocate();
                if (NodeT::invalidOffset != localOffset) {
                    offset = localOffset + i * NodeT::capacity;
                    break;
                }
            }
            if (invalidOffset != offset) {
                break;
            }
        }

        return offset;
    }

    bool free(BitOffsetT offset) {
        auto nodeId = offset / NodeT::capacity;
        if (nodeId >= nodes.size()) {
            log<Verbosity::error>("Invalid offset %zu >= %zu", offset, getCapacity());
            return false;
        }
        nodes[nodeId].free(offset - nodeId * NodeT::capacity);
        return true;
    }

    size_t getCapacity() const {
        return nodes.size() * NodeT::capacity;
    }

  protected:
    std::vector<NodeT> nodes;
};

// Thread-safe
template <typename TagType>
class TagAllocator final {
  public:
    using TagTypeT = TagType;

    TagAllocator() = default;

    TagAllocator(TagType *underlyingAllocation, size_t capacity)
        : underlyingAllocation(underlyingAllocation), allocator(capacity) {
    }

    TagType *allocate() {
        auto offset = allocator.allocate();
        if (BitAllocator::invalidOffset == offset) {
            return nullptr;
        }

        TagType *ret = &underlyingAllocation[offset];
        return ret;
    }

    void free(TagType *tag) {
        auto offset = tag - underlyingAllocation;
        allocator.free(offset);
    }

    size_t getCapacity() const {
        return allocator.getCapacity();
    }

  protected:
    TagType *underlyingAllocation = nullptr;
    BitAllocator allocator;
};

} // namespace Cal::Allocators
