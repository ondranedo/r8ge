#include "Types.h"

namespace r8ge {
    ColorRGBA::ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : ColorRGB(_r, _g, _b), a(_a) {}
    ColorRGBA::ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b) : ColorRGB(_r, _g, _b), a(0xFF) {}
    ColorRGBA::ColorRGBA(uint32_t rgba)
    : ColorRGB(rgba <= 0x00FFFFFF?rgba:rgba>>8), a(rgba <= 0x00FFFFFF?0xFF:(rgba&0xFF))
    {}

    ColorRGBA::ColorRGBA(const ColorRGB &rgb) : ColorRGB(rgb), a(0xFF){}

    std::string Type::to_string(Type::Basic type) {
        switch (type) {
            case VOID: return "VOID";
            case UINT8: return "UINT8";
            case UINT16: return "UINT16";
            case UINT32: return "UINT32";
            case UINT64: return "UINT64";
            case INT8: return "INT8";
            case INT16: return "INT16";
            case INT32: return "INT32";
            case INT64: return "INT64";
            case FLOAT: return "FLOAT";
            case DOUBLE: return "DOUBLE";
        }

        return "UNKNOWN";
    }

    size_t Type::size(Type::Basic type) {
        switch (type) {
            case VOID: return 0;
            case UINT8: return sizeof(uint8_t);
            case UINT16: return sizeof(uint16_t);
            case UINT32: return sizeof(uint32_t);
            case UINT64: return sizeof(uint64_t);
            case INT8: return sizeof(int8_t);
            case INT16: return sizeof(int16_t);
            case INT32: return sizeof(int32_t);
            case INT64: return sizeof(int64_t);
            case FLOAT: return sizeof(float);
            case DOUBLE: return sizeof(double);
        }

        return 0;
    }

    ColorRGB::ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}

    ColorRGB::ColorRGB(uint32_t rgb) :
    r((rgb >> 16) & 0xFF),g((rgb >> 8) & 0xFF),b(rgb & 0xFF)
    {}
}