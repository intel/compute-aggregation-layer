/*
 * Copyright (C) 2022-2024 Intel Corporation
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

class UnexpectedLogException : public std::runtime_error {
  public:
    using runtime_error::runtime_error;
};

class DisallowLogs : public LogCaptureContext {
  public:
    int log(bool appendTimestamp, bool useLoggerName, bool appendPID, Verbosity verbosity, const char *logMessage) override {
        Cal::Utils::LogSstream::log(appendTimestamp, useLoggerName, appendPID, verbosity, logMessage);
        auto log = this->str();
        this->clear();
        throw UnexpectedLogException("Unexpected Log : " + log);
    }
};

} // namespace Mocks

} // namespace Cal