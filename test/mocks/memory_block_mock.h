/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/shmem.h"
#include "test/mocks/shmem_manager_mock.h"

#include <cstddef>

namespace Cal::Mocks {

class MockMemoryBlock : public Cal::Ipc::BasicMemoryBlock<Cal::Mocks::MockShmemManager> {
  public:
    using BasicMemoryBlock::BasicMemoryBlock;
    using BasicMemoryBlock::chunks;
    using BasicMemoryBlock::getTotalContiguousSize;
    using BasicMemoryBlock::oldMappings;
};

class MockMemoryBlocksManager : public Cal::Ipc::BasicMemoryBlocksManager<MockMemoryBlock, Cal::Mocks::MockShmemManager> {
  public:
    using BasicMemoryBlocksManager::getMemoryBlockWhichIncludesChunk;
    using BasicMemoryBlocksManager::getOverlappingBlocksBegin;
    using BasicMemoryBlocksManager::getOverlappingBlocksEnd;
    using BasicMemoryBlocksManager::memoryBlocks;
};

} // namespace Cal::Mocks
