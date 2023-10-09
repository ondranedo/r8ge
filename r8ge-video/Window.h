//
// Created by vojta on 26.09.2023.
//

#ifndef R8GE_WINDOW_H
#define R8GE_WINDOW_H

#include <tuple>

namespace r8ge
{
    class Window
    {
    public:
        Window(int x, int y, const char* title)
            : m_x(x), m_y(y), m_title(title) {}
        virtual void create() = 0;
        virtual void destroy() = 0;
        virtual std::tuple<int,int> getDims() = 0;
        virtual void setVsync(bool vsync) = 0;
        virtual void getReadyForRender() = 0;
        virtual void swapBuffers() = 0;
        virtual void pollEvents() = 0;
        virtual ~Window();

    protected:
        int m_x{};
        int m_y{};
        const char* m_title{};
    };
}
#endif //R8GE_WINDOW_H