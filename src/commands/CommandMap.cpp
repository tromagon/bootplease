#include "commands\CommandMap.h"
#include "commands\Command.h"

CommandMap::~CommandMap()
{
    ClearDetained();
}

void CommandMap::Detain(Command& command)
{
    m_Detained.push_back(&command);
    m_NumDetained++;
}

void CommandMap::Release(Command& command)
{
    int index = GetDetainedIndex(command);
    if (index != -1)
    {
        m_Detained.erase(m_Detained.begin() + index);
        m_NumDetained--;
        delete &command;
    }
}

int CommandMap::GetDetainedIndex(Command& command)
{
    const unsigned short l = m_NumDetained;
    for (unsigned int i = 0 ; i < l ; i++)
    {
        if (m_Detained[i] == &command)
        {
            return i;
        }
    }

    return -1;
}

void CommandMap::ClearDetained()
{
    int i = m_NumDetained;
    Command* command;
    while (i)
    {
        command = m_Detained[i];
        delete command;
    }

    m_Detained.clear();
}