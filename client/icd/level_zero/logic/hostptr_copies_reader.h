/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "boost/container/flat_map.hpp"
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

namespace Cal::Client::Icd::LevelZero::Logic {

class HostptrCopiesReader {
  public:
    ze_result_t readMemory(Cal::Rpc::ChannelClient &channel, Cal::Ipc::ShmemImporter &shmemImporter);
    void addToMap(void *usmPtr, uintptr_t hostPtr);

  protected:
    mockable std::vector<Cal::Rpc::TransferDesc> getHostptrCopiesToUpdate(Cal::Rpc::ChannelClient &channel);
    mockable bool copyMappedMemory(Cal::Ipc::ShmemImporter &shmemImporter, const std::vector<Cal::Rpc::TransferDesc> &transferDescs);
    boost::container::flat_map<const void *, uintptr_t> usmToHostAddressMap{};
};

} // namespace Cal::Client::Icd::LevelZero::Logic
