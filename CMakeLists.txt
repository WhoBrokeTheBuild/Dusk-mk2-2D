cmake_minimum_required (VERSION 2.6)

include(${CMAKE_SOURCE_DIR}/CMake/TargetArch.cmake)

set(DUSK_VERSION_MAJOR 0)
set(DUSK_VERSION_MINOR 5)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

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

set(DUSK_PROJECT_DIR ${CMAKE_SOURCE_DIR}/Engine)
set(DUSK_SOURCE_DIR ${DUSK_PROJECT_DIR}/Dusk)
set(DUSK_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/Libraries)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (DUSK_OS_WINDOWS)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

add_subdirectory(Engine)
add_subdirectory(TestApp)
