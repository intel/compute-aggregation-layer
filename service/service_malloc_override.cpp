/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "service/service_malloc_override.h"

#include "shared/log.h"
#include "shared/sys.h"

namespace Cal::Service {

namespace MallocOverride {

bool isOverridenInCAL() {
    return true;
}

bool initializeClientData(const char *shmemName) {
    return true;
}

} // namespace MallocOverride

void checkForRequiredFilesMallocOverride(std::string &fullCalLibPath) {
    bool overrideMalloc = Cal::Utils::getCalEnvFlag(calOverrideMallocEnvName, false);
    if (overrideMalloc) {
        log<Verbosity::info>("CAL Malloc override enabled, using malloc implementation from : %s", fullCalLibPath.c_str());
        Cal::Sys::setenv("LD_PRELOAD", fullCalLibPath.c_str(), 1);
    }
}

} // namespace Cal::Service
