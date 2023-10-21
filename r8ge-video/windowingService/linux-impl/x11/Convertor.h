#ifndef R8GE_CONVERTOR_H
#define R8GE_CONVERTOR_H

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        class X11Convertor {
        public:
            static Code convertKeyCode(int x11KeDyCode);
        };
    }
}

#endif//!R8GE_X11_CONVERTOR_H
