/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <algorithm>
#include <atomic>
#include <cctype>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <limits>
#if __has_include(<filesystem>)
#include <filesystem>
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace std {
namespace filesystem {
using namespace std::experimental::filesystem::v1;
}
} // namespace std
#else
#include <filesystem>
#endif
#include <optional>
#include <regex.h>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace Cal {

namespace Utils {

constexpr uint64_t fillMask64from4(uint32_t mask4) {
    uint32_t mask8 = mask4 | (static_cast<uint32_t>(mask4) << 4);
    uint32_t mask16 = mask8 | (static_cast<uint32_t>(mask8) << 8);
    uint32_t mask32 = mask16 | (static_cast<uint32_t>(mask16) << 16);
    uint64_t mask64 = mask32 | (static_cast<uint64_t>(mask32) << 32);
    return mask64;
}

constexpr uint64_t fillMask64from8(uint32_t mask8) {
    uint32_t mask16 = mask8 | (static_cast<uint32_t>(mask8) << 8);
    uint32_t mask32 = mask16 | (static_cast<uint32_t>(mask16) << 16);
    uint64_t mask64 = mask32 | (static_cast<uint64_t>(mask32) << 32);
    return mask64;
}

constexpr uint64_t fillMask64from16(uint32_t mask16) {
    uint32_t mask32 = mask16 | (static_cast<uint32_t>(mask16) << 16);
    uint64_t mask64 = mask32 | (static_cast<uint64_t>(mask32) << 32);
    return mask64;
}

constexpr uint64_t fillMask64from32(uint32_t mask32) {
    uint64_t mask64 = mask32 | (static_cast<uint64_t>(mask32) << 32);
    return mask64;
}

constexpr uint32_t popcount(uint64_t v) {
    int ret = 0;
    constexpr uint64_t maskEven = fillMask64from4(0b0101);
    constexpr uint64_t maskEvery2 = fillMask64from4(0b0011);
    constexpr uint64_t maskEvery4 = fillMask64from8(0x0F);
    constexpr uint64_t maskEvery8 = fillMask64from16(0x00FF);
    constexpr uint64_t maskEvery16 = fillMask64from32(0x0000FFFF);
    uint64_t sum = (v & maskEven) + ((v >> 1) & maskEven);
    sum = (sum & maskEvery2) + ((sum >> 2) & maskEvery2);
    sum = (sum & maskEvery4) + ((sum >> 4) & maskEvery4);
    sum = (sum & maskEvery8) + ((sum >> 8) & maskEvery8);
    sum = (sum & maskEvery16) + ((sum >> 16) & maskEvery16);
    ret = static_cast<uint32_t>((sum & 0x00000000FFFFFFFFULL) + (sum >> 32));
    return ret;
}

constexpr bool isPow2(size_t v) {
    return popcount(v) == 1;
}

template <size_t Pow2Alignment, typename T>
constexpr bool isAlignedPow2(T value) {
    static_assert(isPow2(Pow2Alignment));
    size_t asInt = 0;
    if constexpr (std::is_pointer_v<T>) {
        asInt = static_cast<size_t>(reinterpret_cast<uintptr_t>(value));
    } else {
        asInt = static_cast<size_t>(value);
    }
    auto mask = Pow2Alignment - 1;
    return 0 == (asInt & mask);
}

template <typename T>
constexpr bool isAligned(T value, size_t alignment) {
    size_t asInt = 0;
    if constexpr (std::is_pointer_v<T>) {
        asInt = static_cast<size_t>(reinterpret_cast<uintptr_t>(value));
    } else {
        asInt = static_cast<size_t>(value);
    }
    return 0 == (asInt % alignment);
}

template <size_t Pow2Alignment, typename T>
constexpr T alignUpPow2(T value) {
    static_assert(isPow2(Pow2Alignment));
    auto ret = (static_cast<size_t>(value) + Pow2Alignment - 1) & (~(Pow2Alignment - 1));
    return static_cast<T>(ret);
}

template <size_t Alignment, typename T>
constexpr T alignUp(T value) {
    auto ret = (static_cast<size_t>(value) + Alignment - 1);
    ret = ret - ret % Alignment;
    return static_cast<T>(ret);
}

template <typename T>
constexpr T alignUp(T value, size_t alignment) {
    auto ret = (static_cast<size_t>(value) + alignment - 1);
    ret = ret - ret % alignment;
    return static_cast<T>(ret);
}

inline ptrdiff_t byteDistance(const volatile void *from, const volatile void *to) {
    return reinterpret_cast<const volatile char *>(to) - reinterpret_cast<const volatile char *>(from);
}

inline size_t byteDistanceAbs(const volatile void *from, const volatile void *to) {
    auto dist = byteDistance(from, to);
    return static_cast<size_t>(dist > 0 ? dist : -dist);
}

template <typename T>
inline T *moveByBytes(T *ptr, size_t offset) {
    using CharT = std::conditional_t<std::is_volatile_v<T>, volatile char, char>;
    using CharPtrT = std::conditional_t<std::is_const_v<T>, const CharT *, CharT *>;
    return reinterpret_cast<T *>(reinterpret_cast<CharPtrT>(ptr) + offset);
}

template <size_t Pow2Alignment, typename T>
constexpr T *alignUpPow2(T *value) {
    auto before = reinterpret_cast<uintptr_t>(value);
    auto after = alignUpPow2<Pow2Alignment>(before);
    return moveByBytes(value, after - before);
}

template <size_t Alignment, typename T>
constexpr T *alignUp(T *value) {
    auto before = reinterpret_cast<uintptr_t>(value);
    auto after = alignUp<Alignment>(before);
    return moveByBytes(value, static_cast<size_t>(after - before));
}

template <typename T>
constexpr T *alignUp(T *value, size_t alignment) {
    auto before = reinterpret_cast<uintptr_t>(value);
    auto after = alignUp(before, alignment);
    return moveByBytes(value, static_cast<size_t>(after - before));
}

template <typename T>
size_t countNullterminated(T *array) {
    if (nullptr == array) {
        return 0;
    }
    auto it = array;
    while (*it) {
        ++it;
    }
    return it - array + 1; // include nullterminate
}

template <typename T>
size_t countNullterminatedKey(T *array) { // key,pair variant, only null key ends sequence
    if (nullptr == array) {
        return 0;
    }
    auto it = array;
    while (*it) {
        (it += 2);
    }
    return it - array + 1; // include nullterminate
}

inline std::string toLower(const std::string &src) {
    std::string ret = src;
    std::transform(src.begin(), src.end(), ret.begin(), [](unsigned char c) { return std::tolower(c); });
    return ret;
}

template <typename T>
inline char *asMemcpyDstT(T *ptr) {
    static_assert(std::is_standard_layout_v<T>);
    return reinterpret_cast<char *>(const_cast<std::remove_const_t<T> *>(ptr));
};

inline char *asMemcpyDstT(const void *ptr) {
    return reinterpret_cast<char *>(const_cast<void *>(ptr));
};

inline char *asMemcpyDstT(void *ptr) {
    return reinterpret_cast<char *>(const_cast<void *>(ptr));
};

constexpr size_t defaultAlignmentSize = 16U;
constexpr size_t cachelineSize = 64U;
constexpr size_t KB = 1024U;
constexpr size_t MB = KB * 1024U;
constexpr size_t GB = MB * 1024U;
constexpr size_t pageSize4KB = KB * 4U;
constexpr size_t pageSize64KB = KB * 64U;

struct CpuInfo {
    static std::optional<CpuInfo> read();
    using AddressSize = uint32_t;
    AddressSize physical = {};
    AddressSize virtual_ = {};

    bool isAccessibleByApplication(const void *va) const {
        auto mask = ~((1ULL << (virtual_ - 1)) - 1);
        return 0 == (reinterpret_cast<uintptr_t>(va) & mask);
    }
};

template <typename ElT>
inline void atomicMax(std::atomic<ElT> &atomic, ElT value) {
    auto was = atomic.load();
    while (atomic < value && (false == atomic.compare_exchange_weak(was, value))) {
    }
}

template <typename ElT>
inline void atomicMin(std::atomic<ElT> &atomic, ElT value) {
    auto was = atomic.load();
    while (atomic > value && (false == atomic.compare_exchange_weak(was, value))) {
    }
}

template <typename T>
constexpr T clz(T v) {
    static_assert((sizeof(T) == 4) || (sizeof(T) == 8));
    if constexpr (sizeof(v) == 4) {
        return __builtin_clz(v);
    } else if constexpr (sizeof(v) == 8) {
        return __builtin_clzl(v);
    } else {
        return 0;
    }
}

template <typename T>
constexpr T leadingBitNum(T v) {
    auto num0 = clz(v);
    constexpr auto numBits = sizeof(v) * 8;
    if (num0 == numBits) {
        std::abort();
    }
    return numBits - num0;
}

class CountingSemaphore { // switch to counting_semaphore in C++20
  public:
    void signal(uint32_t count) {
        std::unique_lock<std::mutex> lock(mutex);
        for (int i = 0; i < count; ++i) {
            ++counter;
            cv.notify_one();
        }
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex);
        while (counter == 0) {
            cv.wait(lock);
        }
        --counter;
    }

    template <typename DurationT>
    bool waitFor(const DurationT &duration) {
        std::unique_lock<std::mutex> lock(mutex);
        auto timerStart = std::chrono::high_resolution_clock::now();
        while (counter == 0) {
            auto waitedUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timerStart);
            bool overdue = waitedUs > std::chrono::duration_cast<std::chrono::microseconds>(duration);
            if (overdue) {
                return false;
            }
            if (std::cv_status::timeout == cv.wait_for(lock, std::chrono::microseconds(std::chrono::duration_cast<std::chrono::microseconds>(duration) - waitedUs))) {
                return false;
            }
        }
        --counter;
        return true;
    }

    uint32_t peek() const {
        return counter;
    }

    void reset(uint32_t counter = 0) {
        this->counter = counter;
        cv.notify_all();
    }

  protected:
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic_uint32_t counter = 0;
};

std::string getProcessName();
std::filesystem::path getProcessPath();

class Smatch {
  public:
    Smatch() = default;

    Smatch(const char *text, const regmatch_t &regmatch) {
        if (regmatch.rm_so != -1 && regmatch.rm_eo != -1) {
            match = std::string{text + regmatch.rm_so, static_cast<size_t>(regmatch.rm_eo - regmatch.rm_so)};
        }
    }

    std::string str() const {
        return match;
    }

  private:
    std::string match{};
};

class Regex {
  public:
    Regex(const char *regexStr);
    ~Regex();

    bool matches(const char *text);
    bool matches(const char *text, std::vector<Smatch> &matches);

    Regex(const Regex &) = delete;
    Regex(Regex &&) = delete;
    Regex &operator=(const Regex &) = delete;
    Regex &operator=(Regex &&) = delete;

  private:
    regex_t regex;
};

inline size_t getBufferRectSizeInBytes(const size_t region[3], size_t rowPitch, size_t slicePitch) {
    if ((0 == region[0]) || (0 == region[1]) || (0 == region[2])) {
        return 0;
    }

    if (0 == rowPitch) {
        rowPitch = region[0];
    }

    if (0 == slicePitch) {
        slicePitch = rowPitch * region[1];
    }

    size_t size = region[2] * slicePitch;
    return size;
}

char *getCalEnv(std::string_view name);
bool getCalEnvFlag(std::string_view name, bool defaultValue);
inline bool getCalEnvFlag(std::string_view name) {
    return getCalEnvFlag(name, false);
}
int64_t getCalEnvI64(std::string_view name, int64_t defaultValue);

struct AddressRange {
    AddressRange() = default;

    AddressRange(uintptr_t start, uintptr_t end) : start(start), end(end) {
    }

    AddressRange(uint32_t start, uint32_t end) : start(start), end(end) {
    }

    AddressRange(const void *start, void *end)
        : start(reinterpret_cast<uintptr_t>(start)), end(reinterpret_cast<uintptr_t>(end)) {
    }

    AddressRange(const void *start, size_t size)
        : start(reinterpret_cast<uintptr_t>(start)), end(reinterpret_cast<uintptr_t>(start) + size) {
    }

    AddressRange(const void *start)
        : start(reinterpret_cast<uintptr_t>(start)), end(reinterpret_cast<uintptr_t>(start) + 1) {
    }

    AddressRange(uintptr_t start)
        : start(start), end(start + 1) {
    }

    bool contains(AddressRange el) const {
        return (el.start >= this->start) && (el.start < this->end) && (el.end <= this->end);
    }

    bool intersects(AddressRange el) const {
        return false == ((el.end <= this->start) || (this->end <= el.start) || (el.start >= this->end) || (this->start >= el.end));
    }

    void *base() const {
        return reinterpret_cast<void *>(start);
    }

    void *rightBound() const {
        return reinterpret_cast<void *>(end);
    }

    size_t size() const {
        return end - start;
    }

    uintptr_t start = 0;
    uintptr_t end = std::numeric_limits<uintptr_t>::max();
};

inline bool operator==(const AddressRange &lhs, const AddressRange &rhs) {
    return (lhs.start == rhs.start) && (lhs.end == rhs.end);
}

inline bool operator!=(const AddressRange &lhs, const AddressRange &rhs) {
    return !(lhs == rhs);
}

template <typename ValueT>
struct Tag {
    Tag() = default;
    Tag(const ValueT *v) : value(*v) {}
    ValueT value;
};

template <>
struct Tag<void> {
    Tag() = default;
    Tag(const void *) {}
};

template <typename TagValueT = void>
class PartitionedAddressRange {
  public:
    using PartitionedAddressRangeT = PartitionedAddressRange<TagValueT>;
    using TagT = Tag<TagValueT>;

    PartitionedAddressRange(AddressRange desc) : desc(desc) {
    }

    template <typename T = TagValueT>
    static auto tagged(AddressRange desc, const T &tagValue)
        -> std::enable_if_t<false == std::is_void_v<T>, PartitionedAddressRangeT> {
        PartitionedAddressRangeT ret{desc};
        ret.tag.value = tagValue;
        return ret;
    }

    void insertSubRange(PartitionedAddressRangeT &&subRange) {
        if (false == desc.contains(subRange.desc)) {
            if (subRange.desc.start < desc.start) {
                desc.start = subRange.desc.start;
            }
            if (subRange.desc.end > desc.end) {
                desc.end = subRange.desc.end;
            }
        }
        auto comparator = +[](const uintptr_t &start, const PartitionedAddressRangeT &rhs) {
            return rhs.desc.start > start;
        };
        auto pos = std::upper_bound(subRanges.begin(), subRanges.end(), subRange.desc.start, comparator);
        subRanges.insert(pos, std::move(subRange));
    }

    void insertSubRange(AddressRange subRange) {
        this->insertSubRange(PartitionedAddressRange{subRange});
    }

    PartitionedAddressRangeT *findSubRange(AddressRange desc) {
        auto comparator = +[](const PartitionedAddressRangeT &lhs, const uintptr_t start) {
            return lhs.desc.end <= start;
        };
        if (false == this->desc.contains(desc)) {
            return nullptr;
        }
        auto pos = std::lower_bound(subRanges.begin(), subRanges.end(), desc.start, comparator);
        if (subRanges.end() == pos) {
            return nullptr;
        }
        return pos->desc.contains(desc) ? &*pos : nullptr;
    }

    bool intersectsSubRanges(AddressRange desc) const {
        auto pos = this->getIntersectedSubRangesPos(desc);
        if (subRanges.end() == pos) {
            return false;
        }

        return pos->desc.intersects(desc);
    }

    std::vector<PartitionedAddressRangeT *> getIntersectedSubRanges(AddressRange desc) {
        auto pos = this->getIntersectedSubRangesPos(desc);
        std::vector<PartitionedAddressRangeT *> ret;
        while ((subRanges.end() != pos) && pos->getBoundingRange().intersects(desc)) {
            ret.push_back(&*pos);
            ++pos;
        }

        return ret;
    }

    std::vector<AddressRange> getSubRangesDiffFrom(AddressRange lhs) {
        std::vector<PartitionedAddressRangeT *> intersection = this->getIntersectedSubRanges(lhs);
        if (intersection.empty()) {
            return {lhs};
        }

        std::vector<AddressRange> ret;
        auto intersectIt = intersection.begin();
        if (lhs.start < (*intersectIt)->getBoundingRange().start) {
            ret.push_back({lhs.start, (*intersection.begin())->getBoundingRange().start});
        }

        auto lastEnd = (*intersectIt)->getBoundingRange().end;
        ++intersectIt;
        while (intersectIt != intersection.end()) {
            auto start = (*intersectIt)->getBoundingRange().start;
            if (start != lastEnd) {
                ret.push_back({lastEnd, start});
            }
            lastEnd = (*intersectIt)->getBoundingRange().end;
            ++intersectIt;
        }

        if (lhs.end > lastEnd) {
            ret.push_back({lastEnd, lhs.end});
        }

        return ret;
    }

    void mergeSubranges() {
        if (subRanges.size() < 2) {
            return;
        }

        auto rit = subRanges.rbegin();
        while (rit != subRanges.rend()) {
            auto prev = rit + 1;
            if (prev == subRanges.rend()) {
                break;
            }
            if (prev->desc.end != rit->desc.start) {
                rit = prev;
                continue;
            }

            auto prevPrev = prev + 1;
            while (prevPrev != subRanges.rend()) {
                if (prevPrev->desc.end != prev->desc.start) {
                    break;
                }
                prev = prevPrev;
                ++prevPrev;
            }

            PartitionedAddressRangeT mergedRange({prev->desc.start, rit->desc.end});

            auto mergedBeg = prev.base() - 1;
            auto mergedEnd = rit.base();
            for (auto mergedIt = mergedBeg; mergedIt != mergedEnd; ++mergedIt) {
                mergedRange.insertSubRange(std::move(*mergedIt));
            }
            *prev = std::move(mergedRange);
            rit = prevPrev;
            subRanges.erase(mergedBeg + 1, mergedEnd);
        }
    }

    int destroySubRange(AddressRange range) { // returns number of affected subranges
        auto pos = this->getIntersectedSubRangesPos(range);
        if (subRanges.end() == pos) {
            return 0;
        }
        if (range == pos->getBoundingRange()) {
            subRanges.erase(pos);
            return 1;
        }

        if (pos->getBoundingRange().contains(range)) {
            if (pos->desc.start == range.start) {
                pos->destroySubRange(range);
                pos->desc.start = range.end;
            } else if (pos->desc.end == range.end) {
                pos->destroySubRange(range);
                pos->desc.end = range.start;
            } else { // split range
                PartitionedAddressRange rhs = *pos;
                pos->destroySubRange({range.start, pos->desc.end});
                pos->desc.end = range.start;
                rhs.destroySubRange({pos->desc.start, range.end});
                rhs.desc.start = range.end;
                this->insertSubRange(std::move(rhs));
            }
            return 1;
        }

        auto destroyCompletelyBegin = pos;
        if (destroyCompletelyBegin->desc.start < range.start) {
            ++destroyCompletelyBegin;
        }

        auto destroyCompletelyEnd = destroyCompletelyBegin;
        while ((subRanges.end() != destroyCompletelyEnd) && (range.contains(destroyCompletelyEnd->getBoundingRange()))) {
            ++destroyCompletelyEnd;
        }

        auto numImpacted = destroyCompletelyEnd - pos;
        if (subRanges.end() != destroyCompletelyEnd) {
            if (range.intersects(destroyCompletelyEnd->getBoundingRange())) {
                destroyCompletelyEnd->destroySubRange(range);
                destroyCompletelyEnd->desc.start = range.end;
                ++numImpacted;
            }
        }
        if (pos != destroyCompletelyBegin) {
            pos->destroySubRange(range);
            pos->desc.end = range.start;
        }

        subRanges.erase(destroyCompletelyBegin, destroyCompletelyEnd);

        return numImpacted;
    }

    const std::vector<PartitionedAddressRangeT> &getSubRanges() const {
        return subRanges;
    }

    AddressRange getBoundingRange() const {
        return desc;
    }

    template <typename T = TagValueT>
    auto getTag() const
        -> std::enable_if_t<false == std::is_void_v<T>, const T &> {
        return tag.value;
    }

  protected:
    typename std::vector<PartitionedAddressRangeT>::iterator getIntersectedSubRangesPos(AddressRange desc) {
        auto comparator = +[](const PartitionedAddressRangeT &lhs, const uintptr_t start) {
            return lhs.desc.end <= start;
        };
        if (false == this->desc.intersects(desc)) {
            return subRanges.end();
        }
        return std::lower_bound(subRanges.begin(), subRanges.end(), desc.start, comparator);
    }

    typename std::vector<PartitionedAddressRangeT>::const_iterator getIntersectedSubRangesPos(AddressRange desc) const {
        auto comparator = +[](const PartitionedAddressRangeT &lhs, const uintptr_t start) {
            return lhs.desc.end <= start;
        };
        if (false == this->desc.intersects(desc)) {
            return subRanges.end();
        }
        return std::lower_bound(subRanges.begin(), subRanges.end(), desc.start, comparator);
    }

    AddressRange desc;
    std::vector<PartitionedAddressRangeT> subRanges;
    TagT tag;
};

class Heap {
  public:
    Heap() : vma({0U, 0U}) {
    }

    Heap(AddressRange vaRange) : vma(vaRange) {
    }

    void *alloc(size_t sizeInBytes, size_t alignment);

    void *alloc(size_t sizeInBytes) {
        return alloc(sizeInBytes, 16);
    }

    void free(void *addr);

    AddressRange getRange() const {
        return vma.getBoundingRange();
    }

    size_t getSizeUsed() const {
        return sizeUsed;
    }

    size_t getSizeLeft() const {
        return vma.getBoundingRange().size() - sizeUsed;
    }

  protected:
    void commitRange(AddressRange range) {
        vma.insertSubRange(range);
        sizeUsed += range.size();
    }

    void freeRange(AddressRange range) {
        vma.destroySubRange(range);
        sizeUsed -= range.size();
    }

    PartitionedAddressRange<void> vma;
    size_t sizeUsed = 0U;
};

std::string getPathForTempFiles();

inline std::vector<std::string> split(const std::string &input, const char *delimiter) {
    std::vector<std::string> outVector;
    size_t pos = 0;

    while (pos < input.size()) {
        size_t nextDelimiter = input.find_first_of(delimiter, pos);
        outVector.emplace_back(input.substr(pos, std::min(nextDelimiter, input.size()) - pos));

        pos = nextDelimiter;
        if (pos != std::string::npos) {
            pos++;
        }
    }

    return outVector;
}

bool isDebuggerConnected();

} // namespace Utils
} // namespace Cal
