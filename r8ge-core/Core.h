#ifndef R8GE_CORE_H
#define R8GE_CORE_H

#ifdef __GNUC__
    #define R8GE_LINUX
#elif _MSC_VER
    #define R8GE_WINDOWS
#else//!_WIN32
    #error "Unknown/Unsupported platform"
#endif

#ifdef R8GE_SHARED
    #ifdef R8GE_LINUX
        #ifdef R8GE_CORE_BUILD
            #define R8GE_API __attribute__((visibility("default")))
        #else
            #define R8GE_API
        #endif//!R8GE_CORE_BUILD
    #elif defined(R8GE_WINDOWS) //!R8GE_LINUX
        #ifdef R8GE_CORE_BUILD
            #define R8GE_API __declspec((dllexport))
        #else
            #define R8GE_API __declspec((dllimport))
        #endif
    #endif//!R8GE_WINDOWS
#else
    #define R8GE_API
#endif//!R8GE_SHARED

#pragma region asserts
    #include <cassert>
    #include "utility/StringFormat.h"

    namespace r8ge {
        R8GE_API void assertImpl(std::string_view expr, unsigned long line, std::string_view fun, std::string_view msg, const utility::StringFormat::ValidList& list);
    }

    #define R8GE_ASSERT(expr, msg, ...) if(!(expr)) r8ge::assertImpl(#expr, __LINE__, __PRETTY_FUNCTION__, msg, {__VA_ARGS__})
#pragma endregion



#endif//!R8GE_CORE_H
