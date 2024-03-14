/*
 * Copyright (C) 2022-2024 Intel Corporation
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
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <unistd.h>

namespace Cal {
namespace Sys {

extern void *(*mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
extern int (*munmap)(void *addr, size_t length);

extern char *(*getenv)(const char *name);
extern int (*setenv)(const char *name, const char *value, int overwrite);
extern int (*unsetenv)(const char *name);

extern std::unique_ptr<std::istream> (*openFileForRead)(const char *filename, std::ios_base::openmode mode);

extern int (*mprotect)(void *addr, size_t len, int prot);

extern int (*shm_open)(const char *name, int oflag, mode_t mode);
extern int (*shm_unlink)(const char *name);

extern int (*sem_init)(sem_t *sem, int pshared, unsigned int value);
extern int (*sem_destroy)(sem_t *sem);
extern int (*sem_wait)(sem_t *sem);
extern int (*sem_post)(sem_t *sem);

extern int (*ftruncate)(int fd, off_t length);
extern int (*close)(int fd);
extern int (*statfs)(const char *path, struct statfs *buf);
extern int (*unlink)(const char *pathname);
extern int (*socket)(int domain, int type, int protocol);
extern int (*listen)(int sockfd, int backlog);
extern int (*accept)(int sockfd, __SOCKADDR_ARG addr, socklen_t *__restrict addrLen);
extern int (*bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern int (*flock)(int fd, int operation);

extern int (*mkdir)(const char *path, mode_t mode);
extern int (*chmod)(const char *pathname, mode_t mode);
extern int (*stat)(const char *path, struct stat *buf);

} // namespace Sys
} // namespace Cal
