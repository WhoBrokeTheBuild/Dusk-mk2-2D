#ifndef DUSK_UTILITY_PLATFORM_HPP
#define DUSK_UTILITY_PLATFORM_HPP

// Platform Detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) && !defined(__GNUC__)

#define DUSK_OS_WINDOWS

#elif defined(__unix__) || defined(__posix__) || defined(linux) || defined(__linux__)

#define DUSK_OS_LINUX

#elif defined(__APPLE__)

#define DUSK_OS_MAC

#elif defined(__ANDROID__)

#define DUSK_OS_ANDROID

#endif

// Configuration Detection
#if defined(_DEBUG) || defined(DEBUG)

#define DUSK_DEBUG_BUILD

#elif defined(_RELEASE) || defined(RELEASE)

#define DUSK_RELEASE_BUILD

#endif

#endif // DUSK_UTILITY_PLATFORM_HPP