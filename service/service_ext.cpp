/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "service/service.h"

using namespace std::string_literals;

namespace Cal {
namespace Service {

bool getNeoKmdShimEnvEnabled() {
    return false;
}

void setNeoKmdShimEnvEnabled(bool value) {
}

void checkForRequiredFiles(bool kmdShimEnabled) {
    auto calDir = Cal::Utils::getProcessPath().parent_path();
    std::filesystem::path libCalPath;
    std::string fullCalLibPath;

    std::string libCalName = "libcal.so";
    checkForRequiredFilesLibrary(calDir, libCalName, libCalPath, fullCalLibPath);
    log<Verbosity::info>("CAL library: %s", fullCalLibPath.c_str());
    checkForRequiredFilesOcl(calDir);
    checkForRequiredFilesL0(libCalPath);
    checkForRequiredFilesMallocOverride(fullCalLibPath);
}

} // namespace Service
} // namespace Cal
