#ifndef R8GE_X11_H
#define R8GE_X11_H

#include <tuple>
#include <cstddef>
#include <unordered_map>

#include "../../WindowingService.h"

#include "../../../renderingService/context/X11/XContext.h"

#include <X11/Xutil.h>
#include <X11/Xlib.h>

namespace r8ge {
    namespace video {
        class X11 : public WindowingService {
        public:
            X11();
            virtual ~X11() override;
            void init() override;
            void exit() override;
            bool createMainWindow(size_t width, size_t height, std::string_view title) override;

            void poolEvents() override;
            bool destroyMainWindow() override;
            bool setContextOfMainWindow() override;
            void swapBuffersOfMainWindow() override;

        private:
            // TODO: Make Window class
            size_t m_mainWindowWidth, m_mainWindowHeight;
            std::string m_mainWindowTitle;


            ::Window m_mainWindow;
            ::Display *m_display;
            ::Window m_rootWindow;
            ::XSetWindowAttributes m_windowAttributes;
            std::unique_ptr<XContext> m_xContext;
        };
    }
}

#endif//!R8GE_X11_H
