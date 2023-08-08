#
# Copyright (C) 2022-2023 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_executable(shared_test_ult # ULTs
               ${cal_source_root_dir}/shared/allocators.cpp
               ${cal_source_root_dir}/shared/callstack.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/test/mocks/sys_mock.cpp

               ${CMAKE_CURRENT_SOURCE_DIR}/allocators_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/ref_counted_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/rpc_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/memory_block_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/shared_ult_main.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/shmem_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/staging_area_manager_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/usm_ult.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/utils_ult.cpp
)

target_link_libraries(shared_test_ult gmock-gtest ${common_library_dependencies})
macro_add_run_gtest_for(shared_test_ult)

add_subdirectories()
