#ifndef R8GE_GLCONVERTOR_H
#define R8GE_GLCONVERTOR_H

#include <GL/glew.h>
#include "../../renderer/Types.h"

namespace r8ge {
    namespace video {
        class GLConvertor {
        public:
            static GLenum convertToGLType(Type::Basic type);
        };
    }
}

#endif//!R8GE_GLCONVERTOR_H
