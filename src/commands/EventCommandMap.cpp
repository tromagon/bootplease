#include "commands\EventCommandMap.h"
#include "commands\Command.h"
#include "events\EventDispatcher.h"

EventCommandMap::~EventCommandMap()
{
    UnMapAll();
}

void EventCommandMap::UnMapAll()
{
    m_Maps.clear();
}

void EventCommandMap::OnCommandEvent(const Event& evt)
{
    Command* command;

    const unsigned short l = m_NumMap;
    for (unsigned int i = 0 ; i < l ; i++)
    {
        EventCommandMapItemPtr& item = m_Maps[i];
        if (item->GetEventType() == evt.GetType())
        {
            command = &item->GetCommand();
            command->SetEvent(evt);
            command->Execute();

            if (GetDetainedIndex(*command) == -1)
            {
                delete command;
            }
        }
    }
}