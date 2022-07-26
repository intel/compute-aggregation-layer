#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

get_property(ICD_L0_OBJECTS_SOURCES GLOBAL PROPERTY ICD_L0_OBJECTS_SOURCES_PROPERTY)

add_executable(l0_test_ult_icd
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_ult_icd.cpp

               ${cal_source_root_dir}/icd/icd_platform.cpp
               ${cal_source_root_dir}/icd/icd_global_state.cpp
               ${cal_source_root_dir}/icd/icd_ocl.cpp

               ${cal_source_root_dir}/shared/allocators.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp

               ${generated_dir}/generated_icd_ocl.cpp
               ${generated_dir}/generated_rpc_messages_ocl.cpp

               ${ICD_L0_OBJECTS_SOURCES}

               ${cal_source_root_dir}/test/mocks/sys_mock.cpp
)

target_link_libraries(l0_test_ult_icd Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_icd)

add_executable(l0_test_ult_rpc
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_ult_rpc.cpp

               ${cal_source_root_dir}/icd/icd_platform.cpp
               ${cal_source_root_dir}/icd/icd_global_state.cpp
               ${cal_source_root_dir}/icd/icd_ocl.cpp

               ${cal_source_root_dir}/shared/allocators.cpp
               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp

               ${generated_dir}/generated_icd_ocl.cpp
               ${generated_dir}/generated_rpc_messages_ocl.cpp

               ${ICD_L0_OBJECTS_SOURCES}
)

target_link_libraries(l0_test_ult_rpc Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_rpc)

add_subdirectories()
