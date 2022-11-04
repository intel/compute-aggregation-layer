#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_definitions(-DCAL_LOGGER_NAME=C)
add_definitions(-Dmockable=)

add_subdirectories()

add_library(cal SHARED # acts as ICD
            ${CMAKE_CURRENT_SOURCE_DIR}/icd_platform.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/icd_global_state.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/icd_ocl.cpp
            ${cal_source_root_dir}/shared/sys.cpp
            ${cal_source_root_dir}/shared/usm.cpp
            ${cal_source_root_dir}/shared/utils.cpp
            ${generated_dir}/generated_icd_ocl.cpp
            ${generated_dir}/generated_rpc_messages_ocl.cpp
            $<TARGET_OBJECTS:icd_l0_objects>
)

target_link_libraries(cal ${common_library_dependencies})

install(TARGETS cal
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
