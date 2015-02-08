#include "events\EventDispatcher.h"

EventDispatcher::EventDispatcher() : m_NumListeners(0) {}

bool EventDispatcher::HasListener(const char* eventType)
{
    for ( int i = 0 ; i < m_NumListeners ; i++)
    {
        const EventCallBackPtr& cb = m_EventCallBacks[i];
        if (cb->GetType() == eventType)
        {
            return true;
        }
    }

    return false;
}

void EventDispatcher::Dispatch(const Event& evt)
{
    for (int i = 0 ; i < m_NumListeners ; i++)
    {
        const EventCallBackPtr& cb = m_EventCallBacks[i];
        if (cb->GetType() == evt.GetType())
        {
            cb->Call(evt);
        }
    }
}

