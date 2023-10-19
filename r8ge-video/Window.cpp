#include "Window.h"

#include "platform/WindowingService.h"

namespace r8ge {
    namespace video {
        Window::Window(const r8ge::video::Window::Dims &dims_w_h, std::string_view title)
        : m_dims(dims_w_h), m_title(title), m_isCreated(false)
        {}

        Window::~Window() = default;

        void Window::show() {
            if(!m_isCreated)
                create();
        }

        void Window::hide() {

        }

        void Window::create() {

        }
    }
}

