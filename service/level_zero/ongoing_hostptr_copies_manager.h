/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "shared/utils.h"

#include <cstddef>
#include <unordered_map>
#include <vector>

namespace Cal::Service::LevelZero {

class ArtificialEventsManager;

class OngoingHostptrCopiesManager {
  public:
    struct OngoingHostptrCopy {
        void *destination{};
        size_t destinationSize{};
    };

    struct InternalOngoingHostptrCopy : public OngoingHostptrCopy {
        ze_command_list_handle_t commandList{};
        ze_event_handle_t associatedEvent{};
        bool isFinished{false};
        bool canBeResubmitted{true};
    };

    mockable ~OngoingHostptrCopiesManager() = default;

    void registerCopyOperation(ze_command_list_handle_t commandList, ze_event_handle_t associatedEvent, void *destination, size_t destinationSize, bool canBeResubmitted);
    void freeOperationsOfCommandList(ze_command_list_handle_t commandList, ArtificialEventsManager &eventsManager);
    void resubmitOperationsOfCommandList(ze_command_list_handle_t commandList);
    void acquireFinishedCopies(ArtificialEventsManager &eventsManager, std::vector<Cal::Utils::AddressRange> &copies);

  protected:
    mockable ze_result_t queryEventStatus(ze_event_handle_t event);

    std::vector<InternalOngoingHostptrCopy> ongoingOperations{};
    std::unordered_map<ze_command_list_handle_t, std::vector<InternalOngoingHostptrCopy>> operationsForResubmit{};
};

} // namespace Cal::Service::LevelZero
