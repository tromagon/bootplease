#include "commands\EventCommandMap.h"
#include "commands\Command.h"
#include "events\EventDispatcher.h"

void EventCommandMap::UnMapAll()
{
    m_Maps.clear();
}

void EventCommandMap::OnCommandEvent(const Event& evt)
{
    for (int i = 0 ; i < m_NumMap ; i++)
    {
        EventCommandMapItemPtr& item = m_Maps[i];
        if (item->GetEventType() == evt.GetType())
        {
            CommandPtr cmd = CommandPtr(&item->GetCommand());
            cmd->SetEvent(evt);
            cmd->Execute();

            if (cmd->GetIsDetained())
            {
                m_Detained.push_back(move(cmd));
                m_NumDetained++;
            }
        }
    }
}