//
// Created by vojta on 26.09.2023.
//

#ifndef R8GE_WINDOWCLASS_H
#define R8GE_WINDOWCLASS_H

#include <tuple>
#include <GL/glew.h>
#include <GL/glx.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>

namespace r8ge {
    class WindowClass {
    public:
        WindowClass(int x, int y, const char *title)
                : m_x(x), m_y(y), m_title(title) {}

        void init();

        void create();

        void destroy();

        std::tuple<int, int> getDims();

        void setVsync(bool vsync);

        void makeContext();

        void swapBuffers();

        void pollEvents();

    protected:
        int m_x{};
        int m_y{};
        const char *m_title{};
        bool m_isCreated{false},m_isInitialized{false};
    protected:
         inline static Display *m_display;
         inline static Colormap m_colormap;
         inline static XVisualInfo *m_visual;
         inline static GLXContext m_glContext;
        Window m_window;
        int m_screen;
    };

}
#endif //R8GE_WINDOWCLASS_H