#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

cmake_minimum_required(VERSION 3.12)

project(cal LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(IS_MULTI_CONFIG)
  message(STATUS "Running multi-config mode")
  set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "" FORCE)
  set(CMAKE_DEFAULT_CONFIGS "Release" CACHE STRING "" FORCE)
elseif(NOT CMAKE_BUILD_TYPE)
  message(STATUS "CMAKE_BUILD_TYPE not specified, using Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type: [Release, Debug]" FORCE)
endif()

include(CTest)
include(os_release_info.cmake)
include(CheckIPOSupported)
include(CheckCXXCompilerFlag)

file(READ ".branch" BRANCH_TYPE)
string(STRIP "${BRANCH_TYPE}" BRANCH_TYPE)
set(BRANCH_DIR_SUFFIX "/${BRANCH_TYPE}")
message("BRANCH_DIR_SUFFIX : ${BRANCH_DIR_SUFFIX}")

check_ipo_supported(RESULT __IPO_SUPPORTED)
if(__IPO_SUPPORTED)
  message(STATUS "Link Time Optimizations are enabled")
  set(CAL_DISABLE_LD_LLD TRUE)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

find_program(__LD_LLD_FOUND ld.lld)
find_program(__LD_GOLD_FOUND ld.gold)
check_cxx_compiler_flag(-fuse-ld=lld COMPILER_SUPPORTS_LLD)
check_cxx_compiler_flag(-fuse-ld=gold COMPILER_SUPPORTS_GOLD)

if(NOT CAL_DISABLE_LD_LLD AND __LD_LLD_FOUND AND COMPILER_SUPPORTS_LLD)
  message(STATUS "Using linker: ld.lld")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld -Wl,--build-id=sha1")
elseif(__LD_GOLD_FOUND AND COMPILER_SUPPORTS_GOLD)
  message(STATUS "Using linker: ld.gold")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--build-id=sha1")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Werror=format-security -Wno-unused-parameter -Wno-missing-field-initializers -pthread -fstack-protector -fPIC -fno-rtti")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-extern-c-compat")
endif()

option(ENABLE_SPECTRE_MITIGATIONS "Enable compiler protections against branch target injection (Spectre v2)" ON)
if(ENABLE_SPECTRE_MITIGATIONS)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-extern-c-compat")
    check_cxx_compiler_flag(-mretpoline COMPILER_SUPPORTS_RETPOLINE)
    if(COMPILER_SUPPORTS_RETPOLINE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mretpoline")
    else()
      message(WARNING "Spectre mitigation -mretpoline flag is not supported by the compiler")
    endif()
  else()
    check_cxx_compiler_flag(-mindirect-branch=thunk COMPILER_SUPPORTS_INDIRECT_BRANCH_THUNK)
    if(COMPILER_SUPPORTS_INDIRECT_BRANCH_THUNK)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mindirect-branch=thunk")
    else()
      message(WARNING "Spectre mitigation -mindirect-branch=thunk flag is not supported by the compiler")
    endif()
    check_cxx_compiler_flag(-mfunction-return=thunk COMPILER_SUPPORTS_FUNCTION_RETURN_THUNK)
    if(COMPILER_SUPPORTS_FUNCTION_RETURN_THUNK)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfunction-return=thunk")
    else()
      message(WARNING "Spectre mitigation -mfunction-return=thunk flag is not supported by the compiler")
    endif()
    check_cxx_compiler_flag(-mindirect-branch-register COMPILER_SUPPORTS_INDIRECT_BRANCH_REGISTER)
    if(COMPILER_SUPPORTS_INDIRECT_BRANCH_REGISTER)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mindirect-branch-register")
    else()
      message(WARNING "Spectre mitigation -mindirect-branch-register flag is not supported by the compiler")
    endif()
  endif()
else()
  message(WARNING "Spectre mitigations are DISABLED")
endif()

if(USE_SANITIZE_UB)
  unset(COMPILER_SUPPORTS_UNDEFINED_BEHAVIOR_SANITIZER CACHE)
  check_cxx_compiler_flag(-fsanitize=undefined COMPILER_SUPPORTS_UNDEFINED_BEHAVIOR_SANITIZER)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $<$<BOOL:${COMPILER_SUPPORTS_UNDEFINED_BEHAVIOR_SANITIZER}>:-fsanitize=undefined -fno-sanitize-recover=undefined>")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $<$<BOOL:${COMPILER_SUPPORTS_UNDEFINED_BEHAVIOR_SANITIZER}>:-fsanitize=undefined>")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -fstack-protector-strong -O2 -D_FORTIFY_SOURCE=2 -DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,noexecstack,-z,now,-z,relro")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,noexecstack,-z,now,-z,relro")

find_package(Threads REQUIRED)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}")

option(ENABLE_BLOATED_VERBOSITY "Enable all logs (a lot)" OFF)
option(ENABLE_PERFORMANCE_DEBUG "Enable performance-related debug logs" ON)
option(DISABLE_ULT "Disables unit tests from ALL target" OFF)
option(READ_DEBUG_KEYS_IN_RELEASE "Allow CAL debug environment variables even when built in release mode" OFF)

if(READ_DEBUG_KEYS_IN_RELEASE)
  add_definitions(-DCAL_ENABLE_DEBUG_KEYS_IN_RELEASE=1)
endif()
message("READ_DEBUG_KEYS_IN_RELEASE is ${READ_DEBUG_KEYS_IN_RELEASE}")

option(ENABLE_CALLSTACK_DUMPING "Enable dumping of callstack" OFF)
set(ENABLE_CALLSTACK_DUMPING_DEFAULT "$<IF:$<CONFIG:DEBUG>,1,0>")
add_definitions(-DCAL_SUPPORT_CALLSTACK_DUMPING="$<IF:$<BOOL:${ENABLE_CALLSTACK_DUMPING}>,1,${ENABLE_CALLSTACK_DUMPING_DEFAULT}>")

if(NOT IS_MULTI_CONFIG)
  if(ENABLE_CALLSTACK_DUMPING OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("ENABLE_CALLSTACK_DUMPING is ON")
  else()
    message("ENABLE_CALLSTACK_DUMPING is OFF")
  endif()
endif()

include(GNUInstallDirs)
set(CAL_OPT_INSTALL_PATH "/opt/compute-aggregation-layer/")

if(ENABLE_BLOATED_VERBOSITY)
  add_definitions(-DENABLE_BLOATED_VERBOSITY=1)
endif()
message("BLOATED_VERBOSITY is ${ENABLE_BLOATED_VERBOSITY}")

if(ENABLE_PERFORMANCE_DEBUG)
  add_definitions(-DPERFORMANCE_DEBUG=1)
endif()
message("PERFORMANCE_DEBUG is ${ENABLE_PERFORMANCE_DEBUG}")

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

if(${BRANCH_DIR_SUFFIX} STREQUAL "/")
  add_definitions(-DBRANCH_BASED_CMDQ_TIMEOUT_DIVISOR=1000)
else()
  add_definitions(-DBRANCH_BASED_CMDQ_TIMEOUT_DIVISOR=1)
endif()

include_directories(${OpenCL_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${generated_dir}
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/boost
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opencl_headers/
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/level_zero_headers/
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/level_zero_headers/level_zero
                    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest
)

add_custom_target(run_unit_tests ALL)
if(DISABLE_ULT)
  message(WARNING "Unit Testing is DISABLED")
  set_target_properties(run_unit_tests PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

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
