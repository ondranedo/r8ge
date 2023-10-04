#include "Window.h"
#include <stdio.h>
namespace r8ge
{
    Window::~Window() = default;

    void Window::getDims()
    {
        printf("%d",m_x);
    }
}