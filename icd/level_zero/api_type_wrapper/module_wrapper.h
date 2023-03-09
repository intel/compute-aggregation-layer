/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/level_zero/api_type_wrapper/handles_definitions.h"
#include "icd/level_zero/api_type_wrapper/wrapper_base.h"
#include "icd/level_zero/logic/properties_cache.h"
#include "icd/level_zero/logic/types_printer.h"
#include "shared/log.h"
#include "shared/ref_counted.h"

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace Cal::Icd::LevelZero {

class IcdL0Module : public Cal::Shared::RefCountedWithParent<_ze_module_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    ze_result_t getKernelNames(uint32_t *pCount, const char **pNames);
    ze_result_t getKernelNamesCount(uint32_t *pCount);

    Logic::PropertiesCache::VectorTuple<ze_module_properties_t> properties;

    template <typename T>
    constexpr uint32_t &getPropertiesCount() {
        return Logic::PropertiesCache::defaultPropertiesCount;
    }

  private:
    bool queryKernelNames();
    void populateKernelNames(const std::vector<char> &buffer);

    std::atomic_bool wasKernelNamesQueried{false};
    std::vector<std::string> kernelNames{};
    std::mutex kernelNamesMutex{};
};

} // namespace Cal::Icd::LevelZero
