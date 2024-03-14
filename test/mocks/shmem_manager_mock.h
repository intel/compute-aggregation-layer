/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "gtest/gtest.h"
#include "shared/shmem.h"

#include <cstddef>
#include <map>
#include <mutex>
#include <new>

namespace Cal::Mocks {

struct MockFdAllocator {
    using AllocationT = Cal::Allocators::FdAllocation<>;
    static constexpr bool isThreadSafe = true;

    AllocationT allocate(size_t size, size_t alignment) {
        return AllocationT{fdToReturn++, size, true};
    }

    AllocationT allocate(size_t size) {
        return allocate(size, 1);
    }

    void free(const AllocationT &) {
        ++freeCallCount;
    }

    int fdToReturn = 1;
    int freeCallCount = 0;
};

struct MockFdSubAllocator {
    using AllocationT = Cal::Allocators::FdSubAllocation<>;
    static constexpr bool isThreadSafe = true;

    AllocationT allocate(size_t size, size_t alignment) {
        AllocationT ret{Cal::Allocators::FdAllocation<>{fdToReturn, offsetToReturn + size, false}, offsetToReturn};
        offsetToReturn += size;
        return ret;
    }

    void free(const AllocationT &) {
        ++freeCallCount;
    }

    int fdToReturn = 1;
    size_t offsetToReturn = 0;
    int freeCallCount = 0;
};

class ShmemAllocatorWhiteBox : public Cal::Ipc::ShmemAllocator {
  public:
    using Cal::Ipc::ShmemAllocator::basePath;
    using Cal::Ipc::ShmemAllocator::shmemIdAllocator;
    using Cal::Ipc::ShmemAllocator::totalShmemAllocated;
    using Cal::Ipc::ShmemAllocator::totalShmemAvailable;
};

class MmappedShmemAllocationWhiteBox : public Cal::Ipc::MmappedShmemAllocationT {
  public:
    using BaseT = Cal::Ipc::MmappedShmemAllocationT;

    using BaseT::BaseT;

    using BaseT::isShmemOwner;
    using BaseT::shmemId;

    using BaseT::fd;
    using BaseT::fileSize;
    using BaseT::isFdOwner;

    using BaseT::mmappedPtr;
    using BaseT::mmappedSize;
};

class MmappedShmemSubAllocationWhiteBox : public Cal::Ipc::MmappedShmemSubAllocationT {
  public:
    using BaseT = Cal::Ipc::MmappedShmemSubAllocationT;

    using BaseT::BaseT;

    MmappedShmemSubAllocationWhiteBox(const MmappedShmemAllocationWhiteBox &base, size_t offset) {
        this->isShmemOwner = base.isShmemOwner;
        this->shmemId = base.shmemId;

        this->fd = base.fd;
        this->fileSize = base.fileSize;
        this->isFdOwner = base.isFdOwner;
        this->fdOffset = offset;

        this->mmappedPtr = base.mmappedPtr;
        this->mmappedSize = base.mmappedSize;
    }

    MmappedShmemSubAllocationWhiteBox(const Cal::Ipc::MmappedShmemAllocationT &base, size_t offset) {
        this->isShmemOwner = base.isOwnerOfShmem();
        this->shmemId = base.getShmemId();

        this->fd = base.getFd();
        this->fileSize = base.getFileSize();
        this->isFdOwner = base.isOwnerOfFd();
        this->fdOffset = offset;

        this->mmappedPtr = base.getMmappedPtr();
        this->mmappedSize = base.getMmappedSize();
    }

    using BaseT::isShmemOwner;
    using BaseT::shmemId;

    using BaseT::fd;
    using BaseT::fdOffset;
    using BaseT::fileSize;
    using BaseT::isFdOwner;

    using BaseT::mmappedPtr;
    using BaseT::mmappedSize;
};

class MockShmemAllocatorProxy {
  public:
    virtual Cal::Ipc::ShmemAllocator::AllocationT allocateWithoutMmap(size_t size, size_t alignment) = 0;
    virtual void freeWithoutUnmap(const Cal::Ipc::ShmemAllocator::AllocationT &shmem) = 0;
};

class MockShmemAllocator : public Cal::Ipc::ShmemAllocator {
  public:
    MockShmemAllocator(MockShmemAllocatorProxy &proxy) : proxy(proxy) {
    }

    Cal::Ipc::ShmemAllocator::AllocationT allocate(size_t size, size_t alignment) override {
        return proxy.allocateWithoutMmap(size, alignment);
    }

    void free(const Cal::Ipc::ShmemAllocator::AllocationT &shmem) override {
        proxy.freeWithoutUnmap(shmem);
    }

    MockShmemAllocatorProxy &proxy;
};

class MockShmemManager : public Cal::Ipc::NonUsmMmappedShmemAllocator, public Cal::Ipc::ShmemImporter, public MockShmemAllocatorProxy {
  public:
    MockShmemManager() : NonUsmMmappedShmemAllocator(shmemAllocator), shmemAllocator(*this) {
    }

    ~MockShmemManager() override {
        EXPECT_EQ(0u, allocatedShmems.size()) << "Shmems have been leaked!";
    }

    Cal::Ipc::ShmemImporter::AllocationT open(Cal::Ipc::ShmemIdT id, size_t offset, size_t size, void *enforcedVaForMmap) override {
        if (Cal::Ipc::invalidShmemId == id) {
            return {};
        }

        remoteShmemsLog.push_back(Cal::Ipc::RemoteShmemDesc{id, size});
        auto it = allocatedShmems.find(id);
        if (allocatedShmems.end() == it) {
            return {};
        }

        auto shmem = it->second;
        if (enforcedVaForMmap && (enforcedVaForMmap != shmem.getMmappedPtr())) {
            return {}; // remap unsupported in mocks yet
        }

        shmem.fd = fdToReturn++;
        shmem.isFdOwner = true;
        openedShmems[shmem.fd] = MmappedShmemSubAllocationWhiteBox{shmem, offset};

        return openedShmems[shmem.fd];
    }

    Cal::Ipc::NonUsmMmappedShmemAllocator::AllocationT allocate(size_t size, size_t alignment) override {
        return this->allocate(size, alignment, true);
    }

    Cal::Ipc::NonUsmMmappedShmemAllocator::AllocationT allocate(size_t size, size_t alignment, bool mmapPtr) {
        constexpr auto pageSize = Cal::Utils::pageSize4KB;
        const auto alignedSize = Cal::Utils::alignUpPow2<pageSize>(size);

        MmappedShmemAllocationWhiteBox shmem{};

        shmem.shmemId = idToReturn++;
        shmem.isShmemOwner = true;
        shmem.fd = fdToReturn++;
        shmem.isFdOwner = true;
        shmem.fileSize = alignedSize;

        if (mmapPtr) {
            if (allocateRealBackingMemory) {
                shmem.mmappedPtr = new (std::align_val_t(pageSize)) char[alignedSize];
            } else {
                shmem.mmappedPtr = Cal::Sys::mmap(nullptr, alignedSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmem.fd, 0);
            }
        }

        shmem.mmappedSize = alignedSize;

        allocatedShmems[shmem.getShmemId()] = shmem;
        openedShmems[shmem.getFd()] = MmappedShmemSubAllocationWhiteBox{shmem, 0};
        return shmem;
    }

    void release(const Cal::Ipc::ShmemImporter::AllocationT &shmem) override {
        {
            auto it = allocatedShmems.find(shmem.getShmemId());
            if (it != allocatedShmems.end()) {
                if (it->second.fd == shmem.getFd()) {
                    allocatedShmems.erase(it);
                    if (shmem.getMmappedPtr()) {
                        if (allocateRealBackingMemory) {
                            ::operator delete[](reinterpret_cast<char *>(shmem.getMmappedPtr()), std::align_val_t(Cal::Utils::pageSize4KB));
                        } else {
                            Cal::Sys::munmap(shmem.getMmappedPtr(), shmem.getMmappedSize());
                        }
                    }
                }
            }
        }
        {
            auto it = openedShmems.find(shmem.getFd());
            if (it != openedShmems.end()) {
                openedShmems.erase(it);
            } else {
                log<Verbosity::error>("MockShmemManager - attempted for free unknown shmem");
            }
        }
    }

    void free(const Cal::Ipc::NonUsmMmappedShmemAllocator::AllocationT &shmem) override {
        {
            auto it = allocatedShmems.find(shmem.getShmemId());
            if (it != allocatedShmems.end()) {
                if (it->second.fd == shmem.getFd()) {
                    allocatedShmems.erase(it);
                    if (shmem.getMmappedPtr()) {
                        if (allocateRealBackingMemory) {
                            ::operator delete[](reinterpret_cast<char *>(shmem.getMmappedPtr()), std::align_val_t(Cal::Utils::pageSize4KB));
                        } else {
                            Cal::Sys::munmap(shmem.getMmappedPtr(), shmem.getMmappedSize());
                        }
                    }
                }
            }
        }

        {
            auto it = openedShmems.find(shmem.getFd());
            if (it != openedShmems.end()) {
                openedShmems.erase(it);
            } else {
                log<Verbosity::error>("MockShmemManager - attempted for free unknown shmem");
            }
        }
    }

    Cal::Ipc::ShmemAllocator::AllocationT allocateWithoutMmap(size_t size, size_t alignment) override {
        return this->allocate(size, alignment, false);
    }

    void freeWithoutUnmap(const Cal::Ipc::ShmemAllocator::AllocationT &shmem) override {
        this->free(Cal::Ipc::NonUsmMmappedShmemAllocator::AllocationT{shmem, nullptr, 0U});
    }

    Cal::Ipc::ShmemAllocator &getUnderlyingAllocator() override {
        return shmemAllocator;
    }

    std::map<int, MmappedShmemAllocationWhiteBox> allocatedShmems{};
    std::map<int, MmappedShmemSubAllocationWhiteBox> openedShmems{};

    std::vector<Cal::Ipc::RemoteShmemDesc> remoteShmemsLog;

    int idToReturn{0};
    int fdToReturn{7};

    bool allocateRealBackingMemory = false;
    MockShmemAllocator shmemAllocator;
};

template <typename UnderlyingAllocator, bool SharedUnderlyingAllocator = false>
class MockArenaAllocator : public Cal::Allocators::ArenaAllocator<UnderlyingAllocator, SharedUnderlyingAllocator> {
  public:
    using BaseT = Cal::Allocators::ArenaAllocator<UnderlyingAllocator, SharedUnderlyingAllocator>;
    using ThisT = MockArenaAllocator<UnderlyingAllocator, SharedUnderlyingAllocator>;

    using BaseT::BaseT;
    using ArenaT = typename BaseT::ArenaT;

    using BaseT::latestArena;
    using BaseT::recycledArenas;

    ArenaT *peekLatestArena() const override {
        ++apiConfig.peekLatestArena.callCount;
        if (apiConfig.peekLatestArena.returnValue) {
            return apiConfig.peekLatestArena.returnValue.value();
        }
        if (apiConfig.peekLatestArena.impl) {
            return apiConfig.peekLatestArena.impl.value()(*this);
        }
        return BaseT::peekLatestArena();
    }

    mutable struct {
        struct {
            std::optional<ArenaT *> returnValue;
            std::optional<std::function<ArenaT *(const ThisT &arenaAllocator)>> impl;
            uint64_t callCount = 0U;
        } peekLatestArena;
    } apiConfig;
};

} // namespace Cal::Mocks
