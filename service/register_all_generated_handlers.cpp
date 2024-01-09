/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_service_level_zero.h"
#include "generated_service_ocl.h"

namespace Cal::Service::Apis::Ocl{
void registerAllGeneratedHandlersOcl(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
    registerGeneratedHandlersOcl(outHandlers);
}
}

namespace Cal::Service::Apis::LevelZero{
void registerAllGeneratedHandlersLevelZero(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
    registerGeneratedHandlersLevelZero(outHandlers);
}
}

