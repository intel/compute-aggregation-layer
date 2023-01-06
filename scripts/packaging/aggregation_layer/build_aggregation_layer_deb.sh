#!/usr/bin/env bash

#
# Copyright (C) 2022-2023 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set -ex

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
REPO_DIR="$( cd "$( dirname "${DIR}/../../../../" )" && pwd )"

BUILD_DIR="${REPO_DIR}/../build_aggregation_layer"
OS_TYPE="${OS_TYPE:-ubuntu_20.04}"
SPEC_FILE="${SPEC_FILE:-ubuntu}"

BRANCH_SUFFIX="$( cat ${REPO_DIR}/.branch )"

ENABLE_AGGREGATION_LAYER="${ENABLE_AGGREGATION_LAYER:-1}"
if [ "${ENABLE_AGGREGATION_LAYER}" == "0" ]; then
    exit 0
fi

LOG_CCACHE_STATS="${LOG_CCACHE_STATS:-0}"

export BUILD_ID="${BUILD_ID:-1}"
export CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Release}"
export DO_NOT_RUN_AUB_TESTS="${DO_NOT_RUN_AUB_TESTS:-FALSE}"

source "${REPO_DIR}/scripts/packaging/${BRANCH_SUFFIX}/aggregation_layer/aggregation_layer.sh"

get_compute_aggregation_layer_version   # CAL_VERSION_MAJOR CAL_VERSION_MINOR CAL_TAG

export CAL_VERSION_MAJOR
export CAL_VERSION_MINOR
export CAL_TAG

PKG_VERSION="${CAL_VERSION_MAJOR}.${CAL_VERSION_MINOR}.${CAL_VERSION_BUILD}${CAL_DEB_MODEL_LINK}"

if [ "${CMAKE_BUILD_TYPE}" != "Release" ]; then
    PKG_VERSION="${PKG_VERSION}+$(echo "$CMAKE_BUILD_TYPE" | tr '[:upper:]' '[:lower:]')1"
fi

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR/debian

COPYRIGHT="${REPO_DIR}/scripts/packaging/${BRANCH_SUFFIX}/aggregation_layer/${SPEC_FILE}/copyright"
CONTROL="${REPO_DIR}/scripts/packaging/${BRANCH_SUFFIX}/aggregation_layer/${SPEC_FILE}/control"
SHLIBS="${REPO_DIR}/scripts/packaging/${BRANCH_SUFFIX}/aggregation_layer/${SPEC_FILE}/shlibs.local"

cp -pR ${REPO_DIR}/scripts/packaging/aggregation_layer/${SPEC_FILE}/debian/* $BUILD_DIR/debian/
cp $COPYRIGHT $BUILD_DIR/debian/
cp $CONTROL $BUILD_DIR/debian/
if [ -f "${SHLIBS}" ]; then
    cp $SHLIBS $BUILD_DIR/debian/
fi

#needs a top level CMAKE file
cat << EOF | tee $BUILD_DIR/CMakeLists.txt
cmake_minimum_required (VERSION 3.2 FATAL_ERROR)

project(compute_aggregation_layer)

add_subdirectory($REPO_DIR aggregation_layer)
EOF

(
    cd $BUILD_DIR
    if [ "${LOG_CCACHE_STATS}" == "1" ]; then
        ccache -z
    fi
    export DEB_BUILD_OPTIONS="nodocs notest nocheck"
    export DH_VERBOSE=1
    if [ "${CMAKE_BUILD_TYPE}" != "Release" ]; then
      export DH_INTERNAL_BUILDFLAGS=1
    fi

    dch -v ${PKG_VERSION} -m "build $PKG_VERSION" -b
    ulimit -n 65535 || true
    dpkg-buildpackage -j`nproc --all` -us -uc -b -rfakeroot
    sudo dpkg -i --force-depends ../*.deb
    if [ "${LOG_CCACHE_STATS}" == "1" ]; then
        ccache -s
        ccache -s | grep 'cache hit rate' | cut -d ' ' -f 4- | xargs -I{} echo Aggregation Layer {} >> $REPO_DIR/../output/logs/ccache.log
    fi
)

mkdir -p ${REPO_DIR}/../output/dbgsym

mv ${REPO_DIR}/../*.deb ${REPO_DIR}/../output/
find ${REPO_DIR}/.. -maxdepth 1 -name \*.ddeb -type f -print0 | xargs -0r mv -t ${REPO_DIR}/../output/dbgsym/
