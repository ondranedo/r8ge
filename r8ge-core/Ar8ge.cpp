
#include "Ar8ge.h"
#include "Logger.h"

#include "instance/GameInstance.h"

namespace r8ge {
    EventQueue::CallbackFn ar8geEventQueue = nullptr;

    Ar8ge::Ar8ge(): m_running(false){
        ar8geEventQueue = m_queue.getCallbackFn();
        R8GE_LOG("Ar8ge event queue set - events may be received");

        m_game = r8ge::createGame();


        R8GE_LOG("Engine application created");
    }

    void Ar8ge::init() {
        m_game->onInit();

        R8GE_LOG("Ar8ge initialized");
    }

    void Ar8ge::exit() {
        m_game->onExit();

        R8GE_LOG("Ar8ge exited successfully");
    }

    Ar8ge::~Ar8ge() {
        m_queue.emptyQueue();
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