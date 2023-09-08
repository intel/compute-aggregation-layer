/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <cstring>

struct CLIOptions {
    bool useCustomListener{true};
    bool enableAlarm{true};
    bool enableSegv{true};
    bool enableAbrt{true};
};

CLIOptions parseArguments(int argc, char **argv) {
    CLIOptions options{};

    for (auto i = 1; i < argc; i++) {
        if (!strcmp("--disable_custom_listener", argv[i])) {
            options.useCustomListener = false;
        } else if (!strcmp("--disable_alarm", argv[i])) {
            options.enableAlarm = false;
        } else if (!strcmp("--disable_segv", argv[i])) {
            options.enableSegv = false;
        } else if (!strcmp("--disable_abrt", argv[i])) {
            options.enableAbrt = false;
        }
    }

    return options;
}
