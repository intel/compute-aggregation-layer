#!/usr/bin/env bash

#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set -ex

get_compute_aggregation_layer_version() {
    CAL_VERSION_MAJOR="0"
    CAL_VERSION_MINOR="0"
    CAL_VERSION_BUILD="${CAL_VERSION_BUILD:-0}"

    CAL_DEB_MODEL_LINK=""
    CAL_RPM_MODEL_LINK=""
    if [ "${COMPONENT_MODEL}" != "ci" ]; then
        CAL_DEB_MODEL_LINK="~${COMPONENT_MODEL:-unknown}${BUILD_ID:-0}"
        CAL_RPM_MODEL_LINK=".${COMPONENT_MODEL:-unknown}${BUILD_ID:-0}"
    fi
}
