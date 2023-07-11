/*
 * Copyright (C) 2022-2023 Intel Corporation
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
                if (it->getBoundingRange().start - Cal::Utils::alignUp(prev->getBoundingRange().end, alignment) >= sizeInBytes) {
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

Cal::Utils::AddressRange RangeAllocator::resizeOrAllocate(void *rangeBase, size_t newSize, size_t alignment, size_t &oldSize) {
    auto resizedSize = this->resizeRange(rangeBase, newSize, oldSize);
    if (0 == resizedSize) { // unknown address
        return {};
    }

    if (resizedSize >= newSize) { // succesfull resize
        return Cal::Utils::AddressRange{rangeBase, resizedSize};
    }

    auto newRange = this->allocate(newSize, alignment);
    if (newRange.empty()) {
        return {};
    }

    return newRange.base();
}

} // namespace Cal::Allocators
