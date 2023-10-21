#ifndef R8GE_X11_H
#define R8GE_X11_H

#include <tuple>
#include <cstddef>
#include <unordered_map>

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
            bool createMainWindow(size_t width, size_t height, std::string_view title) override;

            void poolEvents() override;
            bool destroyMainWindow() override;
            bool setContextOfMainWindow() override;
            void swapBuffersOfMainWindow() override;

        public:
            Display *m_display;
            ::Window m_rootWindow, m_mainWindow;
            size_t m_mainWindowWidth, m_mainWindowHeight;
            std::string m_mainWindowTitle;
            XVisualInfo* m_visual;
            Colormap m_colormap;
            XSetWindowAttributes m_windowAttributes;

            //TODO: Move to RenderingAPI
            GLXContext m_context;
        };
    }
}

#endif//!R8GE_X11_H
