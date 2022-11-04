/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/level_zero/icd_level_zero.h"

namespace Cal::Mocks {

class MockIcdL0CommandList : public Cal::Icd::LevelZero::IcdL0CommandList {
  public:
    using IcdL0CommandList::ChunkEntry;
    using IcdL0CommandList::memoryToWrite;
    using IcdL0CommandList::mergeChunks;

    MockIcdL0CommandList() : IcdL0CommandList{nullptr, Cal::Shared::SingleReference::wrap(nullptr), nullptr} {}
};

} // namespace Cal::Mocks
