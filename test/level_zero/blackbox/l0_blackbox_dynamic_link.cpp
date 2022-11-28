/*
 * Copyright (C) 2022 Intel Corporation
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
int lib_func_add(int x, int y);
int lib_func_mult(int x, int y);
int lib_func_sub(int x, int y);

kernel void call_library_funcs(__global int* result) {
    int add_result = lib_func_add(1,2);
    int mult_result = lib_func_mult(add_result,2);
    result[0] = lib_func_sub(mult_result, 1);
}
)===";

static constexpr const char *exportModuleSrc = R"===(
int lib_func_add(int x, int y) {
    return x+y;
}

int lib_func_mult(int x, int y) {
    return x*y;
}

int lib_func_sub(int x, int y) {
    return x-y;
}
)===";

bool moduleDynamicLink(const uint32_t numModules, ze_module_handle_t *phModules) {
    log<Verbosity::info>("Dynamic linking modules via zeModuleDynamicLink()");

    ze_module_build_log_handle_t linkLog{};
    const auto zeModuleDynamicLinkResult = zeModuleDynamicLink(numModules, phModules, &linkLog);
    if (zeModuleDynamicLinkResult == ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("Module Dynamic Link succeeded! Module0 = %p, Module1 = %p",
                             static_cast<void *>(phModules[0]), static_cast<void *>(phModules[1]));
    } else {
        log<Verbosity::error>("zeModuleDynamicLink() has failed! Error code: %d",
                              static_cast<int>(zeModuleDynamicLinkResult));
    }

    if (checkBuildLog(linkLog)) {
        log<Verbosity::info>("Build logs checking succeeded!");
    } else {
        log<Verbosity::error>("build log checking has failed!");
    }

    return zeModuleDynamicLinkResult == ZE_RESULT_SUCCESS;
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

    static constexpr uint32_t numModules = 2;
    ze_module_handle_t importModule{};
    RUN_REQUIRED_STEP(createModule(context, devices[0], importSpirv, ZE_MODULE_FORMAT_IL_SPIRV, importModule));
    ze_module_handle_t exportModule{};
    RUN_REQUIRED_STEP(createModule(context, devices[0], exportSpirv, ZE_MODULE_FORMAT_IL_SPIRV, exportModule,
                                   "-library-compilation"));

    ze_module_handle_t modules[]{importModule, exportModule};
    RUN_REQUIRED_STEP(moduleDynamicLink(numModules, modules));

    RUN_REQUIRED_STEP(destroyModule(modules[0]));
    RUN_REQUIRED_STEP(destroyModule(modules[1]));

    RUN_REQUIRED_STEP(destroyContext(context));
}
