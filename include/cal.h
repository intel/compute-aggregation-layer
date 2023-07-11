/*
 * Copyright (C) 2022-2023 Intel Corporation
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

// Settings
constexpr std::string_view calTempFilesDefaultPath = "/tmp/compute_aggregation_layer";
constexpr std::string_view calShmemPathPrefix = "/compute_aggregation_layer_shmem_";
constexpr std::string_view calListenerSocketPathEnvName = "CAL_LISTENER_SOCKET_PATH";

// Controls whether Level Zero API calls should go through CAL
constexpr std::string_view calEnableL0InCalrunEnvName = "CAL_ENABLE_L0_IN_CALRUN";
// Controls whether OpenCL API calls should go through CAL
constexpr std::string_view calEnableOclInCalrunEnvName = "CAL_ENABLE_OCL_IN_CALRUN";

// Controls whether CAL should override chosen command queue gruop indices
constexpr std::string_view calUseComputeRoundRobin = "CAL_USE_COMPUTE_ROUND_ROBIN";
constexpr std::string_view calUseCopyRoundRobin = "CAL_USE_COPY_ROUND_ROBIN";

// Controls whether CAL should make pageable memory copies blocking instead of using event manager
constexpr std::string_view calSyncMallocCopy = "CAL_SYNC_MALLOC_COPY";

// Controls whether some API calls should cache their results for faster access
constexpr std::string_view calIcdEnableCacheEnvName = "CAL_ICD_ENABLE_CACHE";
constexpr std::string_view calEnableAilEnvName = "CAL_USE_AIL";
// Controls whether CAL should use shared allocations
constexpr std::string_view calSharedAllocations = "CAL_SHARED_ALLOCATIONS";
// Controls whether CAL should attempt to print call stack when unhandled page fault occurs (requires CAL_SHARED_ALLOCATIONS to be enabled)
constexpr std::string_view calDumpStackOnUnhandledPagefault = "CAL_DUMP_STACK_ON_UNHANDLED_PAGE_FAULT";
// Controls whether threads should yield control while waiting for connection
constexpr std::string_view calYieldThreadsEnvName = "CAL_YIELD_THREADS";
// Controls whether CAL should reuse buffers
constexpr std::string_view calIcdBufferRecycleEnvName = "CAL_ICD_BUFFER_RECYCLE";
// Contoles whether CAL should use asynchronous calls
constexpr std::string_view calAsynchronousCalls = "CAL_ASYNC_CALLS";
// Contoles whether CAL should batch API calls
constexpr std::string_view calBatchedCalls = "CAL_BATCHED_CALLS";
// Contoles whether CAL should execute batched calls under lock
constexpr std::string_view calBatchedService = "CAL_BATCHED_SERVICE";
// Set default RPC channel size (in MB)
constexpr std::string_view calDefaultRpcChannelSizeEnvName = "CAL_DEFAULT_RPC_CHANNEL_SIZE_MB";
// Set RPC ring size in pages (default is <= 1)
constexpr std::string_view calRpcRingPagesEnvName = "CAL_RPC_RING_SIZE_PAGES";
// Set default shared VA window size per client (in GB)
constexpr std::string_view calDefaultSharedVaSizeEnvName = "CAL_DEFAULT_SHARED_VA_SIZE_GB";
// Allocate RPC channel within shared VA window
constexpr std::string_view calUseSharedVaForRpcChannel = "CAL_USE_SHARED_VA_FOR_RPC_CHANNEL";
// Set shared VA arena size in MB
constexpr std::string_view calSharedVaArenaSizeEnvName = "CAL_SHARED_VA_ARENA_SIZE_MB";
// Override malloc with IPC friendly implementation
constexpr std::string_view calOverrideMallocEnvName = "CAL_OVERRIDE_MALLOC";
// Minimum size of allocation that will be redirected to CAL implementation of malloc
constexpr std::string_view calOverrideMallocThresholdEnvName = "CAL_OVERRIDE_MALLOC_THRESHOLD_BYTES";

constexpr std::string_view calUseCustomOCLPlatformName = "CAL_USE_CUSTOM_OCL_PLATFORM_NAME";
constexpr std::string_view calPlatformName = "Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications";
constexpr std::string_view calServiceProcessName = NAME_TO_STR(CAL_NAME);

// Controls whether CAL should use semaphores as a service synchronization method
constexpr std::string_view calUseSemaphoresInChannelServerEnvName = "CAL_USE_SEMAPHORES_IN_CHANNEL_SERVER";
// Controls whether CAL should use semaphores as a client synchronization method
constexpr std::string_view calUseSemaphoresInChannelClientEnvName = "CAL_USE_SEMAPHORES_IN_CHANNEL_CLIENT";
constexpr std::string_view calUseSemaphoresThresholdInChannelClientEnvName = "CAL_USE_SEMAPHORES_THRESHOLD_IN_CHANNEL_CLIENT";

constexpr std::string_view calUsePnextInZeDeviceGetProperties = "CAL_USE_PNEXT_IN_ZE_DEVICE_GET_PROPERTIES";

// Debug
// Sets required logging verbosity. Available levels: [performance, silent, critical, error, info, debug, bloat]. Warning: bloat verbosity requires CAL to be built with ENABLE_BLOATED_VERBOSITY=1 cmake option
constexpr std::string_view calVerbosityEnvName = "CAL_MAX_VERBOSITY";
// Sets maximum level of logs that will contain callstack dump information (if available), default is silent (no callstack logs)
constexpr std::string_view calVerbosityCallStackEnvName = "CAL_MAX_VERBOSITY_CALLSTACK_DUMP";
// Controls whether CAL should work in benchmarking mode, which prints performance logs for aggregation layer
constexpr std::string_view calBenchmarkEnvName = "CAL_BENCHMARK";
// Set name of logger that prints results to stdout
constexpr std::string_view calUseLoggerNameEnvName = "CAL_USE_LOGGER_NAME";
// Appends PID to logger, for easier debug of multi process applications
constexpr std::string_view calAppendPIDEnvName = "CAL_APPEND_PID";
// Controls OpenCL profiling
constexpr std::string_view calOclDisableProfilingEnvName = "CAL_OCL_DISABLE_PROFILING";
// Set to value >=0 to break in specified CAL process and print PID. This allows to easlily attach a debugger
constexpr std::string_view calDebugBreakClientOrdinalEnvName = "CAL_DEBUG_BREAK_CLIENT_ORDINAL";
// By default CAL will abort any API call that uses structures with field pNext not set to nullptr, when the extension is not recognized by CAL. It effectively means, that usage of uninitialized pNext fields leads to abort of an application
constexpr std::string_view calAbortOnNonNullPNext = "CAL_ABORT_ON_NON_NULL_PNEXT";
// Use standalone allocations instead of allocating memory in an arena for zeMemAllocHost
constexpr std::string_view calUseStandaloneAllocationsForZeMemAllocHost = "CAL_USE_STANDALONE_ALLOCATIONS_FOR_ZE_MEM_ALLOC_HOST";
