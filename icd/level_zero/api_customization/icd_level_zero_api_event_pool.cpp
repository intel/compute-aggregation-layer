/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/log.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeEventPoolGetIpcHandle(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t *phIpc) {
    const auto rpcCommandResult = zeEventPoolGetIpcHandleRpcHelper(hEventPool, phIpc);
    if (rpcCommandResult != ZE_RESULT_SUCCESS) {
        return rpcCommandResult;
    }

    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &connection = globalL0Platform->getConnection();
    auto lock = connection.lock();

    int remoteFileDescriptor{};
    std::memcpy(&remoteFileDescriptor, phIpc->data, sizeof(remoteFileDescriptor));

    Cal::Messages::ReqTransferFd reqTransferFd{remoteFileDescriptor};
    if (false == connection.send(reqTransferFd)) {
        log<Verbosity::error>("zeEventPoolGetIpcHandle: Could not request transfer of file descriptor!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    int localFileDescriptor = 0;
    if (false == connection.receiveFd(localFileDescriptor)) {
        log<Verbosity::error>("zeEventPoolGetIpcHandle: Could not receive file descriptor from service!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::memcpy(phIpc->data, &localFileDescriptor, sizeof(localFileDescriptor));
    return ZE_RESULT_SUCCESS;
}

ze_result_t zeEventPoolOpenIpcHandle(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t *phEventPool) {
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &connection = globalL0Platform->getConnection();
    auto lock = connection.lock();

    int localFileDescriptor{};
    std::memcpy(&localFileDescriptor, hIpc.data, sizeof(localFileDescriptor));

    Cal::Messages::ReqReverseTransferFd reqReverseTransferFd{};
    if (false == connection.send(reqReverseTransferFd)) {
        log<Verbosity::error>("zeEventPoolOpenIpcHandle: Could not request reverse transfer of file descriptor!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    if (false == connection.sendFd(localFileDescriptor)) {
        log<Verbosity::error>("zeEventPoolOpenIpcHandle: Could not send file descriptor to service for reverse transfer!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    Cal::Messages::RespReverseTransferFd respReverseTransferFd{-1};
    if (false == connection.receive(respReverseTransferFd) || respReverseTransferFd.isInvalid()) {
        log<Verbosity::error>("zeEventPoolOpenIpcHandle: Could not receive remote file descriptor from service during reverse transfer!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::memcpy(hIpc.data, &respReverseTransferFd.remoteFd, sizeof(respReverseTransferFd.remoteFd));
    return zeEventPoolOpenIpcHandleRpcHelper(hContext, hIpc, phEventPool);
}

} // namespace Cal::Icd::LevelZero
