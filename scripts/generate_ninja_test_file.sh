#!/bin/bash

#
# Copyright (C) 2023 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

if [ $# -lt 1 ]
then
    echo "[ERROR]: Please pass selected configuration."
    exit -1
fi

python3 ./run_blackbox_tests.py --all-configs-path ./l0_blackbox_runner_configs.yml --selected-config $1 --ninja-output l0_blackbox_$1.ninja
