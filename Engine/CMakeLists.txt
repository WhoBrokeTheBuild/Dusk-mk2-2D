cmake_minimum_required (VERSION 2.6)

project(Dusk)

set(DUSK_LIBRARY_NAME dusk)

file(GLOB_RECURSE DUSK_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/Dusk/*.hpp
    ${PROJECT_SOURCE_DIR}/Dusk/*.cpp)

include_directories(${PROJECT_SOURCE_DIR})
add_library(${DUSK_LIBRARY_NAME} STATIC ${DUSK_SOURCE_FILES})

set_target_properties(${DUSK_LIBRARY_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${DUSK_LIBRARY_NAME})

include(${CMAKE_SOURCE_DIR}/CMake/DuskDependencies.cmake)
dusk_dependencies(${DUSK_LIBRARY_NAME} ${CMAKE_SOURCE_DIR})

set(DUSK_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
