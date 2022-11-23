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

    int fileDescriptor{};
    std::memcpy(&fileDescriptor, phIpc->data, sizeof(fileDescriptor));

    Cal::Messages::ReqTransferFd reqTransferFd{fileDescriptor};
    if (false == connection.send(reqTransferFd)) {
        log<Verbosity::error>("zeEventPoolGetIpcHandle: Could not request transfer of file descriptor!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    fileDescriptor = 0;
    if (false == connection.receiveFd(fileDescriptor)) {
        log<Verbosity::error>("zeEventPoolGetIpcHandle: Could not receive file descriptor from service!");
        return ZE_RESULT_ERROR_DEVICE_LOST;
    }

    std::memcpy(phIpc->data, &fileDescriptor, sizeof(fileDescriptor));
    return ZE_RESULT_SUCCESS;
}

} // namespace Cal::Icd::LevelZero
