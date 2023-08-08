/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <algorithm>
#include <cstddef>
#include <vector>

template <typename Allocator, typename Deallocator>
class StagingAreaManager {
  public:
    StagingAreaManager() = delete;
    StagingAreaManager(Allocator allocator, Deallocator deallocator) : allocator(allocator), deallocator(deallocator) {}
    ~StagingAreaManager() {
        for (const auto &it : allocations) {
            deallocator(it.first);
        }
        allocations.clear();
    }

    void *allocateStagingArea(size_t size) {
        const auto found = std::find_if(allocations.begin(), allocations.end(), [size](std::pair<void *, size_t> it) {
            return it.second == size;
        });
        if (found != allocations.end()) {
            return found->first;
        }
        return allocator(size);
    }

  protected:
    std::vector<std::pair<void *, size_t>> allocations;

  private:
    Allocator allocator;
    Deallocator deallocator;
};
