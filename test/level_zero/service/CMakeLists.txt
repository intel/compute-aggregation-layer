#
# Copyright (C) 2023 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set(SERVICE_L0_TESTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/l0_service_ult_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_list_to_context_tracker.cpp
)

set(SERVICE_L0_TESTS_SHARED_DEPENDECIES
    ${cal_source_root_dir}/shared/callstack.cpp
    ${cal_source_root_dir}/shared/utils.cpp
    ${cal_source_root_dir}/test/mocks/sys_mock.cpp
)

add_executable(l0_test_ult_service
               ${SERVICE_L0_TESTS_SOURCES}
               $<TARGET_OBJECTS:service_l0_objects>
               ${SERVICE_L0_TESTS_SHARED_DEPENDECIES}
)

target_link_libraries(l0_test_ult_service Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_service)

add_subdirectories()
