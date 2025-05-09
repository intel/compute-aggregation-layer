#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

macro(add_l0_blackbox TEST_NAME TEST_FILES)
  add_executable(${TEST_NAME}
                 ${TEST_FILES}
                 $<TARGET_OBJECTS:l0_blackbox_common>
  )
  target_compile_definitions(${TEST_NAME} PUBLIC FULL_VERBOSITY_IN_RELEASE_BUILD=1 ENABLE_BLOATED_VERBOSITY=1)
  target_link_libraries(${TEST_NAME} ze_loader ${common_library_dependencies})
endmacro()

add_library(l0_blackbox_common OBJECT
            ${cal_source_root_dir}/test/utils/l0_common_steps.cpp
            ${cal_source_root_dir}/shared/callstack.cpp
            ${cal_source_root_dir}/shared/utils.cpp
            ${cal_source_root_dir}/shared/sys.cpp
)
target_compile_definitions(l0_blackbox_common PUBLIC FULL_VERBOSITY_IN_RELEASE_BUILD=1 ENABLE_BLOATED_VERBOSITY=1)

add_l0_blackbox(l0_blackbox_append_mem_fill_copy_asynchronous_queue ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_fill_copy_asynchronous_queue.cpp)
add_l0_blackbox(l0_blackbox_append_mem_fill_copy_immediate_asynchronous ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_fill_copy_immediate_asynchronous.cpp)
add_l0_blackbox(l0_blackbox_append_mem_fill_copy_immediate_synchronous ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_fill_copy_immediate_synchronous.cpp)
add_l0_blackbox(l0_blackbox_append_mem_fill_copy_resubmit ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_fill_copy_resubmit.cpp)
add_l0_blackbox(l0_blackbox_append_mem_fill_copy_synchronous ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_fill_copy_synchronous.cpp)
add_l0_blackbox(l0_blackbox_append_mem_copy_from_context_deferred ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_copy_from_context_deferred.cpp)
add_l0_blackbox(l0_blackbox_append_mem_copy_from_context_immediate ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_copy_from_context_immediate.cpp)
add_l0_blackbox(l0_blackbox_append_mem_copy_region_deferred ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_copy_region_deferred.cpp)
add_l0_blackbox(l0_blackbox_append_mem_copy_region_immediate ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_mem_copy_region_immediate.cpp)
add_l0_blackbox(l0_blackbox_append_memory_ranges_barrier ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_append_memory_ranges_barrier.cpp)
add_l0_blackbox(l0_blackbox_context ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_context.cpp)
add_l0_blackbox(l0_blackbox_device ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_device.cpp)
add_l0_blackbox(l0_blackbox_driver ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_driver.cpp)
add_l0_blackbox(l0_blackbox_event ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_event.cpp)
add_l0_blackbox(l0_blackbox_fence ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_fence.cpp)
add_l0_blackbox(l0_blackbox_experimental_memory ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_experimental_memory.cpp)
add_l0_blackbox(l0_blackbox_malloc_override ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_malloc_override.cpp)
add_l0_blackbox(l0_blackbox_memory ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_memory.cpp)
add_l0_blackbox(l0_blackbox_metrics ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_metrics.cpp)
add_l0_blackbox(l0_blackbox_module_and_kernel ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_module_and_kernel.cpp)
add_l0_blackbox(l0_blackbox_module_create_via_extension ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_module_create_via_extension.cpp)
add_l0_blackbox(l0_blackbox_image ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_image.cpp)
add_l0_blackbox(l0_blackbox_dynamic_link ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_dynamic_link.cpp)
add_l0_blackbox(l0_blackbox_sysman ${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_sysman.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/l0_blackbox_runner_configs.yml ${cal_binary_root_dir} COPYONLY)
