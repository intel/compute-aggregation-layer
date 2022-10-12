#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

cmake_minimum_required(VERSION 3.12)

project(cal)

include(CTest)
include(os_release_info.cmake)

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

set(cal_revision 0)
find_program(GIT NAMES git)
if(NOT "${GIT}" STREQUAL "GIT-NOTFOUND")
  if(IS_DIRECTORY ${cal_source_root_dir}/.git)
    set(GIT_arg --git-dir=${cal_source_root_dir}/.git rev-parse HEAD)
    execute_process(
                    COMMAND ${GIT} ${GIT_arg}
                    OUTPUT_VARIABLE cal_revision
                    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  endif()
endif()
add_definitions(-DCAL_REVISION=${cal_revision})
set(distro_id "")
set(distro_version_id "")
set(distro_codename "")
get_os_release_info(distro_id distro_version_id distro_codename)
add_definitions(-DCAL_BUILD_SYSTEM="${distro_id}-${distro_version_id}-${distro_codename}")

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

add_custom_target(run_unit_tests ALL)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest)
macro(macro_add_run_gtest_for target)
  get_target_property(target_sources ${target} SOURCES)
  if(NOT ${CMAKE_CXX_COMPILER} MATCHES "aarch64")
    add_custom_target(run_${target} DEPENDS ${target})
    add_custom_command(TARGET run_${target}
                       POST_BUILD
                       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                       COMMENT Running ${target} tests
                       COMMAND ${target} --gtest_repeat=1
    )
    add_dependencies(run_unit_tests run_${target})
    add_test(NAME ${target} COMMAND ${target} --gtest_repeat=1)
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
