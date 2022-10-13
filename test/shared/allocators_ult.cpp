/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "shared/allocators.h"
#include "shared/utils.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/shmem_manager_mock.h"
#include "test/mocks/sys_mock.h"

namespace Cal::Ult {

using namespace Cal::Allocators;
using MaskT = uint64_t;
using StaticBitAllocatorT = StaticLengthBitAllocator<uint64_t>;

TEST(StaticLengthBitAllocator, WhenDefaultConstructedThenIsEmpty) {
    StaticBitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(StaticBitAllocatorT::invalidOffset, bit) << "it : " << i << " bit : " << bit;
    }
}

TEST(StaticLengthBitAllocator, WhenFullThenReturnsInvalidOffset) {
    StaticBitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
    }

    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, allocator.allocate());
}

TEST(StaticLengthBitAllocator, WhenCopyConstructedThenHoldsTheSameBits) {
    StaticBitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::set<StaticBitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits / 2; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.insert(bit);
    }

    auto copy = allocator;
    for (int i = numBits / 2; i < numBits; ++i) {
        auto bitInOrig = copy.allocate();
        auto bitInCopy = allocator.allocate();
        EXPECT_NE(StaticBitAllocatorT::invalidOffset, bitInOrig) << i;
        EXPECT_EQ(bitInOrig, bitInCopy) << i;
        EXPECT_EQ(0U, occupiedBits.count(bitInOrig)) << i;
        occupiedBits.insert(bitInOrig);
    }
    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, allocator.allocate());
    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, copy.allocate());
}

TEST(StaticLengthBitAllocator, WhenMoveConstructedThenTakesOverTheBits) {
    StaticBitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::set<StaticBitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits / 2; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.insert(bit);
    }

    auto moved = std::move(allocator);
    for (int i = numBits / 2; i < numBits; ++i) {
        auto bit = moved.allocate();
        EXPECT_NE(StaticBitAllocatorT::invalidOffset, bit) << i;
        EXPECT_EQ(0U, occupiedBits.count(bit)) << i;
        occupiedBits.insert(bit);
    }
    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, moved.allocate());

    occupiedBits.clear();
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(StaticBitAllocatorT::invalidOffset, bit) << i;
        EXPECT_EQ(0U, occupiedBits.count(bit)) << i;
        occupiedBits.insert(bit);
    }
    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, allocator.allocate());
}

TEST(StaticLengthBitAllocator, WhenAllocatingBitsThenReturnedValuesAreInCorrectRangeAndUnique) {
    StaticBitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::set<StaticBitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_LE(0, bit) << "it : " << i << " bit : " << bit;
        EXPECT_GT(numBits, bit) << "it : " << i << " bit : " << bit;
        EXPECT_EQ(0U, occupiedBits.count(bit));
        occupiedBits.insert(bit);
    }
}

TEST(StaticLengthBitAllocator, WhenFreeingBitsThenTheyCanBeReallocated) {
    StaticBitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::vector<StaticBitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.push_back(bit);
    }
    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, allocator.allocate());

    static constexpr int bitsToReuseCount = 4;
    static constexpr int bitsToReuse[bitsToReuseCount] = {2, 3, 5, 7};
    std::set<StaticBitAllocatorT::BitOffsetT> freeBits;
    for (int i = 0; i < bitsToReuseCount; ++i) {
        allocator.free(occupiedBits[bitsToReuse[i]]);
        freeBits.insert(occupiedBits[bitsToReuse[i]]);
    }

    for (int i = 0; i < bitsToReuseCount; ++i) {
        auto bit = allocator.allocate();
        EXPECT_EQ(1U, freeBits.count(bit)) << "it : " << i << " bit : " << bit;
        freeBits.erase(bit);
    }
    EXPECT_EQ(StaticBitAllocatorT::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenDefaultInitializedThenHasEmptyCapacity) {
    BitAllocator allocator;
    EXPECT_EQ(0U, allocator.getCapacity());
    EXPECT_EQ(BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenInitializedWithSizeThatIsNotMultipleOfNodeSizeThenAlignsDownAndEmitsWarning) {
    Cal::Mocks::LogCaptureContext logs;
    BitAllocator allocator{65};
    EXPECT_EQ(64U, allocator.getCapacity());
    EXPECT_FALSE(logs.empty());
}

TEST(BitAllocator, WhenDefaultConstructedThenIsEmpty) {
    size_t numBits = 256;
    BitAllocator allocator{numBits};
    EXPECT_EQ(numBits, allocator.getCapacity());
    numBits = allocator.getCapacity();
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(BitAllocator::invalidOffset, bit) << "it : " << i << " bit : " << bit;
    }
}

TEST(BitAllocator, WhenFullThenReturnsInvalidOffset) {
    Cal::Allocators::BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
    }

    EXPECT_EQ(BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenAllocatingBitsThenReturnedValuesAreInCorrectRangeAndUnique) {
    BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    std::set<BitAllocator::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_LE(0, bit) << "it : " << i << " bit : " << bit;
        EXPECT_GT(numBits, bit) << "it : " << i << " bit : " << bit;
        EXPECT_EQ(0U, occupiedBits.count(bit));
        occupiedBits.insert(bit);
    }
}

TEST(BitAllocator, WhenFreeingBitsThenTheyCanBeReallocated) {
    BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    std::vector<BitAllocator::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.push_back(bit);
    }
    EXPECT_EQ(BitAllocator::invalidOffset, allocator.allocate());

    static constexpr int bitsToReuseCount = 16;
    static constexpr int bitsToReuse[bitsToReuseCount] = {2, 3, 5, 7, 73, 79, 83, 89, 137, 139, 149, 151, 197, 199, 211, 223};
    std::set<BitAllocator::BitOffsetT> freeBits;
    for (int i = 0; i < bitsToReuseCount; ++i) {
        EXPECT_TRUE(allocator.free(occupiedBits[bitsToReuse[i]]));
        freeBits.insert(occupiedBits[bitsToReuse[i]]);
    }

    for (int i = 0; i < bitsToReuseCount; ++i) {
        auto bit = allocator.allocate();
        EXPECT_EQ(1U, freeBits.count(bit)) << "it : " << i << " bit : " << bit;
        freeBits.erase(bit);
    }
    EXPECT_EQ(BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenFreeingOutOfRangeBitThenEmitsWarning) {
    Cal::Mocks::LogCaptureContext logs;
    BitAllocator allocator{256};
    EXPECT_FALSE(allocator.free(257));
    EXPECT_FALSE(logs.empty());
}

TEST(TagAllocator, WhenDefaultInitializedThenHasEmptyCapacity) {
    TagAllocator<int> allocator;
    EXPECT_EQ(0U, allocator.getCapacity());
    EXPECT_EQ(nullptr, allocator.allocate());
}

TEST(TagAllocator, WhenInitializedWithUnderlyingBufferThenUsesItForAllocations) {
    std::vector<int> underlyingData(256);
    TagAllocator<int> allocator{underlyingData.data(), underlyingData.size()};
    EXPECT_EQ(underlyingData.size(), allocator.getCapacity());
    int *tag = allocator.allocate();
    ASSERT_NE(nullptr, tag);
    Cal::Utils::AddressRange range{underlyingData.data(), underlyingData.size() * sizeof(int)};
    EXPECT_TRUE(range.contains(tag));
}

TEST(TagAllocator, WhenAllocatingTagsThenReturnedValuesAreInCorrectRangeAndUnique) {
    std::vector<int> underlyingData(256);
    TagAllocator<int> allocator{underlyingData.data(), underlyingData.size()};
    auto numTags = allocator.getCapacity();
    std::set<int *> occupiedTags;
    Cal::Utils::AddressRange range{underlyingData.data(), underlyingData.size() * sizeof(int)};
    for (int i = 0; i < numTags; ++i) {
        auto tag = allocator.allocate();
        EXPECT_EQ(tag, Cal::Utils::alignUp(tag, sizeof(int))) << "it : " << i << " wrong alignment for tag : " << reinterpret_cast<uintptr_t>(tag) << " [range : " << range.start << "-" << range.end << "]";
        EXPECT_TRUE(range.contains(tag)) << "it : " << i << " tag : " << reinterpret_cast<uintptr_t>(tag) << " [range : " << range.start << "-" << range.end << "]";
        EXPECT_EQ(0U, occupiedTags.count(tag));
        occupiedTags.insert(tag);
    }
}

TEST(TagAllocator, WhenFreeingTagsThenTheyCanBeReallocated) {
    std::vector<int> underlyingData(256);
    TagAllocator<int> allocator{underlyingData.data(), underlyingData.size()};
    auto numTags = allocator.getCapacity();
    std::vector<int *> occupiedTags;
    for (int i = 0; i < numTags; ++i) {
        auto tag = allocator.allocate();
        occupiedTags.push_back(tag);
    }
    EXPECT_EQ(nullptr, allocator.allocate());

    static constexpr int tagsToReuseCount = 16;
    static constexpr int tagsToReuse[tagsToReuseCount] = {2, 3, 5, 7, 73, 79, 83, 89, 137, 139, 149, 151, 197, 199, 211, 223};
    std::set<int *> freeTags;
    for (int i = 0; i < tagsToReuseCount; ++i) {
        allocator.free(occupiedTags[tagsToReuse[i]]);
        freeTags.insert(occupiedTags[tagsToReuse[i]]);
    }

    for (int i = 0; i < tagsToReuseCount; ++i) {
        auto tag = allocator.allocate();
        EXPECT_EQ(1U, freeTags.count(tag)) << "it : " << i << " tag : " << reinterpret_cast<uintptr_t>(tag);
        freeTags.erase(tag);
    }
    EXPECT_EQ(nullptr, allocator.allocate());
}

} // namespace Cal::Ult
