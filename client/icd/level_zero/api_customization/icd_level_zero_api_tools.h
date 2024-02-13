/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/zet_api.h"

namespace Cal::Client::Icd::LevelZero {

ze_result_t zetMetricStreamerReadData(zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t *pRawDataSize, uint8_t *pRawData);

} // namespace Cal::Client::Icd::LevelZero
