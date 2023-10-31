/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/icd_ocl.h"
#include "gtest/gtest.h"
#include "test/mocks/log_mock.h"
#include "test/utils/cli_utils.h"
#include "test/utils/custom_event_listener.h"
#include "test/utils/signal_utils.h"

#include <cstdint>
#include <string>

TEST(ClBufferRecycler, givenBufferSizeThenReturnsProperBucketIdForThatSize) {
#define EXPECT_EQ_BUCKET_ID(EXPECTED_BUCKET_ID, SIZE) EXPECT_EQ(EXPECTED_BUCKET_ID, Cal::Client::Icd::Ocl::ClBufferRecycler::getBucketIdForSize(SIZE)) << "size : " << SIZE

    EXPECT_EQ_BUCKET_ID(0U, 0);
    EXPECT_EQ_BUCKET_ID(0U, 1);
    EXPECT_EQ_BUCKET_ID(0U, Cal::Client::Icd::Ocl::ClBufferRecycler::minBucketSize - 1);
    EXPECT_EQ_BUCKET_ID(0U, Cal::Client::Icd::Ocl::ClBufferRecycler::minBucketSize);
    int bucketSize = Cal::Client::Icd::Ocl::ClBufferRecycler::minBucketSize;
    auto bucketId = 1U;
    while (bucketSize < static_cast<int64_t>(Cal::Client::Icd::Ocl::ClBufferRecycler::maxBucketSize)) {
        EXPECT_EQ_BUCKET_ID(bucketId, bucketSize + 1);
        EXPECT_EQ_BUCKET_ID(bucketId, bucketSize * 2 - 1);
        EXPECT_EQ_BUCKET_ID(bucketId, bucketSize * 2);
        bucketSize *= 2;
        ++bucketId;
    }

#undef EXPECT_EQ_BUCKET_ID
}

int main(int argc, char *argv[]) {
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
