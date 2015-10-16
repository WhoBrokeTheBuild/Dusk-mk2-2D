
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

function(dusk_dependencies executable dusk_root)

    if(DUSK_OS_WINDOWS)
        set(SFML_STATIC_LIBRARIES TRUE)
        set(SFML_ROOT ${DUSK_LIBRARIES_DIR}/SFML)

        set(LUA_ROOT ${DUSK_LIBRARIES_DIR}/lua)
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
        target_link_libraries(${executable} ${LUA_LIBRARIES})
    else()
        find_package(Lua51 REQUIRED)
        if (LUA_FOUND)
            include_directories(${LUA_INCLUDE_DIR})
            target_link_libraries(${executable} ${LUA_LIBRARIES})
        endif()
    endif()

    find_package(SFML 2 REQUIRED system window graphics network audio)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${executable} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()

    include_directories(${DUSK_LIBRARIES_DIR}/RapidXML/include)

endfunction()
