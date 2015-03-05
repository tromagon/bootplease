#ifndef _DISPLAYOBJECTEVENT_H_
#define _DISPLAYOBJECTEVENT_H_
#include <events\Event.h>

class DisplayObjectEvent : public Event
{
public:
    static const char* ADDED;
    static const char* ADDED_TO_STAGE;
    static const char* REMOVED;
    static const char* REMOVED_FROM_STAGE;

public:
    explicit DisplayObjectEvent(const char* type) : Event(type) {};
    ~DisplayObjectEvent() {};
};

#endif
