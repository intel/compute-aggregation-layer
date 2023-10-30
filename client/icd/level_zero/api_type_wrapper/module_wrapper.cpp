/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/level_zero/api_type_wrapper/module_wrapper.h"

#include "generated_icd_level_zero.h"

#include <algorithm>

namespace Cal::Icd::LevelZero {

ze_result_t IcdL0Module::getKernelNames(uint32_t *pCount, const char **pNames) {
    if (!wasKernelNamesQueried.load() && !queryKernelNames()) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    const auto count = std::min(*pCount, static_cast<uint32_t>(kernelNames.size()));
    for (uint32_t i = 0; i < count; ++i) {
        pNames[i] = kernelNames[i].c_str();
    }

    *pCount = count;
    return ZE_RESULT_SUCCESS;
}

ze_result_t IcdL0Module::getKernelNamesCount(uint32_t *pCount) {
    if (!wasKernelNamesQueried.load() && !queryKernelNames()) {
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    *pCount = static_cast<uint32_t>(kernelNames.size());
    return ZE_RESULT_SUCCESS;
}

bool IcdL0Module::queryKernelNames() {
    if (wasKernelNamesQueried.load()) {
        return true;
    }

    std::lock_guard lock{kernelNamesMutex};
    if (wasKernelNamesQueried.load()) {
        return true;
    }

    uint32_t totalLength{0};
    auto ret = Cal::Icd::LevelZero::zeModuleGetKernelNamesRpcHelper(this, &totalLength, nullptr);
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::debug>("Failed to get total length of names of kernels from module from service!");
        return false;
    }

    std::vector<char> concatenatedNames;
    concatenatedNames.resize(totalLength);

    ret = Cal::Icd::LevelZero::zeModuleGetKernelNamesRpcHelper(this, &totalLength, concatenatedNames.data());
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::debug>("Failed to get concatenated names of kernels from module from service!");
        return false;
    }

    populateKernelNames(concatenatedNames);

    wasKernelNamesQueried.store(true);
    return true;
}

void IcdL0Module::populateKernelNames(const std::vector<char> &buffer) {
    const auto data = buffer.data();

    auto lastBegin = 0u;
    for (auto i = 0u; i < buffer.size(); ++i) {
        if (buffer[i] == '\0') {
            kernelNames.emplace_back(data + lastBegin, data + i);
            lastBegin = i + 1;
        }
    }
}

} // namespace Cal::Icd::LevelZero
