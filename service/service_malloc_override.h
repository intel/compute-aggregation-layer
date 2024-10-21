/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "cal.h"

#include <string>

namespace Cal::Service {

namespace MallocOverride {

bool isOverridenInCAL();

bool initializeClientData(const char *shmemName);

} // namespace MallocOverride

void checkForRequiredFilesMallocOverride(std::string &fullCalLibPath);

} // namespace Cal::Service
