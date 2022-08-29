/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/control_messages.h"
#include "shared/ipc.h"
#include "shared/log.h"
#include "shared/rpc_message.h"
#include "shared/shmem.h"
#include "shared/utils.h"

#include <atomic>
#include <inttypes.h>
#include <mutex>
#include <thread>
#include <type_traits>

namespace Cal {

namespace Rpc {

// ringbuffer_base            head                   tail           ringbuffer_end
//          | processed commands | unprocessed commands | unused space |
class RingBuffer {
  public:
    struct CommandPacket {
        void *hostAccessible;
        uint64_t size;
        uint64_t ringOffset;
    };

    struct Layout {
        using OffsetWithinRing = int64_t;
        OffsetWithinRing head = -1;
        OffsetWithinRing tail = -1;
        OffsetWithinRing iteration = -1;
        OffsetWithinRing semClient = -1;
        OffsetWithinRing semServer = -1;
        OffsetWithinRing ringStart = -1;

        bool isValid() const {
            bool valid = true;
            valid = valid && (head != -1);
            valid = valid && (tail != -1);
            valid = valid && (iteration != -1);
            valid = valid && (semClient != -1);
            valid = valid && (semServer != -1);
            valid = valid && (ringStart != -1);
            if (false == valid) {
                log<Verbosity::debug>("RPC ring buffer layout is invalid (head : %" PRId64 ", tail : %" PRId64
                                      ", iteration : %" PRId64 ", semClient : %" PRId64 ", semServer : %" PRId64 ", ringStart : %" PRId64 ")");
            }
            return valid;
        }
    };

    virtual CommandPacket getSpace(size_t size) = 0;
    virtual void push(CommandPacket commands) = 0;
    virtual void pop(size_t size) = 0;
    virtual std::unique_lock<std::mutex> lock() = 0;
    virtual Layout getLayout() const = 0;

    virtual uint64_t peekIteration() const = 0;
    virtual uint64_t peekHead() const = 0;
    virtual uint64_t peekTail() const = 0;
    virtual void *getRingRaw() const = 0;

    virtual ~RingBuffer() = default;
};

class ShmemRingBuffer : public RingBuffer {
  public:
    RingBuffer::CommandPacket getSpace(size_t size) override {
        if (*tail >= *head) {
            if (shmemSize - *tail > size) {
                auto addr = Cal::Utils::moveByBytes(this->shmem, *tail);
                return CommandPacket{addr, size, *tail};
            } else {
                log<Verbosity::critical>("Unimplemented ring full");
                exit(1);
            }
        } else {
            log<Verbosity::critical>("Unimplemented ring looped");
            exit(1);
        }
        return {};
    }

    void push(RingBuffer::CommandPacket commands) override {
        __sync_fetch_and_add(tail, commands.size);
    }

    void pop(size_t size) override {
        __sync_fetch_and_add(head, size);
    }

    std::unique_lock<std::mutex> lock() override {
        return std::unique_lock<std::mutex>(criticalSection);
    }

    Layout getLayout() const override {
        Layout ret = {};
        ret.head = head ? Cal::Utils::byteDistanceAbs(shmem, head) : -1;
        ret.tail = tail ? Cal::Utils::byteDistanceAbs(shmem, tail) : -1;
        ret.iteration = iteration ? Cal::Utils::byteDistanceAbs(shmem, iteration) : -1;
        ret.semClient = semClient ? Cal::Utils::byteDistanceAbs(shmem, semClient) : -1;
        ret.semServer = semServer ? Cal::Utils::byteDistanceAbs(shmem, semServer) : -1;
        ret.ringStart = ringStart;
        return ret;
    }

    bool partition(void *shmem, size_t shmemSize, bool init) {
        //  shmem                                                                shmem + alignUp(sizeof(RH), cacheline)       shmem + shmemSize
        //    |                                                                                  |                                |
        //    | <-------------------------RH = RING HEADER-------------------------------------->| <-------- RING --------------->|
        //    | uint64_t head | uint64_t tail | uint64_t iteration | sem_t client | sem_t server | MESSAGE1 MESSAGE2 ... MESSAGEN |
        using namespace Cal::Utils;
        if (false == isAlignedPow2<Cal::Utils::pageSize4KB>(shmem)) {
            log<Verbosity::critical>("Tried to use page-unaligned shmem as RPC ring buffer : %p (rest : %zu)",
                                     shmem, reinterpret_cast<uintptr_t>(shmem) % Cal::Utils::pageSize4KB);
            return false;
        }
        if (false == isAlignedPow2<Cal::Utils::pageSize4KB>(shmemSize)) {
            log<Verbosity::critical>("Tried to use page-unaligned shmem size as RPC ring buffer");
            return false;
        }
        if (shmemSize < Cal::Utils::pageSize4KB) {
            log<Verbosity::critical>("Tried to use shmem smaller than 1 page for RPC ring buffer (size : %zu)", shmemSize);
            return false;
        }
        head = reinterpret_cast<volatile uint64_t *>(shmem);
        tail = head + 1;
        iteration = tail + 1;
        semClient = const_cast<sem_t *>(reinterpret_cast<volatile sem_t *>(alignUp<sizeof(sem_t)>(iteration + 1)));
        semServer = semClient + 1;
        ringStart = alignUpPow2<cachelineSize>(byteDistanceAbs(shmem, semServer + 1));
        this->shmem = shmem;
        this->shmemSize = shmemSize;
        if (init) {
            return initContents();
        } else {
            return false;
        }
    }

    bool partition(void *shmem, size_t shmemSize, const Layout &layout, bool init) {
        using namespace Cal::Utils;
        if (layout.isValid() == false) {
            log<Verbosity::critical>("Tried to partition RPC ring buffer using invalid layout");
            return false;
        }
        head = reinterpret_cast<volatile uint64_t *>(moveByBytes(shmem, layout.head));
        tail = reinterpret_cast<volatile uint64_t *>(moveByBytes(shmem, layout.tail));
        iteration = reinterpret_cast<volatile uint64_t *>(moveByBytes(shmem, layout.iteration));
        semClient = reinterpret_cast<sem_t *>(moveByBytes(shmem, layout.semClient));
        semServer = reinterpret_cast<sem_t *>(moveByBytes(shmem, layout.semServer));
        ringStart = layout.ringStart;
        this->shmem = shmem;
        this->shmemSize = shmemSize;
        if (init) {
            return initContents();
        } else {
            return true;
        }
    }

    uint64_t peekIteration() const override {
        return *iteration;
    }

    uint64_t peekHead() const override {
        return *head;
    }

    uint64_t peekTail() const override {
        return *tail;
    }

    void *getRingRaw() const override {
        return shmem;
    }

  protected:
    bool initContents() {
        *head = ringStart;
        *tail = *head;
        *iteration = 0;
        if (0 != Cal::Ipc::initializeSemaphore(semClient)) {
            log<Verbosity::critical>("Failed to initialize client semaphore in RPC ring buffer shmem");
            return false;
        }
        if (0 != Cal::Ipc::initializeSemaphore(semServer)) {
            log<Verbosity::critical>("Failed to initialize server semaphore in RPC ring buffer  shmem");
            return false;
        }
        return true;
    }

    void *shmem = nullptr;
    size_t shmemSize = 0U;
    size_t ringStart = 0U;
    volatile uint64_t *head = nullptr;
    volatile uint64_t *tail = nullptr;
    volatile uint64_t *iteration = nullptr;
    sem_t *semClient = nullptr;
    sem_t *semServer = nullptr;
    std::mutex criticalSection;
};

class ChannelClient {
  public:
    ChannelClient(Cal::Ipc::Connection &connection, Cal::Ipc::ShmemManager &shmemManager)
        : connection(connection), shmemManager(shmemManager) {
    }

    ~ChannelClient() {
        this->shmemManager.release(this->ringBufferShmem);
    }

    bool init() {
        log<Verbosity::debug>("Creating RPC ring buffer");
        this->ringBuffer = createRingBuffer();
        if (nullptr == ringBuffer) {
            log<Verbosity::critical>("Failed to create RPC ring buffer");
            return false;
        }
        log<Verbosity::debug>("Powering on RPC ring buffer");
        if (false == enableRpc()) {
            log<Verbosity::critical>("Failed to power on RPC ring buffer");
            return false;
        }
        return true;
    }

    template <typename MessageT>
    RingBuffer::CommandPacket getSpace(size_t dynamicSize) {
        return ringBuffer->getSpace(sizeof(MessageT) + dynamicSize);
    }

    template <typename MessageT>
    RingBuffer::CommandPacket getSpace() {
        return ringBuffer->getSpace(sizeof(MessageT));
    }

    bool callSynchronous(RingBuffer::CommandPacket packet /*add timeout*/) {
        ringBuffer->push(packet);
        if (false == wait(packet)) {
            log<Verbosity::critical>("Failed to get response for RPC call");
            return false;
        }
        log<Verbosity::bloat>("Successful synchronous call");
        return true;
    }

    int32_t getId() const {
        return ringBufferShmem.id;
    }

    std::unique_lock<std::mutex> lock() {
        return ringBuffer->lock();
    }

    bool wait(RingBuffer::CommandPacket packet) {
        return activeWait(packet);
    }

    void stop() {
        stopped = true;
    }

  protected:
    bool activeWait(RingBuffer::CommandPacket packet) {
        log<Verbosity::bloat>("Waiting for packet to be processed");
        while (ringBuffer->peekHead() < packet.ringOffset + packet.size) {
            if (stopped) {
                log<Verbosity::debug>("Aborting wait for command to be processed");
                return false;
            }
        }
        log<Verbosity::bloat>("Packet has been processed");
        return true;
    }

    std::unique_ptr<RingBuffer> createRingBuffer() {
        auto remoteShmem = Cal::Ipc::allocateShmemOnRemote(this->connection, Cal::Messages::ReqAllocateShmem::rpcMessageChannel,
                                                           0U, 0U); // let service choose size
        if (false == remoteShmem.isValid()) {
            log<Verbosity::debug>("Failed to allocate RPC ring buffer shmem on the service side");
            return nullptr;
        }
        ringBufferShmem = shmemManager.get(remoteShmem, nullptr);
        if (nullptr == ringBufferShmem.ptr) {
            log<Verbosity::debug>("Failed to map RPC ring buffer shmem on client side");
            return nullptr;
        }
        log<Verbosity::debug>("Succesfully allocated RPC ring buffer shmem : %p, size : %zu", ringBufferShmem.ptr, ringBufferShmem.size);
        auto ringBuffer = std::make_unique<ShmemRingBuffer>();
        if (false == ringBuffer->partition(ringBufferShmem.ptr, ringBufferShmem.size, true)) {
            log<Verbosity::error>("Failed to partition the RPC ring buffer");
            return nullptr;
        }

        return ringBuffer;
    }

    bool enableRpc() {
        Cal::Messages::ReqLaunchRpcShmemRingBuffer request;
        auto ringLayout = ringBuffer->getLayout();
        request.ringbufferShmemId = ringBufferShmem.id;
        request.headOffsetWithinShmem = ringLayout.head;
        request.tailOffsetWithinShmem = ringLayout.tail;
        request.iterationOffsetWithinShmem = ringLayout.iteration;
        request.clientSemaphoreOffsetWithinShmem = ringLayout.semClient;
        request.serverSemaphoreOffsetWithinShmem = ringLayout.semServer;
        request.ringStartOffsetWithinShmem = ringLayout.ringStart;
        request.synchronizationMethod = Cal::Messages::ReqLaunchRpcShmemRingBuffer::activePooling;

        {
            auto lock = connection.lock();
            if (false == connection.send(request)) {
                log<Verbosity::error>("Failed to send request of type ReqLaunchRpcShmemRingBuffer");
                return false;
            }

            Cal::Messages::RespLaunchRpcShmemRingBuffer response;
            if ((false == connection.receive(response)) || response.isInvalid()) {
                log<Verbosity::error>("Invalid response from service for RespLaunchRpcShmemRingBuffer");
                return false;
            }
        }

        return true;
    }

    Cal::Ipc::Connection &connection;
    Cal::Ipc::ShmemManager &shmemManager;
    std::unique_ptr<RingBuffer> ringBuffer;
    Cal::Ipc::Shmem ringBufferShmem;
    std::atomic_bool stopped = false;
};

class ChannelServer {
  public:
    ChannelServer(Cal::Ipc::Connection &connection, Cal::Ipc::ShmemManager &shmemManager)
        : connection(connection), shmemManager(shmemManager) {
    }

    bool init(Cal::Ipc::Shmem ringBufferShmem, const Cal::Messages::ReqLaunchRpcShmemRingBuffer &request) {
        if (Cal::Messages::ReqLaunchRpcShmemRingBuffer::activePooling != request.synchronizationMethod) {
            log<Verbosity::error>("Client : %d requested unsupported synchronization method : %s", connection.getId(), request.synchronizationMethodStr());
            return false;
        }

        auto ringBuffer = std::make_unique<Cal::Rpc::ShmemRingBuffer>();
        Cal::Rpc::RingBuffer::Layout layout = {};

        layout.head = request.headOffsetWithinShmem;
        layout.tail = request.tailOffsetWithinShmem;
        layout.iteration = request.iterationOffsetWithinShmem;
        layout.semClient = request.clientSemaphoreOffsetWithinShmem;
        layout.semServer = request.serverSemaphoreOffsetWithinShmem;
        layout.ringStart = request.ringStartOffsetWithinShmem;
        if (false == ringBuffer->partition(ringBufferShmem.ptr, ringBufferShmem.size, layout, false)) {
            log<Verbosity::error>("Failed to partition RPC ring buffer using layout provided by client : %d", connection.getId());
            return false;
        }
        this->ringBuffer = std::move(ringBuffer);
        this->ringBufferShmem = ringBufferShmem;

        return true;
    }

    int32_t getId() const {
        return ringBufferShmem.id;
    }

    RingBuffer::CommandPacket wait(bool yieldThread) {
        return activeWait(yieldThread);
    }

    void stop() {
        log<Verbosity::debug>("Stoping RPC channel at iteration:%zu, head:%zu, tail:%zu", this->ringBuffer->peekIteration(), this->ringBuffer->peekHead(), this->ringBuffer->peekTail());
        stopped = true;
    }

    void removeCommand(RingBuffer::CommandPacket command) {
        this->ringBuffer->pop(command.size);
    }

  protected:
    RingBuffer::CommandPacket activeWait(bool yieldThread) {
        log<Verbosity::bloat>("Waiting for new command packet request");
        while (ringBuffer->peekTail() == ringBuffer->peekHead()) {
            if (yieldThread) {
                std::this_thread::yield();
            }
            if (stopped) {
                log<Verbosity::debug>("Aborting wait for command packet request");
                return {};
            }
        }
        log<Verbosity::bloat>("New commaned packet request arrived");
        auto ring = this->ringBuffer->getRingRaw();
        auto head = ringBuffer->peekHead();
        auto tail = ringBuffer->peekTail();
        auto newCommandPtr = Cal::Utils::moveByBytes(ring, head);

        return RingBuffer::CommandPacket{newCommandPtr, tail - head, head};
    }

    Cal::Ipc::Connection &connection;
    Cal::Ipc::ShmemManager &shmemManager;
    std::unique_ptr<RingBuffer> ringBuffer;
    Cal::Ipc::Shmem ringBufferShmem;
    std::atomic_bool stopped = false;
};

} // namespace Rpc

} // namespace Cal