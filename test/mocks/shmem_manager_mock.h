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

class MockShmemManager : public Cal::Ipc::ShmemManager {
  public:
    ~MockShmemManager() override {
        EXPECT_EQ(0u, allocatedShmems.size()) << "Shmems have been leaked!";
    }

    Cal::Ipc::Shmem get(const Cal::Ipc::RemoteShmem &remoteShmem, void *enforcedVaForMapping) override {
        if (remoteShmem.isValid() == false) {
            return {};
        }

        remoteShmemsLog.push_back(remoteShmem);
        auto it = allocatedShmems.find(remoteShmem.id);
        if (allocatedShmems.end() == it) {
            return {};
        }

        Cal::Ipc::Shmem shmem = it->second;
        if (enforcedVaForMapping && (enforcedVaForMapping != shmem.ptr)) {
            return {}; // remap unsupported in mocks yet
        }

        shmem.fd = fdToReturn++;
        shmem.owned = false;
        openedShmems[shmem.fd] = shmem;

        return shmem;
    }

    Cal::Ipc::Shmem get(size_t size, bool dontMap) override {
        constexpr auto pageSize = Cal::Utils::pageSize4KB;
        const auto alignedSize = Cal::Utils::alignUpPow2<pageSize>(size);

        Cal::Ipc::Shmem shmem{};

        shmem.id = idToReturn++;
        shmem.fd = fdToReturn++;
        shmem.owned = true;
        shmem.size = size;
        shmem.underlyingSize = alignedSize;

        if (!dontMap) {
            if (allocateRealBackingMemory) {
                shmem.ptr = new (std::align_val_t(pageSize)) char[alignedSize];
            } else {
                shmem.ptr = Cal::Sys::mmap(nullptr, alignedSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmem.fd, 0);
            }
        }

        allocatedShmems[shmem.id] = shmem;
        openedShmems[shmem.fd] = shmem;
        return shmem;
    }

    void release(const Cal::Ipc::Shmem &shmem) override {
        auto it = allocatedShmems.find(shmem.id);
        if (it != allocatedShmems.end()) {
            if (it->second.fd == shmem.fd) {
                allocatedShmems.erase(it);
                if (shmem.ptr) {
                    if (allocateRealBackingMemory) {
                        ::operator delete[](reinterpret_cast<char *>(shmem.ptr), std::align_val_t(Cal::Utils::pageSize4KB));
                    } else {
                        Cal::Sys::munmap(shmem.ptr, shmem.underlyingSize);
                    }
                }
            }
        }

        it = openedShmems.find(shmem.fd);
        if (it != openedShmems.end()) {
            openedShmems.erase(it);
        } else {
            log<Verbosity::error>("MockShmemManager - attempted for free unknown shmem");
        }
    }

    std::map<int, Cal::Ipc::Shmem> allocatedShmems{};
    std::map<int, Cal::Ipc::Shmem> openedShmems{};

    std::vector<Cal::Ipc::RemoteShmem> remoteShmemsLog;

    int idToReturn{0};
    int fdToReturn{7};

    bool allocateRealBackingMemory = false;
};

} // namespace Cal::Mocks
