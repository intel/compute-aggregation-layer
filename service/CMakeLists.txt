#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_definitions(-DCAL_NAME=calrun)
add_definitions(-DCAL_LOGGER_NAME=S)
add_definitions(-Dmockable=)

include_directories(${cal_binary_root_dir}/generated)

add_executable(calrun # SERVICE
               ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}${BRANCH_DIR_SUFFIX}/cochoreographer.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}${BRANCH_DIR_SUFFIX}/register_all_generated_handlers.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/service.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}${BRANCH_DIR_SUFFIX}/service_ext.cpp
               ${cal_source_root_dir}/shared/allocators.cpp
               ${cal_source_root_dir}/shared/callstack.cpp
               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               $<TARGET_OBJECTS:generated_service>
               $<TARGET_OBJECTS:service_l0_objects>
)
target_compile_options(calrun PUBLIC "$<$<CONFIG:RELEASE>:-fPIE>")
target_link_options(calrun PUBLIC "$<$<CONFIG:RELEASE>:-pie>")

install(TARGETS calrun
        RUNTIME
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(calrun ${common_library_dependencies})

if(ENABLE_CALLSTACK_DUMPING)
  target_link_options(calrun PUBLIC -rdynamic)
endif()

add_subdirectories()
