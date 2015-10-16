cmake_minimum_required (VERSION 2.6)

# Includes
include(${CMAKE_SOURCE_DIR}/CMake/TargetArch.cmake)

# Global Defines
set(DUSK_VERSION_MAJOR 0)
set(DUSK_VERSION_MINOR 5)

set(DUSK_LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/Libraries)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

# Prevent In-Source Builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

# Add Custom CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Platform Detection
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(DUSK_OS_WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(DUSK_OS_LINUX TRUE)
endif()

target_architecture(CMAKE_ARCH)
if(${CMAKE_ARCH} STREQUAL "x86_64")
    set(ARCH_LIB_DIR "lib64")
elseif(${CMAKE_ARCH} STREQUAL "i386")
    set(ARCH_LIB_DIR "lib")
endif()

# Remove 'lib' prefix for shared libraries on Windows
if (DUSK_OS_WINDOWS)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# Platform Specific Flags
if(DUSK_OS_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(Engine)
add_subdirectory(TestApp)
