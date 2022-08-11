/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <string_view>

#ifndef NAME_TO_STR
#define NAME_TO_STR2(X) #X
#define NAME_TO_STR(X) NAME_TO_STR2(X)
#endif

constexpr std::string_view calTempFilesDefaultPath = "/tmp/compute_aggregation_layer/";
constexpr std::string_view calShmemPathPrefix = "/compute_aggregation_layer_shmem_";

constexpr std::string_view calPlatformName = "Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications";
constexpr std::string_view calServiceProcessName = NAME_TO_STR(CAL_NAME);

constexpr std::string_view calVerbosityEnvName = "CAL_MAX_VERBOSITY";
constexpr std::string_view calBenchmarkEnvName = "CAL_BENCHMARK";
constexpr std::string_view calListenerSocketPathEnvName = "CAL_LISTENER_SOCKET_PATH";
constexpr std::string_view calDefaultRpcChannelSizeEnvName = "CAL_DEFAULT_RPC_CHANNEL_SIZE_MB";
constexpr std::string_view calYieldThreadsEnvName = "CAL_YIELD_THREADS";
constexpr std::string_view calIcdBufferRecycleEnvName = "CAL_ICD_BUFFER_RECYCLE";
constexpr std::string_view calIcdEnableCacheEnvName = "CAL_ICD_ENABLE_CACHE";
constexpr std::string_view calEnableL0InCalrunEnvName = "CAL_ENABLE_L0_IN_CALRUN";
constexpr std::string_view calEnableOclInCalrunEnvName = "CAL_ENABLE_OCL_IN_CALRUN";
constexpr std::string_view calUseLoggerNameEnvName = "CAL_USE_LOGGER_NAME";
constexpr std::string_view calEnableAilEnvName = "CAL_USE_AIL";
