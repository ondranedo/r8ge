// Created by vojta on 03.10.2023.
//

#include <GL/glew.h>
#include <GL/glx.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include "../Window.h"
#include <stdio.h>

Window m_window;
Display *m_display;
GLXContext m_glContext;
Colormap m_colormap;
XVisualInfo *m_visual;
int m_screen;

namespace r8ge {

    void Window::init() {
        m_display = XOpenDisplay(nullptr);
        if (!m_display) {
            printf("Failed to create X11window\n");
            return;
        }
        else {
            printf("x11 window ok\n");
        }

        m_screen = DefaultScreen(m_display);
        //TODO get supported depth from driver somwehow
        int visualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, None};
        m_visual = glXChooseVisual(m_display, m_screen, visualAttributes);
        if (!m_visual) {
            printf("Failed to create X11Visual\n");
            return;
        }
        else {
            printf("x11 visual ok\n");
        }

        m_colormap = XCreateColormap(m_display, RootWindow(m_display, m_screen), m_visual->visual, AllocNone);
        if (!m_colormap) {
            printf("Failed to create Colormap");
            return;
        }
        else {
            printf("colormap ok\n");
        }
    }

    void Window::create() {
        XSetWindowAttributes m_windowAttributes;
        m_windowAttributes.colormap = m_colormap;
        m_windowAttributes.event_mask = ExposureMask;
        m_window = XCreateWindow(m_display, RootWindow(m_display, m_screen),0, 0, m_x, m_y, 0,
                                 m_visual->depth, InputOutput, m_visual->visual, CWColormap | CWEventMask,
                                 &m_windowAttributes);
        XStoreName(m_display, m_window, m_title);
        XMapWindow(m_display, m_window);

        m_glContext = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);

        if (!m_glContext) {
            printf("Failed to create glXContext");
            return;
        }
        else {
            printf("glXContext ok\n");
        }

        glXMakeCurrent(m_display, m_window, m_glContext);


        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewInitResult));

        }
        else {
            printf("Glew OK");
        }

        m_isCreated = true;
        printf("Window %s has been created\n", m_title);

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


    void Window::makeContext() {
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