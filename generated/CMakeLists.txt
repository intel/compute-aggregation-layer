#
# Copyright (C) 2022-2024 Intel Corporation
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

option(REQUIRE_CACHE_VERIFICATION_DEPENDENCIES "Causes failure of build when the verification of generated cache cannot be performed due to missing dependencies!" OFF)
option(VERIFY_GENERATED_CACHE_IF_POSSIBLE "Verifies if cached generated files are up to date and in synch with source files" ON)

function(find_mako python_interp ret)
  execute_process(
                  COMMAND ${python_interp} -m pip show mako
                  RESULT_VARIABLE mako_check_exit_code
                  OUTPUT_QUIET
  )

  if(${mako_check_exit_code} EQUAL 0)
    set(${ret} 1 PARENT_SCOPE)
  endif()
endfunction()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.20)
  set(Python3_FIND_UNVERSIONED_NAMES "FIRST")
endif()
include(FindPython3)
if(NOT Python3_FOUND)
  message("Failed to find python3 - won't verify generated files")
  if(${REQUIRE_CACHE_VERIFICATION_DEPENDENCIES})
    message(FATAL_ERROR "Verification of generated files requested but can't be performed - missing python3")
  endif()
else()
  find_mako(${Python3_EXECUTABLE} Python3_mako_FOUND)
  if(NOT Python3_mako_FOUND)
    message("Failed to find mako module for python3 - won't verify generated files")
    if(${REQUIRE_CACHE_VERIFICATION_DEPENDENCIES})
      message(FATAL_ERROR "Verification of generated files requested but can't be performed - missing mako module for python3")
    endif()
  else()
    if(${VERIFY_GENERATED_CACHE_IF_POSSIBLE})
      message("Found python3+mako - will perform verification of generated files")
      set(generated_comparison_dir ${CMAKE_CURRENT_BINARY_DIR}/generated_comparison_dir)
      file(MAKE_DIRECTORY ${generated_comparison_dir})
      add_custom_command(OUTPUT verify_generated_cache.generate
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source
                         COMMENT "Generating fresh files to temporary directory : ${CMAKE_CURRENT_SOURCE_DIR}/source"
                         COMMAND ${Python3_EXECUTABLE} generate.py ${generated_comparison_dir}
                         VERBATIM
      )

      add_custom_command(OUTPUT verify_generated_cache.compare
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source
                         COMMENT "Comparing freshly generated files against temporary directory : ${CMAKE_CURRENT_SOURCE_DIR}/source"
                         COMMAND ${Python3_EXECUTABLE} verify.py ${generated_comparison_dir} ${CMAKE_CURRENT_SOURCE_DIR}/cached
                         DEPENDS verify_generated_cache.generate
                         VERBATIM
      )

      add_custom_target(verify_generated_cache ALL
                        DEPENDS verify_generated_cache.compare
      )
    else()
      message("Skipping verification of generated files => VERIFY_GENERATED_CACHE_IF_POSSIBLE = ${VERIFY_GENERATED_CACHE_IF_POSSIBLE}")
    endif()
  endif()
endif()

set(GENERATED_ICD_SOURCES ${GENERATED_ICD_SOURCES}
    "${generated_dir}/generated_icd_level_zero.cpp"
    "${generated_dir}/generated_icd_ocl.cpp"
)
set(GENERATED_SERVICE_SOURCES ${GENERATED_SERVICE_SOURCES}
    "${generated_dir}/generated_service_level_zero.cpp"
    "${generated_dir}/generated_service_ocl.cpp"
)
set(GENERATED_SHARED_SOURCES ${GENERATED_SHARED_SOURCES}
    "${generated_dir}/generated_rpc_messages_level_zero.cpp"
    "${generated_dir}/generated_rpc_messages_ocl.cpp"
)
add_subdirectories()

add_library(generated_icd OBJECT ${GENERATED_ICD_SOURCES} ${GENERATED_SHARED_SOURCES})
set_property(TARGET generated_icd PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(generated_icd PRIVATE -Dmockable= -DCAL_LOGGER_NAME=C)

add_library(generated_service OBJECT ${GENERATED_SERVICE_SOURCES} ${GENERATED_SHARED_SOURCES})
set_property(TARGET generated_service PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(generated_service PRIVATE -Dmockable= -DCAL_LOGGER_NAME=S)

add_library(generated_ult_icd OBJECT ${GENERATED_ICD_SOURCES} ${GENERATED_SHARED_SOURCES})
set_property(TARGET generated_ult_icd PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(generated_ult_icd PRIVATE -Dmockable=virtual -DCAL_LOGGER_NAME=U)

add_library(generated_ult_service OBJECT ${GENERATED_SERVICE_SOURCES} ${GENERATED_SHARED_SOURCES})
set_property(TARGET generated_ult_service PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(generated_ult_service PRIVATE -Dmockable=virtual -DCAL_LOGGER_NAME=U)

add_library(generated_ult OBJECT ${GENERATED_ICD_SOURCES} ${GENERATED_SERVICE_SOURCES} ${GENERATED_SHARED_SOURCES})
set_property(TARGET generated_ult PROPERTY POSITION_INDEPENDENT_CODE OFF)
target_compile_definitions(generated_ult PRIVATE -Dmockable=virtual -DCAL_LOGGER_NAME=U)
