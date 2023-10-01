
#include "Ar8ge.h"
#include "Logger.h"

namespace r8ge {
    EventQueue::CallbackFn ar8geEventQueue = nullptr;

    Ar8ge::Ar8ge(): m_running(true){
        ar8geEventQueue = m_queue.getCallbackFn();
        R8GE_LOG("Ar8ge event queue set - events may be received");

        R8GE_LOG("Engine application created");
    }

    Ar8ge::~Ar8ge() {
        ar8geEventQueue = nullptr;
        R8GE_LOG("Ar8ge event queue set to nullptr");


        R8GE_LOG("Engine application destroyed");
    }

    void Ar8ge::run() {
        R8GE_LOG("Engine application starting main loop");

        /*while(m_running) {

            m_queue.emptyQueue();
            mainLogger->emptyLogQueue();
        }*/

    }
}