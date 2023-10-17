#include "KeyEvents.h"

namespace r8ge {
    KeyPressed::KeyPressed(IOStroke _key, bool _repeat) : repeat(_repeat), stroke(_key) {
        m_header.type = EventType::KEY_PRESSED;
    }

    Event::EventType KeyPressed::getEventType() {
        return Event::EventType::KEY_PRESSED;
    }

    KeyReleased::KeyReleased(IOStroke _key) : stroke(_key) {
        m_header.type = EventType::KEY_RELEASED;
    }

    Event::EventType KeyReleased::getEventType() {
        return Event::EventType::KEY_RELEASED;
    }
}
