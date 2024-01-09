#
# Copyright (C) 2023-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

get_property(SERVICE_L0_OBJECTS_SOURCES GLOBAL PROPERTY SERVICE_L0_OBJECTS_SOURCES_PROPERTY)

set(SERVICE_L0_TESTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/l0_service_ult_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_artificial_events_allocator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_artificial_events_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_command_list_to_context_tracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ongoing_hostrptr_copies_manager.cpp

    ${cal_source_root_dir}/test/mocks/artificial_events_allocator_mock.cpp
    ${cal_source_root_dir}/test/mocks/sys_mock.cpp
    ${cal_source_root_dir}/test/utils/signal_utils.cpp
)

set(SERVICE_L0_TESTS_SHARED_DEPENDECIES
    ${cal_source_root_dir}/shared/allocators.cpp
    ${cal_source_root_dir}/shared/callstack.cpp
    ${cal_source_root_dir}/shared/utils.cpp
    ${cal_source_root_dir}/service/service.cpp
    ${cal_source_root_dir}/service/${BRANCH_DIR_SUFFIX}/register_all_generated_handlers.cpp
    $<TARGET_OBJECTS:generated_ult_service>
)

add_executable(l0_test_ult_service
               ${SERVICE_L0_TESTS_SOURCES}
               ${SERVICE_L0_OBJECTS_SOURCES}
               ${SERVICE_L0_TESTS_SHARED_DEPENDECIES}
)

target_link_libraries(l0_test_ult_service Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_service)

add_subdirectories()
