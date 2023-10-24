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
}