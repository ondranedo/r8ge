#include "WindowEvents.h"

namespace r8ge {

    WindowResized::WindowResized(unsigned int _x, unsigned int _y) :x(_x),y(_y) {
        m_header.type = Event::EventType::WINDOW_RESIZED;
    }

    Event::EventType WindowResized::getEventType() {
        return Event::EventType::WINDOW_RESIZED;;
    }

    WindowClosed::WindowClosed() {
        m_header.type = Event::EventType::WINDOW_CLOSED;
    }

    Event::EventType WindowClosed::getEventType() {
        return Event::EventType::WINDOW_CLOSED;;
    }

    WindowFocus::WindowFocus() {
        m_header.type = Event::EventType::WINDOW_FOCUS;
    }

    Event::EventType WindowFocus::getEventType() {
        return Event::EventType::WINDOW_FOCUS;
    }

    WindowLostFocus::WindowLostFocus() {
        m_header.type = Event::EventType::WINDOW_LOST_FOCUS;
    }

    Event::EventType WindowLostFocus::getEventType() {
        return Event::EventType::WINDOW_LOST_FOCUS;
    }

    WindowMoved::WindowMoved(double _x, double _y) : x(_x), y(_y){
        m_header.type = Event::EventType::WINDOW_MOVED;
    }

    Event::EventType WindowMoved::getEventType() {
        return Event::EventType::WINDOW_MOVED;
    }
}
