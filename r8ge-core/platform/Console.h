#ifndef R8GE_CONSOLE_H
#define R8GE_CONSOLE_H

#include <string>
#include <cstdint>

namespace r8ge {
    class Console {
    public:
        struct Color {
            uint8_t r, g, b;
        };

        enum underlined {
            NOT_UNDERLINED,
            UNDERLINE,
            DOUBLE_UNDERLINE
        };

        struct ConsoleParam {
            Color foregroundColor;
            Color backgroundColor;
            bool bold;
            bool italic;
            underlined underline;
            bool blink;
            bool useDefaultForegroundColor;
            bool useDefaultBackgroundColor;
        };

        static void log(const std::string& str);
        static void set(const ConsoleParam& param);
        static void setDefault();
    };
}

#endif//!R8GE_CONSOLE_H
