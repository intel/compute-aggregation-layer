<!---
Copyright (C) 2022 Intel Corporation

SPDX-License-Identifier: MIT
-->

# Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications

## Introduction
Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications is an IPC-based mechanism for rerouting L0/OCL API calls from multiple processes into an aggregation service, in order to reduce overhead of GPU context switches. It's tested with Intel(R) Graphics Compute Runtime for oneAPI Level Zero and OpenCL(TM) Driver, whose versions are provided in [third_party/linux_dependencies.yml](third_party/linux_dependencies.yml).

## License
The Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications is distributed under the MIT License.

You may obtain a copy of the License at: https://opensource.org/licenses/MIT

We at Intel are commited to create an open, welcoming, diverse, inclusive, and healthy community. Please refer to our [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md) for full text of our pledge and standards.

## Building and Installing
To build Compute Aggregation Layer, a Linux machine with C++17 compliant compiler is required. It also requires [CMake](https://cmake.org/) build system. Following commands will produce Release build. If you would like to build in Debug mode, add `-DCMAKE_BUILD_TYPE=Debug` flag to cmake step.
```bash
git clone https://github.com/intel/compute-aggregation-layer.git
cd compute-aggregation-layer
mkdir build
cd build
cmake ../
make -j
./calrun -h
```

This way binaries will be produced in `build` catalog and ready to use. You can also install them by invoking:

```bash
sudo make install
```

You may also need to run ldconfig to update shared libraries cache for newly installed libraries:

```bash
sudo ldconfig
```

Additional cmake build flags, that can be set during cmake invoke step (`-D<FLAG_NAME>=<VALUE>`):
- `ENABLE_BLOATED_VERBOSITY` - default: `false`. Control whether `bloat` log verbosity should be available
- `ENABLE_PERFORMANCE_DEBUG` - default: `true`. Control whether performance-related debug logs should be available
- `REQUIRE_CACHE_VERIFICATION_DEPENDENCIES` - default: `false`. Causes failure of build when the verification of generated cache cannot be performed
- `VERIFY_GENERATED_CACHE_IF_POSSIBLE` - default: `true`. Verifies if cached generated files are up to date and in synch with source files
- `DISABLE_ULT` - default: `false`. Set to `true` to skip unit testing during build

For development, we use Ubuntu 20.04 native and WSL, with gcc-9 and clang-14.

## Running Compute Aggregation Layer
Use of Compute Aggregation Layer needs to be explicitly opted-in, but it can be done without modifying the original application. There are two modes of running an application with Compute Aggregation Layer: scoped mode and persistent mode.

### Scoped Mode
In scoped mode, dedicated Compute Aggregation Layer service gets launched per workload (affects also all child processes of that workload). To use it, all it takes, is to add calrun into command line, i.e.
`calrun application_name [application_arguments]`
e.g.
`calrun ./l0_test_basic`

### Persistent Mode
In persistent mode, Compute Aggregation Layer service gets launched per user and all of user's workloads that use Compute Aggregation Layer will be rerouted to that single service instance.
In this mode, service needs to be explicitly started. Additionally, applications needs to opt-in to using that service (which, similarly to scoped mode, can be done without modifying the application.

#### Starting the service process
To start the service, simply run `calrun` or `calrun -p`.

#### Starting an application (e.g. an L0 application)
First step is to enable specific api, by scripts available in `/opt/compute-aggregation-layer`. Use `source` to run script for API that you are interesed in:
```bash
# enable cal for Level Zero
source /opt/compute-aggregation-layer/cal_setvars_l0.sh

# enable cal for OpenCL
source /opt/compute-aggregation-layer/cal_setvars_ocl.sh

# enable cal for both APIs
source /opt/compute-aggregation-layer/cal_setvars.sh
```

After that, run target application as you would normally do.

## Available enviroment flags
Refer to [include/cal.h](include/cal.h) for available flags and their descriptions.

## Setting Compute-Runtime environment variables when using Compute Aggregation Layer

When setting Compute Runtime (NEO) environment variables, users need to ensure that they are in the scope of the parent CAL process; i.e. it needs to be set in the environment prior to `calrun <application_name> [application_args]` call in scoped mode or in the environment of the single service instance in the case of persistent mode. Any exceptions to this rule is noted below.

### Exceptions to parent scope environment variable setting

- ZE\_AFFINITY\_MASK: This environment variable can be used/set in scripts that are executed by child process, i.e. individual MPI ranks are free to set their own ZE\_AFFINITY\_MASK value. This is due to fact that Compute Aggregation Layer intercepts this call to provide the correctly filtered list of device(s)/sub-device(s) the client requests.

## See also
- [Intel(R) Graphics Compute Runtime for oneAPI Level Zero and OpenCL(TM) Driver](https://github.com/intel/compute-runtime)
- [oneAPI Level Zero specification](https://spec.oneapi.io/level-zero/latest/index.html)
