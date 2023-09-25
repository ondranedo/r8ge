#ifndef R8GE_CORE_H
#define R8GE_CORE_H

#ifdef linux
    #define R8GE_LINUX
#elif _WIN32
    #define R8GE_WINDOWS
#else//!_WIN32
    #error "Unknown/Unsupported platform"
#endif//!linux

#if defined(R8GE_WINDOWS) && defined(R8GE_SHARED)
    #ifdef R8GE_CORE_BUILD
        #define R8GE_API __declspec((__dllexport))
    #else
        #define R8GE_API __declspec((__dllimport))
    #endif//!R8GE_CORE_BUILD
#else
    #define R8GE_API extern
#endif//!R8GE_WINDOWS




#endif//!R8GE_CORE_H
