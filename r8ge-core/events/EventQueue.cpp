
#include "EventQueue.h"

#include <functional>

namespace r8ge {


    EventQueue::EventQueue() : m_queue{}, m_queueMutex{} {

    }

    void EventQueue::sendEvent(const EventPayload &event) {
        m_queueMutex.lock();
        m_queue.push(event);
        m_queueMutex.unlock();
    }

    void EventQueue::emptyQueue() {
        m_queueMutex.lock();
        while(!m_queue.empty())
        {
            auto& eventP = m_queue.front();
            auto callBack = eventP.getCallback();
            callBack(eventP.getEvent());
            m_queue.pop();
        }
        m_queueMutex.unlock();
    }

    EventQueue::CallbackFn EventQueue::getCallbackFn() {
        return [this](auto && p) { sendEvent(std::forward<decltype(p)>(p)); };
    }

    EventQueue::~EventQueue() {
        emptyQueue();
    }
}