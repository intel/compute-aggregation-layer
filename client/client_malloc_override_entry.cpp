/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <cstddef>

namespace Cal::Icd::MallocOverride {
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nitems, size_t size);
void *realloc(void *ptr, size_t size);
} // namespace Cal::Icd::MallocOverride

extern "C" {

#ifdef __clang__
#pragma clang optimize off
#else
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif
void *malloc(size_t size) {
    return Cal::Icd::MallocOverride::malloc(size);
}

void free(void *ptr) {
    Cal::Icd::MallocOverride::free(ptr);
}

void *calloc(size_t nitems, size_t size) {
    return Cal::Icd::MallocOverride::calloc(nitems, size);
}

void *realloc(void *ptr, size_t size) {
    return Cal::Icd::MallocOverride::realloc(ptr, size);
}
#ifdef __clang__
#pragma clang optimize on
#else
#pragma GCC pop_options
#endif
}