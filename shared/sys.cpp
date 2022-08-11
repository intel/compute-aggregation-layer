/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/sys.h"

namespace Cal {

namespace Sys {

void *(*mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset) = ::mmap;
int (*munmap)(void *addr, size_t length) = ::munmap;

char *(*getenv)(const char *name) = ::getenv;

std::unique_ptr<std::istream> (*openFileForRead)(const char *filename, std::ios_base::openmode mode) = +[](const char *filename, std::ios_base::openmode mode) -> std::unique_ptr<std::istream> {
    return std::make_unique<std::ifstream>(filename, mode);
};

int (*shm_open)(const char *name, int oflag, mode_t mode) = ::shm_open;
int (*shm_unlink)(const char *name) = ::shm_unlink;

} // namespace Sys

} // namespace Cal
