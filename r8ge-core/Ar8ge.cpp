
#include "Ar8ge.h"
#include "Logger.h"

#include "instance/GameInstance.h"
#include "../r8ge-video/Video.h"
#include "../r8ge-video/EntrytPoint.h"

namespace r8ge {
    namespace global {
        EventQueue::CallbackFn ar8geEventQueue = nullptr;
        bool ar8geRunning = false;
        bool ar8geReady = false;
    }

    Ar8ge::Ar8ge(){
        global::ar8geEventQueue = m_queue.getCallbackFn();
        R8GE_LOG("Ar8ge event queue set - events may be received");

        m_game = r8ge::createGame();

        R8GE_LOG("Engine application created");
    }

    void Ar8ge::init() {
        m_game->onInit();

        R8GE_LOG_INFOR("Ar8ge initialized");
        global::ar8geReady = true;
    }

    void Ar8ge::exit() {
        m_game->onExit();

        R8GE_LOG_INFOR("Ar8ge exited successfully");
    }

    Ar8ge::~Ar8ge() {
        m_queue.emptyQueue();
        global::ar8geEventQueue = nullptr;

        R8GE_LOG("Ar8ge event queue set to nullptr");

        R8GE_LOG("Engine application destroyed");
    }

    void Ar8ge::run() {
        R8GE_LOG("Engine application starting main loop");

        R8GE_LOG_INFOR("Starting to wait, other module threads may use this time to initialize");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        while(global::ar8geRunning) {

            m_game->onUpdate();
            m_queue.emptyQueue();
        }
    }
}