#include "Window.h"

#include "platform/WindowingService.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        Window::Window(const r8ge::video::Window::Dims &dims_w_h, std::string_view title)
        : m_dims(dims_w_h), m_title(title), m_isCreated(false)
        {}

        Window::~Window() = default;

        void Window::show() {
            if(!m_isCreated)
                create();
            video::WindowingService::getService().setContextOfWindow(m_title);
        }

        void Window::hide() {
            video::WindowingService::getService().hideWindow(m_title);
        }

        void Window::create() {
            video::WindowingService::getService().createWindow(m_dims, m_title);
            m_isCreated = true;
        }
    }
}

