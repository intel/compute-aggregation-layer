/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1

#include "cal.h"
#include "level_zero/ze_api.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

#include <vector>

using namespace Cal::Testing::Utils::LevelZero;

static constexpr const char *importModuleSrc = R"===(
int add(int x, int y);

kernel void call_add_function(__global int* result) {
    result[0] = add(2, 1);
}
)===";

static constexpr const char *exportModuleSrc = R"===(
int add(int x, int y) {
    return x+y;
}
)===";

bool createModuleViaExtension(ze_context_handle_t context, ze_device_handle_t device, ze_module_handle_t &module, ze_module_program_exp_desc_t &extension) {
    log<Verbosity::info>("Creating module via zeModuleCreate()!");

    ze_module_desc_t moduleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC, // stype
        &extension,                    // pNext
        ZE_MODULE_FORMAT_IL_SPIRV,     // format
        0u,                            // inputSize
        nullptr,                       // pInputModule
        nullptr,                       // pBuildFlags
        nullptr                        // pConstants
    };

    ze_module_build_log_handle_t buildLog{};

    const auto zeModuleCreateResult = zeModuleCreate(context, device, &moduleDescription, &module, &buildLog);
    if (zeModuleCreateResult == ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("Module creation succeeded! Module = %p", static_cast<void *>(module));
    } else {
        log<Verbosity::error>("zeModuleCreate() has failed! Error code: %d", static_cast<int>(zeModuleCreateResult));
    }

    if (checkBuildLog(buildLog)) {
        log<Verbosity::info>("Build log checking succeeded!");
    } else {
        log<Verbosity::error>("build log checking has failed!");
    }

    return zeModuleCreateResult == ZE_RESULT_SUCCESS;
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    ze_context_handle_t context{};
    RUN_REQUIRED_STEP(createContext(drivers[0], context));

    std::vector<uint8_t> importSpirv{};
    RUN_REQUIRED_STEP(generateSpirv(importSpirv, importModuleSrc));
    std::vector<uint8_t> exportSpirv{};
    RUN_REQUIRED_STEP(generateSpirv(exportSpirv, exportModuleSrc));

    static constexpr uint32_t numModules{2u};
    const size_t spirvSizes[numModules] = {importSpirv.size(), exportSpirv.size()};
    const uint8_t *spirvs[numModules] = {importSpirv.data(), exportSpirv.data()};
    const char *buildFlags[numModules] = {"", "-library-compilation"};

    ze_module_program_exp_desc_t extension = {
        ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC, // stype
        nullptr,                                   // pNext
        numModules,                                // count
        spirvSizes,                                // inputSizes
        spirvs,                                    // pInputModules
        buildFlags,                                // pBuildFlags
        nullptr                                    // pConstants
    };

    ze_module_handle_t moduleCreatedViaExtension{};
    RUN_REQUIRED_STEP(createModuleViaExtension(context, devices[0], moduleCreatedViaExtension, extension));

    RUN_REQUIRED_STEP(destroyModule(moduleCreatedViaExtension));
    RUN_REQUIRED_STEP(destroyContext(context));
}
