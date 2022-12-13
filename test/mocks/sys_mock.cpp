/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test/mocks/sys_mock.h"

namespace Cal {
namespace Mocks {

static SysCallsContext &getDefaultSysCallsContext() {
    static SysCallsContext defaultSysCallsContext;
    return defaultSysCallsContext;
}

static SysCallsContext *&getSysCallsContextPtr() {
    static SysCallsContext *sysCallsContext{};
    return sysCallsContext;
}

static SysCallsContext *getSysCallsContext() {
    auto &context = getSysCallsContextPtr();
    if (!context) {
        context = &getDefaultSysCallsContext();
    }

    return context;
}

SysCallsContext::SysCallsContext()
    : fds(8192) {
    fds.allocate(); // reserve 0
    getSysCallsContextPtr() = this;
}
SysCallsContext::~SysCallsContext() {
    getSysCallsContextPtr() = &getDefaultSysCallsContext();
}

} // namespace Mocks

namespace Sys {

void *(*mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset) = +[](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
    return Cal::Mocks::getSysCallsContext()->mmap(addr, length, prot, flags, fd, offset);
};

int (*munmap)(void *addr, size_t length) = +[](void *addr, size_t length) -> int {
    return Cal::Mocks::getSysCallsContext()->munmap(addr, length);
};

char *(*getenv)(const char *name) = +[](const char *name) -> char * {
    return Cal::Mocks::getSysCallsContext()->getenv(name);
};

int (*setenv)(const char *name, const char *value, int overwrite) = +[](const char *name, const char *value, int overwrite) -> int {
    return Cal::Mocks::getSysCallsContext()->setenv(name, value, overwrite);
};

int (*unsetenv)(const char *name) = +[](const char *name) -> int {
    return Cal::Mocks::getSysCallsContext()->unsetenv(name);
};

std::unique_ptr<std::istream> (*openFileForRead)(const char *filename, std::ios_base::openmode mode) = +[](const char *filename, std::ios_base::openmode mode) -> std::unique_ptr<std::istream> {
    return Cal::Mocks::getSysCallsContext()->openFileForRead(filename, mode);
};

int (*shm_open)(const char *name, int oflag, mode_t mode) = +[](const char *name, int oflag, mode_t mode) -> int {
    return Cal::Mocks::getSysCallsContext()->shm_open(name, oflag, mode);
};

int (*shm_unlink)(const char *name) = +[](const char *name) -> int {
    return Cal::Mocks::getSysCallsContext()->shm_unlink(name);
};

int (*sem_init)(sem_t *sem, int pshared, unsigned int value) = +[](sem_t *sem, int pshared, unsigned int value) -> int {
    return Cal::Mocks::getSysCallsContext()->sem_init(sem, pshared, value);
};

int (*sem_destroy)(sem_t *sem) = +[](sem_t *sem) -> int {
    return Cal::Mocks::getSysCallsContext()->sem_destroy(sem);
};

int (*sem_wait)(sem_t *sem) = +[](sem_t *sem) -> int {
    return Cal::Mocks::getSysCallsContext()->sem_wait(sem);
};

int (*sem_post)(sem_t *sem) = +[](sem_t *sem) -> int {
    return Cal::Mocks::getSysCallsContext()->sem_post(sem);
};

int (*close)(int fd) = +[](int fd) -> int {
    return Cal::Mocks::getSysCallsContext()->close(fd);
};

int (*ftruncate)(int fd, off_t length) = +[](int fd, off_t length) -> int {
    return Cal::Mocks::getSysCallsContext()->ftruncate(fd, length);
};

int (*mprotect)(void *addr, size_t len, int prot) = +[](void *addr, size_t len, int prot) -> int {
    return Cal::Mocks::getSysCallsContext()->mprotect(addr, len, prot);
};

} // namespace Sys
} // namespace Cal
