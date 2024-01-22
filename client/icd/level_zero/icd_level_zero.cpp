/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero.h"

#include "client/icd/icd_global_state.h"
#include "client/icd/icd_page_fault_manager.h"
#include "client/icd/level_zero/debugger/debugger.h"
#include "generated_icd_level_zero.h"
#include "include/cal.h"
#include "shared/log.h"

#include <algorithm>
#include <cstring>
#include <iterator>

namespace Cal {
namespace Client::Icd {
namespace LevelZero {

bool checkIfL0RedirectIsNeeded() {
    bool redirectBecauseOfEnv = Cal::Utils::getCalEnvFlag(calRedirectL0EnvName, false);
    if (redirectBecauseOfEnv) {
        log<Verbosity::info>("Redirecting directly to GPU driver because of env : %s", calRedirectL0EnvName.data());
        return true;
    }

    bool redirectBecauseOfDebuggability = Cal::Utils::getCalEnvFlag("ZET_ENABLE_PROGRAM_DEBUGGING", false);
    if (redirectBecauseOfDebuggability) {
        log<Verbosity::info>("Redirecting directly to GPU driver because of env : %s", "ZET_ENABLE_PROGRAM_DEBUGGING");
        return true;
    }

    auto processName = Cal::Utils::getProcessName();
    bool redirectBecauseOfProcessName = std::find(std::begin(L0DebuggerProcessesNames), std::end(L0DebuggerProcessesNames), processName) != std::end(L0DebuggerProcessesNames);

    if (redirectBecauseOfProcessName) {
        log<Verbosity::info>("Redirecting directly to GPU driver because of process name : %s", processName.c_str());
        return true;
    }

    return false;
}

void *l0RedirectLibary = nullptr;
void initializeL0RedirectionLibraryIfNeeded() {
    if (l0RedirectLibary) {
        return;
    }

    static bool isL0RedirectNeded = checkIfL0RedirectIsNeeded();
    if (false == isL0RedirectNeded) {
        return;
    }

    static std::mutex crit;
    std::lock_guard lg{crit};

    if (l0RedirectLibary) {
        return;
    }

    const char *l0LibName = "libze_intel_gpu.so.1";
    l0RedirectLibary = dlopen(l0LibName, RTLD_LAZY | RTLD_LOCAL);
    if (nullptr == l0RedirectLibary) {
        log<Verbosity::error>("Could not load %s for L0 redirection", l0LibName);
        return;
    }

    log<Verbosity::info>("Loaded %s for redirection", l0LibName);
}

IcdL0Context::IcdL0Context(ze_context_handle_t remoteObject, Cal::Shared::SingleReference &&parent, CleanupFuncT cleanupFunc)
    : Cal::Shared::RefCountedWithParent<_ze_context_handle_t, Logic::IcdL0TypePrinter>(remoteObject, std::move(parent), cleanupFunc),
      stagingAreaManager([this](size_t size) { return this->allocateStagingArea(size); },
                         [this](void *ptr) { return this->deallocateStagingAreas(ptr); }) {}

void IcdL0Context::beforeReleaseCallback() {
    this->getStagingAreaManager().clearStagingAreaAllocations();
}

void *IcdL0Context::allocateStagingArea(size_t size) {
    void *usmHostMem{};
    ze_host_mem_alloc_desc_t desc{ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC, nullptr, 0};
    if (ZE_RESULT_SUCCESS != Cal::Client::Icd::LevelZero::zeMemAllocHost(this->asLocalObject(), &desc, size, 0, &usmHostMem)) {
        log<Verbosity::critical>("Failed to allocate staging buffer via zeMemAllocHost of size %zu", size);
        return nullptr;
    }

    return usmHostMem;
}

void IcdL0Context::deallocateStagingAreas(void *ptr) {
    Cal::Client::Icd::LevelZero::zeMemFree(this->asLocalObject(), ptr);
}

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

void IcdL0CommandList::registerMemoryToContainer(const void *ptr, size_t size, std::vector<ChunkEntry> &memory) {
    const auto overlaps = [ptr, size](const auto &chunk) {
        return IcdL0CommandList::rangesOverlap(chunk.base(), chunk.size(), ptr, size);
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
        if (!rangesOverlap(chunk.base(), chunk.size(), ptr, size)) {
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
    const auto firstBegin = reinterpret_cast<uintptr_t>(first.base());
    const auto firstEnd = firstBegin + first.size();

    const auto secondBegin = reinterpret_cast<uintptr_t>(second.base());
    const auto secondEnd = secondBegin + second.size();

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
    std::vector<Cal::Rpc::MemChunk> chunksToWrite;
    chunksToWrite.reserve(memoryToWrite.size());
    for (const auto &mw : memoryToWrite) {
        chunksToWrite.push_back({mw.base(), mw.size()});
    }
    const auto queryCountResult = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper(static_cast<uint32_t>(chunksToWrite.size()),
                                                                                       chunksToWrite.data(),
                                                                                       &transferDescsCount,
                                                                                       nullptr);
    if (queryCountResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get total count of memory blocks to write from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    std::vector<Cal::Rpc::TransferDesc> transferDescs;
    transferDescs.resize(transferDescsCount);

    const auto queryTransferDescs = zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper(static_cast<uint32_t>(chunksToWrite.size()),
                                                                                         chunksToWrite.data(),
                                                                                         &transferDescsCount,
                                                                                         transferDescs.data());
    if (queryTransferDescs != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get memory blocks to write from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    auto globalL0Platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    if (!globalL0Platform->writeRequiredMemory(transferDescs)) {
        log<Verbosity::error>("Could not write required memory from user's stack/heap! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    return ZE_RESULT_SUCCESS;
}

void IcdL0CommandList::moveKernelArgsToGpu(IcdL0Kernel *kernel) {
    if (kernel->sharedIndirectAccessSet) {
        Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().moveAllAllocationsToGpu();
    } else {
        for (auto &alloc : kernel->allocationsToMigrate) {
            moveSharedAllocationsToGpuImpl(alloc);
        }
    }
}

void IcdL0CommandList::registerTemporaryAllocation(const void *ptr, std::unique_ptr<void, std::function<void(void *)>> alloc) {
    std::lock_guard lock{temporaryStagingAreas.mutex};
    temporaryStagingAreas.allocations.insert(std::make_pair(ptr, std::move(alloc)));
}

void IcdL0CommandList::cleanTemporaryAllocations() {
    std::lock_guard lock{temporaryStagingAreas.mutex};
    temporaryStagingAreas.allocations.clear();
}

void *IcdL0CommandList::getTemporaryAllocationForReuse(const void *ptr) {
    if (!isImmediateAsynchronous()) {
        return nullptr;
    }

    std::lock_guard lock{temporaryStagingAreas.mutex};
    auto it = temporaryStagingAreas.allocations.find(ptr);
    if (temporaryStagingAreas.allocations.end() == it) {
        return nullptr;
    }
    return it->second.get();
}

void IcdL0CommandList::moveSharedAllocationsToGpuImpl(const void *ptr) {
    if (this->isImmediate()) {
        Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().moveAllocationToGpu(ptr);
    } else {
        this->usedAllocations.push_back(ptr);
    }
}

void IcdL0CommandQueue::moveSharedAllocationsToGpu(uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists) {
    bool indirectAccessSet = false;
    for (uint32_t i = 0; i < numCommandLists; i++) {
        auto l0CmdList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        if (l0CmdList->sharedIndirectAccessSet) {
            Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().moveAllAllocationsToGpu();
            indirectAccessSet = true;
            break;
        }
    }
    for (uint32_t i = 0; i < numCommandLists; i++) {
        auto l0CmdList = static_cast<IcdL0CommandList *>(phCommandLists[i]);
        auto &allocs = l0CmdList->getUsedAllocations();
        if (!indirectAccessSet) {
            for (auto &alloc : allocs) {
                Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().moveAllocationToGpu(alloc);
            }
        }
        allocs.clear();
    }
}

ze_command_queue_mode_t IcdL0CommandQueue::getCommandQueueMode() {
    return mode;
}

bool IcdL0Platform::isZeAffinityMaskPresent() {
    std::call_once(parseZeAffinityMaskOnce, [this]() {
        auto zeAffinityMask = Cal::Utils::getCalEnv("ZE_AFFINITY_MASK");
        auto zeAffinityMaskDetected = zeAffinityMask != nullptr && zeAffinityMask[0] != 0;

        if (zeAffinityMaskDetected) {
            uint32_t numAllDevices = 0;
            std::vector<ze_device_handle_t> allDevices;
            std::vector<bool> selectedDevices;
            auto status = Cal::Client::Icd::LevelZero::zeDeviceGetRpcHelper(this, &numAllDevices, nullptr);
            if (status != ZE_RESULT_SUCCESS) {
                return;
            }

            allDevices.resize(numAllDevices);
            status = Cal::Client::Icd::LevelZero::zeDeviceGetRpcHelper(this, &numAllDevices, allDevices.data());
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

template <typename RemoteL0ObjectT, typename LocalL0ObjectT>
void objectCleanup(void *remote, void *local) {
    Cal::Client::Icd::icdGlobalState.getL0Platform()->removeObjectFromMap(static_cast<RemoteL0ObjectT>(remote), static_cast<LocalL0ObjectT>(local));
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
template void objectCleanup<zet_metric_group_handle_t, IcdL0MetricGroup *>(void *, void *);
template void objectCleanup<zet_metric_handle_t, IcdL0Metric *>(void *, void *);

} // namespace LevelZero
} // namespace Client::Icd
} // namespace Cal
