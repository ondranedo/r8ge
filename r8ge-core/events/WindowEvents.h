#ifndef R8GE_WINDOWEVENTS_H
#define R8GE_WINDOWEVENTS_H

#include "Event.h"

namespace r8ge {
    struct WindowResized : public Event
    {
        unsigned int x, y;

        WindowResized(unsigned int _x, unsigned int _y);
        static EventType getEventType();
    };

    struct WindowClosed : public Event
    {
        WindowClosed();
        static EventType getEventType();
    };

    struct WindowFocus : public Event
    {
        WindowFocus();
        static EventType getEventType();
    };

    struct WindowLostFocus : public Event
    {
        WindowLostFocus();
        static EventType getEventType();
    };

    struct WindowMoved : public Event
    {
        double x, y;
        WindowMoved(double _x, double _y);
        static EventType getEventType();
    };
}

#endif//!R8GE_WINDOWEVENTS_H
