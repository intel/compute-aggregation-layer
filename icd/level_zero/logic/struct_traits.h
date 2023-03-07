/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <type_traits>

namespace Cal::Icd::LevelZero::Logic {

template <class, class = void>
struct hasPNext : std::false_type {};

template <class T>
struct hasPNext<T, std::void_t<decltype(std::declval<T>().pNext)>> : std::true_type {};

} // namespace Cal::Icd::LevelZero::Logic
