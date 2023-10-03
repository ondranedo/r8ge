//
// Created by vojta on 03.10.2023.
//

#ifndef R8GE_WIN32WINDOW_H
#define R8GE_WIN32WINDOW_H

#include "../Window.h"
#include "../../vendor/glfw/include/GLFW/glfw3.h"

namespace r8ge
{
    class Win32Window : public Window
    {
    public:
        Win32Window();
        ~Win32Window();
        void init() override;
        void create() override;
        void destroy() override;
    private:
        GLFWwindow *m_window;
    };

}
#endif //R8GE_WIN32WINDOW_H