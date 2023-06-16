cmake_minimum_required(VERSION 3.26.4)

project(clangdCrash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
    "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
# Default to C++ extensions being off. Clang's modules support have trouble with
# extensions right now.
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")
file(GLOB_RECURSE MODULES CONFIGURE_DEPENDS "*.cppm")

add_executable(clangdCrash main.cpp)
target_sources(clangdCrash PRIVATE FILE_SET cxx_modules TYPE CXX_MODULES FILES
                                   module.cppm)

add_library(clangdCrashPrecomp empty.cpp)

set_target_properties(
  clangdCrashPrecomp
  PROPERTIES EXPERIMENTAL_CXX_MODULE_DYNDEP 0
             EXPERIMENTAL_CXX_MODULE_CMAKE_API 0
             CXX_SCAN_FOR_MODULES 0)

target_precompile_headers(
  clangdCrashPrecomp PUBLIC
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/precompiled.hpp>")

target_precompile_headers(clangdCrash REUSE_FROM clangdCrashPrecomp)

set_target_properties(clangdCrash PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             "${CMAKE_BINARY_DIR}")

target_include_directories(clangdCrash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
