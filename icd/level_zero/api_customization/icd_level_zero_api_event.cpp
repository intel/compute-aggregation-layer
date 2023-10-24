/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero_api.h"

namespace Cal::Icd::LevelZero {

ze_result_t zeEventQueryKernelTimestampsExtRpcHelper(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t *pCount, ze_kernel_timestamp_result_t *pResultsTimestamps, ze_synchronized_timestamp_result_ext_t *pResultsSynchronizedTimestamps);

ze_result_t zeEventQueryKernelTimestampsExt(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t *pCount,
                                            ze_event_query_kernel_timestamps_results_ext_properties_t *pResults) {

    if (pResults) {
        return zeEventQueryKernelTimestampsExtRpcHelper(hEvent, hDevice, pCount, pResults->pKernelTimestampsBuffer, pResults->pSynchronizedTimestampsBuffer);
    }
    return zeEventQueryKernelTimestampsExtRpcHelper(hEvent, hDevice, pCount, nullptr, nullptr);
}

} // namespace Cal::Icd::LevelZero
