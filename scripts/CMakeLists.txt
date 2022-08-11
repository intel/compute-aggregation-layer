#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cal.icd ${cal_binary_root_dir} COPYONLY)

install(FILES "cal.icd" DESTINATION ${CAL_OPT_INSTALL_PATH})
install(PROGRAMS
        "packaging/aggregation_layer/cal_setvars.sh"
        "packaging/aggregation_layer/cal_setvars_l0.sh"
        "packaging/aggregation_layer/cal_setvars_ocl.sh"
        DESTINATION ${CAL_OPT_INSTALL_PATH}
)

add_subdirectories()
