#ifndef R8GE_GLCONVERTOR_H
#define R8GE_GLCONVERTOR_H

#include <GL/glew.h>
#include "../../types/Primitives.h"

namespace r8ge {
    namespace video {
        class GLConvertor {
        public:
            static GLenum convertToGLType(Primitive type);
        };
    }
}

#endif//!R8GE_GLCONVERTOR_H
