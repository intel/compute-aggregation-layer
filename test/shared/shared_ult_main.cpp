/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "test/mocks/log_mock.h"

#include <cstdio>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    Cal::Mocks::LogCaptureContext globalLogsCapture;
    auto ret = RUN_ALL_TESTS();
    if (false == globalLogsCapture.empty()) {
        printf("Unexpected CAL logs captured globally:\n[%s]\n", globalLogsCapture.str().c_str());
        if (0 == ret) {
            ret = -1;
        }
    }

    return ret;
}
