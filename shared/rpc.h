/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/allocators.h"
#include "shared/control_messages.h"
#include "shared/ipc.h"
#include "shared/log.h"
#include "shared/rpc_message.h"
#include "shared/shmem.h"
#include "shared/shmem_transfer_desc.h"
#include "shared/usm.h"
#include "shared/utils.h"

#include <atomic>
#include <bitset>
#include <inttypes.h>
#include <memory>
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

    void wait() {
        auto tailSnapshot = peekTailOffset();
        while (peekHeadOffset() != tailSnapshot) {
        }
    }

    bool pop() {
        if (peekEmpty()) {
            log<Verbosity::error>("Ring empty");
            return false;
        }
        auto prevHead = peekHeadOffset();
        auto nextHead = prevHead;
        if (prevHead + 1 == static_cast<int64_t>(capacity)) {
            nextHead = 0;
        } else {
            nextHead = prevHead + 1;
        }
        __atomic_store_n(head, nextHead, __ATOMIC_RELAXED);
        return true;
    }

    template <typename T>
    bool push(T &&el, bool batched) {
        auto tailSnapshot = peekTailOffset();
        auto headSnapshot = peekHeadOffset();
        if (tailSnapshot >= headSnapshot) {
            if (static_cast<int64_t>(capacity) > tailSnapshot + batchCounter + 1) {
                data[tailSnapshot + batchCounter] = std::forward<T>(el);
                if (batched) {
                    ++batchCounter;
                } else {
                    __atomic_store_n(tail, tailSnapshot + batchCounter + 1, __ATOMIC_RELAXED);
                    batchCounter = 0u;
                }
                return true;
            } else { // loop
                if (headSnapshot == 0) {
                    log<Verbosity::performance>("Ring full");
                    return false;
                }
                data[tailSnapshot + batchCounter] = std::forward<T>(el);
                batchCounter = 0;
                __atomic_store_n(tail, 0, __ATOMIC_RELAXED);
                ++iteration;
                log<Verbosity::debug>("Ring looped, iteration %lu", iteration);
                return true;
            }
        } else {
            if (tailSnapshot + batchCounter + 1 < headSnapshot) { // looped and wrapped
                data[tailSnapshot + batchCounter] = std::forward<T>(el);
                if (batched) {
                    ++batchCounter;
                } else {
                    __atomic_store_n(tail, tailSnapshot + batchCounter + 1, __ATOMIC_RELAXED);
                    batchCounter = 0u;
                }
                return true;
            } else {
                log<Verbosity::performance>("Ring full");
                return false;
            }
        }
    }

    void flushBatched() {
        if (batchCounter == 0) {
            return;
        }
        __atomic_store_n(tail, peekTailOffset() + batchCounter, __ATOMIC_RELAXED);
    }

  protected:
    DataType *data = nullptr;
    size_t capacity = 0U;

    OffsetType *head = nullptr;
    OffsetType *tail = nullptr;
    OffsetType batchCounter = 0;
    uint64_t iteration = 0;
};

using CompletionStampT = uint32_t;
constexpr CompletionStampT CompletionStampReady = 1;
constexpr CompletionStampT CompletionStampNotReady = 0;
using CompletionStampBufferT = Cal::Allocators::TagAllocator<CompletionStampT>;

using OffsetWithinChannelT = Cal::Messages::OffsetWithinChannelT;

struct RingEntry {
    Cal::Messages::OffsetWithinChannelT messageOffset;
    Cal::Messages::OffsetWithinChannelT completionStampOffset;
};

class CommandsChannel {
  public:
    // | control block + ring | completion stamps | hostptr copies to update | heap ...
    struct Layout {
        using OffsetT = Cal::Messages::OffsetWithinChannelT;

        using RingHeadT = Cal::Messages::OffsetWithinChannelT;
        OffsetT ringHead = 0;

        using SemClientT = ::sem_t;
        OffsetT semClient = Cal::Utils::alignUpPow2<sizeof(SemClientT)>(ringHead + sizeof(RingHeadT));

        using RingTailT = RingHeadT;
        OffsetT ringTail = Cal::Utils::alignUpPow2<Cal::Utils::cachelineSize>(semClient);

        using SemServerT = SemClientT;
        OffsetT semServer = Cal::Utils::alignUpPow2<sizeof(SemServerT)>(ringTail + sizeof(RingTailT));

        using RingEntryT = Cal::Rpc::RingEntry;
        OffsetT ringStart = Cal::Utils::alignUpPow2<Cal::Utils::cachelineSize>(semServer);
        OffsetT ringEnd = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(semServer);

        using CompletionStampT = Cal::Rpc::CompletionStampT;
        OffsetT completionStampsStart = ringEnd;
        OffsetT completionStampsEnd = completionStampsStart + Cal::Utils::pageSize4KB;

        OffsetT hostptrCopiesRingHead = completionStampsEnd;
        OffsetT hostptrCopiesRingTail = Cal::Utils::alignUpPow2<Cal::Utils::cachelineSize>(hostptrCopiesRingHead + sizeof(RingHeadT));

        using MemChunkT = Cal::Rpc::MemChunk;
        OffsetT hostptrCopiesRingStart = Cal::Utils::alignUpPow2<Cal::Utils::cachelineSize>(hostptrCopiesRingTail + sizeof(RingTailT));
        OffsetT hostptrCopiesRingEnd = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(hostptrCopiesRingStart + Cal::Utils::pageSize4KB);

        OffsetT heapStart = hostptrCopiesRingEnd;

        size_t minHeapSize = Cal::Utils::pageSize4KB;
        size_t minShmemSize = heapStart + minHeapSize;

        bool valid() {
            return check((ringEnd - ringStart) / sizeof(RingEntryT) >= 2, "Should contain at least 2 entries") && check(Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(ringEnd), "Unaligned ring end") && check(Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(completionStampsEnd), "Unaligned completion stamps end") && check(Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(hostptrCopiesRingEnd), "Unaligned host ptr copies end");
        }

        void resizeCommandsRing(size_t numberOfPages) {
            OffsetT newRingEnd = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(ringStart) + numberOfPages * Cal::Utils::pageSize4KB;
            if (ringEnd == newRingEnd) {
                return;
            }

            ringEnd = newRingEnd;
            size_t numRingEntries = (ringEnd - ringStart) / sizeof(RingEntryT);
            auto comletionStampsCount = numRingEntries * 4; // 4 times as much in case service consumes ring faster than timestamps are being released (e.g. async calls)
            completionStampsStart = ringEnd;
            completionStampsEnd = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(completionStampsStart + comletionStampsCount * sizeof(CompletionStampT));

            hostptrCopiesRingHead = completionStampsEnd;
            hostptrCopiesRingTail = Cal::Utils::alignUpPow2<Cal::Utils::cachelineSize>(hostptrCopiesRingHead + sizeof(RingHeadT));
            hostptrCopiesRingStart = Cal::Utils::alignUpPow2<Cal::Utils::cachelineSize>(hostptrCopiesRingTail + sizeof(RingTailT));
            hostptrCopiesRingEnd = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(hostptrCopiesRingStart + Cal::Utils::pageSize4KB);

            heapStart = hostptrCopiesRingEnd;
        }

      protected:
        bool check(bool v, const char *errorMessage) {
            if (false == v) {
                log<Verbosity::critical>(errorMessage);
            }
            return v;
        }
    };

    virtual ~CommandsChannel() {
        if (ownsSemaphores) {
            if (0 != Cal::Sys::sem_destroy(semClient)) {
                log<Verbosity::error>("Failed to destroy rpc ring client sempahore");
            }
            if (0 != Cal::Sys::sem_destroy(semServer)) {
                log<Verbosity::error>("Failed to destroy rpc ring service sempahore");
            }
        }
    }

    std::unique_lock<std::mutex> lock() {
        return std::unique_lock<std::mutex>(mutex);
    }

    bool waitOnServiceSemaphore() {
        auto ret = Cal::Sys::sem_wait(semServer);
        if (ret != 0) {
            log<Verbosity::error>("sem_wait failed (error = %d)for RPC ring service semaphore failed", ret);
        }
        return ret == 0;
    }

    bool waitOnClientSemaphore() {
        auto ret = Cal::Sys::sem_wait(semClient);
        if (ret != 0) {
            log<Verbosity::error>("sem_wait failed (error = %d) for RPC ring client semaphore failed", ret);
        }
        return ret == 0;
    }

    bool signalServiceSemaphore() {
        auto ret = Cal::Sys::sem_post(semServer);
        if (ret != 0) {
            log<Verbosity::error>("sem_post failed (error = %d) for RPC ring service semaphore failed", ret);
        }
        return ret == 0;
    }

    bool signalClientSemaphore() {
        auto ret = Cal::Sys::sem_post(semClient);
        if (ret != 0) {
            log<Verbosity::error>("sem_post failed (error = %d) for RPC ring client semaphore failed", ret);
        }
        return ret == 0;
    }

  protected:
    mockable bool partition(void *shmem, size_t shmemSize, bool initializeControlBlock, bool useAsyncCalls) {
        using namespace Cal::Utils;
        if (false == isAlignedPow2<Cal::Utils::pageSize4KB>(shmem)) {
            log<Verbosity::critical>("Tried to use page-unaligned shmem as commands chnnel : %p (rest : %zu)",
                                     shmem, reinterpret_cast<uintptr_t>(shmem) % Cal::Utils::pageSize4KB);
            return false;
        }
        if (false == isAlignedPow2<Cal::Utils::pageSize4KB>(shmemSize)) {
            log<Verbosity::critical>("Tried to use page-unaligned shmem size as commands chnnel");
            return false;
        }

        CommandsChannel::Layout layout;

        auto requestedRpcRingPages = Cal::Utils::getCalEnvI64(calRpcRingPagesEnvName, -1);
        if (requestedRpcRingPages != -1) {
            log<Verbosity::info>("Changing default RPC ring size from <= 1 page %d page(s)", requestedRpcRingPages);
            layout.resizeCommandsRing(requestedRpcRingPages);
        } else if (useAsyncCalls) {
            static constexpr size_t minPagesForAsyncRpcRing = 1;
            log<Verbosity::info>("Applied RPC ring size for async calls %d page(s)", minPagesForAsyncRpcRing);
            layout.resizeCommandsRing(minPagesForAsyncRpcRing);
        }

        if (false == layout.valid()) {
            log<Verbosity::critical>("Tried to use invalid layout for RPC channel");
            return false;
        }

        if (shmemSize < layout.minShmemSize) {
            log<Verbosity::critical>("Tried to use shmem that is too small (size : %zu = %zu pages < %zu)",
                                     shmemSize, shmemSize / Cal::Utils::pageSize4KB, layout.minShmemSize / Cal::Utils::pageSize4KB);
            return false;
        }

        this->shmem = shmem;
        this->shmemSize = shmemSize;

        this->layout.ringHead = layout.ringHead;
        this->layout.semClient = layout.semClient;

        this->layout.ringTail = layout.ringTail;
        this->layout.semServer = layout.semServer;

        this->layout.ringStart = layout.ringStart;
        this->layout.ringCapacity = (layout.ringEnd - layout.ringStart) / sizeof(RingEntry);

        this->layout.completionStampsStart = layout.completionStampsStart;
        this->layout.completionStampsCapacity = (layout.completionStampsEnd - layout.completionStampsStart) / sizeof(Layout::CompletionStampT);

        this->layout.hostptrCopiesRingHead = layout.hostptrCopiesRingHead;
        this->layout.hostptrCopiesRingTail = layout.hostptrCopiesRingTail;

        this->layout.hostptrCopiesRingStart = layout.hostptrCopiesRingStart;
        this->layout.hostptrCopiesRingCapacity = (layout.hostptrCopiesRingEnd - layout.hostptrCopiesRingStart) / sizeof(Layout::MemChunkT);

        this->layout.heapStart = layout.heapStart;
        this->layout.heapEnd = shmemSize;

        this->semClient = getAsLocalAddress<sem_t>(this->layout.semClient);
        this->semServer = getAsLocalAddress<sem_t>(this->layout.semServer);

        this->ring = RingT(getAsLocalAddress<RingEntry>(this->layout.ringStart),
                           this->layout.ringCapacity,
                           getAsLocalAddress<OffsetWithinChannelT>(this->layout.ringHead),
                           getAsLocalAddress<OffsetWithinChannelT>(this->layout.ringTail));

        this->hostptrCopiesRing = HostptrCopiesRingT(getAsLocalAddress<Cal::Rpc::MemChunk>(this->layout.hostptrCopiesRingStart),
                                                     this->layout.hostptrCopiesRingCapacity,
                                                     getAsLocalAddress<OffsetWithinChannelT>(this->layout.hostptrCopiesRingHead),
                                                     getAsLocalAddress<OffsetWithinChannelT>(this->layout.hostptrCopiesRingTail));

        if (initializeControlBlock) {
            return this->initControlBlock();
        } else {
            return true;
        }
    }

    mockable bool partition(void *shmem, size_t shmemSize, const Cal::Messages::CommandsChannelLayout &existingLayout, bool initializeControlBlock) {
        using namespace Cal::Utils;
        if (false == (existingLayout.isValid() && isInBounds(existingLayout, shmemSize))) {
            log<Verbosity::critical>("Tried to partition commands channel using invalid layout");
            return false;
        }

        this->layout = existingLayout;
        this->shmem = shmem;
        this->shmemSize = shmemSize;

        this->semClient = getAsLocalAddress<sem_t>(this->layout.semClient);
        this->semServer = getAsLocalAddress<sem_t>(this->layout.semServer);

        this->ring = RingT(getAsLocalAddress<RingEntry>(this->layout.ringStart),
                           this->layout.ringCapacity,
                           getAsLocalAddress<OffsetWithinChannelT>(this->layout.ringHead),
                           getAsLocalAddress<OffsetWithinChannelT>(this->layout.ringTail));

        this->hostptrCopiesRing = HostptrCopiesRingT(getAsLocalAddress<Cal::Rpc::MemChunk>(this->layout.hostptrCopiesRingStart),
                                                     this->layout.hostptrCopiesRingCapacity,
                                                     getAsLocalAddress<OffsetWithinChannelT>(this->layout.hostptrCopiesRingHead),
                                                     getAsLocalAddress<OffsetWithinChannelT>(this->layout.hostptrCopiesRingTail));

        if (initializeControlBlock) {
            return this->initControlBlock();
        } else {
            return true;
        }
    }

    bool initControlBlock() {
        ring.reset();
        hostptrCopiesRing.reset();

        if (0 != Cal::Ipc::initializeSemaphore(semClient)) {
            log<Verbosity::critical>("Failed to initialize client semaphore in commands channel");
            return false;
        }
        if (0 != Cal::Ipc::initializeSemaphore(semServer)) {
            log<Verbosity::critical>("Failed to initialize server semaphore in commands channel");
            if (0 != Cal::Sys::sem_destroy(semClient)) {
                log<Verbosity::error>("Failed to destroy rpc ring client sempahore");
            }
            return false;
        }
        ownsSemaphores = true;
        return true;
    }

    static bool isInBounds(const Cal::Messages::CommandsChannelLayout &existinglayout, size_t channelSize) {
        const auto &el = existinglayout;
        auto channel = Cal::Utils::AddressRange(static_cast<size_t>(0), channelSize);
        auto ringHead = Cal::Utils::AddressRange(el.ringHead, el.ringHead + sizeof(Cal::Messages::OffsetWithinChannelT));
        auto ringTail = Cal::Utils::AddressRange(el.ringTail, el.ringTail + sizeof(Cal::Messages::OffsetWithinChannelT));
        auto semClient = Cal::Utils::AddressRange(el.semClient, el.semClient + sizeof(sem_t));
        auto semServer = Cal::Utils::AddressRange(el.semServer, el.semServer + sizeof(sem_t));
        auto ring = Cal::Utils::AddressRange(el.ringStart, el.ringStart + el.ringCapacity * sizeof(RingEntry));
        auto completionStamps = Cal::Utils::AddressRange(el.completionStampsStart, el.completionStampsStart + el.completionStampsCapacity * sizeof(CompletionStampT));
        auto hostptrCopiesRingHead = Cal::Utils::AddressRange(el.hostptrCopiesRingHead, el.hostptrCopiesRingHead + sizeof(Cal::Messages::OffsetWithinChannelT));
        auto hostptrCopiesRingTail = Cal::Utils::AddressRange(el.hostptrCopiesRingTail, el.hostptrCopiesRingTail + sizeof(Cal::Messages::OffsetWithinChannelT));
        auto hostptrCopiesRing = Cal::Utils::AddressRange(el.hostptrCopiesRingStart, el.hostptrCopiesRingStart + el.hostptrCopiesRingCapacity * sizeof(Cal::Rpc::MemChunk));
        auto heap = Cal::Utils::AddressRange(static_cast<size_t>(el.heapStart), el.heapEnd);

        std::tuple<const char *, Cal::Utils::AddressRange, size_t> ranges[] = {
            {"ringHead", ringHead, sizeof(Cal::Messages::OffsetWithinChannelT)},
            {"ringTail", ringTail, sizeof(Cal::Messages::OffsetWithinChannelT)},
            {"semClient", semClient, sizeof(sem_t)},
            {"semServer", semServer, sizeof(sem_t)},
            {"ring", ring, Cal::Utils::cachelineSize},
            {"completionStamps", completionStamps, Cal::Utils::cachelineSize},
            {"hostptrCopiesRingHead", hostptrCopiesRingHead, sizeof(Cal::Messages::OffsetWithinChannelT)},
            {"hostptrCopiesRingTail", hostptrCopiesRingTail, sizeof(Cal::Messages::OffsetWithinChannelT)},
            {"hostptrCopiesRing", hostptrCopiesRing, Cal::Utils::cachelineSize},
            {"heap", heap, Cal::Utils::pageSize4KB},
        };

        bool valid = true;
        for (auto &[name, range, alignment] : ranges) {
            if (false == channel.contains(range)) {
                valid = false;
                log<Verbosity::error>("%s (range %zx-%zx) is out of bounds of channel memory (0-%zx)", name, range.start, range.end, channel.end);
            }
            if (false == (Cal::Utils::isAligned(range.start, alignment) && Cal::Utils::isAligned(range.end, alignment))) {
                valid = false;
                log<Verbosity::error>("%s (range %zx-%zx) does not meet alignment (%zx)", name, range.start, range.end, alignment);
            }
            for (auto &[rhsName, rhsRange, rhsAlignment] : ranges) {
                (void)rhsAlignment;

                if (&range == &rhsRange) {
                    continue;
                }
                if (range.intersects(rhsRange)) {
                    valid = false;
                    log<Verbosity::error>("%s (range %zx-%zx) intersects with %s (range %zx-%zx)", name, range.start, range.end, rhsName, rhsRange.start, rhsRange.end);
                }
            }
        }
        return valid;
    }

    void *getAsLocalAddress(OffsetWithinChannelT offset) {
        return Cal::Utils::moveByBytes(shmem, offset);
    }

    template <typename T>
    T *getAsLocalAddress(OffsetWithinChannelT offset) {
        return reinterpret_cast<T *>(getAsLocalAddress(offset));
    }

    OffsetWithinChannelT getAsShmemOffset(void *localAddress) {
        return Cal::Utils::byteDistanceAbs(shmem, localAddress);
    }

    Cal::Messages::CommandsChannelLayout layout;

    using RingT = TypedRing<RingEntry, OffsetWithinChannelT>;
    RingT ring;

    using HostptrCopiesRingT = TypedRing<Cal::Rpc::MemChunk, OffsetWithinChannelT>;
    HostptrCopiesRingT hostptrCopiesRing;

    void *shmem = nullptr;
    size_t shmemSize = 0U;

    sem_t *semClient = nullptr;
    sem_t *semServer = nullptr;

    std::mutex mutex;
    bool ownsSemaphores = false;
};

class ChannelClient : public CommandsChannel {
  public:
    struct ChannelSpaceDeleter {
        ChannelSpaceDeleter(ChannelClient &channel) : channel(channel) {
        }

        void operator()(void *ptr) {
            if (ptr) {
                channel.freeSpace(ptr);
            }
        }

        ChannelClient &getChannel() {
            return channel;
        }

      protected:
        ChannelClient &channel;
    };

    enum ClientSynchronizationMethod : uint32_t { unknown,
                                                  activePolling, // client always polls for command completion status in busy loop
                                                  semaphores,    // client always requires service to signal completion using semaphore
                                                  latencyBased   // client uses mixed mode (semaphore+activePolling) based on command latency traits
    };

    struct SemaphoreThresholds {
        static constexpr float base = 0.0f;                           // "API latency > 0" will trigger semaphores usage
        static constexpr float unreachableAlwaysActiveWait = 100.0f;  // unreachable threshold (no semaphores)
        static constexpr float unreachableAlwaysSemaphores = -100.0f; // all APIs reach this threshold (always semaphores)
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

    ChannelClient(Cal::Ipc::Connection &connection, Cal::Ipc::ShmemImporter &globalShmemImporter, Cal::Usm::UsmShmemImporter &sharedVaShmemImporter)
        : connection(connection), globalShmemImporter(globalShmemImporter), sharedVaShmemImporter(sharedVaShmemImporter) {
    }

    ~ChannelClient() {
        if (usesSharedVaForRpcChannel) {
            this->sharedVaShmemImporter.release(this->underlyingShmem);
        } else {
            this->globalShmemImporter.release(this->underlyingShmem);
        }
    }

    bool init(ClientSynchronizationMethod clientSynchronizationMethod, bool useSharedVaForRpcChannel) {
        if (unknown == clientSynchronizationMethod) {
            log<Verbosity::critical>("Failed to RPC channel client with invalid client synchronization method : %s", asCStr(clientSynchronizationMethod));
            return false;
        }
        log<Verbosity::debug>("Creating RPC channel client with %s client synchronization method", asCStr(clientSynchronizationMethod));
        this->clientSynchronizationMethod = clientSynchronizationMethod;
        switch (clientSynchronizationMethod) {
        default:
            break;
        case activePolling:
            this->semaphoreWaitThreshold = SemaphoreThresholds::unreachableAlwaysActiveWait;
            break;
        case semaphores:
            this->semaphoreWaitThreshold = SemaphoreThresholds::unreachableAlwaysSemaphores;
            break;
        case latencyBased:
            this->semaphoreWaitThreshold = SemaphoreThresholds::base;
            break;
        }

        log<Verbosity::debug>("Creating RPC ring buffer");
        this->usesSharedVaForRpcChannel = useSharedVaForRpcChannel;
        this->useAsyncCalls = Cal::Utils::getCalEnvFlag(calAsynchronousCalls, true);
        if (false == createRingBuffer()) {
            log<Verbosity::critical>("Failed to create RPC ring buffer");
            return false;
        }

        log<Verbosity::debug>("Powering on RPC ring buffer");
        if (false == enableRpc()) {
            log<Verbosity::critical>("Failed to power on RPC ring buffer");
            return false;
        }

        this->completionStamp = getAsLocalAddress<CompletionStampT>(this->layout.completionStampsStart);
        auto totalHeapSize = this->layout.heapEnd - this->layout.heapStart;
        auto cmdHeapSize = totalHeapSize / 4;
        this->cmdHeap = Cal::Allocators::LinearAllocator(Cal::Utils::AddressRange(getAsLocalAddress(this->layout.heapStart), cmdHeapSize));
        this->standaloneHeap = Cal::Allocators::AddressRangeAllocator(Cal::Utils::AddressRange(getAsLocalAddress(this->layout.heapStart + cmdHeapSize), totalHeapSize - cmdHeapSize));
        this->useBatchedCalls = Cal::Utils::getCalEnvFlag(calBatchedCalls, this->useBatchedCalls);

        return true;
    }

    void *getCmdSpaceAligned(size_t size, size_t alignment) {
        auto addr = cmdHeap.allocate(size, alignment);
        if (nullptr == addr) {
            log<Verbosity::critical>("Command channel's commands heap is full");
            std::abort();
            return nullptr;
        }

        return addr;
    }

    std::unique_ptr<void, ChannelSpaceDeleter> getStandaloneSpaceAligned(size_t size, size_t alignment) {
        auto addr = standaloneHeap.allocate(size, alignment);
        if (nullptr == addr) {
            log<Verbosity::critical>("Command channel's standalone heap is full");
            std::abort();
            return std::unique_ptr<void, ChannelSpaceDeleter>(nullptr, ChannelSpaceDeleter(*this));
        }

        return std::unique_ptr<void, ChannelSpaceDeleter>(addr, ChannelSpaceDeleter(*this));
    }

    void *getCmdSpace(size_t size) {
        return this->getCmdSpaceAligned(size, Cal::Utils::defaultAlignmentSize);
    }

    template <typename MessageT>
    void *getCmdSpaceAligned(size_t dynamicSize, size_t alignment) {
        return this->getCmdSpaceAligned(sizeof(MessageT) + dynamicSize, alignment);
    }

    template <typename MessageT>
    void *getCmdSpaceAligned(size_t alignment) {
        return this->getCmdSpaceAligned<MessageT>(0U, alignment);
    }

    template <typename MessageT>
    void *getCmdSpace(size_t dynamicSize) {
        return this->getCmdSpaceAligned<MessageT>(dynamicSize, Cal::Utils::defaultAlignmentSize);
    }

    template <typename MessageT>
    void *getCmdSpace() {
        return this->getCmdSpaceAligned<MessageT>(Cal::Utils::defaultAlignmentSize);
    }

    std::unique_ptr<void, ChannelSpaceDeleter> getStandaloneSpace(size_t size) {
        return this->getStandaloneSpaceAligned(size, Cal::Utils::defaultAlignmentSize);
    }

    template <typename T>
    T *encodeHeapOffsetFromLocalPtr(T *localAddress) {
        return reinterpret_cast<T *>(static_cast<uintptr_t>(Cal::Utils::byteDistanceAbs(shmem, localAddress)));
    }

    CompletionStampT *allocateCompletionStamp() {
        *completionStamp = CompletionStampNotReady;
        return completionStamp;
    }

    bool submitCommand(void *command, Cal::Rpc::RpcMessageHeader::MessageFlagsT messageFlags, CompletionStampT *completionStamp, bool batched) {
        auto commandOffsetWithinRingBuffer = getAsShmemOffset(command);
        auto stampOffsetWithinRingBuffer = completionStamp ? getAsShmemOffset(completionStamp) : Cal::Messages::invalidOffsetWithinChannel;

        if (false == ring.push(RingEntry{commandOffsetWithinRingBuffer, stampOffsetWithinRingBuffer}, batched)) {
            ring.wait();

            if (false == ring.push(RingEntry{commandOffsetWithinRingBuffer, stampOffsetWithinRingBuffer}, batched)) {
                ring.flushBatched();
                if (false == ring.push(RingEntry{commandOffsetWithinRingBuffer, stampOffsetWithinRingBuffer}, batched)) {
                    ring.wait();

                    if (false == ring.push(RingEntry{commandOffsetWithinRingBuffer, stampOffsetWithinRingBuffer}, batched)) {
                        if (false == ring.push(RingEntry{commandOffsetWithinRingBuffer, stampOffsetWithinRingBuffer}, false)) {
                            log<Verbosity::critical>("Could not add command to ring");
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    void freeSpace(void *ptr) {
        standaloneHeap.free(ptr);
    }

    void callAsynchronous(Cal::Rpc::RpcMessageHeader *command, bool batched) {
        if (batched) {
            command->flags |= Cal::Rpc::RpcMessageHeader::batched;
        }

        auto ret = this->submitCommand(command, command->flags, nullptr, batched);

        if (!ret) {
            log<Verbosity::critical>("Asynchronous call failed");
        }

        if (!batched) {
            if (Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores == serviceSynchronizationMethod) {
                if (false == this->signalServiceSemaphore()) {
                    log<Verbosity::critical>("Failed to signal service with new RPC call");
                }
            }
        }

        log<Verbosity::bloat>("Successful asynchronous call");
    }

    bool callSynchronous(Cal::Rpc::RpcMessageHeader *command) {
        *completionStamp = CompletionStampNotReady;
        auto ret = this->submitCommand(command, command->flags, completionStamp, false);
        if (!ret) {
            log<Verbosity::critical>("Synchronous call failed");
            return false;
        }
        if (Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores == serviceSynchronizationMethod) {
            if (false == this->signalServiceSemaphore()) {
                log<Verbosity::critical>("Failed to signal service with new RPC call");
                return false;
            }
        }
        auto messageFlags = command->flags;
        if (false == wait(completionStamp, messageFlags)) {
            log<Verbosity::critical>("Failed to get response for RPC call");
            return false;
        }
        this->cmdHeap.free();
        log<Verbosity::bloat>("Successful synchronous call");
        return true;
    }

    template <typename MessageT>
    bool callSynchronous(MessageT *command) {
        return callSynchronous(&command->header);
    }

    template <typename MessageT>
    void callAsynchronous(MessageT *command) {
        callAsynchronous(&command->header, (MessageT::category == CallCategory::Copy) && this->useBatchedCalls);
    }

    int32_t getId() const {
        return underlyingShmem.getShmemId();
    }

    bool wait(CompletionStampT *completionStamp, Cal::Rpc::RpcMessageHeader::MessageFlagsT messageFlags) {
        if (0 != (messageFlags & Cal::Rpc::RpcMessageHeader::FlagsBits::signalSemaphoreOnCompletion)) {
            return semaphoreWait(completionStamp);
        } else {
            return activeWait(completionStamp);
        }
    }

    void stop() {
        stopped = true;
    }

    bool shouldSynchronizeNextCommandWithSemaphores(float commandLatency) {
        return commandLatency > semaphoreWaitThreshold;
    }

    bool isUsingSharedVaForRpcChannel() const {
        return usesSharedVaForRpcChannel;
    }

    Cal::Rpc::MemChunk acquireHostptrCopiesUpdate() {
        if (hostptrCopiesRing.peekEmpty()) {
            return {nullptr, 0u};
        }

        Cal::Rpc::MemChunk locationToUpdate = *this->hostptrCopiesRing.peekHead();
        this->hostptrCopiesRing.pop();

        return locationToUpdate;
    }

    bool isCallAsyncEnabled() {
        return this->useAsyncCalls;
    }

  protected:
    bool semaphoreWait(CompletionStampT *completionStamp) {
        log<Verbosity::bloat>("Waiting for packet to be processed - semaphores");
        this->waitOnClientSemaphore();
        if (stopped) {
            log<Verbosity::debug>("Aborting wait for command packet request");
            return {};
        }
        if (__atomic_load_n(completionStamp, __ATOMIC_RELAXED) == CompletionStampNotReady) {
            log<Verbosity::error>("Command not processed after woken up from semaphore wait");
            while (__atomic_load_n(completionStamp, __ATOMIC_RELAXED) == CompletionStampNotReady) {
                if (stopped) {
                    log<Verbosity::debug>("Aborting wait for command to be processed");
                    return false;
                }
            }
        }

        log<Verbosity::bloat>("Packet has been processed");
        return true;
    }

    bool activeWait(CompletionStampT *completionStamp) {
        log<Verbosity::bloat>("Waiting for packet to be processed - active wait");

        while (__atomic_load_n(completionStamp, __ATOMIC_RELAXED) == CompletionStampNotReady) {
            if (stopped) {
                log<Verbosity::debug>("Aborting wait for command to be processed");
                return false;
            }
        }

        log<Verbosity::bloat>("Packet has been processed");
        return true;
    }

    bool createRingBuffer() {
        auto remoteShmem = Cal::Ipc::allocateShmemOnRemote(this->connection, Cal::Messages::ReqAllocateShmem::rpcMessageChannel, 0U, usesSharedVaForRpcChannel); // let service choose size
        if (false == remoteShmem.isValid()) {
            log<Verbosity::debug>("Failed to allocate RPC ring buffer shmem on the service side");
            return false;
        }
        if (usesSharedVaForRpcChannel) {
            this->underlyingShmem = sharedVaShmemImporter.open(remoteShmem);
        } else {
            this->underlyingShmem = globalShmemImporter.open(remoteShmem);
        }
        if (nullptr == underlyingShmem.getMmappedPtr()) {
            log<Verbosity::debug>("Failed to map RPC ring buffer shmem on client side");
            return false;
        }
        log<Verbosity::debug>("Succesfully allocated RPC ring buffer shmem : %p, size : %zu", underlyingShmem.getMmappedPtr(), underlyingShmem.getMmappedSize());

        if (false == this->partition(underlyingShmem.getMmappedPtr(), underlyingShmem.getMmappedSize(), true, this->useAsyncCalls)) {
            log<Verbosity::error>("Failed to partition the RPC ring buffer");
            return false;
        }

        return true;
    }

    bool enableRpc() {
        Cal::Messages::ReqLaunchRpcShmemRingBuffer request;
        request.ringbufferShmemId = underlyingShmem.getShmemId();
        request.layout = this->layout;

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
    Cal::Ipc::ShmemImporter &globalShmemImporter;
    Cal::Usm::UsmShmemImporter &sharedVaShmemImporter;
    bool usesSharedVaForRpcChannel = false;
    Cal::Ipc::ShmemImporter::AllocationT underlyingShmem;
    std::atomic_bool stopped = false;

    bool useAsyncCalls = false;
    bool useBatchedCalls = false;
    CompletionStampT *completionStamp;
    Cal::Allocators::LinearAllocator cmdHeap;
    Cal::Allocators::AddressRangeAllocator standaloneHeap;

    Cal::Messages::RespLaunchRpcShmemRingBuffer::ServiceSynchronizationMethod serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::unknown;
    ClientSynchronizationMethod clientSynchronizationMethod = unknown;
    float semaphoreWaitThreshold = 0.0f;
};

class ChannelServer : public CommandsChannel {
  public:
    struct CommandPacket {
        void *command = nullptr;
        size_t commandMaxSize = 0U;
        CompletionStampT *completionStamp = nullptr;
    };

    ChannelServer(Cal::Ipc::Connection &connection, Cal::Ipc::NonUsmMmappedShmemAllocator &shmemAllocator)
        : connection(connection), shmemAllocator(shmemAllocator) {
    }

    bool init(Cal::Ipc::MmappedShmemAllocationT ringBufferShmem, const Cal::Messages::ReqLaunchRpcShmemRingBuffer &request, Cal::Messages::RespLaunchRpcShmemRingBuffer::ServiceSynchronizationMethod serviceSynchronizationMethod) {
        log<Verbosity::debug>("ChannelServer - new client : %d; service synchronization method %s", connection.getId(),
                              Cal::Messages::RespLaunchRpcShmemRingBuffer::asCStr(serviceSynchronizationMethod));
        this->serviceSynchronizationMethod = serviceSynchronizationMethod;

        if (false == this->partition(ringBufferShmem.getMmappedPtr(), ringBufferShmem.getMmappedSize(), request.layout, false)) {
            log<Verbosity::error>("ChannelServer - failed to partition RPC ring buffer using layout provided by client : %d", connection.getId());
            return false;
        }

        this->ringBufferShmem = ringBufferShmem;
        return true;
    }

    int32_t getId() const {
        return ringBufferShmem.getShmemId();
    }

    CommandPacket wait(bool yieldThread) {
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
        log<Verbosity::debug>("Stoping RPC channel at iteration:%zu, head:%zu, tail:%zu, capacity:%zu",
                              this->ring.peekIteration(), this->ring.peekHeadOffset(), this->ring.peekTailOffset(), this->ring.getCapacity());
        stopped = true;
        if (Cal::Messages::RespLaunchRpcShmemRingBuffer::semaphores == serviceSynchronizationMethod) {
            this->signalServiceSemaphore();
        }
    }

    void signalCompletion(CompletionStampT *completionStamp, Cal::Rpc::RpcMessageHeader::MessageFlagsT messageFlags) {
        __atomic_store_n(completionStamp, CompletionStampReady, __ATOMIC_RELAXED);
        if (0 != (messageFlags & Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion)) {
            this->signalClientSemaphore();
        }
    }

    template <typename T>
    T *decodeLocalPtrFromHeapOffset(T *heapOffset) {
        return reinterpret_cast<T *>(Cal::Utils::moveByBytes(shmem, reinterpret_cast<uintptr_t>(heapOffset)));
    }

    bool pushHostptrCopyToUpdate(Cal::Rpc::MemChunk memChunk) {
        if (false == hostptrCopiesRing.push(memChunk, false)) {
            log<Verbosity::critical>("Could not add memChunk copy update notification to ring");
            return false;
        }

        return true;
    }

  protected:
    CommandPacket activeWait(bool yieldThread) {
        log<Verbosity::bloat>("Waiting for new command packet request - active polling");
        while (ring.peekEmpty()) {
            if (yieldThread) {
                std::this_thread::yield();
            }
            if (stopped) {
                log<Verbosity::debug>("Aborting wait for command packet request");
                return {};
            }
        }
        log<Verbosity::bloat>("New command packet request arrived");
        RingEntry newRequest = *this->ring.peekHead();
        this->ring.pop();

        return CommandPacket{getAsLocalAddress(newRequest.messageOffset), static_cast<size_t>(this->layout.heapEnd - newRequest.messageOffset),
                             newRequest.completionStampOffset == Cal::Messages::invalidOffsetWithinChannel ? nullptr : getAsLocalAddress<CompletionStampT>(newRequest.completionStampOffset)};
    }

    CommandPacket semaphoreWait() {
        log<Verbosity::bloat>("Waiting for new command packet request - semaphores");
        while (ring.peekEmpty()) {
            this->waitOnServiceSemaphore();
            if (stopped) {
                log<Verbosity::debug>("Aborting wait for command packet request");
                return {};
            }
        }

        log<Verbosity::bloat>("New commaned packet request arrived");
        RingEntry newRequest = *this->ring.peekHead();
        this->ring.pop();

        return CommandPacket{getAsLocalAddress(newRequest.messageOffset), static_cast<size_t>(this->layout.heapEnd - newRequest.messageOffset),
                             newRequest.completionStampOffset == Cal::Messages::invalidOffsetWithinChannel ? nullptr : getAsLocalAddress<CompletionStampT>(newRequest.completionStampOffset)};
    }

    Cal::Ipc::Connection &connection;
    Cal::Ipc::NonUsmMmappedShmemAllocator &shmemAllocator;
    Cal::Ipc::MmappedShmemAllocationT ringBufferShmem;
    std::atomic_bool stopped = false;
    Cal::Messages::RespLaunchRpcShmemRingBuffer::ServiceSynchronizationMethod serviceSynchronizationMethod = Cal::Messages::RespLaunchRpcShmemRingBuffer::unknown;
};

} // namespace Rpc

} // namespace Cal
