/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <shared_mutex>
#include <vector>

namespace Cal::Icd {

struct KernelArgCache {
    struct KernelArgEntry {
        uint64_t arg_index = {};
        size_t arg_size = {};
        const void *arg_value = {};
        char argValues[8] = {};
    };

    std::shared_mutex mtx;
    std::vector<KernelArgEntry> cache;

    auto findCachedKernelArg(uint64_t arg_index, size_t arg_size, const void *arg_value) {
        std::shared_lock lock(this->mtx);
        return std::find_if(this->cache.begin(), this->cache.end(), [&](const KernelArgEntry &cacheElement) {
            if (arg_index == cacheElement.arg_index &&
                arg_size == cacheElement.arg_size) {
                if (cacheElement.arg_size != 0u && arg_value) {
                    if (memcmp(arg_value, cacheElement.argValues, arg_size) == 0) {
                        return true;
                    }
                } else {
                    if (arg_value == cacheElement.arg_value) {
                        return true;
                    }
                }
            }
            return false;
        });
    }

    inline void cacheKernelArg(uint64_t arg_index, size_t arg_size, const void *arg_value) {
        if (arg_size > 8)
            return;

        std::lock_guard<std::shared_mutex> lock(this->mtx);
        auto foundIt = std::find_if(this->cache.begin(), this->cache.end(), [&](const KernelArgEntry &cacheElement) {
            return arg_index == cacheElement.arg_index;
        });

        auto &cacheEntry = foundIt != this->cache.end() ? *foundIt : this->cache.emplace_back();
        cacheEntry.arg_index = arg_index;
        cacheEntry.arg_size = arg_size;
        cacheEntry.arg_value = arg_value;
        if (arg_value) {
            memcpy(cacheEntry.argValues, arg_value, arg_size);
        }
    }

    void invalidateCache() {
        std::lock_guard<std::shared_mutex> lock(this->mtx);
        this->cache.clear();
    }
};

} // namespace Cal::Icd
