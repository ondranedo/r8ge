//
// Created by vojta on 26.09.2023.
//

#ifndef R8GE_WINDOW_H
#define R8GE_WINDOW_H


#include <string>

namespace r8ge
{
    class Window
    {
    public:
        Window(int x, int y,const std::string& title) : m_x(x), m_y(y),m_title((title.c_str())) {

        }
        virtual ~Window();
        virtual void init() = 0;
        virtual void create() = 0;
        virtual void destroy() = 0;
        //virtual void toggleVsync() = 0;
    protected:
        int m_x;
        int m_y;
        const char *m_title;
    };
}
#endif //R8GE_WINDOW_H