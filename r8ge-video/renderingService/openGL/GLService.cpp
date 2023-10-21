#include "GLService.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        GLService::GLService() {
            R8GE_LOG("GL Service created");
        }
        GLService::~GLService() {
            R8GE_LOG("GL Service destroyed");
        }

        void GLService::init() {

        }

        void GLService::exit() {

        }
    }
}