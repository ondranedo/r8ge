#include "GLService.h"

#include <r8ge/r8ge.h>

#include <GL/glew.h>

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

        void GLService::clear() const {
            glClearColor(
                    static_cast<float>(m_clearColor.r)/0xFF,
                    static_cast<float>(m_clearColor.g)/0xFF,
                    static_cast<float>(m_clearColor.b)/0xFF,
                    static_cast<float>(m_clearColor.a)/0xFF);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void GLService::render() const {

        }
    }
}