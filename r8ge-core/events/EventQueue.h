#ifndef R8GE_EVENTQUEUE_H
#define R8GE_EVENTQUEUE_H

#include <queue>
#include <thread>

#include "EventPayload.h"

namespace r8ge {
    class EventQueue {
    public:
        using CallbackFn = std::function<void(const EventPayload&)>;

        EventQueue();
        ~EventQueue();
        void sendEvent(const EventPayload& event);
        void emptyQueue();
        [[nodiscard]] CallbackFn getCallbackFn();

    private:
        std::queue<EventPayload> m_queue;
        std::mutex m_queueMutex;
    };
}

#endif//!R8GE_EVENTQUEUE_H
