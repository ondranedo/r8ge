
#include "Ar8ge.h"
#include "Logger.h"

namespace r8ge {
    Ar8ge::Ar8ge(): m_running(true){
        R8GE_LOG("Engine application created");
    };

    Ar8ge::~Ar8ge() {
        R8GE_LOG("Engine application destroyed");
    }

    void Ar8ge::run() {
        R8GE_LOG("Engine application starting main loop");

        while(m_running) {
            mainLogger->emptyLogQueue();
        }
    }
}