//
// Created by vojta on 03.10.2023.
//

#ifndef R8GE_WIN32WINDOW_H
#define R8GE_WIN32WINDOW_H

#include "../../vendor/glfw/include/GLFW/glfw3.h"
#include "../Window.h"


namespace r8ge
{
    class Win32Window : public Window
    {
    public:
        Win32Window(int x, int y, const char* title) : Window(x,y,title) {}
		void init() override;
		void create() override;
		void destroy() override;
        
    private:
        GLFWwindow *m_window{};
    };

}
#endif //R8GE_WIN32WINDOW_H