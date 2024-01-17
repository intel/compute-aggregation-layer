/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "imported_host_pointers_manager.h"

#include "shared/log.h"

namespace Cal::Client::Icd::LevelZero::Logic {

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

    Cal::Utils::AddressRange rangeToSearch{ptr};
    const auto ranges = importedPointers.getIntersectedSubRanges(rangeToSearch);
    if (ranges.empty()) {
        log<Verbosity::debug>("Tried to remove a pointer, which had not been imported! ptr = %p", ptr);
        return ZE_RESULT_SUCCESS;
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

} // namespace Cal::Client::Icd::LevelZero::Logic
