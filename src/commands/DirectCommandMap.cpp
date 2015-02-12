#include "commands\DirectCommandMap.h"
#include "commands\Command.h"

void DirectCommandMap::Execute()
{
    for (int i = 0 ; i < m_NumMap ; i++)
    {
        DirectCommandMapItemPtr& item = m_Maps[i];
        CommandPtr command = CommandPtr(&item->GetCommand());
        command->SetCommandMap(*this);
        command->Execute();

        if (command->GetIsDetained())
        {
            m_Detained.push_back(move(command));
            m_NumDetained++;
        }
    }
}

void DirectCommandMap::UnMapAll()
{
    m_Maps.clear();
}