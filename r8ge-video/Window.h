//
// Created by vojta on 26.09.2023.
//

#ifndef R8GE_WINDOW_H
#define R8GE_WINDOW_H

#include <tuple>

namespace r8ge {
    class Window {
    public:
        Window(int x, int y, const char *title)
                : m_x(x), m_y(y), m_title(title) {}

        void init();

        void create();

        void destroy();

        std::tuple<int, int> getDims();

        void setVsync(bool vsync);

        void makeContext();

        void swapBuffers();

        void pollEvents();

    protected:
        int m_x{};
        int m_y{};
        const char *m_title{};
        bool m_isCreated{false};
    };
}
#endif //R8GE_WINDOW_H