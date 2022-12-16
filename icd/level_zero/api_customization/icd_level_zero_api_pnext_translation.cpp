/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero_api.h"
#include "icd_level_zero_ipc_helpers.h"
#include "shared/log.h"

namespace Cal::Icd::LevelZero {

static void translateRequiredPNextExtension(ze_external_memory_import_fd_t &memoryImportFdExt) {
    using Cal::Icd::LevelZero::Ipc::reverseTranslateIpcHandles;

    // This structure is used to match interface of reverseTranslateIpcHandles template function.
    struct IpcHandleFdWrapper {
        int *data;
    };
    IpcHandleFdWrapper handle{&memoryImportFdExt.fd};

    const auto functionName = "translateRequiredPNextExtension(ze_external_memory_import_fd_t)";
    const auto reverseTranslationResult = reverseTranslateIpcHandles(functionName, 1u, &handle);
    if (reverseTranslationResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Could not translate ze_external_memory_import_fd_t! Memory import may not work correctly!");
    }
}

// Translated pNext elements are stored in captures in dynamic memory.
// This memory can be written. Therefore, const_cast is allowed.
void translateRequiredPNextExtensions(const void *pNext) {
    auto current = static_cast<ze_base_desc_t *>(const_cast<void *>(pNext));
    while (current != nullptr) {
        if (ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD == current->stype) {
            auto *memoryImportFdExt = reinterpret_cast<ze_external_memory_import_fd_t *>(current);
            translateRequiredPNextExtension(*memoryImportFdExt);
        }

        current = static_cast<ze_base_desc_t *>(const_cast<void *>(current->pNext));
    }
}

} // namespace Cal::Icd::LevelZero
