#include "XContext.h"

#include "GLX/GLXContext.h"

namespace r8ge {
    namespace video {
        XContext::XContext() : m_display(nullptr) {}
        XContext::~XContext() = default;

        void XContext::setDisplay(::Display *display) {
            m_display = display;
        }

        void XContext::setWindow(::Window window) {
            m_window = window;
        }

        std::unique_ptr<XContext> XContext::create() {
            // TODO: Add option to choose API
            return std::make_unique<GLXContext>();
        }
    }
}