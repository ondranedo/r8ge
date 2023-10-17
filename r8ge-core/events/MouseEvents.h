#ifndef R8GE_MOUSEEVENTS_H
#define R8GE_MOUSEEVENTS_H

#include "Event.h"
#include "Strokes.h"

namespace r8ge {
    struct MouseMoved : public Event
    {
        double x, y;

        MouseMoved(double _x, double _y);
        static EventType getEventType();
    };

    struct MouseScrolled : public Event
    {
        double x, y;

        MouseScrolled(double _x, double _y);
        static EventType getEventType();
    };

    struct MousePressed : public Event
    {
        IOStroke stroke;

        explicit MousePressed(IOStroke _stroke);
        static EventType getEventType();
    };

    struct MouseReleased : public Event
    {
        IOStroke stroke;

        explicit MouseReleased(IOStroke _stroke);
        static EventType getEventType();
    };
}

#endif//!R8GE_MOUSEEVENTS_H
