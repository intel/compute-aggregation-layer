/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/sys.h"
#include "shared/utils.h"

#include <functional>
#include <mutex>
#include <optional>
#include <unordered_map>

namespace Cal {

namespace Mocks {

struct MmapTraits {
    void *addr;
    size_t length;
    int prot;
    int flags;
    int fd;
    off_t offset;
};

struct SysCallsContext {
    using Vma = Cal::Utils::PartitionedAddressRange<MmapTraits>;

    SysCallsContext();
    virtual ~SysCallsContext();

    virtual void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
        ++apiConfig.mmap.callCount;
        if (apiConfig.mmap.returnValue) {
            return apiConfig.mmap.returnValue.value();
        }
        if (apiConfig.mmap.impl) {
            return apiConfig.mmap.impl.value()(addr, length, prot, flags, fd, offset);
        }
        return mmapBaseImpl(addr, length, prot, flags, fd, offset);
    }

    virtual int munmap(void *addr, size_t length) {
        ++apiConfig.munmap.callCount;
        if (apiConfig.munmap.returnValue) {
            return apiConfig.munmap.returnValue.value();
        }
        if (apiConfig.munmap.impl) {
            return apiConfig.munmap.impl.value()(addr, length);
        }
        return munmapBaseImpl(addr, length);
    }

    virtual char *getenv(const char *name) {
        ++apiConfig.getenv.callCount;
        if (apiConfig.getenv.returnValue) {
            return apiConfig.getenv.returnValue.value();
        }
        if (apiConfig.getenv.impl) {
            return apiConfig.getenv.impl.value()(name);
        }
        return getenvBaseImpl(name);
    }

    void *mmapBaseImpl(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
        std::lock_guard<std::mutex> lock(mutex);
        auto addrReceived = addr;
        if (nullptr == addrReceived) {
            if (vma.getSubRanges().empty()) {
                addr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096u));
            } else {
                addr = vma.getSubRanges().rbegin()->getBoundingRange().rightBound();
                if (false == vma.getBoundingRange().contains({addr, length})) {
                    return MAP_FAILED;
                }
            }

            vma.insertSubRange(Vma::tagged(Cal::Utils::AddressRange{addr, length},
                                           MmapTraits{addrReceived, length, prot, flags, fd, offset}));
        } else {
            auto intersection = vma.getIntersectedSubRanges({addr, length});
            if (intersection.empty()) {
                vma.insertSubRange(Vma::tagged(Cal::Utils::AddressRange{addr, length},
                                               MmapTraits{addrReceived, length, prot, flags, fd, offset}));
            } else if (flags & MAP_FIXED) {
                vma.destroySubRange({addr, length});
                vma.insertSubRange(Vma::tagged(Cal::Utils::AddressRange{addr, length},
                                               MmapTraits{addrReceived, length, prot, flags, fd, offset}));
            } else if (flags & MAP_FIXED_NOREPLACE) {
                return MAP_FAILED;
            } else {
                addr = vma.getSubRanges().rbegin()->getBoundingRange().rightBound();
                if (false == vma.getBoundingRange().contains({addr, length})) {
                    return MAP_FAILED;
                }
                vma.insertSubRange(Vma::tagged(Cal::Utils::AddressRange{addr, length},
                                               MmapTraits{addrReceived, length, prot, flags, fd, offset}));
            }
        }

        return addr;
    }

    virtual std::unique_ptr<std::istream> openFileForRead(const char *filename, std::ios_base::openmode mode) {
        ++apiConfig.openFileForRead.callCount;
        if (false == apiConfig.openFileForRead.returnValues.empty()) {
            auto it = apiConfig.openFileForRead.returnValues.find(std::string(filename));
            if (apiConfig.openFileForRead.returnValues.end() != it) {
                return std::make_unique<std::istringstream>(it->second);
            }
        }
        if (apiConfig.openFileForRead.impl) {
            return apiConfig.openFileForRead.impl.value()(filename, mode);
        }
        auto badFile = std::make_unique<std::istringstream>();
        badFile->setstate(std::ios_base::iostate::_S_badbit);
        return badFile;
    }

    virtual int shm_open(const char *name, int oflag, mode_t mode) {
        ++apiConfig.shm_open.callCount;
        if (apiConfig.shm_open.returnValue.has_value()) {
            return apiConfig.shm_open.returnValue.value();
        }
        if (apiConfig.shm_open.impl) {
            return apiConfig.shm_open.impl.value()(name, oflag, mode);
        }
        return -1;
    }

    virtual int shm_unlink(const char *name) {
        ++apiConfig.shm_unlink.callCount;
        if (apiConfig.shm_unlink.returnValue.has_value()) {
            return apiConfig.shm_unlink.returnValue.value();
        }
        if (apiConfig.shm_unlink.impl) {
            return apiConfig.shm_unlink.impl.value()(name);
        }
        return -1;
    }

    int munmapBaseImpl(void *addr, size_t length) {
        std::lock_guard<std::mutex> lock(mutex);
        vma.destroySubRange({addr, length});
        return 0;
    }

    char *getenvBaseImpl(const char *name) {
        return nullptr;
    }

    Vma vma = {{static_cast<uintptr_t>(0U), static_cast<uintptr_t>(1ULL << 48)}};
    std::mutex mutex;

    struct {
        struct {
            std::optional<void *> returnValue;
            std::optional<std::function<void *(void *addr, size_t length, int prot, int flags, int fd, off_t offset)>> impl;
            uint64_t callCount = 0U;
        } mmap;

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(void *addr, size_t length)>> impl;
            uint64_t callCount = 0U;
        } munmap;

        struct {
            std::optional<char *> returnValue;
            std::optional<std::function<char *(const char *name)>> impl;
            uint64_t callCount = 0U;
        } getenv;

        struct {
            std::unordered_map<std::string, std::string> returnValues;
            std::optional<std::function<std::unique_ptr<std::istream>(const char *filename, std::ios_base::openmode mode)>> impl;
            uint64_t callCount = 0U;
        } openFileForRead;

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(const char *name, int oflag, mode_t mode)>> impl;
            uint64_t callCount = 0U;
        } shm_open;

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(const char *name)>> impl;
            uint64_t callCount = 0U;
        } shm_unlink;
    } apiConfig;
};

} // namespace Mocks

} // namespace Cal