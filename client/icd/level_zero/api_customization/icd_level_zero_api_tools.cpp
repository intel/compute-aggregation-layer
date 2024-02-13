/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd_level_zero_api_tools.h"

#include "client/icd/level_zero/icd_level_zero.h"
#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "shared/rpc.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zetMetricStreamerReadData(zet_metric_streamer_handle_t hMetricStreamer,
                                      uint32_t maxReportCount,
                                      size_t *pRawDataSize,
                                      uint8_t *pRawData) {
    ze_result_t ret;
    if (pRawData == nullptr) {
        ret = zetMetricStreamerReadDataRpcHelper(hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
    } else {
        log<Verbosity::info>("hostPtr alloc path, size %lu , host_ptr %p ", *pRawDataSize, pRawData);

        auto context = hMetricStreamer->asLocalObject()->context;
        std::unique_ptr<void, std::function<void(void *)>> standaloneHostPtrAlloc{
            context->getStagingAreaManager().allocateStagingArea(*pRawDataSize),
            [context](void *ptrToMarkAsUnused) { context->getStagingAreaManager().deallocateStagingArea(ptrToMarkAsUnused); }};

        void *standaloneHostPtr = standaloneHostPtrAlloc.get();

        ret = zetMetricStreamerReadDataRpcHelper(hMetricStreamer, maxReportCount, pRawDataSize, reinterpret_cast<uint8_t *>(standaloneHostPtr));
        memcpy(pRawData, standaloneHostPtr, pRawData ? *pRawDataSize : 0u);
    }

    return ret;
}

} // namespace Cal::Client::Icd::LevelZero
