
#include "Ar8ge.h"
#include "Logger.h"

#include "instance/GameInstance.h"
#include "../r8ge-video/Video.h"
#include "../r8ge-video/EntrytPoint.h"

namespace r8ge {

    EventQueue::CallbackFn Ar8ge::s_eventQueue = nullptr;
    bool Ar8ge::s_running = true;
    bool Ar8ge::s_ready = false;

    Ar8ge::Ar8ge(){
        s_eventQueue = m_queue.getCallbackFn();
        R8GE_LOG("Ar8ge event queue set - events may be received");

        m_game = r8ge::createGame();

        R8GE_LOG("Engine application created");
    }

    void Ar8ge::init() {
        R8GE_LOG_INFOR("Ar8ge initialized");

        // Other modules may use this time to initialize
        s_ready = true;
    }

    void Ar8ge::exit() {

        R8GE_LOG_INFOR("Ar8ge exited successfully");
    }

    Ar8ge::~Ar8ge() {
        m_queue.emptyQueue();
        s_eventQueue = nullptr;

        R8GE_LOG("Ar8ge event queue set to nullptr");

        R8GE_LOG("Engine application destroyed");
    }

    void Ar8ge::run() {
        R8GE_LOG_INFOR("Starting to wait, other module threads may use this time to initialize");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        m_game->onInit();

        R8GE_LOG("Engine application starting main loop");

        while(s_running) {
            m_game->onUpdate();
            m_queue.emptyQueue();

            s_running = false;
        }

        m_game->onExit();
    }

    bool Ar8ge::isReady() {
        return s_ready;
    }

    bool Ar8ge::isRunning() {
        return s_running;
    }

    EventQueue::CallbackFn Ar8ge::getEventQueue() {
        return s_eventQueue;
    }
}