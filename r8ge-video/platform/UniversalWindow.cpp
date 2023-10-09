//
// Created by vojta on 03.10.2023.
//

#include "UniversalWindow.h"
#include <stdio.h>

namespace r8ge
{

    void UniversalWindow::create()
    {
        m_window = glfwCreateWindow(m_x, m_y, m_title, nullptr, nullptr);
        m_isCreated = true;

    }

    void UniversalWindow::destroy()
    {
        glfwDestroyWindow(m_window);
        m_isCreated = false;
    }

    std::tuple<int, int> UniversalWindow::getDims()
    {
        return std::make_tuple(m_x, m_y);
    }

    void UniversalWindow::setVsync(bool vsync)
    {
        // 0: Vsync set to OFF
        // 1: Vsync set to ON
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        } else
        {
            glfwSwapInterval(vsync);
        }

    }

    void UniversalWindow::getReadyForRender()
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        } else
        {
            glfwMakeContextCurrent(m_window);
            glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *window, int x, int y)
            {
                glViewport(0, 0, x, y);
            });
            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                printf("Failed to init glad");
            }
        }
    }

    void UniversalWindow::swapBuffers()
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        } else
        {
            glfwSwapBuffers(m_window);
        }
    }

    void UniversalWindow::pollEvents()
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        } else
            glfwPollEvents();
    }
}


