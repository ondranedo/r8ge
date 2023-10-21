#ifndef R8GE_COLOR_H
#define R8GE_COLOR_H

#include <cstdint>

namespace r8ge {
    struct Color {
        uint8_t r, g, b, a;

        Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a);
        Color(uint8_t _r, uint8_t _g, uint8_t _b);
        Color(uint32_t rgba);
    };
}

#endif//!R8GE_COLOR_H
