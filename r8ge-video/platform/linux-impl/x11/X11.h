#ifndef R8GE_X11_H
#define R8GE_X11_H

#include <tuple>
#include <cstddef>
#include <unordered_map>

#include<X11/X.h>
#include<X11/Xlib.h>

#include "../../../Window.h"
#include "../../WindowingService.h"

namespace r8ge {
    namespace video {
        class X11 : public WindowingService {
        public:
            X11();
            virtual ~X11() override;
            void init() override;
            void release() override;
            bool createWindow(const Window::Dims &dims, std::string_view title) override;
            bool showWindow(std::string_view title) override;
            bool hideWindow(std::string_view title) override;
            bool destroyWindow(std::string_view title) override;

        public:
            Display *m_display;
            ::Window m_rootWindow;
            Visual* m_visual;
            Colormap m_colormap;
            XSetWindowAttributes m_windowAttributes;
            uint8_t m_depth;
            std::unordered_map<std::string_view, ::Window> m_windows;
        };
    }
}

#endif//!R8GE_X11_H
