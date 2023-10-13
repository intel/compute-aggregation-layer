/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "service/level_zero/ongoing_hostptr_copies_manager.h"

#include "generated_service_level_zero.h"
#include "service/level_zero/artificial_events_manager.h"
#include "shared/log.h"

#include <algorithm>

namespace Cal::Service::LevelZero {

void OngoingHostptrCopiesManager::registerCopyOperation(ze_command_list_handle_t commandList,
                                                        ze_event_handle_t associatedEvent,
                                                        void *destination,
                                                        size_t destinationSize,
                                                        bool canBeResubmitted) {
    auto &newOperation = ongoingOperations.emplace_back();

    newOperation.commandList = commandList;
    newOperation.associatedEvent = associatedEvent;
    newOperation.destination = destination;
    newOperation.destinationSize = destinationSize;
    newOperation.isFinished = false;
    newOperation.canBeResubmitted = canBeResubmitted;
}

ze_result_t OngoingHostptrCopiesManager::queryEventStatus(ze_event_handle_t event) {
    return Cal::Service::Apis::LevelZero::Standard::zeEventQueryStatus(event);
}

void OngoingHostptrCopiesManager::resubmitOperationsOfCommandList(ze_command_list_handle_t commandList) {
    if (operationsForResubmit.count(commandList) == 0u) {
        return;
    }

    auto &operationsOfCommandList = operationsForResubmit[commandList];
    for (auto &operation : operationsOfCommandList) {
        operation.isFinished = false;
        ongoingOperations.push_back(operation);
    }

    operationsOfCommandList.clear();
}

void OngoingHostptrCopiesManager::freeOperationsOfCommandList(ze_command_list_handle_t commandList, ArtificialEventsManager &eventsManager) {
    bool needsToCallRemove = false;

    for (const auto &operation : ongoingOperations) {
        if (operation.commandList == commandList) {
            eventsManager.returnObtainedEvent(operation.associatedEvent);
            needsToCallRemove = true;
        }
    }

    if (needsToCallRemove) {
        const auto belongsToCommandList = [commandList](auto &operation) { return operation.commandList == commandList; };
        const auto firstToEraseIt = std::remove_if(ongoingOperations.begin(), ongoingOperations.end(), belongsToCommandList);
        ongoingOperations.erase(firstToEraseIt, ongoingOperations.end());
    }

    if (operationsForResubmit.count(commandList) != 0u) {
        for (const auto &operation : operationsForResubmit[commandList]) {
            eventsManager.returnObtainedEvent(operation.associatedEvent);
        }

        operationsForResubmit.erase(commandList);
    }
}

void OngoingHostptrCopiesManager::acquireFinishedCopies(ArtificialEventsManager &eventsManager, std::vector<Cal::Utils::AddressRange> &copies) {
    for (auto &operation : ongoingOperations) {
        if (!operation.isFinished) {
            auto status = queryEventStatus(operation.associatedEvent);
            if (status == ZE_RESULT_SUCCESS) {
                operation.isFinished = true;
            } else {
                continue;
            }
        }

        if (operation.canBeResubmitted) {
            eventsManager.resetObtainedEvent(operation.associatedEvent);
            operationsForResubmit[operation.commandList].push_back(operation);
        } else {
            eventsManager.returnObtainedEvent(operation.associatedEvent);
        }

        copies.push_back({operation.destination, operation.destinationSize});
    }

    const auto firstToEraseIt = std::remove_if(ongoingOperations.begin(), ongoingOperations.end(), [](const auto &other) { return other.isFinished; });
    ongoingOperations.erase(firstToEraseIt, ongoingOperations.end());

    return;
}

} // namespace Cal::Service::LevelZero
