#ifndef R8GE_KEYEVENTS_H
#define R8GE_KEYEVENTS_H

#include <inttypes.h>
#include "Event.h"
#include "Strokes.h"

namespace r8ge {
    struct KeyPressed : public Event {
        IOStroke stroke;
        bool repeat;
        KeyPressed(IOStroke stroke, bool repeat);
        static EventType getEventType();
    };

    struct KeyReleased : public Event {
        IOStroke stroke;

        KeyReleased(IOStroke _key);
        static EventType getEventType();
    };
}

#endif//!R8GE_KEYEVENTS_H
