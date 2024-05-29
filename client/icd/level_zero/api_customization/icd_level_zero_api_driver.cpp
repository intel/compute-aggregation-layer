/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/get_all_extension_function_address.h"
#include "client/icd/icd_global_state.h"
#include "client/icd/level_zero/icd_level_zero.h"
#include "client/icd/level_zero/logic/imported_host_pointers_manager.h"
#include "client/icd/level_zero/logic/properties_cache.h"
#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/log.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zeInit(ze_init_flags_t flags) {
    Cal::Client::Icd::LevelZero::initializeL0RedirectionLibraryIfNeeded();
    const auto platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    if (!platform) {
        log<Verbosity::error>("CAL service not available. zeInit() cannot be performed!");
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    log<Verbosity::info>("Initializing LevelZero! Flags argument used with zeInit() will be ignored by Compute Aggregation Layer service.");
    return Cal::Client::Icd::LevelZero::zeInitRpcHelper(flags);
}

ze_result_t zeDriverGet(uint32_t *pCount, ze_driver_handle_t *phDrivers) {
    const auto platform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    if (!platform) {
        log<Verbosity::debug>("CAL service not available. Trying to return zero available drivers!");
        if (pCount) {
            *pCount = 0;
        }
        return ZE_RESULT_SUCCESS;
    }

    if (nullptr == platform->asRemoteObject()) {
        log<Verbosity::debug>("Getting driver from deamon via zeDriverGet()");
        ze_driver_handle_t calDriverHandle{};

        uint32_t handleDriversArraySize{1};
        auto ret = Cal::Client::Icd::LevelZero::zeDriverGetRpcHelper(&handleDriversArraySize, &calDriverHandle);
        if ((ZE_RESULT_SUCCESS != ret) || (nullptr == calDriverHandle)) {
            log<Verbosity::debug>("Failed to get ze_driver_handle_t from service");
            if (pCount) {
                *pCount = 0;
            }
            return ZE_RESULT_SUCCESS;
        }

        log<Verbosity::debug>("Got ze_driver_handle_t from service : %p", calDriverHandle);
        platform->setRemoteObject(calDriverHandle);
    }

    if (pCount) {
        if (*pCount > 0) {
            phDrivers[0] = platform;
        }

        *pCount = 1;
    }

    return ZE_RESULT_SUCCESS;
}

ze_result_t zeDriverGetProperties(ze_driver_handle_t hDriver, ze_driver_properties_t *pDriverProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Platform *>(hDriver), pDriverProperties, zeDriverGetPropertiesRpcHelper);
}

ze_result_t zeDriverGetIpcProperties(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t *pIpcProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Platform *>(hDriver), pIpcProperties, zeDriverGetIpcPropertiesRpcHelper);
}

ze_result_t zeDriverGetExtensionProperties(ze_driver_handle_t hDriver, uint32_t *pCount, ze_driver_extension_properties_t *pExtensionProperties) {
    return Logic::PropertiesCache::obtainProperties(static_cast<IcdL0Platform *>(hDriver), pCount, pExtensionProperties, zeDriverGetExtensionPropertiesRpcHelper);
}

ze_result_t zexDriverImportExternalPointer(ze_driver_handle_t hDriver, void *ptr, size_t size) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto ptrType = globalPlatform->getPointerType(ptr);
    if (ptrType != local) {
        return Cal::Client::Icd::LevelZero::zexDriverImportExternalPointer(hDriver, ptr, size);
    } else {
        log<Verbosity::performance>("zexDriverImportExternalPointer on private pages has no effect");
        auto &instance = Cal::Client::Icd::LevelZero::Logic::ImportedHostPointersManager::getInstance();
        auto instanceLock = instance.lock();

        return instance.importExternalPointer(ptr, size);
    }
}

ze_result_t zexDriverReleaseImportedPointer(ze_driver_handle_t hDriver, void *ptr) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto ptrType = globalPlatform->getPointerType(ptr);
    if (ptrType != local) {
        return Cal::Client::Icd::LevelZero::zexDriverReleaseImportedPointer(hDriver, ptr);
    } else {
        auto &instance = Cal::Client::Icd::LevelZero::Logic::ImportedHostPointersManager::getInstance();
        auto instanceLock = instance.lock();

        return instance.releaseImportedPointer(ptr);
    }
}

ze_result_t zexDriverGetHostPointerBaseAddress(ze_driver_handle_t hDriver, void *ptr, void **baseAddress) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto ptrType = globalPlatform->getPointerType(ptr);
    if (ptrType != local) {
        return Cal::Client::Icd::LevelZero::zexDriverGetHostPointerBaseAddress(hDriver, ptr, baseAddress);
    } else {
        auto &instance = Cal::Client::Icd::LevelZero::Logic::ImportedHostPointersManager::getInstance();
        auto instanceLock = instance.lock();

        return instance.getHostPointerBaseAddress(ptr, baseAddress);
    }
}

ze_result_t zeDriverGetExtensionFunctionAddress(ze_driver_handle_t hDriver, const char *name, void **ppFunctionAddress) {
    if (!ppFunctionAddress || !name) {
        log<Verbosity::error>("zeDriverGetExtensionFunctionAddress(): Null passed! name = %p, ppFunctionAddress = %p",
                              static_cast<const void *>(name),
                              static_cast<void *>(ppFunctionAddress));

        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    *ppFunctionAddress = getAllL0ExtensionFuncionAddress(name);
    if (*ppFunctionAddress == nullptr) {
        log<Verbosity::warning>("Unsupported extension function address requested for : %s", name);
    }

    return *ppFunctionAddress ? ZE_RESULT_SUCCESS : ZE_RESULT_ERROR_INVALID_ARGUMENT;
}

ze_result_t zeDriverGetLastErrorDescription(ze_driver_handle_t hDriver, const char **ppString) {
    if (ppString) {
        constexpr size_t maxErrorDescriptionSize = 256;
        std::vector<char> errorDescription(maxErrorDescriptionSize);
        auto result = zeDriverGetLastErrorDescriptionRpcHelper(hDriver, errorDescription.size(), errorDescription.data());
        if (result == ZE_RESULT_SUCCESS) {
            auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
            auto tid = std::this_thread::get_id();
            globalPlatform->updateLastErrorDescription(tid, errorDescription.data());
            ppString[0] = globalPlatform->getLastErrorDescription(tid).c_str();
            return ZE_RESULT_SUCCESS;
        }
    }
    return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
}

} // namespace Cal::Client::Icd::LevelZero
