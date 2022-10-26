#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_executable(ocl_test_basic
               ${CMAKE_CURRENT_SOURCE_DIR}/ocl_test_basic.cpp
               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/utils.cpp
)

target_link_libraries(ocl_test_basic OpenCL ${common_library_dependencies})

add_executable(ocl_test_use_host_ptr
               ${CMAKE_CURRENT_SOURCE_DIR}/ocl_use_host_ptr.cpp
               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/utils.cpp
)
target_link_libraries(ocl_test_use_host_ptr OpenCL ${common_library_dependencies})

add_executable(ocl_test_ult_icd
               ${CMAKE_CURRENT_SOURCE_DIR}/ocl_ult_icd.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/sys.cpp

               ${cal_source_root_dir}/icd/icd_platform.cpp
               ${cal_source_root_dir}/icd/icd_global_state.cpp
               ${cal_source_root_dir}/icd/icd_ocl.cpp
               ${cal_source_root_dir}/icd/icd_level_zero.cpp
               ${cal_source_root_dir}/icd/icd_level_zero_table_exports.cpp

               ${cal_source_root_dir}/shared/utils.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${generated_dir}/generated_icd_ocl.cpp
               ${generated_dir}/generated_icd_level_zero.cpp
               ${generated_dir}/generated_rpc_messages_ocl.cpp
               ${generated_dir}/generated_rpc_messages_level_zero.cpp
)

target_link_libraries(ocl_test_ult_icd gmock-gtest ${common_library_dependencies})
macro_add_run_gtest_for(ocl_test_ult_icd)

add_subdirectories()
