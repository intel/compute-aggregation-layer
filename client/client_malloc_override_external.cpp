/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/client_malloc_override.h"

namespace Cal::Client::MallocOverride::External {

void initialize() {
}

bool isExportable(const void *ptr) {
    return false;
}

const void *exportPtr(const void *ptr, Rpc::ChannelClient &channel) {
    return ptr;
}

void *exportPtr(void *ptr, Rpc::ChannelClient &channel) {
    return ptr;
}

} // namespace Cal::Client::MallocOverride::External
