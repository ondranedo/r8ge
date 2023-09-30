#include "KeyEvents.h"

namespace r8ge {
    KeyPressed::KeyPressed(IOStroke _key, bool _repeat) : repeat(_repeat), stroke(_key) {}

    Event::EventType KeyPressed::getEventType() {
        return Event::EventType::WINDOW_MOVED;
    }

    KeyReleased::KeyReleased(IOStroke _key) : stroke(_key) {}

    Event::EventType KeyReleased::getEventType() {
        return Event::EventType::WINDOW_MOVED;
    }
}
