/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "service/service.h"
#include "shared/utils.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/sys_mock.h"

#include <atomic>
#include <string>

namespace Cal {

namespace Ult {
TEST(popcount, givenIntegerThenReturnsNumberOfBitsSet) {
    static_assert(Cal::Utils::popcount(0) == 0);
    static_assert(Cal::Utils::popcount(1) == 1);
    static_assert(Cal::Utils::popcount(2) == 1);
    static_assert(Cal::Utils::popcount(3) == 2);
    static_assert(Cal::Utils::popcount(4096) == 1);
    static_assert(Cal::Utils::popcount(4097) == 2);
    static_assert(Cal::Utils::popcount(0b10110101010101010101111010110) == 17);
    static_assert(Cal::Utils::popcount(std::numeric_limits<uint64_t>::max()) == 64);
}

TEST(ipow2, givenIntegerThenReturnsTrueOnlyOfIsPowerOf2) {
    static_assert(Cal::Utils::isPow2(1));
    static_assert(Cal::Utils::isPow2(2));
    static_assert(Cal::Utils::isPow2(4));
    static_assert(Cal::Utils::isPow2(8));
    static_assert(Cal::Utils::isPow2(4096));
    static_assert(Cal::Utils::isPow2(1ULL << (64 - 1)));

    static_assert(false == Cal::Utils::isPow2(0));
    static_assert(false == Cal::Utils::isPow2(3));
    static_assert(false == Cal::Utils::isPow2(5));
    static_assert(false == Cal::Utils::isPow2(9));
    static_assert(false == Cal::Utils::isPow2(4097));
    static_assert(false == Cal::Utils::isPow2(std::numeric_limits<uint64_t>::max()));
}

TEST(isAlignedPow2, givenPointerOrIntegerThenReturnsTrueOnlyIfAlignmentIsSatisfied) {
    using namespace Cal::Utils;
    static constexpr size_t k = 1024;
    static constexpr size_t m = 1024 * k;
    static constexpr size_t g = 1024 * m;
    uintptr_t testValuesPow2[] = {1, 2, 4, 8, 16, 32, 64, 1 * k, 2 * k, 4 * k, 8 * k, 16 * k, 32 * k, 64 * k, 1 * m, 2 * m, 4 * m, 8 * m, 16 * m, 32 * m, 64 * m,
                                  static_cast<uintptr_t>(1) << (sizeof(uintptr_t) * 8 - 1)};
    for (auto v : testValuesPow2) {
        auto integer = v;
        auto pointer = reinterpret_cast<uintptr_t>(v);
#define TEST_ALIGNMENT(ALIGNMENT)                                                                                                        \
    EXPECT_TRUE(isAlignedPow2<ALIGNMENT>(integer) ^ (v < ALIGNMENT)) << "isAlignedPow2<" << ALIGNMENT << ">(" << integer << ")";         \
    EXPECT_TRUE(isAlignedPow2<ALIGNMENT>(pointer) ^ (v < ALIGNMENT)) << "isAlignedPow2<" << ALIGNMENT << ">(" << pointer << ")";         \
    EXPECT_TRUE(isAlignedPow2<ALIGNMENT>(0)) << "isAlignedPow2<" << ALIGNMENT << ">(" << 0 << ")";                                       \
    EXPECT_FALSE(isAlignedPow2<ALIGNMENT>(integer - 1) && (integer > 1)) << "isAlignedPow2<" << ALIGNMENT << ">(" << integer - 1 << ")"; \
    EXPECT_FALSE(isAlignedPow2<ALIGNMENT>(integer + 1) && ((integer + 1) != ALIGNMENT)) << "isAlignedPow2<" << ALIGNMENT << ">(" << integer + 1 << ")";
        TEST_ALIGNMENT(2);
        TEST_ALIGNMENT(4);
        TEST_ALIGNMENT(8);
        TEST_ALIGNMENT(16);
        TEST_ALIGNMENT(32);
        TEST_ALIGNMENT(64);
        TEST_ALIGNMENT(4 * k);
        TEST_ALIGNMENT(64 * k);
        TEST_ALIGNMENT(1 * m);
        TEST_ALIGNMENT(2 * m);
        TEST_ALIGNMENT(1 * g);
#undef TEST_ALIGNMENT
    }
}

TEST(alignUpPow2, givenNumberThenAlignsItToGivenPowerOf2) {
    std::pair<uintptr_t, uintptr_t> testValues[] = {
        {0U, 0U},
        {4U, 1U},
        {4U, 2U},
        {4U, 3U},
        {4U, 4U},
        {8U, 5U},
        {8U, 6U},
        {8U, 7U},
        {8U, 8U},
        {12U, 9U},
    };
    for (auto testValue : testValues) {
        auto [expected, tested] = testValue;
        EXPECT_EQ(expected, Cal::Utils::alignUpPow2<4>(tested));
        EXPECT_EQ(reinterpret_cast<void *>(expected), reinterpret_cast<void *>(Cal::Utils::alignUpPow2<4>(tested)));
    }
}

TEST(alignUp, givenNumberThenAlignsItToGivenPowerOf2) {
    std::pair<uintptr_t, uintptr_t> testValues[] = {
        {0U, 0U},
        {3U, 1U},
        {3U, 2U},
        {3U, 3U},
        {6U, 4U},
        {6U, 5U},
        {6U, 6U},
        {9U, 7U},
        {9U, 8U},
        {9U, 9U},
    };
    for (auto testValue : testValues) {
        auto [expected, tested] = testValue;
        EXPECT_EQ(expected, Cal::Utils::alignUp<3>(tested));
        EXPECT_EQ(reinterpret_cast<void *>(expected), reinterpret_cast<void *>(Cal::Utils::alignUp<3>(tested)));
    }
}

TEST(byteDistance, givenTwoPointersThenReturnsDistanceInBytesBetweenThem) {
    EXPECT_EQ(0, Cal::Utils::byteDistance(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), reinterpret_cast<void *>(static_cast<uintptr_t>(4090U))));
    EXPECT_EQ(6, Cal::Utils::byteDistance(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), reinterpret_cast<void *>(static_cast<uintptr_t>(4096U))));
    EXPECT_EQ(-6, Cal::Utils::byteDistance(reinterpret_cast<void *>(static_cast<uintptr_t>(4096U)), reinterpret_cast<void *>(static_cast<uintptr_t>(4090U))));

    EXPECT_EQ(0u, Cal::Utils::byteDistanceAbs(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), reinterpret_cast<void *>(static_cast<uintptr_t>(4090U))));
    EXPECT_EQ(6u, Cal::Utils::byteDistanceAbs(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), reinterpret_cast<void *>(static_cast<uintptr_t>(4096U))));
    EXPECT_EQ(6u, Cal::Utils::byteDistanceAbs(reinterpret_cast<void *>(static_cast<uintptr_t>(4096U)), reinterpret_cast<void *>(static_cast<uintptr_t>(4090U))));
}

TEST(moveByBytes, givenBasePointerAndOffsetThenReturnsPointerThatIsOffsetBytesGreaterThanBase) {
    EXPECT_EQ(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), Cal::Utils::moveByBytes(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), 0));
    EXPECT_EQ(reinterpret_cast<void *>(static_cast<uintptr_t>(4096U)), Cal::Utils::moveByBytes(reinterpret_cast<void *>(static_cast<uintptr_t>(4090U)), 6));
}

TEST(AddressRange, givenDifferentConstructionMethodsThenRangeIsExpressedProperly) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange defaultAddr;
    EXPECT_EQ(0U, defaultAddr.start);
    EXPECT_EQ(std::numeric_limits<uintptr_t>::max(), defaultAddr.end);

    Cal::Utils::AddressRange uintptrUintptr(start, end);
    EXPECT_EQ(start, uintptrUintptr.start);
    EXPECT_EQ(end, uintptrUintptr.end);

    Cal::Utils::AddressRange u32U32(static_cast<uint32_t>(start), static_cast<uint32_t>(end));
    EXPECT_EQ(start, u32U32.start);
    EXPECT_EQ(end, u32U32.end);

    Cal::Utils::AddressRange ptrPtr(reinterpret_cast<void *>(start), reinterpret_cast<void *>(end));
    EXPECT_EQ(start, ptrPtr.start);
    EXPECT_EQ(end, ptrPtr.end);

    Cal::Utils::AddressRange ptrSize(reinterpret_cast<void *>(start), end - start);
    EXPECT_EQ(start, ptrSize.start);
    EXPECT_EQ(end, ptrSize.end);

    Cal::Utils::AddressRange ptr(reinterpret_cast<void *>(start));
    EXPECT_EQ(start, ptr.start);
    EXPECT_EQ(start + 1, ptr.end);

    Cal::Utils::AddressRange uintptr(start);
    EXPECT_EQ(start, uintptr.start);
    EXPECT_EQ(start + 1, uintptr.end);
}

TEST(AddressRange, sizeReturnsDifferenceBetweenStartAndEnd) {
    uintptr_t start = 4096U;
    uintptr_t end = 8193U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_EQ(4097U, range.size());
}

TEST(AddressRange, givenSubRangeThenContainsReturnsTrue) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_TRUE(range.contains({start}));
    EXPECT_TRUE(range.contains({end - 1}));
    EXPECT_TRUE(range.contains({start, end}));
    EXPECT_TRUE(range.contains({start + 7, end - 3}));
}

TEST(AddressRange, givenDisjointRangesThenContainsReturnsFalse) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_FALSE(range.contains({start - 1}));
    EXPECT_FALSE(range.contains({end}));
    EXPECT_FALSE(range.contains({start - 3, start}));
    EXPECT_FALSE(range.contains({start - 3, start - 1}));
    EXPECT_FALSE(range.contains({end, end + 3}));
    EXPECT_FALSE(range.contains({end + 1, end + 3}));
}

TEST(AddressRange, givenPartiallyJointRangesThenContainsReturnsFalse) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_FALSE(range.contains({start - 3, start + 1}));
    EXPECT_FALSE(range.contains({end - 1, end + 3}));
    EXPECT_FALSE(range.contains({start - 1, end}));
    EXPECT_FALSE(range.contains({start - 1, end + 1}));
    EXPECT_FALSE(range.contains({start, end + 1}));
    EXPECT_FALSE(range.contains({start + 3, end + 1}));
}

TEST(AddressRange, givenSubRangeThenIntersectsReturnsTrue) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_TRUE(range.intersects({start}));
    EXPECT_TRUE(range.intersects({end - 1}));
    EXPECT_TRUE(range.intersects({start, end}));
    EXPECT_TRUE(range.intersects({start + 7, end - 3}));

    EXPECT_TRUE((Cal::Utils::AddressRange{start}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{end - 1}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{start, end}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{start + 7, end - 3}.intersects(range)));
}

TEST(AddressRange, givenDisjointRangesThenIntersectsReturnsFalse) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_FALSE(range.intersects({start - 1}));
    EXPECT_FALSE(range.intersects({end}));
    EXPECT_FALSE(range.intersects({start - 3, start}));
    EXPECT_FALSE(range.intersects({start - 3, start - 1}));
    EXPECT_FALSE(range.intersects({end, end + 3}));
    EXPECT_FALSE(range.intersects({end + 1, end + 3}));

    EXPECT_FALSE((Cal::Utils::AddressRange{start - 1}.intersects(range)));
    EXPECT_FALSE((Cal::Utils::AddressRange{end}.intersects(range)));
    EXPECT_FALSE((Cal::Utils::AddressRange{start - 3, start}.intersects(range)));
    EXPECT_FALSE((Cal::Utils::AddressRange{start - 3, start - 1}.intersects(range)));
    EXPECT_FALSE((Cal::Utils::AddressRange{end, end + 3}.intersects(range)));
    EXPECT_FALSE((Cal::Utils::AddressRange{end + 1, end + 3}.intersects(range)));
}

TEST(AddressRange, givenPartiallyJointRangesThenIntersectsReturnsFalse) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;

    Cal::Utils::AddressRange range(start, end);

    EXPECT_TRUE(range.intersects({start - 3, start + 1}));
    EXPECT_TRUE(range.intersects({end - 1, end + 3}));
    EXPECT_TRUE(range.intersects({start - 1, end}));
    EXPECT_TRUE(range.intersects({start - 1, end + 1}));
    EXPECT_TRUE(range.intersects({start, end + 1}));
    EXPECT_TRUE(range.intersects({start + 3, end + 1}));

    EXPECT_TRUE((Cal::Utils::AddressRange{start - 3, start + 1}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{end - 1, end + 3}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{start - 1, end}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{start - 1, end + 1}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{start, end + 1}.intersects(range)));
    EXPECT_TRUE((Cal::Utils::AddressRange{start + 3, end + 1}.intersects(range)));
}

TEST(PartitionedAddressRange, whenCreatedFromAddressRangeThenExpressesThatAddressRange) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;
    Cal::Utils::AddressRange range(start, end);
    Cal::Utils::PartitionedAddressRange partitionedRange(range);

    EXPECT_EQ(range.start, partitionedRange.getBoundingRange().start);
    EXPECT_EQ(range.end, partitionedRange.getBoundingRange().end);
}

TEST(PartitionedAddressRange, whenAddingDisjointSubrangesThenRangeGrows) {
    uintptr_t start = 4096U;
    uintptr_t end = 8192U;
    Cal::Utils::AddressRange range(start, end);

    Cal::Utils::PartitionedAddressRange partitionedRange(range);

    uintptr_t left = 2048;
    uintptr_t right = 16000;

    EXPECT_EQ(start, partitionedRange.getBoundingRange().start);
    EXPECT_EQ(end, partitionedRange.getBoundingRange().end);

    partitionedRange.insertSubRange(Cal::Utils::PartitionedAddressRange({start - 1, end + 1}));
    EXPECT_EQ(start - 1, partitionedRange.getBoundingRange().start);
    EXPECT_EQ(end + 1, partitionedRange.getBoundingRange().end);

    partitionedRange.insertSubRange(Cal::Utils::PartitionedAddressRange({left, left + 7}));
    EXPECT_EQ(left, partitionedRange.getBoundingRange().start);
    EXPECT_EQ(end + 1, partitionedRange.getBoundingRange().end);

    partitionedRange.insertSubRange(Cal::Utils::PartitionedAddressRange({end + 1, right}));
    EXPECT_EQ(left, partitionedRange.getBoundingRange().start);
    EXPECT_EQ(right, partitionedRange.getBoundingRange().end);
}

TEST(PartitionedAddressRange, whenAddingSubrangesThenTheyAreOrdered) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});

    static constexpr int numSubRanges = 7;
    Cal::Utils::AddressRange sortedSubranges[numSubRanges] = {{0U, 1024U}, {1024U, 2048U}, {2048U, 4096U}, {4096U, 8192U}, {16384U, 20480U}, {20480U, 20487U}, {20487U, 20489U}};
    int orderOfInsert[numSubRanges] = {1, 2, 4, 0, 3, 5, 6};

    for (auto &idx : orderOfInsert) {
        partitionedRange.insertSubRange(sortedSubranges[idx]);
    }

    auto &subRanges = partitionedRange.getSubRanges();
    ASSERT_EQ(static_cast<unsigned>(numSubRanges), subRanges.size());
    for (int idx = 0; idx < numSubRanges; ++idx) {
        auto bounds = subRanges[idx].getBoundingRange();
        EXPECT_EQ(sortedSubranges[idx], bounds) << idx;
    }
}

TEST(PartitionedAddressRange, whenNoSubrangesThenFindReturnsNull) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({4096U, 8192U}));
}

TEST(PartitionedAddressRange, givenDisjointAddressThenFindReturnsNull) {
    Cal::Utils::PartitionedAddressRange partitionedRange({0, 4096U});
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({8192U, 8196U}));
}

TEST(PartitionedAddressRange, whenSubRangeIsProvidedThenFindReturnsItsRepresentationOrNullIfNotContained) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});

    Cal::Utils::AddressRange sortedSubranges[] = {{0U, 1024U}, {2048U, 4096U}, {4096U, 8192U}, {16384U, 20480U}, {20480U, 20487U}, {20487U, 20489U}};
    Cal::Utils::AddressRange missingRange = {1024U, 2048U};

    for (auto subRange : sortedSubranges) {
        EXPECT_EQ(nullptr, partitionedRange.findSubRange(subRange)) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.end})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({(subRange.start + subRange.end / 2)})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start - 1, subRange.end})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start, subRange.end + 1})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start - 1, subRange.end + 1})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start + 1, subRange.end - 1})) << subRange.start;
        partitionedRange.insertSubRange(subRange);
        EXPECT_EQ(subRange, partitionedRange.findSubRange(subRange)->getBoundingRange()) << subRange.start;
        EXPECT_EQ(subRange, partitionedRange.findSubRange({subRange.start})->getBoundingRange()) << subRange.start;
        if (partitionedRange.findSubRange({subRange.end})) {
            EXPECT_NE(subRange, partitionedRange.findSubRange({subRange.end})->getBoundingRange()) << subRange.start;
        }
        EXPECT_EQ(subRange, partitionedRange.findSubRange({(subRange.start + subRange.end) / 2})->getBoundingRange()) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start - 1, subRange.end})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start, subRange.end + 1})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start - 1, subRange.end + 1})) << subRange.start;
        EXPECT_EQ(subRange, partitionedRange.findSubRange({subRange.start + 1, subRange.end - 1})->getBoundingRange()) << subRange.start;
    }

    for (auto subRange : sortedSubranges) {
        EXPECT_EQ(subRange, partitionedRange.findSubRange(subRange)->getBoundingRange()) << subRange.start;
        EXPECT_EQ(subRange, partitionedRange.findSubRange({subRange.start})->getBoundingRange()) << subRange.start;
        if (partitionedRange.findSubRange({subRange.end})) {
            EXPECT_NE(subRange, partitionedRange.findSubRange({subRange.end})->getBoundingRange()) << subRange.start;
        }
        EXPECT_EQ(subRange, partitionedRange.findSubRange({(subRange.start + subRange.end) / 2})->getBoundingRange()) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start - 1, subRange.end})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start, subRange.end + 1})) << subRange.start;
        EXPECT_EQ(nullptr, partitionedRange.findSubRange({subRange.start - 1, subRange.end + 1})) << subRange.start;
        EXPECT_EQ(subRange, partitionedRange.findSubRange({subRange.start + 1, subRange.end - 1})->getBoundingRange()) << subRange.start;
    }

    EXPECT_EQ(nullptr, partitionedRange.findSubRange(missingRange));
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({missingRange.start}));
    if (partitionedRange.findSubRange({missingRange.end})) {
        EXPECT_NE(missingRange, partitionedRange.findSubRange({missingRange.end})->getBoundingRange());
    }
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({(missingRange.start + missingRange.end) / 2}));
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({missingRange.start - 1, missingRange.end}));
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({missingRange.start, missingRange.end + 1}));
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({missingRange.start - 1, missingRange.end + 1}));
    EXPECT_EQ(nullptr, partitionedRange.findSubRange({missingRange.start + 1, missingRange.end - 1}));
}

TEST(PartitionedAddressRange, givenNoSubrangesThenMergeDoesNothing) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.mergeSubranges();
    EXPECT_TRUE(partitionedRange.getSubRanges().empty());
}

TEST(PartitionedAddressRange, givenOneSubrangeThenMergeDoesNothing) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    Cal::Utils::AddressRange subRange = {4096U, 8192U};
    partitionedRange.insertSubRange(subRange);
    partitionedRange.mergeSubranges();
    ASSERT_EQ(1U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(subRange, partitionedRange.getSubRanges()[0].getBoundingRange());
}

TEST(PartitionedAddressRange, givenTwoNonAdjacentSubrangesThenMergeDoesNothing) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});

    Cal::Utils::AddressRange sortedSubranges[] = {{0U, 1024U}, {2048U, 4096U}};
    for (auto subRange : sortedSubranges) {
        partitionedRange.insertSubRange(subRange);
    }

    partitionedRange.mergeSubranges();
    ASSERT_EQ(2U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(sortedSubranges[0], partitionedRange.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(sortedSubranges[1], partitionedRange.getSubRanges()[1].getBoundingRange());

    EXPECT_TRUE(partitionedRange.getSubRanges()[0].getSubRanges().empty());
    EXPECT_TRUE(partitionedRange.getSubRanges()[1].getSubRanges().empty());
}

TEST(PartitionedAddressRange, givenTwoAdjacentSubrangesThenMergeCreatesABoundingRange) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});

    Cal::Utils::AddressRange sortedSubranges[] = {{0U, 1024U}, {1024U, 4096U}};
    for (auto subRange : sortedSubranges) {
        partitionedRange.insertSubRange(subRange);
    }

    partitionedRange.mergeSubranges();
    ASSERT_EQ(1U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(sortedSubranges[0].start, sortedSubranges[1].end), partitionedRange.getSubRanges()[0].getBoundingRange());

    ASSERT_EQ(2U, partitionedRange.getSubRanges()[0].getSubRanges().size());
    EXPECT_EQ(sortedSubranges[0], partitionedRange.getSubRanges()[0].getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(sortedSubranges[1], partitionedRange.getSubRanges()[0].getSubRanges()[1].getBoundingRange());

    EXPECT_TRUE(partitionedRange.getSubRanges()[0].getSubRanges()[0].getSubRanges().empty());
    EXPECT_TRUE(partitionedRange.getSubRanges()[0].getSubRanges()[1].getSubRanges().empty());
}

TEST(PartitionedAddressRange, givenMultipleSubrangesThenMergeCreatesBoundingRangesForAdjacentRanges) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});

    Cal::Utils::AddressRange sortedSubranges[] = {{0U, 1024U}, {2048U, 4096U}, {4096U, 8192U}, {8192U, 20480U}, {20481U, 20487U}, {20487U, 20489U}, {20490U, 20491U}};
    for (auto subRange : sortedSubranges) {
        partitionedRange.insertSubRange(subRange);
    }

    partitionedRange.mergeSubranges();
    ASSERT_EQ(4U, partitionedRange.getSubRanges().size());

    EXPECT_EQ(sortedSubranges[0], partitionedRange.getSubRanges()[0].getBoundingRange());
    EXPECT_TRUE(partitionedRange.getSubRanges()[0].getSubRanges().empty());

    EXPECT_EQ(Cal::Utils::AddressRange(sortedSubranges[1].start, sortedSubranges[3].end), partitionedRange.getSubRanges()[1].getBoundingRange());
    ASSERT_EQ(3U, partitionedRange.getSubRanges()[1].getSubRanges().size());
    EXPECT_EQ(sortedSubranges[1], partitionedRange.getSubRanges()[1].getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(sortedSubranges[2], partitionedRange.getSubRanges()[1].getSubRanges()[1].getBoundingRange());
    EXPECT_EQ(sortedSubranges[3], partitionedRange.getSubRanges()[1].getSubRanges()[2].getBoundingRange());

    EXPECT_EQ(Cal::Utils::AddressRange(sortedSubranges[4].start, sortedSubranges[5].end), partitionedRange.getSubRanges()[2].getBoundingRange());
    ASSERT_EQ(2U, partitionedRange.getSubRanges()[2].getSubRanges().size());
    EXPECT_EQ(sortedSubranges[4], partitionedRange.getSubRanges()[2].getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(sortedSubranges[5], partitionedRange.getSubRanges()[2].getSubRanges()[1].getBoundingRange());

    EXPECT_EQ(sortedSubranges[6], partitionedRange.getSubRanges()[3].getBoundingRange());
    EXPECT_TRUE(partitionedRange.getSubRanges()[3].getSubRanges().empty());
}

TEST(PartitionedAddressRange, givenNonIntersectingRangeThenIntersectsReturnsFalse) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({9000U, 9010U});
    EXPECT_FALSE(partitionedRange.intersectsSubRanges({0U, 4096U}));
    EXPECT_FALSE(partitionedRange.intersectsSubRanges({8192U, 9000U}));
    EXPECT_FALSE(partitionedRange.intersectsSubRanges({9010U, 9020U}));
}

TEST(PartitionedAddressRange, givenIntersectingRangeThenIntersectsReturnsTrue) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({9000U, 9010U});
    EXPECT_TRUE(partitionedRange.intersectsSubRanges({0U, 4097U}));
    EXPECT_TRUE(partitionedRange.intersectsSubRanges({8191U, 9000U}));
    EXPECT_TRUE(partitionedRange.intersectsSubRanges({8192U, 9001U}));
    EXPECT_TRUE(partitionedRange.intersectsSubRanges({8191U, 9001U}));
    EXPECT_TRUE(partitionedRange.intersectsSubRanges({9009U, 9020U}));
    EXPECT_TRUE(partitionedRange.intersectsSubRanges({0U, 9020U}));
}

TEST(PartitionedAddressRange, givenNonIntersectingRangeThenGetIntersectedSubRangesReturnsEmptyList) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({9000U, 9010U});
    EXPECT_TRUE(partitionedRange.getIntersectedSubRanges({0U, 4096U}).empty());
    EXPECT_TRUE(partitionedRange.getIntersectedSubRanges({8192U, 9000U}).empty());
    EXPECT_TRUE(partitionedRange.getIntersectedSubRanges({9010U, 9020U}).empty());
}

TEST(PartitionedAddressRange, givenIntersectingRangeThenGetIntersectedSubRangesReturnsListOfAffectedSubRanges) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({9000U, 9010U});
    ASSERT_EQ(1U, partitionedRange.getIntersectedSubRanges({0U, 4097U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(4096U, 8192U), partitionedRange.getIntersectedSubRanges({0U, 4097U})[0]->getBoundingRange());

    ASSERT_EQ(1U, partitionedRange.getIntersectedSubRanges({8191U, 9000U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(4096U, 8192U), partitionedRange.getIntersectedSubRanges({8191U, 9000U})[0]->getBoundingRange());

    ASSERT_EQ(1U, partitionedRange.getIntersectedSubRanges({8192U, 9001U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(9000U, 9010U), partitionedRange.getIntersectedSubRanges({8192U, 9001U})[0]->getBoundingRange());

    ASSERT_EQ(2U, partitionedRange.getIntersectedSubRanges({8191U, 9001U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(4096U, 8192U), partitionedRange.getIntersectedSubRanges({8191U, 9001U})[0]->getBoundingRange());
    EXPECT_EQ(Cal::Utils::AddressRange(9000U, 9010U), partitionedRange.getIntersectedSubRanges({8191U, 9001U})[1]->getBoundingRange());

    ASSERT_EQ(1U, partitionedRange.getIntersectedSubRanges({9009U, 9020U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(9000U, 9010U), partitionedRange.getIntersectedSubRanges({9009U, 9020U})[0]->getBoundingRange());

    ASSERT_EQ(2U, partitionedRange.getIntersectedSubRanges({0U, 9020U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(4096U, 8192U), partitionedRange.getIntersectedSubRanges({0U, 9020U})[0]->getBoundingRange());
    EXPECT_EQ(Cal::Utils::AddressRange(9000U, 9010U), partitionedRange.getIntersectedSubRanges({0U, 9020U})[1]->getBoundingRange());
}

TEST(PartitionedAddressRange, givenNonIntersectingRangeThenDiffReturnsWholeRange) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({9000U, 9010U});

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({0U, 4096U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(0U, 4096U), partitionedRange.getSubRangesDiffFrom({0U, 4096U})[0]);

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({8192U, 9000U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(8192U, 9000U), partitionedRange.getSubRangesDiffFrom({8192U, 9000U})[0]);

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({9010U, 9020U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(9010U, 9020U), partitionedRange.getSubRangesDiffFrom({9010U, 9020U})[0]);
}

TEST(PartitionedAddressRange, givenContainedRangeThenDiffReturnsEmptyList) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({8192U, 9010U});

    EXPECT_TRUE(partitionedRange.getSubRangesDiffFrom({4096U, 8192U}).empty());
    EXPECT_TRUE(partitionedRange.getSubRangesDiffFrom({4097U, 8191U}).empty());
    EXPECT_TRUE(partitionedRange.getSubRangesDiffFrom({8192U, 9010U}).empty());
    EXPECT_TRUE(partitionedRange.getSubRangesDiffFrom({4097U, 9009U}).empty());
    EXPECT_TRUE(partitionedRange.getSubRangesDiffFrom({4096U, 9010U}).empty());
}

TEST(PartitionedAddressRange, givenIntersectingRangeThenDiffReturnsRangesThatAreNotCovered) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    partitionedRange.insertSubRange({4096U, 8192U});
    partitionedRange.insertSubRange({9000U, 9010U});
    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({0U, 4097U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(0, 4096U), partitionedRange.getSubRangesDiffFrom({0U, 4097U})[0]);

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({8191U, 9000U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(8192U, 9000U), partitionedRange.getSubRangesDiffFrom({8191U, 9000U})[0]);

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({8192U, 9001U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(8192U, 9000U), partitionedRange.getSubRangesDiffFrom({8192U, 9001U})[0]);

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({8191U, 9001U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(8192U, 9000U), partitionedRange.getSubRangesDiffFrom({8191U, 9001U})[0]);

    ASSERT_EQ(1U, partitionedRange.getSubRangesDiffFrom({9009U, 9020U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(9010U, 9020U), partitionedRange.getSubRangesDiffFrom({9009U, 9020U})[0]);

    ASSERT_EQ(3U, partitionedRange.getSubRangesDiffFrom({0U, 9020U}).size());
    EXPECT_EQ(Cal::Utils::AddressRange(0, 4096U), partitionedRange.getSubRangesDiffFrom({0U, 9020U})[0]);
    EXPECT_EQ(Cal::Utils::AddressRange(8192U, 9000U), partitionedRange.getSubRangesDiffFrom({0U, 9020U})[1]);
    EXPECT_EQ(Cal::Utils::AddressRange(9010U, 9020U), partitionedRange.getSubRangesDiffFrom({0U, 9020U})[2]);
}

TEST(PartitionedAddressRange, whenDestroyingNonInterSectingSubRangeThenDoNothing) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    Cal::Utils::AddressRange range = {4096U, 8192U};
    partitionedRange.insertSubRange(range);

    auto numImpacted = partitionedRange.destroySubRange({0U, 4096U});
    EXPECT_EQ(0, numImpacted);

    numImpacted = partitionedRange.destroySubRange({8192U, 8192U + 4096U});
    EXPECT_EQ(0, numImpacted);

    ASSERT_EQ(1U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(range, partitionedRange.getSubRanges()[0].getBoundingRange());
}

TEST(PartitionedAddressRange, whenDestroyingWholeSubRangeThenRemoveIt) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    Cal::Utils::AddressRange range = {4096U, 8192U};
    partitionedRange.insertSubRange(range);

    auto numImpacted = partitionedRange.destroySubRange(range);
    EXPECT_EQ(1, numImpacted);

    EXPECT_EQ(0U, partitionedRange.getSubRanges().size());
}

TEST(PartitionedAddressRange, whenDestroyingMiddleOfSubRangeThenSplitIt) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    size_t pageSize = 4096U;
    Cal::Utils::AddressRange range = {pageSize, pageSize * 4};
    Cal::Utils::AddressRange middle = {range.start + pageSize, range.end - pageSize};
    Cal::Utils::AddressRange left = {range.start, middle.start};
    Cal::Utils::AddressRange right = {middle.end, range.end};
    partitionedRange.insertSubRange(range);

    auto numImpacted = partitionedRange.destroySubRange(middle);
    EXPECT_EQ(1, numImpacted);

    ASSERT_EQ(2U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(left, partitionedRange.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(right, partitionedRange.getSubRanges()[1].getBoundingRange());
}

TEST(PartitionedAddressRange, whenDestroyingHeadOrTailOfSubRangeThenTruncateIt) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    size_t pageSize = 4096U;
    Cal::Utils::AddressRange range = {pageSize, pageSize * 4};
    Cal::Utils::AddressRange middle = {range.start + pageSize, range.end - pageSize};
    Cal::Utils::AddressRange left = {range.start, middle.start};
    Cal::Utils::AddressRange right = {middle.end, range.end};
    partitionedRange.insertSubRange(range);

    auto numImpacted = partitionedRange.destroySubRange(left);
    EXPECT_EQ(1, numImpacted);
    numImpacted = partitionedRange.destroySubRange(right);
    EXPECT_EQ(1, numImpacted);

    ASSERT_EQ(1U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(middle, partitionedRange.getSubRanges()[0].getBoundingRange());
}

TEST(PartitionedAddressRange, whenDestroyingSpanOfSubrangesThenAffectAllInRange) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    uintptr_t pageSize = 4096U;
    Cal::Utils::AddressRange ranges[4] = {{static_cast<uintptr_t>(0U), pageSize * 2}, {pageSize * 2, pageSize * 3}, {pageSize * 4, pageSize * 5}, {pageSize * 5, pageSize * 7}};
    for (auto range : ranges) {
        partitionedRange.insertSubRange(range);
    }

    auto numImpacted = partitionedRange.destroySubRange({ranges[1].start, ranges[2].end});
    EXPECT_EQ(2, numImpacted);
    ASSERT_EQ(2U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(ranges[0], partitionedRange.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(ranges[3], partitionedRange.getSubRanges()[1].getBoundingRange());

    numImpacted = partitionedRange.destroySubRange({ranges[0].start + pageSize, ranges[3].end - pageSize});
    EXPECT_EQ(2, numImpacted);
    ASSERT_EQ(2U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(ranges[0].start, ranges[0].start + pageSize), partitionedRange.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(Cal::Utils::AddressRange(ranges[3].end - pageSize, ranges[3].end), partitionedRange.getSubRanges()[1].getBoundingRange());

    numImpacted = partitionedRange.destroySubRange({ranges[0].start, ranges[3].end});
    EXPECT_EQ(2, numImpacted);
    EXPECT_EQ(0U, partitionedRange.getSubRanges().size());
}

TEST(PartitionedAddressRange, whenDestroyingSubRangesThenAffectChildSubRangesAsWell) {
    Cal::Utils::PartitionedAddressRange partitionedRange({});
    size_t pageSize = 4096U;
    Cal::Utils::AddressRange range = {pageSize, pageSize * 4};
    Cal::Utils::AddressRange middle = {range.start + pageSize, range.end - pageSize};
    Cal::Utils::AddressRange left = {range.start, middle.start};
    Cal::Utils::AddressRange right = {middle.end, range.end};
    partitionedRange.insertSubRange(range);
    partitionedRange.findSubRange(range)->insertSubRange(range);

    auto numImpacted = partitionedRange.destroySubRange(middle);
    EXPECT_EQ(1, numImpacted);

    ASSERT_EQ(2U, partitionedRange.getSubRanges().size());
    EXPECT_EQ(left, partitionedRange.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(right, partitionedRange.getSubRanges()[1].getBoundingRange());

    ASSERT_EQ(1U, partitionedRange.getSubRanges()[0].getSubRanges().size());
    EXPECT_EQ(left, partitionedRange.getSubRanges()[0].getSubRanges()[0].getBoundingRange());

    ASSERT_EQ(1U, partitionedRange.getSubRanges()[1].getSubRanges().size());
    EXPECT_EQ(right, partitionedRange.getSubRanges()[1].getSubRanges()[0].getBoundingRange());
}

TEST(Heap, whenDefaultInitializedThenRepresentsEmptyRange) {
    Cal::Utils::AddressRange emptyRange = {0U, 0U};
    Cal::Utils::Heap heap;
    EXPECT_EQ(emptyRange, heap.getRange());
    EXPECT_EQ(0U, heap.getSizeUsed());
    EXPECT_EQ(0U, heap.getSizeLeft());
}

TEST(Heap, whenCreatedFromRangeThenRepresentsThatRange) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Utils::Heap heap(heapRange);
    EXPECT_EQ(heapRange, heap.getRange());
    EXPECT_EQ(0U, heap.getSizeUsed());
    EXPECT_EQ(heapRange.size(), heap.getSizeLeft());
}

TEST(Heap, whenAllocatingThenUseFreeAddressesFromTopOfHeapIfPossible) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Utils::Heap heap(heapRange);

    size_t size0 = 64U;
    size_t size1 = 128U;
    size_t size2 = 64U;

    auto ptr0 = heap.alloc(size0);
    auto ptr1 = heap.alloc(size1);
    auto ptr2 = heap.alloc(size2);

    EXPECT_EQ(size0 + size1 + size2, heap.getSizeUsed());
    heap.free(ptr1);
    EXPECT_EQ(size0 + size2, heap.getSizeUsed());

    size_t size3 = 64U;
    size_t size4 = 128U;
    auto ptr3 = heap.alloc(size3);
    auto ptr4 = heap.alloc(size4);
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

TEST(Heap, whenAllocatingAndThereAreNoFreeAddressAtTheTopOfTheHeapThenReuseFreedMiddleRange) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Utils::Heap heap(heapRange);

    size_t size0 = 64U;
    size_t size1 = 128U;
    size_t size2 = heap.getSizeLeft() - size0 - size1;
    size_t size3 = 64U;

    auto ptr0 = heap.alloc(size0);
    auto ptr1 = heap.alloc(size1);
    auto ptr2 = heap.alloc(size2);
    EXPECT_NE(nullptr, ptr0);
    EXPECT_NE(nullptr, ptr1);
    EXPECT_NE(nullptr, ptr2);
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr0, size0).intersects(Cal::Utils::AddressRange(ptr1, size1)));
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr1, size1).intersects(Cal::Utils::AddressRange(ptr2, size2)));

    EXPECT_EQ(0U, heap.getSizeLeft());
    auto ptr3 = heap.alloc(size3);
    EXPECT_EQ(nullptr, ptr3);

    heap.free(ptr1);
    EXPECT_EQ(128U, heap.getSizeLeft());

    size_t size4 = 64U;
    size_t size5 = 64U;
    size_t size6 = 64U;
    auto ptr4 = heap.alloc(size4);
    auto ptr5 = heap.alloc(size5);
    EXPECT_NE(nullptr, ptr4);
    EXPECT_NE(nullptr, ptr5);
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr4, size4).intersects(Cal::Utils::AddressRange(ptr5, size5)));
    EXPECT_TRUE(Cal::Utils::AddressRange(ptr1, size1).contains(Cal::Utils::AddressRange(ptr4, size4)));
    EXPECT_TRUE(Cal::Utils::AddressRange(ptr1, size1).contains(Cal::Utils::AddressRange(ptr5, size5)));
    EXPECT_EQ(0U, heap.getSizeLeft());
    auto ptr6 = heap.alloc(size6);
    EXPECT_EQ(nullptr, ptr6);
}

TEST(Heap, whenAllocatingAndThereAreNoFreeAddressAtTheTopOfTheHeapThenReuseFreedBottomRange) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Utils::Heap heap(heapRange);

    size_t size0 = 64U;
    size_t size1 = heap.getSizeLeft() - size0;
    size_t size2 = 64U;

    auto ptr0 = heap.alloc(size0);
    auto ptr1 = heap.alloc(size1);

    EXPECT_NE(nullptr, ptr0);
    EXPECT_NE(nullptr, ptr1);
    EXPECT_FALSE(Cal::Utils::AddressRange(ptr0, size0).intersects(Cal::Utils::AddressRange(ptr1, size1)));

    auto ptr2 = heap.alloc(size2);
    EXPECT_EQ(nullptr, ptr2);

    heap.free(ptr0);
    EXPECT_EQ(64U, heap.getSizeLeft());

    size_t size3 = 64U;
    auto ptr3 = heap.alloc(size3);
    EXPECT_NE(nullptr, ptr3);
    EXPECT_EQ(Cal::Utils::AddressRange(ptr0, size0), Cal::Utils::AddressRange(ptr3, size3));
}

TEST(Heap, whenNewAllocationsAreAddredThenSizeRemainingDecreases) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Utils::Heap heap(heapRange);
    EXPECT_EQ(0U, heap.getSizeUsed());
    EXPECT_EQ(heapRange.size(), heap.getSizeLeft());

    auto result = heap.alloc(64U);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(64U, heap.getSizeUsed());
    EXPECT_EQ(heapRange.size() - 64U, heap.getSizeLeft());

    result = heap.alloc(heap.getSizeLeft());
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(heapRange.size(), heap.getSizeUsed());
    EXPECT_EQ(0U, heap.getSizeLeft());

    result = heap.alloc(1U);
    EXPECT_EQ(nullptr, result);
    EXPECT_EQ(heapRange.size(), heap.getSizeUsed());
    EXPECT_EQ(0U, heap.getSizeLeft());
}

TEST(Heap, whenAllocatingAddressessThenAlignmentsAreTakenIntoAccount) {
    Cal::Utils::AddressRange heapRange = {4096U, 8192U};
    Cal::Utils::Heap heap(heapRange);
    auto ptr0 = heap.alloc(1);
    auto ptr1 = heap.alloc(1);
    auto ptr2 = heap.alloc(1);
    auto ptr3 = heap.alloc(1, 4096U);

    EXPECT_TRUE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize>(ptr0));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize>(ptr1));
    EXPECT_FALSE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize * 2>(ptr1));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<Cal::Utils::defaultAlignmentSize>(ptr2));
    EXPECT_TRUE(Cal::Utils::isAlignedPow2<4096U>(ptr3));
}

TEST(GetCalEnv, whenEnvNotAvailableThenReturnNull) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    EXPECT_EQ(nullptr, Cal::Utils::getCalEnv("myenv"));
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.getenv.callCount);

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(GetCalEnv, whenEnvAvailableThenReturnItsStringValue) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    char expectedValue[] = "somevalue";
    tempSysCallsCtx.apiConfig.getenv.returnValue = expectedValue;

    EXPECT_EQ(expectedValue, Cal::Utils::getCalEnv("myenv"));
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.getenv.callCount);

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(GetCalEnvFlag, whenEnvNotAvailableThenReturnDefault) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    EXPECT_FALSE(Cal::Utils::getCalEnvFlag("myenv"));
    EXPECT_FALSE(Cal::Utils::getCalEnvFlag("myenv", false));
    EXPECT_TRUE(Cal::Utils::getCalEnvFlag("myenv", true));

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(GetCalEnv, whenEnvAvailableButInvalidThenReturnItsBooleanValue) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    char expectedValue[] = "X";
    tempSysCallsCtx.apiConfig.getenv.returnValue = expectedValue;
    EXPECT_FALSE(Cal::Utils::getCalEnvFlag("myenv"));
    EXPECT_FALSE(Cal::Utils::getCalEnvFlag("myenv", false));
    EXPECT_TRUE(Cal::Utils::getCalEnvFlag("myenv", true));

    EXPECT_FALSE(logs.empty());
}

TEST(GetCalEnvFlag, whenEnvAvailableThenReturnItsBooleanValue) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    char expectedValue[] = "X";

    char enabled[] = {'1', 'Y', 'y', 'T', 't'};
    char disabled[] = {'0', 'N', 'n', 'F', 'f'};

    tempSysCallsCtx.apiConfig.getenv.returnValue = expectedValue;

    for (auto e : enabled) {
        expectedValue[0] = e;
        EXPECT_TRUE(Cal::Utils::getCalEnvFlag("myenv"));
    }

    for (auto d : disabled) {
        expectedValue[0] = d;
        EXPECT_FALSE(Cal::Utils::getCalEnvFlag("myenv"));
    }

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(GetCalEnvI64, whenEnvNotAvailableThenReturnDefault) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    EXPECT_EQ(0, Cal::Utils::getCalEnvI64("myenv", 0));
    EXPECT_EQ(7, Cal::Utils::getCalEnvI64("myenv", 7));

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(GetCalEnvI64, whenEnvAvailableThenReturnItsIntegerValue) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    char expectedValue3[] = "3";
    tempSysCallsCtx.apiConfig.getenv.returnValue = expectedValue3;
    EXPECT_EQ(3, Cal::Utils::getCalEnvI64("myenv", 0));

    char expectedValueM7[] = "-7";
    tempSysCallsCtx.apiConfig.getenv.returnValue = expectedValueM7;
    EXPECT_EQ(-7, Cal::Utils::getCalEnvI64("myenv", 0));

    char expectedValue11[] = "11";
    tempSysCallsCtx.apiConfig.getenv.returnValue = expectedValue11;
    EXPECT_EQ(11, Cal::Utils::getCalEnvI64("myenv", 0));

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(Setenv, whenSetEnvThenEnvSet) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    const char *MockEnvName = "TEST_MOCK_ENV";
    const char *MockEnvValue = "0x123456789";

    EXPECT_FALSE(Cal::Sys::setenv(MockEnvName, "0x123456789", 1));
    auto envIt = tempSysCallsCtx.envVariables.find(MockEnvName);
    EXPECT_FALSE(std::strcmp(envIt->second.c_str(), MockEnvValue));

    EXPECT_FALSE(Cal::Sys::unsetenv(MockEnvName));
    envIt = tempSysCallsCtx.envVariables.find(MockEnvName);
    EXPECT_TRUE(envIt == tempSysCallsCtx.envVariables.end());
}

TEST(Setenv, whenCreateServiceConfigThenSetProperEnv) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    auto envIt = tempSysCallsCtx.envVariables.find(Cal::Service::ServiceConfig::neoCalEnabledEnvName);
    EXPECT_TRUE(envIt == tempSysCallsCtx.envVariables.end());
    auto config = std::make_unique<Cal::Service::ServiceConfig>();
    envIt = tempSysCallsCtx.envVariables.find(Cal::Service::ServiceConfig::neoCalEnabledEnvName);
    EXPECT_FALSE(std::strcmp(envIt->second.c_str(), Cal::Service::ServiceConfig::neoCalEnabledEnvValue));
    config.reset();
    envIt = tempSysCallsCtx.envVariables.find(Cal::Service::ServiceConfig::neoCalEnabledEnvName);
    EXPECT_TRUE(envIt == tempSysCallsCtx.envVariables.end());
}

TEST(CpuInfo, whenProcCpunFileNotAvailableThenReturnsNullopt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    std::optional<Cal::Utils::CpuInfo> cpuInfo = Cal::Utils::CpuInfo::read();
    EXPECT_FALSE(cpuInfo.has_value());
    EXPECT_FALSE(logs.empty());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.openFileForRead.callCount);
};

TEST(CpuInfo, whenProcCpuFileDoesNotContainExpectedDataThenReturnsNullopt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    tempSysCallsCtx.apiConfig.openFileForRead.returnValues["/proc/cpuinfo"] = "some\ndata\n";
    Cal::Mocks::LogCaptureContext logs;
    std::optional<Cal::Utils::CpuInfo> cpuInfo = Cal::Utils::CpuInfo::read();
    EXPECT_FALSE(cpuInfo.has_value());
    EXPECT_FALSE(logs.empty());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.openFileForRead.callCount);
};

TEST(CpuInfo, whenProcCpuFileisValidThenParsesSupportedEntries) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    tempSysCallsCtx.apiConfig.openFileForRead.returnValues["/proc/cpuinfo"] = R"===(
processor       : 0
clflush size    : 64
cache_alignment : 64
address sizes   : 39 bits physical, 48 bits virtual
)===";
    Cal::Mocks::LogCaptureContext logs;
    std::optional<Cal::Utils::CpuInfo> cpuInfo = Cal::Utils::CpuInfo::read();
    ASSERT_TRUE(cpuInfo.has_value());
    EXPECT_TRUE(logs.empty()) << logs.str();
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.openFileForRead.callCount);
    EXPECT_EQ(39U, cpuInfo->physical);
    EXPECT_EQ(48U, cpuInfo->virtual_);
};

TEST(CpuInfoIsAccessibleByApplication, givenAPointerThenReturnsTrueIfPointerFallsIntoLowerHalfOfSupportedVirtualAddresses) {
    Cal::Utils::CpuInfo cpuInfo;
    cpuInfo.virtual_ = 48;
    uintptr_t bit47 = static_cast<uintptr_t>(1) << 47;
    EXPECT_TRUE(cpuInfo.isAccessibleByApplication(reinterpret_cast<void *>(bit47 - 1)));
    EXPECT_FALSE(cpuInfo.isAccessibleByApplication(reinterpret_cast<void *>(bit47)));
    EXPECT_FALSE(cpuInfo.isAccessibleByApplication(reinterpret_cast<void *>(bit47 + 1)));
}

TEST(atomicMax, givenDifferentInputValuesThenAlwaysKeepsMax) {
    std::atomic<int> v = 5;
    Cal::Utils::atomicMax(v, 3);
    EXPECT_EQ(5, v.load());
    Cal::Utils::atomicMax(v, 5);
    EXPECT_EQ(5, v.load());
    Cal::Utils::atomicMax(v, 7);
    EXPECT_EQ(7, v.load());
}

TEST(atomicMin, givenDifferentInputValuesThenAlwaysKeepsMin) {
    std::atomic<int> v = 5;
    Cal::Utils::atomicMin(v, 7);
    EXPECT_EQ(5, v.load());
    Cal::Utils::atomicMin(v, 5);
    EXPECT_EQ(5, v.load());
    Cal::Utils::atomicMin(v, 3);
    EXPECT_EQ(3, v.load());
}

TEST(clz, givenIntegerThenReturnsNumberOfLeadingZeros) {
    unsigned int v = 0;
    EXPECT_EQ(24u + 1u, Cal::Utils::clz(v = 0b01111111));
    EXPECT_EQ(24u + 7u, Cal::Utils::clz(v = 0b00000001));
    EXPECT_EQ(0U, Cal::Utils::clz(v = 0xFFFFFFFF));
}

TEST(leadingBitNum, givenIntegerThenReturnsPositionOfOldestBit) {
    unsigned int v = 0;
    EXPECT_EQ(7u, Cal::Utils::leadingBitNum(v = 0b01111111));
    EXPECT_EQ(1u, Cal::Utils::leadingBitNum(v = 0b00000001));
    EXPECT_EQ(32u, Cal::Utils::leadingBitNum(v = 0xFFFFFFFF));
}

TEST(countNullterminated, givenNullThenReturnsZero) {
    const int *array = nullptr;
    EXPECT_EQ(0U, Cal::Utils::countNullterminated(array));
}

TEST(countNullterminated, givenEmptyArrayThenReturnsOneToAccountForNullterminate) {
    EXPECT_EQ(1U, Cal::Utils::countNullterminated(""));
}

TEST(countNullterminated, givenArrayThenReturnsNumberOfNonZeroElementsPlusOneToAccountForNullterminate) {
    EXPECT_EQ(4U, Cal::Utils::countNullterminated("abc"));
}

TEST(toLower, givenStringThenReturnsAVersionWithAllUpperCasesChangedToLowerCase) {
    EXPECT_STREQ("words words words", Cal::Utils::toLower("words Words wORDs").c_str());
}

TEST(countNullterminatedKey, givenNullThenReturnsZero) {
    const int *array = nullptr;
    EXPECT_EQ(0U, Cal::Utils::countNullterminatedKey(array));
}

TEST(countNullterminatedKey, givenEmptyArrayThenReturnsOneToAccountForNullterminate) {
    EXPECT_EQ(1U, Cal::Utils::countNullterminatedKey(""));
}

TEST(countNullterminatedKey, givenArrayThenCountsKeyValuePairsTreating0KeyAsTerminatorAndAddsOneForNullterminate) {
    EXPECT_EQ(3U, Cal::Utils::countNullterminatedKey("a "));
    EXPECT_EQ(3U, Cal::Utils::countNullterminatedKey("a\0"));
    EXPECT_EQ(1U, Cal::Utils::countNullterminatedKey("\0a"));
    EXPECT_EQ(1U, Cal::Utils::countNullterminatedKey("\0abc"));

    EXPECT_EQ(5U, Cal::Utils::countNullterminatedKey("abcd"));
    EXPECT_EQ(5U, Cal::Utils::countNullterminatedKey("a\0cd"));
    EXPECT_EQ(3U, Cal::Utils::countNullterminatedKey("ab\0d"));
}

TEST(concatenate, givenEmptyArrayThenReturnsEmptyString) {
    const char *substr[] = {"abc", "def"};
    {
        auto concatenated = Cal::Utils::concatenate(&substr[0], &substr[0], "");
        EXPECT_TRUE(concatenated.empty());
    }

    {
        auto concatenated = Cal::Utils::concatenate(&substr[0], &substr[0], " ");
        EXPECT_TRUE(concatenated.empty());
    }
}

TEST(concatenate, givenArrayWithOneEntryThenReturnsThatEntry) {
    const char *substr[] = {"abc", "def"};
    {
        auto concatenated = Cal::Utils::concatenate(&substr[0], &substr[1], "");
        EXPECT_STREQ(substr[0], concatenated.c_str());
    }

    {
        auto concatenated = Cal::Utils::concatenate(&substr[0], &substr[1], " ");
        EXPECT_STREQ(substr[0], concatenated.c_str());
    }
}

TEST(concatenate, givenArrayWithMultipleEntriesThenReturnsConcatenatedString) {
    const char *substr[] = {"abc", "def"};
    {
        auto concatenated = Cal::Utils::concatenate(&substr[0], &substr[2], "");
        EXPECT_STREQ("abcdef", concatenated.c_str());
    }

    {
        auto concatenated = Cal::Utils::concatenate(&substr[0], &substr[2], " ");
        EXPECT_STREQ("abc def", concatenated.c_str());
    }
}

TEST(intAsPath, givenUint64ThenConvertsBackAndForthProperly) {
    auto max32 = std::numeric_limits<uint32_t>::max();
    auto max64 = std::numeric_limits<uint64_t>::max();

    uint64_t valuesToTest[] = {0, 5, 9, 10, 15, 31, 32, 65, 113, max32, max64};
    for (auto v : valuesToTest) {
        EXPECT_EQ(v, Cal::Utils::decodeIntFromPath(Cal::Utils::encodeIntAsPath(v).c_str())) << v;
    }
}

} // namespace Ult
} // namespace Cal
