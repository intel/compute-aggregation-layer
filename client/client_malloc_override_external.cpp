/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/client_malloc_override.h"

namespace Cal::Client::MallocOverride::External {

const char *getShmemName() {
    return "not_used";
}

} // namespace Cal::Client::MallocOverride::External
