#include "GLXContext.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        size_t GLXContext::s_contextCount = 0;
        GLXContext::GLXContext() : m_context(nullptr) {}

        void GLXContext::swapBuffers() const {
            glXSwapBuffers(m_display, m_window);
        }

        void GLXContext::createContext() {
            if(!m_visual) {
                R8GE_LOG_ERROR("GLX Context or Visual was not set");
            }

            m_context = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);
            R8GE_ASSERT(m_context, "GLX Context failed to create");
        }

        XVisualInfo *GLXContext::getVisualInfo() const {
            return m_visual;
        }

        void GLXContext::init() {
            if(!m_display) {
                R8GE_LOG_ERROR("X11 Display was not set");
            }
            // TODO: Add double buffering option into settings
            GLint attributes[] = {
                    GLX_RGBA,
                    GLX_DEPTH_SIZE, 24,
                    GLX_DOUBLEBUFFER,
                    None };
            m_visual = glXChooseVisual(m_display, 0, attributes);
            R8GE_ASSERT(m_visual, "X11 Visual was failed to create");
        }

        void GLXContext::exit() {
            s_contextCount--;
        }

        void GLXContext::setContextActive() const {
            glXMakeCurrent(m_display, m_window, m_context);
        }

        void GLXContext::windowIsReady() const {
            setContextActive();
            if(s_contextCount == 0) {
                auto res = glewInit();
                if(res != GLEW_OK) {
                    R8GE_LOG_ERROR("Failed to initialize GLEW: `{}`", (char *) glewGetErrorString(res));
                    return;
                }
                R8GE_LOG("GLEW initialized");
            }
            s_contextCount++;
        }

        void GLXContext::windowChanged(size_t w, size_t h) const {
            glViewport(0, 0, w, h);
        }

        GLXContext::~GLXContext() = default;
    }
}