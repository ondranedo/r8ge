
#include "Ar8ge.h"
#include "Logger.h"

namespace r8ge {
    EventQueue::CallbackFn ar8geEventQueue = nullptr;

    Ar8ge::Ar8ge(): m_running(true){
        R8GE_LOG("Engine application created");

        ar8geEventQueue = m_queue.getCallbackFn();
        R8GE_LOG("Ar8ge event queue set - events may be received");
    }

    Ar8ge::~Ar8ge() {
        R8GE_LOG("Engine application destroyed");


        ar8geEventQueue = nullptr;
        R8GE_LOG("Ar8ge event queue set to nullptr - events all event are lost");
    }

    void Ar8ge::run() {
        R8GE_LOG("Engine application starting main loop");

        /*while(m_running) {

            m_queue.emptyQueue();
            mainLogger->emptyLogQueue();
        }*/

    }
}