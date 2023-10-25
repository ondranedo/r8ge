#ifndef R8GE_COLOR_H
#define R8GE_COLOR_H

#include <cstdint>
#include <string>
#include <vector>

namespace r8ge {
    using coord_pixel = uint16_t;
    using coord_float = float;

    struct ColorRGB {
        uint32_t r : 8;
        uint32_t g : 8;
        uint32_t b : 8;

        ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b);
        explicit ColorRGB(uint32_t rgba);
    };

    struct ColorRGBA : public ColorRGB {
        ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a);
        ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b);
        ColorRGBA(const ColorRGB& rgb);
        explicit ColorRGBA(uint32_t rgba);

        uint32_t a : 8;
    };

    struct ColorRGB_n {
        float r;
        float g;
        float b;

        std::vector<uint8_t> getRawData() const;
        size_t getSize() const;

        ColorRGB_n(float _r, float _g, float _b);
        explicit ColorRGB_n(ColorRGB rgba);
    };
}

#endif//!R8GE_COLOR_H
