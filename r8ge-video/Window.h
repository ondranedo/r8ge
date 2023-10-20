#ifndef R8GE_WINDOW_H
#define R8GE_WINDOW_H

#include <tuple>
#include <string>
#include <thread>

namespace r8ge {
    namespace video {
        class Window {
        public:
            using Dims = std::pair<unsigned short, unsigned short>;

        public:
            static void show(std::string_view title);
            static void hide(std::string_view title);
            static void create(const Dims& dims_w_h, std::string_view title);
        };
    }
}

#endif//!R8GE_WINDOW_H
