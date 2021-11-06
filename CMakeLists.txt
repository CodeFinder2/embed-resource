cmake_minimum_required(VERSION 3.12)
project("embed_resource" LANGUAGES CXX VERSION 1.0.0
  DESCRIPTION "Embed binary or resource files (e.g., textures, images, or shader files) in C++11"
  HOMEPAGE_URL "https://github.com/CodeFinder2/embed-resource")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

function(embed_resources out_var)
  set(result)
  set(out_dir "${PROJECT_BINARY_DIR}/embed_resource")
  file(MAKE_DIRECTORY ${out_dir})
  set(out_hdr "${out_dir}/resources.h")
  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${out_hdr})
  list(APPEND ADDITIONAL_CLEAN_FILES ${out_hdr})
  foreach(in_f ${ARGN})
    file(RELATIVE_PATH src_f ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/${in_f}")
    set(out_f "${out_dir}/${in_f}.cpp")
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${out_f})
    get_filename_component(out_f_dir "${out_f}" DIRECTORY)
    add_custom_command(OUTPUT ${out_f}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${out_f_dir}"
        COMMAND embed_resource_builder "${out_f}" "${src_f}" "${out_hdr}"
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
target_compile_definitions(embed_resource_builder PRIVATE CMAKE_VERSION="${CMAKE_VERSION}")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
            ${PROJECT_BINARY_DIR})

# Optionally, build the example application:
option(EMBED_RESOURCE_BUILD_EXAMPLE "Build the example?" OFF)
if(EMBED_RESOURCE_BUILD_EXAMPLE)
  embed_resources(MyExampleResources example/data.txt)
  add_executable(${PROJECT_NAME}_example example/main.cpp ${MyExampleResources})
  target_link_libraries(${PROJECT_NAME}_example ${PROJECT_NAME})
endif()
