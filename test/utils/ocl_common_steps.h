/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cal.h"
#include "shared/log.h"
#include "shared/ocl_wrapper.h"

#include <vector>

cl_platform_id getPlatform(int platformOrd);
std::vector<cl_device_id> getDevices(cl_platform_id platform, cl_device_type deviceType);
cl_context createContext(cl_platform_id platform, const std::vector<cl_device_id> &devices, size_t device_index);
cl_program createProgramWithSource(cl_context context, uint32_t numSources, const char **sources);
cl_program createProgramWithBinary(cl_context context, cl_device_id device, const size_t *lengths, unsigned char **binaries);
void compileProgram(cl_program program, cl_device_id device);
cl_program linkProgram(cl_context context, cl_device_id device, cl_program program);
void buildProgram(cl_program program, cl_device_id device);
cl_kernel createKernel(cl_program program, const char *kernelName);
bool isImageSupportedOnTestedDevice(cl_device_id device);

class MemObject {
  public:
    MemObject() = delete;
    MemObject(cl_mem mem) : allocation(mem) {}
    MemObject(const MemObject &other) = delete;
    MemObject(MemObject &&other) {
        allocation = other.allocation;
        other.allocation = 0;
    }

    ~MemObject() {
        if (allocation) {
            clReleaseMemObject(allocation);
        }
    }

    cl_mem get() const {
        return allocation;
    }

  protected:
    cl_mem allocation{};
};
