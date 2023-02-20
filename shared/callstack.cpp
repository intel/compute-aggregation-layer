/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/callstack.h"

#include <execinfo.h>

namespace Cal::Utils {

std::vector<std::string> getCallStack() {
    if constexpr (CAL_SUPPORT_CALLSTACK_DUMPING) {
        constexpr size_t maxBacktraceDepth = 1024;
        void *backtracePtrs[maxBacktraceDepth];
        size_t backtraceDepth = backtrace(backtracePtrs, maxBacktraceDepth);
        char **backtraceStrings = backtrace_symbols(backtracePtrs, backtraceDepth);
        if (nullptr == backtraceStrings) {
            return {};
        }
        std::vector<std::string> ret{backtraceStrings, backtraceStrings + backtraceDepth};
        free(backtraceStrings);
        return ret;
    } else {
        return {};
    }
}

} // namespace Cal::Utils
