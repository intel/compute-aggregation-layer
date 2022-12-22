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
using namespace Cal::Mocks;

TEST(AdjustSizeAndAlignment, GivenNonPow2AlignmentThenFailsAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    size_t size = 5;
    size_t alignment = 7;
    EXPECT_FALSE(adjustSizeAndAlignment<256>(size, alignment));
    EXPECT_EQ(5U, size);
    EXPECT_EQ(7U, alignment);
    EXPECT_FALSE(logs.empty());
}

TEST(AdjustSizeAndAlignment, GivenSmallerAlignmentThanMinAlignmentThenUsesMinAlignment) {
    size_t size = 5;
    size_t alignment = 8;
    EXPECT_TRUE(adjustSizeAndAlignment<16>(size, alignment));
    EXPECT_EQ(16U, size);
    EXPECT_EQ(16U, alignment);
}

TEST(AdjustSizeAndAlignment, GivenHigherAlignmentThanMinAlignmentThenUsesThatAlignment) {
    size_t size = 5;
    size_t alignment = 8;
    EXPECT_TRUE(adjustSizeAndAlignment<4>(size, alignment));
    EXPECT_EQ(8U, size);
    EXPECT_EQ(8U, alignment);
}

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
        allocator.allocate();
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
    for (auto i = numBits / 2; i < numBits; ++i) {
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
    for (auto i = numBits / 2; i < numBits; ++i) {
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
        EXPECT_LE(0u, bit) << "it : " << i << " bit : " << bit;
        EXPECT_GT(static_cast<size_t>(numBits), bit) << "it : " << i << " bit : " << bit;
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
    for (auto i = 0u; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_NE(BitAllocator::invalidOffset, bit) << "it : " << i << " bit : " << bit;
    }
}

TEST(BitAllocator, WhenFullThenReturnsInvalidOffset) {
    Cal::Allocators::BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    for (auto i = 0u; i < numBits; ++i) {
        allocator.allocate();
    }

    EXPECT_EQ(BitAllocator::invalidOffset, allocator.allocate());
}

TEST(BitAllocator, WhenAllocatingBitsThenReturnedValuesAreInCorrectRangeAndUnique) {
    BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    std::set<BitAllocator::BitOffsetT> occupiedBits;
    for (auto i = 0u; i < numBits; ++i) {
        auto bit = allocator.allocate();
        EXPECT_LE(0u, bit) << "it : " << i << " bit : " << bit;
        EXPECT_GT(numBits, bit) << "it : " << i << " bit : " << bit;
        EXPECT_EQ(0U, occupiedBits.count(bit));
        occupiedBits.insert(bit);
    }
}

TEST(BitAllocator, WhenFreeingBitsThenTheyCanBeReallocated) {
    BitAllocator allocator{256};
    auto numBits = allocator.getCapacity();
    std::vector<BitAllocator::BitOffsetT> occupiedBits;
    for (auto i = 0u; i < numBits; ++i) {
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
    for (auto i = 0u; i < numTags; ++i) {
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
    for (auto i = 0u; i < numTags; ++i) {
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

TEST(AddressRangeAllocator, whenDefaultInitializedThenRepresentsEmptyRange) {
    Cal::Utils::AddressRange emptyRange = {0U, 0U};
    Cal::Allocators::AddressRangeAllocator heap;
    EXPECT_EQ(emptyRange, heap.getRange());
    EXPECT_EQ(0U, heap.getSizeUsed());
    EXPECT_EQ(0U, heap.getSizeLeft());
}

TEST(AddressRangeAllocator, whenCreatedFromRangeThenRepresentsThatRange) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Allocators::AddressRangeAllocator heap(heapRange);
    EXPECT_EQ(heapRange, heap.getRange());
    EXPECT_EQ(0U, heap.getSizeUsed());
    EXPECT_EQ(heapRange.size(), heap.getSizeLeft());
}

TEST(AddressRangeAllocator, whenAllocatingThenUseFreeAddressesFromTopOfHeapIfPossible) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Allocators::AddressRangeAllocator heap(heapRange);

    size_t size0 = 64U;
    size_t size1 = 128U;
    size_t size2 = 64U;

    auto ptr0 = heap.allocate(size0);
    auto ptr1 = heap.allocate(size1);
    auto ptr2 = heap.allocate(size2);

    EXPECT_EQ(size0 + size1 + size2, heap.getSizeUsed());
    heap.free(ptr1);
    EXPECT_EQ(size0 + size2, heap.getSizeUsed());

    size_t size3 = 64U;
    size_t size4 = 128U;
    auto ptr3 = heap.allocate(size3);
    auto ptr4 = heap.allocate(size4);
    EXPECT_EQ(size0 + size2 + size3 + size4, heap.getSizeUsed());

    EXPECT_NE(nullptr, ptr0);
    EXPECT_LT(reinterpret_cast<uintptr_t>(ptr0), reinterpret_cast<uintptr_t>(ptr1));
    EXPECT_LT(reinterpret_cast<uintptr_t>(ptr1), reinterpret_cast<uintptr_t>(ptr2));
    EXPECT_LT(reinterpret_cast<uintptr_t>(ptr2), reinterpret_cast<uintptr_t>(ptr3));
    EXPECT_LT(reinterpret_cast<uintptr_t>(ptr3), reinterpret_cast<uintptr_t>(ptr4));

    EXPECT_FALSE(Cal::Utils::AddressRange(ptr0, size0).intersects(Cal::Utils::AddressRange(ptr1, size1)));
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr1, size1).intersects(Cal::Utils::AddressRange(ptr2, size2)));
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr2, size2).intersects(Cal::Utils::AddressRange(ptr3, size3)));
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr3, size3).intersects(Cal::Utils::AddressRange(ptr4, size4)));
}

TEST(AddressRangeAllocator, whenAllocatingAndThereAreNoFreeAddressAtTheTopOfTheHeapThenReuseFreedMiddleRange) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Allocators::AddressRangeAllocator heap(heapRange);

    size_t size0 = 64U;
    size_t size1 = 128U;
    size_t size2 = heap.getSizeLeft() - size0 - size1;
    size_t size3 = 64U;

    auto ptr0 = heap.allocate(size0);
    auto ptr1 = heap.allocate(size1);
    auto ptr2 = heap.allocate(size2);
    EXPECT_NE(nullptr, ptr0);
    EXPECT_NE(nullptr, ptr1);
    EXPECT_NE(nullptr, ptr2);
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr0, size0).intersects(Cal::Utils::AddressRange(ptr1, size1)));
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr1, size1).intersects(Cal::Utils::AddressRange(ptr2, size2)));

    EXPECT_EQ(0U, heap.getSizeLeft());
    auto ptr3 = heap.allocate(size3);
    EXPECT_EQ(nullptr, ptr3);

    heap.free(ptr1);
    EXPECT_EQ(128U, heap.getSizeLeft());

    size_t size4 = 64U;
    size_t size5 = 64U;
    size_t size6 = 64U;
    auto ptr4 = heap.allocate(size4);
    auto ptr5 = heap.allocate(size5);
    EXPECT_NE(nullptr, ptr4);
    EXPECT_NE(nullptr, ptr5);
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr4, size4).intersects(Cal::Utils::AddressRange(ptr5, size5)));
    EXPECT_TRUE(Cal::Utils::AddressRange(ptr1, size1).contains(Cal::Utils::AddressRange(ptr4, size4)));
    EXPECT_TRUE(Cal::Utils::AddressRange(ptr1, size1).contains(Cal::Utils::AddressRange(ptr5, size5)));
    EXPECT_EQ(0U, heap.getSizeLeft());
    auto ptr6 = heap.allocate(size6);
    EXPECT_EQ(nullptr, ptr6);
}

TEST(AddressRangeAllocator, whenAllocatingAndThereAreNoFreeAddressAtTheTopOfTheHeapThenReuseFreedBottomRange) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Allocators::AddressRangeAllocator heap(heapRange);

    size_t size0 = 64U;
    size_t size1 = heap.getSizeLeft() - size0;
    size_t size2 = 64U;

    auto ptr0 = heap.allocate(size0);
    auto ptr1 = heap.allocate(size1);

    EXPECT_NE(nullptr, ptr0);
    EXPECT_NE(nullptr, ptr1);
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr0, size0).intersects(Cal::Utils::AddressRange(ptr1, size1)));

    auto ptr2 = heap.allocate(size2);
    EXPECT_EQ(nullptr, ptr2);

    heap.free(ptr0);
    EXPECT_EQ(64U, heap.getSizeLeft());

    size_t size3 = 64U;
    auto ptr3 = heap.allocate(size3);
    EXPECT_NE(nullptr, ptr3);
    EXPECT_EQ(Cal::Utils::AddressRange(ptr0, size0), Cal::Utils::AddressRange(ptr3, size3));
}

TEST(AddressRangeAllocator, whenNewAllocationsAreAddedThenRemainingSizeDecreases) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Allocators::AddressRangeAllocator heap(heapRange);
    EXPECT_EQ(0U, heap.getSizeUsed());
    EXPECT_EQ(heapRange.size(), heap.getSizeLeft());

    auto result = heap.allocate(64U);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(64U, heap.getSizeUsed());
    EXPECT_EQ(heapRange.size() - 64U, heap.getSizeLeft());

    result = heap.allocate(heap.getSizeLeft());
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(heapRange.size(), heap.getSizeUsed());
    EXPECT_EQ(0U, heap.getSizeLeft());

    result = heap.allocate(1U);
    EXPECT_EQ(nullptr, result);
    EXPECT_EQ(heapRange.size(), heap.getSizeUsed());
    EXPECT_EQ(0U, heap.getSizeLeft());
}

TEST(AddressRangeAllocator, whenAllocatingAddressessThenAlignmentsAreTakenIntoAccount) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Allocators::AddressRangeAllocator heap(heapRange);
    auto ptr0 = heap.allocate(1);
    auto ptr1 = heap.allocate(1);
    auto ptr2 = heap.allocate(1);
    auto ptr3 = heap.allocate(1, 4096U);

    EXPECT_TRUE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize>(ptr0));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize>(ptr1));
    EXPECT_FALSE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize * 2>(ptr1));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize>(ptr2));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<4096U>(ptr3));
}

TEST(BaseAllocation, whenQueuriedForRangeThenReturnsEmptyRange) {
    Cal::Allocators::BaseAllocation baseAlloc;
    EXPECT_TRUE(baseAlloc.getRange().empty());
}

TEST(FdAllocation, whenCheckedIfIsValidThenVerifiesFileDescriptor) {
    {
        FdAllocation<BaseAllocation> fdAllocation;
        EXPECT_EQ(-1, fdAllocation.getFd());
        EXPECT_EQ(0U, fdAllocation.getFileSize());
        EXPECT_FALSE(fdAllocation.isOwnerOfFd());
        EXPECT_FALSE(fdAllocation.isValid());
    }
    {
        FdAllocation<BaseAllocation> fdAllocation(2, 4096U, true);
        EXPECT_EQ(2, fdAllocation.getFd());
        EXPECT_EQ(4096U, fdAllocation.getFileSize());
        EXPECT_TRUE(fdAllocation.isOwnerOfFd());
        EXPECT_TRUE(fdAllocation.isValid());
    }
}

TEST(FdAllocation, whenQueuriedForRangeThenReturnsFrom0ToSize) {
    size_t size = 4096U;
    Cal::Allocators::FdAllocation fdAllocation(2, size, true);
    EXPECT_EQ(Cal::Utils::AddressRange(uintptr_t(0U), size), fdAllocation.getRange());
}

TEST(FdAllocation, givenBaseAllocationThenForwarwadsItAsInitializerForBaseClass) {
    struct DummyBaseAllocation : BaseAllocation {
        DummyBaseAllocation(int x) : dummyBaseMember(x) {}
        int dummyBaseMember = -1;
    };

    FdAllocation<DummyBaseAllocation> fdAllocation(DummyBaseAllocation{7}, 2, 4096U, true);
    EXPECT_EQ(2, fdAllocation.getFd());
    EXPECT_EQ(4096U, fdAllocation.getFileSize());
    EXPECT_TRUE(fdAllocation.isOwnerOfFd());
    EXPECT_TRUE(fdAllocation.isValid());
    EXPECT_EQ(7, fdAllocation.dummyBaseMember);
}

TEST(FdSubAllocation, whenCheckedIfIsValidThenVerifiesOffset) {
    {
        FdSubAllocation<> fdSubAllocation(FdAllocation<>(2, 4096U, false), 0);
        EXPECT_EQ(0U, fdSubAllocation.getFdSubAllocationOffset());
        EXPECT_EQ(0U, FdSubAllocation<>::getSubAllocationOffset(fdSubAllocation));
        EXPECT_FALSE(fdSubAllocation.isOwnerOfFd());
        EXPECT_TRUE(fdSubAllocation.isValid());
    }

    {
        FdSubAllocation<> fdSubAllocation(FdAllocation<>(2, 4096U, false), 4096U);
        EXPECT_EQ(4096U, fdSubAllocation.getFdSubAllocationOffset());
        EXPECT_EQ(4096U, FdSubAllocation<>::getSubAllocationOffset(fdSubAllocation));
        EXPECT_FALSE(fdSubAllocation.isOwnerOfFd());
        EXPECT_FALSE(fdSubAllocation.isValid());
    }

    {
        FdSubAllocation<> fdSubAllocation(FdAllocation<>(2, 4096U, false), 8192U);
        EXPECT_EQ(8192U, fdSubAllocation.getFdSubAllocationOffset());
        EXPECT_EQ(8192U, FdSubAllocation<>::getSubAllocationOffset(fdSubAllocation));
        EXPECT_FALSE(fdSubAllocation.isOwnerOfFd());
        EXPECT_FALSE(fdSubAllocation.isValid());
    }
}

TEST(FdSubAllocation, whenQueuriedForRangeThenReturnsFromOffsetToSize) {
    size_t wholeAllocSize = 8192U;
    size_t offset = 4096U;
    FdSubAllocation<> fdSubAllocation(FdAllocation<>(2, wholeAllocSize, false), offset);
    EXPECT_EQ(Cal::Utils::AddressRange(uintptr_t(offset), wholeAllocSize), fdSubAllocation.getRange());
}

TEST(FdSubAllocation, givenBaseAllocationThenForwarwadsItAsInitializerForBaseClass) {
    FdSubAllocation<> fdSubAllocation(FdAllocation<>(-1, 4096U, false), 0);
    EXPECT_EQ(0U, fdSubAllocation.getFdSubAllocationOffset());
    EXPECT_EQ(-1, fdSubAllocation.getFd());
    EXPECT_EQ(4096U, fdSubAllocation.getFileSize());
    EXPECT_FALSE(fdSubAllocation.isOwnerOfFd());
    EXPECT_FALSE(fdSubAllocation.isValid());
}

TEST(MmappedAllocation, whenCheckedIfIsValidThenVerifiesPtrAndSize) {
    {
        int i = 0;
        MmappedAllocation<FdAllocation<>> mmappedAllocation(FdAllocation<>(2, 4096U, true), &i, 4096U);
        EXPECT_EQ(&i, mmappedAllocation.getMmappedPtr());
        EXPECT_EQ(4096U, mmappedAllocation.getMmappedSize());
        EXPECT_TRUE(mmappedAllocation.isValid());
    }

    {
        MmappedAllocation<FdAllocation<>> mmappedAllocation(FdAllocation<>(2, 4096U, true), nullptr, 4096U);
        EXPECT_EQ(nullptr, mmappedAllocation.getMmappedPtr());
        EXPECT_EQ(4096U, mmappedAllocation.getMmappedSize());
        EXPECT_FALSE(mmappedAllocation.isValid());
    }

    {
        int i = 0;
        MmappedAllocation<FdAllocation<>> mmappedAllocation(FdAllocation<>(2, 4096U, true), &i, 0U);
        EXPECT_EQ(&i, mmappedAllocation.getMmappedPtr());
        EXPECT_EQ(0U, mmappedAllocation.getMmappedSize());
        EXPECT_FALSE(mmappedAllocation.isValid());
    }
}

TEST(MmappedAllocation, whenQueuriedForRangeThenReturnsMmapedRange) {
    size_t wholeAllocSize = 8192U;
    size_t mmapedSize = 4096U;
    int i = 0;
    MmappedAllocation<FdAllocation<>> mmappedAllocation(FdAllocation<>(2, wholeAllocSize, true), &i, mmapedSize);
    EXPECT_EQ(Cal::Utils::AddressRange(&i, mmapedSize), mmappedAllocation.getRange());
}

TEST(MmappedAllocation, givenBaseAllocationThenForwarwadsItAsInitializerForBaseClass) {
    int i = 0;
    MmappedAllocation<FdAllocation<>> mmappedAllocation(FdAllocation<>(-1, 4096U, true), &i, 0U);
    EXPECT_EQ(&i, mmappedAllocation.getMmappedPtr());
    EXPECT_EQ(0U, mmappedAllocation.getMmappedSize());
    EXPECT_FALSE(mmappedAllocation.isValid());
    EXPECT_EQ(-1, mmappedAllocation.getFd());
    EXPECT_FALSE(mmappedAllocation.isValid());
}

TEST(SubAllocation, whenCheckedIfIsValidThenVerifiesSourceAllocationAndSize) {
    FdAllocation<> fdAlloc{2, 4096U, true};

    {
        SubAllocation<FdAllocation<>> subAlloc(&fdAlloc, 128U, 256U);
        EXPECT_EQ(128U, subAlloc.getSubAllocationOffset());
        EXPECT_EQ(256U, subAlloc.getSubAllocationSize());
        EXPECT_EQ(&fdAlloc, subAlloc.getSourceAllocation());
        EXPECT_TRUE(subAlloc.isValid());
    }

    {
        SubAllocation<FdAllocation<>> subAlloc;
        EXPECT_EQ(0U, subAlloc.getSubAllocationOffset());
        EXPECT_EQ(0U, subAlloc.getSubAllocationSize());
        EXPECT_EQ(nullptr, subAlloc.getSourceAllocation());
        EXPECT_FALSE(subAlloc.isValid());
    }

    {
        SubAllocation<FdAllocation<>> subAlloc(&fdAlloc, 128U, 0U);
        EXPECT_EQ(128U, subAlloc.getSubAllocationOffset());
        EXPECT_EQ(0U, subAlloc.getSubAllocationSize());
        EXPECT_EQ(&fdAlloc, subAlloc.getSourceAllocation());
        EXPECT_FALSE(subAlloc.isValid());
    }
}

TEST(SubAllocation, whenQueuriedForRangeThenReturnsRangeFromOffsetToSize) {
    size_t subAllocOffset = 128U;
    size_t subAllocSize = 256U;
    size_t wholeAllocSize = 4096U;

    {
        FdAllocation<> fdAlloc{2, wholeAllocSize, true};
        SubAllocation<FdAllocation<>> subAlloc(&fdAlloc, subAllocOffset, subAllocSize);
        EXPECT_EQ(Cal::Utils::AddressRange(subAllocOffset, subAllocOffset + subAllocSize), subAlloc.getRange());
    }

    {
        int i = 0;
        MmappedAllocation<FdAllocation<>> mmappedAllocation(FdAllocation<>(2, 4096U, true), &i, 4096U);
        SubAllocation<MmappedAllocation<FdAllocation<>>> subAlloc(&mmappedAllocation, subAllocOffset, subAllocSize);
        auto expectedRangeOffset = reinterpret_cast<uintptr_t>(&i) + subAllocOffset;
        EXPECT_EQ(Cal::Utils::AddressRange(expectedRangeOffset, expectedRangeOffset + subAllocSize), subAlloc.getRange());
    }
}

TEST(SubAllocation, whenIsMmappedAllocationAndMmapPtrIsNotNullThenReturnsOffsetedMmapPtr) {
    int i[1024U] = {};
    MmappedAllocation<> baseAlloc{i, 4096U};
    SubAllocation<MmappedAllocation<>> subAlloc(&baseAlloc, 4, 4U);
    EXPECT_EQ(i + 1, subAlloc.getSubAllocationPtr());
}

TEST(SubAllocation, whenIsMmappedAllocationButMmapPtrIsNullThenReturnsNullAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    MmappedAllocation<> baseAlloc{nullptr, 4096U};
    SubAllocation<MmappedAllocation<>> subAlloc(&baseAlloc, 16, 4096U);
    EXPECT_EQ(nullptr, subAlloc.getSubAllocationPtr());
    EXPECT_FALSE(logs.empty());
}

TEST(SubAllocation, whenIsNotMmappedAllocationThenReturnsNullAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    BaseAllocation baseAlloc;
    SubAllocation<BaseAllocation> subAlloc(&baseAlloc, 16, 4096U);
    EXPECT_EQ(nullptr, subAlloc.getSubAllocationPtr());
    EXPECT_FALSE(logs.empty());
}

TEST(SubAllocator, whenRequestedNonPow2AlignmentThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;

    alignas(64) int mem[1024U] = {};
    MmappedAllocation<BaseAllocation> baseAlloc{mem, 4096U};
    SubAllocator<decltype(baseAlloc), 64> subAllocator{baseAlloc, Cal::Utils::AddressRange::withinSize(sizeof(mem))};

    auto subAlloc = subAllocator.allocate(4U, 3);
    EXPECT_FALSE(subAlloc.isValid());

    EXPECT_FALSE(logs.empty());
}

TEST(SubAllocator, whenRequestedForEmptySizeThenReturnsInvalidAllocation) {
    static constexpr size_t alignment = 64U;
    alignas(64) int mem[1024U] = {};
    MmappedAllocation<BaseAllocation> baseAlloc{mem, 4096U};
    SubAllocator<decltype(baseAlloc), alignment> subAllocator{baseAlloc, Cal::Utils::AddressRange::withinSize(sizeof(mem))};

    auto subAlloc = subAllocator.allocate(0U);
    EXPECT_FALSE(subAlloc.isValid());
}

TEST(SubAllocator, givenValidSourceAllocationThenAllocateReturnsPortionOfItUntilItsFullyUtilized) {
    static constexpr size_t alignment = 64U;
    alignas(64) int mem[1024U] = {};
    MmappedAllocation<BaseAllocation> baseAlloc{mem, 4096U};
    SubAllocator<decltype(baseAlloc), alignment> subAllocator{baseAlloc, Cal::Utils::AddressRange::withinSize(sizeof(mem))};
    std::vector<decltype(subAllocator)::AllocationT> subAllocations;
    size_t totalAllocated = 0;
    int i = 1;
    while (totalAllocated <= sizeof(mem)) {
        auto sizeToAllocate = (i++) * sizeof(int);
        totalAllocated += Cal::Utils::alignUpPow2<alignment>(sizeToAllocate);
        auto subAlloc = subAllocator.allocate(sizeToAllocate);
        if (totalAllocated > sizeof(mem)) {
            EXPECT_FALSE(subAlloc.isValid()) << totalAllocated;
            EXPECT_EQ(nullptr, subAlloc.getSourceAllocation()) << totalAllocated;
        } else {
            EXPECT_TRUE(subAlloc.isValid()) << totalAllocated;
            EXPECT_EQ(baseAlloc.getMmappedPtr(), subAlloc.getSourceAllocation()->getMmappedPtr()) << totalAllocated;
            EXPECT_TRUE(Cal::Utils::isAlignedPow2<alignment>(subAlloc.getSubAllocationOffset())) << totalAllocated << " " << subAlloc.getSubAllocationOffset();
            EXPECT_TRUE(Cal::Utils::isAlignedPow2<alignment>(subAlloc.getSubAllocationPtr())) << totalAllocated << " " << subAlloc.getSubAllocationPtr();
            EXPECT_EQ(Cal::Utils::alignUpPow2<alignment>(sizeToAllocate), subAlloc.getSubAllocationSize()) << totalAllocated;
        }
        if (subAlloc.isValid()) {
            subAllocations.push_back(subAlloc);
        }
    }
    for (auto &alloc : subAllocations) {
        subAllocator.free(alloc);
    }
}

TEST(GetFdOffset, givenAllocationThenReturnsOffsetIfAllocationIsFdSubAllocationAndZeroForOtherAllocationTypes) {
    EXPECT_EQ(0U, getFdOffset(BaseAllocation()));
    auto fdSubAlloc = FdSubAllocation<FdAllocation<>>(FdAllocation{}, 8192U);
    EXPECT_EQ(8192U, getFdOffset(fdSubAlloc));
}

TEST(AllocatorWithGlobalMmapToFd, whenRequestedNonPow2AlignmentThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED}};

    auto alloc = allocator.allocate(4, 3);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(AllocatorWithGlobalMmapToFd, givenAlignmentGreaterThe4KBThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED}};

    auto alloc = allocator.allocate(4, 8192U);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(AllocatorWithGlobalMmapToFd, whenUnderlyingFdAllocatorReturnedInvalidAllocationThenFails) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED}};

    mockFdAllocator.fdToReturn = -1;
    auto alloc = allocator.allocate(4);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
}

TEST(AllocatorWithGlobalMmapToFd, whenMmapFailedThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED}};

    tempSysCallsCtx.apiConfig.mmap.returnValue = MAP_FAILED;
    auto alloc = allocator.allocate(4);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_FALSE(logs.empty());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
}

TEST(AllocatorWithGlobalMmapToFd, whenSuccesfullyMmappedFdThenReturnsValidAllocation) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    int fd = 7;
    mockFdAllocator.fdToReturn = fd;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig};
    size_t sizeToAllocate = 4099;
    auto alloc = allocator.allocate(sizeToAllocate);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);

    EXPECT_EQ(fd, alloc.getFd());

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(sizeToAllocate);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(alignedSize, alloc.getMmappedSize());
    EXPECT_EQ(tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().base(), alloc.getMmappedPtr());
    EXPECT_EQ(tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().size(), alloc.getMmappedSize());

    EXPECT_EQ(nullptr, tempSysCallsCtx.vma.getSubRanges()[0].getTag().addr);
    EXPECT_EQ(fd, tempSysCallsCtx.vma.getSubRanges()[0].getTag().fd);
    EXPECT_EQ(alloc.getMmappedSize(), tempSysCallsCtx.vma.getSubRanges()[0].getTag().length);
    EXPECT_EQ(mmapConfig.flags, tempSysCallsCtx.vma.getSubRanges()[0].getTag().flags);
    EXPECT_EQ(mmapConfig.prot, tempSysCallsCtx.vma.getSubRanges()[0].getTag().prot);
    EXPECT_EQ(0U, tempSysCallsCtx.vma.getSubRanges()[0].getTag().offset);

    allocator.free(alloc);
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
}

TEST(AllocatorWithGlobalMmapToFd, whenUnderlyingAllocatorUsesFdSubAllocationThenMmapsUsingProvidedFileOffset) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdSubAllocator mockFdAllocator;
    int fd = 7;
    off_t fileOffset = 8192U;
    mockFdAllocator.fdToReturn = fd;
    mockFdAllocator.offsetToReturn = fileOffset;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    AllocatorWithGlobalMmapToFd<MockFdSubAllocator, true> allocator{mockFdAllocator, mmapConfig};
    size_t sizeToAllocate = 4099;
    auto alloc = allocator.allocate(sizeToAllocate);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);

    EXPECT_EQ(fileOffset, static_cast<off_t>(alloc.getFdSubAllocationOffset()));

    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(fd, tempSysCallsCtx.vma.getSubRanges()[0].getTag().fd);
    EXPECT_EQ(fileOffset, tempSysCallsCtx.vma.getSubRanges()[0].getTag().offset);

    allocator.free(alloc);
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
}

TEST(AllocatorWithGlobalMmapToFd, whenFreeingAllocationWithMmappedPtrThenMunmapsMemory) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig};
    size_t sizeToAllocate = 4099;
    auto alloc = allocator.allocate(sizeToAllocate);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());

    allocator.free(alloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_TRUE(tempSysCallsCtx.vma.getSubRanges().empty());
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
}

TEST(AllocatorWithGlobalMmapToFd, givenAllocationWithMmappedPtrWhenFreeingAndMunmapFailsThenEmitsErrorLeaksFd) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig};
    auto alloc = allocator.allocate(4);
    EXPECT_TRUE(alloc.isValid());

    tempSysCallsCtx.apiConfig.munmap.returnValue = -1;
    allocator.free(alloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(0, mockFdAllocator.freeCallCount);
    EXPECT_FALSE(logs.empty());
}

TEST(AllocatorWithGlobalMmapToFd, whenFreeingAllocationWithoutMmappedPtrThenOnlyForwardsAllocationToBaseAllocator) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    AllocatorWithGlobalMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig};
    auto alloc = AllocatorWithGlobalMmapToFd<MockFdAllocator, true>::AllocationT{FdAllocation<>{7, 4096U, false}, nullptr, 4096U};

    allocator.free(alloc);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenRequestedNonPow2AlignmentThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED},
                                                                  UnmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}}, Cal::Utils::AddressRange(4096U, 4096U * 64)};

    auto alloc = allocator.allocate(4, 3);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(AllocatorWithBoundedMmapToFd, givenAlignmentGreaterThe4KBThenUsesThatAlignment) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED},
                                                                  UnmapConfig{false}, Cal::Utils::AddressRange(4096U, 4096U * 64)};

    static constexpr size_t alignment = 4096U * 4;
    auto alloc = allocator.allocate(4, 4096U * 4);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<alignment>(alloc.getMmappedPtr()));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<alignment>(alloc.getMmappedSize()));
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
    allocator.free(alloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenUnderlyingFdAllocatorReturnedInvalidAllocationThenFails) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED},
                                                                  UnmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}}, Cal::Utils::AddressRange(4096U, 4096U * 64)};

    mockFdAllocator.fdToReturn = -1;
    auto alloc = allocator.allocate(4);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenMmapFailedThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED},
                                                                  UnmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}}, Cal::Utils::AddressRange(4096U, 4096U * 64)};

    tempSysCallsCtx.apiConfig.mmap.returnValue = MAP_FAILED;
    auto alloc = allocator.allocate(4);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_FALSE(logs.empty());
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenNotEnoughMemoryInRangeThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, MmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED},
                                                                  UnmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}}, Cal::Utils::AddressRange(4096U, 4096U * 64)};

    tempSysCallsCtx.apiConfig.mmap.returnValue = reinterpret_cast<void *>(uintptr_t(4096U * 65));
    auto alloc = allocator.allocate(allocator.getMmapRange().size() * 2);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_FALSE(logs.empty());
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenSuccesfullyMmappedFdThenReturnsValidAllocation) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    int fd = 7;
    mockFdAllocator.fdToReturn = fd;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    UnmapConfig munmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}};
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                  Cal::Utils::AddressRange(4096U, 4096U * 64)};
    size_t sizeToAllocate = 4099;
    auto alloc = allocator.allocate(sizeToAllocate);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_TRUE(allocator.getMmapRange().contains(Cal::Utils::AddressRange(alloc.getMmappedPtr(), alloc.getMmappedSize())));

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);

    EXPECT_EQ(fd, alloc.getFd());

    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(sizeToAllocate);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(alignedSize, alloc.getMmappedSize());
    EXPECT_EQ(tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().base(), alloc.getMmappedPtr());
    EXPECT_EQ(tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().size(), alloc.getMmappedSize());

    EXPECT_EQ(alloc.getMmappedPtr(), tempSysCallsCtx.vma.getSubRanges()[0].getTag().addr);
    EXPECT_EQ(fd, tempSysCallsCtx.vma.getSubRanges()[0].getTag().fd);
    EXPECT_EQ(alloc.getMmappedSize(), tempSysCallsCtx.vma.getSubRanges()[0].getTag().length);
    EXPECT_EQ(mmapConfig.flags | MAP_FIXED, tempSysCallsCtx.vma.getSubRanges()[0].getTag().flags);
    EXPECT_EQ(mmapConfig.prot, tempSysCallsCtx.vma.getSubRanges()[0].getTag().prot);
    EXPECT_EQ(0U, tempSysCallsCtx.vma.getSubRanges()[0].getTag().offset);

    allocator.free(alloc);
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.mmap.callCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenUnderlyingAllocatorUsesFdSubAllocationThenMmapsUsingProvidedFileOffset) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdSubAllocator mockFdAllocator;
    int fd = 7;
    off_t fileOffset = 8192U;
    mockFdAllocator.fdToReturn = fd;
    mockFdAllocator.offsetToReturn = fileOffset;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    UnmapConfig munmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}};
    AllocatorWithBoundedMmapToFd<MockFdSubAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                     Cal::Utils::AddressRange(4096U, 4096U * 64)};
    size_t sizeToAllocate = 4099;
    auto alloc = allocator.allocate(sizeToAllocate);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);

    EXPECT_EQ(fileOffset, static_cast<off_t>(alloc.getFdSubAllocationOffset()));

    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(fd, tempSysCallsCtx.vma.getSubRanges()[0].getTag().fd);
    EXPECT_EQ(fileOffset, tempSysCallsCtx.vma.getSubRanges()[0].getTag().offset);

    allocator.free(alloc);
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
}

TEST(AllocatorWithBoundedMmapToFd, whenFreeingAllocationWithMmappedPtrThenRemapOrMunmapsMemory) {
    {
        Cal::Mocks::SysCallsContext tempSysCallsCtx;

        MockFdAllocator mockFdAllocator;
        MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
        UnmapConfig munmapConfig{false};
        AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                      Cal::Utils::AddressRange(4096U, 4096U * 64)};
        size_t sizeToAllocate = 4099;
        auto alloc = allocator.allocate(sizeToAllocate);
        EXPECT_TRUE(alloc.isValid());
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
        EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
        EXPECT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());

        allocator.free(alloc);
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
        EXPECT_TRUE(tempSysCallsCtx.vma.getSubRanges().empty());
        EXPECT_EQ(1, mockFdAllocator.freeCallCount);
    }
    {
        Cal::Mocks::SysCallsContext tempSysCallsCtx;

        MockFdAllocator mockFdAllocator;
        MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
        UnmapConfig munmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}};
        AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                      Cal::Utils::AddressRange(4096U, 4096U * 64)};
        size_t sizeToAllocate = 4099;
        auto alloc = allocator.allocate(sizeToAllocate);
        EXPECT_TRUE(alloc.isValid());
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);

        Cal::Utils::AddressRange allocRange{alloc.getMmappedPtr(), alloc.getMmappedSize()};
        allocator.free(alloc);
        EXPECT_EQ(1, mockFdAllocator.freeCallCount);

        EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
        EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.mmap.callCount);

        ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
        EXPECT_EQ(allocRange, tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
        EXPECT_EQ(-1, tempSysCallsCtx.vma.getSubRanges()[0].getTag().fd);
        EXPECT_EQ(allocRange.base(), tempSysCallsCtx.vma.getSubRanges()[0].getTag().addr);
        EXPECT_EQ(allocRange.size(), tempSysCallsCtx.vma.getSubRanges()[0].getTag().length);
        EXPECT_EQ(munmapConfig.resetTraits.flags | MAP_FIXED, tempSysCallsCtx.vma.getSubRanges()[0].getTag().flags);
        EXPECT_EQ(munmapConfig.resetTraits.prot, tempSysCallsCtx.vma.getSubRanges()[0].getTag().prot);
        EXPECT_EQ(0U, tempSysCallsCtx.vma.getSubRanges()[0].getTag().offset);
    }
}

TEST(AllocatorWithBoundedMmapToFd, whenRemapOrUnmapFailedDuringFreeCallThenEmitsErrorAndLeaksFd) {
    {
        Cal::Mocks::LogCaptureContext logs;
        Cal::Mocks::SysCallsContext tempSysCallsCtx;

        MockFdAllocator mockFdAllocator;
        MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
        UnmapConfig munmapConfig{false};
        AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                      Cal::Utils::AddressRange(4096U, 4096U * 64)};
        auto alloc = allocator.allocate(4099);
        EXPECT_TRUE(alloc.isValid());
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
        EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);

        tempSysCallsCtx.apiConfig.munmap.returnValue = -1;
        allocator.free(alloc);
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
        EXPECT_EQ(0, mockFdAllocator.freeCallCount);
        EXPECT_FALSE(logs.empty());
    }
    {
        Cal::Mocks::LogCaptureContext logs;
        Cal::Mocks::SysCallsContext tempSysCallsCtx;

        MockFdAllocator mockFdAllocator;
        MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
        UnmapConfig munmapConfig{true, {PROT_NONE, MAP_ANONYMOUS}};
        AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                      Cal::Utils::AddressRange(4096U, 4096U * 64)};
        auto alloc = allocator.allocate(4099);
        EXPECT_TRUE(alloc.isValid());
        EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);

        tempSysCallsCtx.apiConfig.mmap.returnValue = MAP_FAILED;
        allocator.free(alloc);
        EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
        EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.mmap.callCount);
        EXPECT_EQ(0, mockFdAllocator.freeCallCount);

        EXPECT_FALSE(logs.empty());
    }
}

TEST(AllocatorWithBoundedMmapToFd, whenFreeingAllocationWithoutMmappedPtrThenOnlyForwardsAllocationToBaseAllocator) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    MockFdAllocator mockFdAllocator;
    MmapConfig mmapConfig{PROT_READ | PROT_WRITE, MAP_SHARED};
    UnmapConfig munmapConfig{false};
    AllocatorWithBoundedMmapToFd<MockFdAllocator, true> allocator{mockFdAllocator, mmapConfig, munmapConfig,
                                                                  Cal::Utils::AddressRange(4096U, 4096U * 64)};
    auto alloc = AllocatorWithBoundedMmapToFd<MockFdAllocator, true>::AllocationT{FdAllocation<>{7, 4096U, false}, nullptr, 4096U};

    allocator.free(alloc);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(1, mockFdAllocator.freeCallCount);
}

TEST(ArenaAllocatorAllocate, whenHugeAllocationIsRequestedThenCreatesANonSharedBackingStorage) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity * 2;
    ArenaAllocator<MockFdAllocator, true> arenaAllocator{baseAllocator, allocationGranularity};
    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation.isValid());
    EXPECT_EQ(0U, allocation.getSubAllocationOffset());
    EXPECT_EQ(allocSize, allocation.getSubAllocationSize());
    ASSERT_NE(nullptr, allocation.getSourceAllocation());
    EXPECT_EQ(allocSize, allocation.getSourceAllocation()->getFileSize());
    arenaAllocator.free(allocation);
}

TEST(ArenaAllocatorAllocate, whenHugeAllocationIsRequestedButUnderlyingAllocatorFailsThenReturnsInvalidAllocation) {
    Cal::Mocks::LogCaptureContext logs;
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity * 2;
    ArenaAllocator<MockFdAllocator, true> arenaAllocator{baseAllocator, allocationGranularity};
    baseAllocator.fdToReturn = -1;
    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_FALSE(allocation.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ArenaAllocatorAllocate, whenLatestArenaSnapshotCanAccomodateNewAllocationThenUsesIt) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT arena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    arenaAllocator.latestArena->store(&arena);
    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation.isValid());

    EXPECT_TRUE(arena.getOffsetRange().contains({allocation.getSubAllocationOffset(), allocation.getSubAllocationSize()}));
    arenaAllocator.free(allocation);

    arenaAllocator.latestArena->store(nullptr);
    baseAllocator.free(arena.getUnderlyingAllocation());
}

TEST(ArenaAllocatorAllocate, whenLatestArenaSnapshotCannotAccomodateNewAllocationThenTriesReusingOldArenas) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT latestArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};
    ArenaAllocatorT::ArenaT recycledArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    arenaAllocator.latestArena->store(&latestArena);
    auto dummyAlloc = latestArena.allocate(allocationGranularity);
    arenaAllocator.recycledArenas->push_back(&recycledArena);

    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation.isValid());
    EXPECT_TRUE(recycledArena.getOffsetRange().contains({allocation.getSubAllocationOffset(), allocation.getSubAllocationSize()}));
    EXPECT_EQ(arenaAllocator.latestArena->load(), &recycledArena);

    arenaAllocator.free(allocation);

    latestArena.free(dummyAlloc);
    arenaAllocator.latestArena->store(nullptr);
    baseAllocator.free(latestArena.getUnderlyingAllocation());
    baseAllocator.free(recycledArena.getUnderlyingAllocation());
}

TEST(ArenaAllocatorAllocate, whenLatestArenaSnapshotCannotAccomodateNewAllocationAndThereAreNoOldArenasToRecycleThenAllocatesNewArena) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT latestArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    arenaAllocator.latestArena->store(&latestArena);
    auto dummyAlloc = latestArena.allocate(allocationGranularity);

    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation.isValid());
    EXPECT_NE(&latestArena, arenaAllocator.latestArena->load());
    EXPECT_EQ(arenaAllocator.latestArena->load(), allocation.getArena());
    EXPECT_TRUE(arenaAllocator.latestArena->load()->getOffsetRange().contains({allocation.getSubAllocationOffset(), allocation.getSubAllocationSize()}));

    arenaAllocator.free(allocation);

    latestArena.free(dummyAlloc);
    baseAllocator.free(latestArena.getUnderlyingAllocation());
}

TEST(ArenaAllocatorAllocate, whenRecycledArenaCannotAccomodateNewAllocationThenAllocatesNewArena) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT latestArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};
    ArenaAllocatorT::ArenaT recycledArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    arenaAllocator.latestArena->store(&latestArena);
    auto dummyAllocLatestArena = latestArena.allocate(allocationGranularity);
    arenaAllocator.recycledArenas->push_back(&recycledArena);
    auto dummyAllocRecycledArena = recycledArena.allocate(allocationGranularity);

    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation.isValid());
    EXPECT_NE(&latestArena, arenaAllocator.latestArena->load());
    EXPECT_NE(&recycledArena, arenaAllocator.latestArena->load());
    EXPECT_EQ(arenaAllocator.latestArena->load(), allocation.getArena());
    EXPECT_TRUE(arenaAllocator.latestArena->load()->getOffsetRange().contains({allocation.getSubAllocationOffset(), allocation.getSubAllocationSize()}));

    arenaAllocator.free(allocation);

    latestArena.free(dummyAllocLatestArena);
    baseAllocator.free(latestArena.getUnderlyingAllocation());
    recycledArena.free(dummyAllocRecycledArena);
    baseAllocator.free(recycledArena.getUnderlyingAllocation());
}

TEST(ArenaAllocatorAllocate, whenNeedsToCreateNewArenaButUnderlyingAllocatorFailsThenAllocatesReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::LogCaptureContext logs;

    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT latestArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    arenaAllocator.latestArena->store(&latestArena);
    auto dummyAlloc = latestArena.allocate(allocationGranularity);

    baseAllocator.fdToReturn = -1;
    auto allocation = arenaAllocator.allocate(allocSize);
    EXPECT_FALSE(allocation.isValid());

    latestArena.free(dummyAlloc);
    baseAllocator.free(latestArena.getUnderlyingAllocation());

    EXPECT_FALSE(logs.empty());
}

TEST(ArenaAllocatorAllocate, whenCreatingNewArenaButInParallelLatestArenaChangedThenUsesIt) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT firstArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};
    ArenaAllocatorT::ArenaT secondArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    auto dummyAllocFirstArena = firstArena.allocate(allocationGranularity);

    arenaAllocator.apiConfig.peekLatestArena.impl = [&](const ArenaAllocatorT &arenaAllocator) -> ArenaAllocatorT::ArenaT * {
        if (arenaAllocator.apiConfig.peekLatestArena.callCount == 0) {
            return &firstArena;
        } else {
            return &secondArena;
        }
    };
    auto allocation = arenaAllocator.allocate(allocSize);

    EXPECT_TRUE(allocation.isValid());
    EXPECT_EQ(&secondArena, allocation.getArena());
    EXPECT_TRUE(secondArena.getOffsetRange().contains({allocation.getSubAllocationOffset(), allocation.getSubAllocationSize()}));

    arenaAllocator.free(allocation);

    firstArena.free(dummyAllocFirstArena);
    baseAllocator.free(firstArena.getUnderlyingAllocation());
    baseAllocator.free(secondArena.getUnderlyingAllocation());
}

TEST(ArenaAllocatorAllocate, whenCreatingNewArenaAndInParallelLatestArenaChangedButItsAlreadyFullThenAllocatesNewArena) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};
    ArenaAllocatorT::ArenaT firstArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};
    ArenaAllocatorT::ArenaT secondArena{baseAllocator.allocate(allocationGranularity), Cal::Utils::OffsetRange{size_t(0U), allocationGranularity}};

    auto dummyAllocFirstArena = firstArena.allocate(allocationGranularity);
    auto dummyAllocSecondArena = secondArena.allocate(allocationGranularity);

    arenaAllocator.apiConfig.peekLatestArena.impl = [&](const ArenaAllocatorT &arenaAllocator) -> ArenaAllocatorT::ArenaT * {
        if (arenaAllocator.apiConfig.peekLatestArena.callCount == 0) {
            return &firstArena;
        } else {
            return &secondArena;
        }
    };
    auto allocation = arenaAllocator.allocate(allocSize);

    EXPECT_TRUE(allocation.isValid());
    EXPECT_NE(&firstArena, arenaAllocator.latestArena->load());
    EXPECT_NE(&secondArena, arenaAllocator.latestArena->load());
    EXPECT_EQ(arenaAllocator.latestArena->load(), allocation.getArena());
    EXPECT_TRUE(arenaAllocator.latestArena->load()->getOffsetRange().contains({allocation.getSubAllocationOffset(), allocation.getSubAllocationSize()}));

    arenaAllocator.free(allocation);

    firstArena.free(dummyAllocFirstArena);
    baseAllocator.free(firstArena.getUnderlyingAllocation());
    secondArena.free(dummyAllocSecondArena);
    baseAllocator.free(secondArena.getUnderlyingAllocation());
}

TEST(ArenaAllocatorFree, whenArenaOfFreedAllocationCanBeRecycledThenPlaceItInRecycleList) {
    MockFdAllocator baseAllocator;
    size_t allocationGranularity = 4096U * 4;
    size_t allocSize = allocationGranularity / 2;
    using ArenaAllocatorT = MockArenaAllocator<MockFdAllocator, true>;
    ArenaAllocatorT arenaAllocator{baseAllocator, allocationGranularity};

    auto allocation1 = arenaAllocator.allocate(allocSize);
    auto allocation2 = arenaAllocator.allocate(allocSize);
    auto allocation3 = arenaAllocator.allocate(allocSize);
    auto allocation4 = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation1.isValid());
    EXPECT_TRUE(allocation2.isValid());
    EXPECT_TRUE(allocation3.isValid());
    EXPECT_TRUE(allocation4.isValid());
    EXPECT_EQ(allocation1.getArena(), allocation2.getArena());
    EXPECT_NE(allocation2.getArena(), allocation3.getArena());
    EXPECT_EQ(allocation3.getArena(), allocation4.getArena());

    arenaAllocator.free(allocation3);
    EXPECT_EQ(arenaAllocator.peekLatestArena(), allocation4.getArena());
    arenaAllocator.free(allocation1);
    EXPECT_EQ(arenaAllocator.peekLatestArena(), allocation4.getArena());

    auto allocation5 = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation5.isValid());
    EXPECT_EQ(allocation5.getArena(), allocation4.getArena());

    auto allocation6 = arenaAllocator.allocate(allocSize);
    EXPECT_TRUE(allocation5.isValid());
    EXPECT_EQ(allocation6.getArena(), allocation2.getArena());

    arenaAllocator.free(allocation2);
    arenaAllocator.free(allocation4);
    arenaAllocator.free(allocation5);
    arenaAllocator.free(allocation6);
}

} // namespace Cal::Ult
