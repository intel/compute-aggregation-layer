/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/level_zero/debugger/debugger.h"

namespace Cal::Client::Icd::LevelZero {

const std::vector<std::string> L0DebuggerProcessesNames = {
    "gdb",
    /* L0 tests that mimic gdb */
    "test_debug",
    "test_debug_helper",
    "child_debugger"};

} // namespace Cal::Client::Icd::LevelZero
