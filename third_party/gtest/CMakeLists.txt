#
# Copyright (C) 2018-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

# Disable warnings from GTest.
string(REPLACE "-Wall" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "-Wextra" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE "-Werror[^ ]*" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

string(REPLACE "-Wall" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
string(REPLACE "-Wextra" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
string(REGEX REPLACE "-Werror[^ ]*" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

add_library(gmock-gtest STATIC EXCLUDE_FROM_ALL
  ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/gmock-gtest-all.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest.h
  ${CMAKE_CURRENT_SOURCE_DIR}/gmock/gmock.h
)

target_include_directories(gmock-gtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
