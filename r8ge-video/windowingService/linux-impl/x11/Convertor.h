#ifndef R8GE_CONVERTOR_H
#define R8GE_CONVERTOR_H

#include "../r8ge-core/events/Strokes.h"

namespace r8ge {
    namespace video {
        class X11Convertor {
        public:
            static IOCode convertKeyCode(int x11KeDyCode);
        };
    }
}

#endif//!R8GE_X11_CONVERTOR_H
