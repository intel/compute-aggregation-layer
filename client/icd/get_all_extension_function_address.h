/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

namespace Cal::Client::Icd::Ocl {

void *getAllExtensionFunctionAddress(const char *funcname);

}

namespace Cal::Client::Icd::LevelZero {

void *getAllL0ExtensionFuncionAddress(const char *name);

}
