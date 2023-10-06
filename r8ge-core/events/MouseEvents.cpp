#include "MouseEvents.h"

namespace r8ge {

    MouseMoved::MouseMoved(double _x, double _y) : x(_x), y(_y) {
        m_header.type = EventType::MOUSE_MOVED;
    }

    Event::EventType MouseMoved::getEventType() {
        return EventType::MOUSE_MOVED;
    }

    MouseScrolled::MouseScrolled(double _x, double _y) : x(_x),y(_y) {
        m_header.type = EventType::MOUSE_SCROLLED;
    }

    Event::EventType MouseScrolled::getEventType() {
        return EventType::MOUSE_SCROLLED;
    }

    MousePressed::MousePressed(IOStroke _stroke) : stroke(_stroke) {
        m_header.type = EventType::MOUSE_PRESSED;
    }

    Event::EventType MousePressed::getEventType() {
        return EventType::MOUSE_PRESSED;
    }

    MouseReleased::MouseReleased(IOStroke _stroke) : stroke(_stroke) {
        m_header.type = EventType::MOUSE_RELEASED;
    }

    Event::EventType MouseReleased::getEventType() {
        return EventType::MOUSE_RELEASED;
    }
}
