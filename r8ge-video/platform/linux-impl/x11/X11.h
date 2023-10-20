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
            bool createWindow(size_t width, size_t height, std::string_view title) override;
            bool showWindow(std::string_view title) override;
            bool hideWindow(std::string_view title) override;
            bool destroyWindow(std::string_view title) override;
            void poolEvents() override;

            void swapBuffersOfWindow(std::string_view title) override;
            void setVSyncOnWindow(std::string_view title, bool enabled) override;

            void setContextOfWindow(std::string_view title) override;

            void updateWindows() override;

            bool isWindowPresent(std::string_view title) const;
        public:
            Display *m_display;
            ::Window m_rootWindow;
            XVisualInfo* m_visual;
            Colormap m_colormap;
            XSetWindowAttributes m_windowAttributes;
            std::unordered_map<std::string_view, std::pair<::Window, bool>> m_windows;

            //TODO: Move to RenderingAPI
            GLXContext m_context;
        };
    }
}

#endif//!R8GE_X11_H
