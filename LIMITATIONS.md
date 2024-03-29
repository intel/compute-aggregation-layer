<!---
Copyright (C) 2024 Intel Corporation

SPDX-License-Identifier: MIT
-->

# Usage limitations and exceptional cases of Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications
The Compute Aggregation Layer (CAL), as a separate tool designed to work on top of the GPU driver and accelerate GPU execution from multiple processes (MPI ranks), can introduce several usage limitations and exceptions.

Here is the list of known CAL usage limitations and exceptional cases with examples from oneAPI Level Zero Conformance tests and OpenCL Khronos conformance tests:

## CAL doesn't support Concurrent Access and Concurrent Atomic Access capabilites in Unified Shared Memory (USM) model
This is a potential limitation when comparing to the underlying GPU driver which may support Concurrent and Concurrent Atomic Access capabilities for the USM shared allocations.
Note: The USM restriction may cause some oneAPI Level Zero Conformance tests that require concurrent access support to be skipped with CAL, e.g.

calrun test_copy --gtest_filter=*GivenMemoryCopiesWithDependenciesWhenExecutingCommandListThenCommandsCompletesSuccessfully*
test output:
Concurrent access for shared allocations unsupported by device, skipping test

## CAL doesn't fully support negative scenarios for some Level Zero and OpenCL API calls
This limitation applies only to the scenarios where returned values from API calls are tested for expected error codes.
Note: CAL uses asynchronous calls by default and CAL client doesn't wait for each API call from aggregated service to complete in order to accelerate execution on the GPU device and ensure the best performance.
This expected behavior can be controlled using the CAL_ASYNC_CALLS=0/1 environmental variable, e.g.

CAL_ASYNC_CALLS=0 calrun test_module_errors --gtest_filter=*GivenKernelWithSharedLocalMemoryLargerThanMaxSharedLocalMemorySizeThenOutOfMemoryErrorIsReturned*

## CAL has limited support for Level Zero source debugger
CAL support for Level Zero source debugger has been limited to detecting the gdb process and redirecting Level Zero API calls directly to the GPU driver, excluding the CAL service entirely. From a CAL implementation perspective, this means that CAL loads GPU driver library (ze_intel_gpu.so) and Level Zero loader initializes the GPU driver API entry points (i.e. the Level Zero DDI in place of the CAL DDI function table)
in order to forward Level Zero API calls to the GPU driver and bypass communication via the CAL service.
Note: the debug API restrictions also affect some of oneAPI Level Zero Conformance tests, which execution will be redirected directly to the GPU driver as well, e.g.

calrun test_debug --gtest_filter=*GivenDeviceSupportsDebugAttachWhenAttachingThenAttachAndDetachIsSuccessful*

## CAL has limited support for GPU kernel printfs
CAL support for GPU kernel printfs has been limitted to printing a debug message to Standard Output (stdout) by the GPU driver running in the CAL service process.
Note: The debug message printed from the GPU kernel is not sent back to the CAL client, so the test can't expect to read the message from stdout stream of the CAL client process to verify the string correctness, e.g.

calrun ./test_printf CL_DEVICE_TYPE_GPU
test output:
0)testing printf("%5d",10)
   10
int_0 FAILED

## CAL has limited support for GPU kernel asserts
CAL support for GPU kernel asserts has been limitted to printing a debug message to Standard Error (stderr) output by the GPU driver running in the CAL service process.
In addition to the debug message the kernel assert will trigger the abort operation in the GPU driver (by design) and therefore cause the CAL service process to terminate, which is the expected behavior.
Note: The debug message is not communicated back to the CAL client, so if the test expects to catch the message from stderr output then it should configure CAL to redirect Level Zero API calls directly to the GPU driver with the CAL_REDIRECT_L0=1 environmental variable.

## CAL can increase timeouts used with some Level Zero API functions
The example affected API functions are: zeCommandListHostSynchronize, zeCommandQueueSynchronize, zeEventHostSynchronize, zeFenceHostSynchronize, zesDriverEventListen, zesDriverEventListenEx.

e.g.
calrun test_cmdqueue --gtest_filter=*GivenTimeoutWhenWaitingForCommandQueueThenWaitForSpecifiedTime*
test output:
Expected: (ratio_cq) <= (1.02f), actual: 1.02654 vs 1.02

## Currently CAL can force some OpenCL API commands used for memory transfers to be blocking/synchronous
This restrictions applies the non-blocking OpenCL API commands used to read or copy into memory, affects the OpenCL scenarios below and can lead to deadlocks.

|      affected API call (non-blocking)         |                           affected OpenCL scenario                            |                               problem  mitigation                                   |
|-----------------------------------------------|-------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| clEnqueueMapBuffer                            | enqueue non-blocking command to map buffer created with malloced host pointer | use USM host or SVM pointer to create buffer with host ptr                          |
| clEnqueueReadBuffer / clEnqueueReadBufferRect | enqueue non-blocking command to read buffer to malloced pointer               | use USM host or SVM pointer instead as a destination for the read buffer operation  |
| clEnqueueSVMMemcpy / clEnqueueMemcpyINTEL     | enqueue non-blocking command to do a memcpy operation to malloced pointer     | use USM host or SVM pointer instead as a destination for the memcpy operation       |
| clEnqueueWriteBufferRect                      | enqueue non-blocking command to write buffer rect from malloced pointer       | use USM host or SVM pointer instead as a source for the write buffer rect operation |

The example scenario in OpenCL Khronos conformance tests when non-blocking clEnqueueReadBuffer command hangs on user event due to forcing blocking read:

calrun test_events callbacks CL_DEVICE_TYPE_GPU
test output:
Waiting for callback...
test timeout

## Currently CAL doesn't support images
This limitation means that clGetDeviceInfo query with CL_DEVICE_IMAGE_SUPPORT will return false for OpenCL device with CAL and OpenCL Khronos conformance tests will be skipped, e.g.

calrun test_cl_read_write_images
test output:
SKIPPED: Device does not supported images as required by this test!

## Currently CAL doesn't support the per-client ZE_FLAT_DEVICE_HIERARCHY configuration setting
Clients sharing a CAL service need to use a single configuration mode and this mode needs to be set-up as an environment variable when starting the service.

## Currently CAL doesn't fully support zeFabricVertexGetSubVerticesExp
The restriction applies to the scenarios when the zeFabricVertexGetSubVerticesExp function is called in conjunction with the per-client ZE_AFFINITY_MASK configuration setting.

e.g.
calrun ./test_fabric --gtest_filter=*GivenAffinityMaskIsSetWhenCallingFabricVertexGetThenVerifyOnlyExpectedVerticesAndSubVerticesAreReturned*
test output:
Value of: is_affinity_set_correctly

## Currently CAL doesn't support oneAPI System Resource Management (sysman) initialization with zesInit()
The new initialization method of the sysman module with a dedicated zesInit() API call is currently not supported.
Note: CAL by default initializes sysman using the ZES_ENABLE_SYSMAN environment variable during the initialization of the oneAPI Level Zero driver with zeInit() call, e.g.

calrun test_sysman_power_zesinit --gtest_filter=*GivenPowerHandleWhenRequestingExtensionPowerPropertiesThenValidDefaultLimitsAreReturned*
test output:
zesInit failed: ZE_RESULT_ERROR_UNSUPPORTED_FEATURE

## CAL limitations related to shared memory usage
CAL makes use of shared memory resources for the purpose of communication between client and service. The allocated resources are represented by `/dev/shm/compute_aggregation_layer_shmem_<ID>` filesystem nodes (and associated file-descriptors).
Both the user-available file-descriptors number as well as the total size of shared memory are limited system resources. Depending on application-created pressure, it is possible that these limits are hit - causing the application to fail.
In order to mitigate that it is possible to tune the limits with respective shell commands.

_(NOTE: In the following part of this section all commands starting with a dollar sign (`$`) are standard bash commands expected to work on all most popular Linux distributions)_

### System limit for the number of file-descriptors
If this limit is the cause of the application failure an error message like `Too many open files` (or similar one) should be observable in the standard output.
* The current value of the limit can be queried with `$ ulimit -n`.
* The new value of the limit can be set with `$ ulimit -n <NEW_VALUE>`. This may or may not require superuser privileges.

### System limit for the size of shared memory
When this limit is being approached by the application, the following (or similar one) error message should be observable in the standard output:
`Reaching size limits of /dev/shm/, allocating additional memory may fail. Please consider increasing the size of /dev/shm.`
* The static size of shared memory available system-wide can be queried with `$ df -h | grep '/dev/shm'` command. It can be modified (upper-bound by the total size of RAM) with the `$ sudo mount -o remount,size=<NEW_SHMEM_SIZE> /dev/shm` command. The latter requires superuser privileges.
* The size of dynamically allocated shared memory (at a given moment) can be queried with `$ cat  /proc/meminfo | grep 'Shmem:'` or `$ free`. For real-time observation it is recommended to combine them with the `$ watch` command, e.g. `$ watch -n1 free -g`.

### Shared memory and docker
In order to use CAL from within a docker container one needs to increase the amount of shared memory assigned to the container by default.
This can be done by passing the additional `--shm-size <NEW_SHMEM_SIZE>` (e.g. `16G` is a reasonable choice) parameter to the docker command.

## CAL limitations related to virtual memory usage
### System limits the maximum number of memory map areas a process can have
You may need to increase the `vm.max_map_count` kernel parameter to avoid running out of map areas for memory resources of the application aggregated to the single CAL service.

* The `vm.max_map_count` kernel parameter can be queried with the `$ cat /proc/sys/vm/max_map_count` command. The default value for `vm.max_map_count` is 65530.
* To increase the `vm.max_map_count` value temporarily, one can load the new count value with the following command: `$ sudo sysctl -w vm.max_map_count=<NEW_MAP_COUNT>`, where `<NEW_MAP_COUNT>` should be around 1 per 128 KB of system memory, e.g. `vm.max_map_count=2097152` on a 256 GB system. The above command will load the new max_map_count value till the next system restart.
* To increase the max_map_count parameter persistently, one can add or update the following line `vm.max_map_count=<NEW_MAP_COUNT>` to `/etc/sysctl.conf` and reload the config as root with the `$sysctl -p` command.
