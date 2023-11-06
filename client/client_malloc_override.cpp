/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client_malloc_override.h"

#include "include/cal.h"
#include "shared/allocators.h"
#include "shared/shmem.h"
#include "shared/utils.h"

#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <execinfo.h>
#include <mutex>

using MallocFT = void *(*)(size_t);
using FreeFT = void (*)(void *);
using CallocFT = void *(*)(size_t, size_t);
using ReallocFT = void *(*)(void *, size_t);

namespace Cal {

namespace Client::MallocOverride {

void *mallocRetAddress = nullptr;
void *callocRetAddress = nullptr;
constexpr size_t naturalAlignment = 16U;

Cal::Utils::AddressRange readCalLibExecAddressRange() {
    Cal::Utils::AddressRange calLibExecAddressRange = {nullptr, size_t{0}};
    const char *mapFilePath = "/proc/self/maps";
    auto file = fopen(mapFilePath, "r");
    if (nullptr == file) {
        return calLibExecAddressRange;
    }
    char buffer[4096U] = {};
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, "libcal.so") && strstr(buffer, " r-xp ")) {
            // e.g. "7f593027f000-7f5930431000 "
            auto delimDash = strstr(buffer, "-");
            if (nullptr == delimDash) {
                break;
            }
            auto delimSpace = strstr(delimDash, " ");
            if (nullptr == delimSpace) {
                break;
            }
            auto from = strtoul(buffer, nullptr, 16);
            auto to = strtoul(delimDash + 1, nullptr, 16);
            calLibExecAddressRange = Cal::Utils::AddressRange{uintptr_t{from}, uintptr_t{to}};
            break;
        }
    }
    fclose(file);
    return calLibExecAddressRange;
}

bool isAllocFromCal(const Cal::Utils::AddressRange &libraryExecAddressRange) {
    constexpr int maxBacktraceDepth = 16;
    void *backtracePtrs[maxBacktraceDepth];
    int backtraceDepth = backtrace(backtracePtrs, maxBacktraceDepth);

    bool foundEntryPoint = false;
    for (int i = 0; i < backtraceDepth; ++i) {
        if (false == foundEntryPoint) {
            foundEntryPoint = (backtracePtrs[i] == Cal::Client::MallocOverride::mallocRetAddress) || (backtracePtrs[i] == Cal::Client::MallocOverride::callocRetAddress);
        } else {
            if (libraryExecAddressRange.contains(backtracePtrs[i])) {
                return true;
            }
        }
    }
    return false;
}

void *getRetAddress(const char *fname) {
    char pattern[1024];
    snprintf(pattern, sizeof(pattern), "libcal.so(%s", fname);
    constexpr int maxBacktraceDepth = 32;
    void *backtracePtrs[maxBacktraceDepth];
    int backtraceDepth = backtrace(backtracePtrs, maxBacktraceDepth);
    char **backtraceStrings = backtrace_symbols(backtracePtrs, backtraceDepth);
    void *ret = nullptr;
    for (int i = 0; i < backtraceDepth; ++i) {
        if (strstr(backtraceStrings[i], pattern)) {
            ret = backtracePtrs[i];
            break;
        }
    }
    free(backtraceStrings);
    return ret;
}

template <typename FT>
static FT getOriginalFunc(const char *fname) {
    auto orignalF = reinterpret_cast<FT>(dlsym(RTLD_NEXT, fname));
    if (NULL == orignalF) {
        auto err = dlerror();
        if (err) {
            fprintf(stderr, "Could not find %s because %s\n", fname, err);
        } else {
            fprintf(stderr, "Could not find %s\n", fname);
        }
        std::abort();
    }
    return orignalF;
}

namespace Original {
MallocFT malloc = nullptr;
FreeFT free = nullptr;
CallocFT calloc = nullptr;
ReallocFT realloc = nullptr;
} // namespace Original

namespace Overriden {
MallocFT malloc = nullptr;
FreeFT free = nullptr;
CallocFT calloc = nullptr;
ReallocFT realloc = nullptr;
} // namespace Overriden

namespace AsCalShmem {

struct GlobalState {
    size_t threshold = Cal::Utils::pageSize4KB;
    size_t maxCapacity = 4 * Cal::Utils::GB;
    size_t initialCapacity = 8 * Cal::Utils::MB;

    char privateMallocShmemPath[4096] = {};
    int shmemFd = -1;
    Cal::Utils::AddressRange asShmemHeapRange = {0U, 0U};
    std::mutex mutex;
    Cal::Allocators::RangeAllocator rangeAllocator;
    size_t currentHeapSize = 0;
    char initError[8192] = "NOT INITIALIZED";
    Cal::Utils::AddressRange calLibExecAddressRange;
};

GlobalState &getGlobalState() {
    static GlobalState globalState;
    return globalState;
}

// NOT thread-safe
bool tryGrow(size_t minSizeToGrow) {
    auto &globalState = getGlobalState();
    size_t currentHeapSize = globalState.currentHeapSize;

    auto preferredSize = currentHeapSize;
    while (preferredSize - currentHeapSize < minSizeToGrow) {
        preferredSize *= 2;
    }
    if (-1 == Cal::Sys::ftruncate(globalState.shmemFd, preferredSize)) {
        return false;
    }
    auto newSegment = Cal::Sys::mmap(reinterpret_cast<void *>(globalState.asShmemHeapRange.start + currentHeapSize), preferredSize - currentHeapSize,
                                     PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, globalState.shmemFd, currentHeapSize);
    if (MAP_FAILED == newSegment) {
        Cal::Sys::ftruncate(globalState.shmemFd, currentHeapSize);
        return false;
    }

    globalState.currentHeapSize = preferredSize;
    return true;
}

// NOT thread-safe
bool ensureMemoryIsMapped(Cal::Utils::AddressRange range) {
    auto &globalState = getGlobalState();
    auto minimumSizeRequired = range.end - globalState.asShmemHeapRange.start;
    if (minimumSizeRequired > globalState.currentHeapSize) {
        auto sizeToGrow = minimumSizeRequired - globalState.currentHeapSize;
        if (false == tryGrow(sizeToGrow)) {
            return false;
        }
    }
    return true;
}

// thread-safe
void *mallocNoFallback(size_t size) {
    auto &globalState = getGlobalState();
    std::lock_guard<std::mutex> lock{globalState.mutex};
    auto range = globalState.rangeAllocator.allocate(size, naturalAlignment);
    if (nullptr == range.base()) {
        return nullptr;
    }
    if (false == ensureMemoryIsMapped(range)) {
        globalState.rangeAllocator.free(range.base());
        return nullptr;
    }
    return range.base();
}

// thread-safe
void *malloc(size_t size) {
    auto &globalState = getGlobalState();
    if (BOOST_LIKELY(size < globalState.threshold)) {
        return Cal::Client::MallocOverride::Original::malloc(size);
    }
    if (isAllocFromCal(globalState.calLibExecAddressRange)) {
        return Cal::Client::MallocOverride::Original::malloc(size);
    }
    auto ptr = mallocNoFallback(size);
    if (nullptr == ptr) {
        ptr = Cal::Client::MallocOverride::Original::malloc(size);
    }
    return ptr;
}

// thread-safe
void free(void *ptr) {
    auto &globalState = getGlobalState();
    if (BOOST_LIKELY(false == globalState.asShmemHeapRange.contains(ptr))) {
        return Cal::Client::MallocOverride::Original::free(ptr);
    }
    std::lock_guard<std::mutex> lock{globalState.mutex};
    globalState.rangeAllocator.free(ptr);
}

// thread-safe
void *calloc(size_t nitems, size_t size) {
    auto &globalState = getGlobalState();
    size_t totalSize = nitems * size;
    if (BOOST_LIKELY(totalSize < globalState.threshold)) {
        return Cal::Client::MallocOverride::Original::calloc(nitems, size);
    }
    if (isAllocFromCal(globalState.calLibExecAddressRange)) {
        return Cal::Client::MallocOverride::Original::calloc(nitems, size);
    }
    auto ptr = AsCalShmem::mallocNoFallback(totalSize);
    if (nullptr == ptr) {
        return Cal::Client::MallocOverride::Original::calloc(nitems, size);
    }
    memset(ptr, 0, totalSize);
    return ptr;
}

// thread-safe
void *realloc(void *ptr, size_t size) {
    auto &globalState = getGlobalState();
    if (BOOST_LIKELY(false == globalState.asShmemHeapRange.contains(ptr))) {
        return Cal::Client::MallocOverride::Original::realloc(ptr, size);
    }
    std::lock_guard<std::mutex> lock{globalState.mutex};
    size_t oldSize = 0U;
    auto newRange = globalState.rangeAllocator.resizeOrAllocate(ptr, size, naturalAlignment, oldSize);

    if (nullptr == newRange.base()) { // could not allocate VA in shared heap
        auto newPtr = Cal::Client::MallocOverride::Original::malloc(size);
        if (newPtr) {
            memcpy(newPtr, ptr, oldSize);
        } else {
            return nullptr;
        }
        globalState.rangeAllocator.free(ptr);
        return newPtr;
    }

    if (ensureMemoryIsMapped(newRange) == false) { // could map pages for VA in shared heap
        auto newPtr = Cal::Client::MallocOverride::Original::malloc(size);
        if (newPtr) {
            memcpy(newPtr, ptr, oldSize);
        } else {
            return nullptr;
        }
        globalState.rangeAllocator.free(ptr);

        return newPtr;
    }

    if (newRange.base() == ptr) {
        return ptr;
    }

    memcpy(newRange.base(), ptr, oldSize);
    globalState.rangeAllocator.free(ptr);

    return newRange.base();
}
} // namespace AsCalShmem

namespace Init {
bool doInit() {
    auto &globalState = AsCalShmem::getGlobalState();
    bool enabled = Cal::Utils::getCalEnvFlag(calOverrideMallocEnvName);
    if (false == enabled) {
        return false;
    }

    globalState.calLibExecAddressRange = readCalLibExecAddressRange();

    using namespace Cal::Client::MallocOverride;

    globalState.threshold = Cal::Utils::getCalEnvI64(calOverrideMallocThresholdEnvName, globalState.threshold);

    Cal::Ipc::getCalShmemPathBase(globalState.privateMallocShmemPath, sizeof(globalState.privateMallocShmemPath), getpid());
    Cal::Sys::shm_unlink(globalState.privateMallocShmemPath);

    globalState.shmemFd = Cal::Sys::shm_open(globalState.privateMallocShmemPath, O_CREAT | O_EXCL | O_RDWR,
                                             S_IRUSR | S_IWUSR);

    if (-1 == globalState.shmemFd) {
        auto err = errno;
        snprintf(globalState.initError, sizeof(globalState.initError), "Could not open : %s (errno=%d=%s)", globalState.privateMallocShmemPath, err, strerror(err));
        return false;
    }
    if (-1 == Cal::Sys::ftruncate(globalState.shmemFd, globalState.initialCapacity)) {
        Cal::Sys::close(globalState.shmemFd);
        Cal::Sys::shm_unlink(globalState.privateMallocShmemPath);
        snprintf(globalState.initError, sizeof(globalState.initError), "Could not ftruncate : %s to %zu", globalState.privateMallocShmemPath, globalState.initialCapacity);
        return false;
    }

    void *ptr = Cal::Sys::mmap(nullptr, globalState.maxCapacity, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        snprintf(globalState.initError, sizeof(globalState.initError), "Could not reserve memory of size %zu", globalState.maxCapacity);
        Cal::Sys::close(globalState.shmemFd);
        return false;
    }

    void *initialPtr = Cal::Sys::mmap(ptr, globalState.initialCapacity, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, globalState.shmemFd, 0);
    if (initialPtr == MAP_FAILED) {
        snprintf(globalState.initError, sizeof(globalState.initError), "Could not map initial heap of size %zu to %p", globalState.initialCapacity, ptr);
        Cal::Sys::close(globalState.shmemFd);
        Cal::Sys::munmap(ptr, globalState.initialCapacity);
        return false;
    }

    globalState.asShmemHeapRange = Cal::Utils::AddressRange(ptr, globalState.maxCapacity);
    globalState.currentHeapSize = globalState.initialCapacity;
    globalState.rangeAllocator = Cal::Allocators::RangeAllocator(globalState.asShmemHeapRange);
    globalState.initError[0] = '\0';

    Cal::Client::MallocOverride::Overriden::free = AsCalShmem::free;
    Cal::Client::MallocOverride::Overriden::realloc = AsCalShmem::realloc;
    return true;
}

bool doCaptureMallocRetAdddress() {
    Cal::Client::MallocOverride::mallocRetAddress = getRetAddress("malloc");
    if (nullptr == Cal::Client::MallocOverride::mallocRetAddress) {
        std::abort();
    }
    return true;
}

bool doCaptureCallocRetAdddress() {
    Cal::Client::MallocOverride::callocRetAddress = getRetAddress("calloc");
    if (nullptr == Cal::Client::MallocOverride::callocRetAddress) {
        std::abort();
    }
    return true;
}

bool ensureInitialized() {
    static bool initialized = doInit();
    return initialized;
}

bool ensureMallocRetAddressCaptured() {
    static bool captured = doCaptureMallocRetAdddress();
    return captured;
}

bool ensureCallocRetAddressCaptured() {
    static bool captured = doCaptureCallocRetAdddress();
    return captured;
}

void *malloc(size_t size) {
    Cal::Client::MallocOverride::Overriden::malloc = Cal::Client::MallocOverride::Original::malloc;
    ensureMallocRetAddressCaptured();
    ensureInitialized();
    Cal::Client::MallocOverride::Overriden::malloc = Cal::Client::MallocOverride::AsCalShmem::malloc;
    auto p = Overriden::malloc(size);
    return p;
}

void *calloc(size_t nitems, size_t size) {
    Cal::Client::MallocOverride::Overriden::calloc = Cal::Client::MallocOverride::Original::calloc;
    ensureCallocRetAddressCaptured();
    ensureInitialized();
    Cal::Client::MallocOverride::Overriden::calloc = Cal::Client::MallocOverride::AsCalShmem::calloc;
    void *p = Overriden::calloc(nitems, size);
    return p;
}
} // namespace Init

bool doPreInit() {
    Cal::Client::MallocOverride::Original::malloc = getOriginalFunc<MallocFT>("malloc");
    Cal::Client::MallocOverride::Original::free = getOriginalFunc<FreeFT>("free");
    Cal::Client::MallocOverride::Original::calloc = getOriginalFunc<CallocFT>("calloc");
    Cal::Client::MallocOverride::Original::realloc = getOriginalFunc<ReallocFT>("realloc");
    Cal::Client::MallocOverride::Overriden::malloc = Cal::Client::MallocOverride::Init::malloc;
    Cal::Client::MallocOverride::Overriden::free = Cal::Client::MallocOverride::Original::free;
    Cal::Client::MallocOverride::Overriden::calloc = Cal::Client::MallocOverride::Init::calloc;
    Cal::Client::MallocOverride::Overriden::realloc = Cal::Client::MallocOverride::Original::realloc;

    return true;
}

bool ensurePreinitialized() {
    static bool preInitialized = doPreInit();
    return preInitialized;
}

const char *getCalMallocOverrideInitError() {
    return AsCalShmem::getGlobalState().initError;
};

MallocOverrideMode getMode() {
    if (Overriden::malloc == AsCalShmem::malloc) {
        return MallocOverrideMode::CalMallocAsShmem;
    }
    return MallocOverrideMode::Disabled;
}

MallocShmemState readMallocShmemState() {
    MallocShmemState ret = {};
    if (getMode() != MallocOverrideMode::CalMallocAsShmem) {
        return ret;
    }
    auto &globalState = AsCalShmem::getGlobalState();
    std::lock_guard<std::mutex> lock{AsCalShmem::getGlobalState().mutex};
    ret.baseAddress = globalState.asShmemHeapRange.base();
    ret.capacity = globalState.asShmemHeapRange.size();
    ret.size = globalState.currentHeapSize;
    ret.fd = globalState.shmemFd;
    ret.resourcePath = globalState.privateMallocShmemPath;
    return ret;
}

void *malloc(size_t size) {
    ensurePreinitialized();
    auto p = Overriden::malloc(size);
    return p;
}

void free(void *ptr) {
    ensurePreinitialized();
    Overriden::free(ptr);
}

void *calloc(size_t nitems, size_t size) {
    ensurePreinitialized();
    void *p = Overriden::calloc(nitems, size);
    return p;
}

void *realloc(void *ptr, size_t size) {
    ensurePreinitialized();
    void *p = Overriden::realloc(ptr, size);
    return p;
}

} // namespace Client::MallocOverride

} // namespace Cal
