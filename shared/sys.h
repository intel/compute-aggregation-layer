/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <fcntl.h>
#include <fstream>
#include <memory>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

namespace Cal {

namespace Sys {

extern void *(*mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
extern int (*munmap)(void *addr, size_t length);

extern char *(*getenv)(const char *name);
extern int (*setenv)(const char *name, const char *value, int overwrite);

extern std::unique_ptr<std::istream> (*openFileForRead)(const char *filename, std::ios_base::openmode mode);

extern int (*shm_open)(const char *name, int oflag, mode_t mode);
extern int (*shm_unlink)(const char *name);

extern int (*sem_init)(sem_t *sem, int pshared, unsigned int value);
extern int (*sem_destroy)(sem_t *sem);
extern int (*sem_wait)(sem_t *sem);
extern int (*sem_post)(sem_t *sem);

} // namespace Sys

} // namespace Cal