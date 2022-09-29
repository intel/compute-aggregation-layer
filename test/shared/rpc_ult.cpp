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

} // namespace Ult
} // namespace Cal
