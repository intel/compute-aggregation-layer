/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "malloc_shmem.h"
#include "shared/log.h"
#include "shared/sys.h"

#include <array>
#include <dlfcn.h>
#include <errno.h>
#include <limits.h>
#include <memory>
#include <mutex>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <unordered_map>

namespace Cal {

namespace Ipc {

inline int initializeSemaphore(sem_t *semaphore, unsigned int value = 0U) {
    if (nullptr == semaphore) {
        log<Verbosity::critical>("Invalid semaphore passed for initialization");
        return -1;
    }

    *semaphore = {};
    if (-1 == Cal::Sys::sem_init(semaphore, 1, value)) {
        log<Verbosity::error>("Failed to initialize semaphore %p to %u", semaphore, value);
        return -1;
    }

    log<Verbosity::debug>("Sucesfully initialized semaphore %p to %u", semaphore, value);
    return 0;
}

class Connection {
  public:
    virtual ~Connection() = default;
    virtual int send(const void *data, size_t dataSize) = 0;
    virtual bool sendFd(int fd) = 0;
    virtual int receive(void *data, size_t dataSize) = 0;
    virtual bool receiveFd(int &fd) = 0;
    virtual int peek(void *data, size_t dataSize) = 0;
    virtual int close() = 0;
    virtual bool isAlive() = 0;
    virtual int getId() = 0;
    virtual std::unique_lock<std::mutex> lock() = 0;

    template <typename T>
    bool send(const T &v) {
        return sizeof(v) == send(&v, sizeof(v));
    }

    template <typename T>
    bool receive(T &v) {
        return sizeof(v) == receive(&v, sizeof(v));
    }

    template <typename T>
    bool peek(T &v) {
        return sizeof(v) == peek(&v, sizeof(v));
    }

    static std::string connectionErrnoToError(int err) {
        constexpr int length = 256;
        char buf[length];
        auto errStr = strerror_r(errno, buf, length);

        return std::string(errStr);
    }
};

class ClientConnectionFactory {
  public:
    virtual ~ClientConnectionFactory() = default;
    virtual std::unique_ptr<Connection> connect(const char *path) = 0;
};

class ConnectionListener {
  public:
    virtual ~ConnectionListener() = default;
    virtual int listen(const char *path) = 0;
    virtual std::unique_ptr<Connection> accept() = 0;
    virtual int close() = 0;
    virtual void shutdown() = 0;
};

struct ControlMessageHeader {
    static constexpr uint16_t messageTypeUnknown = 1U;
    static constexpr uint16_t messageTypeNop = 0U;
    static constexpr uint16_t messageTypePing = 2U;
    static constexpr uint16_t messageTypeRequest = 3U;
    static constexpr uint16_t messageTypeStop = 4U;
    uint16_t type = messageTypeUnknown;
    uint16_t subtype = messageTypeUnknown;
};
static_assert(std::is_standard_layout<ControlMessageHeader>::value);

class Socket : public Connection {
  public:
    Socket(int socketFd) : socketFd(socketFd) {
    }

    ~Socket() override {
        this->Socket::close();
    }

    int send(const void *data, size_t dataSize) override {
        auto ret = write(socketFd, data, dataSize);
        if (static_cast<int64_t>(dataSize) != ret) {
            log<Verbosity::debug>("Failed to send data to socket");
        }
        return ret;
    }

    bool sendFd(int fd) override {
        // Prepare dummy IO vectors.
        // In spite of focusing on ancillary data to send FD, we cannot use empty IOV.
        char dummyData{0};
        std::array<struct iovec, 1> iov = {};
        iov[0].iov_base = &dummyData;
        iov[0].iov_len = sizeof(dummyData);

        // Prepare storage for control message's content and ancillary data.
        constexpr auto fdSize = sizeof(fd);
        constexpr auto paddedControlMessageSize = CMSG_SPACE(fdSize);
        constexpr auto actualControlMessageSize = CMSG_LEN(fdSize);
        std::array<char, paddedControlMessageSize> controlMessageStorage = {};

        // Prepare storage and fill main message.
        struct msghdr message;
        memset(&message, 0, sizeof(message));
        message.msg_control = controlMessageStorage.data();
        message.msg_controllen = paddedControlMessageSize;
        message.msg_iov = iov.data();
        message.msg_iovlen = iov.size();

        // Fill control message with ancillary data.
        auto *controlMessage = CMSG_FIRSTHDR(&message);
        controlMessage->cmsg_len = actualControlMessageSize;
        controlMessage->cmsg_level = SOL_SOCKET;
        controlMessage->cmsg_type = SCM_RIGHTS;
        std::memcpy(CMSG_DATA(controlMessage), &fd, fdSize);

        // Send message and verify results.
        constexpr int flags{0};
        const auto ret = sendmsg(socketFd, &message, flags);
        if (ret == -1) {
            log<Verbosity::error>("Could not send file descriptor! Errno is %d", static_cast<int>(errno));
            return false;
        }

        return true;
    }

    int peek(void *buffer, size_t bufferSize) override {
        auto ret = recv(socketFd, buffer, bufferSize, MSG_PEEK);
        if (ret == -1) {
            log<Verbosity::debug>("Failed to peek from socket");
        }
        return ret;
    }

    int receive(void *buffer, size_t bufferSize) override {
        auto ret = recv(socketFd, buffer, bufferSize, 0);
        if (ret == -1) {
            log<Verbosity::debug>("Failed to read from socket");
        }
        return ret;
    }

    bool receiveFd(int &fd) override {
        // Prepare dummy IO vectors.
        // In spite of focusing on ancillary data to receive FD, we cannot use empty IOV.
        char dummyData{0};
        std::array<struct iovec, 1> iov = {};
        iov[0].iov_base = &dummyData;
        iov[0].iov_len = sizeof(dummyData);

        // Prepare storage for control message's content and ancillary data.
        constexpr auto fdSize = sizeof(fd);
        constexpr auto paddedControlMessageSize = CMSG_SPACE(fdSize);
        constexpr auto actualControlMessageSize = CMSG_LEN(fdSize);
        std::array<char, paddedControlMessageSize> controlMessageStorage = {};

        // Prepare storage and fill main message.
        struct msghdr message;
        memset(&message, 0, sizeof(message));
        message.msg_control = controlMessageStorage.data();
        message.msg_controllen = paddedControlMessageSize;
        message.msg_iov = iov.data();
        message.msg_iovlen = iov.size();

        // Receive message and verify results.
        constexpr int flags{0};
        const auto ret = recvmsg(socketFd, &message, flags);
        if (ret == -1) {
            log<Verbosity::error>("Could not receive file descriptor! Errno is %d", static_cast<int>(errno));
            return false;
        }

        // Validate received control message and assign file descriptor.
        auto *controlMessage = CMSG_FIRSTHDR(&message);
        if (controlMessage->cmsg_len == actualControlMessageSize && controlMessage->cmsg_level == SOL_SOCKET && controlMessage->cmsg_type == SCM_RIGHTS) {
            std::memcpy(&fd, CMSG_DATA(controlMessage), fdSize);
            return true;
        }

        log<Verbosity::error>("Received message does not contain valid file descriptor!");
        return false;
    }

    int close() override {
        if (-1 != this->socketFd) {
            log<Verbosity::debug>("Closing socket %d", socket);
            if (0 != ::close(this->socketFd)) {
                log<Verbosity::error>("Failed to close socket %d", socket);
                return -1;
            } else {
                this->socketFd = -1;
            }
        }
        return 0;
    }

    bool isAlive() override {
        ControlMessageHeader pingMessage{ControlMessageHeader::messageTypePing};
        if ((sizeof(pingMessage) != this->send(&pingMessage, sizeof(pingMessage)))) {
            log<Verbosity::debug>("Detected that socket is dead - can't send ping request");
            return false;
        }
        pingMessage = {};
        if ((sizeof(pingMessage) != this->receive(&pingMessage, sizeof(pingMessage))) || (ControlMessageHeader::messageTypePing != pingMessage.type)) {
            log<Verbosity::debug>("Detected that socket is dead - didn't receive ping response");
            return false;
        }
        return true;
    }

    int getId() override {
        return socketFd;
    }

    std::unique_lock<std::mutex> lock() override {
        return std::unique_lock<std::mutex>(criticalSection);
    }

  protected:
    int socketFd;
    std::mutex criticalSection;
};

class NamedSocketClientConnectionFactory : public ClientConnectionFactory {
  public:
    NamedSocketClientConnectionFactory() = default;

    std::unique_ptr<Connection> connect(const char *path) override {
        log<Verbosity::debug>("Creating socket as client");
        auto socketFd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
        if (-1 == socketFd) {
            log<Verbosity::error>("Failed to create socket");
            return nullptr;
        }

        sockaddr_un socketAddress = {};
        socketAddress.sun_family = AF_UNIX;
        strncpy(socketAddress.sun_path, path, sizeof(socketAddress.sun_path));
        socketAddress.sun_path[sizeof(socketAddress.sun_path) - 1] = '\0';

        log<Verbosity::debug>("Connecting to service through socket at address (family : AF_UNIX) : %s", socketAddress.sun_path);
        if (0 != ::connect(socketFd, reinterpret_cast<const sockaddr *>(&socketAddress), sizeof(socketAddress))) {
            log<Verbosity::debug>("Failed to connect to service through socket at address (family : AF_UNIX) : %s - error : %s", socketAddress.sun_path, Connection::connectionErrnoToError(errno).c_str());
            ::close(socketFd);
            return nullptr;
        }

        log<Verbosity::debug>("Connected to service through socket at address (family : AF_UNIX) : %s", socketAddress.sun_path);
        return std::make_unique<Socket>(socketFd);
    }
};

class NamedSocketConnectionListener : public ConnectionListener {
  public:
    ~NamedSocketConnectionListener() override {
        this->NamedSocketConnectionListener::close();
    }

    int listen(const char *path) override {
        this->path = path;
        if (this->listening) {
            log<Verbosity::debug>("Attempted to reuse active listener socket");
            return 0;
        }
        log<Verbosity::debug>("Creating listener socket as server");
        log<Verbosity::debug>("Unlinking stale socket file (if exists) : %s", path);
        unlink(path);

        log<Verbosity::debug>("Creating listener socket");
        this->listenerSocketFd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
        if (this->listenerSocketFd == -1) {
            log<Verbosity::error>("Failed to create listener socket");
            return -1;
        }

        sockaddr_un socketAddress = {};
        socketAddress.sun_family = AF_UNIX;
        strncpy(socketAddress.sun_path, path, sizeof(socketAddress.sun_path));
        socketAddress.sun_path[sizeof(socketAddress.sun_path) - 1] = '\0';

        log<Verbosity::debug>("Binding socket to address (family : AF_UNIX) : %s", socketAddress.sun_path);
        if (0 != bind(this->listenerSocketFd, reinterpret_cast<const sockaddr *>(&socketAddress), sizeof(socketAddress))) {
            log<Verbosity::error>("Failed to bind socket to address (family : AF_UNIX) : %s - error : %s", socketAddress.sun_path, Connection::connectionErrnoToError(errno).c_str());
            this->close();
            return -1;
        }

        log<Verbosity::debug>("Listening on socket %s", socketAddress.sun_path);
        if (0 != ::listen(this->listenerSocketFd, 4096)) {
            log<Verbosity::error>("Failed while starting to listen on socket (family : AF_UNIX) : %s - error : %s", socketAddress.sun_path, Connection::connectionErrnoToError(errno).c_str());
            this->close();
            return -1;
        }

        this->listening = true;
        return 0;
    }

    std::unique_ptr<Connection> accept() override {
        if (false == this->listening) {
            log<Verbosity::critical>("Attempted to accept on uninitialized listener socket");
            return nullptr;
        }

        int socketFd = ::accept(listenerSocketFd, NULL, NULL);
        if (socketFd == -1) {
            if (this->listening) {
                log<Verbosity::error>("Failed to accept on socket");
            }
            return nullptr;
        }

        return std::make_unique<Socket>(socketFd);
    }

    void shutdown() override {
        if (-1 == this->listenerSocketFd) {
            return;
        }
        this->listening = false;
        ::shutdown(this->listenerSocketFd, SHUT_RDWR);
    }

    int close() override {
        if (-1 == this->listenerSocketFd) {
            return 0;
        }
        log<Verbosity::debug>("Closing listener socket %s", path.c_str());
        if (0 != ::close(this->listenerSocketFd)) {
            log<Verbosity::error>("Failed to close listener socket");
            return -1;
        }

        log<Verbosity::debug>("Unlinking socket file : %s", path.c_str());
        unlink(path.c_str());
        this->listenerSocketFd = -1;
        return 0;
    }

  protected:
    int listenerSocketFd = -1;
    bool listening = false;
    std::string path;
};

class MallocShmemZeroCopyManager {
  public:
    class MallocShmemZeroCopyImportHandler {
      public:
        MallocShmemZeroCopyImportHandler(MallocShmemZeroCopyManager *parent, malloc_shmem_imported_address_space_handle_t src)
            : parent(parent), src(src) {
        }

        ~MallocShmemZeroCopyImportHandler() {
            parent->libraryDispatchTable.releaseImportedAddressSpace(src);
        }

        void *translateZeroCopyMallocShmemPtr(void *ptr, size_t size) {
            if (nullptr == ptr) {
                return nullptr;
            }
            if (0 == size) {
                log<Verbosity::error>("Attempted to translate zero-copy malloc shmem of 0 size");
                return nullptr;
            }
            std::lock_guard<std::mutex> lock(importedPointersMap.mutex);
            void *mapped = nullptr;
            {
                auto alreadyImported = importedPointersMap.clientToServiceMap.find(ptr);
                if (importedPointersMap.clientToServiceMap.end() != alreadyImported) {
                    mapped = const_cast<void *>(alreadyImported->second);
                    log<Verbosity::bloat>("Reusing mapped imported ptr : %p (size : %zuB) as %p", ptr, size, mapped);
                }
            }
            if (nullptr == mapped) {
                mapped = this->map(ptr, size);
                importedPointersMap.clientToServiceMap[ptr] = mapped;
                importedPointersMap.serviceToClientMap[mapped] = ptr;
                log<Verbosity::debug>("Import client malloc ptr : %p (size : %zuB) as %p", ptr, size, mapped);
                log<Verbosity::debug>("Import client malloc ((int*)mapped)[0] : %d", ((int *)mapped)[0]);
            }
            return mapped;
        }

        bool isImportedPointer(const void *ptr) {
            std::lock_guard<std::mutex> lock(importedPointersMap.mutex);
            return importedPointersMap.serviceToClientMap.end() != importedPointersMap.serviceToClientMap.find(ptr);
        }

        const void *translateZeroCopyMallocShmemPtr(const void *ptr, size_t size) {
            return translateZeroCopyMallocShmemPtr(const_cast<void *>(ptr), size);
        }

        template <typename T>
        T *translateZeroCopyMallocShmemPtr(T *ptr, size_t size) {
            return translateZeroCopyMallocShmemPtr(reinterpret_cast<void *>(ptr), size);
        }

        template <typename T>
        const T *translateZeroCopyMallocShmemPtr(const T *ptr, size_t size) {
            return translateZeroCopyMallocShmemPtr(reinterpret_cast<const void *>(ptr), size);
        }

      protected:
        MallocShmemZeroCopyManager *parent = nullptr;
        malloc_shmem_imported_address_space_handle_t src = -1;

        struct ImportedPointersMap {
            std::mutex mutex;
            std::unordered_map<const void *, const void *> clientToServiceMap;
            std::unordered_map<const void *, const void *> serviceToClientMap;
        } importedPointersMap;

        void *map(uintptr_t offset, size_t length) {
            auto ret = parent->libraryDispatchTable.mapImportedVaRange(src, offset, length);
            return ret;
        }

        void *map(void *srcPtr, size_t length) {
            auto ret = parent->libraryDispatchTable.mapImportedVaRange(src, reinterpret_cast<uintptr_t>(srcPtr), length);
            return ret;
        }

        void unmap(void *ptr) {
            parent->libraryDispatchTable.unmapImportedVaRange(ptr);
        }
    };

    MallocShmemZeroCopyManager() {
    }

    ~MallocShmemZeroCopyManager() {
        if (false == isAvailable()) {
            return;
        }
        dlclose(library);
        libraryDispatchTable.shutdown();
    }

    void loadLibrary() {
        std::lock_guard<std::mutex> lock(mutex);
        if (isAvailable()) {
            return;
        }
        librarySoName = MALLOC_SHMEM_LIBNAME;
        library = dlopen(librarySoName.c_str(), RTLD_NOW);
        if (false == isAvailable()) {
            log<Verbosity::info>("Library %s for zero-copy sharing of user-allocated memory is not available", librarySoName.c_str());
            log<Verbosity::performance>("Library %s for zero-copy sharing of user-allocated memory is not available", librarySoName.c_str());
            return;
        }
        char path[PATH_MAX];
        dlinfo(library, RTLD_DI_ORIGIN, path);
        librarySoPath.assign(path);
        librarySoPath += "/" + librarySoName;
        if (false == mallocShmemLoadDispatchTable(&libraryDispatchTable, library, dlsym)) {
            log<Verbosity::error>("Failed to load dispatch table of %s", librarySoPath.c_str());
            dlclose(library);
            library = nullptr;
            return;
        }
        if (false == libraryDispatchTable.init()) {
            log<Verbosity::error>("Failed to initialize %s. May require root privelege.", librarySoPath.c_str());
            dlclose(library);
            library = nullptr;
            return;
        }
        log<Verbosity::info>("Library %s was loaded for zero-copy sharing of user-allocated memory", librarySoPath.c_str());
        log<Verbosity::performance>("Library %s was loaded for zero-copy sharing of user-allocated memory", librarySoPath.c_str());
    }

    void loadLibrary(const std::string &librarySoPath) {
        std::lock_guard<std::mutex> lock(mutex);
        if (isAvailable()) {
            return;
        }
        library = dlopen(librarySoPath.c_str(), RTLD_NOW);
        if (false == isAvailable()) {
            log<Verbosity::debug>("Failed to load %s library for zero-copy sharing of user-allocated memory", librarySoPath.c_str());
            return;
        }
        this->librarySoPath = librarySoPath;
        if (false == mallocShmemLoadDispatchTable(&libraryDispatchTable, library, dlsym)) {
            if (librarySoPath.empty()) { // self-load
                dlclose(library);
                library = nullptr;
                return;
            }
            log<Verbosity::error>("Failed to load dispatch table of %s", librarySoPath.c_str());
            dlclose(library);
            library = nullptr;
            return;
        }
        if (false == libraryDispatchTable.init()) {
            log<Verbosity::error>("Failed to initialize %s. May require root privelege.", librarySoPath.c_str());
            dlclose(library);
            library = nullptr;
            return;
        }
        log<Verbosity::info>("Library %s was loaded for zero-copy sharing of user-allocated memory", librarySoPath.c_str());
        log<Verbosity::performance>("Library %s was loaded for zero-copy sharing of user-allocated memory", librarySoPath.c_str());
    }

    bool isAvailable() const {
        return nullptr != this->library;
    }

    const std::string &getLibrarySoName() const {
        return librarySoName;
    }

    const std::string &getLibrarySoPath() const {
        return librarySoPath;
    }

    bool exportUserAddressSpace() {
        std::lock_guard<std::mutex> lock(mutex);
        if (userAddresSpace > 0) {
            return true;
        }
        if (false == isAvailable()) {
            log<Verbosity::error>("Tried to export user user address space even though malloc_shmem library is not available");
            return false;
        }
        userAddresSpace = libraryDispatchTable.exportWholeUserAddressSpace();
        if (userAddresSpace <= 0) {
            log<Verbosity::error>("Failed to export user address space");
            return false;
        }
        log<Verbosity::debug>("Exported user address space as : %ld", userAddresSpace);
        return true;
    }

    std::unique_ptr<MallocShmemZeroCopyImportHandler> importUserAddressSpace(malloc_shmem_exported_address_space_handle_t src) {
        std::lock_guard<std::mutex> lock(mutex);
        if (false == isAvailable()) {
            log<Verbosity::error>("Tried to import user user address space %ld even though malloc_shmem library is not available", src);
            return nullptr;
        }
        auto importedAddressSpace = libraryDispatchTable.importAddressSpace(src);
        if (importedAddressSpace <= 0) {
            log<Verbosity::error>("Failed to import user user address space %ld", src);
            return nullptr;
        }
        log<Verbosity::debug>("Succesfully imported user address space %ld as : %ld", src, importedAddressSpace);
        return std::make_unique<MallocShmemZeroCopyImportHandler>(this, importedAddressSpace);
    }

    malloc_shmem_exported_address_space_handle_t getExportedUserAddressSpace() const {
        return userAddresSpace;
    }

  protected:
    std::mutex mutex;
    void *library = nullptr;
    std::string librarySoName;
    std::string librarySoPath;
    malloc_shmem_dispatch_table libraryDispatchTable;
    malloc_shmem_exported_address_space_handle_t userAddresSpace = -1;
};

} // namespace Ipc

} // namespace Cal
