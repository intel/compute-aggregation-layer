/*
 * Copyright (C) 2022-2023 Intel Corporation
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

inline const char *asStr(ApiType apiType) {
    switch (apiType) {
    default:
        return "unknown";
    case Cal::ApiType::OpenCL:
        return "OpenCL";
    case Cal::ApiType::LevelZero:
        return "LevelZero";
    }
}

} // namespace Cal
