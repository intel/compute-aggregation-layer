/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <mutex>
#include <vector>

template <typename Allocator, typename Deallocator>
class StagingAreaManager {
  public:
    struct StagingArea {
        StagingArea(void *ptr, size_t size, bool isInUse) : ptr(ptr), size(size), isInUse(isInUse) {}
        void *ptr{};
        size_t size{};
        bool isInUse{};
    };

    StagingAreaManager() = delete;
    StagingAreaManager(Allocator allocator, Deallocator deallocator) : allocator(allocator), deallocator(deallocator) {}
    ~StagingAreaManager() {
        clearStagingAreaAllocations();
    }

    void clearStagingAreaAllocations() {
        std::lock_guard<std::mutex> lock(mutex);
        for (const auto &it : allocations) {
            deallocator(it.ptr);
        }
        allocations.clear();
    }

    void *allocateStagingArea(size_t size) {
        std::lock_guard<std::mutex> lock(mutex);
        auto found = std::find_if(allocations.begin(), allocations.end(), [size](const auto &it) {
            return (false == it.isInUse) && (it.size == size);
        });
        if (found != allocations.end()) {
            found->isInUse = true;
            return found->ptr;
        }

        auto alloc = allocator(size);
        allocations.emplace_back(alloc, size, true);
        return alloc;
    }

    void releaseStagingArea(void *ptr) {
        std::lock_guard<std::mutex> lock(mutex);
        auto found = std::find_if(allocations.begin(), allocations.end(), [ptr](const auto &it) {
            return it.ptr == ptr;
        });
        if (found != allocations.end()) {
            found->isInUse = false;
        }
    }

    void deallocateStagingArea(void *ptr) {
        std::lock_guard<std::mutex> lock(mutex);
        auto found = std::find_if(allocations.begin(), allocations.end(), [ptr](const auto &it) {
            return it.ptr == ptr;
        });
        if (found != allocations.end()) {
            deallocator(ptr);
            allocations.erase(found);
        }
    }

  protected:
    std::vector<StagingArea> allocations{};

  private:
    std::mutex mutex{};
    Allocator allocator;
    Deallocator deallocator;
};
