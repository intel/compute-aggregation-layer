#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

get_property(ICD_L0_OBJECTS_SOURCES GLOBAL PROPERTY ICD_L0_OBJECTS_SOURCES_PROPERTY)
get_property(SERVICE_L0_OBJECTS_SOURCES GLOBAL PROPERTY SERVICE_L0_OBJECTS_SOURCES_PROPERTY)

add_executable(l0_test_ult_icd
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_ult_icd.cpp

               ${cal_source_root_dir}/client/client_connection.cpp
               ${cal_source_root_dir}/client/icd/icd_global_state.cpp
               ${cal_source_root_dir}/client/client_malloc_override.cpp
               ${cal_source_root_dir}/client/icd/icd_ocl.cpp

               ${cal_source_root_dir}/shared/allocators.cpp
               ${cal_source_root_dir}/shared/callstack.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               ${cal_source_root_dir}/test/utils/signal_utils.cpp

               $<TARGET_OBJECTS:generated_ult_icd>

               ${ICD_L0_OBJECTS_SOURCES}

               ${cal_source_root_dir}/test/mocks/sys_mock.cpp
)

target_link_libraries(l0_test_ult_icd Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_icd)

add_executable(l0_test_ult_rpc
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_ult_rpc.cpp

               ${cal_source_root_dir}/client/client_connection.cpp
               ${cal_source_root_dir}/client/icd/icd_global_state.cpp
               ${cal_source_root_dir}/client/client_malloc_override.cpp
               ${cal_source_root_dir}/client/icd/icd_ocl.cpp

               ${cal_source_root_dir}/service/service.cpp

               ${cal_source_root_dir}/service/${BRANCH_DIR_SUFFIX}/register_all_generated_handlers.cpp
               ${cal_source_root_dir}/shared/allocators.cpp
               ${cal_source_root_dir}/shared/callstack.cpp
               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               ${cal_source_root_dir}/test/utils/signal_utils.cpp

               $<TARGET_OBJECTS:generated_ult>

               ${ICD_L0_OBJECTS_SOURCES}
               ${SERVICE_L0_OBJECTS_SOURCES}
)

target_link_libraries(l0_test_ult_rpc Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_rpc)

add_subdirectories()
