#include "GLService.h"
#include "../buffers/VertexBuffer.h"

#include "GLConvertor.h"

#define R8GE_GL_ERROR_MSG_LENGTH 1024

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
            for(auto& [r8geid, glid] : m_programs)
            {
                glDeleteProgram(glid);
                R8GE_LOG("GL Program [r8ge:{},gl:] deleted", r8geid, glid);
            }
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

            auto a = ib.getData();

            glGenBuffers(1, &m_indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(ib.getSize()), &ib.getRawData()[0], GL_STATIC_DRAW);
        }

        void GLService::setVertexBuffer(const VertexBuffer &vb) {
            glGenVertexArrays(1, &m_vertexArrayObject);
            glBindVertexArray(m_vertexArrayObject);

            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vb.getSize()), &vb.getRawData()[0], GL_STATIC_DRAW);

            m_layout = vb.getLayout();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void GLService::setDataLayout() const {
            size_t index = 0, offset = 0;
            for(auto& element : m_layout.getLayout()) {
                glVertexAttribPointer(index,
                                      VertexBufferLayout::EntryTypeComponents(element),
                                      GLConvertor::convertToGLType(VertexBufferLayout::EntryTypeToDataType(element)),
                                      VertexBufferLayout::EntryTypeShouldBeNormalized(element),
                                      static_cast<GLsizei>(m_layout.getStride()),
                                      reinterpret_cast<const void*>(offset)
                );
                glEnableVertexAttribArray(index);
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
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

            setDataLayout();

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, nullptr);
        }

        void GLService::setProgram(const Program &program) {
            glUseProgram(m_programs[program.getId()]);
        }

        bool GLService::compileProgram(Program &program) {

            // Shader creation
            GLuint vs = glCreateShader(GL_VERTEX_SHADER);
            GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertexShaderSource   = program.getVertexShader();
            std::string fragmentShaderSource = program.getFragmentShader();

            if(!compileShader(vs, vertexShaderSource, "vertex shader")) return false;
            if(!compileShader(fs, fragmentShaderSource, "fragment shader")) return false;

            // Program compilation - linking shaders to a program
            GLuint p = glCreateProgram();

            glAttachShader(p, vs);
            glAttachShader(p, fs);

            glLinkProgram(p);

            int result;
            glGetProgramiv(p, GL_LINK_STATUS, &result);
            if (result != GL_TRUE) {
                GLsizei log_length = 0;
                char message[R8GE_GL_ERROR_MSG_LENGTH];
                glGetProgramInfoLog(p, R8GE_GL_ERROR_MSG_LENGTH, &log_length, message);
                R8GE_LOG_ERROR("GL program failed to link: {}", std::string_view(message, R8GE_GL_ERROR_MSG_LENGTH));
                return false;
            }

            glDeleteShader(vs);
            glDeleteShader(fs);

            m_programs[program.getId()] = p;
            program.setValid();

            R8GE_LOG("GL Program [r8ge:{},gl:{}] compiled and created", program.getId(), p);

            return true;
        }

        bool GLService::compileShader(GLuint shader, std::string_view source, std::string_view type) const {
            const std::string shaderSource = std::string(source);
            char * ptr = const_cast<char*>(shaderSource.c_str());
            glShaderSource(shader, 1, &ptr, nullptr);
            glCompileShader(shader);
            int result;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
            if(result != GL_TRUE) {
                GLsizei log_length = 0;
                char message[R8GE_GL_ERROR_MSG_LENGTH];
                glGetShaderInfoLog(shader, R8GE_GL_ERROR_MSG_LENGTH, &log_length, message);
                R8GE_LOG_ERROR("Failed to compile [{}] :\n\n {}", type, std::string(message));
                return false;
            }
            return true;
        }
    }
}