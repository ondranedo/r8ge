#ifndef R8GE_TYPES_H
#define R8GE_TYPES_H

#include <cstdint>
#include <string>

namespace r8ge {
    using coord_pixel = uint16_t;
    using coord_float = float;

    struct Color32 {
        uint32_t r : 8;
        uint32_t g : 8;
        uint32_t b : 8;
        uint32_t a : 8;

        Color32(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a);
        Color32(uint8_t _r, uint8_t _g, uint8_t _b);
        explicit Color32(uint32_t rgba);
    };

    namespace Type {
        enum Basic {
            VOID,
            UINT8,UINT16,UINT32,UINT64,
            INT8,INT16,INT32,INT64,
            FLOAT, DOUBLE
        };

        std::string to_string(Basic type);
        size_t size(Basic type);
    }
}

#endif//!R8GE_COLOR_H
