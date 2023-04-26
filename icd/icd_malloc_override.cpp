/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "include/cal.h"
#include "shared/utils.h"

#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <mutex>

using MallocFT = void *(*)(size_t);
using FreeFT = void (*)(void *);
using CallocFT = void *(*)(size_t, size_t);
using ReallocFT = void *(*)(void *, size_t);

namespace Cal {

namespace MallocOverride {

template <typename FT>
static FT getOriginalFunc(const char *fname) {
    auto orignalF = reinterpret_cast<FT>(dlsym(RTLD_NEXT, fname));
    if (NULL == orignalF) {
        fprintf(stderr, "Could not find %s because %s\n", fname, dlerror());
        std::abort();
    }
    return orignalF;
}

bool isCalMallocOverrideEnabled() {
    static bool enabled = Cal::Utils::getCalEnvFlag(calOverrideMallocEnvName);
    return enabled;
}

namespace Original {
void *malloc(size_t size) {
    static MallocFT orignalF = getOriginalFunc<MallocFT>("malloc");
    return orignalF(size);
}

void free(void *ptr) {
    static FreeFT orignalF = getOriginalFunc<FreeFT>("free");
    orignalF(ptr);
}

void *calloc(size_t nitems, size_t size) {
    static CallocFT orignalF = getOriginalFunc<CallocFT>("calloc");
    return orignalF(nitems, size);
}

void *realloc(void *ptr, size_t size) {
    static ReallocFT orignalF = getOriginalFunc<ReallocFT>("realloc");
    return orignalF(ptr, size);
}
} // namespace Original

namespace AsShmem {
void *malloc(size_t size) {
    // placeholder
    return Cal::MallocOverride::Original::malloc(size);
}

void free(void *ptr) {
    // placeholder
    return Cal::MallocOverride::Original::free(ptr);
}

void *calloc(size_t nitems, size_t size) {
    // placeholder
    return Cal::MallocOverride::Original::calloc(nitems, size);
}

void *realloc(void *ptr, size_t size) {
    // placeholder
    return Cal::MallocOverride::Original::realloc(ptr, size);
}

} // namespace AsShmem

void *malloc(size_t size) {
    void *p = NULL;
    if (predict_true(isCalMallocOverrideEnabled())) {
        p = AsShmem::malloc(size);
    } else {
        p = Original::malloc(size);
    }
    return p;
}

void free(void *ptr) {
    if (predict_true(isCalMallocOverrideEnabled())) {
        AsShmem::free(ptr);
    } else {
        Original::free(ptr);
    }
}

void *calloc(size_t nitems, size_t size) {
    void *p = NULL;
    if (predict_true(isCalMallocOverrideEnabled())) {
        p = AsShmem::calloc(nitems, size);
    } else {
        p = Original::calloc(nitems, size);
    }
    return p;
}

void *realloc(void *ptr, size_t size) {
    void *p = NULL;
    if (predict_true(isCalMallocOverrideEnabled())) {
        p = AsShmem::realloc(ptr, size);
    } else {
        p = Original::realloc(ptr, size);
    }
    return p;
}

} // namespace MallocOverride

} // namespace Cal
