<!---
Copyright (C) 2022 Intel Corporation

SPDX-License-Identifier: MIT
-->

# Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications

## Introduction
Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications is an IPC-based mechanism for rerouting L0/OCL API calls from multiple processes into one (into Aggregation Layer service) in order to reduce overhead of GPU context switches.

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
source /opt/compute-aggregation-layer/cal_setenv_l0.sh

# enable cal for OpenCL
source /opt/compute-aggregation-layer/cal_setenv_ocl.sh

# enable cal for both APIs
source /opt/compute-aggregation-layer/cal_setenv.sh
```

After that, run target application as you would normally do.

## See also
- [Intel(R) Graphics Compute Runtime for oneAPI Level Zero and OpenCL(TM) Driver](https://github.com/intel/compute-runtime)
- [oneAPI Level Zero specification](https://spec.oneapi.io/level-zero/latest/index.html)
