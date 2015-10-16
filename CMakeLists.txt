cmake_minimum_required (VERSION 2.6)

include(${CMAKE_SOURCE_DIR}/CMake/TargetArch.cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)

add_subdirectory(Engine)
add_subdirectory(TestApp)
