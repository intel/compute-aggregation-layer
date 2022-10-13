/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "include/cal.h"
#include "shared/allocators.h"
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
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <utility>
#include <vector>

namespace Cal {
namespace Ipc {

static constexpr int invalidShmemId = -1;

inline std::string getCalShmemPathBase(pid_t servicePid) {
    return calShmemPathPrefix.data() + std::to_string(servicePid) + "_";
}

/// Shmem descriptor received from service
struct RemoteShmem {
    size_t size = 0U;        // size of shmem to be mapped
    int id = invalidShmemId; // id of this shmem within CAL
    bool isValid() const {
        return invalidShmemId != id;
    }
};

/// Descriptor of shmem opened in this process
struct Shmem {
    void *ptr = nullptr;        // mapped VA
    size_t size = 0U;           // requested size
    size_t underlyingSize = 0U; // actual size (includes page alignments)
    int id = invalidShmemId;    // id of this shmem within CAL
    int fd = -1;                // opened FD
    bool owned = false;         // true for process that created shmem (not just opened)
    bool isValid() {
        return (invalidShmemId != id) && ((nullptr != ptr) || (fd != -1));
    }
};

// thread-safe
class ShmemAllocator {
  public:
    static constexpr size_t maxShmems = 4096U;

    ShmemAllocator() : shmemIdAllocator(maxShmems) {
    }
    ShmemAllocator(const std::string &path) : basePath(path), shmemIdAllocator(maxShmems) {
    }
    mockable ~ShmemAllocator() = default;

    mockable Shmem create(size_t size, bool dontMap) {
        auto shmemId = shmemIdAllocator.allocate();
        if (Cal::Allocators::BitAllocator::invalidOffset == shmemId) {
            return {};
        }
        auto path = basePath + std::to_string(shmemId);
        log<Verbosity::debug>("Unlinking stale shmem file (if exists) : %s", path.c_str());
        Cal::Sys::shm_unlink(path.c_str());

        int shmemFd = Cal::Sys::shm_open(path.c_str(), O_CREAT | O_EXCL | O_RDWR,
                                         S_IRUSR | S_IWUSR);

        if (-1 == shmemFd) {
            auto err = errno;
            log<Verbosity::error>("Failed to create shmem object for path : %s (errno=%d=%s)", path.c_str(), err, strerror(err));
            return {};
        }
        auto shmemSize = size;
        static constexpr auto pageSize = Cal::Utils::pageSize4KB;
        auto alignedSize = Cal::Utils::alignUpPow2<pageSize>(shmemSize);
        if (-1 == ftruncate(shmemFd, alignedSize)) {
            log<Verbosity::error>("Failed to ftruncate shmem %s to size : %zu", path.c_str(), alignedSize);
            shm_unlink(path.c_str());
            return {};
        }
        void *ptr = nullptr;
        if (dontMap) {
            log<Verbosity::debug>("Created shmem %s of size : %zu and left it unmapped", path.c_str(), alignedSize);
        } else {
            ptr = Cal::Sys::mmap(nullptr, alignedSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmemFd, 0);
            if (ptr == MAP_FAILED) {
                log<Verbosity::error>("Failed to mmap for shmem %s of size : %zu", path.c_str(), alignedSize);
                shm_unlink(path.c_str());
                return {};
            }
            log<Verbosity::debug>("Created shmem %s of size : %zu and mapped it as : %p", path.c_str(), alignedSize, ptr);
        }
        Shmem ret;
        ret.fd = shmemFd;
        ret.ptr = ptr;
        ret.size = shmemSize;
        ret.underlyingSize = alignedSize;
        ret.id = shmemId;
        ret.owned = true;
        return ret;
    }

    mockable void release(const Shmem &shmem) {
        auto path = basePath + std::to_string(shmem.id);

        if ((nullptr != shmem.ptr) && (-1 == Cal::Sys::munmap(shmem.ptr, shmem.underlyingSize))) {
            log<Verbosity::error>("Failed to munmap %p for shmem %s of size : %zu", shmem.ptr, path.c_str(), shmem.underlyingSize);
        } else {
            log<Verbosity::debug>("munmap-ed %p for shmem %s of size : %zu", shmem.ptr, path.c_str(), shmem.underlyingSize);
        }

        if (-1 != shmem.fd) {
            if (-1 == close(shmem.fd)) {
                auto err = errno;
                log<Verbosity::error>("Failed to close shmem FD %d for path : %s (errno=%d=%s)", shmem.fd, path.c_str(), err, strerror(err));
            } else {
                log<Verbosity::debug>("Closed FD %d for shmem %s of size : %zu", shmem.fd, path.c_str(), shmem.underlyingSize);
            }
        }

        if ((-1 != shmem.id) && (-1 == shm_unlink(path.c_str()))) {
            log<Verbosity::error>("Failed to shm_unlink shmem %s of size : %zu", path.c_str(), shmem.underlyingSize);
        } else {
            log<Verbosity::debug>("shm_unlink-ed shmem %s of size : %zu", path.c_str(), shmem.underlyingSize);
            shmemIdAllocator.free(shmem.id);
        }
    }

  protected:
    Cal::Allocators::BitAllocator shmemIdAllocator;
    std::string basePath;
};

// thread-safe
class ShmemImporter {
  public:
    ShmemImporter() = default;
    ShmemImporter(const std::string &path) : basePath(path) {
    }
    mockable ~ShmemImporter() = default;

    mockable Shmem open(const RemoteShmem &remoteShmem, void *enforcedVaForMapping) {
        if (false == remoteShmem.isValid()) {
            log<Verbosity::critical>("Request to open invalid remote shmem ");
            return {};
        }
        auto path = basePath + std::to_string(remoteShmem.id);
        auto shmemSize = remoteShmem.size;
        static constexpr auto pageSize = Cal::Utils::pageSize4KB;
        auto alignedSize = Cal::Utils::alignUpPow2<pageSize>(remoteShmem.size);
        if (enforcedVaForMapping) {
            if (shmemSize != alignedSize) {
                log<Verbosity::error>("Shmem requires fixed pointer : %p but provided size is not page-aligned : %zu", enforcedVaForMapping, remoteShmem.size);
                return {};
            }
            if (false == Cal::Utils::isAlignedPow2<pageSize>(enforcedVaForMapping)) {
                log<Verbosity::error>("Shmem requires fixed pointer : %p but provided pointer is not page-aligned", enforcedVaForMapping);
                return {};
            }
        }
        int shmemFd = Cal::Sys::shm_open(path.c_str(), O_RDWR, 0);
        if (-1 == shmemFd) {
            log<Verbosity::error>("Failed to open shmem object for path : %s", path.c_str());
            return {};
        }
        void *ptr = Cal::Sys::mmap(enforcedVaForMapping, alignedSize, PROT_READ | PROT_WRITE, MAP_SHARED | (enforcedVaForMapping ? MAP_FIXED : 0), shmemFd, 0);
        if (ptr == MAP_FAILED) {
            log<Verbosity::error>("Failed to mmap for shmem %s of size : %zu", path.c_str(), alignedSize);
            shm_unlink(path.c_str());
            return {};
        }
        log<Verbosity::debug>("Created shmem %s of size : %zu and mapped it as %p", path.c_str(), alignedSize, ptr);
        Shmem ret;
        ret.fd = shmemFd;
        ret.ptr = ptr;
        ret.size = shmemSize;
        ret.underlyingSize = alignedSize;
        ret.id = remoteShmem.id;
        return ret;
    }

    mockable void release(const Shmem &shmem) {
        auto path = basePath + std::to_string(shmem.id);

        if ((nullptr != shmem.ptr) && (-1 == Cal::Sys::munmap(shmem.ptr, shmem.underlyingSize))) {
            log<Verbosity::error>("Failed to munmap %p for shmem %s of size : %zu", shmem.ptr, path.c_str(), shmem.underlyingSize);
        } else {
            log<Verbosity::debug>("munmap-ed %p for shmem %s of size : %zu", shmem.ptr, path.c_str(), shmem.underlyingSize);
        }

        if (-1 != shmem.fd) {
            if (-1 == close(shmem.fd)) {
                auto err = errno;
                log<Verbosity::error>("Failed to close shmem FD %d for path : %s (errno=%d=%s)", shmem.fd, path.c_str(), err, strerror(err));
            } else {
                log<Verbosity::debug>("Closed FD %d for shmem %s of size : %zu", shmem.fd, path.c_str(), shmem.underlyingSize);
            }
        }
    }

  protected:
    std::string basePath;
};

inline RemoteShmem allocateShmemOnRemote(Cal::Ipc::Connection &remoteConnection, Cal::Messages::ReqAllocateShmem::AllocationPurpose purpose,
                                         size_t minSize, size_t size) {
    Cal::Messages::ReqAllocateShmem request;
    Cal::Messages::RespAllocateShmem response;
    request.purpose = Cal::Messages::ReqAllocateShmem::rpcMessageChannel;
    request.size = size;
    request.purpose = purpose;
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
    RemoteShmem ret;
    ret.size = response.size;
    ret.id = response.id;
    return ret;
}

class BasicMemoryBlock {
  protected:
    struct ChunkDescription {
        uintptr_t firstPageAddress{}; // First client page VA.
        Shmem shmem{};                // Shmem block.
    };

  public:
    struct MappingDetails {
        int id{};
        size_t realSize{};
        uintptr_t firstClientAddress{};
    };

    BasicMemoryBlock(ShmemAllocator &shmemManager, const void *srcptr, size_t size) : shmemManager{shmemManager} {
        auto &firstChunk = chunks.emplace_back();

        const auto pageOffset = reinterpret_cast<uintptr_t>(srcptr) % pageSize;
        firstChunk.firstPageAddress = reinterpret_cast<uintptr_t>(srcptr) - pageOffset;

        const auto requiredSize = pageOffset + size;
        firstChunk.shmem = shmemManager.create(requiredSize, false);
    }

    ~BasicMemoryBlock() {
        for (const auto &[ptr, size] : oldMappings) {
            if ((ptr != nullptr) && (Cal::Sys::munmap(ptr, size) == -1)) {
                log<Verbosity::error>("Failed to munmap old mapping %p of size : %zu", ptr, size);
            }
        }

        for (const auto &chunk : chunks) {
            shmemManager.release(chunk.shmem);
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
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;

        return overlaps(srcBegin, srcEnd, blockBegin, blockEnd);
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

        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;
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

            auto mappedChunk = Cal::Sys::mmap(destAddress, chunk.shmem.underlyingSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, chunk.shmem.fd, 0);
            if (mappedChunk == MAP_FAILED) {
                log<Verbosity::error>("mmap() failed for chunk! destAddress = %p, size = %zu, fd = %d, id = %d",
                                      destAddress,
                                      chunk.shmem.underlyingSize,
                                      chunk.shmem.fd,
                                      chunk.shmem.id);
            } else {
                chunk.shmem.ptr = mappedChunk;
            }
        }
    }

    void *translate(const void *srcptr) const {
        const auto src = reinterpret_cast<uintptr_t>(srcptr);
        const auto blockBegin = chunks.front().firstPageAddress;
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;

        if (blockBegin <= src && src < blockEnd) {
            const auto mappedBegin = reinterpret_cast<uintptr_t>(chunks.front().shmem.ptr);
            const auto offset = src - blockBegin;

            return reinterpret_cast<void *>(mappedBegin + offset);
        }

        log<Verbosity::error>("Failed to translate srcptr=%p to mapped shared memory! It does not belong to memory block!", srcptr);
        return nullptr;
    }

    void merge(BasicMemoryBlock &&rhs) {
        const auto lhsBegin = chunks.front().firstPageAddress;
        const auto lhsEnd = chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;

        const auto rhsBegin = rhs.chunks.front().firstPageAddress;
        const auto rhsEnd = rhs.chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;

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
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;

        return (srcPageBegin < blockBegin) || (blockEnd < srcEnd);
    }

    size_t getCountOfOverlappingChunks(const void *srcPtr, size_t srcSize) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcPtr);
        const auto srcEnd = srcBegin + srcSize;

        const auto chunkOverlaps = [this, srcBegin, srcEnd](const auto &chunk) {
            const auto chunkBegin = chunk.firstPageAddress;
            const auto chunkEnd = chunkBegin + chunk.shmem.underlyingSize;

            return overlaps(srcBegin, srcEnd, chunkBegin, chunkEnd);
        };

        return std::count_if(chunks.begin(), chunks.end(), chunkOverlaps);
    }

    bool appendOverlappingChunks(const void *srcPtr,
                                 size_t srcSize,
                                 uint32_t &appendedTransfersCount,
                                 Cal::Rpc::ShmemTransferDesc *transferDescs,
                                 uint32_t transferDescsCount) {
        const auto srcBegin = reinterpret_cast<uintptr_t>(srcPtr);
        const auto srcEnd = srcBegin + srcSize;

        for (const auto &chunk : chunks) {
            const auto chunkBegin = chunk.firstPageAddress;
            const auto chunkEnd = chunkBegin + chunk.shmem.underlyingSize;

            if (overlaps(srcBegin, srcEnd, chunkBegin, chunkEnd)) {
                // Not enough space.
                if (appendedTransfersCount >= transferDescsCount) {
                    return false;
                }

                transferDescs[appendedTransfersCount].shmemId = chunk.shmem.id;
                transferDescs[appendedTransfersCount].underlyingSize = chunk.shmem.underlyingSize;

                const auto copyBegin = std::max(chunkBegin, srcBegin);
                const auto copyEnd = std::min(chunkEnd, srcEnd);
                const auto bytesCountToCopy = copyEnd - copyBegin;

                transferDescs[appendedTransfersCount].bytesCountToCopy = bytesCountToCopy;
                transferDescs[appendedTransfersCount].transferStart = copyBegin;

                const auto offset = copyBegin - chunkBegin;
                transferDescs[appendedTransfersCount].offsetFromMapping = offset;

                ++appendedTransfersCount;
            }
        }

        return true;
    }

  protected:
    void prependChunk(uintptr_t blockBegin, uintptr_t srcPageBegin) {
        auto &prependedChunk = chunks.emplace_front();
        prependedChunk.firstPageAddress = srcPageBegin;

        constexpr auto dontMap = true;
        const auto requiredSize = blockBegin - srcPageBegin;
        prependedChunk.shmem = shmemManager.create(requiredSize, dontMap);
    }

    void appendChunk(uintptr_t blockEnd, uintptr_t srcEnd) {
        auto &appendedChunk = chunks.emplace_back();
        appendedChunk.firstPageAddress = blockEnd;

        constexpr auto dontMap = true;
        const auto requiredSize = srcEnd - blockEnd;
        appendedChunk.shmem = shmemManager.create(requiredSize, dontMap);
    }

    void preserveExistingMappings() {
        for (auto &chunk : chunks) {
            if (chunk.shmem.ptr) {
                oldMappings.emplace_back(chunk.shmem.ptr, chunk.shmem.underlyingSize);
                chunk.shmem.ptr = nullptr;
            }
        }
    }

    size_t getTotalContiguousSize() const {
        const auto blockBegin = chunks.front().firstPageAddress;
        const auto blockEnd = chunks.back().firstPageAddress + chunks.back().shmem.underlyingSize;

        return blockEnd - blockBegin;
    }

    bool overlaps(uintptr_t srcBegin, uintptr_t srcEnd, uintptr_t blockBegin, uintptr_t blockEnd) const {
        return (srcBegin <= blockBegin && blockBegin < srcEnd) || (blockBegin <= srcBegin && srcBegin < blockEnd);
    }

    static constexpr auto pageSize{Cal::Utils::pageSize4KB};

    std::deque<ChunkDescription> chunks{};
    std::vector<std::pair<void *, size_t>> oldMappings{};
    ShmemAllocator &shmemManager;
};

template <typename BasicMemoryBlockT = BasicMemoryBlock>
class BasicMemoryBlocksManager {
  protected:
    using MemoryBlockIterator = typename std::map<uintptr_t, BasicMemoryBlockT>::iterator;

  public:
    const BasicMemoryBlockT &registerMemoryBlock(ShmemAllocator &shmemManager, const void *srcptr, size_t size) {
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

        auto [insertedBlockIt, wasInserted] = memoryBlocks.try_emplace(srcPageBegin, shmemManager, srcptr, size);
        assert(wasInserted && "Cannot insert memory block! This should not happen!");

        return (*insertedBlockIt).second;
    }

    bool getCountOfRequiredTransferDescs(uint32_t &transferDescsCount, uint32_t chunksCount, const Cal::Rpc::MemChunk *chunks) {
        transferDescsCount = 0;

        for (uint32_t i = 0; i < chunksCount; ++i) {
            auto memoryBlock = getMemoryBlockWhichIncludesChunk(chunks[i].address, chunks[i].size);
            if (!memoryBlock) {
                log<Verbosity::error>("Could not retrieve memory block, which includes given chunk!");
                return false;
            }

            transferDescsCount += memoryBlock->getCountOfOverlappingChunks(chunks[i].address, chunks[i].size);
        }

        return true;
    }

    bool getRequiredTransferDescs(uint32_t &transferDescsCount,
                                  Cal::Rpc::ShmemTransferDesc *transferDescs,
                                  uint32_t chunksCount,
                                  const Cal::Rpc::MemChunk *chunks) {
        uint32_t appendedTransfersCount{0};

        for (uint32_t i = 0; i < chunksCount; ++i) {
            auto memoryBlock = getMemoryBlockWhichIncludesChunk(chunks[i].address, chunks[i].size);
            if (!memoryBlock) {
                log<Verbosity::error>("Could not retrieve memory block, which includes given chunk!");
                return false;
            }

            const auto enoughtSpace = memoryBlock->appendOverlappingChunks(chunks[i].address,
                                                                           chunks[i].size,
                                                                           appendedTransfersCount,
                                                                           transferDescs,
                                                                           transferDescsCount);
            if (!enoughtSpace) {
                log<Verbosity::error>("Client has not provided enough space for transferDescs!");
                return false;
            }
        }

        transferDescsCount = appendedTransfersCount;
        return true;
    }

  protected:
    BasicMemoryBlockT *getMemoryBlockWhichIncludesChunk(const void *srcptr, size_t size) {
        const auto overlappingBegin = getOverlappingBlocksBegin(srcptr, size);
        if (overlappingBegin == memoryBlocks.end()) {
            log<Verbosity::error>("Queried file descriptors of non-registered chunk!");
            return nullptr;
        }

        const auto overlappingEnd = getOverlappingBlocksEnd(srcptr, size);
        const auto overlappingBlocksCount = std::distance(overlappingBegin, overlappingEnd);
        if (overlappingBlocksCount != 1) {
            log<Verbosity::error>("Number of registered overlapping blocks should be 1! Actual value: %d", static_cast<int>(overlappingBlocksCount));
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
            auto &[firstPageAddress, blockToBeMerged] = entry;
            singleBlock.merge(std::move(blockToBeMerged));
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

        return memoryBlocks.upper_bound(srcEnd);
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
};

using MemoryBlock = BasicMemoryBlock;
using MemoryBlocksManager = BasicMemoryBlocksManager<MemoryBlock>;

} // namespace Ipc
} // namespace Cal
