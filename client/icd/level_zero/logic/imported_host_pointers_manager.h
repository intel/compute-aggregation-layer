/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "shared/utils.h"

#include <cstddef>
#include <mutex>

namespace Cal::Client::Icd::LevelZero::Logic {

class ImportedHostPointersManager {
  public:
    ze_result_t importExternalPointer(void *ptr, size_t size);
    ze_result_t releaseImportedPointer(void *ptr);
    ze_result_t getHostPointerBaseAddress(void *ptr, void **baseAddress);

    [[nodiscard]] std::lock_guard<std::mutex> lock() {
        return std::lock_guard<std::mutex>{objMutex};
    }

    static ImportedHostPointersManager &getInstance() {
        static ImportedHostPointersManager manager{};
        return manager;
    }

  private:
    std::mutex objMutex{};
    Cal::Utils::PartitionedAddressRange<void> importedPointers{Cal::Utils::AddressRange{uintptr_t{0}, uintptr_t{0}}};
};

} // namespace Cal::Client::Icd::LevelZero::Logic
