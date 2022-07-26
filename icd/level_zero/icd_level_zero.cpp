/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero.h"

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd/icd_global_state.h"
#include "include/cal.h"
#include "shared/log.h"
#include "shared/usm.h"

#include <algorithm>
#include <cstring>
#include <iterator>

namespace Cal {
namespace Icd {
namespace LevelZero {

IcdL0CommandList::CommandListType IcdL0CommandList::selectImmediateType(const ze_command_queue_desc_t *altdesc) {
    if (altdesc && altdesc->mode == ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS) {
        return CommandListType::ImmediateSynchronous;
    } else {
        return CommandListType::Immediate;
    }
}

void IcdL0CommandList::registerMemoryToWrite(const void *srcPtr, size_t srcSize) {
    std::lock_guard lock{memoryToWriteMutex};
    registerMemoryToContainer(srcPtr, srcSize, memoryToWrite);
}

void IcdL0CommandList::registerMemoryToRead(const void *dstPtr, size_t dstSize) {
    std::lock_guard lock{memoryToReadMutex};
    registerMemoryToContainer(dstPtr, dstSize, memoryToRead);
}

void IcdL0CommandList::registerMemoryToContainer(const void *ptr, size_t size, std::vector<ChunkEntry> &memory) {
    const auto overlaps = [ptr, size](const auto &chunk) {
        return IcdL0CommandList::rangesOverlap(chunk.address, chunk.size, ptr, size);
    };

    const auto overlappingCount = std::count_if(std::begin(memory), std::end(memory), overlaps);
    if (overlappingCount == 0) {
        memory.emplace_back(ptr, size);
        return;
    }

    if (overlappingCount == 1) {
        auto overlappingChunkIt = std::find_if(std::begin(memory), std::end(memory), overlaps);
        *overlappingChunkIt = mergeChunks(ChunkEntry{ptr, size}, *overlappingChunkIt);

        return;
    }

    std::vector<ChunkEntry> newChunks{};
    newChunks.reserve(memory.size());

    ChunkEntry currentChunk{ptr, size};
    for (auto &chunk : memory) {
        if (!rangesOverlap(chunk.address, chunk.size, ptr, size)) {
            newChunks.push_back(chunk);
            continue;
        }

        currentChunk = mergeChunks(currentChunk, chunk);
    }

    newChunks.push_back(currentChunk);
    memory = std::move(newChunks);
}

bool IcdL0CommandList::rangesOverlap(const void *srcPtr, const void *dstPtr, size_t size) {
    return rangesOverlap(srcPtr, size, dstPtr, size);
}

bool IcdL0CommandList::rangesOverlap(const void *srcPtr, size_t srcSize, const void *dstPtr, size_t dstSize) {
    const auto srcBegin = reinterpret_cast<uintptr_t>(srcPtr);
    const auto srcEnd = srcBegin + srcSize;

    const auto dstBegin = reinterpret_cast<uintptr_t>(dstPtr);
    const auto dstEnd = dstBegin + dstSize;

    return (srcBegin <= dstBegin && dstBegin < srcEnd) || (dstBegin <= srcBegin && srcBegin < dstEnd);
}

auto IcdL0CommandList::mergeChunks(const ChunkEntry &first, const ChunkEntry &second) -> ChunkEntry {
    const auto firstBegin = reinterpret_cast<uintptr_t>(first.address);
    const auto firstEnd = firstBegin + first.size;

    const auto secondBegin = reinterpret_cast<uintptr_t>(second.address);
    const auto secondEnd = secondBegin + second.size;

    const auto mergedBegin = std::min(firstBegin, secondBegin);
    const auto mergedEnd = std::max(firstEnd, secondEnd);

    const auto mergedAddress = reinterpret_cast<const void *>(mergedBegin);
    const auto mergedSize = static_cast<size_t>(mergedEnd - mergedBegin);

    return ChunkEntry{mergedAddress, mergedSize};
}

ze_result_t IcdL0CommandList::writeRequiredMemory() {
    std::lock_guard lock{memoryToWriteMutex};

    if (memoryToWrite.empty()) {
        return ZE_RESULT_SUCCESS;
    }

    uint32_t transferDescsCount{0};
    const auto queryCountResult = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper(static_cast<uint32_t>(memoryToWrite.size()),
                                                                                       memoryToWrite.data(),
                                                                                       &transferDescsCount,
                                                                                       nullptr);
    if (queryCountResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get total count of memory blocks to write from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    std::vector<Cal::Rpc::ShmemTransferDesc> transferDescs;
    transferDescs.resize(transferDescsCount);

    const auto queryTransferDescs = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper(static_cast<uint32_t>(memoryToWrite.size()),
                                                                                         memoryToWrite.data(),
                                                                                         &transferDescsCount,
                                                                                         transferDescs.data());
    if (queryTransferDescs != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get memory blocks to write from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    if (!globalL0Platform->writeRequiredMemory(transferDescs)) {
        log<Verbosity::error>("Could not write required memory from user's stack/heap! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    return ZE_RESULT_SUCCESS;
}

ze_result_t IcdL0CommandList::readRequiredMemory() {
    std::lock_guard lock{memoryToReadMutex};

    if (memoryToRead.empty()) {
        return ZE_RESULT_SUCCESS;
    }

    uint32_t transferDescsCount{0};
    const auto queryCountResult = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper(static_cast<uint32_t>(memoryToRead.size()),
                                                                                       memoryToRead.data(),
                                                                                       &transferDescsCount,
                                                                                       nullptr);
    if (queryCountResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get total count of memory blocks to read from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    std::vector<Cal::Rpc::ShmemTransferDesc> transferDescs;
    transferDescs.resize(transferDescsCount);

    const auto queryTransferDescs = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper(static_cast<uint32_t>(memoryToRead.size()),
                                                                                         memoryToRead.data(),
                                                                                         &transferDescsCount,
                                                                                         transferDescs.data());
    if (queryTransferDescs != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get memory blocks to read from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    auto globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    if (!globalL0Platform->readRequiredMemory(transferDescs)) {
        log<Verbosity::error>("Could not read required memory to user's stack/heap! Results of execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    return ZE_RESULT_SUCCESS;
}

void IcdL0CommandList::moveKernelArgsToGpu(IcdL0Kernel *kernel) {
    if (kernel->sharedIndirectAccessSet) {
        Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager()->moveAllAllocationsToGpu();
    } else {
        for (auto &alloc : kernel->allocationsToMigrate) {
            moveSharedAllocationsToGpuImpl(alloc);
        }
    }
}

void IcdL0CommandList::moveSharedAllocationsToGpuImpl(const void *ptr) {
    if (this->isImmediate()) {
        Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager()->moveAllocationToGpu(ptr);
    } else {
        this->usedAllocations.push_back(ptr);
    }
}

void IcdL0CommandQueue::moveSharedAllocationsToGpu(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists) {
    bool indirectAccessSet = false;
    for (uint32_t i = 0; i < numCommandLists; i++) {
        auto l0CmdList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        if (l0CmdList->sharedIndirectAccessSet) {
            Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager()->moveAllAllocationsToGpu();
            indirectAccessSet = true;
            break;
        }
    }
    for (uint32_t i = 0; i < numCommandLists; i++) {
        auto l0CmdList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        auto &allocs = l0CmdList->getUsedAllocations();
        if (!indirectAccessSet) {
            for (auto &alloc : allocs) {
                Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager()->moveAllocationToGpu(alloc);
            }
        }
        allocs.clear();
    }
}

ze_command_queue_mode_t IcdL0CommandQueue::getCommandQueueMode() {
    return mode;
}

ze_result_t IcdL0CommandQueue::readMemoryRequiredByCurrentlyExecutedCommandLists() {
    for (const auto &commandList : currentlyExecutedCommandLists) {
        const auto icdCommandList = static_cast<IcdL0CommandList *>(commandList);
        const auto readResult = icdCommandList->readRequiredMemory();

        if (readResult != ZE_RESULT_SUCCESS) {
            return readResult;
        }
    }

    return ZE_RESULT_SUCCESS;
}

void IcdL0CommandQueue::storeExecutedCommandListsPointers(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists) {
    currentlyExecutedCommandLists.insert(currentlyExecutedCommandLists.end(),
                                         phCommandLists,
                                         phCommandLists + numCommandLists);
}

void IcdL0CommandQueue::removeFromExecutedCommandLists(const std::vector<ze_command_list_handle_t> &commandListsToRemove) {
    if (commandListsToRemove.empty()) {
        return;
    }

    auto first = std::find(currentlyExecutedCommandLists.begin(), currentlyExecutedCommandLists.end(), commandListsToRemove.front());
    auto last = std::find(currentlyExecutedCommandLists.begin(), currentlyExecutedCommandLists.end(), commandListsToRemove.back());
    if (first == currentlyExecutedCommandLists.end() && last == currentlyExecutedCommandLists.end()) {
        // Everything is fine. The range was synchronized in another call.
        return;
    }

    if (first == currentlyExecutedCommandLists.end() || last == currentlyExecutedCommandLists.end()) {
        log<Verbosity::error>("Could not remove executed command lists! Could not find all elements!");
        return;
    }

    const auto realLast = std::next(last);
    const auto foundRangeSize = std::distance(first, realLast);

    if (foundRangeSize != static_cast<int64_t>(commandListsToRemove.size())) {
        log<Verbosity::error>("Could not remove executed command lists! Invalid range! "
                              "Expected range size: %d, actual range size: %d",
                              static_cast<int>(commandListsToRemove.size()),
                              static_cast<int>(foundRangeSize));
        return;
    }

    currentlyExecutedCommandLists.erase(first, realLast);
}

std::vector<ze_command_list_handle_t> IcdL0Fence::clearExecutedCommandListsPointers() {
    std::lock_guard lock{currentlyExecutedCommandListsMutex};
    return std::move(currentlyExecutedCommandLists);
}

void IcdL0Fence::storeExecutedCommandListsPointers(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists) {
    std::lock_guard lock{currentlyExecutedCommandListsMutex};

    currentlyExecutedCommandLists.insert(currentlyExecutedCommandLists.end(),
                                         phCommandLists,
                                         phCommandLists + numCommandLists);
}

ze_result_t ImportedHostPointersManager::importExternalPointer(void *ptr, size_t size) {
    if (!ptr || !size) {
        log<Verbosity::error>("ImportedHostPointersManager::importExternalPointer(): passed NULL! ptr = %p, size = %zd", ptr, size);
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    const auto rangeBegin = reinterpret_cast<std::uintptr_t>(ptr);
    const auto rangeEnd = rangeBegin + size;

    Cal::Utils::AddressRange rangeToInsert{rangeBegin, rangeEnd};
    if (importedPointers.intersectsSubRanges(rangeToInsert)) {
        log<Verbosity::error>("Tried to import host pointer, which is already registered! ptr = %p, size = %zd", ptr, size);
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    importedPointers.insertSubRange(rangeToInsert);
    return ZE_RESULT_SUCCESS;
}

ze_result_t ImportedHostPointersManager::releaseImportedPointer(void *ptr) {
    if (!ptr) {
        log<Verbosity::error>("ImportedHostPointersManager::releaseImportedPointer(): passed NULL! ptr = %p", ptr);
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    const auto rangeBegin = reinterpret_cast<std::uintptr_t>(ptr);
    const auto rangeEnd = rangeBegin;

    Cal::Utils::AddressRange rangeToSearch{rangeBegin, rangeEnd};

    const auto ranges = importedPointers.getIntersectedSubRanges(rangeToSearch);
    if (ranges.empty()) {
        log<Verbosity::error>("Tried to remove a pointer, which had not been imported! ptr = %p", ptr);
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    if (ranges.size() > 1) {
        log<Verbosity::error>("More than one range intersects given address! Logic error - this should not happen!");
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    importedPointers.destroySubRange(ranges[0]->getBoundingRange());
    return ZE_RESULT_SUCCESS;
}

ze_result_t ImportedHostPointersManager::getHostPointerBaseAddress(void *ptr, void **baseAddress) {
    if (!baseAddress || !ptr) {
        log<Verbosity::error>("ImportedHostPointersManager::getHostPointerBaseAddress(): passed NULL! ptr = %p, baseAddress = %p", ptr, static_cast<void *>(baseAddress));
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    const auto rangeBegin = reinterpret_cast<std::uintptr_t>(ptr);
    const auto rangeEnd = rangeBegin;

    Cal::Utils::AddressRange rangeToSearch{rangeBegin, rangeEnd};

    const auto ranges = importedPointers.getIntersectedSubRanges(rangeToSearch);
    if (ranges.empty()) {
        *baseAddress = nullptr;
        return ZE_RESULT_SUCCESS;
    }

    if (ranges.size() > 1) {
        log<Verbosity::error>("More than one range intersects given address! Logic error - this should not happen!");
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    *baseAddress = ranges[0]->getBoundingRange().base();
    return ZE_RESULT_SUCCESS;
}

bool IcdL0Platform::isZeAffinityMaskPresent() {
    std::call_once(parseZeAffinityMaskOnce, [this]() {
        auto zeAffinityMask = Cal::Utils::getCalEnv("ZE_AFFINITY_MASK");
        auto zeAffinityMaskDetected = zeAffinityMask != nullptr && zeAffinityMask[0] != 0;

        if (zeAffinityMaskDetected) {
            uint32_t numAllDevices = 0;
            std::vector<ze_device_handle_t> allDevices;
            std::vector<bool> selectedDevices;
            auto status = Cal::Icd::LevelZero::zeDeviceGetRpcHelper(this, &numAllDevices, nullptr);
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }

            allDevices.resize(numAllDevices);
            status = Cal::Icd::LevelZero::zeDeviceGetRpcHelper(this, &numAllDevices, allDevices.data());
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }
            selectedDevices.resize(numAllDevices);
            auto affinityMaskEntries = Cal::Utils::split(zeAffinityMask, ",");
            for (const auto &entry : affinityMaskEntries) {
                auto subEntries = Cal::Utils::split(entry, ".");
                auto deviceIndex = static_cast<uint32_t>(std::stoul(subEntries[0], nullptr, 0));
                if (deviceIndex < numAllDevices) {
                    selectedDevices[deviceIndex] = true;
                    if (subEntries.size() > 1) {
                        auto subDeviceIndex = static_cast<uint32_t>(std::stoul(subEntries[1], nullptr, 0));
                        auto device = static_cast<IcdL0Device *>(allDevices[deviceIndex]);
                        device->addSubDeviceToFilter(subDeviceIndex);
                    }
                }
            }

            for (auto i = 0u; i < numAllDevices; i++) {

                if (selectedDevices[i]) {
                    filteredDevices.push_back(allDevices[i]);
                }
            }
            zeAffinityMaskPresent = zeAffinityMaskDetected;
        }
    });

    return zeAffinityMaskPresent;
}

void IcdL0Device::addSubDeviceToFilter(uint32_t subDeviceIndex) {
    if (selectedDevices.size() < subDeviceIndex + 1) {
        selectedDevices.resize(subDeviceIndex + 1);
    }
    selectedDevices[subDeviceIndex] = true;
}
bool IcdL0Device::isZeAffinityMaskPresent() {
    std::call_once(parseZeAffinityMaskOnce, [this]() {
        if (!selectedDevices.empty()) {
            uint32_t numAllDevices = 0;
            std::vector<ze_device_handle_t> allDevices;
            auto status = Cal::Icd::LevelZero::zeDeviceGetSubDevicesRpcHelper(this, &numAllDevices, nullptr);
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }

            allDevices.resize(numAllDevices);
            status = Cal::Icd::LevelZero::zeDeviceGetSubDevicesRpcHelper(this, &numAllDevices, allDevices.data());
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }

            selectedDevices.resize(numAllDevices);

            for (auto i = 0u; i < numAllDevices; i++) {

                if (selectedDevices[i]) {
                    filteredDevices.push_back(allDevices[i]);
                }
            }
            zeAffinityMaskPresent = true;
        }
    });

    return zeAffinityMaskPresent;
}

ze_result_t IcdL0Module::getKernelNames(uint32_t *pCount, const char **pNames) {
    if (!wasKernelNamesQueried.load() && !queryKernelNames()) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    const auto count = std::min(*pCount, static_cast<uint32_t>(kernelNames.size()));
    for (uint32_t i = 0; i < count; ++i) {
        pNames[i] = kernelNames[i].c_str();
    }

    *pCount = count;
    return ZE_RESULT_SUCCESS;
}

ze_result_t IcdL0Module::getKernelNamesCount(uint32_t *pCount) {
    if (!wasKernelNamesQueried.load() && !queryKernelNames()) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    *pCount = static_cast<uint32_t>(kernelNames.size());
    return ZE_RESULT_SUCCESS;
}

bool IcdL0Module::queryKernelNames() {
    if (wasKernelNamesQueried.load()) {
        return true;
    }

    std::lock_guard lock{kernelNamesMutex};

    uint32_t totalLength{0};
    auto ret = Cal::Icd::LevelZero::zeModuleGetKernelNamesRpcHelper(this, &totalLength, nullptr);
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::debug>("Failed to get total length of names of kernels from module from service!");
        return false;
    }

    std::vector<char> concatenatedNames;
    concatenatedNames.resize(totalLength);

    ret = Cal::Icd::LevelZero::zeModuleGetKernelNamesRpcHelper(this, &totalLength, concatenatedNames.data());
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::debug>("Failed to get concatenated names of kernels from module from service!");
        return false;
    }

    populateKernelNames(concatenatedNames);

    wasKernelNamesQueried.store(true);
    return true;
}

void IcdL0Module::populateKernelNames(const std::vector<char> &buffer) {
    const auto data = buffer.data();

    auto lastBegin = 0u;
    for (auto i = 0u; i < buffer.size(); ++i) {
        if (buffer[i] == '\0') {
            kernelNames.emplace_back(data + lastBegin, data + i);
            lastBegin = i + 1;
        }
    }
}

bool IcdL0Module::removeGlobalPointer() {
    auto globalPtrLock = globalPointers.lock();
    for (auto &ptr : globalPointers.ptrList) {
        Cal::Icd::icdGlobalState.getL0Platform()->removeGlobalPointer(ptr);
    }
    globalPointers.ptrList.clear();
    return true;
}

bool IcdL0Module::recordGlobalPointer(void *ptr) {
    // Add to list if ptr is unique
    auto globalPtrLock = globalPointers.lock();
    if (std::find(globalPointers.ptrList.begin(), globalPointers.ptrList.end(), ptr) == globalPointers.ptrList.end()) {
        globalPointers.ptrList.push_back(ptr);
    } else {
        return true;
    }
    globalPtrLock.unlock();
    Cal::Icd::icdGlobalState.getL0Platform()->recordGlobalPointer(ptr);
    return true;
}

bool IcdL0Device::patchDeviceName(ze_device_properties_t &properties) {
    const auto nullTerminator = std::find(std::begin(properties.name), std::end(properties.name), '\0');
    if (nullTerminator == std::begin(properties.name)) {
        log<Verbosity::critical>("Cannot patch device name! It is empty!");
        return false;
    }

    static constexpr char deviceNameSuffix[] = " (aggregated)";
    static constexpr auto requiredSpace = std::distance(std::begin(deviceNameSuffix), std::end(deviceNameSuffix));

    const auto availableSpace = std::distance(nullTerminator, std::end(properties.name));
    if (availableSpace < requiredSpace) {
        log<Verbosity::critical>("Cannot patch device name with '(aggregated)' suffix! Not enough space!");
        return false;
    }

    std::copy(std::begin(deviceNameSuffix), std::end(deviceNameSuffix), nullTerminator);
    return true;
}

template <typename RemoteL0ObjectT, typename LocalL0ObjectT>
void objectCleanup(void *remote, void *local) {
    Cal::Icd::icdGlobalState.getL0Platform()->removeObjectFromMap(static_cast<RemoteL0ObjectT>(remote), static_cast<LocalL0ObjectT>(local));
}

template void objectCleanup<ze_device_handle_t, IcdL0Device *>(void *, void *);
template void objectCleanup<ze_context_handle_t, IcdL0Context *>(void *, void *);
template void objectCleanup<ze_command_queue_handle_t, IcdL0CommandQueue *>(void *, void *);
template void objectCleanup<ze_command_list_handle_t, IcdL0CommandList *>(void *, void *);
template void objectCleanup<ze_module_handle_t, IcdL0Module *>(void *, void *);
template void objectCleanup<ze_module_build_log_handle_t, IcdL0ModuleBuildLog *>(void *, void *);
template void objectCleanup<ze_kernel_handle_t, IcdL0Kernel *>(void *, void *);
template void objectCleanup<ze_event_handle_t, IcdL0Event *>(void *, void *);
template void objectCleanup<ze_event_pool_handle_t, IcdL0EventPool *>(void *, void *);
template void objectCleanup<ze_fence_handle_t, IcdL0Fence *>(void *, void *);
template void objectCleanup<ze_image_handle_t, IcdL0Image *>(void *, void *);

} // namespace LevelZero
} // namespace Icd
} // namespace Cal
