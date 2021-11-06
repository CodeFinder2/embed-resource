cmake_minimum_required(VERSION 3.12)
project("embed_resource" VERSION 1.0.0
  DESCRIPTION "Embed binary or resource files (e.g., textures, images, or GLSL shader files) in C++11"
  HOMEPAGE_URL "https://github.com/CodeFinder2/embed-resource")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

function(embed_resources out_var)
  set(result)
  foreach(in_f ${ARGN})
    file(RELATIVE_PATH src_f ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/${in_f}")
    set(out_f "${PROJECT_BINARY_DIR}/${in_f}.c")
    get_filename_component(out_f_dir "${out_f}" DIRECTORY)
    add_custom_command(OUTPUT ${out_f}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${out_f_dir}"
        COMMAND embed_resource_builder "${out_f}" "${src_f}"
        DEPENDS "${in_f}" embed_resource_builder
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Building binary file for embedding ${out_f}"
        VERBATIM)
    list(APPEND result "${out_f}")
  endforeach()
  set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

add_executable(embed_resource_builder src/embed_resource.cpp)
target_compile_features(embed_resource_builder INTERFACE cxx_std_11)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
