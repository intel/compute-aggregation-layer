/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "shared/rpc.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/sys_mock.h"

namespace Cal {

namespace Ult {

TEST(TypedRing, givenDefaultInitializerThenCreatesEmptyRing) {
    Cal::Rpc::TypedRing<int, int> ring;
    EXPECT_EQ(0U, ring.getCapacity());
}

TEST(TypedRing, givenSpaceAndCapacityThenUsesThemAsUnderlyingMemory) {
    std::vector<int> data = {2, 3, 5, 7, 11, 13};
    int head = 0;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(data.size(), ring.getCapacity());

    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(0U, ring.peekHeadOffset());
    EXPECT_EQ(0U, ring.peekTailOffset());
    head = 1;
    tail = 4;
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(1U, ring.peekHeadOffset());
    EXPECT_EQ(4U, ring.peekTailOffset());
    EXPECT_EQ(3, *ring.peekHead());
}

TEST(TypedRing, whenResetIsCalledThenReinitializesHeadAndTailOffsetToZero) {
    std::vector<int> data = {2, 3, 5, 7, 11, 13};
    int head = 1;
    int tail = 4;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(1U, ring.peekHeadOffset());
    EXPECT_EQ(4U, ring.peekTailOffset());
    ring.reset();
    EXPECT_EQ(0U, ring.peekHeadOffset());
    EXPECT_EQ(0U, ring.peekTailOffset());
}

TEST(TypedRing, whenCheckedIfEmptyThenReturnsTrueOnlyIfHeadEqualsToTail) {
    std::vector<int> data = {2, 3, 5, 7, 11, 13};
    int head = 1;
    int tail = 4;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_FALSE(ring.peekEmpty());
    tail = 1;
    head = 4;
    EXPECT_FALSE(ring.peekEmpty());
    tail = head;
    EXPECT_TRUE(ring.peekEmpty());
}

TEST(TypedRingPush, whenTailNotAtEndThenPushMovesTailByOne) {
    std::vector<int> data = {2, 3, 5};
    int head = 0;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.push(17));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(1, tail);
    EXPECT_EQ(0, head);
    EXPECT_EQ(17, data[0]);
    EXPECT_EQ(17, *ring.peekHead());

    EXPECT_TRUE(ring.push(19));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(2, tail);
    EXPECT_EQ(0, head);
    EXPECT_EQ(19, data[1]);
}

TEST(TypedRingPush, whenTailAtEndAndHeadOn0ThenPushFailsDueToRingBeingFull) {
    Cal::Mocks::LogCaptureContext logs;
    std::vector<int> data = {2, 3, 5};
    int head = 0;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.push(17));
    EXPECT_TRUE(ring.push(19));

    EXPECT_FALSE(ring.push(23));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(2, tail);
    EXPECT_EQ(0, head);

    EXPECT_EQ(17, data[0]);
    EXPECT_EQ(19, data[1]);
    EXPECT_EQ(5, data[2]);

    EXPECT_FALSE(logs.empty());
}

TEST(TypedRingPush, whenTailAtEndAndHeadNotOn0ThenPushSucceedsAndWraps) {
    std::vector<int> data = {2, 3, 5};
    int head = 1;
    int tail = 2;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_TRUE(ring.push(23));
    EXPECT_EQ(1U, ring.peekIteration());
    EXPECT_EQ(0, tail);
    EXPECT_EQ(1, head);

    EXPECT_EQ(2, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(23, data[2]);
}

TEST(TypedRingPush, whenWrappedAndRingNotFullThenPushMovesTailByOne) {
    std::vector<int> data = {2, 3, 5};
    int head = 2;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_TRUE(ring.push(23));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(1, tail);
    EXPECT_EQ(2, head);

    EXPECT_EQ(23, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(5, data[2]);
}

TEST(TypedRingPush, whenWrappedAndRingFullThenFailsAndEmitsLog) {
    Cal::Mocks::LogCaptureContext logs;
    std::vector<int> data = {2, 3, 5};
    int head = 1;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_FALSE(ring.push(23));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(0, tail);
    EXPECT_EQ(1, head);

    EXPECT_EQ(2, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(5, data[2]);
    EXPECT_FALSE(logs.empty());
}

TEST(TypedRingPop, whenEmptyThenFailsAndEmitsLog) {
    Cal::Mocks::LogCaptureContext logs;
    std::vector<int> data = {2, 3, 5};
    int head = 2;
    int tail = 2;
    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.peekEmpty());
    EXPECT_FALSE(ring.pop());
    EXPECT_FALSE(logs.empty());
}

TEST(TypedRingPop, whenNotAtTheEndThenAdvancesHeadByOne) {
    std::vector<int> data = {2, 3, 5};
    int head = 0;
    int tail = 2;
    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.pop());
    EXPECT_EQ(1, head);
    EXPECT_EQ(2, tail);

    EXPECT_EQ(2, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(5, data[2]);
}

TEST(TypedRingPop, whenAtTheEndThenMovesHeadToZero) {
    std::vector<int> data = {2, 3, 5};
    int head = 2;
    int tail = 1;
    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.pop());
    EXPECT_EQ(0, head);
    EXPECT_EQ(1, tail);

    EXPECT_EQ(2, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(5, data[2]);
}

TEST(StaticLengthBitAllocator, WhenDefaultConstructedThenIsEmpty) {
    using MaskT = uint64_t;
    using BitAllocatorT = Cal::Rpc::StaticLengthBitAllocator<uint64_t>;
    BitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(BitAllocatorT::invalidOffset, bit) << "it : " << i << " bit : " << bit;
    }
}

TEST(StaticLengthBitAllocator, WhenFullThenReturnsInvalidOffset) {
    using MaskT = uint64_t;
    using BitAllocatorT = Cal::Rpc::StaticLengthBitAllocator<uint64_t>;
    BitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
    }

    EXPECT_EQ(BitAllocatorT::invalidOffset, allocator.allocate());
}

TEST(StaticLengthBitAllocator, WhenCopyConstructedThenHoldsTheSameBits) {
    using MaskT = uint64_t;
    using BitAllocatorT = Cal::Rpc::StaticLengthBitAllocator<uint64_t>;
    BitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::set<BitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits / 2; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.insert(bit);
    }

    auto copy = allocator;
    for (int i = numBits / 2; i < numBits; ++i) {
        auto bitInOrig = copy.allocate();
        auto bitInCopy = allocator.allocate();
        EXPECT_NE(BitAllocatorT::invalidOffset, bitInOrig) << i;
        EXPECT_EQ(bitInOrig, bitInCopy) << i;
        EXPECT_EQ(0U, occupiedBits.count(bitInOrig)) << i;
        occupiedBits.insert(bitInOrig);
    }
    EXPECT_EQ(BitAllocatorT::invalidOffset, allocator.allocate());
    EXPECT_EQ(BitAllocatorT::invalidOffset, copy.allocate());
}

TEST(StaticLengthBitAllocator, WhenMoveConstructedThenTakesOverTheBits) {
    using MaskT = uint64_t;
    using BitAllocatorT = Cal::Rpc::StaticLengthBitAllocator<uint64_t>;
    BitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::set<BitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits / 2; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.insert(bit);
    }

    auto moved = std::move(allocator);
    for (int i = numBits / 2; i < numBits; ++i) {
        auto bit = moved.allocate();
        EXPECT_NE(BitAllocatorT::invalidOffset, bit) << i;
        EXPECT_EQ(0U, occupiedBits.count(bit)) << i;
        occupiedBits.insert(bit);
    }
    EXPECT_EQ(BitAllocatorT::invalidOffset, moved.allocate());

    occupiedBits.clear();
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(BitAllocatorT::invalidOffset, bit) << i;
        EXPECT_EQ(0U, occupiedBits.count(bit)) << i;
        occupiedBits.insert(bit);
    }
    EXPECT_EQ(BitAllocatorT::invalidOffset, allocator.allocate());
}

TEST(StaticLengthBitAllocator, WhenAllocatingBitsThenReturnedValuesAreInCorrectRangeAndUnique) {
    using MaskT = uint64_t;
    using BitAllocatorT = Cal::Rpc::StaticLengthBitAllocator<uint64_t>;
    BitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::set<BitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_LE(0, bit) << "it : " << i << " bit : " << bit;
        EXPECT_GT(numBits, bit) << "it : " << i << " bit : " << bit;
        EXPECT_EQ(0U, occupiedBits.count(bit));
        occupiedBits.insert(bit);
    }
}

TEST(StaticLengthBitAllocator, WhenFreeingBitsThenTheyCanBeReallocated) {
    using MaskT = uint64_t;
    using BitAllocatorT = Cal::Rpc::StaticLengthBitAllocator<uint64_t>;
    BitAllocatorT allocator;
    auto numBits = std::numeric_limits<MaskT>::digits;
    std::vector<BitAllocatorT::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.push_back(bit);
    }
    EXPECT_EQ(BitAllocatorT::invalidOffset, allocator.allocate());

    static constexpr int bitsToReuseCount = 4;
    static constexpr int bitsToReuse[bitsToReuseCount] = {2, 3, 5, 7};
    std::set<BitAllocatorT::BitOffsetT> freeBits;
    for (int i = 0; i < bitsToReuseCount; ++i) {
        allocator.free(occupiedBits[bitsToReuse[i]]);
        freeBits.insert(occupiedBits[bitsToReuse[i]]);
    }

    for (int i = 0; i < bitsToReuseCount; ++i) {
        auto bit = allocator.allocate();
        EXPECT_EQ(1U, freeBits.count(bit)) << "it : " << i << " bit : " << bit;
        freeBits.erase(bit);
    }
    EXPECT_EQ(BitAllocatorT::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenDefaultInitializedThenHasEmptyCapacity) {
    Cal::Rpc::BitAllocator allocator;
    EXPECT_EQ(0U, allocator.getCapacity());
    EXPECT_EQ(Cal::Rpc::BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenInitializedWithSizeThatIsNotMultipleOfNodeSizeThenAlignsDownAndEmitsWarning) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Rpc::BitAllocator allocator{65};
    EXPECT_EQ(64U, allocator.getCapacity());
    EXPECT_FALSE(logs.empty());
}

TEST(BitAllocator, WhenDefaultConstructedThenIsEmpty) {
    size_t numBits = 256;
    Cal::Rpc::BitAllocator allocator{numBits};
    EXPECT_EQ(numBits, allocator.getCapacity());
    numBits = allocator.getCapacity();
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(Cal::Rpc::BitAllocator::invalidOffset, bit) << "it : " << i << " bit : " << bit;
    }
}

TEST(BitAllocator, WhenFullThenReturnsInvalidOffset) {
    Cal::Rpc::BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
    }

    EXPECT_EQ(Cal::Rpc::BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenAllocatingBitsThenReturnedValuesAreInCorrectRangeAndUnique) {
    Cal::Rpc::BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    std::set<Cal::Rpc::BitAllocator::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_LE(0, bit) << "it : " << i << " bit : " << bit;
        EXPECT_GT(numBits, bit) << "it : " << i << " bit : " << bit;
        EXPECT_EQ(0U, occupiedBits.count(bit));
        occupiedBits.insert(bit);
    }
}

TEST(BitAllocator, WhenFreeingBitsThenTheyCanBeReallocated) {
    Cal::Rpc::BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    std::vector<Cal::Rpc::BitAllocator::BitOffsetT> occupiedBits;
    for (int i = 0; i < numBits; ++i) {
        auto bit = allocator.allocate();
        occupiedBits.push_back(bit);
    }
    EXPECT_EQ(Cal::Rpc::BitAllocator::invalidOffset, allocator.allocate());

    static constexpr int bitsToReuseCount = 16;
    static constexpr int bitsToReuse[bitsToReuseCount] = {2, 3, 5, 7, 73, 79, 83, 89, 137, 139, 149, 151, 197, 199, 211, 223};
    std::set<Cal::Rpc::BitAllocator::BitOffsetT> freeBits;
    for (int i = 0; i < bitsToReuseCount; ++i) {
        EXPECT_TRUE(allocator.free(occupiedBits[bitsToReuse[i]]));
        freeBits.insert(occupiedBits[bitsToReuse[i]]);
    }

    for (int i = 0; i < bitsToReuseCount; ++i) {
        auto bit = allocator.allocate();
        EXPECT_EQ(1U, freeBits.count(bit)) << "it : " << i << " bit : " << bit;
        freeBits.erase(bit);
    }
    EXPECT_EQ(Cal::Rpc::BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenFreeingOutOfRangeBitThenEmitsWarning) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Rpc::BitAllocator allocator{256};
    EXPECT_FALSE(allocator.free(257));
    EXPECT_FALSE(logs.empty());
}

TEST(TagAllocator, WhenDefaultInitializedThenHasEmptyCapacity) {
    Cal::Rpc::TagAllocator<int> allocator;
    EXPECT_EQ(0U, allocator.getCapacity());
    EXPECT_EQ(nullptr, allocator.allocate());
}

TEST(TagAllocator, WhenInitializedWithUnderlyingBufferThenUsesItForAllocations) {
    std::vector<int> underlyingData(256);
    Cal::Rpc::TagAllocator<int> allocator{underlyingData.data(), underlyingData.size()};
    EXPECT_EQ(underlyingData.size(), allocator.getCapacity());
    int *tag = allocator.allocate();
    ASSERT_NE(nullptr, tag);
    Cal::Utils::AddressRange range{underlyingData.data(), underlyingData.size() * sizeof(int)};
    EXPECT_TRUE(range.contains(tag));
}

TEST(TagAllocator, WhenAllocatingTagsThenReturnedValuesAreInCorrectRangeAndUnique) {
    std::vector<int> underlyingData(256);
    Cal::Rpc::TagAllocator<int> allocator{underlyingData.data(), underlyingData.size()};
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
    Cal::Rpc::TagAllocator<int> allocator{underlyingData.data(), underlyingData.size()};
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

} // namespace Ult
} // namespace Cal
