/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero_api_tracing.h"

#include "client/icd/level_zero/tracing/tracing_imp.h"
#include "generated_icd_level_zero.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zetTracerExpCreate(zet_context_handle_t hContext, const zet_tracer_exp_desc_t *desc, zet_tracer_exp_handle_t *phTracer) {
    return createAPITracer(hContext, desc, phTracer);
}

ze_result_t zetTracerExpDestroy(zet_tracer_exp_handle_t hTracer) {
    return APITracer::fromHandle(hTracer)->destroyTracer(hTracer);
}

ze_result_t zetTracerExpSetPrologues(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t *pCoreCbs) {
    return APITracer::fromHandle(hTracer)->setPrologues(pCoreCbs);
}

ze_result_t zetTracerExpSetEpilogues(zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t *pCoreCbs) {
    return APITracer::fromHandle(hTracer)->setEpilogues(pCoreCbs);
}

ze_result_t zetTracerExpSetEnabled(zet_tracer_exp_handle_t hTracer, ze_bool_t enable) {
    return APITracer::fromHandle(hTracer)->enableTracer(enable);
}

} // namespace Cal::Client::Icd::LevelZero
