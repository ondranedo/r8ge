// Created by vojta on 03.10.2023.
//

#include "../../r8ge-core/Logger.h"
#include "../WindowClass.h"
#include <stdio.h>


namespace r8ge {

    void WindowClass::init() {
        m_display = XOpenDisplay(nullptr);
        if (!m_display) {
            R8GE_LOG_ERROR("Window `{}` failed to create X11Display", m_title);
            return;
        }
        else {
            R8GE_LOG_TRACE("Window `{}` created X11Display", m_title);
        }

        m_screen = DefaultScreen(m_display);
        //TODO get supported depth from driver somehow
        int visualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, None};
        m_visual = glXChooseVisual(m_display, m_screen, visualAttributes);
        if (!m_visual) {
            R8GE_LOG_ERROR("Window `{}` failed to create X11Visual", m_title);
            return;
        }
        else {
            R8GE_LOG_TRACE("Window `{}` created X11Visual", m_title);
        }

        m_colormap = XCreateColormap(m_display, RootWindow(m_display, m_screen), m_visual->visual, AllocNone);
        if (!m_colormap) {
            R8GE_LOG_ERROR("Window `{}` failed to create X11Colormap", m_title);
            return;
        }
        else {
            R8GE_LOG_TRACE("Window `{}` created X11Colormap", m_title);
        }
        R8GE_LOG_TRACE("Window `{}` successfully initialized", m_title);
        m_isInitialized = True;
    }


    void WindowClass::create() {
        if (!m_isInitialized) {
            R8GE_LOG_ERROR("Window {} creation was called before init", m_title);
        }

        XSetWindowAttributes m_windowAttributes;
        m_windowAttributes.colormap = m_colormap;
        m_windowAttributes.event_mask = ExposureMask;
        m_window = XCreateWindow(m_display, RootWindow(m_display, m_screen), 0, 0, m_x, m_y, 0,
                                 m_visual->depth, InputOutput, m_visual->visual, CWColormap | CWEventMask,
                                 &m_windowAttributes);
        XStoreName(m_display, m_window, m_title);
        XMapWindow(m_display, m_window);

        m_glContext = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);

        if (!m_glContext) {
            R8GE_LOG_ERROR("Window `{}` failed to create glXContext", m_title);
            return;
        }
        else {
            R8GE_LOG_TRACE("Window `{}` created glXContext", m_title);
        }

        glXMakeCurrent(m_display, m_window, m_glContext);


        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK) {
            R8GE_LOG_ERROR("Window `{}` failed to initialize GLEW ", m_title);
        }
        else {
            R8GE_LOG_TRACE("Window `{}` successfully initialized GLEW", m_title);
        }
        m_isCreated = true;
        R8GE_LOG_TRACE("Window `{}` successfully created", m_title);
    }

    void WindowClass::destroy() {
        glXMakeCurrent(m_display, None, nullptr);
        glXDestroyContext(m_display, m_glContext);
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);
        m_isCreated = false;
    }

    std::tuple<int, int> WindowClass::getDims() {
        return std::make_tuple(m_x, m_y);
    }

    void WindowClass::setVsync(bool vsync) {
        if (!m_isCreated) {
            R8GE_LOG_WARNI("Window `{}` needs to be created before calling setVsync", m_title);
        }
        else {
            auto glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC) glXGetProcAddress(
                    (const GLubyte *) "glXSwapIntervalEXT");
            glXSwapIntervalEXT(m_display, m_window, vsync);
        }
    }


    void WindowClass::makeContext() {
        if (!m_isCreated) {
            R8GE_LOG_WARNI("Window `{}` needs to be created before calling makeContext", m_title);
        }
        else {
            glXMakeCurrent(m_display, m_window, m_glContext);
        }
    }

    void WindowClass::swapBuffers() {
        if (!m_isCreated) {
            R8GE_LOG_WARNI("Window `{}` needs to be created before calling swapBuffers", m_title);
        }
        else {
            glXSwapBuffers(m_display, m_window);
        }
    }

    void WindowClass::pollEvents() {
        if (!m_isCreated) {
            R8GE_LOG_WARNI("Window `{}` needs to be created before calling pollEvents", m_title);
        }
        else {
            XEvent event;
            while (XPending(m_display) > 0) {
                XNextEvent(m_display, &event);
            }
        }
    }
}