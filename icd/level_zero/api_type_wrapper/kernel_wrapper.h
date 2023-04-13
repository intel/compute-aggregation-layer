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
            allocationsToMigrate.resize(argNum + 1, nullptr);
        }
        allocationsToMigrate[argNum] = argValue;
    }

    bool sharedIndirectAccessSet{false};
    std::vector<const void *> allocationsToMigrate{};

    struct GroupSize {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t z = 0;
    } groupSize;
    struct SuggestedGroupSizeEntry {
        GroupSize globalSize;
        GroupSize suggestedSize;
    };
    std::vector<SuggestedGroupSizeEntry> suggestedGroupSizes;
    bool obtainSuggestedGroupSizes(uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t *groupSizeX, uint32_t *groupSizeY, uint32_t *groupSizeZ) {
        for (const auto &suggestedGroupSize : suggestedGroupSizes) {
            if (suggestedGroupSize.globalSize.x == globalSizeX &&
                suggestedGroupSize.globalSize.y == globalSizeY &&
                suggestedGroupSize.globalSize.z == globalSizeZ) {
                *groupSizeX = suggestedGroupSize.suggestedSize.x;
                *groupSizeY = suggestedGroupSize.suggestedSize.y;
                *groupSizeZ = suggestedGroupSize.suggestedSize.z;
                return true;
            }
        }
        return false;
    }
    void storeSuggestedGroupSizes(uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
        suggestedGroupSizes.push_back(SuggestedGroupSizeEntry{GroupSize{globalSizeX, globalSizeY, globalSizeX}, GroupSize{groupSizeX, groupSizeY, groupSizeZ}});
    }
};

} // namespace Cal::Icd::LevelZero
