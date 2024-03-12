/*
 * Copyright (C) 2022-2024 Intel Corporation
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
inline constexpr std::string_view calTempFilesDefaultPath = "/tmp/compute_aggregation_layer";
inline constexpr std::string_view calShmemPathPrefix = "/compute_aggregation_layer_shmem_";
inline constexpr std::string_view calListenerSocketPathEnvName = "CAL_LISTENER_SOCKET_PATH";

// Controls whether Level Zero API calls should go through CAL
inline constexpr std::string_view calEnableL0InCalrunEnvName = "CAL_ENABLE_L0_IN_CALRUN";
// Controls whether OpenCL API calls should go through CAL
inline constexpr std::string_view calEnableOclInCalrunEnvName = "CAL_ENABLE_OCL_IN_CALRUN";
// Controls whether CAL should redirect L0 directly to the GPU driver
inline constexpr std::string_view calRedirectL0EnvName = "CAL_REDIRECT_L0";

// Controls whether CAL should override chosen command queue gruop indices
inline constexpr std::string_view calUseComputeRoundRobin = "CAL_USE_COMPUTE_ROUND_ROBIN";
inline constexpr std::string_view calUseCopyRoundRobin = "CAL_USE_COPY_ROUND_ROBIN";

// Controls whether CAL should make pageable memory copies blocking instead of using event manager
inline constexpr std::string_view calSyncMallocCopy = "CAL_SYNC_MALLOC_COPY";

// Controls whether some API calls should cache their results for faster access
inline constexpr std::string_view calIcdEnableCacheEnvName = "CAL_ICD_ENABLE_CACHE";
inline constexpr std::string_view calEnableAilEnvName = "CAL_USE_AIL";
// Controls whether CAL should use shared allocations
inline constexpr std::string_view calSharedAllocations = "CAL_SHARED_ALLOCATIONS";
// Controls whether CAL should attempt to print call stack when unhandled page fault occurs (requires CAL_SHARED_ALLOCATIONS to be enabled)
inline constexpr std::string_view calDumpStackOnUnhandledPagefault = "CAL_DUMP_STACK_ON_UNHANDLED_PAGE_FAULT";
// Controls whether threads should yield control while waiting for connection
inline constexpr std::string_view calYieldThreadsEnvName = "CAL_YIELD_THREADS";
// Controls whether CAL should reuse buffers
inline constexpr std::string_view calIcdBufferRecycleEnvName = "CAL_ICD_BUFFER_RECYCLE";
// Contoles whether CAL should use asynchronous calls
inline constexpr std::string_view calAsynchronousCalls = "CAL_ASYNC_CALLS";
// Contoles whether CAL should batch API calls
inline constexpr std::string_view calBatchedCalls = "CAL_BATCHED_CALLS";
// Contoles whether CAL should execute batched calls under lock
inline constexpr std::string_view calBatchedService = "CAL_BATCHED_SERVICE";
// Set default RPC channel size (in MB)
inline constexpr std::string_view calDefaultRpcChannelSizeEnvName = "CAL_DEFAULT_RPC_CHANNEL_SIZE_MB";
// Set RPC ring size in pages (default is <= 1)
inline constexpr std::string_view calRpcRingPagesEnvName = "CAL_RPC_RING_SIZE_PAGES";
// Set default shared VA window size per client (in GB)
inline constexpr std::string_view calDefaultSharedVaSizeEnvName = "CAL_DEFAULT_SHARED_VA_SIZE_GB";
// Allocate RPC channel within shared VA window
inline constexpr std::string_view calUseSharedVaForRpcChannel = "CAL_USE_SHARED_VA_FOR_RPC_CHANNEL";
// Set shared VA arena size in MB
inline constexpr std::string_view calSharedVaArenaSizeEnvName = "CAL_SHARED_VA_ARENA_SIZE_MB";
// Override malloc with IPC friendly implementation
inline constexpr std::string_view calOverrideMallocEnvName = "CAL_OVERRIDE_MALLOC";
// Minimum size of allocation that will be redirected to CAL implementation of malloc
inline constexpr std::string_view calOverrideMallocThresholdEnvName = "CAL_OVERRIDE_MALLOC_THRESHOLD_BYTES";
// Controls whether CAL should use emulated synchronous mode for command lists in synchronous mode (i.e. override synchronous queue with asynchronous mode and call command list execute + queue synchronize with timeout)
inline constexpr std::string_view calCommandQueueModeEmulatedSynchronousEnvName = "CAL_COMMAND_QUEUE_MODE_EMULATED_SYNCHRONOUS";

inline constexpr std::string_view calUseCustomOCLPlatformName = "CAL_USE_CUSTOM_OCL_PLATFORM_NAME";
inline constexpr std::string_view calPlatformName = "Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications";
inline constexpr std::string_view calServiceProcessName = NAME_TO_STR(CAL_NAME);

// Controls whether CAL should use semaphores as a service synchronization method
inline constexpr std::string_view calUseSemaphoresInChannelServerEnvName = "CAL_USE_SEMAPHORES_IN_CHANNEL_SERVER";
// Controls whether CAL should use semaphores as a client synchronization method
inline constexpr std::string_view calUseSemaphoresInChannelClientEnvName = "CAL_USE_SEMAPHORES_IN_CHANNEL_CLIENT";
inline constexpr std::string_view calUseSemaphoresThresholdInChannelClientEnvName = "CAL_USE_SEMAPHORES_THRESHOLD_IN_CHANNEL_CLIENT";

inline constexpr std::string_view calEarlyShmUnlinkEnvName = "CAL_EARLY_SHM_UNLINK";

// Debug
// Sets required logging verbosity. Available levels: [performance, silent, critical, error, info, debug, bloat]. Warning: bloat verbosity requires CAL to be built with ENABLE_BLOATED_VERBOSITY=1 cmake option
inline constexpr std::string_view calVerbosityEnvName = "CAL_MAX_VERBOSITY";
// Sets maximum level of logs that will contain callstack dump information (if available), default is silent (no callstack logs)
inline constexpr std::string_view calVerbosityCallStackEnvName = "CAL_MAX_VERBOSITY_CALLSTACK_DUMP";
// Controls whether CAL should work in benchmarking mode, which prints performance logs for aggregation layer
inline constexpr std::string_view calBenchmarkEnvName = "CAL_BENCHMARK";
// Set name of logger that prints results to stdout
inline constexpr std::string_view calUseLoggerNameEnvName = "CAL_USE_LOGGER_NAME";
// Appends PID to logger, for easier debug of multi process applications
inline constexpr std::string_view calAppendPIDEnvName = "CAL_APPEND_PID";
// Controls OpenCL profiling
inline constexpr std::string_view calOclDisableProfilingEnvName = "CAL_OCL_DISABLE_PROFILING";
// Set to value >=0 to break in specified CAL process and print PID. This allows to easlily attach a debugger
inline constexpr std::string_view calDebugBreakClientOrdinalEnvName = "CAL_DEBUG_BREAK_CLIENT_ORDINAL";
// By default CAL will abort any API call that uses structures with field pNext not set to nullptr, when the extension is not recognized by CAL. It effectively means, that usage of uninitialized pNext fields leads to abort of an application
inline constexpr std::string_view calAbortOnNonNullPNext = "CAL_ABORT_ON_NON_NULL_PNEXT";
// Use standalone allocations instead of allocating memory in an arena for zeMemAllocHost
inline constexpr std::string_view calUseStandaloneAllocationsForZeMemAllocHost = "CAL_USE_STANDALONE_ALLOCATIONS_FOR_ZE_MEM_ALLOC_HOST";
// Use alternative library (instead of regular libcal.so) on client side for L0 API
inline constexpr std::string_view calClientZeEnableAltDriversEnvName = "CAL_CLIENT_ZE_ENABLE_ALT_DRIVERS";
// Set 1 to debug break instead of aborting
inline constexpr std::string_view calDebugBreakInsteadOfAbortingEnvName = "CAL_DEBUG_BREAK_INSTEAD_ABORT";

// Set 1 to enable debug keys for CAL built in release mode
inline constexpr std::string_view calReadDebugKeysEnvName = "CAL_READ_DEBUG_KEYS";

// Environment variables available in CAL release mode (unless CAL_READ_DEBUG_KEYS=1) :
inline constexpr std::string_view calReleaseModeEnvs[] = {
    calVerbosityEnvName,
    calUseLoggerNameEnvName,
    calAppendPIDEnvName,
    calEnableL0InCalrunEnvName,
    calEnableOclInCalrunEnvName,
    calAsynchronousCalls,
    calUseCustomOCLPlatformName,
    calRedirectL0EnvName,
    calListenerSocketPathEnvName};
