/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/log.h"

#include <mutex>

namespace Cal {

namespace Mocks {

class LogCaptureContext : public Cal::Utils::LogSstream {
  public:
    LogCaptureContext() {
        prevLogger = Cal::Utils::globalLog;
        Cal::Utils::globalLog = this;
    }
    ~LogCaptureContext() override {
        Cal::Utils::globalLog = prevLogger;
    }

  protected:
    Cal::Utils::Log *prevLogger = nullptr;
};

} // namespace Mocks

} // namespace Cal