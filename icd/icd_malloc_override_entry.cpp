/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <cstddef>

namespace Cal::MallocOverride {
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nitems, size_t size);
void *realloc(void *ptr, size_t size);
} // namespace Cal::MallocOverride

extern "C" {

void *malloc(size_t size) {
    return Cal::MallocOverride::malloc(size);
}

void free(void *ptr) {
    Cal::MallocOverride::free(ptr);
}

void *calloc(size_t nitems, size_t size) {
    return Cal::MallocOverride::calloc(nitems, size);
}

void *realloc(void *ptr, size_t size) {
    return Cal::MallocOverride::realloc(ptr, size);
}
}