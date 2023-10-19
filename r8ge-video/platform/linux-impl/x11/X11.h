#ifndef R8GE_X11_H
#define R8GE_X11_H

#include <tuple>
#include <cstddef>
#include <unordered_map>

#include "../../../Window.h"
#include "../../WindowingService.h"

//  TODO: Move to RenderingAPI
#include <GL/glew.h>
#include <GL/glx.h>

#include <X11/Xutil.h>
#include <X11/Xlib.h>

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
            void poolEvents() override;

            void swapBuffersOfWindow(std::string_view title) override;
            void setVSyncOnWindow(std::string_view title, bool enabled) override;

            void setContextOfWindow(std::string_view title) override;

            void updateWindows() override;

        public:
            Display *m_display;
            ::Window m_rootWindow;
            XVisualInfo* m_visual;
            Colormap m_colormap;
            XSetWindowAttributes m_windowAttributes;
            uint8_t m_depth;
            std::unordered_map<std::string_view, std::pair<::Window, bool>> m_windows;

            //TODO: Move to RenderingAPI
            GLXContext m_context;
        };
    }
}

#endif//!R8GE_X11_H
