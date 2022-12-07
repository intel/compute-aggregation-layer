/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_rpc_messages_level_zero.h"
#include "gtest/gtest.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <memory>

namespace Cal::Rpc::LevelZero {

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

} // namespace Cal::Rpc::LevelZero

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
