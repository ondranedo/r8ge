#include "GLService.h"
#include "../buffers/VertexBuffer.h"

#include "GLConvertor.h"

namespace r8ge {
    namespace video {
        static void debugMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            R8GE_LOG_ERROR("GL debug message: {}", std::string_view(message, length));
        }

        GLService::GLService() : m_indexCount(0), m_indexBuffer(-1), m_vertexArrayObject(-1), m_vertexBuffer(-1) {
            R8GE_LOG("GL Service created");
        }
        GLService::~GLService() {
            R8GE_LOG("GL Service destroyed");
        }

        void GLService::init() {
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

            glDebugMessageCallback(debugMsg, nullptr);

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

        void GLService::setIndexBuffer(const IndexBuffer &ib) {
            m_indexCount = ib.getIndeciesCount();

            glGenBuffers(1, &m_indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(ib.getSize()), &ib.getRawData()[0], GL_STATIC_DRAW);
        }

        void GLService::setVertexBuffer(const VertexBuffer &vb) {
            glGenVertexArrays(1, &m_vertexArrayObject);
            glBindVertexArray(m_vertexArrayObject);

            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

            auto data = vb.getRawData();


            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vb.getSize()), &vb.getRawData()[0], GL_STATIC_DRAW);

            m_layout = vb.getLayout();
            setDataLayout();
        }

        void GLService::setDataLayout() const {
            size_t index = 0, offset = 0;
            for(auto& element : m_layout.getLayout()) {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index,
                                      VertexBufferLayout::EntryTypeComponents(element),
                                      GLConvertor::convertToGLType(VertexBufferLayout::EntryTypeToDataType(element)),
                                      VertexBufferLayout::EntryTypeShouldBeNormalized(element),
                                      static_cast<GLsizei>(m_layout.getStride()),
                                      reinterpret_cast<const void*>(offset)
                );
                index++;
                offset+= VertexBufferLayout::EntryTypeSize(element);
            }
        }

        void GLService::render() const {
            if(m_indexCount==0)
                R8GE_LOG_ERROR("Invalid index count: {}", m_indexCount);
            if(m_indexCount%3!=0)
                R8GE_LOG_WARNI("Index count is not divisible by 3: {}", m_indexCount);
            if(m_indexBuffer==-1)
                R8GE_LOG_ERROR("Invalid index buffer - index buffer is not bound");
            if(m_vertexArrayObject==-1)
                R8GE_LOG_ERROR("Invalid vertex array object - vertex array object is not bound");

            glBindVertexArray(m_vertexArrayObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
            //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

            setDataLayout();

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, nullptr);
        }
    }
}