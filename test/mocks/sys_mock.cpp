/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test/mocks/sys_mock.h"

namespace Cal {

namespace Mocks {

SysCallsContext defaultSysCallsContext;
SysCallsContext *sysCallsContext = &defaultSysCallsContext;

SysCallsContext::SysCallsContext() {
    sysCallsContext = this;
}
SysCallsContext::~SysCallsContext() {
    sysCallsContext = &defaultSysCallsContext;
}

} // namespace Mocks

namespace Sys {

void *(*mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset) = +[](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
    return Cal::Mocks::sysCallsContext->mmap(addr, length, prot, flags, fd, offset);
};

int (*munmap)(void *addr, size_t length) = +[](void *addr, size_t length) -> int {
    return Cal::Mocks::sysCallsContext->munmap(addr, length);
};

char *(*getenv)(const char *name) = +[](const char *name) -> char * {
    return Cal::Mocks::sysCallsContext->getenv(name);
};

std::unique_ptr<std::istream> (*openFileForRead)(const char *filename, std::ios_base::openmode mode) = +[](const char *filename, std::ios_base::openmode mode) -> std::unique_ptr<std::istream> {
    return Cal::Mocks::sysCallsContext->openFileForRead(filename, mode);
};

int (*shm_open)(const char *name, int oflag, mode_t mode) = +[](const char *name, int oflag, mode_t mode) -> int {
    return Cal::Mocks::sysCallsContext->shm_open(name, oflag, mode);
};

int (*shm_unlink)(const char *name) = +[](const char *name) -> int {
    return Cal::Mocks::sysCallsContext->shm_unlink(name);
};

} // namespace Sys

} // namespace Cal