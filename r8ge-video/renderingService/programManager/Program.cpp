#include "Program.h"

namespace r8ge {
    namespace video {

        Program::Program(size_t id, std::string_view vertexShader, std::string_view fragmentShader)
        : m_valid(false), m_vertexShader(vertexShader), m_fragmentShader(fragmentShader), m_id(id)
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
            return m_vertexShader;
        }

        std::string Program::getFragmentShader() const {
            return m_fragmentShader;
        }
    }
}