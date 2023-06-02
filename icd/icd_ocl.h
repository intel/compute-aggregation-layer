/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/icd_global_state.h"
#include "icd/icd_kernel_arg_cache.h"
#include "icd/icd_page_fault_manager.h"
#include "icd/icd_platform.h"
#include "shared/ipc.h"
#include "shared/ocl_fat_def.h"
#include "shared/ref_counted.h"
#include "shared/rpc.h"
#include "shared/usm.h"

#include <atomic>
#include <cstdlib>
#include <limits>
#include <mutex>
#include <unordered_map>

extern cl_icd_dispatch clIcdDispatchTable;

struct cl_icd_base {
    cl_icd_dispatch *dt = &clIcdDispatchTable;
};

template <typename LocalObjectType>
struct cl_icd_base_mapped : cl_icd_base {
    using LocalObjectT = LocalObjectType;
    LocalObjectT *asLocalObject() {
        ensureIsLocalObjet();
        return static_cast<LocalObjectT *>(this);
    }
    const LocalObjectT *asLocalObject() const {
        ensureIsLocalObjet();
        return static_cast<LocalObjectT *>(this);
    }

    void ensureIsLocalObjet() {
        if (this->isRemote()) {
            log<Verbosity::critical>("Attempted to use remote object as local object");
            std::abort();
        }
    }

    bool isLocal() const {
        return this->dt == &clIcdDispatchTable;
    }

    bool isRemote() const {
        return false == this->isLocal();
    }
};

struct IcdOclTypePrinter {
    template <typename OclObjT>
    static const char *getObjectTypeAsStr() {
        if constexpr (std::is_same_v<OclObjT, cl_platform_id>) {
            return "cl_platform_id";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_platform_id>) {
            return "_cl_platform_id";
        }

        if constexpr (std::is_same_v<OclObjT, cl_device_id>) {
            return "cl_device_id";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_device_id>) {
            return "_cl_device_id";
        }

        if constexpr (std::is_same_v<OclObjT, cl_context>) {
            return "cl_context";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_context>) {
            return "_cl_context";
        }

        if constexpr (std::is_same_v<OclObjT, cl_command_queue>) {
            return "cl_command_queue";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_command_queue>) {
            return "_cl_command_queue";
        }

        if constexpr (std::is_same_v<OclObjT, cl_program>) {
            return "cl_program";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_program>) {
            return "_cl_program";
        }

        if constexpr (std::is_same_v<OclObjT, cl_kernel>) {
            return "cl_kernel";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_kernel>) {
            return "_cl_kernel";
        }

        if constexpr (std::is_same_v<OclObjT, cl_mem>) {
            return "cl_mem";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_mem>) {
            return "_cl_mem";
        }

        if constexpr (std::is_same_v<OclObjT, cl_event>) {
            return "cl_event";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_event>) {
            return "_cl_event";
        }

        if constexpr (std::is_same_v<OclObjT, cl_sampler>) {
            return "cl_sampler";
        }

        if constexpr (std::is_same_v<OclObjT, _cl_sampler>) {
            return "_cl_sampler";
        }

        return "unknown";
    }
};

template <typename OclObjectType>
auto asLocalObjectOrNull(OclObjectType *obj) {
    return obj ? obj->asLocalObject() : nullptr;
}

namespace Cal {
namespace Icd {
namespace Ocl {
class IcdOclPlatform;
struct IcdOclDevice;
struct IcdOclContext;
struct IcdOclCommandQueue;
struct IcdOclProgram;
struct IcdOclKernel;
struct IcdOclMem;
struct IcdOclEvent;
struct IcdOclSampler;
} // namespace Ocl
} // namespace Icd
} // namespace Cal

struct _cl_platform_id : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclPlatform> {};
struct _cl_device_id : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclDevice> {};
struct _cl_context : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclContext> {};
struct _cl_command_queue : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclCommandQueue> {};
struct _cl_program : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclProgram> {};
struct _cl_kernel : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclKernel> {};
struct _cl_mem : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclMem> {};
struct _cl_event : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclEvent> {};
struct _cl_sampler : cl_icd_base_mapped<Cal::Icd::Ocl::IcdOclSampler> {};

namespace Cal {
namespace Icd {
namespace Ocl {
cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms);
cl_int clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
cl_int clGetProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
void *clGetExtensionFunctionAddress(const char *funcname);
cl_kernel clCreateKernel(cl_program program, const char *kernel_name, cl_int *errcode_ret);
cl_int clCreateKernelsInProgram(cl_program program, cl_uint num_kernels, cl_kernel *kernels, cl_uint *num_kernels_ret);
void *clSVMAlloc(cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment);
void *clHostMemAllocINTEL(cl_context context, const cl_mem_properties_intel *properties, size_t size, cl_uint alignment, cl_int *errcode_ret);
void *clSharedMemAllocINTEL(cl_context context, cl_device_id device, const cl_mem_properties_intel *properties, size_t size, cl_uint alignment, cl_int *errcode_ret);
cl_int clEnqueueMemcpyINTEL(cl_command_queue commandQueue, cl_bool blocking, void *dstPtr, const void *srcPtr, size_t size, cl_uint numEventsInWaitList, const cl_event *eventWaitList, cl_event *event);
cl_int clEnqueueSVMMemcpy(cl_command_queue commandQueue, cl_bool blocking, void *dstPtr, const void *srcPtr, size_t size, cl_uint numEventsInWaitList, const cl_event *eventWaitList, cl_event *event);
cl_mem clCreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret);
cl_int clEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
cl_int clEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
cl_int clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool write_read, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
cl_int clEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
cl_int clGetHostTimer(cl_device_id device, cl_ulong *host_timestamp);

cl_int clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value);
cl_int clSetKernelArgMemPointerINTEL(cl_kernel kernel, cl_uint argIndex, const void *argValue);
cl_int clSetKernelArgSVMPointer(cl_kernel kernel, cl_uint argIndex, const void *argValue);
cl_int clGetMemObjectInfo(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);

cl_int clReleaseMemObject(cl_mem memobj);

size_t getTexelSizeBytes(const cl_image_format *imageFormat);

inline PageFaultManager::Placement getSharedAllocationPlacement(const cl_mem_properties_intel *properties) {
    auto placement = PageFaultManager::Placement::HOST;
    if (properties != nullptr) {
        for (int i = 0; properties[i] != 0; i += 2) {
            if (properties[i] == CL_MEM_ALLOC_FLAGS_INTEL) {
                auto allocflags = static_cast<cl_mem_alloc_flags_intel>(properties[i + 1]);
                if (allocflags & CL_MEM_ALLOC_INITIAL_PLACEMENT_DEVICE_INTEL) {
                    placement = PageFaultManager::Placement::DEVICE;
                }
                if (allocflags & CL_MEM_ALLOC_INITIAL_PLACEMENT_HOST_INTEL) {
                    placement = PageFaultManager::Placement::HOST;
                }
                break;
            }
        }
    }
    return placement;
}

struct OclImageTraits {
    OclImageTraits() = default;
    OclImageTraits(const cl_image_format *imageFormat, const cl_image_desc *imageDesc) {
        elementStrideBytes = getTexelSizeBytes(imageFormat);
        if (imageDesc) {
            this->imageWidth = imageDesc->image_width;
            this->imageHeight = imageDesc->image_height;
        }
    }

    OclImageTraits(const cl_image_format *imageFormat, size_t imageWidth, size_t imageHeight, size_t imageRowPitch) {
        this->elementStrideBytes = getTexelSizeBytes(imageFormat);
        this->imageWidth = imageWidth;
    }

    OclImageTraits(const cl_image_format *imageFormat, size_t imageWidth, size_t imageHeight, size_t imageDepth, size_t imageRowPitch, size_t imageSlicePitch) {
        this->elementStrideBytes = getTexelSizeBytes(imageFormat);
        this->imageWidth = imageWidth;
        this->imageHeight = imageHeight;
    }

    size_t getElementStrideBytes() const {
        return this->elementStrideBytes;
    }

    size_t getRowStandardLayoutStrideBytes() const {
        return elementStrideBytes * imageWidth;
    }

    size_t getSliceStandardLayoutStrideBytes() const {
        return getRowStandardLayoutStrideBytes() * imageHeight;
    }

  protected:
    size_t elementStrideBytes = 0U;
    size_t imageWidth = 0U;
    size_t imageHeight = 0U;
};

struct IcdOclMem : Cal::Shared::RefCountedWithParent<_cl_mem, IcdOclTypePrinter> {
    ~IcdOclMem();
    using RefCountedWithParent::RefCountedWithParent;
    void *hostPtr = nullptr;
    void *apiHostPtr = nullptr;
    size_t size = 0U;
    cl_mem_flags flags = 0U;
    IcdOclContext *parent = nullptr;

    IcdOclContext *getContext() const {
        return parent;
    }

    void setImageTraits(OclImageTraits imageTraits) {
        this->imageTraits = imageTraits;
    }

    const OclImageTraits &getImageTraits() const {
        return imageTraits;
    }

  protected:
    OclImageTraits imageTraits = {};
};

struct ClBufferRecycler {
    static constexpr size_t minBucketSize = 64 * Cal::Utils::KB;
    static constexpr size_t maxBucketSize = 128 * Cal::Utils::MB;
    size_t allowedReuseSizeTotal = 0;
    float reuseSingleWasteTolerance = 5.0f / 100.f; // can be at most 5% smaller // control by ENV/AIL

    ClBufferRecycler() {
        this->allowedReuseSizeTotal = Cal::Utils::getCalEnvI64(calIcdBufferRecycleEnvName, 0) * Cal::Utils::MB;

        size_t leftBound = 0U;
        size_t rightBound = minBucketSize;
        while (rightBound <= maxBucketSize) {
            buckets.resize(buckets.size() + 1);
            buckets.rbegin()->leftBound = leftBound;
            buckets.rbegin()->rightBound = rightBound;

            leftBound = rightBound + 1;
            rightBound *= 2;
        }
    }

    struct Statistics {
        size_t hitsCount = 0U;
        size_t missesCount = 0U;
        size_t reuseTotal = 0U;
        size_t wasteTotal = 0U;
        size_t maxWaitedBuffersCount = 0U;
        size_t maxWaitedBuffersTotalSize = 0U;

        void dumpToLog(size_t sizeMin, size_t sizeMax) const {
            if constexpr (Cal::Utils::enablePerformanceLogs) {
                log<Verbosity::performance>("cl_mem reuse statistics for sizes in range (%zuKB - %zuKB] BEGIN :", sizeMin / 1024, sizeMax / 1024);
                if ((0 == hitsCount) && (0 == missesCount)) {
                    log<Verbosity::performance>(" * range unused (0 hits, 0 misses)");
                } else {
                    log<Verbosity::performance>(" * hit rate : %f% (%zu hits, %zu misses)", int((((float)(hitsCount) / hitsCount + missesCount) * 10000)) / 100.0f, hitsCount, missesCount);
                    log<Verbosity::performance>(" * reuse total : %zuB = %zuKB = %fMB", reuseTotal, reuseTotal / 1024, (reuseTotal / 1024) / 1024.0f);
                    log<Verbosity::performance>(" * waste total : %zuB = %zuKB = %fMB", wasteTotal, wasteTotal / 1024, (wasteTotal / 1024) / 1024.0f);
                    log<Verbosity::performance>(" * waste ratio : %f% ", int((((float)(wasteTotal) / reuseTotal + wasteTotal) * 10000)) / 100.0f);
                    log<Verbosity::performance>(" * peek recycled buffer count : %zu", maxWaitedBuffersCount);
                    log<Verbosity::performance>(" * peek recycled buffer total size : %zuB = %zuKB = %fMB", maxWaitedBuffersTotalSize, maxWaitedBuffersTotalSize / 1024, (wasteTotal / 1024) / 1024.0f);
                }
                log<Verbosity::performance>("cl_mem reuse statistics for sizes in range (%zuKB - %zuKB] END", sizeMin / 1024, sizeMax / 1024);
            }
        }
    };

    struct RecycleListBucket {
        size_t leftBound = 0U;
        size_t rightBound = 0U;
        std::vector<IcdOclMem *> objects;

        size_t currentRecycleSizeTotal = {};
        size_t currentRecycleCountTotal = 0;

        Statistics statistics;

        bool tryRecycleClBuffer(cl_mem mem) {
            objects.push_back(mem->asLocalObject());
            currentRecycleSizeTotal += mem->asLocalObject()->size;
            ++currentRecycleCountTotal;
            if constexpr (Cal::Utils::enablePerformanceLogs) {
                statistics.maxWaitedBuffersCount = std::max(statistics.maxWaitedBuffersCount, currentRecycleCountTotal);
                statistics.maxWaitedBuffersTotalSize = std::max(statistics.maxWaitedBuffersTotalSize, currentRecycleSizeTotal);
            }
            return true;
        }

        cl_mem tryGetRecycledClBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret, float reuseSingleWasteTolerance) {
            if (objects.empty() || (currentRecycleSizeTotal < size)) {
                if constexpr (Cal::Utils::enablePerformanceLogs) {
                    ++statistics.missesCount;
                }
                return nullptr;
            }
            auto it = objects.begin();
            auto end = objects.end();
            auto bestFit = end;
            uint32_t fitLevel = 0;
            float bestFitWaste = 1.0f;
            if (0 == (flags & CL_MEM_USE_HOST_PTR)) {
                host_ptr = nullptr; // take into account only if USE_HOST_PTR
            }
            while (it < end) {
                if ((*it)->flags != flags) {
                    ++it;
                    continue;
                }
                if ((*it)->size < size) {
                    ++it;
                    continue;
                }

                auto waste = ((*it)->size - size) / float((*it)->size);
                auto hostPtrMatch = (*it)->apiHostPtr == host_ptr;

                // for CL_MEM_USE_HOST_PTR we must match host_ptr
                if ((flags | CL_MEM_USE_HOST_PTR) && !hostPtrMatch) {
                    ++it;
                    continue;
                }

                if (waste == 0 && hostPtrMatch) {
                    bestFit = it;
                    bestFitWaste = waste;
                    break;
                }

                if ((waste < bestFitWaste && hostPtrMatch && fitLevel == 2u) ||
                    (waste <= reuseSingleWasteTolerance && hostPtrMatch && fitLevel < 2u)) {
                    bestFit = it;
                    bestFitWaste = waste;
                    fitLevel = 2u;
                }

                if ((waste < bestFitWaste && fitLevel == 1u) ||
                    (waste <= reuseSingleWasteTolerance && fitLevel < 1u)) {
                    bestFit = it;
                    bestFitWaste = waste;
                    fitLevel = 1u;
                }

                ++it;
            }
            if ((end == bestFit) || (bestFitWaste > reuseSingleWasteTolerance)) {
                if constexpr (Cal::Utils::enablePerformanceLogs) {
                    ++statistics.missesCount;
                }
                return nullptr;
            }

            auto recycledBuffer = *bestFit;
            currentRecycleSizeTotal -= recycledBuffer->size;
            --currentRecycleCountTotal;
            if (bestFit - objects.begin() != (static_cast<int64_t>(objects.size()) - 1)) {
                *bestFit = *objects.rbegin();
            }
            objects.pop_back();

            if constexpr (Cal::Utils::enablePerformanceLogs) {
                ++statistics.hitsCount;
                statistics.reuseTotal += size;
                auto waste = recycledBuffer->size - size;
                if (waste) {
                    statistics.wasteTotal += waste;
                }
            }
            return recycledBuffer;
        }

        void cleanup() {
            for (auto &obj : objects) {
                Cal::Icd::Ocl::clReleaseMemObject(obj);
            }
            this->statistics.dumpToLog(leftBound, rightBound);
        }

        void dumpStatsToLog() const {
            this->statistics.dumpToLog(leftBound, rightBound);
        }
    };

    std::mutex mutex;
    std::vector<RecycleListBucket> buckets; // pow2 * 64KB <= maxAllowedBucketSize

    std::atomic<size_t> currentRecycleSizeTotal = {};
    size_t currentRecycleCountTotal = 0;
    Statistics statistics;

    static size_t getBucketIdForSize(size_t size) {
        if (size <= minBucketSize) {
            return 0U;
        }

        size_t bucketId = 0U;
        auto over = size / minBucketSize;
        auto shift = Cal::Utils::leadingBitNum(over) - 1;
        bucketId += shift;
        if ((minBucketSize << shift) != size) {
            ++bucketId;
        }
        return bucketId;
    }

    bool tryRecycleClBuffer(cl_mem mem) {
        if (isCleaningUp) {
            return false;
        }
        auto memObject = mem->asLocalObject();
        if (memObject->peekRefCount() > 1) {
            return false;
        }
        if (memObject->size == 0) {
            return false;
        }

        if (memObject->size > maxBucketSize) {
            return false;
        }

        if (currentRecycleSizeTotal + memObject->size > allowedReuseSizeTotal) {
            return false;
        }

        size_t bucketId = getBucketIdForSize(memObject->size);

        std::unique_lock<std::mutex> lock(mutex);

        if (currentRecycleSizeTotal + memObject->size > allowedReuseSizeTotal) {
            return false;
        }

        if (false == buckets[bucketId].tryRecycleClBuffer(mem)) {
            return false;
        }

        currentRecycleSizeTotal += memObject->size;
        ++currentRecycleCountTotal;

        if constexpr (Cal::Utils::enablePerformanceLogs) {
            statistics.maxWaitedBuffersCount = std::max(statistics.maxWaitedBuffersCount, currentRecycleCountTotal);
            statistics.maxWaitedBuffersTotalSize = std::max(statistics.maxWaitedBuffersTotalSize, currentRecycleSizeTotal.load());
        }

        return true;
    }

    cl_mem tryGetRecycledClBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret) {
        if (isCleaningUp) {
            return nullptr;
        }
        if (size > maxBucketSize) {
            return nullptr;
        }

        if (currentRecycleSizeTotal < size) {
            return nullptr;
        }

        size_t bucketId = getBucketIdForSize(size);

        std::unique_lock<std::mutex> lock(mutex);

        if (currentRecycleSizeTotal < size) {
            return nullptr;
        }

        auto recycledBuffer = buckets[bucketId].tryGetRecycledClBuffer(context, flags, size, host_ptr, errcode_ret, reuseSingleWasteTolerance);
        if (nullptr == recycledBuffer) {
            if constexpr (Cal::Utils::enablePerformanceLogs) {
                ++statistics.missesCount;
                statistics.maxWaitedBuffersTotalSize = std::max(statistics.maxWaitedBuffersTotalSize, currentRecycleSizeTotal.load());
            }
            return nullptr;
        }
        currentRecycleSizeTotal -= recycledBuffer->asLocalObject()->size;
        --currentRecycleCountTotal;

        if constexpr (Cal::Utils::enablePerformanceLogs) {
            ++statistics.hitsCount;
            statistics.reuseTotal += size;
            auto waste = recycledBuffer->asLocalObject()->size - size;
            if (waste) {
                statistics.wasteTotal += waste;
            }
        }
        return recycledBuffer;
    }

    void cleanup() {
        isCleaningUp = true;
        for (auto &bucket : buckets) {
            bucket.cleanup();
        }
        this->statistics.dumpToLog(0, maxBucketSize);
        isCleaningUp = false;
    }

    void dumpStatsToLog() const {
        for (auto &bucket : buckets) {
            bucket.dumpStatsToLog();
        }
        this->statistics.dumpToLog(0, maxBucketSize);
    }

    std::atomic_bool isCleaningUp = false;
};

struct InfoCache {
    struct Entry {
        cl_uint paramName = {};
        size_t paramValueSize = {};
        uint8_t *paramValue = nullptr;
    };

    bool find(cl_uint paramName, void *paramValue, size_t *paramValueSize) {
        std::shared_lock lock(mutex);
        auto it = findImpl(paramName);
        if (it != cache.end()) {
            if (paramValue) {
                if (it->paramValue) {
                    memcpy(paramValue, it->paramValue, it->paramValueSize);
                } else {
                    return false;
                }
            }
            if (paramValueSize) {
                *paramValueSize = it->paramValueSize;
            }
            return true;
        }
        return false;
    }

    void store(cl_uint paramName, void *paramValue, size_t paramValueSize) {
        std::lock_guard<std::shared_mutex> lock(mutex);
        auto it = findImpl(paramName);
        auto &entry = it != cache.end() ? *it : cache.emplace_back();
        entry.paramValueSize = paramValueSize;
        entry.paramName = paramName;
        if (paramValue) {
            entry.paramValue = new uint8_t[entry.paramValueSize];
            memcpy(entry.paramValue, paramValue, entry.paramValueSize);
        }
    }

    ~InfoCache() {
        for (auto &entry : cache) {
            delete[] entry.paramValue;
        }
    }

  protected:
    std::vector<Entry>::iterator findImpl(cl_uint paramName) {
        for (auto it = cache.begin(); it != cache.end(); ++it) {
            if (it->paramName == paramName) {
                return it;
            }
        }
        return cache.end();
    }

    std::vector<Entry> cache;
    std::shared_mutex mutex;
};

struct IcdOclDevice : Cal::Shared::RefCountedWithParent<_cl_device_id, IcdOclTypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
    bool isSubDevice = false;
    InfoCache cache;
};

struct IcdOclContext : Cal::Shared::RefCountedWithParent<_cl_context, IcdOclTypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;

    IcdOclContext(cl_context remoteObject, Cal::Shared::SingleReference &&parent,
                  Cal::Shared::RefCounted<_cl_context, IcdOclTypePrinter>::CleanupFuncT cleanupFunc);

    ~IcdOclContext() override {
        Cal::Icd::icdGlobalState.unregisterAtExit(this);
        clBufferRecycler.cleanup();
        for (auto &device : this->devices) {
            if (device) {
                static_cast<IcdOclDevice *>(device)->dec();
            }
        }
    }

    void beforeReleaseCallback();
    void globalReleaseCallback() {
        clBufferRecycler.dumpStatsToLog();
    }

    cl_mem tryGetRecycledClBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret);
    bool tryRecycleClBuffer(cl_mem mem);
    void setDevicesList(size_t numDevices, const cl_device_id *devices);

    std::vector<cl_device_id> devices;
    ClBufferRecycler clBufferRecycler;
    InfoCache cache;
    cl_command_queue implicitQueue = nullptr;
    bool skipTransferOnHostPtrMatch = false;
};

struct IcdOclCommandQueue : Cal::Shared::RefCountedWithParent<_cl_command_queue, IcdOclTypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
    std::atomic<int> enqueueCount{};
    std::atomic<int> currentWaitedCount{};
    uint32_t subDeviceIndex = 0u;

    bool isSynchronized() const {
        return (enqueueCount <= currentWaitedCount);
    }

    void synchronizeNow() {
        currentWaitedCount = enqueueCount.load();
        this->cleanTemporaryAllocations();
    }

    void enqueue() {
        ++enqueueCount;
    }

    void registerTemporaryAllocation(std::unique_ptr<void, Cal::Rpc::ChannelClient::ChannelSpaceDeleter> alloc) {
        std::lock_guard<std::mutex> lock(temporaryAllocations.mutex);
        temporaryAllocations.allocations.push_back(std::move(alloc));
    }

    void cleanTemporaryAllocations() {
        std::vector<std::unique_ptr<void, Cal::Rpc::ChannelClient::ChannelSpaceDeleter>> tmp;
        {
            std::lock_guard<std::mutex> lock(temporaryAllocations.mutex);
            tmp.swap(temporaryAllocations.allocations);
        }

        if (tmp.empty()) {
            return;
        }

        auto &channel = tmp[0].get_deleter().getChannel();
        auto channelLock = channel.lock();
        tmp.clear();
    }

    struct {
        std::mutex mutex;
        std::vector<std::unique_ptr<void, Cal::Rpc::ChannelClient::ChannelSpaceDeleter>> allocations;
    } temporaryAllocations;

    InfoCache cache;
};

struct IcdOclProgram : Cal::Shared::RefCountedWithParent<_cl_program, IcdOclTypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;

    void storeSizesOfBinaries(void *paramValue, size_t paramValueSize);
    std::vector<size_t> getBinariesSizes();

  protected:
    std::vector<size_t> binariesSizes;
    std::mutex binariesSizesMutex;
};

struct IcdOclEvent : Cal::Shared::RefCountedWithParent<_cl_event, IcdOclTypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};
struct IcdOclSampler : Cal::Shared::RefCountedWithParent<_cl_sampler, IcdOclTypePrinter> {
    using RefCountedWithParent::RefCountedWithParent;
};

struct IcdOclKernel : Cal::Shared::RefCountedWithParent<_cl_kernel, IcdOclTypePrinter> {
    struct ArgTraits {
        bool isPointer = false;
    };
    using RefCountedWithParent::RefCountedWithParent;

    bool initTraits();
    bool initTraits(const IcdOclKernel *source);

    void convertClMemArgIfNeeded(uint32_t argIndex, size_t argSize, void *argData) {
        if (false == argsTraits[argIndex].isPointer) {
            return;
        }
        if (sizeof(argSize) != sizeof(cl_mem)) {
            log<Verbosity::error>("Invalid cl_mem arg size");
            return;
        }
        *static_cast<cl_mem *>(argData) = static_cast<IcdOclMem *>(*(reinterpret_cast<cl_mem *>(argData)))->asRemoteObject();
    }
    KernelArgCache clSetKernelArgCache;

    void moveArgsToGpu();
    void storeKernelArg(const void *argValue, uint32_t argNum) {
        if (allocationsToMigrate.size() < argNum + 1) {
            allocationsToMigrate.resize(argNum + 1);
        }
        allocationsToMigrate[argNum] = argValue;
    }
    bool sharedIndirectAccessSet = false;
    std::vector<const void *> allocationsToMigrate;
    InfoCache cache;

  protected:
    std::vector<ArgTraits> argsTraits;
};

template <typename OclObjectT>
void objectCleanup(void *remote, void *local);

class IcdOclPlatform : public Cal::Icd::IcdPlatform, public _cl_platform_id {
  public:
    IcdOclPlatform(Cal::Icd::IcdGlobalState &globalState)
        : IcdPlatform(globalState, Cal::ApiType::OpenCL) {
        this->envToggles.disableProfiling = Cal::Utils::getCalEnvFlag(calOclDisableProfilingEnvName, false);
    }

    void *translateMappedPointer(cl_mem buffer, void *ptr, size_t offset) {
        if (isUsmHostOrShared(ptr)) {
            return ptr;
        }

        if (globalState.isZeroCopyForMallocShmemEnabled()) {
            return reinterpret_cast<char *>(buffer->asLocalObject()->apiHostPtr) + offset;
        }

        return nullptr;
    }

    IcdOclDevice *translateNewRemoteObjectToLocalObject(cl_device_id calDevice, cl_device_id parentDevice, bool isSubDevice) {
        if (nullptr == calDevice) {
            return nullptr;
        }
        auto lock = mappings.deviceMap.lock();
        auto it = mappings.deviceMap.map.find(calDevice);
        if (mappings.deviceMap.map.end() != it) {
            return it->second;
        }

        auto localDevice = new IcdOclDevice(calDevice, Cal::Shared::SingleReference::wrap(asLocalObjectOrNull(parentDevice)), &objectCleanup<cl_device_id>);
        localDevice->isSubDevice = isSubDevice;
        mappings.deviceMap.map[calDevice] = localDevice;
        log<Verbosity::bloat>("Translating new cl_device_id %p to %p", calDevice, localDevice);
        return localDevice;
    }

    IcdOclDevice *translateNewRemoteObjectToLocalObject(cl_device_id calDevice, cl_platform_id parentDevice, bool isSubDevice) {
        return translateNewRemoteObjectToLocalObject(calDevice, static_cast<cl_device_id>(nullptr), isSubDevice);
    }

    IcdOclDevice *translateNewRemoteObjectToLocalObject(cl_device_id calDevice, cl_context parent, bool isSubDevice) {
        return translateNewRemoteObjectToLocalObject(calDevice, static_cast<cl_device_id>(nullptr), isSubDevice);
    }

    template <typename LocalObjT, typename MapT, typename RemoteObjT, typename ParentsT>
    LocalObjT *translateNewRemoteObjectToLocalObjectFromMap(MapT &map, RemoteObjT v, ParentsT &&parents) {
        const char *objectTypeName = IcdOclTypePrinter::getObjectTypeAsStr<LocalObjT>();
        if (nullptr == v) {
            return nullptr;
        }
        auto lock = map.lock();
        auto it = map.map.find(v);
        if (map.map.end() != it) {
            log<Verbosity::bloat>("Translating %s %p to %p", objectTypeName, v, it->second);
            return it->second;
        }

        auto localObj = std::make_unique<LocalObjT>(v, std::move(parents), &objectCleanup<RemoteObjT>);
        map.map[v] = localObj.get();
        log<Verbosity::bloat>("Translating new %s %p to %p", objectTypeName, v, localObj.get());
        return localObj.release();
    }

    IcdOclContext *translateNewRemoteObjectToLocalObject(cl_context v) {
        return translateNewRemoteObjectToLocalObjectFromMap<IcdOclContext>(mappings.ctxMap, v, Cal::Shared::SingleReference::wrap(nullptr));
    }

    template <typename OclObjectT, typename OclParentObjectT>
    auto translateNewRemoteObjectToLocalObject(OclObjectT *obj, OclParentObjectT parent) {
        return translateNewRemoteObjectToLocalObjectFromMap<typename OclObjectT::LocalObjectT>(getObjectsMap<OclObjectT>(), obj,
                                                                                               Cal::Shared::SingleReference::wrap(asLocalObjectOrNull(parent)));
    }

    IcdOclKernel *translateNewRemoteObjectToLocalObject(cl_kernel v, IcdOclKernel *sourceKernel) {
        auto ret = translateNewRemoteObjectToLocalObjectFromMap<IcdOclKernel>(mappings.kernelMap, v, sourceKernel->cloneReferenes());
        if (ret) {
            ret->initTraits(sourceKernel);
        }
        return ret;
    }

    template <typename OclObjectT, typename OclParentObjectT>
    auto translateNewRemoteImageObjectToLocalObject(OclObjectT *mem, OclParentObjectT parent, OclImageTraits imageTraits) {
        auto *calMem = this->translateNewRemoteObjectToLocalObject(mem, parent);
        calMem->setImageTraits(imageTraits);
        return calMem;
    }

    template <typename MapT, typename ObjT>
    void translateRemoteObjectToLocalObject(MapT &map, ObjT &v) {
        const char *objectTypeName = IcdOclTypePrinter::getObjectTypeAsStr<ObjT>();
        if (nullptr == v) {
            return;
        }
        auto lock = map.lock();
        auto it = map.map.find(v);
        if (it == map.map.end()) {
            log<Verbosity::error>("Failed to translate %s %p remote object to local object", objectTypeName, v);
            return;
        }
        log<Verbosity::bloat>("Translating %p to %p", v, &*it->second);
        v = &*it->second;
    }

    void translateRemoteObjectToLocalObject(cl_platform_id &v) {
        v = this;
    }

    void translateRemoteObjectToLocalObject(cl_device_id &calDevice) {
        translateRemoteObjectToLocalObject(mappings.deviceMap, calDevice);
    }

    template <typename OclObjT>
    auto &getObjectsMap() {
        using ElT = std::remove_pointer_t<OclObjT>;
        if constexpr (std::is_same_v<ElT, _cl_device_id>) {
            return mappings.deviceMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_context>) {
            return mappings.ctxMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_command_queue>) {
            return mappings.queueMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_program>) {
            return mappings.programMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_kernel>) {
            return mappings.kernelMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_mem>) {
            return mappings.clMemMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_event>) {
            return mappings.clEventMap;
        }

        if constexpr (std::is_same_v<ElT, _cl_sampler>) {
            return mappings.clSamplerMap;
        }

        std::abort();
    }

    template <typename ObjT>
    void translateRemoteObjectToLocalObject(ObjT &v) {
        translateRemoteObjectToLocalObject(getObjectsMap<ObjT>(), v);
    }

    template <typename T>
    void translateRemoteObjectToLocalObject(void *&v) {
        translateRemoteObjectToLocalObject(*reinterpret_cast<T *&>(v));
    }

    void translateRemoteObjectToLocalObjectInParams(void *dst, cl_int param_name) {
        switch (param_name) {
        default:
            break;
        case CL_DEVICE_PLATFORM:
        case CL_CONTEXT_PLATFORM: {
            translateRemoteObjectToLocalObject<cl_platform_id>(dst);
            return;
        }

        case CL_MEM_ALLOC_DEVICE_INTEL:
        case CL_DEVICE_PARENT_DEVICE:
        case CL_QUEUE_DEVICE: {
            translateRemoteObjectToLocalObject<cl_device_id>(dst);
            return;
        }

        case CL_QUEUE_CONTEXT:
        case CL_PROGRAM_CONTEXT:
        case CL_KERNEL_CONTEXT:
        case CL_MEM_CONTEXT:
        case CL_EVENT_CONTEXT: {
            translateRemoteObjectToLocalObject<cl_context>(dst);
            return;
        }

        case CL_QUEUE_DEVICE_DEFAULT:
        case CL_EVENT_COMMAND_QUEUE: {
            translateRemoteObjectToLocalObject<cl_command_queue>(dst);
            return;
        }

        case CL_KERNEL_PROGRAM: {
            translateRemoteObjectToLocalObject<cl_program>(dst);
            return;
        }

        case CL_MEM_ASSOCIATED_MEMOBJECT:
            translateRemoteObjectToLocalObject<cl_mem>(dst);
            return;
        }
    }

    template <typename MapT, typename RemoteObjT, typename LocalObjT>
    void removeObjectFromMap(MapT &map, RemoteObjT remote, LocalObjT local) {
        const char *objectTypeName = IcdOclTypePrinter::getObjectTypeAsStr<RemoteObjT>();
        auto lock = map.lock();
        auto it = map.map.find(remote);
        if (map.map.end() == it) {
            log<Verbosity::error>("Trying to remove unknown remote %s from the map : %p (local : %p)", objectTypeName, remote, local);
            return;
        }

        map.map.erase(it);
        log<Verbosity::bloat>("Removed remote %s : %p (local : %p) from the map", objectTypeName, remote, local);
    }

    template <typename RemoteObjectT, typename LocalObjectT>
    void removeObjectFromMap(RemoteObjectT *remote, LocalObjectT *local) {
        removeObjectFromMap(getObjectsMap<RemoteObjectT>(), remote, local);
    }

    cl_platform_id asRemoteObject() const {
        return calPlatformId;
    }

    void setRemoteObject(cl_platform_id platformId) {
        this->calPlatformId = platformId;
    }

    cl_command_queue_properties translateQueueFlags(cl_command_queue_properties in) {
        if (false == envToggles.disableProfiling) {
            return in;
        }
        if (0 != (in & CL_QUEUE_PROFILING_ENABLE)) {
            log<Verbosity::debug>("Disabling CL_QUEUE_PROFILING_ENABLE based on %s environment variable", calOclDisableProfilingEnvName.data());
        }
        return in & (~CL_QUEUE_PROFILING_ENABLE);
    }

    void translateQueueFlags(cl_queue_properties *in) {
        if (false == envToggles.disableProfiling) {
            return;
        }
        while (*in) {
            if (*in == CL_QUEUE_PROPERTIES) {
                ++in;
                if (0 != (*in & CL_QUEUE_PROFILING_ENABLE)) {
                    log<Verbosity::debug>("Disabling CL_QUEUE_PROFILING_ENABLE based on %s environment variable", calOclDisableProfilingEnvName.data());
                }
                *in = *in & (~CL_QUEUE_PROFILING_ENABLE);
            } else {
                in += 2;
            }
        }
    }

    bool overrideEventProfilingInfo(cl_event event, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret) {
        if (false == envToggles.disableProfiling) {
            return false;
        }

        if (param_value_size < sizeof(cl_ulong)) {
            log<Verbosity::error>("Can't override event profiling info for unsupported param_value_size : %zu", param_value_size);
            return false;
        }

        if (param_value_size_ret) {
            *param_value_size_ret = sizeof(cl_ulong);
        }

        log<Verbosity::debug>("Overriding event profiling info based on %s environment variable", calOclDisableProfilingEnvName.data());
        *reinterpret_cast<ulong *>(param_value) = 0;

        return true;
    }

  protected:
    cl_platform_id calPlatformId{};

    struct Mappings {
        template <typename CalT, typename ClientT>
        struct ObjectMap {
            std::unique_lock<std::mutex> lock() { return std::unique_lock<std::mutex>(criticalSection); }
            std::mutex criticalSection;

            std::unordered_map<CalT, ClientT> map;
        };

        ObjectMap<cl_context, IcdOclContext *> ctxMap;
        ObjectMap<cl_command_queue, IcdOclCommandQueue *> queueMap;
        ObjectMap<cl_program, IcdOclProgram *> programMap;
        ObjectMap<cl_kernel, IcdOclKernel *> kernelMap;
        ObjectMap<cl_mem, IcdOclMem *> clMemMap;
        ObjectMap<cl_event, IcdOclEvent *> clEventMap;
        ObjectMap<cl_sampler, IcdOclSampler *> clSamplerMap;
        ObjectMap<cl_device_id, IcdOclDevice *> deviceMap;
    } mappings;

    struct {
        bool disableProfiling = false;
    } envToggles;

    std::unique_ptr<Cal::Ipc::ClientConnectionFactory> createConnectionFactory() {
        log<Verbosity::debug>("Creating connection listener based on local named socket");
        return std::make_unique<Cal::Ipc::NamedSocketClientConnectionFactory>();
    }
};

inline IcdOclMem::~IcdOclMem() {
    Cal::Icd::icdGlobalState.getOclPlatform()->destroyUsmDescriptor(hostPtr);
}

template <typename T1, typename T2>
T1 *createIfValidCalId(T2 calId) {
    if (nullptr == calId) {
        return nullptr;
    }
    return new T1(calId);
}

inline size_t getSingleSourceLengthForClCreateProgramWithSource(const char **strings, size_t index, const size_t *lengths) {
    if (lengths && lengths[index] > 0) {
        return lengths[index];
    }
    return Cal::Utils::countNullterminated(strings[index]);
}

inline cl_mem_flags translateUseHostPtr(cl_mem_flags memFlags) {
    if (0 == (CL_MEM_USE_HOST_PTR & memFlags)) {
        return memFlags;
    }

    log<Verbosity::info>("Translating unsupported CL_MEM_USE_HOST_PTR to CL_MEM_COPY_HOST_PTR");
    memFlags = (~CL_MEM_USE_HOST_PTR & memFlags) | CL_MEM_COPY_HOST_PTR;
    return memFlags;
}

inline void warnIfNonBlockingRead(cl_bool &blockingRead) {
    if (false == blockingRead) {
        log<Verbosity::debug>("Overriding async read with serialized one to ensure memory coherency");
        blockingRead = true;
    }
}

inline size_t getChannelSizeBytes(cl_channel_type channelType) {
    switch (channelType) {
    default:
        return 0;
    case CL_SNORM_INT8:
    case CL_UNORM_INT8:
    case CL_SIGNED_INT8:
    case CL_UNSIGNED_INT8:
        return 1;
    case CL_SNORM_INT16:
    case CL_UNORM_INT16:
    case CL_SIGNED_INT16:
    case CL_UNSIGNED_INT16:
    case CL_HALF_FLOAT:
        return 4;
    case CL_UNORM_INT24:
        return 3;
    case CL_SIGNED_INT32:
    case CL_UNSIGNED_INT32:
    case CL_FLOAT:
        return 4;
    }
}

inline size_t getChannelCount(cl_channel_order channelOrder) {
    switch (channelOrder) {
    default:
        return 0U;
    case CL_A:
    case CL_R:
    case CL_INTENSITY:
    case CL_LUMINANCE:
    case CL_DEPTH:
        return 1;
    case CL_RG:
    case CL_RA:
    case CL_Rx:
        return 2;
    case CL_RGB:
    case CL_RGx:
    case CL_sRGB:
        return 3;
    case CL_RGBA:
    case CL_BGRA:
    case CL_ARGB:
    case CL_ABGR:
    case CL_RGBx:
    case CL_sRGBx:
    case CL_sRGBA:
    case CL_sBGRA:
        return 4;
    }
}

inline size_t getTexelSizeBytes(const cl_image_format *format) {
    if (nullptr == format) {
        return 0;
    }

    auto channelSize = getChannelSizeBytes(format->image_channel_data_type);
    auto channelCount = getChannelCount(format->image_channel_order);
    auto size = channelSize * channelCount;
    if (0U == size) {
        switch (format->image_channel_data_type) {
        default:
            log<Verbosity::error>("Could not calculate texel size for channel type : %d order : %d", format->image_channel_data_type, format->image_channel_order);
            return 16;
        case CL_UNORM_SHORT_565:
            return 2;
        case CL_UNORM_SHORT_555:
            return 2;
        case CL_UNORM_INT_101010:
            return 4;
        case CL_UNORM_INT_101010_2:
            return 4;
        }
    }
    return size;
}

inline size_t getImageHostMemorySize(cl_mem_object_type type, const cl_image_format *format, size_t imageWidth, size_t imageHeight,
                                     size_t imageDepth, size_t rowPitch, size_t slicePitch, size_t imageArraySize, const void *hostPtr) {
    if (nullptr == hostPtr) {
        return 0;
    }

    if (0 == rowPitch) {
        rowPitch = getTexelSizeBytes(format) * imageWidth;
    }

    if (0 == slicePitch) {
        slicePitch = rowPitch * imageHeight;
    }

    switch (type) {
    default:
        log<Verbosity::error>("Unknown image type : %d", type);
        return 0;
    case CL_MEM_OBJECT_IMAGE1D:
        return rowPitch;
    case CL_MEM_OBJECT_IMAGE2D:
        return rowPitch * imageWidth;
    case CL_MEM_OBJECT_IMAGE3D:
        return slicePitch * imageHeight;
    case CL_MEM_OBJECT_IMAGE1D_BUFFER:
        return rowPitch;
    case CL_MEM_OBJECT_IMAGE1D_ARRAY:
        return slicePitch * imageArraySize;
    case CL_MEM_OBJECT_IMAGE2D_ARRAY:
        return slicePitch * imageArraySize;
    }
}

inline size_t getImageHostMemorySize(const cl_image_format *format, const cl_image_desc *image_desc, const void *hostPtr) {
    if (nullptr == image_desc) {
        return 0;
    }

    return getImageHostMemorySize(image_desc->image_type, format, image_desc->image_width, image_desc->image_height, image_desc->image_depth,
                                  image_desc->image_row_pitch, image_desc->image_slice_pitch, image_desc->image_array_size, hostPtr);
}

inline size_t getImageReadWriteHostMemorySize(cl_mem image, const size_t srcOrigin[3], const size_t region[3], size_t rowPitch, size_t slicePitch) {
    if ((0 == region[0]) || (0 == region[1]) || (0 == region[2])) {
        return 0;
    }

    const auto &imageTraits = image->asLocalObject()->getImageTraits();
    auto elementSize = imageTraits.getElementStrideBytes();
    if (0 == rowPitch) {
        rowPitch = elementSize * region[0];
    }

    if (0 == slicePitch) {
        slicePitch = rowPitch * region[1];
    }

    size_t size = region[2] * slicePitch;
    return size;
}

inline size_t getSubBufferCreateInfoSize(cl_buffer_create_type type) {
    switch (type) {
    default:
        log<Verbosity::error>("Unknown sub buffer create type : %d", type);
        return 0;
    case CL_BUFFER_CREATE_TYPE_REGION:
        return sizeof(cl_buffer_region);
    }
}

inline void invalidateKernelArgCache() {
    auto globalOclPlatform = Cal::Icd::icdGlobalState.getOclPlatform();
    auto &objectsMap = globalOclPlatform->getObjectsMap<_cl_kernel>();
    for (auto &kernel : objectsMap.map) {
        kernel.second->clSetKernelArgCache.invalidateCache();
    }
}

} // namespace Ocl
} // namespace Icd
} // namespace Cal
