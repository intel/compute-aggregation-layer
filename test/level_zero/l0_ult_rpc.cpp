/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_rpc_messages_level_zero.h"
#include "gtest/gtest.h"
#include "service/service.h"
#include "test/utils/cli_utils.h"
#include "test/utils/custom_event_listener.h"
#include "test/utils/signal_utils.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <memory>

namespace Cal::Rpc::LevelZero {

TEST(ZeModuleCreateExtensionsTest, GivenOpaqueListWithExtendedModuleDescriptionsWhenCopyingAndReassemblingMessageThenExtensionsAreProperlyHandled) {
    // 0. Prepare extension and ze_module_desc_t.
    constexpr uint32_t modulesCount{2u};

    constexpr size_t firstModuleSize = 8u;
    constexpr size_t secondModuleSize = 16u;
    const std::array<size_t, modulesCount> inputSizes = {firstModuleSize, secondModuleSize};

    constexpr uint8_t firstModule[firstModuleSize] = {1, 2, 3, 4, 5, 6, 7, 8};
    constexpr uint8_t secondModule[secondModuleSize] = {9, 9, 9, 9, 1, 1, 1, 1, 4, 4, 4, 4, 3, 2, 5, 7};
    std::array<const uint8_t *, modulesCount> inputModules = {&firstModule[0], &secondModule[0]};

    constexpr const char *firstBuildFlags = "--some-flags --of-first-module";
    constexpr const char *secondBuildFlags = "--some-other-flags --of-other-module";
    std::array<const char *, modulesCount> buildFlags = {firstBuildFlags, secondBuildFlags};

    constexpr static size_t firstConstantsCount = 3;
    std::array<uint32_t, firstConstantsCount> firstConstantsIds = {3, 13, 53};
    std::array<uint64_t, firstConstantsCount> firstConstantsValuesStorage = {7, 29, 33};
    std::array<const void *, firstConstantsCount> firstConstantsValues = {&firstConstantsValuesStorage[0],
                                                                          &firstConstantsValuesStorage[1],
                                                                          &firstConstantsValuesStorage[2]};
    ze_module_constants_t firstConstants = {
        firstConstantsCount,
        firstConstantsIds.data(),
        firstConstantsValues.data()};

    constexpr static size_t secondConstantsCount = 1;
    std::array<uint32_t, secondConstantsCount> secondConstantsIds = {2};
    std::array<uint64_t, secondConstantsCount> secondConstantsValuesStorage = {27};
    std::array<const void *, secondConstantsCount> secondConstantsValues = {&secondConstantsValuesStorage[0]};

    ze_module_constants_t secondConstants = {
        secondConstantsCount,
        secondConstantsIds.data(),
        secondConstantsValues.data()};

    std::array<const ze_module_constants_t *, modulesCount> constants = {&firstConstants, &secondConstants};

    ze_module_program_exp_desc_t moduleExpDesc = {
        ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC, // stype
        nullptr,                                   // pNext
        modulesCount,                              // count
        inputSizes.data(),                         // inputSizes
        inputModules.data(),                       // pInputModules
        buildFlags.data(),                         // pBuildFlags
        constants.data()                           // pConstants
    };

    // When the extension is used  pInputModule, pBuildFlags and pConstants are ignored.
    // However, in this test case we want to check the generic code generator and thus we set SPIR-V fields.
    constexpr static size_t spirvLen = 20;
    std::array<uint8_t, spirvLen> spirV = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    ze_module_desc_t moduleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC, // stype
        &moduleExpDesc,                // pNext
        ZE_MODULE_FORMAT_IL_SPIRV,     // format
        spirvLen,                      // inputSize
        spirV.data(),                  // pInputModule
    };

    // Dummy objects. Handles are passed as values.
    ze_context_handle_t contextHandle{};
    ze_device_handle_t deviceHandle{};
    ze_module_handle_t moduleHandle{};
    ze_module_build_log_handle_t buildLogHandle{};

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeModuleCreateRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(contextHandle, deviceHandle, &moduleDescription, &moduleHandle, &buildLogHandle);
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, contextHandle, deviceHandle, &moduleDescription, &moduleHandle, &buildLogHandle);

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits);

    // 4. Ensure that addresses were only shallow-copied and nullptrs were not changed.
    ASSERT_EQ(&moduleExpDesc, command->captures.desc.pNext);
    ASSERT_EQ(spirV.data(), command->captures.desc.pInputModule);
    ASSERT_EQ(nullptr, command->captures.desc.pBuildFlags);
    ASSERT_EQ(nullptr, command->captures.desc.pConstants);

    // 5. Reassemble captures.
    command->captures.reassembleNestedStructs();

    // 6. Verify data.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pNext));
    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pInputModule));
    ASSERT_EQ(spirvLen, command->captures.desc.inputSize);
    ASSERT_EQ(nullptr, command->captures.desc.pBuildFlags);
    ASSERT_EQ(nullptr, command->captures.desc.pConstants);

    EXPECT_EQ(0, std::memcmp(moduleDescription.pInputModule, command->captures.desc.pInputModule, spirvLen));

    const auto extensionInDynMem = static_cast<const ze_module_program_exp_desc_t *>(command->captures.desc.pNext);
    ASSERT_EQ(ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC, extensionInDynMem->stype);

    EXPECT_EQ(nullptr, extensionInDynMem->pNext);
    EXPECT_EQ(modulesCount, extensionInDynMem->count);

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->inputSizes));
    ASSERT_EQ(firstModuleSize, extensionInDynMem->inputSizes[0]);
    ASSERT_EQ(secondModuleSize, extensionInDynMem->inputSizes[1]);

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pInputModules));
    EXPECT_EQ(0, std::memcmp(firstModule, extensionInDynMem->pInputModules[0], firstModuleSize));
    EXPECT_EQ(0, std::memcmp(secondModule, extensionInDynMem->pInputModules[1], secondModuleSize));

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pBuildFlags));
    EXPECT_STREQ(firstBuildFlags, extensionInDynMem->pBuildFlags[0]);
    EXPECT_STREQ(secondBuildFlags, extensionInDynMem->pBuildFlags[1]);

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants));
    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants[0]));
    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants[1]));

    EXPECT_EQ(firstConstantsCount, extensionInDynMem->pConstants[0]->numConstants);
    EXPECT_EQ(secondConstantsCount, extensionInDynMem->pConstants[1]->numConstants);

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants[0]->pConstantIds));
    EXPECT_EQ(0, std::memcmp(firstConstantsIds.data(), extensionInDynMem->pConstants[0]->pConstantIds, sizeof(uint32_t) * firstConstantsCount));

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants[1]->pConstantIds));
    EXPECT_EQ(0, std::memcmp(secondConstantsIds.data(), extensionInDynMem->pConstants[1]->pConstantIds, sizeof(uint32_t) * secondConstantsCount));

    for (auto i = 0u; i < firstConstantsCount; ++i) {
        ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants[0]->pConstantValues[i]));

        auto *firstConstantValue = static_cast<const uint64_t *>(extensionInDynMem->pConstants[0]->pConstantValues[i]);
        EXPECT_EQ(firstConstantsValuesStorage[i], *firstConstantValue);
    }

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pConstants[1]->pConstantValues[0]));
    auto *secondConstantValue = static_cast<const uint64_t *>(extensionInDynMem->pConstants[1]->pConstantValues[0]);
    EXPECT_EQ(secondConstantsValuesStorage[0], *secondConstantValue);
}

TEST(ZeModuleCreateExtensionsTest, GivenOpaqueListWithExtendedModuleDescriptionsWithSomeNullptrFieldsWhenCopyingAndReassemblingMessageThenExtensionsAreProperlyHandled) {
    // 0. Prepare extension and ze_module_desc_t.
    constexpr uint32_t modulesCount{2u};

    constexpr size_t firstModuleSize = 8u;
    constexpr size_t secondModuleSize = 16u;
    const std::array<size_t, modulesCount> inputSizes = {firstModuleSize, secondModuleSize};

    constexpr uint8_t firstModule[firstModuleSize] = {1, 2, 3, 4, 5, 6, 7, 8};
    constexpr uint8_t secondModule[secondModuleSize] = {9, 9, 9, 9, 1, 1, 1, 1, 4, 4, 4, 4, 3, 2, 5, 7};
    std::array<const uint8_t *, modulesCount> inputModules = {&firstModule[0], &secondModule[0]};

    constexpr const char *firstBuildFlags = "--some-flags --of-first-module";
    constexpr const char *secondBuildFlags = "--some-other-flags --of-other-module";
    std::array<const char *, modulesCount> buildFlags = {firstBuildFlags, secondBuildFlags};

    ze_module_program_exp_desc_t moduleExpDesc = {
        ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC, // stype
        nullptr,                                   // pNext
        modulesCount,                              // count
        inputSizes.data(),                         // inputSizes
        inputModules.data(),                       // pInputModules
        buildFlags.data(),                         // pBuildFlags
        nullptr                                    // pConstants
    };

    constexpr static size_t spirvLen = 20;
    std::array<uint8_t, spirvLen> spirV = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    ze_module_desc_t moduleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC, // stype
        &moduleExpDesc,                // pNext
        ZE_MODULE_FORMAT_IL_SPIRV,     // format
        spirvLen,                      // inputSize
        spirV.data(),                  // pInputModule
    };

    // Dummy objects. Handles are passed as values.
    ze_context_handle_t contextHandle{};
    ze_device_handle_t deviceHandle{};
    ze_module_handle_t moduleHandle{};
    ze_module_build_log_handle_t buildLogHandle{};

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeModuleCreateRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(contextHandle, deviceHandle, &moduleDescription, &moduleHandle, &buildLogHandle);
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, contextHandle, deviceHandle, &moduleDescription, &moduleHandle, &buildLogHandle);

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits);

    // 4. Ensure that addresses were only shallow-copied and nullptrs were not changed.
    ASSERT_EQ(&moduleExpDesc, command->captures.desc.pNext);
    ASSERT_EQ(spirV.data(), command->captures.desc.pInputModule);
    ASSERT_EQ(nullptr, command->captures.desc.pBuildFlags);
    ASSERT_EQ(nullptr, command->captures.desc.pConstants);

    // 5. Reassemble captures.
    command->captures.reassembleNestedStructs();

    // 6. Verify data.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pNext));
    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pInputModule));
    ASSERT_EQ(spirvLen, command->captures.desc.inputSize);
    ASSERT_EQ(nullptr, command->captures.desc.pBuildFlags);
    ASSERT_EQ(nullptr, command->captures.desc.pConstants);

    EXPECT_EQ(0, std::memcmp(moduleDescription.pInputModule, command->captures.desc.pInputModule, spirvLen));

    const auto extensionInDynMem = static_cast<const ze_module_program_exp_desc_t *>(command->captures.desc.pNext);
    ASSERT_EQ(ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC, extensionInDynMem->stype);

    EXPECT_EQ(nullptr, extensionInDynMem->pNext);
    EXPECT_EQ(nullptr, extensionInDynMem->pConstants);
    EXPECT_EQ(modulesCount, extensionInDynMem->count);

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->inputSizes));
    ASSERT_EQ(firstModuleSize, extensionInDynMem->inputSizes[0]);
    ASSERT_EQ(secondModuleSize, extensionInDynMem->inputSizes[1]);

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pInputModules));
    EXPECT_EQ(0, std::memcmp(firstModule, extensionInDynMem->pInputModules[0], firstModuleSize));
    EXPECT_EQ(0, std::memcmp(secondModule, extensionInDynMem->pInputModules[1], secondModuleSize));

    ASSERT_TRUE(pointsToDynMemBuffer(extensionInDynMem->pBuildFlags));
    EXPECT_STREQ(firstBuildFlags, extensionInDynMem->pBuildFlags[0]);
    EXPECT_STREQ(secondBuildFlags, extensionInDynMem->pBuildFlags[1]);
}

TEST(ZeMemAllocSharedExtensionsTest, GivenOpaqueListsAttachedToTwoDifferentFunctionArgumentsWhenCopyingAndReassemblingTwiceMessageThenExtensionsAreProperlyHandled) {
    ze_relaxed_allocation_limits_exp_desc_t relaxedLimitsDescForDeviceMemDesc = {
        ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC, // stype
        nullptr,                                              // pNext
        ZE_RELAXED_ALLOCATION_LIMITS_EXP_FLAG_MAX_SIZE        // flags
    };

    ze_raytracing_mem_alloc_ext_desc_t raytracingMemAllocDesc = {
        ZE_STRUCTURE_TYPE_RAYTRACING_MEM_ALLOC_EXT_DESC, // stype
        &relaxedLimitsDescForDeviceMemDesc,              // pNext
        0                                                // flags
    };

    // First function argument. Contains two extension defined as opaque list.
    ze_device_mem_alloc_desc_t deviceMemAllocDesc = {ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC, &raytracingMemAllocDesc};

    ze_relaxed_allocation_limits_exp_desc_t relaxedLimitsDescForHostMemDesc1 = {
        ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC, // stype
        nullptr,                                              // pNext
        ZE_RELAXED_ALLOCATION_LIMITS_EXP_FLAG_MAX_SIZE        // flags
    };

    ze_relaxed_allocation_limits_exp_desc_t relaxedLimitsDescForHostMemDesc2 = {
        ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC, // stype
        &relaxedLimitsDescForHostMemDesc1,                    // pNext
        ZE_RELAXED_ALLOCATION_LIMITS_EXP_FLAG_MAX_SIZE        // flags
    };

    // Second function argument. Contains two extensions defined as opaque list.
    ze_host_mem_alloc_desc_t hostMemAllocDesc = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC, &relaxedLimitsDescForHostMemDesc2};

    // Dummy parameters needed to create message object.
    ze_context_handle_t contextHandle{};
    ze_device_handle_t deviceHandle{};
    void *usmSharedBuffer{};
    size_t bufferSize{};
    size_t alignment{};

    Cal::Rpc::LevelZero::ZeMemAllocSharedRpcMImplicitArgs implicitArgs{};

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(contextHandle, &deviceMemAllocDesc, &hostMemAllocDesc, bufferSize, alignment, deviceHandle, &usmSharedBuffer);
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, contextHandle, &deviceMemAllocDesc, &hostMemAllocDesc, bufferSize, alignment, deviceHandle, &usmSharedBuffer);

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits, implicitArgs);

    // 4. Ensure that address was only shallow-copied and pointers are invalid.
    ASSERT_EQ(&raytracingMemAllocDesc, command->captures.device_desc.pNext);
    ASSERT_EQ(&relaxedLimitsDescForHostMemDesc2, command->captures.host_desc.pNext);

    // 5. Reassemble captures twice. We simulate a situation, when reassemble is called firstly in ICD to transform opaque lists and then
    //    it is called in service to allow passing to UMD.
    command->captures.reassembleNestedStructs();
    command->captures.reassembleNestedStructs();

    // 6. Verify pointers.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    // Second function argument.
    EXPECT_EQ(hostMemAllocDesc.stype, command->captures.host_desc.stype);
    ASSERT_NE(&relaxedLimitsDescForHostMemDesc2, command->captures.host_desc.pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.host_desc.pNext));

    auto *relaxedLimitsDescForHost2InDynMem = static_cast<const ze_relaxed_allocation_limits_exp_desc_t *>(command->captures.host_desc.pNext);
    EXPECT_EQ(relaxedLimitsDescForHostMemDesc2.stype, relaxedLimitsDescForHost2InDynMem->stype);
    ASSERT_NE(&relaxedLimitsDescForHostMemDesc1, relaxedLimitsDescForHost2InDynMem->pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(relaxedLimitsDescForHost2InDynMem->pNext));

    auto *relaxedLimitsDescForHost1InDynMem = static_cast<const ze_relaxed_allocation_limits_exp_desc_t *>(relaxedLimitsDescForHost2InDynMem->pNext);
    EXPECT_EQ(relaxedLimitsDescForHostMemDesc1.stype, relaxedLimitsDescForHost1InDynMem->stype);
    ASSERT_EQ(nullptr, relaxedLimitsDescForHost1InDynMem->pNext);

    // First function argument.
    EXPECT_EQ(deviceMemAllocDesc.stype, command->captures.device_desc.stype);
    ASSERT_NE(&raytracingMemAllocDesc, command->captures.device_desc.pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.device_desc.pNext));

    auto *raytracingMemAllocDescInMem = static_cast<const ze_raytracing_mem_alloc_ext_desc_t *>(command->captures.device_desc.pNext);
    EXPECT_EQ(raytracingMemAllocDesc.stype, raytracingMemAllocDescInMem->stype);
    ASSERT_NE(&relaxedLimitsDescForDeviceMemDesc, raytracingMemAllocDescInMem->pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(raytracingMemAllocDescInMem->pNext));

    auto *relaxedLimitsDescForDeviceMemDescInDynMem = static_cast<const ze_relaxed_allocation_limits_exp_desc_t *>(raytracingMemAllocDescInMem->pNext);
    EXPECT_EQ(relaxedLimitsDescForDeviceMemDesc.stype, relaxedLimitsDescForDeviceMemDescInDynMem->stype);
    ASSERT_EQ(nullptr, relaxedLimitsDescForDeviceMemDescInDynMem->pNext);
}

TEST(ZeDeviceGetPropertiesExtensionsTest, GivenPassedExtensionsWhenCopyingAndReassemblingMessageThenExtensionsAreProperlyHandled) {
    // 0. Prepare two extensions and form opaque list from them.
    ze_eu_count_ext_t euCountExtension = {
        ZE_STRUCTURE_TYPE_EU_COUNT_EXT, // stype
        nullptr,                        // pNext
        0u                              // numTotalEUs
    };

    ze_device_luid_ext_properties_t luidExtension = {
        ZE_STRUCTURE_TYPE_DEVICE_LUID_EXT_PROPERTIES, // stype
        &euCountExtension,                            // pNext
        ze_device_luid_ext_t{},                       // luid
        0u                                            // nodeMask
    };

    ze_device_properties_t deviceProperties = {
        ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES, // stype
        &luidExtension                       // pNext
    };

    // Dummy device handle used to fulfill interface.
    ze_device_handle_t deviceHandle{};

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(deviceHandle, &deviceProperties);
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, deviceHandle, &deviceProperties);

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits);

    // 4. Ensure that address was only shallow-copied and pointers are invalid.
    ASSERT_EQ(&luidExtension, command->captures.pDeviceProperties.pNext);

    // 5. Reassemble captures.
    command->captures.reassembleNestedStructs();

    // 6. Verify pointers.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    EXPECT_EQ(deviceProperties.stype, command->captures.pDeviceProperties.stype);
    ASSERT_NE(&luidExtension, command->captures.pDeviceProperties.pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.pDeviceProperties.pNext));

    auto *luidInDynMem = static_cast<ze_device_luid_ext_properties_t *>(command->captures.pDeviceProperties.pNext);
    EXPECT_EQ(luidExtension.stype, luidInDynMem->stype);
    ASSERT_NE(&euCountExtension, luidInDynMem->pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(luidInDynMem->pNext));

    auto *euCountInDynMem = static_cast<ze_eu_count_ext_t *>(luidInDynMem->pNext);
    EXPECT_EQ(euCountExtension.stype, euCountInDynMem->stype);
    ASSERT_EQ(nullptr, euCountInDynMem->pNext);

    // 7. Modify scalar fields to simulate output parameters and then copy to caller.
    const auto expectedNumTotalEUs = 16u;
    euCountInDynMem->numTotalEUs = expectedNumTotalEUs;

    const auto expectedNodeMask = 15u;
    luidInDynMem->nodeMask = expectedNodeMask;

    const ze_device_luid_ext_t expectedLuid{"1234"};
    luidInDynMem->luid = expectedLuid;

    command->copyToCaller(dynMemTraits);

    // 8. Validate pointers and output fields.
    EXPECT_EQ(&luidExtension, deviceProperties.pNext);
    EXPECT_EQ(&euCountExtension, luidExtension.pNext);
    EXPECT_EQ(nullptr, euCountExtension.pNext);

    EXPECT_EQ(expectedNumTotalEUs, euCountExtension.numTotalEUs);
    EXPECT_EQ(expectedNodeMask, luidExtension.nodeMask);
    EXPECT_EQ(0, std::memcmp(expectedLuid.id, luidExtension.luid.id, ZE_MAX_DEVICE_LUID_SIZE_EXT));
}

TEST(OpaqueListReassemblationAndCopyTest, GivenCapturesWithOpaqueListNestedStructFieldWhenCopyingAndReassemblingTheStructureThenStructCapturesFieldsPointsToDynMem) {
    // 0. Prepare arguments, which need to be copied: opaque list -> 2 opaque elements appended to first, known element.
    ze_kernel_preferred_group_size_properties_t lastElement = {
        ZE_STRUCTURE_TYPE_KERNEL_PREFERRED_GROUP_SIZE_PROPERTIES, // stype
        nullptr,                                                  // pNext
        8u                                                        // preferredMultiple
    };

    ze_kernel_preferred_group_size_properties_t secondElement = {
        ZE_STRUCTURE_TYPE_KERNEL_PREFERRED_GROUP_SIZE_PROPERTIES, // stype
        &lastElement,                                             // pNext
        4u                                                        // preferredMultiple
    };

    ze_kernel_properties_t firstElement{
        ZE_STRUCTURE_TYPE_KERNEL_PROPERTIES, // stype
        &secondElement,                      // pNext
        3u,                                  // numKernelArgs
        16u,                                 // requiredGroupSizeX
        32u,                                 // requiredGroupSizeY
        48u,                                 // requiredGroupSizeZ
        4u,                                  // requiredNumSubGroups
        12u,                                 // requiredSubgroupSize
        24u,                                 // maxSubgroupSize
        8u,                                  // maxNumSubgroups
        128u,                                // localMemSize
        64u,                                 // privateMemSize
        32u,                                 // spillMemSize
        ze_kernel_uuid_t{
            {1, 2, 3, 4}, // kid
            {5, 6, 7, 8}, // mid
        }};

    // Dummy kernel handle used to fulfill interface.
    ze_kernel_handle_t kernelHandle{};

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernelHandle, &firstElement);
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, kernelHandle, &firstElement);

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits);

    // 4.  Ensure that address was only shallow-copied and pointers are invalid.
    ASSERT_EQ(&secondElement, command->captures.pKernelProperties.pNext);

    // 5. Reassemble captures.
    command->captures.reassembleNestedStructs();

    // 6. Verify pointers.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    EXPECT_EQ(firstElement.stype, command->captures.pKernelProperties.stype);
    ASSERT_NE(&secondElement, command->captures.pKernelProperties.pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.pKernelProperties.pNext));

    auto secondElementInDynMem = reinterpret_cast<ze_kernel_preferred_group_size_properties_t *>(command->captures.pKernelProperties.pNext);
    EXPECT_EQ(secondElement.stype, secondElementInDynMem->stype);
    EXPECT_EQ(secondElement.preferredMultiple, secondElementInDynMem->preferredMultiple);
    ASSERT_NE(secondElement.pNext, secondElementInDynMem->pNext);
    ASSERT_TRUE(pointsToDynMemBuffer(secondElementInDynMem->pNext));

    auto thirdElementInDynMem = reinterpret_cast<ze_kernel_preferred_group_size_properties_t *>(secondElementInDynMem->pNext);
    EXPECT_EQ(lastElement.stype, thirdElementInDynMem->stype);
    EXPECT_EQ(lastElement.preferredMultiple, thirdElementInDynMem->preferredMultiple);
    EXPECT_EQ(nullptr, thirdElementInDynMem->pNext);

    // 7. Modify scalar fields to simulate output parameters and then copy to caller.
    constexpr auto expectedPreferredMultipleOfSecondElement = 44u;
    secondElementInDynMem->preferredMultiple = expectedPreferredMultipleOfSecondElement;

    constexpr auto expectedPreferredMultipleOfThirdElement = 21u;
    thirdElementInDynMem->preferredMultiple = expectedPreferredMultipleOfThirdElement;

    command->copyToCaller(dynMemTraits);

    // 8. Validate pointers and output fields.
    EXPECT_EQ(&secondElement, firstElement.pNext);

    EXPECT_EQ(expectedPreferredMultipleOfSecondElement, secondElement.preferredMultiple);
    EXPECT_EQ(&lastElement, secondElement.pNext);

    EXPECT_EQ(expectedPreferredMultipleOfThirdElement, lastElement.preferredMultiple);
    EXPECT_EQ(nullptr, lastElement.pNext);
}

TEST(OpaqueListReassemblationAndCopyTest, GivenMultipleDynamicCapturesWithOpaqueListNestedStructFieldWhenCopyingAndReassemblingTheStructuresThenStructCapturesFieldsPointsToDynMem) {
    // 0. Prepare arguments, which need to be copied:
    //     - dynamic array of two elements
    //     - each element contain opaque list with additional 1 opaque element
    std::array<ze_device_memory_properties_t, 2> deviceMemoryProperties = {};
    for (auto &property : deviceMemoryProperties) {
        property.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES;
    }

    ze_device_memory_ext_properties_t extensionOfFirst = {
        ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES, // stype
        nullptr,                                        // pNext
        ZE_DEVICE_MEMORY_EXT_TYPE_FORCE_UINT32,         // type
        0,                                              // physicalSize
        0,                                              // readBandwidth
        0,                                              // writeBandwidth
        ZE_BANDWIDTH_UNIT_FORCE_UINT32,                 // bandwidthUnit
    };

    ze_device_memory_ext_properties_t extensionOfSecond = {
        ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES, // stype
        nullptr,                                        // pNext
        ZE_DEVICE_MEMORY_EXT_TYPE_FORCE_UINT32,         // type
        0,                                              // physicalSize
        0,                                              // readBandwidth
        0,                                              // writeBandwidth
        ZE_BANDWIDTH_UNIT_FORCE_UINT32,                 // bandwidthUnit
    };

    deviceMemoryProperties[0].pNext = &extensionOfFirst;
    deviceMemoryProperties[1].pNext = &extensionOfSecond;

    // Dummy device handle used to fulfill interface.
    ze_device_handle_t deviceHandle{};
    uint32_t count = deviceMemoryProperties.size();

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(deviceHandle, &count, deviceMemoryProperties.data());
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, deviceHandle, &count, deviceMemoryProperties.data());

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits);

    // 4.  Ensure that addresses were only shallow-copied and pointers are invalid.
    auto *pMemProperties = command->captures.getPMemProperties();
    ASSERT_EQ(&extensionOfFirst, pMemProperties[0].pNext);
    ASSERT_EQ(&extensionOfSecond, pMemProperties[1].pNext);

    // 5. Reassemble captures.
    command->captures.reassembleNestedStructs();

    // 6. Verify pointers.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    ASSERT_NE(&extensionOfFirst, pMemProperties[0].pNext);
    EXPECT_TRUE(pointsToDynMemBuffer(pMemProperties[0].pNext));

    ASSERT_NE(&extensionOfSecond, pMemProperties[1].pNext);
    EXPECT_TRUE(pointsToDynMemBuffer(pMemProperties[1].pNext));

    // 7. Modify scalar fields to simulate output parameters and then copy to caller.
    auto *extensionOfFirstInDynMem = static_cast<ze_device_memory_ext_properties_t *>(pMemProperties[0].pNext);
    extensionOfFirstInDynMem->physicalSize = 128u;
    extensionOfFirstInDynMem->readBandwidth = 16u;
    extensionOfFirstInDynMem->writeBandwidth = 32u;

    auto *extensionOfSecondInDynMem = static_cast<ze_device_memory_ext_properties_t *>(pMemProperties[1].pNext);
    extensionOfSecondInDynMem->physicalSize = 256u;
    extensionOfSecondInDynMem->readBandwidth = 8u;
    extensionOfSecondInDynMem->writeBandwidth = 12u;

    command->copyToCaller(dynMemTraits);

    // 8. Validate pointers and output fields.
    ASSERT_EQ(&extensionOfFirst, deviceMemoryProperties[0].pNext);
    ASSERT_EQ(&extensionOfSecond, deviceMemoryProperties[1].pNext);

    EXPECT_EQ(128u, extensionOfFirst.physicalSize);
    EXPECT_EQ(16u, extensionOfFirst.readBandwidth);
    EXPECT_EQ(32u, extensionOfFirst.writeBandwidth);

    EXPECT_EQ(256u, extensionOfSecond.physicalSize);
    EXPECT_EQ(8u, extensionOfSecond.readBandwidth);
    EXPECT_EQ(12u, extensionOfSecond.writeBandwidth);
}

TEST(ReassemblationTest, GivenCapturesWithNestedStructFieldsWhenCopyingAndReassemblingTheStructureThenStructCapturesFieldsPointToDynMem) {
    // 0. Prepare arguments, which need to be copied.
    constexpr static size_t constantsCount = 3;
    std::array<uint32_t, constantsCount> constantsIds = {1, 5, 21};

    uint64_t firstConstant = 121;
    uint64_t secondConstant = 77;
    uint64_t thirdConstant = 212;
    std::array<const void *, constantsCount> constantValues = {&firstConstant, &secondConstant, &thirdConstant};

    ze_module_constants_t moduleConstants = {
        constantsCount,
        constantsIds.data(),
        constantValues.data()};

    constexpr static size_t spirvLen = 20;
    std::array<uint8_t, spirvLen> spirV = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // This structure and its nested fields need to be deep-copied and reassembled.
    ze_module_desc_t moduleHandleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC,
        nullptr,
        ZE_MODULE_FORMAT_IL_SPIRV,
        spirvLen,
        spirV.data(),
        "-Wno-recompiled-from-ir",
        &moduleConstants};

    // Dummy objects. Handles are passed as values.
    ze_context_handle_t contextHandle{};
    ze_device_handle_t deviceHandle{};
    ze_module_handle_t moduleHandle{};
    ze_module_build_log_handle_t buildLogHandle{};

    // 1. Prepare required offsets and calculate size.
    using CommandT = Cal::Rpc::LevelZero::ZeModuleCreateRpcM;

    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(contextHandle, deviceHandle, &moduleHandleDescription, &moduleHandle, &buildLogHandle);
    const auto requiredBufferSize = sizeof(CommandT) + dynMemTraits.totalDynamicSize;

    // 2. Allocate space and create command.
    auto space = std::make_unique<char[]>(requiredBufferSize);
    auto command = new (space.get()) CommandT(dynMemTraits, contextHandle, deviceHandle, &moduleHandleDescription, &moduleHandle, &buildLogHandle);

    // 3. Deep-copy all required data without reassemblation.
    command->copyFromCaller(dynMemTraits);

    // 4.  Ensure that addresses were only shallow-copied.
    ASSERT_EQ(moduleHandleDescription.pInputModule, command->captures.desc.pInputModule);
    ASSERT_EQ(moduleHandleDescription.pBuildFlags, command->captures.desc.pBuildFlags);
    ASSERT_EQ(moduleHandleDescription.pConstants, command->captures.desc.pConstants);

    // 5. Reassemble captures.
    command->captures.reassembleNestedStructs();

    // 6. Verify data.
    const auto pointsToDynMemBuffer = [dynMem = command->captures.dynMem, dynMemSize = command->captures.dynMemSize](const auto &ptr) {
        const auto dynMemBeginning = reinterpret_cast<uintptr_t>(dynMem);
        const auto dynMemEnd = dynMemBeginning + dynMemSize;

        const auto address = reinterpret_cast<uintptr_t>(ptr);
        return (dynMemBeginning <= address && address < dynMemEnd);
    };

    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pInputModule));
    EXPECT_EQ(0, std::memcmp(moduleHandleDescription.pInputModule, command->captures.desc.pInputModule, spirvLen));

    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pBuildFlags));
    EXPECT_STREQ(moduleHandleDescription.pBuildFlags, command->captures.desc.pBuildFlags);

    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pConstants));
    ASSERT_EQ(moduleHandleDescription.pConstants->numConstants, command->captures.desc.pConstants->numConstants);

    ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pConstants->pConstantIds));

    for (auto i = 0u; i < constantsCount; ++i) {
        EXPECT_EQ(moduleHandleDescription.pConstants->pConstantIds[i], command->captures.desc.pConstants->pConstantIds[i]);

        ASSERT_TRUE(pointsToDynMemBuffer(command->captures.desc.pConstants->pConstantValues[i]));

        const auto expectedConstantValue = *static_cast<const uint64_t *>(moduleHandleDescription.pConstants->pConstantValues[i]);
        const auto actualConstantValue = *static_cast<const uint64_t *>(command->captures.desc.pConstants->pConstantValues[i]);
        EXPECT_EQ(expectedConstantValue, actualConstantValue);
    }
}

TEST(CapturesAssignFrom, GivenTwoCapturesWithDifferentDynMemSizeWhenTryingToAssignThemThenFalseIsReturned) {
    using CommandT = Cal::Rpc::LevelZero::ZeKernelCreateRpcM;

    // First captures.
    ze_module_handle_t firstModuleHandle{};
    ze_kernel_handle_t firstKernelHandle{};
    ze_kernel_desc_t firstKernelDescription = {ZE_STRUCTURE_TYPE_KERNEL_DESC, nullptr, 0, "FirstKernelName"};

    const auto firstDynMemTraits = CommandT::Captures::DynamicTraits::calculate(firstModuleHandle, &firstKernelDescription, &firstKernelHandle);
    const auto firstRequiredBufferSize = sizeof(CommandT) + firstDynMemTraits.totalDynamicSize;

    auto firstSpace = std::make_unique<char[]>(firstRequiredBufferSize);
    auto firstCommand = new (firstSpace.get()) CommandT(firstDynMemTraits, firstModuleHandle, &firstKernelDescription, &firstKernelHandle);

    // Second captures.
    ze_module_handle_t secondModuleHandle{};
    ze_kernel_handle_t secondKernelHandle{};
    ze_kernel_desc_t secondKernelDescription = {ZE_STRUCTURE_TYPE_KERNEL_DESC, nullptr, 0, "SecondKernelNameWhichIsMuchLonger"};

    const auto secondDynMemTraits = CommandT::Captures::DynamicTraits::calculate(secondModuleHandle, &secondKernelDescription, &secondKernelHandle);
    const auto secondRequiredBufferSize = sizeof(CommandT) + secondDynMemTraits.totalDynamicSize;

    auto secondSpace = std::make_unique<char[]>(secondRequiredBufferSize);
    auto secondCommand = new (secondSpace.get()) CommandT(secondDynMemTraits, secondModuleHandle, &secondKernelDescription, &secondKernelHandle);

    EXPECT_FALSE(firstCommand->captures.assignFrom(secondCommand->captures));
}

TEST(CapturesAssignFrom, GivenTwoCapturesWithTheSameDynMemSizeWhenTryingToAssignThemThenTrueIsReturned) {
    using CommandT = Cal::Rpc::LevelZero::ZeKernelCreateRpcM;

    // First captures.
    ze_module_handle_t firstModuleHandle{};
    ze_kernel_handle_t firstKernelHandle{};
    ze_kernel_desc_t firstKernelDescription = {ZE_STRUCTURE_TYPE_KERNEL_DESC, nullptr, 0, "KernelName01"};

    const auto firstDynMemTraits = CommandT::Captures::DynamicTraits::calculate(firstModuleHandle, &firstKernelDescription, &firstKernelHandle);
    const auto firstRequiredBufferSize = sizeof(CommandT) + firstDynMemTraits.totalDynamicSize;

    auto firstSpace = std::make_unique<char[]>(firstRequiredBufferSize);
    auto firstCommand = new (firstSpace.get()) CommandT(firstDynMemTraits, firstModuleHandle, &firstKernelDescription, &firstKernelHandle);

    firstCommand->copyFromCaller(firstDynMemTraits);
    firstCommand->captures.reassembleNestedStructs();

    // Second captures.
    ze_module_handle_t secondModuleHandle{};
    ze_kernel_handle_t secondKernelHandle{};
    ze_kernel_desc_t secondKernelDescription = {ZE_STRUCTURE_TYPE_KERNEL_DESC, nullptr, 0, "KernelName02"};

    const auto secondDynMemTraits = CommandT::Captures::DynamicTraits::calculate(secondModuleHandle, &secondKernelDescription, &secondKernelHandle);
    const auto secondRequiredBufferSize = sizeof(CommandT) + secondDynMemTraits.totalDynamicSize;

    auto secondSpace = std::make_unique<char[]>(secondRequiredBufferSize);
    auto secondCommand = new (secondSpace.get()) CommandT(secondDynMemTraits, secondModuleHandle, &secondKernelDescription, &secondKernelHandle);

    secondCommand->copyFromCaller(secondDynMemTraits);
    secondCommand->captures.reassembleNestedStructs();

    ASSERT_TRUE(firstCommand->captures.assignFrom(secondCommand->captures));
    ASSERT_NE(firstCommand->captures.desc.pKernelName, secondCommand->captures.desc.pKernelName);
    EXPECT_STREQ(firstCommand->captures.desc.pKernelName, secondCommand->captures.desc.pKernelName);
}

struct MockProvider : public Cal::Service::Provider {
    using Cal::Service::Provider::commandQueueGroups;
    using Cal::Service::Provider::defaultRpcMessageChannelSizeMB;
    using Cal::Service::Provider::defaultSharedVaSizeInGB;
    using Cal::Service::Provider::Provider;
    using Cal::Service::Provider::sharedVaArenaSizeMB;
};

TEST(CopyGroupAssign, whenServiceProviderIsCreatedThenApplyDefaultServiceConfigurationSettings) {
    MockProvider service(nullptr, Cal::Service::ServiceConfig());

    EXPECT_EQ(service.defaultSharedVaSizeInGB, 32);
    EXPECT_EQ(service.defaultRpcMessageChannelSizeMB, 256);
    EXPECT_EQ(service.sharedVaArenaSizeMB, 256);
}

TEST(CopyGroupAssign, givenParsedCommandQueueGroupsWhenOverrideClientsDescsThenAssignProperCopyQueueGroups) {
    MockProvider service(nullptr, Cal::Service::ServiceConfig());

    std::array<ze_command_queue_group_properties_t, 4u> prop{};
    prop[0].flags |= ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE;
    prop[0].numQueues = 1u;
    prop[0].stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    prop[1].flags |= (ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE | ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY);
    prop[1].numQueues = 3u;
    prop[1].stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    prop[2].flags |= ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY;
    prop[2].numQueues = 56u;
    prop[2].stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    prop[3].flags |= ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY;
    prop[3].numQueues = 1u;
    prop[3].stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    uint32_t size = 4u;

    service.parseCommandQueueGroups(&size, prop.data());

    EXPECT_EQ(service.commandQueueGroups.linkedCopyGroupIndex, 2u);
    EXPECT_EQ(service.commandQueueGroups.copyGroupIndex, 3u);
    EXPECT_EQ(service.commandQueueGroups.numLinkedCopyEngines, 56u);
    EXPECT_EQ(service.commandQueueGroups.selector.load(), 0u);

    service.commandQueueGroups.computeRoundRobinEnabled = service.commandQueueGroups.copyRoundRobinEnabled = true;

    std::string path("path");
    Cal::Ipc::GlobalShmemAllocators allocator(path);
    Cal::Service::ClientContext ctx(allocator, false);
    ze_command_queue_desc_t desc{};
    desc.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    desc.index = 0u;
    desc.ordinal = 1u;
    {
        service.overrideCommandQueueDesc(&desc, ctx);

        EXPECT_EQ(service.commandQueueGroups.selector.load(), 0u);
        EXPECT_EQ(ctx.getCopyCommandQueueGroupIndex(), std::numeric_limits<uint32_t>::max());
        EXPECT_EQ(desc.ordinal, 1u);
        EXPECT_EQ(desc.index, 0u);
    }
    {
        desc.ordinal = 2u;
        desc.index = 3u;
        service.overrideCommandQueueDesc(&desc, ctx);

        EXPECT_EQ(service.commandQueueGroups.selector.load(), 1u);
        EXPECT_EQ(ctx.getCopyCommandQueueGroupIndex(), 0u);
        EXPECT_EQ(desc.ordinal, 3u);
        EXPECT_EQ(desc.index, 0u);
    }
    {
        desc.ordinal = 2u;
        desc.index = 5u;
        service.overrideCommandQueueDesc(&desc, ctx);

        EXPECT_EQ(service.commandQueueGroups.selector.load(), 1u);
        EXPECT_EQ(ctx.getCopyCommandQueueGroupIndex(), 0u);
        EXPECT_EQ(desc.ordinal, 3u);
        EXPECT_EQ(desc.index, 0u);
    }
    {
        ze_command_list_desc_t desc{};
        desc.stype = ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC;
        desc.commandQueueGroupOrdinal = 2u;
        service.overrideCommandListDesc(&desc, ctx);

        EXPECT_EQ(service.commandQueueGroups.selector.load(), 1u);
        EXPECT_EQ(ctx.getCopyCommandQueueGroupIndex(), 0u);
        EXPECT_EQ(desc.commandQueueGroupOrdinal, 3u);
    }
    {
        Cal::Service::ClientContext ctx2(allocator, false);
        desc.ordinal = 3u;
        desc.index = 1u;
        service.overrideCommandQueueDesc(&desc, ctx2);

        EXPECT_EQ(service.commandQueueGroups.selector.load(), 2u);
        EXPECT_EQ(ctx.getCopyCommandQueueGroupIndex(), 0u);
        EXPECT_EQ(ctx2.getCopyCommandQueueGroupIndex(), 1u);
        EXPECT_EQ(desc.ordinal, 2u);
        EXPECT_EQ(desc.index, 0u);
    }
}

struct MockModuleCache : public Cal::Service::Provider::ModuleCache {
    using Cal::Service::Provider::ModuleCache::cache;
};
TEST(L0Service, givenServiceWhenStoreNativeBinaryThenBinaryIsStoredWithModuleDesc) {
    MockModuleCache cache;
    EXPECT_TRUE(cache.cache.empty());

    ze_context_handle_t hContext = reinterpret_cast<ze_context_handle_t>(0x1234);
    ze_device_handle_t hDevice = reinterpret_cast<ze_device_handle_t>(0x5678);
    uint8_t binary[] = {1, 2, 3, 4, 5, 0, 6, 7, 8, 9};
    constexpr size_t nativeSize = 5;
    auto native = new uint8_t[nativeSize];
    for (uint32_t i = 0u; i < nativeSize; ++i) {
        native[i] = 10 + i;
    }
    char buildOptions[] = {"--build=option"};
    uint32_t ids[] = {1, 5, 9};
    uint64_t values[] = {0x13, 0x45, 0x89};
    uint64_t *pValues[] = {values, values + 1, values + 2};
    ze_module_constants_t constants;
    constants.numConstants = 3u;
    constants.pConstantIds = ids;
    constants.pConstantValues = reinterpret_cast<const void **>(&pValues);
    ze_module_desc_t desc = {};
    desc.stype = ZE_STRUCTURE_TYPE_MODULE_DESC;
    desc.format = ZE_MODULE_FORMAT_IL_SPIRV;
    desc.inputSize = sizeof(binary);
    desc.pBuildFlags = buildOptions;
    desc.pInputModule = binary;
    desc.pConstants = &constants;

    cache.store(hContext, hDevice, &desc, nativeSize, native);
    EXPECT_EQ(cache.cache.size(), 1u);
    EXPECT_EQ(cache.cache[0].hContext, hContext);
    EXPECT_EQ(cache.cache[0].hDevice, hDevice);
    EXPECT_EQ(cache.cache[0].format, desc.format);
    EXPECT_EQ(cache.cache[0].inputSize, desc.inputSize);
    EXPECT_EQ(cache.cache[0].nativeSize, nativeSize);
    EXPECT_EQ(cache.cache[0].pNativeBinary, native);
    EXPECT_EQ(cache.cache[0].binaryHash, std::hash<std::string>{}(std::string(reinterpret_cast<const char *>(desc.pInputModule), desc.inputSize)));
    EXPECT_EQ(cache.cache[0].buildOptionsHash, std::hash<std::string>{}(std::string(reinterpret_cast<const char *>(desc.pBuildFlags))));
    EXPECT_EQ(cache.cache[0].constants.numConstants, desc.pConstants->numConstants);
    for (uint32_t i = 0; i < desc.pConstants->numConstants; ++i) {
        EXPECT_EQ(cache.cache[0].constants.pConstantIds[i], desc.pConstants->pConstantIds[i]);
        EXPECT_EQ(reinterpret_cast<uint64_t *>(cache.cache[0].constants.pConstantValues)[i], *static_cast<const uint64_t *>(desc.pConstants->pConstantValues[i]));
    }

    {
        auto ret = cache.find(hContext, hDevice, &desc);
        EXPECT_TRUE(ret.has_value());
    }
    {
        ze_context_handle_t hContext = reinterpret_cast<ze_context_handle_t>(0x11223344);
        auto ret = cache.find(hContext, hDevice, &desc);
        EXPECT_TRUE(ret.has_value());
    }
    {
        ze_device_handle_t hDevice = reinterpret_cast<ze_device_handle_t>(0x55667788);
        auto ret = cache.find(hContext, hDevice, &desc);
        EXPECT_FALSE(ret.has_value());
    }
    {
        values[1] = 0x126;
        auto ret = cache.find(hContext, hDevice, &desc);
        EXPECT_FALSE(ret.has_value());
        values[1] = 0x45;
    }
    {
        binary[6] = 1;
        binary[7] = 2;
        binary[8] = 3;
        binary[9] = 4;
        auto ret = cache.find(hContext, hDevice, &desc);
        EXPECT_FALSE(ret.has_value());
        binary[6] = 6;
        binary[7] = 7;
        binary[8] = 8;
        binary[9] = 9;
    }
    {
        desc.pBuildFlags = nullptr;
        auto ret = cache.find(hContext, hDevice, &desc);
        EXPECT_FALSE(ret.has_value());
        auto native2 = new uint8_t[nativeSize];
        for (uint32_t i = 0u; i < nativeSize; ++i) {
            native2[i] = native[i];
        }
        cache.store(hContext, hDevice, &desc, nativeSize, native2);

        ret = cache.find(hContext, hDevice, &desc);
        EXPECT_TRUE(ret.has_value());
        EXPECT_EQ(cache.cache.size(), 2u);
    }
}

} // namespace Cal::Rpc::LevelZero

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    auto options = parseArguments(argc, argv);

    if (int result = enableSignals(options.enableAlarm, options.enableSegv, options.enableAbrt); result != 0) {
        return result;
    }

    if (options.useCustomListener) {
        auto &listeners = ::testing::UnitTest::GetInstance()->listeners();
        auto defaultListener = listeners.default_result_printer();
        auto customEventListener = new CCustomEventListener(defaultListener);
        listeners.Release(defaultListener);
        listeners.Append(customEventListener);
    }

    return RUN_ALL_TESTS();
}
