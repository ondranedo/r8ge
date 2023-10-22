#ifndef R8GE_XCONTEXT_H
#define R8GE_XCONTEXT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <memory>

namespace r8ge {
    namespace video {
        class XContext {
        public:
            XContext();
            virtual ~XContext();

            void setDisplay(::Display *display);
            void setWindow(::Window window);
            virtual void windowIsReady() const = 0;
            virtual void swapBuffers() const = 0;

            virtual void createContext() = 0;
            virtual void setContextActive() const = 0;

            virtual void init() = 0;
            virtual void exit() = 0;

            virtual void windowChanged(size_t w, size_t h) const = 0;

            [[nodiscard]] virtual ::XVisualInfo* getVisualInfo() const = 0;

            [[nodiscard]] static std::unique_ptr<XContext> create();
        protected:
            ::Display *m_display;
            ::Window m_window;
        };
    }
}

#endif//!R8GE_XCONTEXT_H
