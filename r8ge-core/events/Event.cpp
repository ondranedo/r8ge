
#include "Event.h"

namespace r8ge {


    Event::Event() : m_header({EventType::NONE, false}){}

    Event::~Event() = default;

    Event::EventType Event::getType() const {
        return m_header.type;
    }

    bool Event::isHandled() const {
        return m_header.handled;
    }

    void Event::setToHandled() {
        m_header.handled = true;
    }

    std::string Event::getTypeAsString() const {
        switch (m_header.type) {
            case EventType::NONE:               return "NONE";
            case EventType::WINDOW_RESIZED:     return "WINDOW_RESIZED";
            case EventType::WINDOW_CLOSED:      return "WINDOW_CLOSED";
            case EventType::WINDOW_FOCUS:       return "WINDOW_FOCUS";
            case EventType::WINDOW_LOST_FOCUS:  return "WINDOW_LOST_FOCUS";
            case EventType::WINDOW_MOVED:       return "WINDOW_MOVED";
            case EventType::KEY_PRESSED:        return "KEY_PRESSED";
            case EventType::KEY_RELEASED:       return "KEY_RELEASED";
            case EventType::MOUSE_PRESSED:      return "MOUSE_PRESSED";
            case EventType::MOUSE_RELEASED:     return "MOUSE_RELEASED";
            case EventType::MOUSE_MOVED:        return "MOUSE_MOVED";
            case EventType::MOUSE_SCROLLED:     return "MOUSE_SCROLLED";
        }
    }
}