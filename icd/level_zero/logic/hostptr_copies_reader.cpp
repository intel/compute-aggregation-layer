/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "hostptr_copies_reader.h"

#include "generated_rpc_messages_level_zero.h"
#include "icd/icd_global_state.h"
#include "shared/ipc.h"
#include "shared/rpc.h"
#include "shared/shmem.h"

#include <cstring>

namespace Cal::Icd::LevelZero::Logic {

ze_result_t HostptrCopiesReader::readMemory(Cal::Rpc::ChannelClient &channel, Cal::Ipc::ShmemImporter &shmemImporter) {
    const auto memoryToRead = getHostptrCopiesToUpdate(channel);
    if (memoryToRead.empty()) {
        return ZE_RESULT_SUCCESS;
    }

    uint32_t transferDescsCount{0};
    const auto queryCountResult = performNonlockingTransferDescsRequest(channel,
                                                                        static_cast<uint32_t>(memoryToRead.size()),
                                                                        memoryToRead.data(),
                                                                        &transferDescsCount,
                                                                        nullptr);
    if (queryCountResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get total count of memory blocks to read from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    std::vector<Cal::Rpc::ShmemTransferDesc> transferDescs;
    transferDescs.resize(transferDescsCount);

    const auto queryTransferDescs = performNonlockingTransferDescsRequest(channel,
                                                                          static_cast<uint32_t>(memoryToRead.size()),
                                                                          memoryToRead.data(),
                                                                          &transferDescsCount,
                                                                          transferDescs.data());
    if (queryTransferDescs != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not get memory blocks to read from service! Execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    if (false == copyMappedMemory(shmemImporter, transferDescs)) {
        log<Verbosity::error>("Could not read required memory to user's stack/heap! Results of execution of command list would be invalid!");
        return ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    return ZE_RESULT_SUCCESS;
}

std::vector<Cal::Rpc::MemChunk> HostptrCopiesReader::getHostptrCopiesToUpdate(Cal::Rpc::ChannelClient &channel) {
    std::vector<Cal::Rpc::MemChunk> memoryToRead{};

    while (true) {
        auto chunk = channel.acquireHostptrCopiesUpdate();
        if (chunk.address == nullptr || chunk.size == 0u) {
            break;
        }

        memoryToRead.push_back(chunk);
    }

    return memoryToRead;
}

ze_result_t HostptrCopiesReader::performNonlockingTransferDescsRequest(Cal::Rpc::ChannelClient &channel,
                                                                       uint32_t chunksCount,
                                                                       const Cal::Rpc::MemChunk *chunks,
                                                                       uint32_t *outDescsCount,
                                                                       Cal::Rpc::ShmemTransferDesc *outDescs) {
    log<Verbosity::bloat>("Establishing RPC for memory transfer!");

    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(chunksCount, chunks, outDescsCount, outDescs);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);

    auto command = new (commandSpace.get()) CommandT(dynMemTraits, chunksCount, chunks, outDescsCount, outDescs);
    command->copyFromCaller(dynMemTraits);

    if (channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if (false == channel.callSynchronous(command)) {
        return command->returnValue();
    }

    command->copyToCaller(dynMemTraits);
    return command->captures.ret;
}

bool HostptrCopiesReader::copyMappedMemory(Cal::Ipc::ShmemImporter &shmemImporter,
                                           const std::vector<Cal::Rpc::ShmemTransferDesc> &transferDescs) {
    for (const auto &transfer : transferDescs) {
        auto shmem = shmemImporter.open(transfer.shmemId, transfer.underlyingSize, nullptr);
        if (!shmem.isValid()) {
            log<Verbosity::error>("Cannot map shared memory to perform transfer from service to client!");
            return false;
        }

        const auto sourceAddress = reinterpret_cast<uintptr_t>(shmem.getMmappedPtr()) + transfer.offsetFromMapping;
        const auto source = reinterpret_cast<const void *>(sourceAddress);
        const auto destination = reinterpret_cast<void *>(transfer.transferStart);

        std::memcpy(destination, source, transfer.bytesCountToCopy);
        shmemImporter.release(shmem);
    }

    return true;
}

} // namespace Cal::Icd::LevelZero::Logic
