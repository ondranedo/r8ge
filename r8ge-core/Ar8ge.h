#ifndef R8GE_AR8GE_H
#define R8GE_AR8GE_H

#include "Core.h"
#include "events/EventQueue.h"
#include "instance/GameInstance.h"

namespace r8ge {
    // The global main event queue, every event is sent to this queue
    namespace global {
        extern EventQueue::CallbackFn ar8geEventQueue;
        extern bool ar8geRunning;
        extern bool ar8geReady;
    }

    // Main Application class, handles the main loop, the event queue, and the game instances
    class Ar8ge {
    public:
        Ar8ge();
        ~Ar8ge();

        // Initializes the engine
        void init();

        // Starts to execute the main loop
        void run();

        // Performs the necessary cleanup, and exits the engine
        void exit();
    private:
        EventQueue m_queue;
        std::shared_ptr<GameInstance> m_game;
    };
}

#endif//!R8GE_AR8GE_H
