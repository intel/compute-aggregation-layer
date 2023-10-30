/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/icd/icd_global_state.h"
#include "client/icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/control_messages.h"
#include "shared/log.h"

namespace Cal::Icd::LevelZero::Ipc {

template <typename IpcHandleT>
ze_result_t translateIpcHandles(const char *functionName, uint32_t numIpcHandles, IpcHandleT *pIpcHandles) {
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &connection = globalL0Platform->getConnection();
    auto lock = connection.lock();

    static constexpr auto maxHandlesCount = Cal::Messages::ReqTransferFd::maxFdsCount;
    if (numIpcHandles > maxHandlesCount) {
        log<Verbosity::error>("%s: number of IPC handles to translate exceeds the maximum available count!", functionName, maxHandlesCount);
        return ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY;
    }

    Cal::Messages::ReqTransferFd reqTransferFd{static_cast<uint16_t>(numIpcHandles)};
    for (auto i = 0u; i < numIpcHandles; ++i) {
        std::memcpy(&reqTransferFd.remoteFds[i], pIpcHandles[i].data, sizeof(reqTransferFd.remoteFds[i]));
    }

    if (false == connection.send(reqTransferFd)) {
        log<Verbosity::error>("%s: Could not request transfer of file descriptors!", functionName);
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::array<int, maxHandlesCount> localFileDescriptors{};
    if (false == connection.receiveFds(localFileDescriptors.data(), numIpcHandles)) {
        log<Verbosity::error>("%s: Could not receive file descriptors from service!", functionName);
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    for (auto i = 0u; i < numIpcHandles; ++i) {
        std::memcpy(pIpcHandles[i].data, &localFileDescriptors[i], sizeof(localFileDescriptors[i]));
    }

    return ZE_RESULT_SUCCESS;
}

template <typename IpcHandleT>
ze_result_t reverseTranslateIpcHandles(const char *functionName, uint32_t numIpcHandles, IpcHandleT *pIpcHandles) {
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &connection = globalL0Platform->getConnection();
    auto lock = connection.lock();

    static constexpr auto maxHandlesCount = Cal::Messages::ReqReverseTransferFd::maxFdsCount;
    if (numIpcHandles > maxHandlesCount) {
        log<Verbosity::error>("%s: number of IPC handles to translate exceeds the maximum available count!", functionName, maxHandlesCount);
        return ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY;
    }

    Cal::Messages::ReqReverseTransferFd reqReverseTransferFd{static_cast<uint16_t>(numIpcHandles)};
    if (false == connection.send(reqReverseTransferFd)) {
        log<Verbosity::error>("%s: Could not request reverse transfer of file descriptor!", functionName);
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::array<int, maxHandlesCount> localFileDescriptors{};
    for (auto i = 0u; i < numIpcHandles; ++i) {
        std::memcpy(&localFileDescriptors[i], pIpcHandles[i].data, sizeof(localFileDescriptors[i]));
    }

    if (false == connection.sendFds(localFileDescriptors.data(), numIpcHandles)) {
        log<Verbosity::error>("%s: Could not send file descriptor to service for reverse transfer!", functionName);
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    Cal::Messages::RespReverseTransferFd respReverseTransferFd{};
    if (false == connection.receive(respReverseTransferFd) || respReverseTransferFd.isInvalid()) {
        log<Verbosity::error>("%s: Could not receive remote file descriptor from service during reverse transfer!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    for (auto i = 0u; i < numIpcHandles; ++i) {
        std::memcpy(pIpcHandles[i].data, &respReverseTransferFd.remoteFds[i], sizeof(respReverseTransferFd.remoteFds[i]));
    }

    return ZE_RESULT_SUCCESS;
}

} // namespace Cal::Icd::LevelZero::Ipc
