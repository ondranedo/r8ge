#ifndef R8GE_EVENTPAYLOAD_H
#define R8GE_EVENTPAYLOAD_H

#include <functional>
#include <memory>

#include "Event.h"

namespace r8ge {
    class EventPayload {
        using EventCallbackFn = std::function<void(std::shared_ptr<Event> const&)>;
    public:
        [[nodiscard]] EventCallbackFn getCallback() const;
        void setCallback(const EventCallbackFn&);

        [[nodiscard]] std::shared_ptr<Event> getEvent() const;
        void setEvent(std::shared_ptr<Event> const&);

    private:
        std::shared_ptr<Event> m_event;
        EventCallbackFn m_callback;
    };
}

#endif//!R8GE_EVENTPAYLOAD_H
