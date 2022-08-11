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
#include <memory>

namespace Cal::Rpc::LevelZero {

TEST(ReassemblationTest, GivenCapturesWithNestedStructFieldsWhenCopyingAndReassemblingTheStructureThenStructCapturesFieldsPointToDynMem) {
    // 0. Prepare arguments, which need to be copied.
    constexpr static size_t constantsCount = 3;
    std::array<uint32_t, constantsCount> constantsIds = {1, 5, 21};

    uint64_t firstConstant = 121;
    uint64_t secondConstant = 77;
    uint64_t thirdConstant = 212;
    std::array<const void *, constantsCount> constantValues = {&firstConstant, &secondConstant, &secondConstant};

    ze_module_constants_t moduleConstants = {
        constantsCount,
        constantsIds.data(),
        constantValues.data()};

    constexpr static const char *skipWarningAboutModuleRecompilationFlag = "-Wno-recompiled-from-ir";

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
