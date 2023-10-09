//
// Created by vojta on 03.10.2023.
//

#ifndef R8GE_UNIVERSALWINDOW_H
#define R8GE_UNIVERSALWINDOW_H

#define GLFW_INCLUDE_NONE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Window.h"


namespace r8ge
{
    class UniversalWindow : public Window
    {
    public:
        UniversalWindow(int x, int y, const char *title) : Window(x, y, title) {}

        void create() override;

        void destroy() override;

        void setVsync(bool vsync) override;

        std::tuple<int, int> getDims() override;

        void getReadyForRender() override;

        void swapBuffers() override;

        void pollEvents() override;

    private:
        GLFWwindow *m_window{};
        bool m_isCreated{};
    };

}
#endif //R8GE_UNIVERSALWINDOW_H