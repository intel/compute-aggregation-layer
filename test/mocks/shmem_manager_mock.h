/*
 * Copyright (C) 2022 Intel Corporation
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
};

class MmappedShmemAllocationWhiteBox : public Cal::Ipc::MmappedShmemAllocationT {
  public:
    using BaseT = Cal::Ipc::NonUsmMmappedShmemAllocator::AllocationT;

    using BaseT::BaseT;

    using BaseT::isShmemOwner;
    using BaseT::shmemId;

    using BaseT::fd;
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

    Cal::Ipc::ShmemImporter::AllocationT open(Cal::Ipc::ShmemIdT id, size_t size, void *enforcedVaForMmap) override {
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
        openedShmems[shmem.fd] = MmappedShmemAllocationWhiteBox{shmem};

        return shmem;
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
        openedShmems[shmem.getFd()] = MmappedShmemAllocationWhiteBox{shmem};
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
    std::map<int, MmappedShmemAllocationWhiteBox> openedShmems{};

    std::vector<Cal::Ipc::RemoteShmemDesc> remoteShmemsLog;

    int idToReturn{0};
    int fdToReturn{7};

    bool allocateRealBackingMemory = false;
    MockShmemAllocator shmemAllocator;
};

} // namespace Cal::Mocks
