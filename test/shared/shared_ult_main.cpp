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

    Cal::Mocks::DisallowLogs disallowLogs;
    auto ret = RUN_ALL_TESTS();
    return ret;
}
