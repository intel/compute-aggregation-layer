/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "icd/icd_platform.h"

namespace Cal {
namespace Mocks {

class PageFaultManagerMock : public Cal::Icd::PageFaultManager {
  public:
    using PageFaultManager::findSharedAlloc;
    using PageFaultManager::PageFaultManager;
    using PageFaultManager::sharedAllocMap;
    using PageFaultManager::verifyPageFault;
};

} // namespace Mocks
} // namespace Cal
