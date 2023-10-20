#include "Window.h"

#include "platform/WindowingService.h"

#include <r8ge/r8ge.h>

#include "Video.h"

namespace r8ge {
    namespace video {
        void Window::show(std::string_view title) {
            Video::getWindowingService()->showWindow(title);
        }

        void Window::hide(std::string_view title) {
            Video::getWindowingService()->hideWindow(title);
        }

        void Window::create(const Window::Dims &dims_w_h, std::string_view title) {
            Video::getWindowingService()->createWindow(dims_w_h, title);
        }
    }
}

