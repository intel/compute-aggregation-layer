#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set(SERVICE_L0_OBJECTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/artificial_events_allocator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/artificial_events_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/context_mappings_tracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/l0_shared_objects.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ongoing_hostptr_copies_manager.cpp
)

set_property(GLOBAL PROPERTY SERVICE_L0_OBJECTS_SOURCES_PROPERTY "${SERVICE_L0_OBJECTS_SOURCES}")

add_library(service_l0_objects OBJECT ${SERVICE_L0_OBJECTS_SOURCES})
set_property(TARGET service_l0_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
