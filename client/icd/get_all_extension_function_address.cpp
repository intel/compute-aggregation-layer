/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/get_all_extension_function_address.h"

#include "generated_icd_level_zero.h"
#include "generated_icd_ocl.h"

namespace Cal::Client::Icd::Ocl {

void *getAllExtensionFunctionAddress(const char *funcname) {
    return Cal::Client::Icd::Ocl::getOclExtensionFuncionAddressRpcHelper(funcname);
}

} // namespace Cal::Client::Icd::Ocl

namespace Cal::Client::Icd::LevelZero {

void *getAllL0ExtensionFuncionAddress(const char *funcname) {
    return Cal::Client::Icd::LevelZero::getL0ExtensionFuncionAddressRpcHelper(funcname);
}

} // namespace Cal::Client::Icd::LevelZero
