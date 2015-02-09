#include "commands\DirectCommandMap.h"
#include "commands\Command.h"

DirectCommandMap::~DirectCommandMap()
{
    UnMapAll();
}

void DirectCommandMap::Execute()
{
    const unsigned short l = m_NumMap;
    DirectCommandMapItem* item;
    Command* command;

    for (unsigned int i = 0 ; i < l ; i++)
    {
        item = m_Maps[i];
        command = &(item->GetCommand());
        command->Execute();

        if (GetDetainedIndex(*command) == -1)
        {
            delete command;
        }
    }
}

void DirectCommandMap::UnMapAll()
{
    int i = m_NumMap;
    DirectCommandMapItem* item;

    while(i-- > 0)
    {
        item = m_Maps[i];
        delete item;
    }

    m_Maps.clear();
}