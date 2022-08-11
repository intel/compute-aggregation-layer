/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "service/cochoreographer.h"

namespace Cal {

namespace Service {

std::unique_ptr<ChoreographyLibrary> ChoreographyLibrary::create() {
    return std::make_unique<ChoreographyLibrary>();
}

} // namespace Service

} // namespace Cal
