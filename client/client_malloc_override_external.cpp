/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/client_malloc_override.h"

namespace Cal::Client::MallocOverride::ExternalMemoryProvider {

void initialize() {
}

bool isEnabled() {
    return false;
}

bool isSharable(const void *ptr) {
    return false;
}

const void *exportPtr(const void *ptr, Rpc::ChannelClient &channel) {
    return ptr;
}

void *exportPtr(void *ptr, Rpc::ChannelClient &channel) {
    return ptr;
}

} // namespace Cal::Client::MallocOverride::ExternalMemoryProvider
