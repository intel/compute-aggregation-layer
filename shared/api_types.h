/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <cstdint>

namespace Cal {

enum class ApiType : std::uint32_t {
    Unknown = 0,
    OpenCL = 1,
    LevelZero = 2,
};

} // namespace Cal
