/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd/level_zero/logic/hostptr_copies_reader.h"
#include "icd/level_zero/logic/imported_host_pointers_manager.h"
#include "test/mocks/icd_l0_command_list_mock.h"
#include "test/mocks/log_mock.h"

#include <cstddef>

using Cal::Icd::LevelZero::Logic::ImportedHostPointersManager;

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

    ASSERT_EQ(3u, mockCommandList.memoryToWrite.size());

    const auto &[firstAddress, firstSize] = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&bytes[0], firstAddress);
    EXPECT_EQ(chunkSize, firstSize);

    const auto &[secondAddress, secondSize] = mockCommandList.memoryToWrite[1];
    EXPECT_EQ(&bytes[chunkSize], secondAddress);
    EXPECT_EQ(chunkSize, secondSize);

    const auto &[thirdAddress, thirdSize] = mockCommandList.memoryToWrite[2];
    EXPECT_EQ(&bytes[(2 * chunkSize) + 2], thirdAddress);
    EXPECT_EQ(2u, thirdSize);
}

TEST_F(IcdL0CommandListTest, GivenTwoOverlappingChunksWhenRegisteringThemToWriteThenTheyAreMerged) {
    mockCommandList.registerMemoryToWrite(&bytes[0], chunkSize);
    mockCommandList.registerMemoryToWrite(&bytes[chunkSize - 2], chunkSize);

    ASSERT_EQ(1u, mockCommandList.memoryToWrite.size());

    const auto &[firstAddress, firstSize] = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&bytes[0], firstAddress);
    EXPECT_EQ(6u, firstSize);
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
    ASSERT_EQ(2u, mockCommandList.memoryToWrite.size());

    // Unrelated chunk.
    const auto &[firstAddress, firstSize] = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&otherBytes[0], firstAddress);
    EXPECT_EQ(8u, firstSize);

    // Long chunk, which contains partitioned ones.
    const auto &[secondAddress, secondSize] = mockCommandList.memoryToWrite[1];
    EXPECT_EQ(&bytes[0], secondAddress);
    EXPECT_EQ(16u, secondSize);
}

class ImportedHostPointersManagerTest : public ::testing::Test {
  protected:
    void *rangeBegin{reinterpret_cast<void *>(0x00FF000000)};
    size_t rangeSize{8192};

    ImportedHostPointersManager pointersManager{};
};

TEST_F(ImportedHostPointersManagerTest, GivenNullptrWhenImportingPointerThenResultInvalidNullHandleIsReturned) {
    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE, pointersManager.importExternalPointer(nullptr, rangeSize));

    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenZeroSizeWhenImportingPointerThenResultInvalidNullHandleIsReturned) {
    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE, pointersManager.importExternalPointer(rangeBegin, 0));

    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenEmptyManagerWhenPointerIsImportedThenItsBaseAddressCanBeQueried) {
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.importExternalPointer(rangeBegin, rangeSize));

    auto uintRangeBegin = reinterpret_cast<uintptr_t>(rangeBegin);
    auto rangeBeginWithOffset = reinterpret_cast<void *>(uintRangeBegin + 32);

    void *baseAddress{};
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.getHostPointerBaseAddress(rangeBeginWithOffset, &baseAddress));

    EXPECT_EQ(rangeBegin, baseAddress);
}

TEST_F(ImportedHostPointersManagerTest, GivenTwoRangesWithHoleBetweenWhenInsertingOverlappingRangeThenErrorIsReturned) {
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.importExternalPointer(rangeBegin, rangeSize));

    auto uintRangeBegin = reinterpret_cast<uintptr_t>(rangeBegin);
    auto secondRangeBegin = reinterpret_cast<void *>(uintRangeBegin + 2 * rangeSize);
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.importExternalPointer(secondRangeBegin, rangeSize));

    Cal::Mocks::LogCaptureContext logs;

    auto thirdRangeBegin = reinterpret_cast<void *>(uintRangeBegin + rangeSize + 1);
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_ARGUMENT, pointersManager.importExternalPointer(thirdRangeBegin, 2 * rangeSize));
    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenNullptrWhenTryingToGetBaseAddressThenResultInvalidNullHandleIsReturned) {
    Cal::Mocks::LogCaptureContext logs;

    auto baseAddress = reinterpret_cast<void *>(0x00AA);
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE, pointersManager.getHostPointerBaseAddress(nullptr, &baseAddress));

    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenNullBaseStorageWhenTryingToGetBaseAddressThenResultInvalidNullHandleIsReturned) {
    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE, pointersManager.getHostPointerBaseAddress(rangeBegin, nullptr));

    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenManagerWithPointerWhenTryingToGetBaseAddressOfUnknownPointerThenNullptrIsSetAndResultIsReturned) {
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.importExternalPointer(rangeBegin, rangeSize));

    auto uintRangeBegin = reinterpret_cast<uintptr_t>(rangeBegin);
    auto rangeBeginWithOffset = reinterpret_cast<void *>(uintRangeBegin - 128);

    auto baseAddress = reinterpret_cast<void *>(0x00AA);
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.getHostPointerBaseAddress(rangeBeginWithOffset, &baseAddress));

    EXPECT_EQ(nullptr, baseAddress);
}

TEST_F(ImportedHostPointersManagerTest, GivenManagerWithPointerWhenTryingToGetBaseAddressOfThatPointerThenItsBaseAddressIsSetAndResultIsReturned) {
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.importExternalPointer(rangeBegin, rangeSize));

    auto uintRangeBegin = reinterpret_cast<uintptr_t>(rangeBegin);
    auto rangeBeginWithOffset = reinterpret_cast<void *>(uintRangeBegin + 256);

    auto baseAddress = reinterpret_cast<void *>(0x00AA);
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.getHostPointerBaseAddress(rangeBeginWithOffset, &baseAddress));

    EXPECT_EQ(rangeBegin, baseAddress);
}

TEST_F(ImportedHostPointersManagerTest, GivenManagerWhenTryingToReleaseNullptrThenResultInvalidNullHandleIsReturned) {
    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE, pointersManager.releaseImportedPointer(nullptr));

    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenManagerWhenTryingToReleaseNotImportedPointerThenResultInvalidArgumentIsReturned) {
    Cal::Mocks::LogCaptureContext logs;
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_ARGUMENT, pointersManager.releaseImportedPointer(rangeBegin));

    EXPECT_FALSE(logs.empty());
}

TEST_F(ImportedHostPointersManagerTest, GivenEmptyManagerWhenPointerIsImportedAndReleasedThenItsBaseAddressCanNotBeQueried) {
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.importExternalPointer(rangeBegin, rangeSize));

    auto uintRangeBegin = reinterpret_cast<uintptr_t>(rangeBegin);
    auto rangeBeginWithOffset = reinterpret_cast<void *>(uintRangeBegin + 32);
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.releaseImportedPointer(rangeBeginWithOffset));

    auto baseAddress = reinterpret_cast<void *>(0x00AA);
    ASSERT_EQ(ZE_RESULT_SUCCESS, pointersManager.getHostPointerBaseAddress(rangeBeginWithOffset, &baseAddress));

    EXPECT_EQ(nullptr, baseAddress);
}

} // namespace Cal::Icd::LevelZero

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
