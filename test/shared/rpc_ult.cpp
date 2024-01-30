/*
 * Copyright (C) 2022-2024 Intel Corporation
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
    EXPECT_EQ(0, ring.peekHeadOffset());
    EXPECT_EQ(0, ring.peekTailOffset());
    head = 1;
    tail = 4;
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(1, ring.peekHeadOffset());
    EXPECT_EQ(4, ring.peekTailOffset());
    EXPECT_EQ(3, *ring.peekHead());
}

TEST(TypedRing, whenResetIsCalledThenReinitializesHeadAndTailOffsetToZero) {
    std::vector<int> data = {2, 3, 5, 7, 11, 13};
    int head = 1;
    int tail = 4;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(1, ring.peekHeadOffset());
    EXPECT_EQ(4, ring.peekTailOffset());
    ring.reset();
    EXPECT_EQ(0, ring.peekHeadOffset());
    EXPECT_EQ(0, ring.peekTailOffset());
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
    EXPECT_TRUE(ring.push(17, false));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(1, tail);
    EXPECT_EQ(0, head);
    EXPECT_EQ(17, data[0]);
    EXPECT_EQ(17, *ring.peekHead());

    EXPECT_TRUE(ring.push(19, false));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(2, tail);
    EXPECT_EQ(0, head);
    EXPECT_EQ(19, data[1]);
}

TEST(TypedRingPush, whenBatchedPushThenDoNotUpdateHead) {
    std::vector<int> data = {2, 3, 5};
    int head = 0;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.push(17, true));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(0, tail);
    EXPECT_EQ(0, head);
    EXPECT_EQ(17, data[0]);

    EXPECT_TRUE(ring.push(19, false));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(2, tail);
    EXPECT_EQ(0, head);
    EXPECT_EQ(17, data[0]);
    EXPECT_EQ(19, data[1]);
}

TEST(TypedRingPush, whenTailAtEndAndHeadOn0ThenPushReturnsFalseDueToRingBeingFull) {
    Cal::Mocks::LogCaptureContext logs;
    std::vector<int> data = {2, 3, 5};
    int head = 0;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_TRUE(ring.push(17, false));
    EXPECT_TRUE(ring.push(19, false));

    EXPECT_FALSE(ring.push(23, false));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(2, tail);
    EXPECT_EQ(0, head);

    EXPECT_EQ(17, data[0]);
    EXPECT_EQ(19, data[1]);
    EXPECT_EQ(5, data[2]);
}

TEST(TypedRingPush, whenTailAtEndAndHeadNotOn0ThenPushSucceedsAndWraps) {
    std::vector<int> data = {2, 3, 5};
    int head = 1;
    int tail = 2;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_TRUE(ring.push(23, false));
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
    EXPECT_TRUE(ring.push(23, false));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(1, tail);
    EXPECT_EQ(2, head);

    EXPECT_EQ(23, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(5, data[2]);
}

TEST(TypedRingPush, whenWrappedAndRingFullThenPushReturnsFalse) {
    Cal::Mocks::LogCaptureContext logs;
    std::vector<int> data = {2, 3, 5};
    int head = 1;
    int tail = 0;

    Cal::Rpc::TypedRing<int, int> ring{data.data(), data.size(), &head, &tail};
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_FALSE(ring.push(23, false));
    EXPECT_EQ(0U, ring.peekIteration());
    EXPECT_EQ(0, tail);
    EXPECT_EQ(1, head);

    EXPECT_EQ(2, data[0]);
    EXPECT_EQ(3, data[1]);
    EXPECT_EQ(5, data[2]);
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    commandsChannel.ownsSemaphores = false;
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
    EXPECT_FALSE(commandsChannel.partition(shmem.data() + 1, Cal::Utils::pageSize4KB * 15, false, false));

    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartitionUsingDefaultLayout, givenUnalignedShmemSizeThenFailsAndEmitsWarning) {
    CommandsChannelWhiteBox commandsChannel;
    Cal::Mocks::LogCaptureContext logs;

    std::vector<char> shmem;
    shmem.resize(Cal::Utils::pageSize4KB * 16);
    EXPECT_FALSE(commandsChannel.partition(Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data()), Cal::Utils::pageSize4KB * 15 - 1, false, false));

    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartitionUsingDefaultLayout, givenTooSmallShmemSizeThenFailsAndEmitsWarning) {
    CommandsChannelWhiteBox commandsChannel;
    Cal::Mocks::LogCaptureContext logs;

    std::vector<char> shmem;
    shmem.resize(Cal::Utils::pageSize4KB * 16);
    EXPECT_FALSE(commandsChannel.partition(Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data()),
                                           Cal::Rpc::CommandsChannel::Layout().minShmemSize - Cal::Utils::pageSize4KB, false, false));

    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartitioUsingDefaultLayoutn, givenCorrectShmemSizeThenPartitionsItUsingDefaultLayout) {
    CommandsChannelWhiteBox commandsChannel;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false, false));

    EXPECT_EQ(layout.ringHead, commandsChannel.layout.ringHead);
    EXPECT_EQ(layout.semClient, commandsChannel.layout.semClient);

    EXPECT_EQ(layout.ringTail, commandsChannel.layout.ringTail);
    EXPECT_EQ(layout.semServer, commandsChannel.layout.semServer);

    EXPECT_EQ(layout.ringStart, commandsChannel.layout.ringStart);
    EXPECT_EQ((layout.ringEnd - layout.ringStart) / sizeof(Cal::Rpc::RingEntry), commandsChannel.layout.ringCapacity);

    EXPECT_EQ(layout.completionStampsStart, commandsChannel.layout.completionStampsStart);
    EXPECT_EQ((layout.completionStampsEnd - layout.completionStampsStart) / sizeof(Cal::Rpc::CompletionStampT), commandsChannel.layout.completionStampsCapacity);

    EXPECT_EQ(layout.clientHeapStart, commandsChannel.layout.clientHeapStart);
    EXPECT_EQ(static_cast<int64_t>(alignedShmemSize), commandsChannel.layout.clientHeapEnd);

    EXPECT_EQ(commandsChannel.getAsLocalAddress<sem_t>(layout.semClient), commandsChannel.semClient);
    EXPECT_EQ(commandsChannel.getAsLocalAddress<sem_t>(layout.semServer), commandsChannel.semServer);

    EXPECT_EQ(layout.ringStart, commandsChannel.getAsShmemOffset(commandsChannel.ring.peekHead()));
    EXPECT_EQ((layout.ringEnd - layout.ringStart) / sizeof(Cal::Rpc::RingEntry), commandsChannel.ring.getCapacity());
}

TEST(CommandsChannelPartitionUsingDefaultLayout, whenInitializationOfControlBlockIsNotRequestedThenDoesNotResetRingAndDoesNotInitializeSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, layout.ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, layout.ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false, false));
    EXPECT_FALSE(commandsChannel.ownsSemaphores);
    EXPECT_EQ(0u, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(3, *ringHead);
    EXPECT_EQ(5, *ringTail);
}

TEST(CommandsChannelPartitionUsingDefaultLayout, whenInitializationOfControlBlockIsRequestedThenResetsRingAndInitializesSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    CommandsChannelWhiteBox commandsChannel;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, layout.ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, layout.ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, true, false));
    EXPECT_TRUE(commandsChannel.ownsSemaphores);
    EXPECT_EQ(3u, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(0, *ringHead);
    EXPECT_EQ(0, *ringTail);
}

TEST(CommandsChannelPartitionUsingDefaultLayout, whenInitializationOfControlBlockIsRequestedButInitializationOfSemaphoresFailsThenCleansUpReturnsFalseAndEmitsErrorMessage) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        tempSysCallsCtx.apiConfig.sem_init.returnValue = -1;
        EXPECT_FALSE(commandsChannel.partition(alignedShmem, alignedShmemSize, true, false));
        EXPECT_EQ(1u, tempSysCallsCtx.apiConfig.sem_init.callCount);
        EXPECT_FALSE(commandsChannel.ownsSemaphores);
        EXPECT_FALSE(logs.empty());
        EXPECT_EQ(0u, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
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
        EXPECT_FALSE(commandsChannel.partition(alignedShmem, alignedShmemSize, true, false));
        EXPECT_EQ(2u, tempSysCallsCtx.apiConfig.sem_init.callCount);
        EXPECT_EQ(1u, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
        EXPECT_FALSE(logs.empty());
    }
}

TEST(CommandsChannelPartition, whenInitializedSempahoresThenDestroysThemDuringOwnDestructor) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, true, false));
        EXPECT_TRUE(commandsChannel.ownsSemaphores);
        EXPECT_EQ(3u, tempSysCallsCtx.apiConfig.sem_init.callCount);
    }

    EXPECT_EQ(3u, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
}

TEST(CommandsChannelPartition, whenInitializedSempahoresButFailedToDestroyThemThenEmitsWarning) {
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, true, false));
        EXPECT_TRUE(commandsChannel.ownsSemaphores);
        EXPECT_EQ(3u, tempSysCallsCtx.apiConfig.sem_init.callCount);
        tempSysCallsCtx.apiConfig.sem_destroy.returnValue = -1;
    }

    EXPECT_EQ(3u, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(CommandsChannelPartition, whenDidNotInitializeSempahoresThenDoesNotDestroyThemDuringOwnDestructor) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout layout;
    shmem.resize(layout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = layout.minShmemSize + Cal::Utils::pageSize4KB;

    {
        CommandsChannelWhiteBox commandsChannel;
        EXPECT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false, false));
        EXPECT_FALSE(commandsChannel.ownsSemaphores);
        EXPECT_EQ(0u, tempSysCallsCtx.apiConfig.sem_init.callCount);
    }

    EXPECT_EQ(0u, tempSysCallsCtx.apiConfig.sem_destroy.callCount);
}

TEST(CommandsChannelPartitionUsingGivenLayout, givenInvalidLayoutThenFailsAndEmitsWarning) {
    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout validDefaultLayout;
    shmem.resize(validDefaultLayout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = validDefaultLayout.minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox validCommandsChannel;
    ASSERT_TRUE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, false, false));

    auto validLayout = validCommandsChannel.layout;
    ASSERT_TRUE(validLayout.isValid());
    ASSERT_TRUE(validCommandsChannel.partition(alignedShmem, alignedShmemSize, validLayout, false));

    auto invalidLayout = validLayout;

    Cal::Messages::OffsetWithinChannelT *offsetsToBreak[] = {&invalidLayout.semClient, &invalidLayout.semServer, &invalidLayout.ringHead, &invalidLayout.ringTail,
                                                             &invalidLayout.ringStart, &invalidLayout.completionStampsStart, &invalidLayout.clientHeapStart, &invalidLayout.clientHeapEnd};

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
    Cal::Rpc::CommandsChannel::Layout validDefaultLayout;
    shmem.resize(validDefaultLayout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = validDefaultLayout.minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox commandsChannel;
    ASSERT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false, false));

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

    EXPECT_EQ(commandsChannel.layout.clientHeapStart, commandsChannel2.layout.clientHeapStart);
    EXPECT_EQ(commandsChannel.layout.clientHeapEnd, commandsChannel2.layout.clientHeapEnd);

    EXPECT_EQ(commandsChannel.semClient, commandsChannel2.semClient);
    EXPECT_EQ(commandsChannel.semServer, commandsChannel2.semServer);

    EXPECT_EQ(commandsChannel.ring.peekHead(), commandsChannel2.ring.peekHead());
    EXPECT_EQ(commandsChannel.ring.getCapacity(), commandsChannel2.ring.getCapacity());
}

TEST(CommandsChannelPartitionUsingGivenLayout, whenInitializationOfControlBlockIsNotRequestedThenDoesNotResetRingAndDoesNotInitializeSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout validDefaultLayout;
    shmem.resize(validDefaultLayout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = validDefaultLayout.minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox commandsChannel;
    ASSERT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false, false));

    CommandsChannelWhiteBox commandsChannel2;
    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel2.partition(alignedShmem, alignedShmemSize, commandsChannel.layout, false));
    EXPECT_FALSE(commandsChannel2.ownsSemaphores);
    EXPECT_EQ(0u, tempSysCallsCtx.apiConfig.sem_init.callCount);

    EXPECT_EQ(3, *ringHead);
    EXPECT_EQ(5, *ringTail);
}

TEST(CommandsChannelPartitionUsingGivenLayout, whenInitializationOfControlBlockIsRequestedThenResetsRingAndInitializesSemaphores) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    std::vector<char> shmem;
    Cal::Rpc::CommandsChannel::Layout validDefaultLayout;
    shmem.resize(validDefaultLayout.minShmemSize + 3 * Cal::Utils::pageSize4KB);
    char *alignedShmem = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(shmem.data());
    size_t alignedShmemSize = validDefaultLayout.minShmemSize + Cal::Utils::pageSize4KB;
    CommandsChannelWhiteBox commandsChannel;
    ASSERT_TRUE(commandsChannel.partition(alignedShmem, alignedShmemSize, false, false));

    CommandsChannelWhiteBox commandsChannel2;

    auto ringHead = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringHead));
    auto ringTail = reinterpret_cast<Cal::Rpc::OffsetWithinChannelT *>(Cal::Utils::moveByBytes(alignedShmem, commandsChannel.layout.ringTail));

    *ringHead = 3;
    *ringTail = 5;

    EXPECT_TRUE(commandsChannel2.partition(alignedShmem, alignedShmemSize, commandsChannel.layout, true));
    EXPECT_TRUE(commandsChannel2.ownsSemaphores);
    EXPECT_EQ(3u, tempSysCallsCtx.apiConfig.sem_init.callCount);

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
    using ChannelClient::cmdHeap;
    using ChannelClient::completionStamp;
    using ChannelClient::semaphoreWaitThreshold;
    using ChannelClient::serviceSynchronizationMethod;
    using ChannelClient::standaloneHeap;
    using ChannelClient::underlyingShmem;
};

TEST(ChannelClientInit, givenInvalidSynchronizationMethodWhenInitializingThenFailsAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Mocks::ConnectionMock connection;
    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::unknown, false));
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
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
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
    std::get<0>(connection.inMessages).size = Cal::Rpc::CommandsChannel::Layout().minShmemSize;
    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    EXPECT_EQ(1U, shmemManager.remoteShmemsLog.size());
}

class ChannelClientMockFailPartition : public ChannelClientWhiteBox {
  public:
    using ChannelClientWhiteBox::ChannelClientWhiteBox;
    bool partition(void *shmem, size_t shmemSize, bool initializeControlBlock, bool useAsyncCalls) override {
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
    std::get<0>(connection.inMessages).size = Cal::Rpc::CommandsChannel::Layout().minShmemSize;
    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    auto shmem = shmemManager.allocate(Cal::Rpc::CommandsChannel::Layout().minShmemSize, false);
    ChannelClientMockFailPartition channelClient{connection, shmemManager, usmShmemImporter};
    std::get<0>(connection.inMessages).id = shmem.getShmemId();
    EXPECT_EQ(0U, shmemManager.remoteShmemsLog.size());
    EXPECT_EQ(0, channelClient.failedPartitionCallsCounter);
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    EXPECT_EQ(1U, shmemManager.remoteShmemsLog.size());
    EXPECT_EQ(1, channelClient.failedPartitionCallsCounter);
    shmemManager.free(shmem);
}

auto createChannelClientInitProtocolMockConnection(int shmemId, void *shmem, size_t shmemSize) {
    CommandsChannelWhiteBox tempChannel;
    if (false == tempChannel.partition(shmem, shmemSize, false, true)) {
        throw std::runtime_error("Failed to partition channel for mock");
    }

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqAllocateShmem, ReqLaunchRpcShmemRingBuffer>;
    using InMessages = std::tuple<RespAllocateShmem, RespLaunchRpcShmemRingBuffer>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> connection;
    std::get<0>(connection.outMessages).size = 0;
    std::get<0>(connection.outMessages).purpose = ReqAllocateShmem::rpcMessageChannel;
    std::get<0>(connection.inMessages).size = Cal::Rpc::CommandsChannel::Layout().minShmemSize;
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
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.allocate(Cal::Rpc::CommandsChannel::Layout().minShmemSize, false);

    using namespace Cal::Messages;
    auto connection = createChannelClientInitProtocolMockConnection(commandsChannelShmem.getShmemId(), commandsChannelShmem.getMmappedPtr(), commandsChannelShmem.getMmappedSize());
    std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::unknown;

    ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
    EXPECT_FALSE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
    EXPECT_FALSE(logs.empty());
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
    shmemManager.free(commandsChannelShmem);
}

TEST(ChannelClientInit, whenInitializationIsSuccesfullThenSetsSemaphoreWaitThresholdAccordingly) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.allocate(Cal::Rpc::CommandsChannel::Layout().minShmemSize, false);
    auto connectionTemplate = createChannelClientInitProtocolMockConnection(commandsChannelShmem.getShmemId(), commandsChannelShmem.getMmappedPtr(), commandsChannelShmem.getMmappedSize());

    {
        auto connection = connectionTemplate;
        ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(Cal::Rpc::ChannelClient::SemaphoreThresholds::unreachableAlwaysActiveWait, channelClient.semaphoreWaitThreshold);
    }

    {
        auto connection = connectionTemplate;
        ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::semaphores, false));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(Cal::Rpc::ChannelClient::SemaphoreThresholds::unreachableAlwaysSemaphores, channelClient.semaphoreWaitThreshold);
    }

    {
        auto connection = connectionTemplate;
        ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::latencyBased, false));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(Cal::Rpc::ChannelClient::SemaphoreThresholds::base, channelClient.semaphoreWaitThreshold);
    }
    shmemManager.free(commandsChannelShmem);
}

TEST(ChannelClientInit, whenInitializationIsSuccesfullThenSetsServiceWaitMethodBasedOnResponseFromService) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.allocate(Cal::Rpc::CommandsChannel::Layout().minShmemSize, false);

    using namespace Cal::Messages;
    auto connectionTemplate = createChannelClientInitProtocolMockConnection(commandsChannelShmem.getShmemId(), commandsChannelShmem.getMmappedPtr(), commandsChannelShmem.getMmappedSize());

    {
        auto connection = connectionTemplate;
        std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::activePolling;
        ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(RespLaunchRpcShmemRingBuffer::activePolling, channelClient.serviceSynchronizationMethod);
    }

    {
        auto connection = connectionTemplate;
        std::get<1>(connection.inMessages).serviceSynchronizationMethod = RespLaunchRpcShmemRingBuffer::semaphores;
        ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
        EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
        EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
        EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";
        EXPECT_EQ(RespLaunchRpcShmemRingBuffer::semaphores, channelClient.serviceSynchronizationMethod);
    }

    shmemManager.free(commandsChannelShmem);
}

TEST(ChannelClientInit, whenInitializationIsSuccesfullThenRingBufferIsLaunchedAndHeapAndCompletionStampsAreInitialized) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    shmemManager.allocateRealBackingMemory = true;
    auto commandsChannelShmem = shmemManager.allocate(Cal::Rpc::CommandsChannel::Layout().minShmemSize, false);
    auto connection = createChannelClientInitProtocolMockConnection(commandsChannelShmem.getShmemId(), commandsChannelShmem.getMmappedPtr(), commandsChannelShmem.getMmappedSize());

    ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
    EXPECT_TRUE(channelClient.init(ChannelClientWhiteBox::ClientSynchronizationMethod::activePolling, false));
    EXPECT_TRUE(connection.mismatchLogs.empty()) << " out messages issues : [" << connection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(connection.encodeIssues.empty()) << " in messages issues : [" << connection.getEncodeLogFlat() << "]";

    EXPECT_EQ(channelClient.getAsLocalAddress(channelClient.layout.completionStampsStart),
              channelClient.completionStamp);

    auto fullHeapRange = Cal::Utils::AddressRange{channelClient.getAsLocalAddress(channelClient.layout.clientHeapStart), static_cast<size_t>(channelClient.layout.clientHeapEnd - channelClient.layout.clientHeapStart)};
    EXPECT_EQ(fullHeapRange.base(), channelClient.cmdHeap.getRange().base());
    EXPECT_EQ(fullHeapRange.rightBound(), channelClient.standaloneHeap.getRange().rightBound());
    EXPECT_EQ(channelClient.cmdHeap.getRange().rightBound(), channelClient.standaloneHeap.getRange().base());

    shmemManager.free(commandsChannelShmem);
}

TEST(ChannelClient, WhenBeingDestroyedThenReleasesUnderlyingShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Mocks::ConnectionMock connection;
    Cal::Mocks::MockShmemManager shmemManager;
    Cal::Usm::UsmShmemImporter usmShmemImporter{shmemManager};
    {
        auto alloc = shmemManager.allocate(Cal::Rpc::CommandsChannel::Layout().minShmemSize, false);
        ChannelClientWhiteBox channelClient{connection, shmemManager, usmShmemImporter};
        channelClient.underlyingShmem = Cal::Mocks::MmappedShmemSubAllocationWhiteBox{alloc, 0};
        EXPECT_FALSE(shmemManager.allocatedShmems.empty());
    }
    EXPECT_TRUE(shmemManager.allocatedShmems.empty());
}

} // namespace Ult
} // namespace Cal
