// Created by vojta on 03.10.2023.
//

#include "UniversalWindow.h"
#include <stdio.h>


namespace r8ge
{

    void UniversalWindow::create()
    {
        if (!glfwInit())
        {
            printf("Failed to initialize GLFW\n");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        m_window = glfwCreateWindow(m_x, m_y, m_title, nullptr, nullptr);
        if (!m_window)
        {
            printf("Failed to create GLFW window\n");
            return;
        }

        glfwMakeContextCurrent(m_window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            printf("Failed to initialize GLEW\n");
            return;
        }

        m_isCreated = true;
    }

    void UniversalWindow::destroy()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_isCreated = false;
    }

    std::tuple<int, int> UniversalWindow::getDims()
    {
        return std::make_tuple(m_x, m_y);
    }

    void UniversalWindow::setVsync(bool vsync)
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        }
        else
        {
            glfwSwapInterval(vsync);
        }
    }

    void UniversalWindow::getReadyForRender()
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        }
        else
        {
            glfwMakeContextCurrent(m_window);
            glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *window, int x, int y)
            {
                glViewport(0, 0, x, y);
            });
        }
    }

    void UniversalWindow::swapBuffers()
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        }
        else
        {
            glfwSwapBuffers(m_window);
        }
    }

    void UniversalWindow::pollEvents()
    {
        if (!m_isCreated)
        {
            printf("Window needs to be created\n");
        }
        else
        {
            glfwPollEvents();
        }
    }
}
