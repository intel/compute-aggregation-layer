#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

macro(add_l0_blackbox TEST_NAME TEST_FILES)
  add_executable(${TEST_NAME}
                 ${TEST_FILES}
                 ${cal_source_root_dir}/test/utils/l0_common_steps.cpp
                 ${cal_source_root_dir}/shared/utils.cpp
                 ${cal_source_root_dir}/shared/sys.cpp
  )
  target_link_libraries(${TEST_NAME} ze_loader ${common_library_dependencies})
endmacro()

add_l0_blackbox(l0_blackbox_context ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_context.cpp)
add_l0_blackbox(l0_blackbox_device ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_device.cpp)
add_l0_blackbox(l0_blackbox_driver ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_driver.cpp)
add_l0_blackbox(l0_blackbox_fence ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_fence.cpp)
add_l0_blackbox(l0_blackbox_experimental_memory ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_experimental_memory.cpp)
add_l0_blackbox(l0_blackbox_memory ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_memory.cpp)
add_l0_blackbox(l0_blackbox_module_and_kernel ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_module_and_kernel.cpp)

add_executable(l0_test_basic
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_test_basic.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               ${cal_source_root_dir}/shared/sys.cpp
)
target_link_libraries(l0_test_basic ze_loader ${common_library_dependencies})

add_executable(l0_test_ult_icd
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_ult_icd.cpp

               ${cal_source_root_dir}/icd/icd_platform.cpp
               ${cal_source_root_dir}/icd/icd_global_state.cpp
               ${cal_source_root_dir}/icd/icd_ocl.cpp
               ${cal_source_root_dir}/icd/icd_level_zero.cpp

               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp

               ${generated_dir}/generated_icd_ocl.cpp
               ${generated_dir}/generated_rpc_messages_ocl.cpp
               ${generated_dir}/generated_icd_level_zero.cpp
               ${generated_dir}/generated_rpc_messages_level_zero.cpp
)

target_link_libraries(l0_test_ult_icd Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_icd)

add_executable(l0_test_ult_rpc
               ${CMAKE_CURRENT_SOURCE_DIR}/l0_ult_rpc.cpp

               ${cal_source_root_dir}/icd/icd_platform.cpp
               ${cal_source_root_dir}/icd/icd_global_state.cpp
               ${cal_source_root_dir}/icd/icd_ocl.cpp
               ${cal_source_root_dir}/icd/icd_level_zero.cpp

               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp

               ${generated_dir}/generated_icd_ocl.cpp
               ${generated_dir}/generated_rpc_messages_ocl.cpp
               ${generated_dir}/generated_icd_level_zero.cpp
               ${generated_dir}/generated_rpc_messages_level_zero.cpp
)

target_link_libraries(l0_test_ult_rpc Threads::Threads rt dl ${common_library_dependencies} gmock-gtest)
macro_add_run_gtest_for(l0_test_ult_rpc)

add_subdirectories()
