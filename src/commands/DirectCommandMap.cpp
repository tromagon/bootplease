#include "DirectCommandMap.h"
#include "Command.h"

void DirectCommandMap::Execute()
{
	const unsigned short l = m_Maps.size();
	DirectCommandMapItem* item;
	Command* command;

	for (unsigned int i = 0 ; i < l ; i++)
	{
		item = m_Maps[i];
		command = &(item->GetCommand());
		command->Execute();

		if (GetDetainedIndex(*command) == -1)
		{
			delete &command;
		}
	}
}