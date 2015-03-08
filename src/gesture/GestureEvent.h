#ifndef _GESTUREEVENT_H_
#define _GESTUREEVENT_H_

#include "events\EventDispatcher.h"
#include "Gesture.h"

class GestureEvent : public Event
{
public:
    explicit GestureEvent(const char* type, const Gesture& gesture) 
        : Event(type), m_Gesture(gesture) {}
    ~GestureEvent() {}

    static const char* GESTURE_RECOGNIZED;

    const Gesture& m_Gesture;
};

#endif