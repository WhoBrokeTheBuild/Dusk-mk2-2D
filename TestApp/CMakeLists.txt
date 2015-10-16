cmake_minimum_required (VERSION 2.6)

project(TestApp)

set(TESTAPP_EXECUTABLE_NAME "TestApp")

file(GLOB_RECURSE TESTAPP_SOURCE_FILES
        ${TESTAPP_SOURCE_DIR}/*.h
        ${TESTAPP_SOURCE_DIR}/*.cpp)

add_executable(${TESTAPP_EXECUTABLE_NAME} ${TESTAPP_SOURCE_FILES})

include_directories(${DUSK_INCLUDE_DIRS})
dusk_dependencies(${TESTAPP_EXECUTABLE_NAME} ${CMAKE_SOURCE_DIR})
