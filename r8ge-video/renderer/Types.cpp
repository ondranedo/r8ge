#include "Types.h"

namespace r8ge {
    Color32::Color32(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {}
    Color32::Color32(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b), a(0xFF) {}
    Color32::Color32(uint32_t rgba){
        if(rgba <= 0x00FFFFFF) {
            rgba <<= 8;
            rgba |= 0xFF;
        }

        r = (rgba >> 24) & 0xFF;
        g = (rgba >> 16) & 0xFF;
        b = (rgba >> 8) & 0xFF;
        a = rgba & 0xFF;
    }

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
}