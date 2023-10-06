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
    #define R8GE_API
#endif//!R8GE_WINDOWS

#include <cassert>

#include "utility/StringFormat.h"

namespace r8ge {
    R8GE_API void assertImpl(const char * expr, unsigned long line, const char * fun, const char *msg, const utility::StringFormat::ValidList& list);
}

#define R8GE_ASSERT(expr, msg, ...) if(!(expr)) r8ge::assertImpl(#expr, __LINE__, __PRETTY_FUNCTION__, msg, {__VA_ARGS__})


#endif//!R8GE_CORE_H
