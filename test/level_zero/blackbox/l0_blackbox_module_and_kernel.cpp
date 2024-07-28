/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/dynamic_library.h"
#include "test/utils/l0_common_steps.h"
#include "third_party/level_zero_headers/driver_experimental/public/zex_module.h"

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

using namespace Cal::Testing::Utils::LevelZero;

static constexpr const char *simpleKernelSource =
    R"(__kernel void CopyBuffer(__global unsigned int *src, __global unsigned int *dst) {
    int id = (int)get_global_id(0);
    dst[id] = src[id];
}
__kernel void DoubleVals(__global unsigned int *src, __global unsigned int *dst) {
    int id = (int)get_global_id(0);
    dst[id] = 2 * src[id];
})";

bool testBuildLogFunctions(ze_context_handle_t context, ze_device_handle_t device, const std::vector<uint8_t> &binary,
                           ze_module_format_t binaryFormat) {
    log<Verbosity::info>("Testing build log querying!");

    ze_module_desc_t moduleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC, nullptr, binaryFormat, binary.size(), binary.data(), "", nullptr};

    ze_module_build_log_handle_t buildLog{};
    ze_module_handle_t module{};
    auto zeModuleCreateResult = zeModuleCreate(context, device, &moduleDescription, &module, &buildLog);
    if (zeModuleCreateResult == ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("Module creation succeeded! Module = %p", static_cast<void *>(module));
    } else {
        log<Verbosity::error>("zeModuleCreate() has failed! Error code: %d", static_cast<int>(zeModuleCreateResult));
        return false;
    }

    return checkBuildLog(buildLog);
}

bool getNativeBinary(std::vector<uint8_t> &nativeBinary, ze_module_handle_t module) {
    log<Verbosity::info>("Getting native binary size from the module!");

    size_t nativeBinarySize{0};
    auto zeModuleGetNativeBinaryResult = zeModuleGetNativeBinary(module, &nativeBinarySize, nullptr);
    if (zeModuleGetNativeBinaryResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Cannot get the size of native binary from module! Error code = %d",
                              static_cast<int>(zeModuleGetNativeBinaryResult));
        return false;
    }

    log<Verbosity::info>("Retrieved size of native binary is : %zd", nativeBinarySize);
    if (nativeBinarySize == 0) {
        return true;
    }

    log<Verbosity::info>("Retrieving native binary from module!");
    nativeBinary.resize(nativeBinarySize);

    zeModuleGetNativeBinaryResult = zeModuleGetNativeBinary(module, &nativeBinarySize, nativeBinary.data());
    if (zeModuleGetNativeBinaryResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("Cannot get native binary from module! Error code = %d", zeModuleGetNativeBinaryResult);
        return false;
    }

    log<Verbosity::info>("Retrieved native binary from module!");
    return true;
}

bool getKernelNames(ze_module_handle_t module) {
    log<Verbosity::info>("Getting count of available kernels in module!");

    uint32_t kernelNamesCount{0};
    auto zeModuleGetKernelNamesResult = zeModuleGetKernelNames(module, &kernelNamesCount, nullptr);
    if (zeModuleGetKernelNamesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetKernelNames() call has failed! Error code = %d",
                              static_cast<int>(zeModuleGetKernelNamesResult));
        return false;
    }

    log<Verbosity::info>("Count of kernels in module is: %d!", static_cast<int>(kernelNamesCount));
    if (kernelNamesCount == 0) {
        return true;
    }

    log<Verbosity::info>("Getting available kernel names from module!");

    std::vector<const char *> kernelNames{};
    kernelNames.resize(kernelNamesCount);

    zeModuleGetKernelNamesResult = zeModuleGetKernelNames(module, &kernelNamesCount, kernelNames.data());
    if (zeModuleGetKernelNamesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetKernelNames() call has failed! Error code = %d",
                              static_cast<int>(zeModuleGetKernelNamesResult));
        return false;
    }

    log<Verbosity::info>("Kernel names from module are:");
    for (const auto &name : kernelNames) {
        log<Verbosity::info>("%s", name);
    }

    return true;
}

bool getModuleProperties(ze_module_handle_t module) {
    log<Verbosity::info>("Getting module properties via zeModuleGetProperties()");

    ze_module_properties_t moduleProps = {ZE_STRUCTURE_TYPE_MODULE_PROPERTIES};
    const auto zeModuleGetPropertiesResult = zeModuleGetProperties(module, &moduleProps);
    if (zeModuleGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetProperties() call has failed! Error code = %d",
                              static_cast<int>(zeModuleGetPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Module properties flags are: %d", static_cast<int>(moduleProps.flags));
    return true;
}

bool getNonexistentFunctionPointer(ze_module_handle_t module) {
    log<Verbosity::info>(
        "Getting function pointer to non-existing function from module via zeModuleGetFunctionPointer!");

    void *nonexistingFunctionPtr{nullptr};
    const auto zeModuleGetFunctionPointerResult =
        zeModuleGetFunctionPointer(module, "SomeNonexistingFunction", &nonexistingFunctionPtr);
    if (zeModuleGetFunctionPointerResult == ZE_RESULT_ERROR_INVALID_FUNCTION_NAME &&
        nonexistingFunctionPtr == nullptr) {
        log<Verbosity::info>("zeModuleGetFunctionPointer() correctly returned ZE_RESULT_ERROR_INVALID_FUNCTION_NAME!");
        return true;
    }

    log<Verbosity::error>("zeModuleGetFunctionPointer() call has failed! Error code = %d, nonexistingFunctionPtr = %p",
                          static_cast<int>(zeModuleGetFunctionPointerResult), nonexistingFunctionPtr);
    return false;
}

bool getNonexistentGlobalVariable(ze_module_handle_t module) {
    log<Verbosity::info>("Getting nonexistent global pointer from module");

    const char *nonexistentGlobalVariable = "nonexisting_global_variable";
    size_t globalSize{};
    void *globalPtr{nullptr};

    const auto zeModuleGetGlobalPointerResult =
        zeModuleGetGlobalPointer(module, nonexistentGlobalVariable, &globalSize, &globalPtr);
    if (zeModuleGetGlobalPointerResult != ZE_RESULT_SUCCESS && globalPtr == nullptr) {
        log<Verbosity::info>(
            "zeModuleGetGlobalPointer() correctly could not get a pointer for nonexistent_global_variable!");
        return true;
    }

    log<Verbosity::error>("zeModuleGetGlobalPointer() unexpectedly returned a pointer for nonexistent_global_variable! "
                          "This should not happen! "
                          "Error code = %d, nonexistingGlobalVariable = %p",
                          static_cast<int>(zeModuleGetGlobalPointerResult), globalPtr);
    return false;
}

bool createKernel(ze_module_handle_t module, ze_kernel_handle_t &kernel, const char *kernelName) {
    ze_kernel_desc_t kernelDesc = {ZE_STRUCTURE_TYPE_KERNEL_DESC, nullptr, 0, kernelName};

    const auto zeKernelCreateResult = zeKernelCreate(module, &kernelDesc, &kernel);
    if (zeKernelCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelCreate() call has failed! Error code = %d",
                              static_cast<int>(zeKernelCreateResult));
        return false;
    }

    log<Verbosity::info>("Kernel has been created successfully!");
    return true;
}

bool destroyKernel(ze_kernel_handle_t &kernel) {
    const auto zeKernelDestroyResult = zeKernelDestroy(kernel);
    if (zeKernelDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelDestroy() call has failed! Error code = %d",
                              static_cast<int>(zeKernelDestroyResult));
        return false;
    }

    kernel = nullptr;
    log<Verbosity::info>("Kernel has been successfully destroyed!");

    return true;
}

bool getKernelName(ze_kernel_handle_t kernel) {
    log<Verbosity::info>("Getting kernel name size via zeKernelGetName()");

    size_t kernelNameSize{};
    const auto zeKernelGetNameSizeResult = zeKernelGetName(kernel, &kernelNameSize, nullptr);
    if (zeKernelGetNameSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetName() call has failed! Error code = %d",
                              static_cast<int>(zeKernelGetNameSizeResult));
        return false;
    }

    log<Verbosity::info>("The size of kernel name is %zd", kernelNameSize);
    if (kernelNameSize == 0) {
        return true;
    }

    log<Verbosity::info>("Getting kernel name via zeKernelGetName()");

    std::string kernelName{};
    kernelName.resize(kernelNameSize + 1);

    const auto zeKernelGetNameResult = zeKernelGetName(kernel, &kernelNameSize, kernelName.data());
    if (zeKernelGetNameResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetName() call has failed! Error code = %d",
                              static_cast<int>(zeKernelGetNameResult));
        return false;
    }

    log<Verbosity::info>("Kernel name is: %s", kernelName.c_str());
    return true;
}

bool getIndirectAccessFlags(ze_kernel_handle_t kernel, ze_kernel_indirect_access_flags_t &indirectAccessFlags) {
    log<Verbosity::info>("Getting indirect access flags via zeKernelGetIndirectAccess()!");

    const auto zeKernelGetIndirectAccessResult = zeKernelGetIndirectAccess(kernel, &indirectAccessFlags);
    if (zeKernelGetIndirectAccessResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetIndirectAccess() call has failed! Error code = %d",
                              static_cast<int>(zeKernelGetIndirectAccessResult));
        return false;
    }

    log<Verbosity::info>("Indirect access flags: %d", static_cast<int>(indirectAccessFlags));
    return true;
}

bool setIndirectAccessFlags(ze_kernel_handle_t kernel, ze_kernel_indirect_access_flags_t indirectAccessFlags) {
    log<Verbosity::info>("Setting indirect access flags via zeKernelSetIndirectAccess()!");

    const auto zeKernelSetIndirectAccessResult = zeKernelSetIndirectAccess(kernel, indirectAccessFlags);
    if (zeKernelSetIndirectAccessResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetIndirectAccess() call has failed! Error code = %d",
                              static_cast<int>(zeKernelSetIndirectAccessResult));
        return false;
    }

    log<Verbosity::info>("Indirect access flags have been set successfully!");
    return true;
}

bool getTotalGroupCount(ze_kernel_handle_t kernel) {
    log<Verbosity::info>("Getting total group count via zeKernelSuggestMaxCooperativeGroupCount()");

    uint32_t totalGroupCount{};
    const auto zeKernelSuggestMaxCooperativeGroupCountResult =
        zeKernelSuggestMaxCooperativeGroupCount(kernel, &totalGroupCount);
    if (zeKernelSuggestMaxCooperativeGroupCountResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSuggestMaxCooperativeGroupCount() call has failed! Error code = %d",
                              static_cast<int>(zeKernelSuggestMaxCooperativeGroupCountResult));
        return false;
    }

    log<Verbosity::info>("Total group count is: %d", static_cast<int>(totalGroupCount));
    return true;
}

bool getKernelProperties(ze_kernel_handle_t kernel) {
    log<Verbosity::info>("Getting kernel properties via zeKernelGetProperties()!");

    zex_kernel_register_file_size_exp_t registerFilesSize{};

    ze_kernel_preferred_group_size_properties_t preferredGroupSizeProperties = {
        ZE_STRUCTURE_TYPE_KERNEL_PREFERRED_GROUP_SIZE_PROPERTIES, // stype
        &registerFilesSize,                                       // pNext
        0u                                                        // preferredMultiple
    };

    ze_kernel_properties_t kernelProperties = {};

    kernelProperties.stype = ZE_STRUCTURE_TYPE_KERNEL_PROPERTIES;
    kernelProperties.pNext = &preferredGroupSizeProperties;

    const auto zeKernelGetPropertiesResult = zeKernelGetProperties(kernel, &kernelProperties);
    if (zeKernelGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetProperties() call has failed! Error code = %d",
                              static_cast<int>(zeKernelGetPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Number of kernel arguments read from properties is: %d",
                         static_cast<int>(kernelProperties.numKernelArgs));

    log<Verbosity::info>("ze_kernel_preferred_group_size_properties_t: preferredMultiple = %d",
                         static_cast<int>(preferredGroupSizeProperties.preferredMultiple));

    log<Verbosity::info>("zex_kernel_register_file_size_exp_t: registerFileSize = %d", registerFilesSize.registerFileSize);

    return true;
}

bool setCacheConfig(ze_kernel_handle_t kernel, ze_cache_config_flag_t config) {
    log<Verbosity::info>("Calling zeKernelSetCacheConfig() to set config flags = %d!", static_cast<int>(config));

    const auto zeKernelSetCacheConfigResult = zeKernelSetCacheConfig(kernel, config);
    if (zeKernelSetCacheConfigResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetCacheConfig() call has failed! Error code = %d",
                              static_cast<int>(zeKernelSetCacheConfigResult));
        return false;
    }

    log<Verbosity::info>("zeKernelSetCacheConfig() call has succeeded!");
    return true;
}

bool suggestGroupSize(ze_kernel_handle_t kernel, uint32_t xSize, uint32_t ySize, uint32_t zSize,
                      uint32_t &suggestedGroupSizeX, uint32_t &suggestedGroupSizeY, uint32_t &suggestedGroupSizeZ) {
    log<Verbosity::info>("Trying to get suggested group size for processing (%d x %d x %d) problem.",
                         static_cast<int>(xSize), static_cast<int>(ySize), static_cast<int>(zSize));

    const auto zeKernelSuggestGroupSizeResult = zeKernelSuggestGroupSize(
        kernel, xSize, ySize, zSize, &suggestedGroupSizeX, &suggestedGroupSizeY, &suggestedGroupSizeZ);
    if (zeKernelSuggestGroupSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSuggestGroupSize() call has failed! Error code = %d",
                              static_cast<int>(zeKernelSuggestGroupSizeResult));
        return false;
    }

    log<Verbosity::info>("The suggested sizes are: (%d, %d, %d)", static_cast<int>(suggestedGroupSizeX),
                         static_cast<int>(suggestedGroupSizeY), static_cast<int>(suggestedGroupSizeZ));
    return true;
}

bool setGroupSize(ze_kernel_handle_t kernel, uint32_t suggestedGroupSizeX, uint32_t suggestedGroupSizeY, uint32_t suggestedGroupSizeZ) {
    log<Verbosity::info>("Setting kernel group size via zeKernelSetGroupSize() for kernel (%p)!", static_cast<void *>(kernel));

    const auto zeKernelSetGroupSizeResult =
        zeKernelSetGroupSize(kernel, suggestedGroupSizeX, suggestedGroupSizeY, suggestedGroupSizeZ);
    if (zeKernelSetGroupSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetGroupSize() call has failed! Error code: %d",
                              static_cast<int>(zeKernelSetGroupSizeResult));
        return false;
    }

    log<Verbosity::info>("Call to zeKernelSetGroupSize() has been successful!");
    return true;
}

bool setSchedulingHint(ze_kernel_handle_t kernel, ze_scheduling_hint_exp_desc_t &hint) {
    log<Verbosity::info>("Setting kernel scheduling hint via zeKernelSchedulingHintExp() for kernel (%p)!", static_cast<void *>(kernel));

    const auto zeKernelSchedulingHintExpResult = zeKernelSchedulingHintExp(kernel, &hint);
    if (zeKernelSchedulingHintExpResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSchedulingHintExp() call has failed! Error code: %d",
                              static_cast<int>(zeKernelSchedulingHintExpResult));
        return false;
    }

    log<Verbosity::info>("Scheduling hint has been successfully set!");
    return true;
}

bool setKernelArgument(ze_kernel_handle_t kernel, uint32_t argIndex, size_t argSize, const void *arg) {
    const auto zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(kernel, argIndex, argSize, arg);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed! Error code: %d",
                              static_cast<int>(zeKernelSetArgumentValueResult));
        return false;
    }

    log<Verbosity::info>("Argument has been set correctly!");
    return true;
}

bool appendLaunchKernel(ze_command_list_handle_t cmdList, ze_kernel_handle_t kernel, ze_group_count_t &launchArgs,
                        ze_event_handle_t signalEvent) {
    const auto zeCommandListAppendLaunchKernelResult =
        zeCommandListAppendLaunchKernel(cmdList, kernel, &launchArgs, signalEvent, 0, nullptr);
    if (zeCommandListAppendLaunchKernelResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchKernel() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListAppendLaunchKernelResult));
        return false;
    }

    log<Verbosity::info>("Launch kernel operation appended successfully!");
    return true;
}

bool appendLaunchCooperativeKernel(ze_command_list_handle_t cmdList, ze_kernel_handle_t kernel, ze_group_count_t &launchArgs,
                                   ze_event_handle_t signalEvent) {
    const auto zeCommandListAppendLaunchCooperativeKernelResult =
        zeCommandListAppendLaunchCooperativeKernel(cmdList, kernel, &launchArgs, signalEvent, 0, nullptr);
    if (zeCommandListAppendLaunchCooperativeKernelResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchCooperativeKernel() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListAppendLaunchCooperativeKernelResult));
        return false;
    }

    log<Verbosity::info>("Launch cooperative kernel operation appended successfully!");
    return true;
}

bool appendLaunchKernelIndirect(ze_command_list_handle_t cmdList, ze_kernel_handle_t kernel,
                                ze_group_count_t *launchArgsDeviceAccessibleBuffer, ze_event_handle_t signalEvent,
                                uint32_t numWaitEvents, ze_event_handle_t *waitEvents) {
    const auto zeCommandListAppendLaunchKernelIndirectResult = zeCommandListAppendLaunchKernelIndirect(
        cmdList, kernel, launchArgsDeviceAccessibleBuffer, signalEvent, numWaitEvents, waitEvents);
    if (zeCommandListAppendLaunchKernelIndirectResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchKernelIndirect() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListAppendLaunchKernelIndirectResult));
        return false;
    }

    log<Verbosity::info>("Launch kernel indirect operation appended successfully!");
    return true;
}

bool appendLaunchMultipleKernelsIndirect(ze_command_list_handle_t cmdList, uint32_t numKernels, ze_kernel_handle_t *kernels,
                                         const uint32_t *countBuffer, const ze_group_count_t *launchArgumentsBuffer,
                                         ze_event_handle_t signalEvent, uint32_t numWaitEvents, ze_event_handle_t *waitEvents) {
    const auto zeCommandListAppendLaunchMultipleKernelsIndirectResult = zeCommandListAppendLaunchMultipleKernelsIndirect(
        cmdList, numKernels, kernels, countBuffer, launchArgumentsBuffer, signalEvent, numWaitEvents, waitEvents);
    if (zeCommandListAppendLaunchMultipleKernelsIndirectResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchMultipleKernelsIndirect() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListAppendLaunchMultipleKernelsIndirectResult));
        return false;
    }

    log<Verbosity::info>("Launch multiple kernels indirect operation appended successfully!");
    return true;
}

bool appendQueryKernelTimestamps(ze_command_list_handle_t cmdList, uint32_t numEvents, ze_event_handle_t *events, void *dstptr, const size_t *pOffsets) {
    const auto zeCommandListAppendQueryKernelTimestampsResult = zeCommandListAppendQueryKernelTimestamps(
        cmdList, numEvents, events, dstptr, pOffsets, nullptr, 0, nullptr);
    if (zeCommandListAppendQueryKernelTimestampsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendQueryKernelTimestamps() call has failed! Error code = %d",
                              static_cast<int>(zeCommandListAppendQueryKernelTimestampsResult));
        return false;
    }

    log<Verbosity::info>("Query kernel timestamps operation appended successfully!");
    return true;
}

bool setGlobalOffset(ze_kernel_handle_t kernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
    const auto zeKernelSetGlobalOffsetExpResult = zeKernelSetGlobalOffsetExp(kernel, offsetX, offsetY, offsetZ);
    if (zeKernelSetGlobalOffsetExpResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetGlobalOffsetExp() call has failed! Error code = %d",
                              static_cast<int>(zeKernelSetGlobalOffsetExpResult));
        return false;
    }

    log<Verbosity::info>("Kernel global offsets set to (%d, %d, %d)", static_cast<int>(offsetX),
                         static_cast<int>(offsetY), static_cast<int>(offsetZ));
    return true;
}

bool verifyCopyBufferResults(const void *sourceCopyBuffer, const void *destinationCopyBuffer, size_t bufferSize) {
    log<Verbosity::info>("Validating results of CopyBuffer kernel execution!");

    const auto src = static_cast<const char *>(sourceCopyBuffer);
    const auto dst = static_cast<const char *>(destinationCopyBuffer);

    for (size_t i = 0; i < bufferSize; ++i) {
        if (src[i] != dst[i]) {
            log<Verbosity::error>(
                "Destination of CopyBuffer contains invalid value! Expected: %d, Actual: %d at index %zd.",
                static_cast<int>(src[i]), static_cast<int>(dst[i]), i);
            return false;
        }
    }

    log<Verbosity::info>("CopyBuffer passed validation!");
    return true;
}

bool verifyDoubleValsResults(const void *sourceDoubleVals, const void *destinationDoubleVals, size_t bufferSize) {
    log<Verbosity::info>("Validating results of DoubleVals kernel execution!");

    const auto src = static_cast<const unsigned int *>(sourceDoubleVals);
    const auto dst = static_cast<const unsigned int *>(destinationDoubleVals);
    const auto count = bufferSize / sizeof(unsigned int);

    for (size_t i = 0; i < count; ++i) {
        if ((2 * src[i]) != dst[i]) {
            log<Verbosity::error>(
                "Destination of DoubleVals contains invalid value! Expected: %d, Actual: %d at index %zd.", 2 * src[i],
                dst[i], i);
            return false;
        }
    }

    log<Verbosity::info>("DoubleVals passed validation!");
    return true;
}

bool queryKernelTimestamp(ze_event_handle_t event, ze_device_handle_t device) {
    log<Verbosity::info>("Querying kernel timestamp via zeEventQueryKernelTimestamp()");

    ze_kernel_timestamp_result_t kernelTsResults{};
    const auto zeEventQueryKernelTimestampsResult = zeEventQueryKernelTimestamp(event, &kernelTsResults);
    if (zeEventQueryKernelTimestampsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryKernelTimestamp() call has failed! Error code = %d",
                              static_cast<int>(zeEventQueryKernelTimestampsResult));
        return false;
    }

    log<Verbosity::info>("Getting timerResolution via zeDeviceGetProperties()");

    ze_device_properties_t deviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
    const auto zeDeviceGetPropertiesResult = zeDeviceGetProperties(device, &deviceProperties);
    if (zeDeviceGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetProperties() call has failed! Error code = %d",
                              static_cast<int>(zeDeviceGetPropertiesResult));
        return false;
    }

    uint64_t timerResolution = deviceProperties.timerResolution;
    uint64_t kernelDuration = kernelTsResults.context.kernelEnd - kernelTsResults.context.kernelStart;

    log<Verbosity::info>("Kernel timestamp statistics: \n"
                         " Global start : %lx cycles\n"
                         " Kernel start:  %lx cycles\n"
                         " Kernel end: %lx cycles\n"
                         " Global end: %lx cycles\n"
                         " timerResolution clock: %d ns\n"
                         " Kernel duration : %d cycles",
                         kernelTsResults.global.kernelStart, kernelTsResults.context.kernelStart,
                         kernelTsResults.context.kernelEnd, kernelTsResults.global.kernelEnd, timerResolution,
                         kernelDuration);
    return true;
}

bool queryTimestampsExp(ze_event_handle_t event, ze_device_handle_t device) {
    uint32_t count = 0;
    auto zeEventQueryTimestampsExpResult = zeEventQueryTimestampsExp(event, device, &count, nullptr);
    if (zeEventQueryTimestampsExpResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryTimestampsExp() call has failed! Error code = %d",
                              static_cast<int>(zeEventQueryTimestampsExpResult));
        return false;
    }

    log<Verbosity::info>("zeEventQueryTimestampsExp() call was successful, count = %d", count);

    if (count == 0) {
        return true;
    }

    auto timestamps = std::make_unique<ze_kernel_timestamp_result_t[]>(count);
    zeEventQueryTimestampsExpResult = zeEventQueryTimestampsExp(event, device, &count, timestamps.get());
    if (zeEventQueryTimestampsExpResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryTimestampsExp() call has failed! Error code = %d",
                              static_cast<int>(zeEventQueryTimestampsExpResult));
        return false;
    }

    log<Verbosity::info>("zeEventQueryTimestampsExp() call was successful");
    return true;
}

bool queryKernelTimestampsExt(ze_event_handle_t event, ze_device_handle_t device) {
    uint32_t count = 0;
    auto zeEventQueryKernelTimestampsExtResult = zeEventQueryKernelTimestampsExt(event, device, &count, nullptr);
    if (zeEventQueryKernelTimestampsExtResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryKernelTimestampsExt() call has failed! Error code = %d",
                              static_cast<int>(zeEventQueryKernelTimestampsExtResult));
        return false;
    }

    log<Verbosity::info>("zeEventQueryKernelTimestampsExt() call was successful, count = %d", count);
    if (count == 0) {
        return true;
    }

    constexpr size_t MAX_COUNT = 8;

    if (count > MAX_COUNT) {
        log<Verbosity::error>("count is %d, which is greater than MAX_COUNT of %d", count, MAX_COUNT);
        return false;
    }

    std::array<ze_kernel_timestamp_result_t, MAX_COUNT> tsBuffer;
    std::array<ze_synchronized_timestamp_result_ext_t, MAX_COUNT> synchronizedTsBuffer;
    ze_event_query_kernel_timestamps_results_ext_properties_t timestampsProperties{};
    timestampsProperties.pNext = nullptr;
    timestampsProperties.stype = ZE_STRUCTURE_TYPE_EVENT_QUERY_KERNEL_TIMESTAMPS_RESULTS_EXT_PROPERTIES;
    timestampsProperties.pKernelTimestampsBuffer = tsBuffer.data();
    timestampsProperties.pSynchronizedTimestampsBuffer = synchronizedTsBuffer.data();

    zeEventQueryKernelTimestampsExtResult = zeEventQueryKernelTimestampsExt(event, device, &count, &timestampsProperties);
    if (zeEventQueryKernelTimestampsExtResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryKernelTimestampsExt() call has failed! Error code = %d",
                              static_cast<int>(zeEventQueryKernelTimestampsExtResult));
        return false;
    }

    log<Verbosity::info>("zeEventQueryKernelTimestampsExt() call was successful");
    return true;
}

bool inspectModulesLinkage(uint32_t numModules, ze_module_handle_t *modules, ze_linkage_inspection_ext_flags_t flags, ze_module_build_log_handle_t *inspectionLog) {
    ze_linkage_inspection_ext_desc_t linkageInspectionDesc{};
    linkageInspectionDesc.pNext = nullptr;
    linkageInspectionDesc.stype = ZE_STRUCTURE_TYPE_LINKAGE_INSPECTION_EXT_DESC;
    linkageInspectionDesc.flags = flags;

    auto zeModuleInspectLinkageExtResult = zeModuleInspectLinkageExt(&linkageInspectionDesc, numModules, modules, inspectionLog);
    if (zeModuleInspectLinkageExtResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleInspectLinkageExt() call has failed! Error code = %d",
                              static_cast<int>(zeModuleInspectLinkageExtResult));
        return false;
    }

    log<Verbosity::info>("zeModuleInspectLinkageExt() call was successful");
    return true;
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

    std::vector<uint8_t> spirv{};
    RUN_REQUIRED_STEP(generateSpirv(spirv, simpleKernelSource));

    RUN_REQUIRED_STEP(testBuildLogFunctions(context, devices[0], spirv, ZE_MODULE_FORMAT_IL_SPIRV));

    ze_module_handle_t module{};
    RUN_REQUIRED_STEP(createModule(context, devices[0], spirv, ZE_MODULE_FORMAT_IL_SPIRV, module, "-library-compilation"));

    std::vector<uint8_t> nativeBinary{};
    RUN_REQUIRED_STEP(getNativeBinary(nativeBinary, module));

    ze_module_handle_t anotherModule{};
    RUN_REQUIRED_STEP(createModule(context, devices[0], nativeBinary, ZE_MODULE_FORMAT_NATIVE, anotherModule));

    RUN_REQUIRED_STEP(getKernelNames(module));
    RUN_REQUIRED_STEP(getModuleProperties(module));
    RUN_REQUIRED_STEP(getNonexistentFunctionPointer(module));
    RUN_REQUIRED_STEP(getNonexistentGlobalVariable(module));

    ze_module_handle_t modules[2] = {module, anotherModule};
    ze_module_build_log_handle_t inspectionLog;
    RUN_REQUIRED_STEP(inspectModulesLinkage(2, modules, ZE_LINKAGE_INSPECTION_EXT_FLAG_EXPORTS, &inspectionLog));
    RUN_REQUIRED_STEP(checkBuildLog(inspectionLog));

    ze_kernel_handle_t copyBufferKernel{};
    RUN_REQUIRED_STEP(createKernel(module, copyBufferKernel, "CopyBuffer"));

    RUN_REQUIRED_STEP(getKernelName(copyBufferKernel));
    RUN_REQUIRED_STEP(getTotalGroupCount(copyBufferKernel));
    RUN_REQUIRED_STEP(getKernelProperties(copyBufferKernel));
    RUN_REQUIRED_STEP(setCacheConfig(copyBufferKernel, ZE_CACHE_CONFIG_FLAG_LARGE_SLM));

    ze_scheduling_hint_exp_desc_t schedulingHint = {
        ZE_STRUCTURE_TYPE_SCHEDULING_HINT_EXP_DESC, // stype
        nullptr,                                    // pNext
        ZE_SCHEDULING_HINT_EXP_FLAG_ROUND_ROBIN     // flags
    };

    RUN_REQUIRED_STEP(setSchedulingHint(copyBufferKernel, schedulingHint));

    ze_kernel_indirect_access_flags_t indirectAccessFlags{};
    RUN_REQUIRED_STEP(getIndirectAccessFlags(copyBufferKernel, indirectAccessFlags));
    RUN_REQUIRED_STEP(setIndirectAccessFlags(copyBufferKernel, indirectAccessFlags));

    constexpr int xSize{1024};
    constexpr int ySize{1};
    constexpr int zSize{1};

    uint32_t suggestedGroupSizeX{};
    uint32_t suggestedGroupSizeY{};
    uint32_t suggestedGroupSizeZ{};

    RUN_REQUIRED_STEP(suggestGroupSize(copyBufferKernel, xSize, ySize, zSize, suggestedGroupSizeX, suggestedGroupSizeY,
                                       suggestedGroupSizeZ));
    RUN_REQUIRED_STEP(setGroupSize(copyBufferKernel, suggestedGroupSizeX, suggestedGroupSizeY, suggestedGroupSizeZ));

    ze_kernel_handle_t doubleValsKernel{};
    RUN_REQUIRED_STEP(createKernel(module, doubleValsKernel, "DoubleVals"));
    RUN_REQUIRED_STEP(getKernelName(doubleValsKernel));
    RUN_REQUIRED_STEP(setGroupSize(doubleValsKernel, suggestedGroupSizeX, suggestedGroupSizeY, suggestedGroupSizeZ));

    uint32_t ordinal{};
    RUN_REQUIRED_STEP(getComputeQueueOrdinal(devices[0], ordinal));

    ze_command_queue_handle_t queue{};
    RUN_REQUIRED_STEP(createCommandQueue(context, devices[0], ordinal, queue, ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS));

    ze_command_list_handle_t cmdList{};
    RUN_REQUIRED_STEP(createCommandList(context, devices[0], ordinal, cmdList));

    constexpr uint32_t eventsCount{10};
    ze_event_pool_handle_t eventPool{};
    RUN_REQUIRED_STEP(createEventPool(context, eventsCount, &devices[0], 1, eventPool));

    constexpr size_t bufferSize{xSize * sizeof(unsigned int)};
    constexpr size_t alignment{8};

    void *sourceCopyBuffer{nullptr};
    void *destinationCopyBuffer{nullptr};

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, sourceCopyBuffer));
    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, destinationCopyBuffer));

    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(sourceCopyBuffer, 0xFF, bufferSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(destinationCopyBuffer, 0xAA, bufferSize));

    RUN_REQUIRED_STEP(setKernelArgument(copyBufferKernel, 0, sizeof(sourceCopyBuffer), &sourceCopyBuffer));
    RUN_REQUIRED_STEP(setKernelArgument(copyBufferKernel, 1, sizeof(destinationCopyBuffer), &destinationCopyBuffer));

    ze_event_handle_t copyBufferFinishedEvent{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 1, copyBufferFinishedEvent));

    ze_group_count_t launchArgs{};
    launchArgs.groupCountX = xSize / suggestedGroupSizeX;
    launchArgs.groupCountY = ySize / suggestedGroupSizeY;
    launchArgs.groupCountZ = zSize / suggestedGroupSizeZ;

    RUN_REQUIRED_STEP(appendLaunchKernel(cmdList, copyBufferKernel, launchArgs, copyBufferFinishedEvent));

    struct TimestampResult {
        uint8_t otherData[8];
        ze_kernel_timestamp_result_t timestampResult;
    } timestampResultStruct;
    const size_t timestampResultOffsets[] = {offsetof(TimestampResult, timestampResult)};
    RUN_REQUIRED_STEP(appendQueryKernelTimestamps(cmdList, 1, &copyBufferFinishedEvent, &timestampResultStruct, timestampResultOffsets));

    RUN_REQUIRED_STEP(queryTimestampsExp(copyBufferFinishedEvent, devices[0]));
    RUN_REQUIRED_STEP(queryKernelTimestampsExt(copyBufferFinishedEvent, devices[0]));

    void *sourceDoubleVals{nullptr};
    void *destinationDoubleVals{nullptr};

    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, sourceDoubleVals));
    RUN_REQUIRED_STEP(allocateHostMemory(context, bufferSize, alignment, destinationDoubleVals));

    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(sourceDoubleVals, 0x1, bufferSize));
    RUN_REQUIRED_STEP(fillBufferOnHostViaMemset(destinationDoubleVals, 0x2, bufferSize));

    RUN_REQUIRED_STEP(setKernelArgument(doubleValsKernel, 0, sizeof(sourceDoubleVals), &sourceDoubleVals));
    RUN_REQUIRED_STEP(setKernelArgument(doubleValsKernel, 1, sizeof(destinationDoubleVals), &destinationDoubleVals));

    RUN_REQUIRED_STEP(setGlobalOffset(doubleValsKernel, 0, 0, 0));

    void *indirectLaunchArgs{nullptr};
    RUN_REQUIRED_STEP(
        allocateDeviceMemory(context, sizeof(ze_group_count_t), sizeof(uint32_t), devices[0], indirectLaunchArgs));

    ze_event_handle_t indirectLaunchArgsPreparedEvent{};
    RUN_REQUIRED_STEP(createEvent(eventPool, 2, indirectLaunchArgsPreparedEvent));

    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, indirectLaunchArgs, &launchArgs, sizeof(ze_group_count_t),
                                       indirectLaunchArgsPreparedEvent));
    RUN_REQUIRED_STEP(appendLaunchKernelIndirect(cmdList, doubleValsKernel,
                                                 static_cast<ze_group_count_t *>(indirectLaunchArgs), nullptr, 1,
                                                 &indirectLaunchArgsPreparedEvent));

    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(verifyCopyBufferResults(sourceCopyBuffer, destinationCopyBuffer, bufferSize));
    RUN_REQUIRED_STEP(verifyDoubleValsResults(sourceDoubleVals, destinationDoubleVals, bufferSize));

    RUN_REQUIRED_STEP(queryKernelTimestamp(copyBufferFinishedEvent, devices[0]));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    RUN_REQUIRED_STEP(appendLaunchCooperativeKernel(cmdList, copyBufferKernel, launchArgs, copyBufferFinishedEvent));
    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(resetCommandList(cmdList));
    ze_kernel_handle_t kernels[] = {copyBufferKernel, doubleValsKernel};
    void *countBuffer{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, sizeof(uint32_t), sizeof(uint32_t), devices[0], countBuffer));
    void *multipleKernelsIndirectLaunchArgs{nullptr};
    RUN_REQUIRED_STEP(allocateDeviceMemory(context, sizeof(ze_group_count_t) * 2, sizeof(uint32_t), devices[0], multipleKernelsIndirectLaunchArgs));
    ze_event_handle_t multipleKernelsIndirectLaunchArgsPreparedEvents[2];
    RUN_REQUIRED_STEP(createEvent(eventPool, 3, multipleKernelsIndirectLaunchArgsPreparedEvents[0]));
    RUN_REQUIRED_STEP(createEvent(eventPool, 4, multipleKernelsIndirectLaunchArgsPreparedEvents[1]));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, multipleKernelsIndirectLaunchArgs, &launchArgs, sizeof(ze_group_count_t),
                                       multipleKernelsIndirectLaunchArgsPreparedEvents[0]));
    RUN_REQUIRED_STEP(appendMemoryCopy(cmdList, static_cast<ze_group_count_t *>(multipleKernelsIndirectLaunchArgs) + 1, &launchArgs,
                                       sizeof(ze_group_count_t), multipleKernelsIndirectLaunchArgsPreparedEvents[1]));
    RUN_REQUIRED_STEP(appendLaunchMultipleKernelsIndirect(cmdList, 2, kernels, static_cast<const uint32_t *>(countBuffer),
                                                          static_cast<ze_group_count_t *>(multipleKernelsIndirectLaunchArgs),
                                                          nullptr, 2, multipleKernelsIndirectLaunchArgsPreparedEvents));
    RUN_REQUIRED_STEP(closeCommandList(cmdList));
    RUN_REQUIRED_STEP(executeCommandLists(queue, 1, &cmdList, nullptr));
    RUN_REQUIRED_STEP(synchronizeCommandQueue(queue));

    RUN_REQUIRED_STEP(destroyEvent(multipleKernelsIndirectLaunchArgsPreparedEvents[1]));
    RUN_REQUIRED_STEP(destroyEvent(multipleKernelsIndirectLaunchArgsPreparedEvents[0]));
    RUN_REQUIRED_STEP(destroyEvent(indirectLaunchArgsPreparedEvent));
    RUN_REQUIRED_STEP(destroyEvent(copyBufferFinishedEvent));
    RUN_REQUIRED_STEP(destroyEventPool(eventPool));
    RUN_REQUIRED_STEP(destroyCommandList(cmdList));
    RUN_REQUIRED_STEP(destroyCommandQueue(queue));

    RUN_REQUIRED_STEP(freeMemory(context, indirectLaunchArgs));
    RUN_REQUIRED_STEP(freeMemory(context, sourceDoubleVals));
    RUN_REQUIRED_STEP(freeMemory(context, destinationDoubleVals));

    RUN_REQUIRED_STEP(freeMemory(context, sourceCopyBuffer));
    RUN_REQUIRED_STEP(freeMemory(context, destinationCopyBuffer));

    RUN_REQUIRED_STEP(destroyKernel(doubleValsKernel));
    RUN_REQUIRED_STEP(destroyKernel(copyBufferKernel));

    RUN_REQUIRED_STEP(destroyModule(anotherModule));
    RUN_REQUIRED_STEP(destroyModule(module));

    RUN_REQUIRED_STEP(destroyContext(context));
}
