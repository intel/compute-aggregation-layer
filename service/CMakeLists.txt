#
# Copyright (C) 2022 Intel Corporation
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
               ${CMAKE_CURRENT_SOURCE_DIR}/service.cpp
               ${cal_source_root_dir}/shared/sys.cpp
               ${cal_source_root_dir}/shared/usm.cpp
               ${cal_source_root_dir}/shared/utils.cpp
               ${generated_dir}/generated_service_ocl.cpp
               ${generated_dir}/generated_service_level_zero.cpp
)
install(TARGETS calrun
        RUNTIME
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(calrun ${common_library_dependencies})

add_subdirectories()

