/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "shared/shmem_transfer_desc.h"

#include <cstddef>
#include <vector>

namespace Cal::Ipc {
class ShmemImporter;
} // namespace Cal::Ipc

namespace Cal::Rpc {
class ChannelClient;
} // namespace Cal::Rpc

namespace Cal::Icd::LevelZero::Logic {

class HostptrCopiesReader {
  public:
    ze_result_t readMemory(Cal::Rpc::ChannelClient &channel, Cal::Ipc::ShmemImporter &shmemImporter);

  protected:
    mockable std::vector<Cal::Rpc::MemChunk> getHostptrCopiesToUpdate(Cal::Rpc::ChannelClient &channel);
    mockable bool copyMappedMemory(Cal::Ipc::ShmemImporter &shmemImporter, const std::vector<Cal::Rpc::ShmemTransferDesc> &transferDescs);
    mockable ze_result_t performNonlockingTransferDescsRequest(Cal::Rpc::ChannelClient &channel,
                                                               uint32_t chunksCount,
                                                               const Cal::Rpc::MemChunk *chunks,
                                                               uint32_t *outDescsCount,
                                                               Cal::Rpc::ShmemTransferDesc *outDescs);
};

} // namespace Cal::Icd::LevelZero::Logic
