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

namespace Cal::Mocks {

class MockShmemManager {
  public:
    ~MockShmemManager() {
        EXPECT_EQ(0u, allocatedShmems.size()) << "Shmems have been leaked!";
    }

    Cal::Ipc::Shmem get(const Cal::Ipc::RemoteShmem &remoteShmem, void *enforcedVaForMapping) {
        return {};
    }

    Cal::Ipc::Shmem get(size_t size, bool dontMap) {
        constexpr auto pageSize = Cal::Utils::pageSize4KB;
        const auto alignedSize = Cal::Utils::alignUpPow2<pageSize>(size);

        Cal::Ipc::Shmem shmem{};

        shmem.id = idToReturn++;
        shmem.fd = fdToReturn++;
        shmem.owned = true;
        shmem.size = size;
        shmem.underlyingSize = alignedSize;

        if (!dontMap) {
            shmem.ptr = Cal::Sys::mmap(nullptr, alignedSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmem.fd, 0);
        }

        allocatedShmems[shmem.id] = shmem;
        return shmem;
    }

    void release(const Cal::Ipc::Shmem &shmem) {
        const auto it = allocatedShmems.find(shmem.id);
        if (it != allocatedShmems.end()) {
            allocatedShmems.erase(it);
        }

        if (shmem.ptr) {
            Cal::Sys::munmap(shmem.ptr, shmem.underlyingSize);
        }
    }

    std::unique_lock<std::mutex> lock() {
        return std::unique_lock<std::mutex>(criticalSection);
    }

  protected:
    std::map<int, Cal::Ipc::Shmem> allocatedShmems{};
    std::mutex criticalSection;

    int idToReturn{0};
    int fdToReturn{7};
};

} // namespace Cal::Mocks
