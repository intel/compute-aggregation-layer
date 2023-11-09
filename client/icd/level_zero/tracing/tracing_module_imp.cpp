/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "client/icd/level_zero/tracing/tracing_imp.h"
#include "generated_icd_level_zero.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zeModuleCreateTracing(ze_context_handle_t hContext,
                                  ze_device_handle_t hDevice,
                                  const ze_module_desc_t *desc,
                                  ze_module_handle_t *phModule,
                                  ze_module_build_log_handle_t *phBuildLog) {

    ZE_HANDLE_TRACER_RECURSION(l0Ddi.Module.pfnCreate,
                               hContext,
                               hDevice,
                               desc,
                               phModule,
                               phBuildLog);

    ze_module_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.pphModule = &phModule;
    tracerParams.pphBuildLog = &phBuildLog;

    Cal::Client::Icd::APITracerCallbackDataImp<ze_pfnModuleCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleCreateCb_t, Module, pfnCreateCb);

    ze_pfnModuleCreate_t pfnCreate = Cal::Client::Icd::LevelZero::zeModuleCreate;

    return Cal::Client::Icd::apiTracerWrapperImp(pfnCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext,
                                                 *tracerParams.phDevice,
                                                 *tracerParams.pdesc,
                                                 *tracerParams.pphModule,
                                                 *tracerParams.pphBuildLog);
}

} // namespace Cal::Client::Icd::LevelZero
