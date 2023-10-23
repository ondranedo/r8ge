#include "GLConvertor.h"

namespace r8ge {
    namespace video {

        GLenum GLConvertor::convertToGLType(Type::Basic type) {
            switch(type) {
                case Type::VOID: return GL_NONE;
                case Type::UINT8: return GL_UNSIGNED_BYTE;
                case Type::UINT16: return GL_UNSIGNED_SHORT;
                case Type::UINT32: return GL_UNSIGNED_INT;
                case Type::UINT64: return GL_UNSIGNED_INT64_ARB;
                case Type::INT8: return GL_BYTE;
                case Type::INT16: return GL_SHORT;
                case Type::INT32: return GL_INT;
                case Type::INT64: return GL_INT64_ARB;
                case Type::FLOAT: return GL_FLOAT;
                case Type::DOUBLE: return GL_DOUBLE;
            }

            return GL_NONE;
        }
    }
}