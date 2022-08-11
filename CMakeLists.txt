#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

cmake_minimum_required(VERSION 3.12)

project(cal)

file(READ ".branch" BRANCH_TYPE)
string(STRIP "${BRANCH_TYPE}" BRANCH_TYPE)
set(BRANCH_DIR_SUFFIX "/${BRANCH_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
find_package(Threads REQUIRED)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}")

option(ENABLE_BLOATED_VERBOSITY "Enable all logs (a lot)" OFF)
option(ENABLE_PERFORMANCE_DEBUG "Enable performance-related debug logs" ON)

include(GNUInstallDirs)
set(CAL_OPT_INSTALL_PATH "/opt/compute-aggregation-layer/")

if(ENABLE_BLOATED_VERBOSITY)
  add_definitions(-DENABLE_BLOATED_VERBOSITY=1)
endif()

if(ENABLE_PERFORMANCE_DEBUG)
  add_definitions(-DPERFORMANCE_DEBUG=1)
endif()

set(cal_source_root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(cal_binary_root_dir ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(generated_dir ${cal_source_root_dir}/generated/cached)
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_SKIP_INSTALL_RPATH TRUE)
set(common_library_dependencies Threads::Threads rt dl)
if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
  set(common_library_dependencies ${common_library_dependencies} stdc++fs)
endif()

include_directories(${OpenCL_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${generated_dir}
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opencl_headers/
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/level_zero_headers/
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/level_zero_headers/level_zero
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest)
macro(macro_add_run_gtest_for target)
  if(NOT ${CMAKE_CXX_COMPILER} MATCHES "aarch64")
    add_custom_command(TARGET ${target}
                       POST_BUILD
                       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                       COMMENT Running ${target} tests
                       COMMAND ${target} --gtest_repeat=1
    )
  endif()
endmacro()

macro(add_subdirectories)
  file(GLOB subdirectories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
  foreach(subdir ${subdirectories})
    file(RELATIVE_PATH subdir_relative ${cal_source_root_dir} ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt)
      add_subdirectory(${subdir})
    endif()
  endforeach()
endmacro()

add_subdirectories()
