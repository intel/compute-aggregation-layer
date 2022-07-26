/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "shared/log.h"

#include <array>

inline size_t countOpaqueList(const ze_base_desc_t *desc) {
    size_t count{0};

    while (desc != nullptr) {
        ++count;
        desc = static_cast<const ze_base_desc_t *>(desc->pNext);
    }

    return count;
}

inline size_t getUnderlyingSize(const ze_base_desc_t *desc) {
    if (desc == nullptr) {
        log<Verbosity::error>("Nullptr pNext passed to getUnderlyingSize! Aborting...");
        std::abort();
        return 0;
    }

    if (ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_FD == desc->stype) {
        return sizeof(ze_external_memory_export_fd_t);
    }

    if (ZE_STRUCTURE_TYPE_DEVICE_P2P_BANDWIDTH_EXP_PROPERTIES == desc->stype) {
        return sizeof(ze_device_p2p_bandwidth_exp_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_KERNEL_PREFERRED_GROUP_SIZE_PROPERTIES == desc->stype) {
        return sizeof(ze_kernel_preferred_group_size_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_FLOAT_ATOMIC_EXT_PROPERTIES == desc->stype) {
        return sizeof(ze_float_atomic_ext_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_SCHEDULING_HINT_EXP_PROPERTIES == desc->stype) {
        return sizeof(ze_scheduling_hint_exp_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES == desc->stype) {
        return sizeof(ze_device_raytracing_ext_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_RAYTRACING_MEM_ALLOC_EXT_DESC == desc->stype) {
        return sizeof(ze_raytracing_mem_alloc_ext_desc_t);
    }

    if (ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES == desc->stype) {
        return sizeof(ze_device_memory_ext_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_POWER_SAVING_HINT_EXP_DESC == desc->stype) {
        return sizeof(ze_context_power_saving_hint_exp_desc_t);
    }

    if (ZE_STRUCTURE_TYPE_CACHE_RESERVATION_EXT_DESC == desc->stype) {
        return sizeof(ze_cache_reservation_ext_desc_t);
    }

    if (ZE_STRUCTURE_TYPE_DEVICE_LUID_EXT_PROPERTIES == desc->stype) {
        return sizeof(ze_device_luid_ext_properties_t);
    }

    if (ZE_STRUCTURE_TYPE_EU_COUNT_EXT == desc->stype) {
        return sizeof(ze_eu_count_ext_t);
    }

    if (ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC == desc->stype) {
        return sizeof(ze_relaxed_allocation_limits_exp_desc_t);
    }

    if (ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD == desc->stype) {
        return sizeof(ze_external_memory_import_fd_t);
    }

    if (ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC == desc->stype) {
        return sizeof(ze_external_memory_export_desc_t);
    }

    if (ZE_STRUCTURE_TYPE_MEMORY_COMPRESSION_HINTS_EXT_DESC == desc->stype) {
        return sizeof(ze_memory_compression_hints_ext_desc_t);
    }

    log<Verbosity::error>("Unknown type passed as pNext! ENUM = %d", static_cast<int>(desc->stype));
    std::abort();
    return 0;
}

inline const ze_base_desc_t *getNext(const ze_base_desc_t *desc) {
    const void *pNext = desc ? desc->pNext : nullptr;
    return reinterpret_cast<const ze_base_desc_t *>(pNext);
}

inline const void *&getNextField(const ze_base_desc_t &desc) {
    return const_cast<const void *&>(desc.pNext);
}

inline ze_structure_type_t getExtensionType(const ze_base_desc_t *desc) {
    if (desc == nullptr) {
        log<Verbosity::error>("Nullptr pNext passed to getExtensionType! Aborting...");
        std::abort();
        return {};
    }

    return desc->stype;
}

inline bool isReadOnly(ze_structure_type_t stype) {
    static constexpr std::array readOnlyExtensions = {
        ZE_STRUCTURE_TYPE_POWER_SAVING_HINT_EXP_DESC,
        ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC,
        ZE_STRUCTURE_TYPE_RAYTRACING_MEM_ALLOC_EXT_DESC,
        ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
        ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_DESC,
    };

    for (const auto extensionType : readOnlyExtensions) {
        if (extensionType == stype) {
            return true;
        }
    }

    return false;
}

struct NestedPNextTraits {
    ze_structure_type_t extensionType{};
    int32_t extensionOffset{};
};
