/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "service/level_zero/ongoing_hostptr_copies_manager.h"

#include <unordered_map>

namespace Cal::Mocks {

class MockOngoingHostptrCopiesManager : public Cal::Service::LevelZero::OngoingHostptrCopiesManager {
  public:
    using OngoingHostptrCopiesManager::ongoingOperations;
    using OngoingHostptrCopiesManager::operationsForResubmit;

    ~MockOngoingHostptrCopiesManager() override = default;

    ze_result_t queryEventStatus(ze_event_handle_t event) override {
        ++queryEventStatusCallsCount;

        if (queryEventStatusToReturn.count(event) == 0u) {
            return ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT;
        }

        return queryEventStatusToReturn[event];
    }

    size_t queryEventStatusCallsCount{0u};
    std::unordered_map<ze_event_handle_t, ze_result_t> queryEventStatusToReturn{};
};

} // namespace Cal::Mocks
