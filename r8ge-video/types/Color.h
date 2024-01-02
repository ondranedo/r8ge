#ifndef R8GE_COLOR_H
#define R8GE_COLOR_H

#include <cstdint>
#include <string>

namespace r8ge {
    using coord_pixel = uint16_t;
    using coord_float = float;
    using texture_coord = float;

    struct ColorRGB {
        uint32_t r : 8;
        uint32_t g : 8;
        uint32_t b : 8;

        ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b);
        explicit ColorRGB(uint32_t rgba);
    }__attribute__((packed));

    struct ColorRGBA : public ColorRGB {
        ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a);
        ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b);
        ColorRGBA(const ColorRGB& rgb);
        explicit ColorRGBA(uint32_t rgba);

        uint32_t a : 8;
    };
}

#endif//!R8GE_COLOR_H
