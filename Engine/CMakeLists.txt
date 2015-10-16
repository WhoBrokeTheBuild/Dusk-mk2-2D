cmake_minimum_required (VERSION 2.6)

project (Engine)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(DUSK_OS_WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(DUSK_OS_LINUX TRUE)
endif()

target_architecture(CMAKE_ARCH)
if(${CMAKE_ARCH} STREQUAL "x86_64")
    set(ARCH_DIR "x64")
elseif(${CMAKE_ARCH} STREQUAL "i386")
    set(ARCH_DIR "x86")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(DUSK2D_VERSION_MAJOR 0)
set(DUSK2D_VERSION_MINOR 5)
configure_file(
    Dusk/Config.hpp.in
    Dusk/Config.hpp
)

set(LIBRARY_NAME "Dusk")
add_library(
    ${LIBRARY_NAME}

    Dusk/Audio/AudioSystem.hpp
    Dusk/Audio/AudioSystem.cpp
    Dusk/Audio/Music.hpp
    Dusk/Audio/Music.cpp
    Dusk/Audio/Sound.hpp
    Dusk/Audio/Sound.cpp

    Dusk/Collections/ArrayList.hpp
    Dusk/Collections/Map.hpp

    Dusk/Events/Callbacks.hpp
    Dusk/Events/Callbacks.cpp
    Dusk/Events/Delegate.hpp
    Dusk/Events/Event.hpp
    Dusk/Events/Event.cpp
    Dusk/Events/EventDispatcher.hpp
    Dusk/Events/EventDispatcher.cpp

    Dusk/Geometry/Vector2.hpp
    Dusk/Geometry/Rect.hpp

    Dusk/Graphics/Color.hpp
    Dusk/Graphics/Font.hpp
    Dusk/Graphics/Font.cpp
    Dusk/Graphics/GraphicsContext.hpp
    Dusk/Graphics/GraphicsContext.cpp
    Dusk/Graphics/GraphicsSystem.hpp
    Dusk/Graphics/GraphicsSystem.cpp
    Dusk/Graphics/Sprite.hpp
    Dusk/Graphics/Sprite.cpp
    Dusk/Graphics/TextBuffer.hpp
    Dusk/Graphics/TextBuffer.cpp
    Dusk/Graphics/Texture.hpp
    Dusk/Graphics/Texture.cpp

    Dusk/Input/InputSystem.hpp
    Dusk/Input/InputSystem.cpp
    Dusk/Input/Keyboard.hpp
    Dusk/Input/Keyboard.cpp
    Dusk/Input/Mapped.hpp
    Dusk/Input/Mapped.cpp
    Dusk/Input/Mouse.hpp
    Dusk/Input/Mouse.cpp

)

set(DUSK_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/Libraries)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

if(DUSK_OS_WINDOWS)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_ROOT ${DUSK_LIBRARY_DIR}/SFML)
    find_package(SFML 2 REQUIRED system window graphics network audio)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()

    set(LUA_DIR ${DUSK_LIBRARY_DIR}/lua/${ARCH_DIR})
    message(STATUS ${LUA_DIR})
    find_package(Lua 5.1)
    if (LUA_FOUND)
        include_directories(${LUA_INCLUDE_DIR})
        target_link_libraries(${LIBRARY_NAME} ${LUA_LIBRARY})
    endif()
else()
    find_package(SFML 2 REQUIRED system window graphics network audio)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${LIBRARY_NAME} ${SFML_LIBRARIES})
    endif()

    find_package(Lua 5.1)
    if (LUA_FOUND)
        include_directories(${LUA_INCLUDE_DIR})
        target_link_libraries(${LIBRARY_NAME} ${LUA_LIBRARY})
    endif()
endif()
