#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_library(OpenCL SHARED ${generated_dir}/generated_stub_lib_ocl.cpp)
add_library(ze_loader SHARED ${generated_dir}/generated_stub_lib_level_zero.cpp)
set_target_properties(ze_loader PROPERTIES VERSION 1)

set_target_properties(OpenCL
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stub_libs"
)

set_target_properties(ze_loader
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stub_libs"
)

add_subdirectories()