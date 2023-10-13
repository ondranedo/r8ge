// Created by vojta on 03.10.2023.
//

#include <GL/glx.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include "../Window.h"
#include <stdio.h>

static Window m_window;
static Display *m_display;
static GLXContext m_glContext;


namespace r8ge {

    void Window::create() {
        m_display = XOpenDisplay(nullptr);
        if (!m_display) {
            printf("Failed to create X11window\n");
            return;
        }

        int m_screen = DefaultScreen(m_display);
        int visualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 32, None};
        XVisualInfo *m_visual = glXChooseVisual(m_display, m_screen, visualAttributes);

        Colormap m_colormap = XCreateColormap(m_display, RootWindow(m_display, m_screen), m_visual->visual, AllocNone);
        XSetWindowAttributes m_windowAttributes;
        m_windowAttributes.colormap = m_colormap;
        m_windowAttributes.event_mask = ExposureMask;
        m_window = XCreateWindow(m_display, RootWindow(m_display, m_screen), 0, 0, m_x, m_y, 0,
                                   m_visual->depth, InputOutput, m_visual->visual, CWColormap | CWEventMask, &m_windowAttributes);
        XStoreName(m_display, m_window, m_title);
        XMapWindow(m_display, m_window);

        m_glContext = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);
        m_isCreated = true;
    }

    void Window::destroy() {
        glXMakeCurrent(m_display, None, nullptr);
        glXDestroyContext(m_display, m_glContext);
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);
        m_isCreated = false;
    }

    std::tuple<int, int> Window::getDims() {
        return std::make_tuple(m_x, m_y);
    }

    void Window::setVsync(bool vsync) {
        if (!m_isCreated) {
            printf("Window needs to be created\n");
        }
        else {
            auto glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC) glXGetProcAddress(
                    (const GLubyte *) "glXSwapIntervalEXT");
            glXSwapIntervalEXT(m_display, m_window, vsync);
        }
    }


    void Window::getReadyForRender() {
        if (!m_isCreated) {
            printf("Window needs to be created\n");
        }
        else {
            glXMakeCurrent(m_display, m_window, m_glContext);
        }
    }

    void Window::swapBuffers() {
        if (!m_isCreated) {
            printf("Window needs to be created\n");
        }
        else {
            glXSwapBuffers(m_display, m_window);
        }
    }

    void Window::pollEvents() {
        if (!m_isCreated) {
            printf("Window needs to be created\n");
        }
        else {
            XEvent event;
            while (XPending(m_display) > 0) {
                XNextEvent(m_display, &event);
            }
        }
    }
}