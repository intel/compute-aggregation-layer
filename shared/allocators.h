/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/log.h"
#include "shared/sys.h"
#include "shared/utils.h"

#include <mutex>
#include <utility>
#include <vector>

namespace Cal::Allocators {

template <size_t MinAlignment>
bool adjustSizeAndAlignment(size_t &size, size_t &alignment) {
    static_assert(Cal::Utils::isPow2(MinAlignment));
    if (false == Cal::Utils::isPow2(alignment)) {
        log<Verbosity::error>("Requested alignment is not power of 2");
        return false;
    }

    if (alignment < MinAlignment) {
        alignment = MinAlignment;
        size = Cal::Utils::alignUpPow2<MinAlignment>(size);
    } else {
        size = Cal::Utils::alignUp(size, alignment);
    }

    return true;
}

// Thread-safe
template <typename MaskType = uint64_t>
class StaticLengthBitAllocator final {
  public:
    using MaskT = MaskType;
    static constexpr uint32_t capacity = std::numeric_limits<MaskT>::digits;
    using BitOffsetT = uint32_t;
    static constexpr MaskT fullMask = std::numeric_limits<MaskT>::max();
    static constexpr BitOffsetT invalidOffset = std::numeric_limits<BitOffsetT>::max();

    StaticLengthBitAllocator() = default;

    StaticLengthBitAllocator(const StaticLengthBitAllocator &rhs) {
        occupied = rhs.occupied.load();
    }

    StaticLengthBitAllocator(StaticLengthBitAllocator &&rhs) {
        occupied = rhs.occupied.exchange(0);
    }

    BitOffsetT allocate() {
        BitOffsetT offset = invalidOffset;
        auto prev = occupied.load();
        while (true) {
            if (prev == fullMask) {
                break;              // full
            } else if (0 == prev) { // empty
                if (occupied.compare_exchange_weak(prev, 1U)) {
                    offset = 0;
                    break;
                }
            }

            auto inv = ~prev;
            auto firstUnset = __builtin_ffsl(inv) - 1;
            if (occupied.compare_exchange_weak(prev, prev | (static_cast<MaskT>(1) << firstUnset))) {
                offset = firstUnset;
                break;
            }
        }
        return offset;
    }

    void free(BitOffsetT offset) {
        auto mask = ~(static_cast<MaskT>(1) << offset);
        auto prev = occupied.load();
        while (false == occupied.compare_exchange_weak(prev, prev & mask)) {
        }
    }

  protected:
    std::atomic<MaskT> occupied = 0U;
};

// Thread-safe
class BitAllocator final {
  public:
    using NodeT = StaticLengthBitAllocator<uint64_t>;
    using BitOffsetT = NodeT::BitOffsetT;
    static constexpr BitOffsetT invalidOffset = NodeT::invalidOffset;

    BitAllocator() = default;

    BitAllocator(size_t capacity) {
        nodes.resize(capacity / NodeT::capacity);
        if (0 != (capacity % NodeT::capacity)) {
            log<Verbosity::error>("BitAllocator capacity not divisible by node size - %zu elements will be wasted", capacity % NodeT::capacity);
        }
    }

    BitOffsetT allocate() {
        auto offset = invalidOffset;
        constexpr int numTries = 2;
        for (int tryNum = 0; tryNum < numTries; ++tryNum) {
            for (size_t i = 0; i < nodes.size(); ++i) {
                auto localOffset = nodes[i].allocate();
                if (NodeT::invalidOffset != localOffset) {
                    offset = localOffset + i * NodeT::capacity;
                    break;
                }
            }
            if (invalidOffset != offset) {
                break;
            }
        }

        return offset;
    }

    bool free(BitOffsetT offset) {
        auto nodeId = offset / NodeT::capacity;
        if (nodeId >= nodes.size()) {
            log<Verbosity::error>("Invalid offset %zu >= %zu", offset, getCapacity());
            return false;
        }
        nodes[nodeId].free(offset - nodeId * NodeT::capacity);
        return true;
    }

    size_t getCapacity() const {
        return nodes.size() * NodeT::capacity;
    }

  protected:
    std::vector<NodeT> nodes;
};

// Thread-safe
template <typename TagType>
class TagAllocator final {
  public:
    using TagTypeT = TagType;

    TagAllocator() = default;

    TagAllocator(TagType *underlyingAllocation, size_t capacity)
        : underlyingAllocation(underlyingAllocation), allocator(capacity) {
    }

    TagType *allocate() {
        auto offset = allocator.allocate();
        if (BitAllocator::invalidOffset == offset) {
            return nullptr;
        }

        TagType *ret = &underlyingAllocation[offset];
        return ret;
    }

    void free(TagType *tag) {
        auto offset = tag - underlyingAllocation;
        allocator.free(offset);
    }

    size_t getCapacity() const {
        return allocator.getCapacity();
    }

  protected:
    TagType *underlyingAllocation = nullptr;
    BitAllocator allocator;
};

class RangeAllocatorBase {
  public:
    RangeAllocatorBase() : vma({0U, 0U}) {
    }

    RangeAllocatorBase(Cal::Utils::AddressRange vaRange) : vma(vaRange) {
    }

    Cal::Utils::AddressRange getRange() const {
        return vma.getBoundingRange();
    }

    size_t getSizeUsed() const {
        return sizeUsed;
    }

    size_t getSizeLeft() const {
        return vma.getBoundingRange().size() - sizeUsed;
    }

  protected:
    const Cal::Utils::PartitionedAddressRange<void> getVma() const {
        return vma;
    }

    void commitRange(Cal::Utils::AddressRange range) {
        vma.insertSubRange(range);
        sizeUsed += range.size();
    }

    void freeRange(void *rangeBase) {
        auto range = vma.findSubRange({rangeBase});
        if (nullptr == range) {
            log<Verbosity::error>("Attempted to free non-allocated range");
            return;
        }

        auto bounds = range->getBoundingRange();
        vma.destroySubRange(bounds);
        sizeUsed -= bounds.size();
    }

  private:
    Cal::Utils::PartitionedAddressRange<void> vma;
    size_t sizeUsed = 0U;
};

// NOT thread-safe
class RangeAllocator : public RangeAllocatorBase {
  public:
    static constexpr bool isThreadSafe = false;
    using AllocationT = Cal::Utils::AddressRange;

    using RangeAllocatorBase::RangeAllocatorBase;

    Cal::Utils::AddressRange allocate(size_t sizeInBytes, size_t alignment);

    Cal::Utils::AddressRange allocate(size_t sizeInBytes) {
        return allocate(sizeInBytes, 1);
    }

    void free(void *rangeBase) {
        this->freeRange(rangeBase);
    }
};

class AddressRangeAllocator : public RangeAllocator {
  public:
    static constexpr bool isThreadSafe = RangeAllocator::isThreadSafe;
    using AllocationT = void *;

    using RangeAllocator::RangeAllocator;

    void *allocate(size_t sizeInBytes, size_t alignment) {
        auto allocated = RangeAllocator::allocate(sizeInBytes, alignment);
        return (allocated.size() >= sizeInBytes) ? allocated.base() : nullptr;
    }

    void *allocate(size_t sizeInBytes) {
        return this->allocate(sizeInBytes, 16);
    }

    void free(void *ptr) {
        RangeAllocator::free(ptr);
    }
};

class OffsetRangeAllocator : public RangeAllocator {
  public:
    static constexpr bool isThreadSafe = RangeAllocator::isThreadSafe;
    using AllocationT = std::optional<uintptr_t>;

    OffsetRangeAllocator(Cal::Utils::OffsetRange offsetRange) : RangeAllocator(offsetRange) {
    }

    using RangeAllocator::RangeAllocator;

    std::optional<uintptr_t> allocate(size_t sizeInBytes, size_t alignment) {
        auto allocated = RangeAllocator::allocate(sizeInBytes, alignment);
        return (allocated.size() >= sizeInBytes) ? std::optional<uintptr_t>{allocated.start} : std::nullopt;
    }

    std::optional<uintptr_t> allocate(size_t sizeInBytes) {
        return this->allocate(sizeInBytes, 16);
    }

    void free(uintptr_t offset) {
        RangeAllocator::free(reinterpret_cast<void *>(offset));
    }
};

// thread-safe base
class BaseAllocation {
  public:
    static constexpr bool isThreadSafe = true;

    static constexpr bool isShmemAllocation = false;
    static constexpr bool isFdAllocation = false;
    static constexpr bool isFdSubAllocation = false;
    static constexpr bool isMmappedAllocation = false;
    static constexpr bool isSubAllocation = false;

    BaseAllocation() = default;

    bool isValid() const {
        return true;
    }

    Cal::Utils::OffsetRange getRange() const {
        return Cal::Utils::OffsetRange{0U, 0U};
    }
};

// thread-safe decoration
template <typename BaseAllocationType = BaseAllocation>
class FdAllocation : public BaseAllocationType {
  public:
    static constexpr bool isThreadSafe = BaseAllocationType::isThreadSafe;
    static constexpr bool isFdAllocation = true;

    using BaseT = BaseAllocationType;

    template <typename BaseAllocationTypeInitT>
    FdAllocation(BaseAllocationTypeInitT &&baseAllocation, int fd, size_t fileSize, bool isFdOwner)
        : BaseAllocationType(std::forward<BaseAllocationTypeInitT>(baseAllocation)),
          fileSize(fileSize), fd(fd), isFdOwner(isFdOwner) {
    }

    FdAllocation(int fd, size_t fileSize, bool isFdOwner)
        : fileSize(fileSize), fd(fd), isFdOwner(isFdOwner) {
    }

    FdAllocation() = default;

    int getFd() const {
        return fd;
    }

    bool isOwnerOfFd() const {
        return isFdOwner;
    }

    size_t getFileSize() const {
        return fileSize;
    }

    bool isValid() const {
        return (-1 != fd) && BaseAllocationType::isValid();
    }

    Cal::Utils::OffsetRange getRange() const {
        return Cal::Utils::OffsetRange{uintptr_t{0U}, this->fileSize};
    }

  protected:
    size_t fileSize = 0U;   // file size
    int fd = -1;            // opened FD
    bool isFdOwner = false; // freeing this allocation closes the fd
};

// thread-safe decoration
template <typename BaseAllocationType = FdAllocation<>>
class FdSubAllocation : public BaseAllocationType {
  public:
    static constexpr bool isThreadSafe = BaseAllocationType::isThreadSafe;
    static_assert(BaseAllocationType::isFdAllocation);
    static constexpr bool isFdSubAllocation = true;

    using BaseT = BaseAllocationType;

    template <typename BaseAllocationTypeInitT>
    FdSubAllocation(BaseAllocationTypeInitT &&baseAllocation, size_t fdOffset)
        : BaseAllocationType(std::forward<BaseAllocationTypeInitT>(baseAllocation)), fdOffset(fdOffset) {
    }

    FdSubAllocation() = default;

    size_t getFdSubAllocationOffset() const {
        return fdOffset;
    }

    static size_t getSubAllocationOffset(const FdSubAllocation<BaseAllocationType> &subAlloc) {
        return subAlloc.getFdSubAllocationOffset();
    }

    bool isValid() const {
        return (fdOffset < this->fileSize) && BaseAllocationType::isValid();
    }

    Cal::Utils::OffsetRange getRange() const {
        return Cal::Utils::OffsetRange{fdOffset, this->fileSize};
    }

  protected:
    size_t fdOffset = 0U;
};

// thread-safe decoration
template <typename BaseAllocationType = FdAllocation<>>
class MmappedAllocation : public BaseAllocationType {
  public:
    static constexpr bool isThreadSafe = BaseAllocationType::isThreadSafe;
    static constexpr bool isMmappedAllocation = true;

    using BaseT = BaseAllocationType;

    template <typename BaseAllocationTypeInitT>
    MmappedAllocation(BaseAllocationTypeInitT &&baseAllocation, void *mmappedPtr, size_t mmappedSize)
        : BaseAllocationType(std::forward<BaseAllocationTypeInitT>(baseAllocation)),
          mmappedPtr(mmappedPtr), mmappedSize(mmappedSize) {
    }

    MmappedAllocation(void *mmappedPtr, size_t mmappedSize)
        : mmappedPtr(mmappedPtr), mmappedSize(mmappedSize) {
    }

    MmappedAllocation() = default;

    void *getMmappedPtr() const {
        return mmappedPtr;
    }

    size_t getMmappedSize() const {
        return mmappedSize;
    }

    bool isValid() const {
        return (mmappedPtr && mmappedSize) && BaseAllocationType::isValid();
    }

    Cal::Utils::OffsetRange getRange() const {
        return Cal::Utils::OffsetRange{mmappedPtr, mmappedSize};
    }

  protected:
    void *mmappedPtr = nullptr;
    size_t mmappedSize = 0U;
};

// thread-safe
template <typename SourceAllocationType>
class SubAllocation {
  public:
    static constexpr bool isThreadSafe = true;
    static constexpr bool isSubAllocation = true;

    using ThisT = SubAllocation<SourceAllocationType>;
    using SourceT = SourceAllocationType;

    SubAllocation(const SourceAllocationType *sourceAllocation,
                  size_t subAllocationOffset, size_t subAllocationSize)
        : sourceAllocation(sourceAllocation),
          subAllocationOffset(subAllocationOffset), subAllocationSize(subAllocationSize) {
    }

    SubAllocation() = default;

    size_t getSubAllocationOffset() const {
        return subAllocationOffset;
    }

    static size_t getSubAllocationOffset(const ThisT &alloc) {
        return alloc.subAllocationOffset;
    }

    size_t getSubAllocationSize() const {
        return subAllocationSize;
    }

    template <typename T = void *>
    T getSubAllocationPtr() const {
        static_assert(std::is_pointer_v<T>);
        if constexpr (SourceAllocationType::isMmappedAllocation) {
            static_assert(SourceAllocationType::isThreadSafe);
            if (nullptr == sourceAllocation->getMmappedPtr()) {
                log<Verbosity::error>("Attempted to getSubAllocationPtr when mmapped ptr is NULL");
                return nullptr;
            }
            return reinterpret_cast<T>(Cal::Utils::moveByBytes(sourceAllocation->getMmappedPtr(), subAllocationOffset));
        } else {
            log<Verbosity::error>("Attempted to getSubAllocationPtr of non-mmapped allocation");
            return nullptr;
        }
    }

    const SourceAllocationType *getSourceAllocation() const {
        return sourceAllocation;
    }

    bool isValid() const {
        return subAllocationSize && sourceAllocation && (sourceAllocation->isValid());
    }

    Cal::Utils::OffsetRange getRange() const {
        auto range = sourceAllocation->getRange();
        range.start += subAllocationOffset;
        range.end = range.start + subAllocationSize;
        return range;
    }

  protected:
    const SourceAllocationType *sourceAllocation = nullptr;
    size_t subAllocationOffset = 0U;
    size_t subAllocationSize = 0U;
};

// thread-safe
template <typename UnderlyingAllocationType, size_t MinAlignment = UnderlyingAllocationType::MinAlignment, typename AllocationType = SubAllocation<UnderlyingAllocationType>>
class SubAllocator final {
  public:
    static_assert(Cal::Utils::isPow2(MinAlignment));
    static constexpr bool isThreadSafe = true;

    using ThisT = SubAllocator<AllocationType, MinAlignment, UnderlyingAllocationType>;
    using AllocationT = AllocationType;
    static constexpr size_t minAlignment = MinAlignment;

    SubAllocator(UnderlyingAllocationType underlyingAllocation, Cal::Utils::OffsetRange offsetsRange, bool offsetRangeIsRelativeToUnderlingAllocation)
        : underlyingAllocation(underlyingAllocation), rangeAllocator(offsetsRange), offsetRangeIsRelativeToUnderlingAllocation(offsetRangeIsRelativeToUnderlingAllocation) {
    }

    SubAllocator(UnderlyingAllocationType underlyingAllocation, Cal::Utils::OffsetRange offsetsRange)
        : SubAllocator(underlyingAllocation, offsetsRange, false) {
    }

    mockable ~SubAllocator() = default;

    mockable AllocationType allocate(size_t size, size_t alignment) {
        if (false == adjustSizeAndAlignment<minAlignment>(size, alignment)) {
            return AllocationType{};
        }

        OffsetRangeAllocator::AllocationT assignedOffset = {};
        {
            auto rangeAllocatorLock = rangeAllocator.lock();
            assignedOffset = rangeAllocator->allocate(size, alignment);
        }
        if (assignedOffset.has_value() == false) {
            return AllocationType{};
        }
        auto relativeOffset = assignedOffset.value();
        if (false == offsetRangeIsRelativeToUnderlingAllocation) {
            relativeOffset -= rangeAllocator->getRange().start;
        }
        AllocationType ret{&underlyingAllocation, relativeOffset, size};
        return ret;
    }

    AllocationType allocate(size_t size) {
        return this->allocate(size, minAlignment);
    }

    void free(const AllocationType &allocation) {
        auto rangeAllocatorLock = rangeAllocator.lock();
        auto offset = AllocationType::getSubAllocationOffset(static_cast<const AllocationType &>(allocation));
        if (false == offsetRangeIsRelativeToUnderlingAllocation) {
            offset += rangeAllocator->getRange().start;
        }
        rangeAllocator->free(offset);
    }

    const UnderlyingAllocationType &getUnderlyingAllocation() const {
        return underlyingAllocation;
    }

    size_t getSizeLeft() {
        auto rangeAllocatorLock = rangeAllocator.lock();
        return rangeAllocator->getSizeLeft();
    }

    Cal::Utils::OffsetRange getOffsetRange() const {
        return rangeAllocator->getRange();
    }

  protected:
    UnderlyingAllocationType underlyingAllocation;
    Cal::Utils::Lockable<OffsetRangeAllocator> rangeAllocator;
    bool offsetRangeIsRelativeToUnderlingAllocation = false;
};

struct MmapConfig {
    int prot = 0;
    int flags = 0;
};

struct UnmapConfig {
    bool useResetInsteadOfMunamp = false;
    MmapConfig resetTraits;
};

template <typename AllocationT>
static size_t getFdOffset(const AllocationT &alloc) {
    if constexpr (AllocationT::isFdSubAllocation) {
        return alloc.getFdSubAllocationOffset();
    } else {
        return 0U;
    }
}

// thread-safe
template <typename UnderlyingAllocator, bool SharedUnderlyingAllocator = false>
class AllocatorWithGlobalMmapToFd {
  public:
    static_assert(UnderlyingAllocator::AllocationT::isFdAllocation); // requirement
    static_assert(UnderlyingAllocator::isThreadSafe);                // requirement

    static constexpr bool isThreadSafe = true;

    using ThisT = AllocatorWithGlobalMmapToFd<UnderlyingAllocator, SharedUnderlyingAllocator>;
    static constexpr bool isUsingSharedUnderlyingAllocator = SharedUnderlyingAllocator;

    using UnderyAllocationT = typename UnderlyingAllocator::AllocationT;

    using AllocationT = MmappedAllocation<UnderyAllocationT>;
    using UnderlyingAllocatorVarT = std::conditional_t<SharedUnderlyingAllocator, UnderlyingAllocator &, UnderlyingAllocator>;

    static constexpr size_t minAlignment = Cal::Utils::pageSize4KB;

    AllocatorWithGlobalMmapToFd(UnderlyingAllocatorVarT underlyingAllocator, MmapConfig mmapConfig)
        : underlyingAllocator(underlyingAllocator), mmapConfig(mmapConfig) {}

    AllocatorWithGlobalMmapToFd(const ThisT &rhs, int = 0)
        : underlyingAllocator(rhs.underlyingAllocator), mmapConfig(rhs.mmapConfig) {}

    template <typename T = ThisT, std::enable_if_t<T::isUingSharedUnderlyingAllocator, int> = 0>
    AllocatorWithGlobalMmapToFd(ThisT &&rhs)
        : underlyingAllocator(rhs.underlyingAllocator), mmapConfig(std::move(rhs.mmapConfig)) {
    }

    template <typename T = ThisT, std::enable_if_t<false == T::isUsingSharedUnderlyingAllocator, int> = 0>
    AllocatorWithGlobalMmapToFd(ThisT &&rhs)
        : underlyingAllocator(std::move(rhs.underlyingAllocator)), mmapConfig(std::move(rhs.mmapConfig)) {}

    virtual ~AllocatorWithGlobalMmapToFd() = default;

    mockable AllocationT allocate(size_t size, size_t alignment) {
        if (false == adjustSizeAndAlignment<minAlignment>(size, alignment)) {
            return {};
        }

        auto baseAlloc = underlyingAllocator.allocate(size, alignment);
        if (baseAlloc.isValid() == false) {
            return {};
        }
        if (alignment > Cal::Utils::pageSize4KB) {
            log<Verbosity::error>("Unsupported alignment %zu > %zu", alignment, Cal::Utils::pageSize4KB);
            return {};
        }
        auto fd = baseAlloc.getFd();
        auto fdOffset = getFdOffset(baseAlloc);
        void *mmappedPtr = Cal::Sys::mmap(nullptr, size, mmapConfig.prot, mmapConfig.flags, fd, fdOffset);
        if (MAP_FAILED == mmappedPtr) {
            log<Verbosity::error>("Failed to mmap allocation of size : %zu to fd : %d at offset %zu", size, fd, fdOffset);
            underlyingAllocator.free(baseAlloc);
            return {};
        }

        AllocationT ret{std::move(baseAlloc), mmappedPtr, size};
        return ret;
    }

    AllocationT allocate(size_t size) {
        return this->allocate(size, minAlignment);
    }

    mockable void free(const AllocationT &allocation) {
        if (allocation.getMmappedPtr()) {
            if (-1 == Cal::Sys::munmap(allocation.getMmappedPtr(), allocation.getMmappedSize())) {
                log<Verbosity::error>("Failed to munmap %p size : %zu - leaking allocation", allocation.getMmappedPtr(), allocation.getMmappedSize());
                return;
            }
        }
        underlyingAllocator.free(allocation);
    }

    mockable UnderlyingAllocator &getUnderlyingAllocator() {
        return underlyingAllocator;
    }

    const MmapConfig &getMmapConfig() const {
        return mmapConfig;
    }

  protected:
    UnderlyingAllocatorVarT underlyingAllocator;
    MmapConfig mmapConfig;
};

// thread-safe
template <typename UnderlyingAllocator, bool SharedUnderlyingAllocator = false>
class AllocatorWithBoundedMmapToFd {
  public:
    static_assert(UnderlyingAllocator::AllocationT::isFdAllocation); // requirement
    static_assert(UnderlyingAllocator::isThreadSafe);                // requirement

    static constexpr bool isThreadSafe = true;

    using ThisT = AllocatorWithBoundedMmapToFd<UnderlyingAllocator, SharedUnderlyingAllocator>;
    static constexpr bool isUsingSharedUnderlyingAllocator = SharedUnderlyingAllocator;

    using UnderyAllocationT = typename UnderlyingAllocator::AllocationT;

    using AllocationT = MmappedAllocation<UnderyAllocationT>;
    using UnderlyingAllocatorVarT = std::conditional_t<SharedUnderlyingAllocator, UnderlyingAllocator &, UnderlyingAllocator>;

    static constexpr size_t minAlignment = Cal::Utils::pageSize4KB;

    AllocatorWithBoundedMmapToFd(UnderlyingAllocatorVarT underlyingAllocator, MmapConfig mmapConfig, UnmapConfig munmapConfig, Cal::Utils::AddressRange bounds)
        : underlyingAllocator(std::forward<UnderlyingAllocatorVarT>(underlyingAllocator)), mmapConfig(mmapConfig), munmapConfig(munmapConfig), rangeAllocator(bounds) {}

    AllocatorWithBoundedMmapToFd(const ThisT &rhs, int = 0)
        : underlyingAllocator(rhs.underlyingAllocator), mmapConfig(rhs.mmapConfig), munmapConfig(rhs.munmapConfig), rangeAllocator(rhs.rangeAllocator) {}

    template <typename T = ThisT, std::enable_if_t<T::isUingSharedUnderlyingAllocator, int> = 0>
    AllocatorWithBoundedMmapToFd(ThisT &&rhs)
        : underlyingAllocator(rhs.underlyingAllocator), mmapConfig(std::move(rhs.mmapConfig)), munmapConfig(std::move(rhs.munmapConfig)), rangeAllocator(std::move(rhs.rangeAllocator)) {}

    template <typename T = ThisT, std::enable_if_t<false == T::isUsingSharedUnderlyingAllocator, int> = 0>
    AllocatorWithBoundedMmapToFd(ThisT &&rhs)
        : underlyingAllocator(std::move(rhs.underlyingAllocator)), mmapConfig(std::move(rhs.mmapConfig)), munmapConfig(std::move(rhs.munmapConfig)), rangeAllocator(std::move(rhs.rangeAllocator)) {}

    virtual ~AllocatorWithBoundedMmapToFd() = default;

    mockable AllocationT allocate(size_t size, size_t alignment) {
        if (false == adjustSizeAndAlignment<minAlignment>(size, alignment)) {
            return {};
        }

        auto baseAlloc = underlyingAllocator.allocate(size, alignment);
        if (baseAlloc.isValid() == false) {
            return {};
        }

        void *assignedPtr = nullptr;
        {
            auto rangeAllocatorLock = rangeAllocator.lock();
            assignedPtr = rangeAllocator->allocate(size, alignment);
        }
        if (nullptr == assignedPtr) {
            log<Verbosity::error>("No space left in range");
            underlyingAllocator.free(baseAlloc);
            return {};
        }

        auto fd = baseAlloc.getFd();
        auto fdOffset = getFdOffset(baseAlloc);
        void *mmappedPtr = Cal::Sys::mmap(assignedPtr, size, mmapConfig.prot, MAP_FIXED | mmapConfig.flags, fd, fdOffset);
        if (MAP_FAILED == mmappedPtr) {
            log<Verbosity::error>("Failed to mmap allocation of size : %zu to fd : %d at offset : %zu using ptr : %p", size, fd, fdOffset, assignedPtr);
            {
                auto rangeAllocatorLock = rangeAllocator.lock();
                rangeAllocator->free(assignedPtr);
            }
            underlyingAllocator.free(baseAlloc);
            return {};
        }

        AllocationT ret{std::move(baseAlloc), mmappedPtr, size};
        return ret;
    }

    AllocationT allocate(size_t size) {
        return this->allocate(size, minAlignment);
    }

    mockable void free(const AllocationT &allocation) {
        bool unmapSucesful = true;
        if (allocation.getMmappedPtr()) {
            if (munmapConfig.useResetInsteadOfMunamp) {
                auto ret = Cal::Sys::mmap(allocation.getMmappedPtr(), allocation.getMmappedSize(), munmapConfig.resetTraits.prot, munmapConfig.resetTraits.flags | MAP_FIXED, -1, 0);
                if (MAP_FAILED == ret) {
                    log<Verbosity::error>("Failed to reset range, ptr : %p, size : %zu", allocation.getMmappedPtr(), allocation.getMmappedSize());
                    unmapSucesful = false;
                }
            } else {
                if (-1 == Cal::Sys::munmap(allocation.getMmappedPtr(), allocation.getMmappedSize())) {
                    log<Verbosity::error>("Failed to munmap %p size : %zu", allocation.getMmappedPtr(), allocation.getMmappedSize());
                    unmapSucesful = false;
                }
            }
            if (unmapSucesful) {
                {
                    auto rangeAllocatorLock = rangeAllocator.lock();
                    rangeAllocator->free(allocation.getMmappedPtr());
                }
            }
        }
        if (unmapSucesful) {
            underlyingAllocator.free(allocation);
        } else {
            log<Verbosity::debug>("Leaking allocation because of failed unmap/reset");
        }
    }

    Cal::Utils::AddressRange getMmapRange() const {
        return rangeAllocator->getRange();
    }

    const MmapConfig &getMmapConfig() const {
        return mmapConfig;
    }

    const UnmapConfig &getUnmapConfig() const {
        return munmapConfig;
    }

  protected:
    UnderlyingAllocatorVarT underlyingAllocator;
    MmapConfig mmapConfig;
    UnmapConfig munmapConfig;
    Cal::Utils::Lockable<AddressRangeAllocator> rangeAllocator;
};

template <typename UnderlyingAllocator, bool SharedUnderlyingAllocator>
class ArenaAllocator;

// thread-safe decoration
template <typename SourceAllocationType, typename ArenaType = void>
class ArenaSubAllocation : public SubAllocation<SourceAllocationType> {
    template <typename, bool>
    friend class ArenaAllocator;

  public:
    static constexpr bool isThreadSafe = true && SubAllocation<SourceAllocationType>::isThreadSafe;

    using ThisT = ArenaSubAllocation<SourceAllocationType, ArenaType>;
    using BaseT = SubAllocation<SourceAllocationType>;

    ArenaSubAllocation(const SourceAllocationType *sourceAllocation, size_t subAllocationOffset, size_t subAllocationSize)
        : SubAllocation<SourceAllocationType>(sourceAllocation, subAllocationOffset, subAllocationSize) {
    }

    ArenaSubAllocation() = default;

    ArenaType *getArena() const {
        return arena;
    }

  protected:
    ArenaType *arena = nullptr;
};

// thread-safe
template <typename UnderlyingAllocator, bool SharedUnderlyingAllocator = false>
class ArenaAllocator {
  public:
    static constexpr bool isThreadSafe = true;
    static_assert(UnderlyingAllocator::isThreadSafe); // requirement

    using ThisT = ArenaAllocator<UnderlyingAllocator, SharedUnderlyingAllocator>;
    static constexpr bool isUsingSharedUnderlyingAllocator = SharedUnderlyingAllocator;

    using UnderlyingAllocationT = typename UnderlyingAllocator::AllocationT;
    using AllocationT = ArenaSubAllocation<UnderlyingAllocationT, void>;
    using SubAllocatorT = SubAllocator<UnderlyingAllocationT, Cal::Utils::pageSize4KB, AllocationT>;
    static_assert(SubAllocatorT::isThreadSafe);
    using ArenaT = SubAllocatorT;
    static constexpr size_t minAlignment = ArenaT::minAlignment;

    using UnderlyingAllocatorVarT = std::conditional_t<SharedUnderlyingAllocator, UnderlyingAllocator &, UnderlyingAllocator>;

    ArenaAllocator(UnderlyingAllocatorVarT underlyingAllocator, size_t underlyingAllocationGranularity)
        : underlyingAllocator(std::forward<UnderlyingAllocatorVarT>(underlyingAllocator)),
          underlyingAllocationGranularity(underlyingAllocationGranularity),
          standaloneAllocationThreshold(underlyingAllocationGranularity / 2) {
        constexpr size_t entryArenaSize = 4096U;
        auto entryArenaAllocation = this->underlyingAllocator.allocate(entryArenaSize);
        if (entryArenaAllocation.isValid() == false) {
            log<Verbosity::critical>("Could not allocate entry memory arena");
        }
        auto entryArena = std::make_unique<ArenaT>(entryArenaAllocation, getArenaOffsetRange(entryArenaAllocation, underlyingAllocationGranularity), false);
        latestArena->store(entryArena.get());
        allArenas->push_back(std::move(entryArena));
    }

    ArenaAllocator(const ThisT &rhs, int = 0)
        : ArenaAllocator(rhs.underlyingAllocator, rhs.underlyingAllocationGranularity) {
    }

    template <typename T = ThisT, std::enable_if_t<T::isUingSharedUnderlyingAllocator, int> = 0>
    ArenaAllocator(ThisT &&rhs)
        : underlyingAllocator(rhs.underlyingAllocator), underlyingAllocationGranularity(rhs.underlyingAllocationGranularity), standaloneAllocationThreshold(rhs.standaloneAllocationThreshold),
          allArenas(std::move(rhs.allArenas)), recycledArenas(std::move(rhs.recycledArenas)), latestArena(rhs.latestArena->load()) {}

    template <typename T = ThisT, std::enable_if_t<false == T::isUsingSharedUnderlyingAllocator, int> = 0>
    ArenaAllocator(ThisT &&rhs)
        : underlyingAllocator(std::move(rhs.underlyingAllocator)), underlyingAllocationGranularity(rhs.underlyingAllocationGranularity), standaloneAllocationThreshold(rhs.standaloneAllocationThreshold),
          allArenas(std::move(rhs.allArenas)), recycledArenas(std::move(rhs.recycledArenas)), latestArena(rhs.latestArena->load()) {}

    virtual ~ArenaAllocator() {
        for (auto &arena : *allArenas) {
            underlyingAllocator.free(arena->getUnderlyingAllocation());
        }
    }

    mockable AllocationT allocateAsStandalone(size_t size, size_t alignment) {
        auto newSourceAlloc = underlyingAllocator.allocate(size, alignment);
        if (newSourceAlloc.isValid() == false) {
            log<Verbosity::error>("Failed to allocate arena underlying allocation for standalone allocation");
            return AllocationT{};
        }
        auto baseAllocation = std::make_unique<UnderlyingAllocationT>(std::move(newSourceAlloc));
        AllocationT fullSubAllocation{baseAllocation.get(), 0U, size};
        baseAllocation.release();
        return fullSubAllocation;
    }

    AllocationT allocateAsStandalone(size_t size) {
        return this->allocateAsStandalone(size, minAlignment);
    }

    mockable AllocationT allocate(size_t size, size_t alignment) {
        if (false == adjustSizeAndAlignment<minAlignment>(size, alignment)) {
            return AllocationT{};
        }

        if (size > standaloneAllocationThreshold) {
            return this->allocateAsStandalone(size, alignment); // too big for arena
        }

        auto latestArenaSnapshot = this->peekLatestArena();
        auto alloc = latestArenaSnapshot->allocate(size, alignment); // fast path
        if (alloc.isValid()) {                                       // try use latest used arena
            alloc.arena = latestArenaSnapshot;
            return alloc;
        }

        { // try reuse recycled arenas
            auto recycleLock = recycledArenas.lock();
            if (recycledArenas->size() > 0) {
                auto recycledArena = *recycledArenas->rbegin();
                recycledArenas->pop_back();

                alloc = recycledArena->allocate(size, alignment);
                if (alloc.isValid()) {
                    alloc.arena = recycledArena;

                    {
                        auto latestArenaLock = latestArena.lock();
                        if (this->peekLatestArena() == latestArenaSnapshot) { // assume recycled arena is better than latest
                            latestArena->store(recycledArena);
                        }
                    }
                    return alloc;
                } else { // probably arena is too fragmented
                    log<Verbosity::performance>("Failed to allocate from reused arena");
                }
            }
        }

        { // try creating new arena
            auto newArenaLock = allArenas.lock();
            {
                auto prevLatestArenaSnapshot = latestArenaSnapshot;
                latestArenaSnapshot = this->peekLatestArena();
                if (latestArenaSnapshot != prevLatestArenaSnapshot) { // check if latest arena is still not suitable
                    latestArenaSnapshot->allocate(size, alignment);
                    if (alloc.isValid()) {
                        return alloc;
                    }
                }
            }
            auto newArenaAllocation = underlyingAllocator.allocate(underlyingAllocationGranularity);
            if (newArenaAllocation.isValid() == false) {
                log<Verbosity::error>("Failed to allocate new memory arena");
                return {};
            }
            auto newArena = std::make_unique<ArenaT>(newArenaAllocation, getArenaOffsetRange(newArenaAllocation, underlyingAllocationGranularity), false);
            auto arena = newArena.get();
            allArenas->push_back(std::move(newArena));
            alloc = arena->allocate(size, alignment);
            alloc.arena = arena;

            {
                auto latestArenaLock = latestArena.lock(); // assume new arena is better than latest
                latestArena->store(arena);
            }

            return alloc;
        }
    }

    AllocationT allocate(size_t size) {
        return this->allocate(size, minAlignment);
    }

    mockable void free(const AllocationT &alloc) {
        if (nullptr == alloc.arena) { // standalone allocation
            underlyingAllocator.free(*alloc.getSourceAllocation());
            delete alloc.getSourceAllocation();
            return;
        }

        ArenaT *arena = static_cast<ArenaT *>(alloc.arena);

        arena->free(alloc);
        {
            if (this->peekLatestArena() == arena) {
                return;
            }

            {
                auto latestArenaLock = latestArena.lock();
                if (this->peekLatestArena() == arena) {
                    return;
                }

                if (arena->getSizeLeft() >= standaloneAllocationThreshold) {
                    auto recycleLock = recycledArenas.lock();
                    if (recycledArenas->end() == std::find(recycledArenas->begin(), recycledArenas->end(), arena)) {
                        recycledArenas->push_back(arena);
                    }
                }
            }
        }
    }

    mockable ArenaT *peekLatestArena() const {
        return latestArena->load();
    }

    const UnderlyingAllocator &getUnderlyingAllocator() const {
        return underlyingAllocator;
    }

  protected:
    Cal::Utils::OffsetRange getArenaOffsetRange(const UnderlyingAllocationT &alloc, size_t sizeAllocated) {
        auto range = alloc.getRange();
        if (range.empty() && alloc.isValid()) {
            range = {uintptr_t{0U}, uintptr_t{sizeAllocated}}; // allocation does not keep range information, use default
        }
        return range;
    }

    UnderlyingAllocatorVarT underlyingAllocator;
    size_t underlyingAllocationGranularity = 0U;
    size_t standaloneAllocationThreshold = 0U;

    using OwnedArenasVecT = std::vector<std::unique_ptr<ArenaT>>;
    using ReferencedArenasVecT = std::vector<ArenaT *>;
    Cal::Utils::Lockable<OwnedArenasVecT> allArenas;           // relevant only when creating arena and for cleanup
    Cal::Utils::Lockable<ReferencedArenasVecT> recycledArenas; // arena that is ready for reuse (after part of it was reaped)

    Cal::Utils::Lockable<std::atomic<ArenaT *>> latestArena; // latest snapshot can be peeked via atomic directly, update only under lock
};

} // namespace Cal::Allocators
