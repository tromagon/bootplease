#ifndef _SEQUENCEEVENT_H_
#define _SEQUENCEEVENT_H_

#include "events\Event.h"

class Sequence;

class SequenceEvent : public Event
{
public:
    static const char* STARTED;
    static const char* COMPLETE;
    static const char* STEP_COMPLETE;

private:
    Sequence& m_Sequence;

public:
    Sequence&   GetSequence() const { return m_Sequence; }

public:
    explicit SequenceEvent(const char* type, Sequence& sequence) : Event(type), m_Sequence(sequence) {}
    virtual ~SequenceEvent() {};
};

#endif