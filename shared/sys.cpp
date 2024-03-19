/*
 * Copyright (C) 2022-2024 Intel Corporation
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
int (*setenv)(const char *name, const char *value, int overwrite) = ::setenv;
int (*unsetenv)(const char *name) = ::unsetenv;

std::unique_ptr<std::istream> (*openFileForRead)(const char *filename, std::ios_base::openmode mode) = +[](const char *filename, std::ios_base::openmode mode) -> std::unique_ptr<std::istream> {
    return std::make_unique<std::ifstream>(filename, mode);
};

int (*shm_open)(const char *name, int oflag, mode_t mode) = ::shm_open;
int (*shm_unlink)(const char *name) = ::shm_unlink;

int (*mprotect)(void *addr, size_t len, int prot) = ::mprotect;

int (*sem_init)(sem_t *sem, int pshared, unsigned int value) = ::sem_init;
int (*sem_destroy)(sem_t *sem) = ::sem_destroy;
int (*sem_wait)(sem_t *sem) = ::sem_wait;
int (*sem_post)(sem_t *sem) = ::sem_post;

int (*close)(int fd) = ::close;
int (*ftruncate)(int fd, off_t length) = ::ftruncate;
int (*unlink)(const char *pathname) = ::unlink;
int (*socket)(int domain, int type, int protocol) = ::socket;
int (*listen)(int sockfd, int backlog) = ::listen;
int (*accept)(int sockfd, __SOCKADDR_ARG addr, socklen_t *__restrict addrLen) = ::accept;
int (*bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen) = ::bind;
int (*flock)(int fd, int operation) = ::flock;

int (*mkdir)(const char *path, mode_t mode) = ::mkdir;
int (*chmod)(const char *pathname, mode_t mode) = ::chmod;
int (*stat)(const char *path, struct stat *buf) = ::stat;

} // namespace Sys
} // namespace Cal
