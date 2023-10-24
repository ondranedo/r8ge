#include "Program.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {

        Program::Program(size_t id, std::string_view source)
        : m_valid(false), m_source(source), m_id(id)
        {}

        bool Program::isValid() const {
            return m_valid;
        }

        void Program::setValid() {
            m_valid = true;
        }

        VertexBufferLayout Program::getLayout() const {
            return m_layout;
        }

        void Program::setLayout(const VertexBufferLayout &layout) {
            m_layout = layout;
        }

        size_t Program::getId() const {
            return m_id;
        }

        std::string Program::getVertexShader() const {
            File<reader::Glsl> glsl(m_source);
            glsl->load_glsl();
            return glsl->getVertexShader();
        }

        std::string Program::getFragmentShader() const {
            File<reader::Glsl> glsl(m_source);
            glsl->load_glsl();
            return glsl->getFragmentShader();
        }
    }
}