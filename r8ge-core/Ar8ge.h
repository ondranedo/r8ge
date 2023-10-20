#ifndef R8GE_AR8GE_H
#define R8GE_AR8GE_H

#include "Core.h"
#include "events/EventQueue.h"
#include "instance/GameInstance.h"

namespace r8ge {
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

        // STATIC HACKING
    public:
        // Returns true if the engine is ready to run
        // Other modules may use this time to initialize
        static bool isReady();

        // Returns true if the engine is running
        // Other modules may use this time to exit
        static bool isRunning();

        // Returns the main event queue
        static EventQueue::CallbackFn getEventQueue();

    private:
        static EventQueue::CallbackFn s_eventQueue;
        static bool s_running;
        static bool s_ready;
    };
}

#endif//!R8GE_AR8GE_H
