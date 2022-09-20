#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

add_library(OpenCL SHARED ${generated_dir}/generated_stub_lib_ocl.cpp)
add_library(ze_loader SHARED ${generated_dir}/generated_stub_lib_level_zero.cpp)
set_target_properties(ze_loader PROPERTIES VERSION 1)

set_target_properties(OpenCL
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stub_libs"
)

set_target_properties(ze_loader
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stub_libs"
)

add_subdirectories()

option(VERIFY_GENERATED_CACHE "Verifies if cached generated files are up to date and in synch with source files" OFF)
if(${VERIFY_GENERATED_CACHE})
  include(FindPythonInterp)
  set(generated_comparison_dir ${CMAKE_CURRENT_BINARY_DIR}/generated_comparison_dir)
  file(MAKE_DIRECTORY ${generated_comparison_dir})
  add_custom_command(OUTPUT verify_generated_cache.generate
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source
                     COMMENT "Generating fresh files to temporary directory : ${CMAKE_CURRENT_SOURCE_DIR}/source"
                     COMMAND ${PYTHON_EXECUTABLE} generate.py ${generated_comparison_dir}
                     VERBATIM
  )

  add_custom_command(OUTPUT verify_generated_cache.compare
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source
                     COMMENT "Comparing freshly generated files against temporary directory : ${CMAKE_CURRENT_SOURCE_DIR}/source"
                     COMMAND ${PYTHON_EXECUTABLE} verify.py ${generated_comparison_dir} ${CMAKE_CURRENT_SOURCE_DIR}/cached
                     DEPENDS verify_generated_cache.generate
                     VERBATIM
  )

  add_custom_target(verify_generated_cache ALL
                    DEPENDS verify_generated_cache.compare
  )
endif()