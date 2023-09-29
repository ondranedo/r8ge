#ifndef R8GE_AR8GE_H
#define R8GE_AR8GE_H

#include "Core.h"

namespace r8ge {
    class Ar8ge {
    public:
        Ar8ge();
        ~Ar8ge();

        void init();
        void run();
        void release();

    private:
        bool m_running;
    };
}

#endif//!R8GE_AR8GE_H
