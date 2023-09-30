#ifndef R8GE_AR8GE_H
#define R8GE_AR8GE_H

#include "Core.h"
#include "events/EventQueue.h"

namespace r8ge {
    extern EventQueue::CallbackFn ar8geEventQueue;

    class Ar8ge {
    public:
        Ar8ge();
        ~Ar8ge();

        void run();


    private:
        bool m_running;
        EventQueue m_queue;
    };
}

#endif//!R8GE_AR8GE_H
