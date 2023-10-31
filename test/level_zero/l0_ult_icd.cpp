/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/level_zero/icd_level_zero.h"
#include "client/icd/level_zero/logic/hostptr_copies_reader.h"
#include "client/icd/level_zero/logic/imported_host_pointers_manager.h"
#include "gtest/gtest.h"
#include "test/mocks/icd_l0_command_list_mock.h"
#include "test/mocks/log_mock.h"
#include "test/utils/cli_utils.h"
#include "test/utils/custom_event_listener.h"
#include "test/utils/signal_utils.h"

#include <cstddef>

using Cal::Client::Icd::LevelZero::Logic::ImportedHostPointersManager;

namespace Cal::Client::Icd::LevelZero {

class IcdL0CommandListTest : public ::testing::Test {
  protected:
    using ChunkEntry = Cal::Mocks::MockIcdL0CommandList::ChunkEntry;

  public:
    IcdL0CommandListTest() = default;

  protected:
    size_t chunkSize = 4;
    uint8_t *testAddress = reinterpret_cast<uint8_t *>(0xffff00);
    Cal::Mocks::MockIcdL0CommandList mockCommandList{};
};

TEST_F(IcdL0CommandListTest, GivenNonOverlappingRangesOfTheSameSizeWhenOverlappingIsCheckedThenTheyDoNotOverlap) {
    EXPECT_FALSE(IcdL0CommandList::rangesOverlap(&testAddress[0], &testAddress[chunkSize + 1], chunkSize));
}

TEST_F(IcdL0CommandListTest, GivenOverlappingRangesOfTheSameSizeWhenOverlappingIsCheckedThenTheyOverlap) {
    EXPECT_TRUE(IcdL0CommandList::rangesOverlap(&testAddress[0], &testAddress[chunkSize - 1], chunkSize));
}

TEST_F(IcdL0CommandListTest, GivenConsecutiveRangesWhenOverlappingIsCheckedThenTheyDoNotOverlap) {
    EXPECT_FALSE(IcdL0CommandList::rangesOverlap(&testAddress[0], &testAddress[chunkSize], chunkSize));
}

TEST_F(IcdL0CommandListTest, GivenLongRangeWhichIncludesShortRangeWhenOverlappingIsCheckedThenTheyOverlap) {
    constexpr size_t longBufferSize{16};
    constexpr size_t shortBufferSize{4};

    EXPECT_TRUE(IcdL0CommandList::rangesOverlap(&testAddress[0], longBufferSize, &testAddress[chunkSize], shortBufferSize));
}

TEST_F(IcdL0CommandListTest, GivenOverlappingChunksWhenMergingThemThenCorrectChunkIsReturned) {
    ChunkEntry first{testAddress, chunkSize};
    ChunkEntry second{testAddress + chunkSize - 1, chunkSize};

    const auto mergedChunk = mockCommandList.mergeChunks(first, second);
    EXPECT_EQ(testAddress, mergedChunk.base());

    EXPECT_EQ((2 * chunkSize) - 1, mergedChunk.size());
}

TEST_F(IcdL0CommandListTest, GivenLongChunkWhichIncludesShortChunkWhenMergingThemThenLongChunkIsReturned) {
    constexpr size_t longBufferSize = 12;
    constexpr size_t shortBufferSize = 4;

    ChunkEntry first{testAddress, longBufferSize};
    ChunkEntry second{testAddress + 4, shortBufferSize};

    const auto mergedChunk = mockCommandList.mergeChunks(first, second);
    EXPECT_EQ(testAddress, mergedChunk.base());
    EXPECT_EQ(longBufferSize, mergedChunk.size());
}

TEST_F(IcdL0CommandListTest, GivenNonOverlappingChunksWhenRegisteringThemToWriteThenTheyAreRegisteredAndNoneOfChunksIsMerged) {
    mockCommandList.registerMemoryToWrite(testAddress, chunkSize);
    mockCommandList.registerMemoryToWrite(&testAddress[chunkSize], chunkSize);
    mockCommandList.registerMemoryToWrite(&testAddress[(2 * chunkSize) + 2], 2);

    ASSERT_EQ(3u, mockCommandList.memoryToWrite.size());

    const auto first = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(testAddress, first.base());
    EXPECT_EQ(chunkSize, first.size());

    const auto second = mockCommandList.memoryToWrite[1];
    EXPECT_EQ(&testAddress[chunkSize], second.base());
    EXPECT_EQ(chunkSize, second.size());

    const auto third = mockCommandList.memoryToWrite[2];
    EXPECT_EQ(&testAddress[(2 * chunkSize) + 2], third.base());
    EXPECT_EQ(2u, third.size());
}

TEST_F(IcdL0CommandListTest, GivenTwoOverlappingChunksWhenRegisteringThemToWriteThenTheyAreMerged) {
    mockCommandList.registerMemoryToWrite(testAddress, chunkSize);
    mockCommandList.registerMemoryToWrite(testAddress + chunkSize - 2, chunkSize);

    ASSERT_EQ(1u, mockCommandList.memoryToWrite.size());

    const auto first = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&testAddress[0], first.base());
    EXPECT_EQ(6u, first.size());
}

TEST_F(IcdL0CommandListTest, GivenNonOverlappingChunksAndOneWhichOverlapsTheRestWhenRegisteringThemToWriteThenLongChunkReplacesSmallerOnes) {
    // Register unrelated chunk.
    uint8_t *otherTestAdress = testAddress + 4096U * 117;
    mockCommandList.registerMemoryToWrite(otherTestAdress, 8);

    // Register partitioned memory chunks.
    mockCommandList.registerMemoryToWrite(testAddress, chunkSize);
    mockCommandList.registerMemoryToWrite(testAddress + chunkSize, chunkSize);
    mockCommandList.registerMemoryToWrite(testAddress + (2 * chunkSize) + 2, 2);

    // Register additional chunk, which includes partitioned chunks.
    mockCommandList.registerMemoryToWrite(testAddress, 16);

    // Validate registered blocks.
    ASSERT_EQ(2u, mockCommandList.memoryToWrite.size());

    // Unrelated chunk.
    const auto first = mockCommandList.memoryToWrite[0];
    EXPECT_EQ(&otherTestAdress[0], first.base());
    EXPECT_EQ(8u, first.size());

    // Long chunk, which contains partitioned ones.
    const auto second = mockCommandList.memoryToWrite[1];
    EXPECT_EQ(testAddress, second.base());
    EXPECT_EQ(16u, second.size());
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

TEST_F(ImportedHostPointersManagerTest, GivenManagerWhenTryingToReleaseNotImportedPointerThenResultSuccessIsReturned) {
    EXPECT_EQ(ZE_RESULT_SUCCESS, pointersManager.releaseImportedPointer(rangeBegin));
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

} // namespace Cal::Client::Icd::LevelZero

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    auto options = parseArguments(argc, argv);

    if (int result = enableSignals(options.enableAlarm, options.enableSegv, options.enableAbrt); result != 0) {
        return result;
    }

    if (options.useCustomListener) {
        auto &listeners = ::testing::UnitTest::GetInstance()->listeners();
        auto defaultListener = listeners.default_result_printer();
        auto customEventListener = new CCustomEventListener(defaultListener);
        listeners.Release(defaultListener);
        listeners.Append(customEventListener);
    }

    Cal::Mocks::DisallowLogs disallowLogs;
    return RUN_ALL_TESTS();
}
