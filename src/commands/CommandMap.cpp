#include "commands\CommandMap.h"
#include "commands\Command.h"

void CommandMap::Release(Command& command)
{
    for (int i = 0 ; i < m_NumDetained ; i++)
    {
        CommandPtr& cmd = m_Detained[i];

        if (cmd.get() == &command)
        {
            m_Detained.erase(m_Detained.begin() + i);
            m_NumDetained--;

            return;
        }
    }
}