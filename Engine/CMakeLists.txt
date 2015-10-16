cmake_minimum_required (VERSION 2.6)

project(Dusk)
set(DUSK_LIBRARY_NAME "dusk")

configure_file(${DUSK_SOURCE_DIR}/Config.hpp.in
               ${DUSK_SOURCE_DIR}/Config.hpp)

include_directories(${DUSK_PROJECT_DIR})

file(GLOB SOURCE_FILES ${DUSK_SOURCE_DIR}/*/*.cpp)
file(GLOB HEADER_FILES ${DUSK_SOURCE_DIR}/*/*.hpp)
add_library(${DUSK_LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(${DUSK_LIBRARY_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${DUSK_LIBRARY_NAME})

if(DUSK_OS_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_ROOT ${DUSK_LIBRARY_DIR}/SFML)

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
    target_link_libraries(${DUSK_LIBRARY_NAME} ${LUA_LIBRARIES})
else()
    find_package(Lua51 REQUIRED)
    if (LUA_FOUND)
        include_directories(${LUA_INCLUDE_DIR})
        target_link_libraries(${DUSK_LIBRARY_NAME} ${LUA_LIBRARIES})
    endif()
endif()

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${DUSK_LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

include_directories(${DUSK_LIBRARY_DIR}/RapidXML/include)

set(DUSK_INCLUDE_DIRS ${DUSK_PROJECT_DIR}
                      ${SFML_INCLUDE_DIR}
                      ${LUA_INCLUDE_DIR}
                      ${DUSK_LIBRARY_DIR}/RapidXML/include
    CACHE INTERNAL "Dusk: Include Directories" FORCE)
