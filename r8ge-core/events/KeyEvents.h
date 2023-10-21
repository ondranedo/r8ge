#ifndef R8GE_KEYEVENTS_H
#define R8GE_KEYEVENTS_H

#include <inttypes.h>
#include "Event.h"
#include "Strokes.h"

namespace r8ge {
    struct KeyPressed : public UserEvent {
        IOStroke stroke;
        bool repeat;
        KeyPressed(IOStroke stroke, bool repeat);
        static Type getEventType();
    };

    struct KeyReleased : public UserEvent {
        IOStroke stroke;

        KeyReleased(IOStroke _key);
        static Type getEventType();
    };
}

#endif//!R8GE_KEYEVENTS_H
