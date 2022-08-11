#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

cmake_minimum_required(VERSION 3.12)

string(REPLACE " " ";" src_list "${SRC}")
string(REPLACE "\\;" " " src_list "${src_list}")

list(LENGTH src_list num_src)

set(generated_output
    "/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// This is a generated file, please don't hand-modify
#pragma once

#include <cstddef>

struct FileAsStr{
    const char *fname;
    size_t len;
    const char *src;
};

static const FileAsStr ${VAR}[${num_src}] = {"
)

foreach(src_fname ${src_list})
  file(READ ${src_fname} contents)
  string(LENGTH "${contents}" contents_len)
  string(REPLACE "${SRC_ROOT}/" "" relative_path ${src_fname})
  string(REPLACE "${SRC_ROOT}" "" relative_path ${relative_path})
  set(generated_output "${generated_output}
      { \"${relative_path}\", ${contents_len}, R\"===|===(${contents})===|===\"},"
  )
endforeach()

set(generated_output "${generated_output}
};"
)

set(dst_fname ${DST})
file(WRITE ${dst_fname} "${generated_output}")
