#include "Color.h"

namespace r8ge {
    ColorRGBA::ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : ColorRGB(_r, _g, _b), a(_a) {}
    ColorRGBA::ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b) : ColorRGB(_r, _g, _b), a(0xFF) {}
    ColorRGBA::ColorRGBA(uint32_t rgba)
    : ColorRGB(rgba <= 0x00FFFFFF?rgba:rgba>>8), a(rgba <= 0x00FFFFFF?0xFF:(rgba&0xFF))
    {}

    ColorRGBA::ColorRGBA(const ColorRGB &rgb) : ColorRGB(rgb), a(0xFF){}

    ColorRGB::ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}

    ColorRGB::ColorRGB(uint32_t rgb) :
    r((rgb >> 16) & 0xFF),g((rgb >> 8) & 0xFF),b(rgb & 0xFF)
    {}

    ColorRGB_n::ColorRGB_n(float _r, float _g, float _b)
    : r(_r), g(_g), b(_b){}

    ColorRGB_n::ColorRGB_n(ColorRGB rgba)
    : r(static_cast<float>(rgba.r)/255.0f),
      g(static_cast<float>(rgba.g)/255.0f),
      b(static_cast<float>(rgba.b)/255.0f){}

    std::vector<uint8_t> ColorRGB_n::getRawData() const {
        union {
            struct { float r, g, b;};
            uint8_t _raw[sizeof(float)*3];
        } convertor = {r, g, b};
        return {convertor._raw, convertor._raw + sizeof(float)*3};
    }

    size_t ColorRGB_n::getSize() const {
        return 0;
    }
}