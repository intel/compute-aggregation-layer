/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/icd_kernel_arg_cache.h"
#include "icd/level_zero/api_type_wrapper/handles_definitions.h"
#include "icd/level_zero/api_type_wrapper/wrapper_base.h"
#include "icd/level_zero/logic/properties_cache.h"
#include "icd/level_zero/logic/types_printer.h"
#include "shared/ref_counted.h"

#include <vector>

namespace Cal::Icd::LevelZero {

struct IcdL0Kernel : Cal::Shared::RefCountedWithParent<_ze_kernel_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    KernelArgCache zeKernelSetArgumentValueCache;
    Logic::PropertiesCache::VectorTuple<ze_kernel_properties_t> properties;

    template <typename T>
    constexpr uint32_t &getPropertiesCount() {
        return Logic::PropertiesCache::defaultPropertiesCount;
    }

    void storeKernelArg(const void *argValue, uint32_t argNum) {
        if (allocationsToMigrate.size() < argNum + 1) {
            allocationsToMigrate.resize(argNum + 1);
        }
        allocationsToMigrate[argNum] = argValue;
    }

    bool sharedIndirectAccessSet{false};
    std::vector<const void *> allocationsToMigrate{};
};

} // namespace Cal::Icd::LevelZero
