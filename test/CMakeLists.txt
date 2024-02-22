#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_definitions(-Dmockable=virtual)
add_definitions(-Dfinal=)
string(REGEX REPLACE "-Werror[^=]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE "-Werror[^=]" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
add_subdirectories()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run_blackbox_tests.py ${cal_binary_root_dir} COPYONLY)
