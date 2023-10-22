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
            auto version = std::string_view(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
            R8GE_LOG_INFOR("GL Running version: {}", version);
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

        void GLService::render(const std::vector<size_t>& index_data, const std::vector<float>& vertex_data) const {
            
        }
    }
}