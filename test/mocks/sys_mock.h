/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/sys.h"
#include "shared/utils.h"

#include <cstring>
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

struct PSemaphore {
    Utils::CountingSemaphore cs;
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

    virtual int sem_init(sem_t *sem, int pshared, unsigned int value) {
        ++apiConfig.sem_init.callCount;
        if (apiConfig.sem_init.returnValue) {
            return apiConfig.sem_init.returnValue.value();
        }
        if (apiConfig.sem_init.impl) {
            return apiConfig.sem_init.impl.value()(sem, pshared, value);
        }
        return sem_initBaseImpl(sem, pshared, value);
    };

    virtual int sem_destroy(sem_t *sem) {
        ++apiConfig.sem_destroy.callCount;
        if (apiConfig.sem_destroy.returnValue) {
            return apiConfig.sem_destroy.returnValue.value();
        }
        if (apiConfig.sem_destroy.impl) {
            return apiConfig.sem_destroy.impl.value()(sem);
        }
        return sem_destroyBaseImpl(sem);
    }

    virtual int sem_wait(sem_t *sem) {
        ++apiConfig.sem_wait.callCount;
        if (apiConfig.sem_wait.returnValue) {
            return apiConfig.sem_wait.returnValue.value();
        }
        if (apiConfig.sem_wait.impl) {
            return apiConfig.sem_wait.impl.value()(sem);
        }
        return sem_waitBaseImpl(sem);
    };

    virtual int sem_post(sem_t *sem) {
        ++apiConfig.sem_post.callCount;
        if (apiConfig.sem_post.returnValue) {
            return apiConfig.sem_post.returnValue.value();
        }
        if (apiConfig.sem_post.impl) {
            return apiConfig.sem_post.impl.value()(sem);
        }
        return sem_postBaseImpl(sem);
    };

    virtual int setenv(const char *name, const char *value, int overwrite) {
        ++apiConfig.setenv.callCount;
        if (apiConfig.setenv.returnValue) {
            return apiConfig.setenv.returnValue.value();
        }

        return setenvBaseImpl(name, value, overwrite);
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

    int munmapBaseImpl(void *addr, size_t length) {
        std::lock_guard<std::mutex> lock(mutex);
        vma.destroySubRange({addr, length});
        return 0;
    }

    char *getenvBaseImpl(const char *name) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = envVariables.find(name);
        return (it != envVariables.end()) ? it->second.data() : nullptr;
    }

    int setenvBaseImpl(const char *name, const char *value, int overwrite) {
        if ((nullptr == name) || ('\0' == name[0]) || (nullptr != strstr(name, "="))) {
            return EINVAL;
        }
        std::lock_guard<std::mutex> lock(mutex);
        auto prev = envVariables.find(name);
        if ((prev != envVariables.end()) && (0 == overwrite)) {
            return 0;
        }
        envVariables[name] = value;
        return 0;
    }

    int sem_initBaseImpl(sem_t *sem, int pshared, unsigned int value) {
        auto representation = std::make_unique<PSemaphore>();
        representation->cs.reset(value);
        std::lock_guard<std::mutex> lock(mutex);
        semaphores[sem] = std::move(representation);
        return 0;
    }

    int sem_destroyBaseImpl(sem_t *sem) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = semaphores.find(sem);
        if (semaphores.end() == it) {
            return -1;
        }
        semaphores.erase(it);
        return 0;
    }

    int sem_waitBaseImpl(sem_t *sem) {
        PSemaphore *representation = nullptr;
        {
            std::lock_guard<std::mutex> lock(mutex);
            auto it = semaphores.find(sem);
            if (semaphores.end() == it) {
                return -1;
            }
            representation = it->second.get();
        }
        representation->cs.wait();
        return 0;
    }

    int sem_postBaseImpl(sem_t *sem) {
        PSemaphore *representation = nullptr;
        {
            std::lock_guard<std::mutex> lock(mutex);
            auto it = semaphores.find(sem);
            if (semaphores.end() == it) {
                return -1;
            }
            representation = it->second.get();
        }
        representation->cs.signal(1);
        return 0;
    }

    Vma vma = {{static_cast<uintptr_t>(0U), static_cast<uintptr_t>(1ULL << 48)}};
    std::unordered_map<sem_t *, std::unique_ptr<PSemaphore>> semaphores;
    std::unordered_map<std::string, std::string> envVariables;
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
            std::optional<int> returnValue;
            std::optional<std::function<int(const char *name, const char *value, int overwrite)>> impl;
            uint64_t callCount = 0U;
        } setenv;

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

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(sem_t *sem, int pshared, unsigned int value)>> impl;
            uint64_t callCount = 0U;
        } sem_init;

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(sem_t *sem)>> impl;
            uint64_t callCount = 0U;
        } sem_destroy;

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(sem_t *sem)>> impl;
            uint64_t callCount = 0U;
        } sem_wait;

        struct {
            std::optional<int> returnValue;
            std::optional<std::function<int(sem_t *sem)>> impl;
            uint64_t callCount = 0U;
        } sem_post;
    } apiConfig;
};

} // namespace Mocks

} // namespace Cal
