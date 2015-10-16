cmake_minimum_required (VERSION 2.6)

project(TestApp)

set(TESTAPP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/TestApp)
set(TESTAPP_EXECUTABLE_NAME "TestApp")

add_definitions(${DUSK_DEFINITIONS})
include_directories(${DUSK_INCLUDE_DIRS})

file(GLOB SOURCE_FILES ${TESTAPP_SOURCE_DIR}/*.h)
file(GLOB HEADER_FILES ${TESTAPP_SOURCE_DIR}/*.cpp)
add_executable(${TESTAPP_EXECUTABLE_NAME} ${SOURCE_FILES} ${HEADER_FILES})

message(STATUS ${CMAKE_BINARY_DIR}/Engine)
find_library(dusk
            PATHS ${CMAKE_BINARY_DIR}/Engine
            PATH_SUFFIXES Debug Release)
target_link_libraries(${TESTAPP_EXECUTABLE_NAME} ${DUSK_LIBRARY_PATH})
