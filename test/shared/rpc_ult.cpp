/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "shared/rpc.h"
#include "test/mocks/connection_mock.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/shmem_manager_mock.h"
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

class CommandsChannelWhiteBox : public Cal::Rpc::CommandsChannel {
  public:
    using CommandsChannel::layout;
    using CommandsChannel::ownsSemaphores;
    using CommandsChannel::ring;
    using CommandsChannel::semClient;
    using CommandsChannel::semServer;
    using CommandsChannel::shmem;
    using CommandsChannel::shmemSize;

    using CommandsChannel::getAsLocalAddress;
    using CommandsChannel::getAsShmemOffset;
    using CommandsChannel::partition;
};

TEST(CommandsChannel, whenWaitOnServiceSemparhoreIsCalledThenWaitsOnSemaphoreAndReturnsTrueOnlyIfSuccesfull) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semServer = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semServer, 1, 1));
    commandsChannel.semServer = &semServer;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    EXPECT_TRUE(commandsChannel.waitOnServiceSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semServer));
}

TEST(CommandsChannel, whenWaitOnServiceSemparhoreIsCalledAndSystemCallFailsThenReturnsFalseAndEmitsWarning) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semServer = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semServer, 1, 1));
    commandsChannel.semServer = &semServer;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    tempSysCallsCtx.apiConfig.sem_wait.returnValue = -1;
    EXPECT_FALSE(commandsChannel.waitOnServiceSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semServer));
    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannel, whenWaitOnClientSemparhoreIsCalledThenWaitsOnSemaphoreAndReturnsTrueOnlyIfSuccesfull) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semClient = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semClient, 1, 1));
    commandsChannel.semClient = &semClient;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    EXPECT_TRUE(commandsChannel.waitOnClientSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semClient));
}

TEST(CommandsChannel, whenWaitOnClientSemparhoreIsCalledAndSystemCallFailsThenReturnsFalseAndEmitsWarning) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semClient = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semClient, 1, 1));
    commandsChannel.semClient = &semClient;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    tempSysCallsCtx.apiConfig.sem_wait.returnValue = -1;
    EXPECT_FALSE(commandsChannel.waitOnClientSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_wait.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semClient));
    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannel, whenSignalServiceSemparhoreIsCalledThenSignalsSemaphoreAndReturnsTrueOnlyIfSuccesfull) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semServer = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semServer, 1, 0));
    commandsChannel.semServer = &semServer;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    EXPECT_TRUE(commandsChannel.signalServiceSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semServer));
}

TEST(CommandsChannel, whenSignalServiceSemparhoreIsCalledAndSystemCallFailsThenReturnsFalseAndEmitsWarning) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semServer = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semServer, 1, 0));
    commandsChannel.semServer = &semServer;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    tempSysCallsCtx.apiConfig.sem_post.returnValue = -1;
    EXPECT_FALSE(commandsChannel.signalServiceSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semServer));
    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannel, whenSignalClientSemparhoreIsCalledThenSignalsSemaphoreAndReturnsTrueOnlyIfSuccesfull) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semClient = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semClient, 1, 0));
    commandsChannel.semClient = &semClient;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    EXPECT_TRUE(commandsChannel.signalClientSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semClient));
}

TEST(CommandsChannel, whenSignalClientSemparhoreIsCalledAndSystemCallFailsThenReturnsFalseAndEmitsWarning) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    CommandsChannelWhiteBox commandsChannel;
    sem_t semClient = {};
    ASSERT_EQ(0, Cal::Sys::sem_init(&semClient, 1, 0));
    commandsChannel.semClient = &semClient;
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    tempSysCallsCtx.apiConfig.sem_post.returnValue = -1;
    EXPECT_FALSE(commandsChannel.signalClientSemaphore());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.sem_post.callCount);
    ASSERT_EQ(0, Cal::Sys::sem_destroy(&semClient));
    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannel, givenChannelOffsetWhenGetAsLocalAddressIsCalledThenReturnsFragmentOfMappedShmemThatCorrespondsToThatOffset) {
    CommandsChannelWhiteBox commandsChannel;

    int tab[16] = {};
    commandsChannel.shmem = tab;
    EXPECT_EQ(tab, commandsChannel.getAsLocalAddress(0));
    EXPECT_EQ(tab, commandsChannel.getAsLocalAddress<int>(0));
    EXPECT_EQ(tab + 2, commandsChannel.getAsLocalAddress(8));
    EXPECT_EQ(tab + 2, commandsChannel.getAsLocalAddress<int>(8));
}

TEST(CommandsChannel, givenPointerToPortionOfMappedShmemWhenGetAsShmemOffsetIsCalledThenOffsetFromBeginningOfShmem) {
    CommandsChannelWhiteBox commandsChannel;

    int tab[16] = {};
    commandsChannel.shmem = tab;
    EXPECT_EQ(0, commandsChannel.getAsShmemOffset(tab));
    EXPECT_EQ(8, commandsChannel.getAsShmemOffset(tab + 2));
}

TEST(CommandsChannelPartitionUsingDefaultLayout, givenUnalignedShmemPointerThenFailsAndEmitsWarning) {
    CommandsChannelWhiteBox commandsChannel;
    Cal::Mocks::LogCaptureContext logs;

    std::vector<char> shmem;
    shmem.resize(Cal::Utils::pageSize4KB * 16);
    EXPECT_FALSE(commandsChannel.partition(shmem.data() + 1, Cal::Utils::pageSize4KB * 15, false));

    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartitionUsingDefaultLayout, givenUnalignedShmemSizeThenFailsAndEmitsWarning) {
    CommandsChannelWhiteBox commandsChannel;
    Cal::Mocks::LogCaptureContext logs;

    std::vector<char> shmem;
    shmem.resize(Cal::Utils::pageSize4KB * 16);
    EXPECT_FALSE(commandsChannel.partition(Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data()), Cal::Utils::pageSize4KB * 15 - 1, false));

    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartitionUsingDefaultLayout, givenTooSmallShmemSizeThenFailsAndEmitsWarning) {
    CommandsChannelWhiteBox commandsChannel;
    Cal::Mocks::LogCaptureContext logs;

    std::vector<char> shmem;
    shmem.resize(Cal::Utils::pageSize4KB * 16);
    EXPECT_FALSE(commandsChannel.partition(Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data()),
                                           Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize - Cal::Utils::pageSize4KB, false));

    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartitioUsingDefaultLayoutn, givenCorrectShmemSizeThenPartitionsItUsingDefaultLayout) {
    CommandsChannelWhiteBox commandsChannel;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false));

    EXPECT_EQ(LayoutT::ringHead, commandsChannel.layout.ringHead);
    EXPECT_EQ(LayoutT::semClient, commandsChannel.layout.semClient);

    EXPECT_EQ(LayoutT::ringTail, commandsChannel.layout.ringTail);
    EXPECT_EQ(LayoutT::semServer, commandsChannel.layout.semServer);

    EXPECT_EQ(LayoutT::ringStart, commandsChannel.layout.ringStart);
    EXPECT_EQ((LayoutT::ringEnd - LayoutT::ringStart) / sizeof(Cal::Rpc::RingEntry), commandsChannel.layout.ringCapacity);

    EXPECT_EQ(LayoutT::completionStampsStart, commandsChannel.layout.completionStampsStart);
    EXPECT_EQ((LayoutT::completionStampsEnd - LayoutT::completionStampsStart) / sizeof(Cal::Rpc::CompletionStampT), commandsChannel.layout.completionStampsCapacity);

    EXPECT_EQ(LayoutT::heapStart, commandsChannel.layout.heapStart);
    EXPECT_EQ(alignedShmemSize, commandsChannel.layout.heapEnd);

    EXPECT_EQ(commandsChannel.getAsLocalAddress<sem_t>(LayoutT::semClient), commandsChannel.semClient);
    EXPECT_EQ(commandsChannel.getAsLocalAddress<sem_t>(LayoutT::semServer), commandsChannel.semServer);

    EXPECT_EQ(LayoutT::ringStart, commandsChannel.getAsShmemOffset(commandsChannel.ring.peekHead()));
    EXPECT_EQ((LayoutT::ringEnd - LayoutT::ringStart) / sizeof(Cal::Rpc::RingEntry), commandsChannel.ring.getCapacity());
}

TEST(CommandsChannelPartitionUsingDefaultLayout, whenInitializationOfControlBlockIsNotRequestedThenDoesNotResetRingAndDoesNotInitializeSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, LayoutT::ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, LayoutT::ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false));
    EXPECT_FALSE(commandsChannel.ownsSemaphores);
    EXPECT_EQ(0, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(3, *ringHead);
    EXPECT_EQ(5, *ringTail);
}

TEST(CommandsChannelPartitionUsingDefaultLayout, whenInitializationOfControlBlockIsRequestedThenResetsRingAndInitializesSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, LayoutT::ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, LayoutT::ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, true));
    EXPECT_TRUE(commandsChannel.ownsSemaphores);
    EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(0, *ringHead);
    EXPECT_EQ(0, *ringTail);
}

TEST(CommandsChannelPartitionUsingDefaultLayout, whenInitializationOfControlBlockIsRequestedButInitializationOfSemaphoresFailsThenCleansUpReturnsFalseAndEmitsErrorMessage) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        tempSysCallsCtx.apiConfig.sem_init.returnValue = -1;
        EXPECT_FALSE(commandsChannel.partition(alignedShmem, alignedShmemSize, true));
        EXPECT_EQ(1, tempSysCallsCtx.apiConfig.sem_init.callCount);
        EXPECT_FALSE(commandsChannel.ownsSemaphores);
        EXPECT_FALSE(logs.empty());
        EXPECT_EQ(0, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
    }

    logs.clear();
    {
        CommandsChannelWhiteBox commandsChannel;
        tempSysCallsCtx.apiConfig.sem_init.returnValue.reset();
        tempSysCallsCtx.apiConfig.sem_init.callCount = 0;
        tempSysCallsCtx.apiConfig.sem_init.impl = [&](sem_t *sem, int pshared, unsigned int value) -> int {
            if (2 == tempSysCallsCtx.apiConfig.sem_init.callCount) {
                return -1;
            }
            return tempSysCallsCtx.sem_initBaseImpl(sem, pshared, value);
        };
        EXPECT_FALSE(commandsChannel.ownsSemaphores);
        EXPECT_FALSE(commandsChannel.partition(alignedShmem, alignedShmemSize, true));
        EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_init.callCount);
        EXPECT_EQ(1, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
        EXPECT_FALSE(logs.empty());
    }
}

TEST(CommandsChannelPartition, whenInitializedSempahoresThenDestroysThemDuringOwnDestructor) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, true));
        EXPECT_TRUE(commandsChannel.ownsSemaphores);
        EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_init.callCount);
    }

    EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
}

TEST(CommandsChannelPartition, whenInitializedSempahoresButFailedToDestroyThemThenEmitsWarning) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, true));
        EXPECT_TRUE(commandsChannel.ownsSemaphores);
        EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_init.callCount);
        tempSysCallsCtx.apiConfig.sem_destroy.returnValue = -1;
    }

    EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartition, whenDidNotInitializeSempahoresThenDoesNotDestroyThemDuringOwnDestructor) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    using LayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(LayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = LayoutT::minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false));
        EXPECT_FALSE(commandsChannel.ownsSemaphores);
        EXPECT_EQ(0, tempSysCallsCtx.apiConfig.sem_init.callCount);
    }

    EXPECT_EQ(0, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
}

TEST(CommandsChannelPartitionUsingGivenLayout, givenInvalidLayoutThenFailsAndEmitsWarning) {
    std::vector<char> shmem;
    using ValidLayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(ValidLayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = ValidLayoutT::minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox validCommandsChannel;
    ASSERT_TRUE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, false));

    auto validLayout = validCommandsChannel.layout;
    ASSERT_TRUE(validLayout.isValid());
    ASSERT_TRUE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, validLayout, false));

    auto invalidLayout = validLayout;

    Cal::Messages::OffsetWithinChannelT *offsetsToBreak[] = {&invalidLayout.semClient, &invalidLayout.semServer, &invalidLayout.ringHead, &invalidLayout.ringTail,
                                                             &invalidLayout.ringStart, &invalidLayout.completionStampsStart, &invalidLayout.heapStart, &invalidLayout.heapEnd};

    size_t *capacitiesToBreak[] = {&invalidLayout.ringCapacity, &invalidLayout.completionStampsCapacity};

    std::pair<Cal::Messages::OffsetWithinChannelT *, Cal::Messages::OffsetWithinChannelT *> overlapsToTest[] = {
        {&invalidLayout.semClient, &invalidLayout.semServer},
        {&invalidLayout.ringHead, &invalidLayout.ringTail},
    };

    for (auto offsetToBreak : offsetsToBreak) {
        Cal::Mocks::LogCaptureContext logs;
        invalidLayout = validLayout;
        *offsetToBreak = Cal::Messages::invalidOffsetWithinChannel;
        CommandsChannelWhiteBox invalidCommandsChannel;
        EXPECT_FALSE(invalidLayout.isValid());
        EXPECT_FALSE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, invalidLayout, false));
        EXPECT_FALSE(logs.empty());
    }

    for (auto capacityToBreak : capacitiesToBreak) {
        Cal::Mocks::LogCaptureContext logs;
        invalidLayout = validLayout;
        *capacityToBreak = 0;
        CommandsChannelWhiteBox invalidCommandsChannel;
        EXPECT_FALSE(invalidLayout.isValid());
        EXPECT_FALSE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, invalidLayout, false));
        EXPECT_FALSE(logs.empty());
    }

    for (auto alignmentToBreak : offsetsToBreak) {
        Cal::Mocks::LogCaptureContext logs;
        invalidLayout = validLayout;
        *alignmentToBreak += 1;
        CommandsChannelWhiteBox invalidCommandsChannel;
        EXPECT_FALSE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, invalidLayout, false));
        EXPECT_FALSE(logs.empty());
    }

    for (auto &[lhs, rhs] : overlapsToTest) {
        {
            Cal::Mocks::LogCaptureContext logs;
            invalidLayout = validLayout;
            *lhs = *rhs;
            CommandsChannelWhiteBox invalidCommandsChannel;
            EXPECT_FALSE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, invalidLayout, false));
            EXPECT_FALSE(logs.empty());
        }
        {
            Cal::Mocks::LogCaptureContext logs;
            invalidLayout = validLayout;
            *rhs = *lhs;
            CommandsChannelWhiteBox invalidCommandsChannel;
            EXPECT_FALSE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, invalidLayout, false));
            EXPECT_FALSE(logs.empty());
        }
    }
}

TEST(CommandsChannelPartitionUsingGivenLayout, givenValidLayoutThenUsesIt) {
    std::vector<char> shmem;
    using ValidLayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(ValidLayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = ValidLayoutT::minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox commandsChannel;
    ASSERT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false));

    CommandsChannelWhiteBox commandsChannel2;
    EXPECT_TRUE(commandsChannel2.partition(alignedShmem, alignedShmemSize, commandsChannel.layout, false));

    EXPECT_EQ(commandsChannel.layout.ringHead, commandsChannel2.layout.ringHead);
    EXPECT_EQ(commandsChannel.layout.semClient, commandsChannel2.layout.semClient);

    EXPECT_EQ(commandsChannel.layout.ringTail, commandsChannel2.layout.ringTail);
    EXPECT_EQ(commandsChannel.layout.semServer, commandsChannel2.layout.semServer);

    EXPECT_EQ(commandsChannel.layout.ringStart, commandsChannel2.layout.ringStart);
    EXPECT_EQ(commandsChannel.layout.ringCapacity, commandsChannel2.layout.ringCapacity);

    EXPECT_EQ(commandsChannel.layout.completionStampsStart, commandsChannel2.layout.completionStampsStart);
    EXPECT_EQ(commandsChannel.layout.completionStampsCapacity, commandsChannel2.layout.completionStampsCapacity);

    EXPECT_EQ(commandsChannel.layout.heapStart, commandsChannel2.layout.heapStart);
    EXPECT_EQ(commandsChannel.layout.heapEnd, commandsChannel2.layout.heapEnd);

    EXPECT_EQ(commandsChannel.semClient, commandsChannel2.semClient);
    EXPECT_EQ(commandsChannel.semServer, commandsChannel2.semServer);

    EXPECT_EQ(commandsChannel.ring.peekHead(), commandsChannel2.ring.peekHead());
    EXPECT_EQ(commandsChannel.ring.getCapacity(), commandsChannel2.ring.getCapacity());
}

TEST(CommandsChannelPartitionUsingGivenLayout, whenInitializationOfControlBlockIsNotRequestedThenDoesNotResetRingAndDoesNotInitializeSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    std::vector<char> shmem;
    using ValidLayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(ValidLayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = ValidLayoutT::minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox commandsChannel;
    ASSERT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false));

    CommandsChannelWhiteBox commandsChannel2;
    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel2.partition(alignedShmem, alignedShmemSize, commandsChannel.layout, false));
    EXPECT_FALSE(commandsChannel2.ownsSemaphores);
    EXPECT_EQ(0, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(3, *ringHead);
    EXPECT_EQ(5, *ringTail);
}

TEST(CommandsChannelPartitionUsingGivenLayout, whenInitializationOfControlBlockIsRequestedThenResetsRingAndInitializesSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    std::vector<char> shmem;
    using ValidLayoutT = Cal::Rpc::CommandsChannel::DefaultLayout;
    shmem.resize(ValidLayoutT::minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = ValidLayoutT::minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox commandsChannel;
    ASSERT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false));

    CommandsChannelWhiteBox commandsChannel2;

    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel2.partition(alignedShmem, alignedShmemSize, commandsChannel.layout, true));
    EXPECT_TRUE(commandsChannel2.ownsSemaphores);
    EXPECT_EQ(2, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(0, *ringHead);
    EXPECT_EQ(0, *ringTail);
}

class ChannelClientWhiteBox : public Cal::Rpc::ChannelClient {
  public:
    using CommandsChannel::layout;
    using CommandsChannel::ownsSemaphores;
    using CommandsChannel::ring;
    using CommandsChannel::semClient;
    using CommandsChannel::semServer;
    using CommandsChannel::shmem;
    using CommandsChannel::shmemSize;

    using CommandsChannel::getAsLocalAddress;
    using CommandsChannel::getAsShmemOffset;
    using CommandsChannel::partition;

    using ChannelClient::ChannelClient;
    using ChannelClient::completionStamps;
    using ChannelClient::heap;
    using ChannelClient::semaphoreWaitThreshold;
    using ChannelClient::serviceSynchronizationMethod;
    using ChannelClient::underlyingShmem;
};

TEST(ChannelClientInit, givenInvalidSynchronizationMethodWhenInitializingThenFailsAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Mocks::ConnectionMock connection;
    Cal::Mocks::MockShmemManager shmemManager;
    ChannelClientWhiteBox channelClient{connection, shmemManager};
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::unknown));
    EXPECT_FALSE(logs.empty());
}

TEST(ChannelClientInit, whenFailedToAllocateShmemForCommandsChannelThenFailsAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqAllocateShmem>;
    using InMessages = std::tuple<RespAllocateShmem>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> connection;
    std::get<0>(connection.outMessages).size = 0;
    std::get<0>(connection.outMessages).purpose = ReqAllocateShmem::rpcMessageChannel;
    std::get<0>(connection.inMessages).id = -1;
    Cal::Mocks::MockShmemManager shmemManager;
    ChannelClientWhiteBox channelClient{connection, shmemManager};
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
}

TEST(ChannelClientInit, whenFailedToMapAllocatedShmemForCommandsChannelThenFailsAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqAllocateShmem>;
    using InMessages = std::tuple<RespAllocateShmem>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> connection;
    std::get<0>(connection.outMessages).size = 0;
    std::get<0>(connection.outMessages).purpose = ReqAllocateShmem::rpcMessageChannel;
    std::get<0>(connection.inMessages).id = 1;
    std::get<0>(connection.inMessages).size = Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize;
    Cal::Mocks::MockShmemManager shmemManager;
    ChannelClientWhiteBox channelClient{connection, shmemManager};
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    EXPECT_EQ(1U, shmemManager.remoteShmemsLog.size());
}

class ChannelClientMockFailPartition : public ChannelClientWhiteBox {
  public:
    using ChannelClientWhiteBox::ChannelClientWhiteBox;
    bool partition(void *shmem, size_t shmemSize, bool initializeControlBlock) override {
        ++failedPartitionCallsCounter;
        return false;
    }
    bool partition(void *shmem, size_t shmemSize, const Cal::Messages::CommandsChannelLayout &existingLayout, bool initializeControlBlock) override {
        ++failedPartitionCallsCounter;
        return false;
    }

    int failedPartitionCallsCounter = 0;
};

TEST(ChannelClientInit, whenFailedToPartitionTheCommandChannelThenFailsAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqAllocateShmem>;
    using InMessages = std::tuple<RespAllocateShmem>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> connection;
    std::get<0>(connection.outMessages).size = 0;
    std::get<0>(connection.outMessages).purpose = ReqAllocateShmem::rpcMessageChannel;
    std::get<0>(connection.inMessages).size = Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize;
    Cal::Mocks::MockShmemManager shmemManager;
    auto shmem = shmemManager.get(Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize, false);
    ChannelClientMockFailPartition channelClient{connection, shmemManager};
    std::get<0>(connection.inMessages).id = shmem.id;
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
    EXPECT_EQ(0, channelClient.failedPartitionCallsCounter);
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    EXPECT_EQ(1U, shmemManager.remoteShmemsLog.size());
    EXPECT_EQ(1, channelClient.failedPartitionCallsCounter);
    shmemManager.release(shmem);
}

auto createChannelClientInitProtocolMockConnection(int shmemId, void *shmem, size_t shmemSize) {
    CommandsChannelWhiteBox tempChannel;
    if (false == tempChannel.partition(shmem, shmemSize, false)) {
        throw std::runtime_error("Failed to partition channel for mock");
    }

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqAllocateShmem, ReqLaunchRpcShmemRingBuffer>;
    using InMessages = std::tuple<RespAllocateShmem, RespLaunchRpcShmemRingBuffer>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> connection;
    std::get<0>(connection.outMessages).size = 0;
    std::get<0>(connection.outMessages).purpose = ReqAllocateShmem::rpcMessageChannel;
    std::get<0>(connection.inMessages).size = Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize;
    std::get<0>(connection.inMessages).id = shmemId;

    std::get<1>(connection.outMessages).ringbufferShmemId = shmemId;
    std::get<1>(connection.outMessages).layout = tempChannel.layout;
    std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::activePolling;
    return connection;
}

TEST(ChannelClientInit, whenFailedToLaunchTheCommandsChannelThenFailsAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Mocks::MockShmemManager shmemManager;
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.get(Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize, false);

    using namespace Cal::Messages;
    auto connection = createChannelClientInitProtocolMockConnection(commandsChannelShmem.id, commandsChannelShmem.ptr, commandsChannelShmem.size);
    std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::unknown;

    ChannelClientWhiteBox channelClient{connection, shmemManager};
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    shmemManager.release(commandsChannelShmem);
}

TEST(ChannelClientInit, whenInitializationIsSuccesfullThenSetsSemaphoreWaitThresholdAccordingly) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::MockShmemManager shmemManager;
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.get(Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize, false);
    auto connectionTemplate = createChannelClientInitProtocolMockConnection(commandsChannelShmem.id, commandsChannelShmem.ptr, commandsChannelShmem.size);

    {
        auto connection = connectionTemplate;
        ChannelClientWhiteBox channelClient{connection, shmemManager};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(Cal::Rpc::ChannelClient::SemaphoreThresholds::unreachableAlwaysActiveWait, channelClient.semaphoreWaitThreshold);
    }

    {
        auto connection = connectionTemplate;
        ChannelClientWhiteBox channelClient{connection, shmemManager};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::semaphores));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(Cal::Rpc::ChannelClient::SemaphoreThresholds::unreachableAlwaysSemaphores, channelClient.semaphoreWaitThreshold);
    }

    {
        auto connection = connectionTemplate;
        ChannelClientWhiteBox channelClient{connection, shmemManager};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::latencyBased));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(Cal::Rpc::ChannelClient::SemaphoreThresholds::base, channelClient.semaphoreWaitThreshold);
    }
    shmemManager.release(commandsChannelShmem);
}

TEST(ChannelClientInit, whenInitializationIsSuccesfullThenSetsServiceWaitMethodBasedOnResponseFromService) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::MockShmemManager shmemManager;
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.get(Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize, false);

    using namespace Cal::Messages;
    auto connectionTemplate = createChannelClientInitProtocolMockConnection(commandsChannelShmem.id, commandsChannelShmem.ptr, commandsChannelShmem.size);

    {
        auto connection = connectionTemplate;
        std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::activePolling;
        ChannelClientWhiteBox channelClient{connection, shmemManager};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(RespLaunchRpcShmemRingBuffer::activePolling, channelClient.serviceSynchronizationMethod);
    }

    {
        auto connection = connectionTemplate;
        std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::semaphores;
        ChannelClientWhiteBox channelClient{connection, shmemManager};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(RespLaunchRpcShmemRingBuffer::semaphores, channelClient.serviceSynchronizationMethod);
    }

    shmemManager.release(commandsChannelShmem);
}

TEST(ChannelClientInit, whenInitializationIsSuccesfullThenRingBufferIsLaunchedAndHeapAndCompletionStampsAreInitialized) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::MockShmemManager shmemManager;
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.get(Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize, false);
    auto connection = createChannelClientInitProtocolMockConnection(commandsChannelShmem.id, commandsChannelShmem.ptr, commandsChannelShmem.size);

    ChannelClientWhiteBox channelClient{connection, shmemManager};
    EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling));
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";

    EXPECT_EQ(channelClient.getAsLocalAddress(channelClient.layout.completionStampsStart),
              channelClient.completionStamps.allocate());
    EXPECT_EQ(channelClient.layout.completionStampsCapacity, channelClient.completionStamps.getCapacity());

    auto heapRamge = Cal::Utils::AddressRange{channelClient.getAsLocalAddress(channelClient.layout.heapStart), static_cast<size_t>(channelClient.layout.heapEnd - channelClient.layout.heapStart)};
    EXPECT_EQ(heapRamge, channelClient.heap.getRange());

    shmemManager.release(commandsChannelShmem);
}

TEST(ChannelClient, WhenBeingDestroyedThenReleasesUnderlyingShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::ConnectionMock connection;
    Cal::Mocks::MockShmemManager shmemManager;
    {
        ChannelClientWhiteBox channelClient{connection, shmemManager};
        channelClient.underlyingShmem = shmemManager.get(Cal::Rpc::CommandsChannel::DefaultLayout::minShmemSize, false);
        EXPECT_FALSE(shmemManager.allocatedShmems.empty());
    }
    EXPECT_TRUE(shmemManager.allocatedShmems.empty());
}

} // namespace Ult
} // namespace Cal
