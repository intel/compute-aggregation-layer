/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "icd/icd_level_zero.h"
#include "test/mocks/icd_l0_command_list_mock.h"

#include <cstddef>

namespace Cal::Icd::LevelZero {

class IcdL0CommandListTest : public ::testing::Test {
  protected:
    using ChunkEntry = Cal::Mocks::MockIcdL0CommandList::ChunkEntry;

  public:
    IcdL0CommandListTest() = default;

  protected:
    size_t chunkSize{4};
    std::byte bytes[16]{};
    Cal::Mocks::MockIcdL0CommandList mockCommandList{};
};

TEST_F(IcdL0CommandListTest, GivenNonOverlappingRangesOfTheSameSizeWhenOverlappingIsCheckedThenTheyDoNotOverlap) {
    EXPECT_FALSE(IcdL0CommandList::rangesOverlap(&bytes[0], &bytes[chunkSize + 1], chunkSize));
}

TEST_F(IcdL0CommandListTest, GivenOverlappingRangesOfTheSameSizeWhenOverlappingIsCheckedThenTheyOverlap) {
    EXPECT_TRUE(IcdL0CommandList::rangesOverlap(&bytes[0], &bytes[chunkSize - 1], chunkSize));
}

TEST_F(IcdL0CommandListTest, GivenConsecutiveRangesWhenOverlappingIsCheckedThenTheyDoNotOverlap) {
    EXPECT_FALSE(IcdL0CommandList::rangesOverlap(&bytes[0], &bytes[chunkSize], chunkSize));
}

TEST_F(IcdL0CommandListTest, GivenLongRangeWhichIncludesShortRangeWhenOverlappingIsCheckedThenTheyOverlap) {
    constexpr size_t longBufferSize{16};
    constexpr size_t shortBufferSize{4};

    EXPECT_TRUE(IcdL0CommandList::rangesOverlap(&bytes[0], longBufferSize, &bytes[chunkSize], shortBufferSize));
}

TEST_F(IcdL0CommandListTest, GivenOverlappingChunksWhenMergingThemThenCorrectChunkIsReturned) {
    ChunkEntry first{&bytes[0], chunkSize};
    ChunkEntry second{&bytes[chunkSize - 1], chunkSize};

    const auto [mergedChunkAddress, mergedChunkSize] = mockCommandList.mergeChunks(first, second);
    EXPECT_EQ(&bytes[0], mergedChunkAddress);

    const size_t expectedSize{(2 * chunkSize) - 1};
    EXPECT_EQ(expectedSize, mergedChunkSize);
}

TEST_F(IcdL0CommandListTest, GivenLongChunkWhichIncludesShortChunkWhenMergingThemThenLongChunkIsReturned) {
    constexpr size_t longBufferSize{12};
    constexpr size_t shortBufferSize{4};

    ChunkEntry first{&bytes[0], longBufferSize};
    ChunkEntry second{&bytes[4], shortBufferSize};

    const auto [mergedChunkAddress, mergedChunkSize] = mockCommandList.mergeChunks(first, second);
    EXPECT_EQ(&bytes[0], mergedChunkAddress);
    EXPECT_EQ(longBufferSize, mergedChunkSize);
}

TEST_F(IcdL0CommandListTest, GivenNonOverlappingChunksWhenRegisteringThemToWriteThenTheyAreRegisteredAndNoneOfChunksIsMerged) {
    mockCommandList.registerMemoryToWrite(&bytes[0], chunkSize);
    mockCommandList.registerMemoryToWrite(&bytes[chunkSize], chunkSize);
    mockCommandList.registerMemoryToWrite(&bytes[(2 * chunkSize) + 2], 2);

    ASSERT_EQ(3, mockCommandList.memoryToWrite.size());

    const auto &[firstAddress, firstSize] = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&bytes[0], firstAddress);
    EXPECT_EQ(chunkSize, firstSize);

    const auto &[secondAddress, secondSize] = mockCommandList.memoryToWrite[1];
    EXPECT_EQ(&bytes[chunkSize], secondAddress);
    EXPECT_EQ(chunkSize, secondSize);

    const auto &[thirdAddress, thirdSize] = mockCommandList.memoryToWrite[2];
    EXPECT_EQ(&bytes[(2 * chunkSize) + 2], thirdAddress);
    EXPECT_EQ(2, thirdSize);
}

TEST_F(IcdL0CommandListTest, GivenTwoOverlappingChunksWhenRegisteringThemToWriteThenTheyAreMerged) {
    mockCommandList.registerMemoryToWrite(&bytes[0], chunkSize);
    mockCommandList.registerMemoryToWrite(&bytes[chunkSize - 2], chunkSize);

    ASSERT_EQ(1, mockCommandList.memoryToWrite.size());

    const auto &[firstAddress, firstSize] = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&bytes[0], firstAddress);
    EXPECT_EQ(6, firstSize);
}

TEST_F(IcdL0CommandListTest, GivenNonOverlappingChunksAndOneWhichOverlapsTheRestWhenRegisteringThemToWriteThenLongChunkReplacesSmallerOnes) {
    // Register unrelated chunk.
    std::byte otherBytes[12] = {};
    mockCommandList.registerMemoryToWrite(&otherBytes[0], 8);

    // Register partitioned memory chunks.
    mockCommandList.registerMemoryToWrite(&bytes[0], chunkSize);
    mockCommandList.registerMemoryToWrite(&bytes[chunkSize], chunkSize);
    mockCommandList.registerMemoryToWrite(&bytes[(2 * chunkSize) + 2], 2);

    // Register additional chunk, which includes partitioned chunks.
    mockCommandList.registerMemoryToWrite(&bytes[0], 16);

    // Validate registered blocks.
    ASSERT_EQ(2, mockCommandList.memoryToWrite.size());

    // Unrelated chunk.
    const auto &[firstAddress, firstSize] = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&otherBytes[0], firstAddress);
    EXPECT_EQ(8, firstSize);

    // Long chunk, which contains partitioned ones.
    const auto &[secondAddress, secondSize] = mockCommandList.memoryToWrite[1];
    EXPECT_EQ(&bytes[0], secondAddress);
    EXPECT_EQ(16, secondSize);
}

} // namespace Cal::Icd::LevelZero

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}