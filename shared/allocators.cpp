/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/allocators.h"

namespace Cal::Allocators {

Cal::Utils::AddressRange RangeAllocator::allocate(size_t sizeInBytes, size_t alignment) {
    if (this->getSizeLeft() < sizeInBytes) {
        return Cal::Utils::AddressRange::createEmpty();
    }

    void *const invalidAddr = reinterpret_cast<void *>(std::numeric_limits<uintptr_t>::max());
    const auto &vma = this->getVma();
    void *addr = invalidAddr;
    if (vma.getSubRanges().empty()) {
        addr = vma.getBoundingRange().base();
    } else {
        addr = vma.getSubRanges().rbegin()->getBoundingRange().rightBound();
    }

    addr = Cal::Utils::alignUp(addr, alignment);

    if (false == vma.getBoundingRange().contains({addr, sizeInBytes})) {
        if (Cal::Utils::alignUp(vma.getSubRanges().begin()->getBoundingRange().start, alignment) - vma.getBoundingRange().start >= sizeInBytes) {
            addr = Cal::Utils::alignUp(vma.getBoundingRange().base(), alignment);
        } else {
            addr = invalidAddr;
            auto prev = vma.getSubRanges().begin();
            auto it = prev + 1;
            while (it != vma.getSubRanges().end()) {
                if (Cal::Utils::alignUp(prev->getBoundingRange().end, alignment) - it->getBoundingRange().start >= sizeInBytes) {
                    addr = Cal::Utils::alignUp(prev->getBoundingRange().rightBound(), alignment);
                    break;
                }
                prev = it;
                ++it;
            }
            if (invalidAddr == addr) {
                log<Verbosity::debug>("Failed to allocate range");
                return Cal::Utils::AddressRange::createEmpty();
            }
        }
    }

    commitRange({addr, sizeInBytes});
    return {addr, sizeInBytes};
}

} // namespace Cal::Allocators
