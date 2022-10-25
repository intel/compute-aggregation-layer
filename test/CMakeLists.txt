#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_definitions(-Dmockable=virtual)
add_definitions(-Dfinal=)
add_subdirectories()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run_blackbox_tests.py ${cal_binary_root_dir} COPYONLY)
