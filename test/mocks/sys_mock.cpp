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

int (*setenv)(const char *name, const char *value, int overwrite) = +[](const char *name, const char *value, int overwrite) -> int {
    return Cal::Mocks::sysCallsContext->setenv(name, value, overwrite);
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

int (*sem_init)(sem_t *sem, int pshared, unsigned int value) = +[](sem_t *sem, int pshared, unsigned int value) -> int {
    return Cal::Mocks::sysCallsContext->sem_init(sem, pshared, value);
};

int (*sem_destroy)(sem_t *sem) = +[](sem_t *sem) -> int {
    return Cal::Mocks::sysCallsContext->sem_destroy(sem);
};

int (*sem_wait)(sem_t *sem) = +[](sem_t *sem) -> int {
    return Cal::Mocks::sysCallsContext->sem_wait(sem);
};

int (*sem_post)(sem_t *sem) = +[](sem_t *sem) -> int {
    return Cal::Mocks::sysCallsContext->sem_post(sem);
};

} // namespace Sys

} // namespace Cal