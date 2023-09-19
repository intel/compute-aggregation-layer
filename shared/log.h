/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#pragma GCC diagnostic ignored "-Wformat-security"

#include "include/cal.h"
#include "shared/callstack.h"
#include "shared/utils.h"

#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

namespace Cal {

namespace Utils {

class Log {
  public:
    enum Verbosity : int {
        performance = -1,
        silent = 0,
        critical = 1,
        error = 2,
        info = 3,
        debug = 4,
        bloat = 5,
        unknown = 6
    };

    virtual ~Log() = default;

    static constexpr const char *to_cstring(Verbosity v) {
        switch (v) {
        default:
            return "";
        case Verbosity::silent:
            return "silent";
        case Verbosity::critical:
            return "critical";
        case Verbosity::error:
            return "error";
        case Verbosity::info:
            return "info";
        case Verbosity::debug:
            return "debug";
        case Verbosity::bloat:
            return "bloat";
        case Verbosity::performance:
            return "performance";
        }
    }

    static constexpr const char *to_cstring_tag(Verbosity v) {
        switch (v) {
        default:
            return "";
        case Verbosity::silent:
            return "";
        case Verbosity::critical:
            return "[!CRITICAL!]";
        case Verbosity::error:
            return "[  ERROR   ]";
        case Verbosity::info:
            return "[   info   ]";
        case Verbosity::debug:
            return "[  debug   ]";
        case Verbosity::bloat:
            return "[  bloat   ]";
        case Verbosity::performance:
            return "[   perf   ]";
        }
    }

    static constexpr const char *to_cstring_logger() {
#ifdef CAL_LOGGER_NAME
        return "[" NAME_TO_STR(CAL_LOGGER_NAME) "]";
#else
        return "[-]";
#endif
    }

    const char *to_cstring_pid() {
        static std::string pid = std::invoke([]() {
            std::ostringstream oss;
            oss << "[";
            oss << std::setfill(' ') << std::setw(8) << getpid();
            oss << "]";
            return oss.str();
        });

        return pid.c_str();
    }

    template <Verbosity V, typename... Args>
    int add(bool useLoggerName, bool appendPID, bool addCallStackDump, const char *formatString, Args &&...args) {
        isEmpty = false;
        auto len = snprintf(nullptr, 0, formatString, std::forward<Args>(args)...);
        if (len <= 0) {
            return len;
        }
        std::vector<char> buff(len + 1);
        snprintf(buff.data(), buff.size(), formatString, std::forward<Args>(args)...);
        if constexpr (CAL_SUPPORT_CALLSTACK_DUMPING) {
            if (addCallStackDump) {
                std::string callStackInfo = Cal::Utils::concatenate(Cal::Utils::getCallStack(), "\n");
                *buff.rbegin() = ' ';
                std::string callStackInfoHeader = "- call stack dump :\n";
                buff.insert(buff.end(), callStackInfoHeader.begin(), callStackInfoHeader.end());
                buff.insert(buff.end(), callStackInfo.begin(), callStackInfo.end());
                buff.push_back('\0');
            }
        }
        return log(useLoggerName, appendPID, V, buff.data());
    }

    bool empty() const {
        return isEmpty;
    }

  protected:
    virtual int log(bool useLoggerName, bool appendPID, Verbosity verbosity, const char *logMessage) = 0;
    bool isEmpty = true;
};

class LogStdout : public Log {
  protected:
    int log(bool useLoggerName, bool appendPID, Verbosity verbosity, const char *logMessage) override {
        int ret = 0;
        printf("%s%s%s : %s\n", useLoggerName ? to_cstring_logger() : "", appendPID ? to_cstring_pid() : "", to_cstring_tag(verbosity), logMessage);
        fflush(stdout);
        return ret;
    }
};

class LogSstream : public Log {
  public:
    void clear() {
        buff.clear();
    }
    std::string str() const {
        return buff.str();
    }

  protected:
    int log(bool useLoggerName, bool appendPID, Verbosity verbosity, const char *logMessage) override {
        auto prevPos = buff.tellp();
        if (useLoggerName) {
            buff << to_cstring_logger();
        }
        if (appendPID) {
            buff << to_cstring_pid();
        }
        buff << to_cstring_tag(verbosity) << " : " << logMessage << "\n";
        fflush(stdout);
        return buff.tellp() - prevPos;
    }

    std::stringstream buff;
};

inline Cal::Utils::Log *globalLog = new Cal::Utils::LogStdout();

} // namespace Utils

} // namespace Cal

using Verbosity = Cal::Utils::Log::Verbosity;

template <Verbosity V, typename... Args>
int log(const char *formatString, Args &&...args);

namespace Cal {

namespace Utils {

#if defined(NDEBUG) && !defined(FULL_VERBOSITY_IN_RELEASE_BUILD)
static constexpr Verbosity maxStaticVebosity = Verbosity::info;
#else
#if defined(ENABLE_BLOATED_VERBOSITY)
static constexpr Verbosity maxStaticVebosity = Verbosity::bloat;
#else
static constexpr Verbosity maxStaticVebosity = Verbosity::debug;
#endif
#endif

#ifdef PERFORMANCE_DEBUG
static constexpr Verbosity minStaticVebosity = Verbosity::performance;
static constexpr bool enablePerformanceLogs = true;
#else
static constexpr Verbosity minStaticVebosity = Verbosity::silent;
static constexpr bool enablePerformanceLogs = false;
#endif

inline Verbosity minDynamicVerbosity = Verbosity::silent;
inline Verbosity maxDynamicVerbosity = Verbosity::error;
inline Verbosity maxDynamicCallStackVerbosity = Verbosity::silent;
inline bool useLoggerName = false;
inline bool appendPID = false;

inline std::string getListOfAllExistingVerbosityLevels() {
    std::string existing;
    for (int j = Verbosity::performance; j <= Verbosity::bloat; ++j) {
        if (existing.empty() == false) {
            existing += ", ";
        }
        existing += Cal::Utils::Log::to_cstring(static_cast<Verbosity>(j));
    }
    return existing;
}

inline std::string getListOfAllAvailableVerbosityLevels() {
    std::string available;
    for (int j = minStaticVebosity; j <= maxStaticVebosity; ++j) {
        if (available.empty() == false) {
            available += ", ";
        }
        available += Cal::Utils::Log::to_cstring(static_cast<Verbosity>(j));
    }
    return available;
}

inline void initMaxDynamicVerbosity(Verbosity max) {
    maxDynamicVerbosity = max;
    if (max > maxStaticVebosity) {
        auto available = getListOfAllAvailableVerbosityLevels();
        log<Verbosity::error>("Requested verbosity level : %s is higher than maximum available : %s (chosen statically at service build time - choose one of : %s)",
                              Cal::Utils::Log::to_cstring(max), Cal::Utils::Log::to_cstring(maxStaticVebosity), available.c_str());
    }
}

inline void initMaxDynamicCallStackDumpingVerbosity(Verbosity max) {
    if constexpr (0 == CAL_SUPPORT_CALLSTACK_DUMPING) {
        log<Verbosity::error>("Requested callstack dumping verbosity level : %s, but build type does not support call stack dumping");
        return;
    }
    maxDynamicCallStackVerbosity = max;
    if (max > maxStaticVebosity) {
        auto available = getListOfAllAvailableVerbosityLevels();
        log<Verbosity::error>("Requested callstack dumping verbosity level : %s is higher than maximum available : %s (chosen statically at service build time - choose one of : %s)",
                              Cal::Utils::Log::to_cstring(max), Cal::Utils::Log::to_cstring(maxStaticVebosity), available.c_str());
    }
}

inline void initBenchmarkingMode(bool value) {
    if (value) {
        minDynamicVerbosity = Verbosity::performance;
        if (minStaticVebosity > Verbosity::performance) {
            log<Verbosity::error>("Can't enable benchmarking mode because service was built without PERFORMANCE_DEBUG switch)");
        }
    } else {
        minDynamicVerbosity = Verbosity::silent;
    }
}

inline Verbosity parseVerbosity(const char *strV) {
    for (int i = Verbosity::performance; i <= Verbosity::bloat; ++i) {
        Verbosity v = static_cast<Verbosity>(i);
        if (0 == strcmp(strV, Cal::Utils::Log::to_cstring(v))) {
            return v;
        }
    }
    return Verbosity::unknown;
}

inline void initDynamicVerbosity() {
    auto requestedBenchmarkingMode = getCalEnvFlag(calBenchmarkEnvName);
    initBenchmarkingMode(requestedBenchmarkingMode);

    auto requestedVerbosityStr = getCalEnv(calVerbosityEnvName);
    if (requestedVerbosityStr) {
        auto requestedVerbosity = parseVerbosity(requestedVerbosityStr);
        if (Verbosity::unknown != requestedVerbosity) {
            initMaxDynamicVerbosity(requestedVerbosity);
            log<Verbosity::info>("Initializing verbosity level to %s based on %s environment variable", requestedVerbosityStr, calVerbosityEnvName.data());
        } else {
            std::string existing = getListOfAllExistingVerbosityLevels();
            log<Verbosity::error>("Ignoring unkown verbosity level %s from %s environment variable (expected one of (case sensitive) : %s)", requestedVerbosityStr, calVerbosityEnvName.data(), existing.c_str());
        }
    }

    auto requestedCallStackVerbosityStr = getCalEnv(calVerbosityCallStackEnvName);
    if (requestedCallStackVerbosityStr) {
        auto requestedCallStackVerbosity = parseVerbosity(requestedCallStackVerbosityStr);
        if (Verbosity::unknown != requestedCallStackVerbosity) {
            initMaxDynamicCallStackDumpingVerbosity(requestedCallStackVerbosity);
            log<Verbosity::info>("Initializing verbosity level of callstack dumping to %s based on %s environment variable", requestedCallStackVerbosityStr, calVerbosityCallStackEnvName.data());
        } else {
            std::string existing = getListOfAllExistingVerbosityLevels();
            log<Verbosity::error>("Ignoring unkown callstack dumping verbosity level %s from %s environment variable (expected one of (case sensitive) : %s)", requestedCallStackVerbosityStr, calVerbosityCallStackEnvName.data(), existing.c_str());
        }
    }

    useLoggerName = getCalEnvFlag(calUseLoggerNameEnvName);
    appendPID = getCalEnvFlag(calAppendPIDEnvName);

    return;
}

} // namespace Utils

} // namespace Cal

template <Verbosity V, typename... Args>
int log(const char *formatString, Args &&...args) {
    if constexpr (V < Cal::Utils::minStaticVebosity) {
        return 0;
    }

    if constexpr (V > Cal::Utils::maxStaticVebosity) {
        return 0;
    }

    if (V < Cal::Utils::minDynamicVerbosity) {
        return 0;
    }

    if (V > Cal::Utils::maxDynamicVerbosity) {
        return 0;
    }

    bool addCallStackDump = false;
    if constexpr (CAL_SUPPORT_CALLSTACK_DUMPING) {
        if (V <= Cal::Utils::maxDynamicCallStackVerbosity) {
            addCallStackDump = true;
        }
    }

    return Cal::Utils::globalLog->add<V>(Cal::Utils::useLoggerName, Cal::Utils::appendPID, addCallStackDump, formatString, std::forward<Args>(args)...);
}
