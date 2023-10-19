#ifndef R8GE_WINDOW_H
#define R8GE_WINDOW_H

#include <tuple>
#include <string>

namespace r8ge {
    namespace video {
        class Window {
        public:
            using Dims = std::pair<unsigned short, unsigned short>;

        public:
            Window(const Dims& dims_w_h, std::string_view title);
            ~Window();
            void show();
            void hide();
        private:
            void create();

        public:
            Dims m_dims;
            std::string m_title;
            bool m_isCreated;
        };
    }
}

#endif//!R8GE_WINDOW_H
