/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/client_platform.h"

namespace Cal {
namespace Mocks {

class PageFaultManagerMock : public Cal::Client::Icd::PageFaultManager {
  public:
    using PageFaultManager::findSharedAlloc;
    using PageFaultManager::PageFaultManager;
    using PageFaultManager::sharedAllocMap;
    using PageFaultManager::verifyPageFault;
};

} // namespace Mocks
} // namespace Cal
