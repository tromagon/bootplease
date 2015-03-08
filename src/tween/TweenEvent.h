#ifndef _TWEENEVENT_H_
#define _TWEENEVENT_H_

#include "events\Event.h"
#include <memory>

using namespace std;

class Tween;

class TweenEvent : public Event
{
public:
    static const char* START;
    static const char* UPDATE;
    static const char* COMPLETE;

public:
    explicit TweenEvent(const char* type, Tween& tween) 
        : Event(type), m_Tween(tween) {}

    ~TweenEvent() {}

    Tween&  GetTween() const { return m_Tween; }

private:
    Tween& m_Tween;
};

#endif
