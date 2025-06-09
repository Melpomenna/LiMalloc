cmake_minimum_required(VERSION 3.19...4.0)

enable_testing()

project(Memory VERSION 1.0.0 LANGUAGES C CXX)

set(BENCHMARK_ENABLE_GTEST_TESTS  OFF CACHE BOOL "Whether to install benchmark")
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable tests")
set(BENCHMARK_INSTALL_DOCS OFF CACHE BOOL "Disable docs")

if (MSVC)
    set(BENCHMARK_ENABLE_LTO   ON CACHE BOOL "Enable LTO")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}:${CMAKE_MODULE_PATH}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/WorkFolder)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/WorkFolder)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/WorkFolder)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/WorkFolder)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

include(GlobalCompileOptions)
include(InstallLibrary)
SetGlobalCompileOptions()
InstallLibrary()

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)

add_custom_target(
    run_benchmarks
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/WorkFolder/Benchmarks
    COMMENT "Executing benchmark script"
    OUTPUT Unused
)