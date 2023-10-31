/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <cstddef>

namespace Cal::Client::MallocOverride {
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nitems, size_t size);
void *realloc(void *ptr, size_t size);
} // namespace Cal::Client::MallocOverride

extern "C" {

#ifdef __clang__
#pragma clang optimize off
#else
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif
void *malloc(size_t size) {
    return Cal::Client::MallocOverride::malloc(size);
}

void free(void *ptr) {
    Cal::Client::MallocOverride::free(ptr);
}

void *calloc(size_t nitems, size_t size) {
    return Cal::Client::MallocOverride::calloc(nitems, size);
}

void *realloc(void *ptr, size_t size) {
    return Cal::Client::MallocOverride::realloc(ptr, size);
}
#ifdef __clang__
#pragma clang optimize on
#else
#pragma GCC pop_options
#endif
}