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

// Implementation is lock-free for single-producer, single-consumer scenarios
//    multi-producer/consumer scenarios (multithreading on client/service side)
//    require external lock of the ring
//
// tail modified by producer
// head modified by consumer
// head chases tail (tail > head in first iteration)
template <typename DataType, typename OffsetType>
class TypedRing final {
  public:
    TypedRing() = default;

    TypedRing(DataType *data, size_t capacity,
              OffsetType *head, OffsetType *tail)
        : data(data), capacity(capacity), head(head), tail(tail) {
    }

    void reset() {
        __atomic_store_n(head, 0U, __ATOMIC_RELAXED);
        __atomic_store_n(tail, 0U, __ATOMIC_RELAXED);
    }

    OffsetType peekHeadOffset() const {
        return __atomic_load_n(head, __ATOMIC_RELAXED);
    }

    OffsetType peekTailOffset() const {
        return __atomic_load_n(tail, __ATOMIC_RELAXED);
    }

    uint64_t peekIteration() const {
        return iteration;
    }

    DataType *peekHead() {
        return &data[__atomic_load_n(head, __ATOMIC_RELAXED)];
    }

    bool peekEmpty() const {
        return peekHeadOffset() == peekTailOffset();
    }

    size_t getCapacity() const {
        return capacity;
    }

    bool pop() {
        if (peekEmpty()) {
            log<Verbosity::error>("Ring empty");
            return false;
        }
        auto prevHead = peekHeadOffset();
        auto nextHead = prevHead;
        if (prevHead + 1 == capacity) {
            nextHead = 0;
        } else {
            nextHead = prevHead + 1;
        }
        __atomic_store_n(head, nextHead, __ATOMIC_RELAXED);
        return true;
    }

    template <typename T>
    bool push(T &&el) {
        auto tailSnapshot = peekTailOffset();
        auto headSnapshot = peekHeadOffset();
        if (tailSnapshot >= headSnapshot) {
            if (capacity > tailSnapshot + 1) {
                data[tailSnapshot] = std::forward<T>(el);
                __atomic_store_n(tail, tailSnapshot + 1, __ATOMIC_RELAXED);
                return true;
            } else { // loop
                if (headSnapshot == 0) {
                    log<Verbosity::error>("Ring full");
                    return false;
                }
                data[tailSnapshot] = std::forward<T>(el);
                __atomic_store_n(tail, 0, __ATOMIC_RELAXED);
                ++iteration;
                log<Verbosity::debug>("Ring looped, iteration %lu", iteration);
                return true;
            }
        } else {
            if (tailSnapshot + 1 < headSnapshot) { // looped and wrapped
                data[tailSnapshot] = std::forward<T>(el);
                __atomic_store_n(tail, tailSnapshot + 1, __ATOMIC_RELAXED);
                return true;
            } else {
                log<Verbosity::error>("Ring full");
                return false;
            }
        }
    }

  protected:
    DataType *data = nullptr;
    size_t capacity = 0U;

    OffsetType *head = nullptr;
    OffsetType *tail = nullptr;
    uint64_t iteration = 0;
};

// Thread-safe
template <typename MaskType = uint64_t>
class StaticLengthBitAllocator final {
  public:
    using MaskT = MaskType;
    static constexpr uint32_t capacity = std::numeric_limits<MaskT>::digits;
    using BitOffsetT = uint32_t;
    static constexpr MaskT fullMask = std::numeric_limits<MaskT>::max();
    static constexpr BitOffsetT invalidOffset = std::numeric_limits<BitOffsetT>::max();

    StaticLengthBitAllocator() = default;

    StaticLengthBitAllocator(const StaticLengthBitAllocator &rhs) {
        occupied = rhs.occupied.load();
    }

    StaticLengthBitAllocator(StaticLengthBitAllocator &&rhs) {
        occupied = rhs.occupied.exchange(0);
    }

    BitOffsetT allocate() {
        BitOffsetT offset = invalidOffset;
        auto prev = occupied.load();
        while (true) {
            if (prev == fullMask) {
                break;              // full
            } else if (0 == prev) { // empty
                if (occupied.compare_exchange_weak(prev, 1U)) {
                    offset = 0;
                    break;
                }
            }

            auto inv = ~prev;
            auto firstUnset = __builtin_ffsl(inv) - 1;
            if (occupied.compare_exchange_weak(prev, prev | (static_cast<MaskT>(1) << firstUnset))) {
                offset = firstUnset;
                break;
            }
        }
        return offset;
    }

    void free(BitOffsetT offset) {
        auto mask = ~(1 << offset);
        auto prev = occupied.load();
        while (false == occupied.compare_exchange_weak(prev, prev & mask)) {
        }
    }

  protected:
    std::atomic<MaskT> occupied = 0U;
};

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

    virtual bool waitOnServiceSemaphore() = 0;
    virtual bool waitOnClientSemaphore() = 0;
    virtual bool signalServiceSemaphore() = 0;
    virtual bool signalClientSemaphore() = 0;

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

    ~ShmemRingBuffer() override {
        if (ownsSemaphores) {
            if (0 != Cal::Sys::sem_destroy(semClient)) {
                log<Verbosity::error>("Failed to destroy rpc ring client sempahore");
            }
            if (0 != Cal::Sys::sem_destroy(semServer)) {
                log<Verbosity::error>("Failed to destroy rpc ring service sempahore");
            }
        }
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

    bool waitOnServiceSemaphore() override {
        auto ret = Cal::Sys::sem_wait(semServer);
        if (ret != 0) {
            log<Verbosity::error>("sem_wait failed (error = %d)for RPC ring service semaphore failed", ret);
        }
        return ret == 0;
    }
    bool waitOnClientSemaphore() override {
        auto ret = Cal::Sys::sem_wait(semClient);
        if (ret != 0) {
            log<Verbosity::error>("sem_wait failed (error = %d) for RPC ring client semaphore failed", ret);
        }
        return ret == 0;
    }
    bool signalServiceSemaphore() override {
        auto ret = Cal::Sys::sem_post(semServer);
        if (ret != 0) {
            log<Verbosity::error>("sem_post failed (error = %d) for RPC ring service semaphore failed", ret);
        }
        return ret == 0;
    }
    bool signalClientSemaphore() override {
        auto ret = Cal::Sys::sem_post(semClient);
        if (ret != 0) {
            log<Verbosity::error>("sem_post failed (error = %d) for RPC ring client semaphore failed", ret);
        }
        return ret == 0;
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
        ownsSemaphores = true;
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
    bool ownsSemaphores = false;
};

class ChannelClient {
  public:
    enum ClientSynchronizationMethod : uint32_t { unknown,
                                                  activePolling, // client always polls for command completion status in busy loop
                                                  semaphores,    // client always requires service to signal completion using semaphore
                                                  latencyBased   // client uses mixed mode (semaphore+activePolling) based on command latency traits
    };

    static const char *asCStr(ClientSynchronizationMethod e) {
        switch (e) {
        default:
            return "unknown";
        case activePolling:
            return "activePolling";
        case semaphores:
            return "semaphores";
        case latencyBased:
            return "latencyBased";
        }
    }

    ChannelClient(Cal::Ipc::Connection &connection, Cal::Ipc::ShmemManager &shmemManager)
        : connection(connection), shmemManager(shmemManager) {
    }

    ~ChannelClient() {
        this->shmemManager.release(this->ringBufferShmem);
    }

    bool init(ClientSynchronizationMethod clientSynchronizationMethod) {
        if (unknown == clientSynchronizationMethod) {
            log<Verbosity::critical>("Failed to create RPC ring buffer with invalid client synchronization method : %s", asCStr(clientSynchronizationMethod));
            return false;
        }
        log<Verbosity::debug>("Creating RPC ring buffer with %s client synchronization method", asCStr(clientSynchronizationMethod));
        this->clientSynchronizationMethod = clientSynchronizationMethod;
        switch (clientSynchronizationMethod) {
        default:
            break;
        case activePolling:
            this->semaphoreWaitThreshold = 100.0f; // unreachable threshold (no semaphores)
            break;
        case semaphores:
            this->semaphoreWaitThreshold = -100.0f; // all APIs reach this threshold (always semaphores)
            break;
        case latencyBased:
            this->semaphoreWaitThreshold = 0.0f; // "API latency > 0" will trigger semaphores usage
            break;
        }
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

    bool callSynchronous(RingBuffer::CommandPacket packet /*add timeout*/, Cal::Rpc::RpcMessageHeader::MessageFlagsT messageFlags) {
        ringBuffer->push(packet);
        if (Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores == serviceSynchronizationMethod) {
            if (false == ringBuffer->signalServiceSemaphore()) {
                log<Verbosity::critical>("Failed to signal service with new RPC call");
                return false;
            }
        }
        if (false == wait(packet, messageFlags)) {
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

    bool wait(RingBuffer::CommandPacket packet, Cal::Rpc::RpcMessageHeader::MessageFlagsT messageFlags) {
        if (0 != messageFlags & Cal::Rpc::RpcMessageHeader::FlagsBits::signalSemaphoreOnCompletion) {
            return semaphoreWait(packet);
        } else {
            return activeWait(packet);
        }
    }

    void stop() {
        stopped = true;
    }

    bool shouldSynchronizeNextCommandWithSemaphores(float commandLatency) {
        return commandLatency > semaphoreWaitThreshold;
    }

  protected:
    bool semaphoreWait(RingBuffer::CommandPacket packet) {
        log<Verbosity::bloat>("Waiting for packet to be processed - semaphores");
        ringBuffer->waitOnClientSemaphore();
        if (stopped) {
            log<Verbosity::debug>("Aborting wait for command packet request");
            return {};
        }
        if (ringBuffer->peekHead() < packet.ringOffset + packet.size) {
            log<Verbosity::error>("Command not processed after woken up from semaphore wait");
        }

        while (ringBuffer->peekHead() < packet.ringOffset + packet.size) {
            if (stopped) {
                log<Verbosity::debug>("Aborting wait for command to be processed");
                return false;
            }
        }
        log<Verbosity::bloat>("Packet has been processed");
        return true;
    }

    bool activeWait(RingBuffer::CommandPacket packet) {
        log<Verbosity::bloat>("Waiting for packet to be processed - active wait");
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

        Cal::Messages::RespLaunchRpcShmemRingBuffer response;
        {
            auto lock = connection.lock();
            if (false == connection.send(request)) {
                log<Verbosity::error>("Failed to send request of type ReqLaunchRpcShmemRingBuffer");
                return false;
            }

            if ((false == connection.receive(response)) || response.isInvalid()) {
                log<Verbosity::error>("Invalid response from service for RespLaunchRpcShmemRingBuffer");
                return false;
            }
        }
        serviceSynchronizationMethod = response.serviceSynchronizationMethod;

        return true;
    }

    Cal::Ipc::Connection &connection;
    Cal::Ipc::ShmemManager &shmemManager;
    std::unique_ptr<RingBuffer> ringBuffer;
    Cal::Ipc::Shmem ringBufferShmem;
    std::atomic_bool stopped = false;
    Cal::Messages::RespLaunchRpcShmemRingBuffer::ServiceSynchronizationMethod serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::unknown;
    ClientSynchronizationMethod clientSynchronizationMethod = unknown;
    float semaphoreWaitThreshold = 0.0f;
};

class ChannelServer {
  public:
    ChannelServer(Cal::Ipc::Connection &connection, Cal::Ipc::ShmemManager &shmemManager)
        : connection(connection), shmemManager(shmemManager) {
    }

    bool init(Cal::Ipc::Shmem ringBufferShmem, const Cal::Messages::ReqLaunchRpcShmemRingBuffer &request, Cal::Messages::RespLaunchRpcShmemRingBuffer::ServiceSynchronizationMethod serviceSynchronizationMethod) {
        log<Verbosity::debug>("Client : %d; service synchronization method %s", connection.getId(),
                              Cal::Messages::RespLaunchRpcShmemRingBuffer::asCStr(serviceSynchronizationMethod));
        this->serviceSynchronizationMethod = serviceSynchronizationMethod;

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
        switch (serviceSynchronizationMethod) {
        case Cal::Messages::RespLaunchRpcShmemRingBuffer::activePolling:
            return activeWait(yieldThread);
        case Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores:
            return semaphoreWait();
        default:
            log<Verbosity::critical>("Unhandled wait method");
            return {};
        }
    }

    void stop() {
        log<Verbosity::debug>("Stoping RPC channel at iteration:%zu, head:%zu, tail:%zu", this->ringBuffer->peekIteration(), this->ringBuffer->peekHead(), this->ringBuffer->peekTail());
        stopped = true;
        if (Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores == serviceSynchronizationMethod) {
            this->ringBuffer->signalServiceSemaphore();
        }
    }

    void removeCommand(RingBuffer::CommandPacket command, Cal::Rpc::RpcMessageHeader::MessageFlagsT messageFlags) {
        this->ringBuffer->pop(command.size);
        if (0 != (messageFlags & Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion)) {
            this->ringBuffer->signalClientSemaphore();
        }
    }

  protected:
    RingBuffer::CommandPacket activeWait(bool yieldThread) {
        log<Verbosity::bloat>("Waiting for new command packet request - active polling");
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

    RingBuffer::CommandPacket semaphoreWait() {
        log<Verbosity::bloat>("Waiting for new command packet request - semaphores");
        ringBuffer->waitOnServiceSemaphore();
        if (stopped) {
            log<Verbosity::debug>("Aborting wait for command packet request");
            return {};
        }
        if (ringBuffer->peekTail() == ringBuffer->peekHead()) {
            log<Verbosity::error>("Ring empty after woken up from semaphore wait");
        }
        while (ringBuffer->peekTail() == ringBuffer->peekHead()) {
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
    Cal::Messages::RespLaunchRpcShmemRingBuffer::ServiceSynchronizationMethod serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::unknown;
};

} // namespace Rpc

} // namespace Cal
