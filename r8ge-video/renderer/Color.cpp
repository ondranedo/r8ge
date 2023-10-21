#include "Color.h"

namespace r8ge {
    Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {}
    Color::Color(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b), a(0xFF) {}
    Color::Color(uint32_t rgba){
        if(rgba <= 0x00FFFFFF) {
            rgba <<= 8;
            rgba |= 0xFF;
        }

        r = (rgba >> 24) & 0xFF;
        g = (rgba >> 16) & 0xFF;
        b = (rgba >> 8) & 0xFF;
        a = rgba & 0xFF;
    }
}