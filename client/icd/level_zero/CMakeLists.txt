#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set(ICD_L0_OBJECTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_level_zero.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_level_zero_table_exports.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_command_list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_command_queue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/${BRANCH_DIR_SUFFIX}/icd_level_zero_api_customization.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_driver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_event_pool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api.h
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_memory_experimental.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_module.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_pnext_translation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_sysman.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_tracing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_customization/icd_level_zero_api_tools.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/api_type_wrapper/device_wrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api_type_wrapper/module_wrapper.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/debugger/${BRANCH_DIR_SUFFIX}/debugger_imp.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/logic/hostptr_copies_reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/imported_host_pointers_manager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tracing/tracing_imp.cpp
)

set_property(GLOBAL PROPERTY ICD_L0_OBJECTS_SOURCES_PROPERTY "${ICD_L0_OBJECTS_SOURCES}")

add_library(icd_l0_objects OBJECT ${ICD_L0_OBJECTS_SOURCES})
set_property(TARGET icd_l0_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
