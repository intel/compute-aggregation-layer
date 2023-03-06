/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"

#include <unordered_map>

namespace Cal::Service::LevelZero {

class CommandListToContextTracker {
  public:
    ze_context_handle_t getAssociatedContext(ze_command_list_handle_t commandList) const;

    void registerCommandListToContextMapping(ze_command_list_handle_t commandList, ze_context_handle_t context);
    void deregisterCommandListMapping(ze_command_list_handle_t commandList);

  private:
    std::unordered_map<ze_command_list_handle_t, ze_context_handle_t> commandListToContextMapping{};
};

} // namespace Cal::Service::LevelZero
