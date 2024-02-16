/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "boost/container/flat_map.hpp"
#include "include/cal.h"
#include "shared/allocators.h"
#include "shared/callstack.h"
#include "shared/control_messages.h"
#include "shared/ipc.h"
#include "shared/shmem_transfer_desc.h"
#include "shared/sys.h"
#include "shared/utils.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <deque>
#include <errno.h>
#include <fcntl.h>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <utility>
#include <vector>

namespace Cal::Ipc {

inline void getCalShmemPathBase(char *buff, size_t bufferSize, pid_t pid) {
    buff[0] = '\0';
    snprintf(buff, bufferSize, "%s%d_", calShmemPathPrefix.data(), pid);
}

inline std::string getCalShmemPathBase(pid_t pid) {
    char path[4096];
    getCalShmemPathBase(path, sizeof(path), pid);
    return path;
}

using ShmemIdT = int;
static constexpr ShmemIdT invalidShmemId = -1;

// thread-safe
template <typename BaseAllocationType = Cal::Allocators::BaseAllocation>
class ShmemAllocation : public BaseAllocationType {
  public:
    static constexpr bool isThreadSafe = true && BaseAllocationType::isThreadSafe;
    static constexpr bool isShmemAllocation = true;
    using BaseT = BaseAllocationType;

    template <typename BaseAllocationTypeInitT>
    ShmemAllocation(BaseAllocationTypeInitT &&baseAllocation, ShmemIdT shmemId, bool isShmemOwner)
        : BaseAllocationType(std::forward<BaseAllocationTypeInitT>(baseAllocation)), shmemId(shmemId), isShmemOwner(isShmemOwner) {
    }

    ShmemAllocation(ShmemIdT shmemId, bool isShmemOwner)
        : shmemId(shmemId), isShmemOwner(isShmemOwner) {
    }

    ShmemAllocation() = default;

    ShmemIdT getShmemId() const {
        return shmemId;
    }

    bool isOwnerOfShmem() const {
        return isShmemOwner;
    }

    bool isValid() const {
        return (invalidShmemId != shmemId) && BaseAllocationType::isValid();
    }

  protected:
    ShmemIdT shmemId = invalidShmemId; // id of this shmem within CAL
    bool isShmemOwner = false;         // true for process that created shmem (not just opened)
};

// thread-safe
using OpenedShmemAllocationT = Cal::Allocators::FdAllocation<ShmemAllocation<>>;
using MmappedShmemAllocationT = Cal::Allocators::MmappedAllocation<OpenedShmemAllocationT>;

using OpenedShmemSubAllocationT = Cal::Allocators::FdSubAllocation<OpenedShmemAllocationT>;
using MmappedShmemSubAllocationT = Cal::Allocators::MmappedAllocation<OpenedShmemSubAllocationT>;

// thread-safe
class ShmemAllocator final {
  public:
    static constexpr size_t maxShmems = 4096U;
    static constexpr bool isThreadSafe = true;
    using AllocationT = OpenedShmemAllocationT;
    static constexpr size_t minAlignment = Cal::Utils::pageSize4KB;

    ShmemAllocator() : shmemIdAllocator(maxShmems) {
    }
    ShmemAllocator(const std::string &path) : shmemIdAllocator(maxShmems), basePath(path) {
    }

    mockable ~ShmemAllocator() = default;

    mockable AllocationT allocate(size_t size, size_t alignment) {
        if (false == Cal::Allocators::adjustSizeAndAlignment<Cal::Utils::pageSize4KB>(size, alignment)) {
            return {};
        }
        auto shmemId = shmemIdAllocator.allocate();
        if (Cal::Allocators::BitAllocator::invalidOffset == shmemId) {
            log<Verbosity::error>("Maximum number of shmems reached : %zu", shmemIdAllocator.getCapacity());
            return {};
        }
        auto path = basePath + std::to_string(shmemId);
        log<Verbosity::debug>("Unlinking stale shmem file (if exists) : %s", path.c_str());
        Cal::Sys::shm_unlink(path.c_str());

        int shmemFd = Cal::Sys::shm_open(path.c_str(), O_CREAT | O_EXCL | O_RDWR,
                                         S_IRUSR | S_IWUSR);

        if (-1 == shmemFd) {
            auto err = errno;
            log<Verbosity::error>("Failed to create shmem for path : %s (errno=%d=%s)", path.c_str(), err, strerror(err));
            return {};
        }
        if (-1 == Cal::Sys::ftruncate(shmemFd, size)) {
            log<Verbosity::error>("Failed to ftruncate shmem %s to size : %zu", path.c_str(), size);
            Cal::Sys::close(shmemFd);
            Cal::Sys::shm_unlink(path.c_str());
            return {};
        }

        return AllocationT(ShmemAllocation<>(shmemId, true), shmemFd, size, true);
    }

    mockable AllocationT allocate(size_t size) {
        return this->allocate(size, minAlignment);
    }

    mockable void free(const AllocationT &alloc) {
        auto path = basePath + std::to_string(alloc.getShmemId());

        if (alloc.isOwnerOfFd()) {
            if (-1 == Cal::Sys::ftruncate(alloc.getFd(), 0)) {
                auto err = errno;
                log<Verbosity::error>("Failed to ftruncate shmem %s to size : 0 (errno=%d=%s)", path.c_str(), err, strerror(err));
            }
            if (-1 == Cal::Sys::close(alloc.getFd())) {
                auto err = errno;
                log<Verbosity::error>("Failed to close shmem FD %d for path : %s (errno=%d=%s)", alloc.getFd(), path.c_str(), err, strerror(err));
            } else {
                log<Verbosity::debug>("Closed FD %d for shmem %s of size : %zu", alloc.getFd(), path.c_str(), alloc.getFileSize());
            }
        }

        if (alloc.isOwnerOfShmem()) {
            if (-1 == Cal::Sys::shm_unlink(path.c_str())) {
                auto err = errno;
                if (err != ENOENT) {
                    log<Verbosity::error>("Failed to shm_unlink shmem %s of size : %zu (errno=%d=%s)", path.c_str(), alloc.getFileSize(), err, strerror(err));
                }
            } else {
                log<Verbosity::debug>("shm_unlink-ed shmem %s of size : %zu", path.c_str(), alloc.getFileSize());
                shmemIdAllocator.free(alloc.getShmemId());
            }
        }
    }

  protected:
    Cal::Allocators::BitAllocator shmemIdAllocator;
    std::string basePath;
};

struct RemoteShmemDesc {
    ShmemIdT id = invalidShmemId;
    size_t offset = 0U;
    size_t size = 0U;
    void *sharedVa = nullptr;

    bool isValid() const {
        return invalidShmemId != this->id;
    }
};

// thread-safe
class ShmemImporter {
  public:
    struct RefCountedFd {
        int fd = -1;
        int refcnt = 0;
    };

    static constexpr bool isThreadSafe = true;

    using AllocationT = MmappedShmemSubAllocationT;

    ShmemImporter() = default;
    ShmemImporter(const std::string &path) : basePath(path) {
        doEarlyUnlink = Cal::Utils::getCalEnvI64(calEarlyShmUnlinkEnvName, true);
    }
    mockable ~ShmemImporter() = default;

    mockable AllocationT open(ShmemIdT id, size_t offset, size_t size, void *enforcedVaForMmap) {
        if (invalidShmemId == id) {
            log<Verbosity::critical>("Request to open invalid remote shmem");
            return {};
        }

        if (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(size)) {
            log<Verbosity::critical>("Request to open misaligned shmem %zu", size);
            return {};
        }

        if (enforcedVaForMmap) {
            if (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(enforcedVaForMmap)) {
                log<Verbosity::critical>("Request to map to misaligned ptr %p", enforcedVaForMmap);
                return {};
            }
        }
        auto path = basePath + std::to_string(id);
        int shmemFd = this->getFileDescriptor(path);
        if (-1 == shmemFd) {
            log<Verbosity::error>("Failed to open shmem object for path : %s", path.c_str());
            return {};
        }
        void *ptr = Cal::Sys::mmap(enforcedVaForMmap, size, PROT_READ | PROT_WRITE, MAP_SHARED | (enforcedVaForMmap ? MAP_FIXED : 0), shmemFd, offset);
        if (ptr == MAP_FAILED) {
            auto err = errno;
            log<Verbosity::error>("Failed to mmap for shmem %s (offset : %zu) of size : %zu (errno=%d=%s)", path.c_str(), offset, size, err, strerror(err));
            Cal::Sys::shm_unlink(path.c_str());
            return {};
        }
        log<Verbosity::debug>("Opened shmem %s (offset : %zu) of size : %zu and mapped it as %p", path.c_str(), offset, size, ptr);
        using namespace Cal::Allocators;
        return AllocationT(OpenedShmemSubAllocationT(OpenedShmemAllocationT(ShmemAllocation<>(id, false), shmemFd, offset + size, true), offset), ptr, size);
    }

    mockable AllocationT open(ShmemIdT id, size_t size, void *enforcedVaForMmap) {
        return this->open(id, 0U, size, enforcedVaForMmap);
    }

    AllocationT open(const RemoteShmemDesc &desc) {
        return this->open(desc.id, desc.offset, desc.size, desc.sharedVa);
    }

    mockable void release(const AllocationT &shmem) {
        auto path = basePath + std::to_string(shmem.getShmemId());

        if (nullptr != shmem.getMmappedPtr()) {
            if (-1 == Cal::Sys::munmap(shmem.getMmappedPtr(), shmem.getMmappedSize())) {
                log<Verbosity::error>("Failed to munmap %p for shmem %s of size : %zu", shmem.getMmappedPtr(), path.c_str(), shmem.getMmappedSize());
            } else {
                log<Verbosity::debug>("munmap-ed %p for shmem %s of size : %zu", shmem.getMmappedPtr(), path.c_str(), shmem.getMmappedSize());
            }
        }

        if (shmem.isOwnerOfFd()) {
            closeFileDescriptor(shmem, path);
        }
    }

    const std::string &getBasePath() {
        return this->basePath;
    }

    int getFileDescriptor(const std::string &path) {
        auto fileMapLock = fileMap.lock();
        int fd = -1;
        auto iter = (*fileMap).find(path);
        if (iter == (*fileMap).end()) {
            fd = Cal::Sys::shm_open(path.c_str(), O_RDWR, 0);
            if (-1 == fd) {
                auto err = errno;
                log<Verbosity::error>("Failed to open shmem for path : %s (errno=%d=%s)", path.c_str(), err, strerror(err));
                return -1;
            }
            log<Verbosity::debug>("Opened shmem for path : %s", path.c_str());
            (*fileMap)[path] = {fd, 1};
            if (doEarlyUnlink) {
                Cal::Sys::shm_unlink(path.c_str());
            }
        } else {
            fd = (*iter).second.fd;
            ++iter->second.refcnt;
        }
        return fd;
    }

    void closeFileDescriptor(const AllocationT &shmem, const std::string &path) {
        auto fileMapLock = fileMap.lock();
        auto iter = (*fileMap).find(path);
        if (iter == (*fileMap).end()) {
            log<Verbosity::debug>("Couldn't find shmem FD %s for path : %s", shmem.getFd(), path.c_str());
            return;
        }
        int fd = (*iter).second.fd;
        if (fd != shmem.getFd()) {
            log<Verbosity::error>("Found incorrect fd %d for path : %s with shmem FD %d", fd, path.c_str(), shmem.getFd());
            return;
        }
        int refcnt = (*iter).second.refcnt;
        if (refcnt <= 0) {
            log<Verbosity::error>("Found incorrect refcnt %d for path : %s with shmem FD %d", fd, path.c_str(), shmem.getFd());
            return;
        }
        if (doEarlyUnlink) {
            --iter->second.refcnt;
        } else {
            if (refcnt == 1) {
                if (-1 == Cal::Sys::close(fd)) {
                    auto err = errno;
                    log<Verbosity::error>("Failed to close shmem FD %d for path : %s (errno=%d=%s)", fd, path.c_str(), err, strerror(err));
                    return;
                }
                log<Verbosity::debug>("Closed FD %d for shmem %s of size : %zu", fd, path.c_str(), shmem.getMmappedSize());
                (*fileMap).erase(path);
            } else {
                --iter->second.refcnt;
            }
        }
    }

  protected:
    std::string basePath;
    Cal::Utils::Lockable<std::unordered_map<std::string, RefCountedFd>> fileMap{};
    bool doEarlyUnlink = false;
};

inline RemoteShmemDesc allocateShmemOnRemote(Cal::Ipc::Connection &remoteConnection,
                                             Cal::Messages::ReqAllocateShmem::AllocationPurpose purpose,
                                             size_t minSize, bool useSharedVa) {
    auto alignedSize = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(minSize);
    Cal::Messages::ReqAllocateShmem request;
    Cal::Messages::RespAllocateShmem response;
    request.purpose = Cal::Messages::ReqAllocateShmem::rpcMessageChannel;
    request.size = alignedSize;
    request.purpose = purpose;
    request.sharedVa = useSharedVa;
    {
        auto lock = remoteConnection.lock();
        log<Verbosity::debug>("Sending request for shmem to service (purpose : %s, size : %zu)", request.purposeStr(), request.size);
        if (false == remoteConnection.send(request)) {
            log<Verbosity::error>("Failed to send request for shmem (purpose : %s, size : %zu)", request.purposeStr(), request.size);
            return {};
        }
        if ((false == remoteConnection.receive(response)) || response.isInvalid()) {
            log<Verbosity::error>("Invalid response from service for shmem (purpose : %s, size : %zu)", request.purposeStr(), request.size);
            return {};
        }
        log<Verbosity::debug>("Returned shmem from service : (id : %d, size : %zu)", response.id, response.size);
    }

    RemoteShmemDesc ret;
    ret.id = response.id;
    ret.offset = 0U;
    ret.size = response.size;
    ret.sharedVa = response.sharedVa;
    return ret;
}

// thread-safe
using NonUsmMmappedShmemAllocatorBaseT = Cal::Allocators::AllocatorWithGlobalMmapToFd<Cal::Ipc::ShmemAllocator, true>;
class NonUsmMmappedShmemAllocator : public NonUsmMmappedShmemAllocatorBaseT {
  public:
    static_assert(NonUsmMmappedShmemAllocatorBaseT::isThreadSafe);

    static constexpr Cal::Allocators::MmapConfig mmapConfig = {
        PROT_READ | PROT_WRITE, // prot
        MAP_SHARED              // flags;
    };

    NonUsmMmappedShmemAllocator(ShmemAllocator &shmemAllocator)
        : NonUsmMmappedShmemAllocatorBaseT(shmemAllocator, mmapConfig) {
    }
};

// thread-safe
using NonUsmMmappedShmemArenaAllocatorBaseT = Cal::Allocators::ArenaAllocator<NonUsmMmappedShmemAllocator, false>;
class NonUsmMmappedShmemArenaAllocator : public NonUsmMmappedShmemArenaAllocatorBaseT {
  public:
    static_assert(NonUsmMmappedShmemArenaAllocatorBaseT::isThreadSafe);

    NonUsmMmappedShmemArenaAllocator(ShmemAllocator &shmemAllocator)
        : NonUsmMmappedShmemArenaAllocatorBaseT(NonUsmMmappedShmemAllocator(shmemAllocator), Cal::Utils::MB * 64) {
    }
};

// thread-safe
class GlobalShmemAllocators {
  public:
    static_assert(Cal::Ipc::ShmemAllocator::isThreadSafe);
    static_assert(Cal::Ipc::NonUsmMmappedShmemArenaAllocator::isThreadSafe);
    static constexpr bool isThreadSafe = true;

    using NonUsmShmemAllocationT = Cal::Ipc::NonUsmMmappedShmemAllocator::AllocationT;
    using NonUsmShmemArenaAllocationT = Cal::Ipc::NonUsmMmappedShmemArenaAllocator::AllocationT;

    GlobalShmemAllocators(const std::string &basePath)
        : baseAllocator(basePath), nonUsmMmappedShmemAllocator(baseAllocator), nonUsmMmappedShmemArenaAllocator(baseAllocator) {
    }

    Cal::Ipc::ShmemAllocator &getBaseAllocator() {
        return baseAllocator;
    }

    Cal::Ipc::NonUsmMmappedShmemAllocator &getNonUsmMmappedAllocator() {
        return nonUsmMmappedShmemAllocator;
    }

    Cal::Ipc::NonUsmMmappedShmemArenaAllocator &getNonUsmMmappedArenaAllocator() {
        return nonUsmMmappedShmemArenaAllocator;
    }

  protected:
    ShmemAllocator baseAllocator;
    NonUsmMmappedShmemAllocator nonUsmMmappedShmemAllocator;
    NonUsmMmappedShmemArenaAllocator nonUsmMmappedShmemArenaAllocator;
};

class BasicMemoryBlock {
  protected:
    class RemmapableShmemAllocation : public MmappedShmemAllocationT {
      public:
        RemmapableShmemAllocation &operator=(const MmappedShmemAllocationT &rhs) {
            this->MmappedShmemAllocationT::operator=(rhs);
            return *this;
        }
        RemmapableShmemAllocation &operator=(const OpenedShmemAllocationT &rhs) {
            this->OpenedShmemAllocationT::operator=(rhs);
            this->mmappedPtr = nullptr;
            this->mmappedSize = 0U;
            return *this;
        }
        void remap(void *va, size_t size) {
            this->mmappedPtr = va;
            this->mmappedSize = size;
            if (static_cast<bool>(va) != static_cast<bool>(size)) {
                log<Verbosity::error>("Invalid remap as va=%p and size=%zu", va, size);
            }
        }
    };
    struct ChunkDescription {
        uintptr_t firstPageAddress{};      // First client page VA.
        RemmapableShmemAllocation shmem{}; // Shmem block.
    };

  public:
    struct MappingDetails {
        int id{};
        size_t realSize{};
        uintptr_t firstClientAddress{};
    };

    BasicMemoryBlock(NonUsmMmappedShmemAllocator &shmemAllocator, const void *srcptr, size_t size) : shmemAllocator{shmemAllocator} {
        auto &firstChunk = chunks.emplace_back();

        const auto pageOffset = reinterpret_cast<uintptr_t>(srcptr) % pageSize;
        firstChunk.firstPageAddress = reinterpret_cast<uintptr_t>(srcptr) - pageOffset;

        const auto requiredSize = pageOffset + size;
        firstChunk.shmem = shmemAllocator.allocate(requiredSize);
    }

    ~BasicMemoryBlock() {
        for (const auto &[ptr, size] : oldMappings) {
            if ((ptr != nullptr) && (Cal::Sys::munmap(ptr, size) == -1)) {
                log<Verbosity::error>("Failed to munmap old mapping %p of size : %zu", ptr, size);
            }
        }

        for (const auto &chunk : chunks) {
            shmemAllocator.free(chunk.shmem);
        }
    }

    BasicMemoryBlock(const BasicMemoryBlock &other) = delete;
    BasicMemoryBlock &operator=(const BasicMemoryBlock &other) = delete;
    BasicMemoryBlock(BasicMemoryBlock &&other) = delete;
    BasicMemoryBlock &operator=(BasicMemoryBlock &&) = delete;

    bool overlapsPages(const void *srcptr, size_t size) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcptr);
        const auto srcEnd = srcBegin + size;

        const auto blockBegin = chunks.front().firstPageAddress;
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();

        return overlaps(srcBegin, srcEnd, blockBegin, blockEnd);
    }

    auto getBlockStartAddress() const {
        return chunks.front().firstPageAddress;
    }

    auto getBlockEndAddress() const {
        return chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();
    }

    void extendBlockIfRequired(const void *srcptr, size_t size) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcptr);
        const auto srcEnd = srcBegin + size;

        const auto pageOffset = reinterpret_cast<uintptr_t>(srcptr) % pageSize;
        const auto srcPageBegin = srcBegin - pageOffset;

        bool shouldRemapChunks{false};
        const auto blockBegin = chunks.front().firstPageAddress;
        if (srcPageBegin < blockBegin) {
            prependChunk(blockBegin, srcPageBegin);
            shouldRemapChunks = true;
        }

        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();
        if (blockEnd < srcEnd) {
            appendChunk(blockEnd, srcEnd);
            shouldRemapChunks = true;
        }

        if (shouldRemapChunks) {
            remapChunksAsContiguousMemory();
        }
    }

    void remapChunksAsContiguousMemory() {
        // 1. Existing mappings must be preserved, because previous zeCommandListAppendMemoryCopy() can use it.
        preserveExistingMappings();

        // 2. Contiguous address space is obtained via MAP_ANONYMOUS.
        const auto totalSize{getTotalContiguousSize()};
        auto mappedSpace = Cal::Sys::mmap(nullptr, totalSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (mappedSpace == MAP_FAILED) {
            log<Verbosity::error>("mmap() failed! Could not obtain contiguous address space of size %zu!", totalSize);
            return;
        }

        // 3. When MAP_FIXED flag is specified and addresses overlap previously mapped pages, then old pages are replaced.
        const auto mappedSpaceBegin = reinterpret_cast<uintptr_t>(mappedSpace);
        const auto blockBegin = chunks.front().firstPageAddress;

        for (auto &chunk : chunks) {
            const auto offsetToFirstPage = chunk.firstPageAddress - blockBegin;
            auto destAddress = reinterpret_cast<void *>(mappedSpaceBegin + offsetToFirstPage);

            auto mappedChunk = Cal::Sys::mmap(destAddress, chunk.shmem.getFileSize(), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, chunk.shmem.getFd(), 0);
            if (mappedChunk == MAP_FAILED) {
                log<Verbosity::error>("mmap() failed for chunk! destAddress = %p, size = %zu, fd = %d, id = %d",
                                      destAddress,
                                      chunk.shmem.getFileSize(),
                                      chunk.shmem.getFd(),
                                      chunk.shmem.getShmemId());
            } else {
                chunk.shmem.remap(mappedChunk, chunk.shmem.getFileSize());
            }
        }
    }

    void *translate(const void *srcptr) const {
        const auto src = reinterpret_cast<uintptr_t>(srcptr);
        const auto blockBegin = chunks.front().firstPageAddress;
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();

        if (blockBegin <= src && src < blockEnd) {
            const auto mappedBegin = reinterpret_cast<uintptr_t>(chunks.front().shmem.getMmappedPtr());
            const auto offset = src - blockBegin;

            return reinterpret_cast<void *>(mappedBegin + offset);
        }

        log<Verbosity::error>("Failed to translate srcptr=%p to mapped shared memory! It does not belong to memory block!", srcptr);
        return nullptr;
    }

    void merge(BasicMemoryBlock &&rhs) {
        const auto lhsEnd = chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();
        const auto rhsBegin = rhs.chunks.front().firstPageAddress;

        assert(lhsEnd <= rhsBegin && "Logic error! Currently only greater rhs can be merged!");

        const auto requiresFillingHoleBetween = (lhsEnd != rhsBegin);
        if (requiresFillingHoleBetween) {
            appendChunk(lhsEnd, rhsBegin);
        }

        chunks.insert(chunks.end(),
                      std::make_move_iterator(rhs.chunks.begin()),
                      std::make_move_iterator(rhs.chunks.end()));

        oldMappings.insert(oldMappings.end(),
                           std::make_move_iterator(rhs.oldMappings.begin()),
                           std::make_move_iterator(rhs.oldMappings.end()));

        rhs.chunks.clear();
        rhs.oldMappings.clear();
    }

    uintptr_t getFirstPageAddress() const {
        return chunks.front().firstPageAddress;
    }

    bool requiresExtension(const void *srcptr, size_t size) const {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcptr);
        const auto srcEnd = srcBegin + size;

        const auto pageOffset = reinterpret_cast<uintptr_t>(srcptr) % pageSize;
        const auto srcPageBegin = srcBegin - pageOffset;

        const auto blockBegin = chunks.front().firstPageAddress;
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();

        return (srcPageBegin < blockBegin) || (blockEnd < srcEnd);
    }

    size_t getCountOfOverlappingChunks(const void *srcPtr, size_t srcSize) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcPtr);
        const auto srcEnd = srcBegin + srcSize;

        const auto chunkOverlaps = [this, srcBegin, srcEnd](const auto &chunk) {
            const auto chunkBegin = chunk.firstPageAddress;
            const auto chunkEnd = chunkBegin + chunk.shmem.getFileSize();

            return overlaps(srcBegin, srcEnd, chunkBegin, chunkEnd);
        };

        return std::count_if(chunks.begin(), chunks.end(), chunkOverlaps);
    }

    bool appendOverlappingChunks(const void *srcPtr,
                                 size_t srcSize,
                                 uint32_t &appendedTransfersCount,
                                 Cal::Rpc::TransferDesc *transferDescs,
                                 uint32_t transferDescsCount) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcPtr);
        const auto srcEnd = srcBegin + srcSize;

        for (const auto &chunk : chunks) {
            const auto chunkBegin = chunk.firstPageAddress;
            const auto chunkEnd = chunkBegin + chunk.shmem.getFileSize();

            if (overlaps(srcBegin, srcEnd, chunkBegin, chunkEnd)) {
                // Not enough space.
                if (appendedTransfersCount >= transferDescsCount) {
                    return false;
                }

                transferDescs[appendedTransfersCount].shmemId = chunk.shmem.getShmemId();
                transferDescs[appendedTransfersCount].underlyingSize = chunk.shmem.getFileSize();

                const auto copyBegin = std::max(chunkBegin, srcBegin);
                const auto copyEnd = std::min(chunkEnd, srcEnd);
                const auto bytesCountToCopy = copyEnd - copyBegin;

                transferDescs[appendedTransfersCount].bytesCountToCopy = bytesCountToCopy;
                transferDescs[appendedTransfersCount].clientAddress = copyBegin;

                const auto offset = copyBegin - chunkBegin;
                transferDescs[appendedTransfersCount].offsetFromResourceStart = offset;

                ++appendedTransfersCount;
            }
        }

        return true;
    }

  protected:
    void prependChunk(uintptr_t blockBegin, uintptr_t srcPageBegin) {
        auto &prependedChunk = chunks.emplace_front();
        prependedChunk.firstPageAddress = srcPageBegin;

        const auto requiredSize = blockBegin - srcPageBegin;
        prependedChunk.shmem = shmemAllocator.getUnderlyingAllocator().allocate(requiredSize);
    }

    void appendChunk(uintptr_t blockEnd, uintptr_t srcEnd) {
        auto &appendedChunk = chunks.emplace_back();
        appendedChunk.firstPageAddress = blockEnd;

        const auto requiredSize = srcEnd - blockEnd;
        appendedChunk.shmem = shmemAllocator.getUnderlyingAllocator().allocate(requiredSize);
    }

    void preserveExistingMappings() {
        for (auto &chunk : chunks) {
            if (chunk.shmem.getMmappedPtr()) {
                oldMappings.emplace_back(chunk.shmem.getMmappedPtr(), chunk.shmem.getFileSize());
                chunk.shmem.remap(nullptr, 0U);
            }
        }
    }

    size_t getTotalContiguousSize() const {
        const auto blockBegin = chunks.front().firstPageAddress;
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.getFileSize();

        return blockEnd - blockBegin;
    }

    bool overlaps(uintptr_t srcBegin, uintptr_t srcEnd, uintptr_t blockBegin, uintptr_t blockEnd) const {
        return (srcBegin <= blockBegin && blockBegin < srcEnd) || (blockBegin <= srcBegin && srcBegin < blockEnd);
    }

    static constexpr auto pageSize{Cal::Utils::pageSize4KB};

    std::deque<ChunkDescription> chunks{};
    std::vector<std::pair<void *, size_t>> oldMappings{};
    NonUsmMmappedShmemAllocator &shmemAllocator;
};

template <typename BasicMemoryBlockT = BasicMemoryBlock>
class BasicMemoryBlocksManager {
  protected:
    using MemoryBlockIterator = typename std::map<uintptr_t, BasicMemoryBlockT>::iterator;

  public:
    const BasicMemoryBlockT &registerMemoryBlock(NonUsmMmappedShmemAllocator &shmemAllocator, const void *srcptr, size_t size) {
        auto *memoryBlock = getMergedOverlappingMemoryBlocks(srcptr, size);
        if (memoryBlock) {
            const auto oldFirstPageAddress = memoryBlock->getFirstPageAddress();
            memoryBlock->extendBlockIfRequired(srcptr, size);

            const auto newFirstPageAddress = memoryBlock->getFirstPageAddress();
            if (oldFirstPageAddress != newFirstPageAddress) {
                updateBeginningAddressInContainer(oldFirstPageAddress, newFirstPageAddress);
            }

            return *memoryBlock;
        }

        const auto srcBegin = reinterpret_cast<uintptr_t>(srcptr);
        const auto pageOffset = reinterpret_cast<uintptr_t>(srcptr) % pageSize;
        const auto srcPageBegin = srcBegin - pageOffset;

        auto [insertedBlockIt, wasInserted] = memoryBlocks.try_emplace(srcPageBegin, shmemAllocator, srcptr, size);
        if (!wasInserted) {
            log<Verbosity::critical>("Could not insert block! Aborting...");
            std::abort();
        }

        return (*insertedBlockIt).second;
    }

    void registerUSMStaging(const void *usmAddress, const size_t size) {
        usmMemoryPairs.emplace(usmAddress, size);
    }

    bool getCountOfRequiredTransferDescs(uint32_t &transferDescsCount, uint32_t chunksCount, const Cal::Rpc::MemChunk *chunks) {
        transferDescsCount = 0;

        for (uint32_t i = 0; i < chunksCount; ++i) {
            auto memoryBlock = getMemoryBlockWhichIncludesChunk(chunks[i].address, chunks[i].size);
            if (memoryBlock) {
                transferDescsCount += memoryBlock->getCountOfOverlappingChunks(chunks[i].address, chunks[i].size);
                continue;
            } else {
                bool foundAsUSM{false};
                for (auto &pair : usmMemoryPairs) {
                    if (pair.first == chunks[i].address) {
                        transferDescsCount++;
                        foundAsUSM = true;
                        break;
                    }
                }
                if (foundAsUSM) {
                    continue;
                }
            }

            log<Verbosity::error>("Could not retrieve memory block, which includes given chunk!");
            return false;
        }

        return true;
    }

    inline void fillTransferDescFromUsmPair(Cal::Rpc::TransferDesc &transferDesc, std::pair<const void *, size_t> &usmMemoryPair) {
        transferDesc.offsetFromResourceStart = reinterpret_cast<uint64_t>(usmMemoryPair.first);
        transferDesc.bytesCountToCopy = usmMemoryPair.second;
        transferDesc.shmemId = -1;
    }

    bool getRequiredTransferDescs(uint32_t &transferDescsCount,
                                  Cal::Rpc::TransferDesc *transferDescs,
                                  uint32_t chunksCount,
                                  const Cal::Rpc::MemChunk *chunks) {
        uint32_t appendedTransfersCount{0};

        for (uint32_t i = 0; i < chunksCount; ++i) {
            auto memoryBlock = getMemoryBlockWhichIncludesChunk(chunks[i].address, chunks[i].size);
            if (memoryBlock) {
                const auto enoughtSpace = memoryBlock->appendOverlappingChunks(chunks[i].address,
                                                                               chunks[i].size,
                                                                               appendedTransfersCount,
                                                                               transferDescs,
                                                                               transferDescsCount);
                if (!enoughtSpace) {
                    log<Verbosity::error>("Client has not provided enough space for transferDescs!");
                    return false;
                }
                continue;
            } else {
                bool foundAsUSM{false};
                for (auto &pair : usmMemoryPairs) {
                    if (pair.first == chunks[i].address) {
                        fillTransferDescFromUsmPair(transferDescs[appendedTransfersCount], pair);
                        appendedTransfersCount++;
                        usmMemoryPairs.erase(pair.first);
                        foundAsUSM = true;
                        break;
                    }
                }
                if (foundAsUSM) {
                    continue;
                }
            }

            log<Verbosity::error>("Could not retrieve memory block, which includes given chunk!");
            return false;
        }

        transferDescsCount = appendedTransfersCount;
        return true;
    }

    bool getRequiredTransferDescs(Cal::Utils::AddressRange range, std::vector<Cal::Rpc::TransferDesc> &transferDescs) {
        auto memoryBlock = getMemoryBlockWhichIncludesChunk(range.base(), range.size());
        if (!memoryBlock) {
            for (auto &pair : usmMemoryPairs) {
                if (pair.first == range.base()) {
                    fillTransferDescFromUsmPair(transferDescs.emplace_back(), pair);
                    usmMemoryPairs.erase(pair.first);
                    return true;
                }
            }

            log<Verbosity::error>("Could not retrieve memory block, which includes given range!");
            return false;
        }

        uint32_t newTransferDescsCount = memoryBlock->getCountOfOverlappingChunks(range.base(), range.size());
        if (!newTransferDescsCount) {
            log<Verbosity::debug>("Could not retrieve memory block, which includes given chunk!");
        }

        uint32_t prevTransferDescsCount = static_cast<uint32_t>(transferDescs.size());
        transferDescs.resize(prevTransferDescsCount + newTransferDescsCount);
        uint32_t appendedTransfersCount = prevTransferDescsCount;

        const auto enoughSpace = memoryBlock->appendOverlappingChunks(range.base(),
                                                                      range.size(),
                                                                      appendedTransfersCount,
                                                                      transferDescs.data(),
                                                                      transferDescs.size());
        if (!enoughSpace) {
            log<Verbosity::error>("Client has not provided enough space for transferDescs!");
            return false;
        }

        return true;
    }

  protected:
    BasicMemoryBlockT *getMemoryBlockWhichIncludesChunk(const void *srcptr, size_t size) {
        const auto overlappingBegin = getOverlappingBlocksBegin(srcptr, size);
        if (overlappingBegin == memoryBlocks.end()) {
            return nullptr;
        }

        const auto overlappingEnd = getOverlappingBlocksEnd(srcptr, size);
        const auto overlappingBlocksCount = std::distance(overlappingBegin, overlappingEnd);
        if (overlappingBlocksCount != 1) {
            log<Verbosity::error>("Number of registered overlapping blocks should be 1! Actual value: %d", static_cast<int>(overlappingBlocksCount));

            std::stringstream errorMessage;
            errorMessage << "\tRequested chunk: (srcptr = " << reinterpret_cast<uintptr_t>(srcptr) << ", size = " << size << ")\n";
            errorMessage << "\tAvailable memory blocks: \n";

            for (const auto &[keyBeginAddress, block] : memoryBlocks) {
                errorMessage << "\t\tKey: " << keyBeginAddress
                             << "\t Block: (firstAddress = " << block.getBlockStartAddress() << ", lastAddress = " << block.getBlockEndAddress() << ")\n";
            }

            auto errorMessageStr = errorMessage.str();
            log<Verbosity::debug>("State of memory blocks manager: \n%s", errorMessageStr.c_str());

            return nullptr;
        }

        auto &memoryBlock = (*overlappingBegin).second;
        if (memoryBlock.requiresExtension(srcptr, size)) {
            log<Verbosity::error>("Memory chunk is not fully included in the memory block. Extension would be needed!");
            return nullptr;
        }

        return &memoryBlock;
    }

    BasicMemoryBlockT *getMergedOverlappingMemoryBlocks(const void *srcptr, size_t size) {
        if (memoryBlocks.empty()) {
            return nullptr;
        }

        auto blocksToMergeBegin = getOverlappingBlocksBegin(srcptr, size);
        if (blocksToMergeBegin == memoryBlocks.end()) {
            return nullptr;
        }

        auto &singleBlock = (*blocksToMergeBegin).second;
        std::advance(blocksToMergeBegin, 1);

        auto blocksToMergeEnd = getOverlappingBlocksEnd(srcptr, size);
        if (blocksToMergeBegin == blocksToMergeEnd) {
            return &singleBlock;
        }

        std::for_each(blocksToMergeBegin, blocksToMergeEnd, [&singleBlock](auto &entry) {
            singleBlock.merge(std::move(entry.second));
        });

        // The range is now in the single block. Remove empty blocks.
        eraseUnneededBlocks(blocksToMergeBegin, blocksToMergeEnd);

        // Remap merged blocks as single contiguous range.
        // In case of the need for extension we do not remap the blocks,
        // because extension will remap them anyways.
        if (!singleBlock.requiresExtension(srcptr, size)) {
            singleBlock.remapChunksAsContiguousMemory();
        }

        return &singleBlock;
    }

    MemoryBlockIterator getOverlappingBlocksBegin(const void *srcptr, size_t size) {
        if (memoryBlocks.empty()) {
            return memoryBlocks.end();
        }

        auto srcBegin = reinterpret_cast<uintptr_t>(srcptr);
        auto overlappingBegin = memoryBlocks.lower_bound(srcBegin);

        if (overlappingBegin != memoryBlocks.begin()) {
            auto previous = std::prev(overlappingBegin);
            auto &previousMemoryBlock = (*previous).second;

            if (previousMemoryBlock.overlapsPages(srcptr, size)) {
                return previous;
            }
        }

        if (overlappingBegin != memoryBlocks.end()) {
            auto &currentMemoryBlock = (*overlappingBegin).second;

            if (currentMemoryBlock.overlapsPages(srcptr, size)) {
                return overlappingBegin;
            }
        }

        return memoryBlocks.end();
    }

    MemoryBlockIterator getOverlappingBlocksEnd(const void *srcptr, size_t size) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcptr);
        const auto srcEnd = srcBegin + size;

        return memoryBlocks.lower_bound(srcEnd);
    }

    void eraseUnneededBlocks(MemoryBlockIterator first, MemoryBlockIterator last) {
        while (first != last) {
            auto toBeErased = first++;
            memoryBlocks.erase(toBeErased);
        }
    }

    void updateBeginningAddressInContainer(uintptr_t oldFirstPageAddress, uintptr_t newFirstPageAddress) {
        auto node = memoryBlocks.extract(oldFirstPageAddress);
        node.key() = newFirstPageAddress;

        auto ret = memoryBlocks.insert(std::move(node));
        assert(ret.inserted && "Cannot insert memory block! This should not happen!");
    }

    static constexpr auto pageSize{Cal::Utils::pageSize4KB};
    std::map<uintptr_t, BasicMemoryBlockT> memoryBlocks{};
    boost::container::flat_map<const void *, size_t> usmMemoryPairs{};
};

using MemoryBlock = BasicMemoryBlock;
using MemoryBlocksManager = BasicMemoryBlocksManager<MemoryBlock>;

class MallocShmemImporter {
  public:
    MallocShmemImporter() = default;
    MallocShmemImporter(const MallocShmemImporter &) = delete;
    MallocShmemImporter &operator=(const MallocShmemImporter &) = delete;

    ~MallocShmemImporter() {
        if (localBaseAddress) {
            Cal::Sys::munmap(localBaseAddress, capacity);
            localBaseAddress = nullptr;
        }
        if (-1 != fd) {
            Cal::Sys::close(fd);
        }
    }

    bool open(std::string_view path, size_t capacity, uintptr_t exporterBaseAddress) {
        if (-1 != fd) {
            return false; // already opened some resource
        }
        this->exporterBaseAddress = exporterBaseAddress;
        this->capacity = capacity;
        fd = Cal::Sys::shm_open(std::string(path).c_str(), O_RDWR, 0);
        if (-1 == fd) {
            auto err = errno;
            log<Verbosity::error>("Failed to open shmem object for path : %s (errno=%d=%s)", std::string(path).c_str(), err, strerror(err));
            return false;
        }
        localBaseAddress = Cal::Sys::mmap(nullptr, capacity, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
        if (MAP_FAILED == localBaseAddress) {
            localBaseAddress = nullptr;
            Cal::Sys::close(fd);
            fd = -1;
            return false;
        }
        return true;
    }

    void *import(uintptr_t exporterAddress, size_t size, size_t exporterHeapSizeHint) {
        if (exporterAddress < exporterBaseAddress) { // includes translation of NULL to NULL
            return nullptr;
        }
        uintptr_t offset = exporterAddress - exporterBaseAddress;
        size_t requiredHeapSize = Cal::Utils::alignUp<Cal::Utils::pageSize4KB>(offset + size);
        if (exporterHeapSizeHint) {
            requiredHeapSize = exporterHeapSizeHint;
        }

        if (requiredHeapSize > capacity) {
            return nullptr; // invalid operation
        }

        if (offset + size > requiredHeapSize) {
            return nullptr; // invalid operation
        }

        if (offset + size < *importedHeapSize) {
            return Cal::Utils::moveByBytes(localBaseAddress, offset);
        }

        auto growLock = importedHeapSize.lock();
        if (offset + size < *importedHeapSize) {
            return Cal::Utils::moveByBytes(localBaseAddress, offset);
        }

        auto importedEnd = Cal::Utils::moveByBytes(localBaseAddress, *importedHeapSize);
        auto ptr = Cal::Sys::mmap(importedEnd, requiredHeapSize - *importedHeapSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, *importedHeapSize);
        if (MAP_FAILED == ptr) {
            return nullptr;
        }

        *importedHeapSize = requiredHeapSize;
        return Cal::Utils::moveByBytes(localBaseAddress, offset);
    }

    bool isImported(void *ptr) {
        return Cal::Utils::AddressRange(localBaseAddress, capacity).contains(ptr);
    }

    void *getLocalBaseAddress() {
        return localBaseAddress;
    }

  protected:
    int fd = -1;
    uintptr_t exporterBaseAddress = std::numeric_limits<uintptr_t>::max();
    size_t capacity = 0;
    Cal::Utils::Lockable<size_t> importedHeapSize = 0;
    void *localBaseAddress = nullptr;
};

} // namespace Cal::Ipc
