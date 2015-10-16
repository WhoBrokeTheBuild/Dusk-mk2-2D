cmake_minimum_required (VERSION 2.6)

project(TestApp)

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

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(
    ./
    ${CMAKE_SOURCE_DIR}/Engine/
)

set(EXECUTABLE_NAME "TestApp")
add_executable(
    ${EXECUTABLE_NAME}
    TestApp.h
    TestApp.cpp
    Main.cpp
)

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_BINARY_DIR}/Build/libdusk)

set(DUSK_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/Libraries)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

if(DUSK_OS_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_ROOT ${DUSK_LIBRARY_DIR}/SFML)
    find_package(SFML 2 REQUIRED system window graphics network audio)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()

    set(LUA_ROOT ${DUSK_LIBRARY_DIR}/lua)
    find_path(
        LUA_INCLUDE_DIR lua.h
        PATHS ${LUA_ROOT}
        PATH_SUFFIXES include
        REQUIRED
    )
    find_library(
        LUA_LIBRARIES lua
        PATHS ${LUA_ROOT}
        PATH_SUFFIXES ${ARCH_LIB_DIR}
    )
    include_directories(${LUA_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${LUA_LIBRARIES})
else()
    find_package(SFML 2 REQUIRED system window graphics network audio)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    endif()

    find_package(Lua51 REQUIRED)
    if (LUA_FOUND)
        include_directories(${LUA_INCLUDE_DIR})
        target_link_libraries(${EXECUTABLE_NAME} ${LUA_LIBRARIES})
    endif()
endif()

include_directories(${DUSK_LIBRARY_DIR}/RapidXML/include)
