/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "shared/shmem.h"
#include "test/mocks/memory_block_mock.h"
#include "test/mocks/shmem_manager_mock.h"

#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>

class MemoryBlockTest : public ::testing::Test {
  protected:
    size_t pageOffset{128};
    uintptr_t pageBeginning{Cal::Utils::pageSize4KB * 1024};
    const void *srcPtr{reinterpret_cast<const void *>(pageBeginning + pageOffset)};
    const size_t pageSize{Cal::Utils::pageSize4KB};
    const size_t chunkSize{(pageSize / 2) + pageSize};

    Cal::Mocks::MockShmemManager shmemManagerMock{};
    Cal::Mocks::MockMemoryBlock memoryBlock{shmemManagerMock, srcPtr, chunkSize};
};

class MemoryBlocksManagerTest : public ::testing::Test {
  protected:
    uintptr_t firstPageAddress{Cal::Utils::pageSize4KB * 512};
    const size_t pageSize{Cal::Utils::pageSize4KB};

    Cal::Mocks::MockShmemManager shmemManagerMock{};
    Cal::Mocks::MockMemoryBlocksManager memoryBlocksManager{};
};

class MemoryBlocksManagerTestWithThreeNonOverlappingBlocks : public MemoryBlocksManagerTest {
  protected:
    using MemoryBlocksManagerTest::firstPageAddress;
    using MemoryBlocksManagerTest::memoryBlocksManager;
    using MemoryBlocksManagerTest::pageSize;
    using MemoryBlocksManagerTest::shmemManagerMock;

  public:
    void SetUp() override {
        memoryBlocksManager.registerMemoryBlock(shmemManagerMock, firstSrcAddress, firstChunkSize);
        memoryBlocksManager.registerMemoryBlock(shmemManagerMock, secondSrcAddress, secondChunkSize);
        memoryBlocksManager.registerMemoryBlock(shmemManagerMock, thirdSrcAddress, thirdChunkSize);
    }

  protected:
    const void *firstSrcAddress{reinterpret_cast<const void *>(firstPageAddress + 64)};
    const size_t firstChunkSize{pageSize};

    const uintptr_t firstPageOfSecondChunk{firstPageAddress + (4 * pageSize)};
    const void *secondSrcAddress{reinterpret_cast<const void *>(firstPageOfSecondChunk)};
    const size_t secondChunkSize{3 * pageSize};

    const uintptr_t firstPageOfThirdChunk{firstPageAddress + (10 * pageSize)};
    const void *thirdSrcAddress{reinterpret_cast<const void *>(firstPageOfThirdChunk)};
    const size_t thirdChunkSize{2 * pageSize};
};

namespace Cal::Ult {

TEST_F(MemoryBlockTest, GivenInputChunkWhenConstructingMemoryBlockThenChunkIsAddedAndDescriptionIsValid) {
    ASSERT_EQ(1u, memoryBlock.chunks.size());

    const auto &firstChunk = memoryBlock.chunks[0];
    EXPECT_EQ(pageBeginning, firstChunk.firstPageAddress);

    constexpr auto expectedShmemFd = 7;
    EXPECT_EQ(expectedShmemFd, firstChunk.shmem.fd);

    constexpr auto expectedShmemId = 0;
    EXPECT_EQ(expectedShmemId, firstChunk.shmem.id);

    EXPECT_TRUE(firstChunk.shmem.owned);
    EXPECT_NE(nullptr, firstChunk.shmem.ptr);

    const auto expectedRequestedSize = chunkSize + pageOffset;
    EXPECT_EQ(expectedRequestedSize, firstChunk.shmem.size);

    const auto expectedUnderlyingSize = 2 * Cal::Utils::pageSize4KB;
    EXPECT_EQ(expectedUnderlyingSize, firstChunk.shmem.underlyingSize);
}

TEST_F(MemoryBlockTest, GivenLongerBlockWhichIncludesShorterChunkWhenTryingToExtendLongerByShorterThenNothingIsDone) {
    const void *shorterChunkPtr{srcPtr};
    const size_t shorterChunkSize{chunkSize / 2};

    ASSERT_EQ(1u, memoryBlock.chunks.size());
    const auto oldMappedAddress = memoryBlock.chunks[0].shmem.ptr;
    const auto oldPageBeginning = memoryBlock.chunks[0].firstPageAddress;

    memoryBlock.extendBlockIfRequired(shorterChunkPtr, shorterChunkSize);

    ASSERT_EQ(1u, memoryBlock.chunks.size());
    EXPECT_EQ(oldMappedAddress, memoryBlock.chunks[0].shmem.ptr);
    EXPECT_EQ(oldPageBeginning, memoryBlock.chunks[0].firstPageAddress);
}

TEST_F(MemoryBlockTest, GivenShorterBlockAndChunkWhichExtendsItAtTheEndWhenTryingToExtendBlockThenChunkIsAddedAtEndAndMemoryIsRemapped) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning)};
    const size_t longerChunkSize{chunkSize * 2};

    ASSERT_EQ(1u, memoryBlock.chunks.size());
    const auto oldMappedAddress = memoryBlock.chunks[0].shmem.ptr;
    const auto oldPageBeginning = memoryBlock.chunks[0].firstPageAddress;

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(2u, memoryBlock.chunks.size());

    const auto expectedTotalContiguousSize{pageSize * 3};
    EXPECT_EQ(expectedTotalContiguousSize, memoryBlock.getTotalContiguousSize());

    const auto &firstChunk = memoryBlock.chunks[0];
    EXPECT_NE(oldMappedAddress, firstChunk.shmem.ptr);
    EXPECT_EQ(oldPageBeginning, firstChunk.firstPageAddress);

    const auto &secondChunk = memoryBlock.chunks[1];
    const auto expectedContiguousFirstPage = firstChunk.firstPageAddress + firstChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousFirstPage, secondChunk.firstPageAddress);

    const auto expectedContiguousMappedAddress = reinterpret_cast<uintptr_t>(firstChunk.shmem.ptr) + firstChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousMappedAddress, reinterpret_cast<uintptr_t>(secondChunk.shmem.ptr));

    const auto expectedSize = pageSize;
    EXPECT_EQ(expectedSize, secondChunk.shmem.underlyingSize);
}

TEST_F(MemoryBlockTest, GivenShorterBlockAndChunkWhichExtendsItAtTheBeginningWhenTryingToExtendBlockThenChunkIsAddedAtBeginningAndMemoryIsRemapped) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t longerChunkSize{chunkSize + 1024};

    ASSERT_EQ(1u, memoryBlock.chunks.size());
    const auto oldMappedAddress = memoryBlock.chunks[0].shmem.ptr;
    const auto oldPageBeginning = memoryBlock.chunks[0].firstPageAddress;

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(2u, memoryBlock.chunks.size());

    const auto expectedTotalContiguousSize{pageSize * 4};
    EXPECT_EQ(expectedTotalContiguousSize, memoryBlock.getTotalContiguousSize());

    const auto &firstChunk = memoryBlock.chunks[0];
    EXPECT_NE(nullptr, firstChunk.shmem.ptr);

    const auto expectedFirstPageAddress = pageBeginning - (2 * pageSize);
    EXPECT_EQ(expectedFirstPageAddress, firstChunk.firstPageAddress);

    const auto expectedFirstSize = 2 * pageSize;
    EXPECT_EQ(expectedFirstSize, firstChunk.shmem.underlyingSize);

    const auto &secondChunk = memoryBlock.chunks[1];
    EXPECT_NE(oldMappedAddress, secondChunk.shmem.ptr);
    EXPECT_EQ(oldPageBeginning, secondChunk.firstPageAddress);

    const auto expectedContiguousFirstPage = firstChunk.firstPageAddress + firstChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousFirstPage, secondChunk.firstPageAddress);

    const auto expectedContiguousMappedAddress = reinterpret_cast<uintptr_t>(firstChunk.shmem.ptr) + firstChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousMappedAddress, reinterpret_cast<uintptr_t>(secondChunk.shmem.ptr));

    const auto expectedOldSize = (2 * pageSize);
    EXPECT_EQ(expectedOldSize, secondChunk.shmem.underlyingSize);
}

TEST_F(MemoryBlockTest, GivenShorterBlockAndChunkWhichExtendsItAtTheBeginningAndEndWhenTryingToExtendBlockThenChunksAreAddedAtBeginningAndEndAndMemoryIsRemapped) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t longerChunkSize{4 * chunkSize};

    ASSERT_EQ(1u, memoryBlock.chunks.size());
    const auto oldMappedAddress = memoryBlock.chunks[0].shmem.ptr;
    const auto oldPageBeginning = memoryBlock.chunks[0].firstPageAddress;

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(3u, memoryBlock.chunks.size());

    const auto expectedTotalContiguousSize{pageSize * 7};
    EXPECT_EQ(expectedTotalContiguousSize, memoryBlock.getTotalContiguousSize());

    const auto &firstChunk = memoryBlock.chunks[0];
    EXPECT_NE(nullptr, firstChunk.shmem.ptr);

    const auto expectedFirstPageAddress = pageBeginning - (2 * pageSize);
    EXPECT_EQ(expectedFirstPageAddress, firstChunk.firstPageAddress);

    const auto expectedFirstSize = 2 * pageSize;
    EXPECT_EQ(expectedFirstSize, firstChunk.shmem.underlyingSize);

    const auto &secondChunk = memoryBlock.chunks[1];
    EXPECT_NE(oldMappedAddress, secondChunk.shmem.ptr);
    EXPECT_EQ(oldPageBeginning, secondChunk.firstPageAddress);

    const auto expectedContiguousFirstPage = firstChunk.firstPageAddress + firstChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousFirstPage, secondChunk.firstPageAddress);

    const auto expectedContiguousMappedAddress = reinterpret_cast<uintptr_t>(firstChunk.shmem.ptr) + firstChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousMappedAddress, reinterpret_cast<uintptr_t>(secondChunk.shmem.ptr));

    const auto expectedOldSize = 2 * pageSize;
    EXPECT_EQ(expectedOldSize, secondChunk.shmem.underlyingSize);

    const auto &thirdChunk = memoryBlock.chunks[2];
    EXPECT_NE(nullptr, thirdChunk.shmem.ptr);

    const auto expectedContiguousSecondPage = secondChunk.firstPageAddress + secondChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousSecondPage, thirdChunk.firstPageAddress);

    const auto expectedContiguousMappedAddressOfThird = reinterpret_cast<uintptr_t>(secondChunk.shmem.ptr) + secondChunk.shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousMappedAddressOfThird, reinterpret_cast<uintptr_t>(thirdChunk.shmem.ptr));

    const auto expectedThirdSize = 3 * pageSize;
    EXPECT_EQ(expectedThirdSize, thirdChunk.shmem.underlyingSize);
}

TEST_F(MemoryBlockTest, GivenShorterBlockAndChunkWhichExtendsItAtTheBeginningAndEndWhenTryingToExtendBlockThenBlockIsExtendedAndOldMappingsArePreserved) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t longerChunkSize{4 * chunkSize};

    ASSERT_EQ(1u, memoryBlock.chunks.size());
    const auto oldMappedAddress = memoryBlock.chunks[0].shmem.ptr;

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(3u, memoryBlock.chunks.size());

    const auto &oldChunk = memoryBlock.chunks[1];
    EXPECT_NE(oldMappedAddress, oldChunk.shmem.ptr);

    ASSERT_EQ(1u, memoryBlock.oldMappings.size());
    EXPECT_EQ(oldMappedAddress, memoryBlock.oldMappings[0].first);
    EXPECT_EQ(oldChunk.shmem.underlyingSize, memoryBlock.oldMappings[0].second);
}

TEST_F(MemoryBlockTest, GivenChunkAndOverlappingMemoryWhenCheckingForOverlappingThenTrueIsReturned) {
    const void *overlappingChunkPtr{srcPtr};
    const size_t overlappingChunkSize{chunkSize / 2};

    EXPECT_TRUE(memoryBlock.overlapsPages(overlappingChunkPtr, overlappingChunkSize));
}

TEST_F(MemoryBlockTest, GivenChunkAndNonOverlappingMemoryWhenCheckingForOverlappingThenFalseIsReturned) {
    const void *nonOverlappingChunkPtr{reinterpret_cast<const void *>(pageBeginning - (2 * chunkSize))};
    const size_t nonOverlappingChunkSize{chunkSize / 2};

    EXPECT_FALSE(memoryBlock.overlapsPages(nonOverlappingChunkPtr, nonOverlappingChunkSize));
}

TEST_F(MemoryBlockTest, GivenChunkWhenTranslatingOverlappingMemoryThenTranslatedAddressIsReturned) {
    const void *overlappingChunkPtr{reinterpret_cast<const void *>(pageBeginning + pageOffset + 8)};
    const auto mappedPtr = reinterpret_cast<uintptr_t>(memoryBlock.translate(overlappingChunkPtr));

    const auto expectedMappedPtr = reinterpret_cast<uintptr_t>(memoryBlock.chunks[0].shmem.ptr) + pageOffset + 8;
    EXPECT_EQ(expectedMappedPtr, mappedPtr);
}

TEST_F(MemoryBlockTest, GivenChunkWhenTranslatingNonOverlappingMemoryThenErrorIsLoggedAndNullptrIsReturned) {
    const void *nonOverlappingChunkPtr{reinterpret_cast<const void *>(pageBeginning - (2 * chunkSize))};

    ::testing::internal::CaptureStdout();
    const auto mappedPtr = memoryBlock.translate(nonOverlappingChunkPtr);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(nullptr, mappedPtr);
    EXPECT_FALSE(output.empty());
}

TEST_F(MemoryBlockTest, GivenTwoBlocksWithoutHoleBetweenThemWhenMergingThemThenOneConsecutiveBlockIsCreated) {
    const void *secondBeginning{reinterpret_cast<const void *>(pageBeginning + (2 * pageSize))};
    Cal::Mocks::MockMemoryBlock secondBlock{shmemManagerMock, secondBeginning, chunkSize};

    // Remap second block to allow verification of oldMappings' content.
    secondBlock.remapChunksAsContiguousMemory();

    const auto oldFirstPageAddress = memoryBlock.chunks[0].firstPageAddress;
    const auto oldFirstPageAddressOfSecond = secondBlock.chunks[0].firstPageAddress;
    const auto oldMappingsOfSecondBlock = secondBlock.oldMappings;

    memoryBlock.merge(std::move(secondBlock));

    EXPECT_TRUE(secondBlock.chunks.empty());
    EXPECT_TRUE(secondBlock.oldMappings.empty());

    ASSERT_EQ(2u, memoryBlock.chunks.size());
    ASSERT_EQ(1u, memoryBlock.oldMappings.size());

    EXPECT_EQ(oldFirstPageAddress, memoryBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(oldFirstPageAddressOfSecond, memoryBlock.chunks[1].firstPageAddress);

    EXPECT_EQ(oldMappingsOfSecondBlock, memoryBlock.oldMappings);
}

TEST_F(MemoryBlockTest, GivenTwoBlocksWithHoleBetweenThemWhenMergingThemThenOneConsecutiveBlockIsCreatedWhichCoversAlsoTheHole) {
    const void *secondBeginning{reinterpret_cast<const void *>(pageBeginning + (3 * pageSize))};
    Cal::Mocks::MockMemoryBlock secondBlock{shmemManagerMock, secondBeginning, chunkSize};

    // Remap second block to allow verification of oldMappings' content.
    secondBlock.remapChunksAsContiguousMemory();

    const auto oldFirstPageAddress = memoryBlock.chunks[0].firstPageAddress;
    const auto oldFirstPageAddressOfSecond = secondBlock.chunks[0].firstPageAddress;
    const auto oldMappingsOfSecondBlock = secondBlock.oldMappings;

    memoryBlock.merge(std::move(secondBlock));

    EXPECT_TRUE(secondBlock.chunks.empty());
    EXPECT_TRUE(secondBlock.oldMappings.empty());

    ASSERT_EQ(3u, memoryBlock.chunks.size());
    ASSERT_EQ(1u, memoryBlock.oldMappings.size());

    EXPECT_EQ(oldFirstPageAddress, memoryBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(oldFirstPageAddressOfSecond, memoryBlock.chunks[2].firstPageAddress);

    EXPECT_EQ(oldMappingsOfSecondBlock, memoryBlock.oldMappings);

    const auto expectedContiguousAddress = oldFirstPageAddress + memoryBlock.chunks[0].shmem.underlyingSize;
    EXPECT_EQ(expectedContiguousAddress, memoryBlock.chunks[1].firstPageAddress);
    EXPECT_EQ(pageSize, memoryBlock.chunks[1].shmem.underlyingSize);
}

TEST_F(MemoryBlockTest, GivenMemoryBlockWhichConsistsOfThreeChunksWhenGettingCountOfOverlappingChunksThenCorrectResultsAreReturned) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t longerChunkSize{4 * chunkSize};

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(3u, memoryBlock.chunks.size());

    const void *singleChunkOverlappingPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t singleChunkOverlappingSize{pageSize};

    const auto firstOverlappingCount = memoryBlock.getCountOfOverlappingChunks(singleChunkOverlappingPtr, singleChunkOverlappingSize);
    EXPECT_EQ(1u, firstOverlappingCount);

    const void *twoChunksOverlappingPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t twoChunksOverlappingSize{3 * pageSize};

    const auto secondOverlappingCount = memoryBlock.getCountOfOverlappingChunks(twoChunksOverlappingPtr, twoChunksOverlappingSize);
    EXPECT_EQ(2u, secondOverlappingCount);

    const void *zeroChunksOverlappingPtr{reinterpret_cast<const void *>(pageBeginning - (4 * chunkSize))};
    const size_t zeroChunksOverlappingSize{pageSize};

    const auto thirdOverlappingCount = memoryBlock.getCountOfOverlappingChunks(zeroChunksOverlappingPtr, zeroChunksOverlappingSize);
    EXPECT_EQ(0u, thirdOverlappingCount);
}

TEST_F(MemoryBlockTest, GivenMemoryBlockWhichConsistsOfThreeChunksWhenGettingTwoOverlappingChunksAndNotEnoughSpaceIsProvidedThenFalseIsReturned) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t longerChunkSize{4 * chunkSize};

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(3u, memoryBlock.chunks.size());

    const void *twoChunksOverlappingPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t twoChunksOverlappingSize{3 * pageSize};

    const uint32_t transferDescsCount{1};
    Cal::Rpc::ShmemTransferDesc transferDescs[transferDescsCount] = {};

    uint32_t appendedTransfersCount{0};
    EXPECT_FALSE(memoryBlock.appendOverlappingChunks(twoChunksOverlappingPtr,
                                                     twoChunksOverlappingSize,
                                                     appendedTransfersCount,
                                                     transferDescs,
                                                     transferDescsCount));
}

TEST_F(MemoryBlockTest, GivenMemoryBlockAndNotEnoughOutputSpacePriorToExecutionWhenGettingOverlappingChunksDataThenFalseIsReturned) {
    const void *singleChunkOverlappingPtr{reinterpret_cast<const void *>(pageBeginning)};
    const size_t singleChunkOverlappingSize{pageSize};

    const uint32_t transferDescsCount{1};
    Cal::Rpc::ShmemTransferDesc transferDescs[transferDescsCount] = {};

    uint32_t appendedTransfersCount{1};
    EXPECT_FALSE(memoryBlock.appendOverlappingChunks(singleChunkOverlappingPtr,
                                                     singleChunkOverlappingSize,
                                                     appendedTransfersCount,
                                                     transferDescs,
                                                     transferDescsCount));
}

TEST_F(MemoryBlockTest, GivenMemoryBlockWhichConsistsOfThreeChunksWhenGettingTwoOverlappingChunksAndEnoughSpaceIsProvidedThenTrueIsReturnedAndAppendedChunksDataIsCorrect) {
    const void *longerChunkPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t longerChunkSize{4 * chunkSize};

    memoryBlock.extendBlockIfRequired(longerChunkPtr, longerChunkSize);
    ASSERT_EQ(3u, memoryBlock.chunks.size());

    const void *twoChunksOverlappingPtr{reinterpret_cast<const void *>(pageBeginning - chunkSize)};
    const size_t twoChunksOverlappingSize{2 * chunkSize};

    const uint32_t transferDescsCount{2};
    Cal::Rpc::ShmemTransferDesc transferDescs[transferDescsCount] = {};

    uint32_t appendedTransfersCount{0};
    EXPECT_TRUE(memoryBlock.appendOverlappingChunks(twoChunksOverlappingPtr,
                                                    twoChunksOverlappingSize,
                                                    appendedTransfersCount,
                                                    transferDescs,
                                                    transferDescsCount));

    EXPECT_EQ(memoryBlock.chunks[0].shmem.id, transferDescs[0].shmemId);
    EXPECT_EQ(memoryBlock.chunks[0].shmem.underlyingSize, transferDescs[0].underlyingSize);
    EXPECT_EQ(chunkSize, transferDescs[0].bytesCountToCopy);
    EXPECT_EQ(pageSize / 2, transferDescs[0].offsetFromMapping);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(twoChunksOverlappingPtr), transferDescs[0].transferStart);

    EXPECT_EQ(memoryBlock.chunks[1].shmem.id, transferDescs[1].shmemId);
    EXPECT_EQ(memoryBlock.chunks[1].shmem.underlyingSize, transferDescs[1].underlyingSize);
    EXPECT_EQ(chunkSize, transferDescs[1].bytesCountToCopy);
    EXPECT_EQ(0u, transferDescs[1].offsetFromMapping);
    EXPECT_EQ(memoryBlock.chunks[1].firstPageAddress, transferDescs[1].transferStart);
}

TEST_F(MemoryBlocksManagerTest, DefaultConstructedMemoryBlocksManagerDoesNotContainAnyBlocks) {
    EXPECT_TRUE(memoryBlocksManager.memoryBlocks.empty());
}

TEST_F(MemoryBlocksManagerTest, GivenEmptyManagerWhenRegisteringNonOverlapingChunksThenTheyAreRegisteredAsSeparateMemoryBlocks) {
    const void *firstSrcAddress{reinterpret_cast<const void *>(firstPageAddress + 64)};
    const size_t firstChunkSize{pageSize};

    const uintptr_t firstPageOfSecondChunk{firstPageAddress + (4 * pageSize)};
    const void *secondSrcAddress{reinterpret_cast<const void *>(firstPageOfSecondChunk)};
    const size_t secondChunkSize{3 * pageSize};

    auto &firstRegisteredMemoryBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, firstSrcAddress, firstChunkSize);
    auto &secondRegisteredMemoryBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, secondSrcAddress, secondChunkSize);

    ASSERT_EQ(2u, memoryBlocksManager.memoryBlocks.size());

    auto &realFirstMemoryBlock = memoryBlocksManager.memoryBlocks.at(firstPageAddress);
    ASSERT_EQ(&realFirstMemoryBlock, &firstRegisteredMemoryBlock);

    EXPECT_EQ(firstPageAddress, realFirstMemoryBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(2 * pageSize, realFirstMemoryBlock.chunks[0].shmem.underlyingSize);

    auto &realSecondMemoryBlock = memoryBlocksManager.memoryBlocks.at(firstPageOfSecondChunk);
    ASSERT_EQ(&realSecondMemoryBlock, &secondRegisteredMemoryBlock);

    EXPECT_EQ(firstPageOfSecondChunk, realSecondMemoryBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(3 * pageSize, realSecondMemoryBlock.chunks[0].shmem.underlyingSize);
}

TEST_F(MemoryBlocksManagerTest, GivenEmptyManagerWhenRegisteringChunkWhichIsIncludedByAnotherThenOnlySingleMemoryBlockIsRegistered) {
    const void *firstSrcAddress{reinterpret_cast<const void *>(firstPageAddress + 64)};
    const size_t firstChunkSize{pageSize};

    const uintptr_t firstPageOfSecondChunk{firstPageAddress + pageSize};
    const void *secondSrcAddress{reinterpret_cast<const void *>(firstPageOfSecondChunk)};
    const size_t secondChunkSize{pageSize};

    auto &firstRegisteredMemoryBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, firstSrcAddress, firstChunkSize);
    auto &secondRegisteredMemoryBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, secondSrcAddress, secondChunkSize);

    ASSERT_EQ(1u, memoryBlocksManager.memoryBlocks.size());
    ASSERT_EQ(&firstRegisteredMemoryBlock, &secondRegisteredMemoryBlock);

    auto &realFirstMemoryBlock = memoryBlocksManager.memoryBlocks.at(firstPageAddress);
    ASSERT_EQ(&realFirstMemoryBlock, &firstRegisteredMemoryBlock);

    EXPECT_EQ(firstPageAddress, realFirstMemoryBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(2 * pageSize, realFirstMemoryBlock.chunks[0].shmem.underlyingSize);

    // Remapping should not be done.
    EXPECT_TRUE(realFirstMemoryBlock.oldMappings.empty());
}

TEST_F(MemoryBlocksManagerTest, GivenEmptyManagerWhenRegisteringSeveralChunksAndOneWhichIncludesThemAndExtendsThenTheyAreMergedAndRemmapedOnce) {
    const void *firstSrcAddress{reinterpret_cast<const void *>(firstPageAddress + 64)};
    const size_t firstChunkSize{pageSize};

    const uintptr_t firstPageOfSecondChunk{firstPageAddress + (4 * pageSize)};
    const void *secondSrcAddress{reinterpret_cast<const void *>(firstPageOfSecondChunk)};
    const size_t secondChunkSize{3 * pageSize};

    const uintptr_t firstPageOfThirdChunk{firstPageAddress + (10 * pageSize)};
    const void *thirdSrcAddress{reinterpret_cast<const void *>(firstPageOfThirdChunk)};
    const size_t thirdChunkSize{2 * pageSize};

    // First three chunks should be registered as three memory blocks. They do not overlap.
    memoryBlocksManager.registerMemoryBlock(shmemManagerMock, firstSrcAddress, firstChunkSize);
    memoryBlocksManager.registerMemoryBlock(shmemManagerMock, secondSrcAddress, secondChunkSize);
    auto &shortBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, thirdSrcAddress, thirdChunkSize);

    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    const uintptr_t firstPageOfFourthChunk{firstPageAddress - pageSize};
    const void *fourthSrcAddress{reinterpret_cast<const void *>(firstPageOfFourthChunk)};
    const size_t fourthChunkSize{10 * pageSize};

    // Fourth chunk includes the first and second chunks.
    // Furthermore, it extends them at the beginning and at the end.
    // Between the first and the second chunk there is a gap. It needs to be filled.
    auto &longBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, fourthSrcAddress, fourthChunkSize);
    ASSERT_EQ(2u, memoryBlocksManager.memoryBlocks.size());

    auto &realLongBlock = memoryBlocksManager.memoryBlocks.at(firstPageOfFourthChunk);
    ASSERT_EQ(&realLongBlock, &longBlock);

    auto &realShortBlock = memoryBlocksManager.memoryBlocks.at(firstPageOfThirdChunk);
    ASSERT_EQ(&realShortBlock, &shortBlock);

    // Verify short block.
    ASSERT_EQ(1u, shortBlock.chunks.size());
    EXPECT_EQ(firstPageOfThirdChunk, shortBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(thirdChunkSize, shortBlock.chunks[0].shmem.underlyingSize);

    // Verify long block.
    ASSERT_EQ(5u, longBlock.chunks.size());

    // Prepended chunk.
    EXPECT_EQ(firstPageOfFourthChunk, longBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(pageSize, longBlock.chunks[0].shmem.underlyingSize);
    EXPECT_NE(nullptr, longBlock.chunks[0].shmem.ptr);

    // A chunk, which was originally the first one.
    EXPECT_EQ(firstPageAddress, longBlock.chunks[1].firstPageAddress);
    EXPECT_EQ(2 * pageSize, longBlock.chunks[1].shmem.underlyingSize);

    auto expectedBeginningOfNextMapping = reinterpret_cast<uintptr_t>(longBlock.chunks[0].shmem.ptr) + pageSize;
    EXPECT_EQ(expectedBeginningOfNextMapping, reinterpret_cast<uintptr_t>(longBlock.chunks[1].shmem.ptr));

    // Chunk, which fills gap between the original first and the original second.
    const auto expectedGapChunkFirstPageAddress = firstPageAddress + (2 * pageSize);
    EXPECT_EQ(expectedGapChunkFirstPageAddress, longBlock.chunks[2].firstPageAddress);
    EXPECT_EQ(2 * pageSize, longBlock.chunks[2].shmem.underlyingSize);

    expectedBeginningOfNextMapping = reinterpret_cast<uintptr_t>(longBlock.chunks[1].shmem.ptr) + (2 * pageSize);
    EXPECT_EQ(expectedBeginningOfNextMapping, reinterpret_cast<uintptr_t>(longBlock.chunks[2].shmem.ptr));

    // A chunk, which was originally the second one.
    EXPECT_EQ(firstPageOfSecondChunk, longBlock.chunks[3].firstPageAddress);
    EXPECT_EQ(secondChunkSize, longBlock.chunks[3].shmem.underlyingSize);

    expectedBeginningOfNextMapping = reinterpret_cast<uintptr_t>(longBlock.chunks[2].shmem.ptr) + (2 * pageSize);
    EXPECT_EQ(expectedBeginningOfNextMapping, reinterpret_cast<uintptr_t>(longBlock.chunks[3].shmem.ptr));

    // Appended chunk.
    const auto expectedAppendedChunkFirstPageAddress = firstPageOfSecondChunk + secondChunkSize;
    EXPECT_EQ(expectedAppendedChunkFirstPageAddress, longBlock.chunks[4].firstPageAddress);
    EXPECT_EQ(2 * pageSize, longBlock.chunks[4].shmem.underlyingSize);

    expectedBeginningOfNextMapping = reinterpret_cast<uintptr_t>(longBlock.chunks[3].shmem.ptr) + secondChunkSize;
    EXPECT_EQ(expectedBeginningOfNextMapping, reinterpret_cast<uintptr_t>(longBlock.chunks[4].shmem.ptr));

    // Long block should contain old mappings for the original first and second blocks.
    EXPECT_EQ(2u, longBlock.oldMappings.size());
}

TEST_F(MemoryBlocksManagerTest, GivenEmptyManagerWhenRegisteringSeveralChunksAndOneWhichIncludesThemThenTheyAreMergedAndRemmapedOnce) {
    const void *firstSrcAddress{reinterpret_cast<const void *>(firstPageAddress + 64)};
    const size_t firstChunkSize{pageSize};

    const uintptr_t firstPageOfSecondChunk{firstPageAddress + (4 * pageSize)};
    const void *secondSrcAddress{reinterpret_cast<const void *>(firstPageOfSecondChunk)};
    const size_t secondChunkSize{3 * pageSize};

    const uintptr_t firstPageOfThirdChunk{firstPageAddress + (10 * pageSize)};
    const void *thirdSrcAddress{reinterpret_cast<const void *>(firstPageOfThirdChunk)};
    const size_t thirdChunkSize{2 * pageSize};

    // First three chunks should be registered as three memory blocks. They do not overlap.
    memoryBlocksManager.registerMemoryBlock(shmemManagerMock, firstSrcAddress, firstChunkSize);
    memoryBlocksManager.registerMemoryBlock(shmemManagerMock, secondSrcAddress, secondChunkSize);
    auto &shortBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, thirdSrcAddress, thirdChunkSize);

    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    const uintptr_t firstPageOfFourthChunk{firstPageAddress};
    const void *fourthSrcAddress{reinterpret_cast<const void *>(firstPageOfFourthChunk)};
    const size_t fourthChunkSize{7 * pageSize};

    // Fourth chunk includes the first and second chunks.
    // Between the first and the second chunk there is a gap. It needs to be filled.
    auto &longBlock = memoryBlocksManager.registerMemoryBlock(shmemManagerMock, fourthSrcAddress, fourthChunkSize);
    ASSERT_EQ(2u, memoryBlocksManager.memoryBlocks.size());

    auto &realLongBlock = memoryBlocksManager.memoryBlocks.at(firstPageOfFourthChunk);
    ASSERT_EQ(&realLongBlock, &longBlock);

    auto &realShortBlock = memoryBlocksManager.memoryBlocks.at(firstPageOfThirdChunk);
    ASSERT_EQ(&realShortBlock, &shortBlock);

    // Verify short block.
    ASSERT_EQ(1u, shortBlock.chunks.size());
    EXPECT_EQ(firstPageOfThirdChunk, shortBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(thirdChunkSize, shortBlock.chunks[0].shmem.underlyingSize);

    // Verify long block.
    ASSERT_EQ(3u, longBlock.chunks.size());

    // Prepended chunk.
    EXPECT_EQ(firstPageOfFourthChunk, longBlock.chunks[0].firstPageAddress);
    EXPECT_EQ(2 * pageSize, longBlock.chunks[0].shmem.underlyingSize);
    EXPECT_NE(nullptr, longBlock.chunks[0].shmem.ptr);

    // Chunk, which fills gap between the original first and the original second.
    const auto expectedGapChunkFirstPageAddress = firstPageAddress + (2 * pageSize);
    EXPECT_EQ(expectedGapChunkFirstPageAddress, longBlock.chunks[1].firstPageAddress);
    EXPECT_EQ(2 * pageSize, longBlock.chunks[1].shmem.underlyingSize);

    auto expectedBeginningOfNextMapping = reinterpret_cast<uintptr_t>(longBlock.chunks[0].shmem.ptr) + (2 * pageSize);
    EXPECT_EQ(expectedBeginningOfNextMapping, reinterpret_cast<uintptr_t>(longBlock.chunks[1].shmem.ptr));

    // A chunk, which was originally the second one.
    EXPECT_EQ(firstPageOfSecondChunk, longBlock.chunks[2].firstPageAddress);
    EXPECT_EQ(secondChunkSize, longBlock.chunks[2].shmem.underlyingSize);

    expectedBeginningOfNextMapping = reinterpret_cast<uintptr_t>(longBlock.chunks[1].shmem.ptr) + (2 * pageSize);
    EXPECT_EQ(expectedBeginningOfNextMapping, reinterpret_cast<uintptr_t>(longBlock.chunks[2].shmem.ptr));

    // Long block should contain old mappings for the original first and second blocks.
    EXPECT_EQ(2u, longBlock.oldMappings.size());
}

TEST_F(MemoryBlocksManagerTestWithThreeNonOverlappingBlocks, GivenThreeNonOverlappingMemoryBlocksInManagerWhenGettingBlockForChunkWhichIsIncludedThenReturnThatBlock) {
    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    const void *includedChunk{reinterpret_cast<const void *>(firstPageAddress)};
    const size_t includedChunkSize{pageSize + 128};

    ::testing::internal::CaptureStdout();
    const auto foundMemoryBlock = memoryBlocksManager.getMemoryBlockWhichIncludesChunk(includedChunk, includedChunkSize);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_NE(nullptr, foundMemoryBlock);
    EXPECT_TRUE(output.empty()) << output;
}

TEST_F(MemoryBlocksManagerTestWithThreeNonOverlappingBlocks, GivenThreeNonOverlappingMemoryBlocksInManagerWhenGettingBlockForChunkWhichRequiresExtensionThenReturnNullptr) {
    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    const void *chunkWhichRequiresExtension{reinterpret_cast<const void *>(firstPageAddress - 128)};
    const size_t chunkWhichRequiresExtensionSize{2 * pageSize};

    ::testing::internal::CaptureStdout();
    const auto foundMemoryBlock = memoryBlocksManager.getMemoryBlockWhichIncludesChunk(chunkWhichRequiresExtension, chunkWhichRequiresExtensionSize);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(nullptr, foundMemoryBlock);

    const auto containsExpectedError = output.find("Memory chunk is not fully included in the memory block. Extension would be needed!") != std::string::npos;
    EXPECT_TRUE(containsExpectedError) << output;
}

TEST_F(MemoryBlocksManagerTestWithThreeNonOverlappingBlocks, GivenThreeNonOverlappingMemoryBlocksInManagerWhenGettingBlockForChunkWhichOverlapsMultipleBlocksThenReturnNullptr) {
    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    const void *multipleBlocksOverlappingChunk{reinterpret_cast<const void *>(firstPageAddress)};
    const size_t multipleBlocksOverlappingChunkSize{7 * pageSize};

    ::testing::internal::CaptureStdout();
    const auto foundMemoryBlock = memoryBlocksManager.getMemoryBlockWhichIncludesChunk(multipleBlocksOverlappingChunk, multipleBlocksOverlappingChunkSize);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(nullptr, foundMemoryBlock);

    const auto containsExpectedError = output.find("Number of registered overlapping blocks should be 1! Actual value: 2") != std::string::npos;
    EXPECT_TRUE(containsExpectedError) << output;
}

TEST_F(MemoryBlocksManagerTest, GivenMemoryBlockInManagerWhenGettingBlockForChunkWhichDoesNotOverlapThenReturnNullptr) {
    const void *firstSrcAddress{reinterpret_cast<const void *>(firstPageAddress + 64)};
    const size_t firstChunkSize{pageSize};

    memoryBlocksManager.registerMemoryBlock(shmemManagerMock, firstSrcAddress, firstChunkSize);
    ASSERT_EQ(1u, memoryBlocksManager.memoryBlocks.size());

    const void *nonOverlappingChunk{reinterpret_cast<const void *>(firstPageAddress + (4 * pageSize))};
    const size_t nonOverlappingChunkSize{pageSize};

    ::testing::internal::CaptureStdout();
    const auto foundMemoryBlock = memoryBlocksManager.getMemoryBlockWhichIncludesChunk(nonOverlappingChunk, nonOverlappingChunkSize);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(nullptr, foundMemoryBlock);

    const auto containsExpectedError = output.find("Queried file descriptors of non-registered chunk!") != std::string::npos;
    EXPECT_TRUE(containsExpectedError) << output;
}

TEST_F(MemoryBlocksManagerTestWithThreeNonOverlappingBlocks, GivenThreeNonOverlappingMemoryBlocksInManagerWhenGettingCountOfRequiredTransfersForChunksThenCorrectCountIsReturned) {
    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    uint32_t transferDescsCount{0};

    const uint32_t chunksCount{2};
    Cal::Rpc::MemChunk chunks[chunksCount] = {
        {firstSrcAddress, firstChunkSize},
        {thirdSrcAddress, thirdChunkSize}};

    ::testing::internal::CaptureStdout();
    const auto wasCountCalculationSuccessful = memoryBlocksManager.getCountOfRequiredTransferDescs(transferDescsCount, chunksCount, chunks);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.empty()) << output;
    ASSERT_TRUE(wasCountCalculationSuccessful);
    EXPECT_EQ(2u, transferDescsCount);
}

TEST_F(MemoryBlocksManagerTestWithThreeNonOverlappingBlocks, GivenThreeNonOverlappingMemoryBlocksInManagerWhenGettingRequiredTransfersForChunksThenCorrectTransfersAreReturned) {
    ASSERT_EQ(3u, memoryBlocksManager.memoryBlocks.size());

    auto getBlock = [this](int id) -> Cal::Mocks::MockMemoryBlock & {
        auto it = std::next(memoryBlocksManager.memoryBlocks.begin(), id);
        return (*it).second;
    };

    auto &firstBlock = getBlock(0);
    auto &secondBlock = getBlock(1);
    auto &thirdBlock = getBlock(2);

    uint32_t transferDescsCount{4};
    Cal::Rpc::ShmemTransferDesc transferDescs[4] = {};

    const uint32_t chunksCount{2};
    Cal::Rpc::MemChunk chunks[chunksCount] = {
        {firstSrcAddress, firstChunkSize},
        {thirdSrcAddress, thirdChunkSize}};

    ::testing::internal::CaptureStdout();
    const auto enoughSpace = memoryBlocksManager.getRequiredTransferDescs(transferDescsCount, transferDescs, chunksCount, chunks);
    const auto output = ::testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.empty()) << output;
    ASSERT_TRUE(enoughSpace);

    ASSERT_EQ(2u, transferDescsCount);

    // Validate transfers
    EXPECT_EQ(firstBlock.chunks[0].shmem.id, transferDescs[0].shmemId);
    EXPECT_EQ(firstBlock.chunks[0].shmem.underlyingSize, transferDescs[0].underlyingSize);
    EXPECT_EQ(firstChunkSize, transferDescs[0].bytesCountToCopy);
    EXPECT_EQ(64, transferDescs[0].offsetFromMapping);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(firstSrcAddress), transferDescs[0].transferStart);

    EXPECT_EQ(thirdBlock.chunks[0].shmem.id, transferDescs[1].shmemId);
    EXPECT_EQ(thirdBlock.chunks[0].shmem.underlyingSize, transferDescs[1].underlyingSize);
    EXPECT_EQ(thirdChunkSize, transferDescs[1].bytesCountToCopy);
    EXPECT_EQ(0u, transferDescs[1].offsetFromMapping);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(thirdSrcAddress), transferDescs[1].transferStart);
}

} // namespace Cal::Ult
