/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <type_traits>

namespace Cal::Icd::LevelZero::Logic {

/*
 *  AlwaysFalse metafunction maps any type to std::false_type.
 *  It is utilized when we want to throw an error from static_assert.
 */
template <typename...>
struct AlwaysFalse : std::false_type {};

/*
 *  HasPNext type trait predicates if the given type contains
 *  a non-static member called pNext. It is utilized to check structures
 *  from LevelZero API.
 */
template <class, class = void>
struct HasPNext : std::false_type {};

template <class T>
struct HasPNext<T, std::void_t<decltype(std::declval<T>().pNext)>> : std::true_type {};

} // namespace Cal::Icd::LevelZero::Logic
