//
// Created by vojta on 03.10.2023.
//

#include "Win32Window.h"

namespace r8ge{

	void Win32Window::init()
    {
        glfwInit();
        glfwMakeContextCurrent(m_window);
    }

    void Win32Window::create()
    {
        m_window = glfwCreateWindow(m_x,m_y,m_title,NULL,NULL);
    }

    void Win32Window::destroy()
    {
        glfwDestroyWindow(m_window);
    }

}