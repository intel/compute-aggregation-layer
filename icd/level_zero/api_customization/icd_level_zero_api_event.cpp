/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_icd_level_zero.h"
#include "icd/icd_global_state.h"
#include "icd/level_zero/icd_level_zero.h"
#include "icd_level_zero_api.h"
#include "shared/log.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeEventHostSynchronize(ze_event_handle_t hEvent, uint64_t timeout) {
    log<Verbosity::debug>("Detected call to zeEventHostSynchronize()! "
                          "If events were used to synchronize zeCommandListAppendMemoryCopy() to user's heap/stack, then operation result may be invalid!");
    return zeEventHostSynchronizeRpcHelper(hEvent, timeout);
}

} // namespace Cal::Icd::LevelZero
