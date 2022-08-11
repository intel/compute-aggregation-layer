/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "icd/icd_ocl.h"

#include <string>

TEST(ClBufferRecycler, givenBufferSizeThenReturnsProperBucketIdForThatSize) {
#define EXPECT_EQ_BUCKET_ID(EXPECTED_BUCKET_ID, SIZE) EXPECT_EQ(EXPECTED_BUCKET_ID, Cal::Icd::Ocl::ClBufferRecycler::getBucketIdForSize(SIZE)) << "size : " << SIZE

    EXPECT_EQ_BUCKET_ID(0U, 0);
    EXPECT_EQ_BUCKET_ID(0U, 1);
    EXPECT_EQ_BUCKET_ID(0U, Cal::Icd::Ocl::ClBufferRecycler::minBucketSize - 1);
    EXPECT_EQ_BUCKET_ID(0U, Cal::Icd::Ocl::ClBufferRecycler::minBucketSize);
    int bucketSize = Cal::Icd::Ocl::ClBufferRecycler::minBucketSize;
    int bucketId = 1U;
    while (bucketSize < Cal::Icd::Ocl::ClBufferRecycler::maxBucketSize) {
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

    auto ret = RUN_ALL_TESTS();

    return ret;

    return 0;
}
