#
# Copyright (C) 2022-2023 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set(ICD_L0_OBJECTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_level_zero.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_level_zero_table_exports.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_command_list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_command_queue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_driver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_event_pool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_fence.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api.h
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_memory_experimental.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_module.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_pnext_translation.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/api_type_wrapper/module_wrapper.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/logic/imported_host_pointers_manager.cpp

    ${generated_dir}/generated_icd_level_zero.cpp
    ${generated_dir}/generated_rpc_messages_level_zero.cpp
)

set_property(GLOBAL PROPERTY ICD_L0_OBJECTS_SOURCES_PROPERTY "${ICD_L0_OBJECTS_SOURCES}")

add_library(icd_l0_objects OBJECT ${ICD_L0_OBJECTS_SOURCES})
set_property(TARGET icd_l0_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
