#include "EventCommandMap.h"
#include "Command.h"
#include "EventDispatcher.h"

void EventCommandMap::OnCommandEvent(const Event& evt)
{
	EventCommandMapItem* item;
	Command* command;

	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		item = m_Maps[i];
		if (item->GetEventType() == evt.GetType())
		{
			command = &item->GetCommand();
			command->SetEvent(evt);
			command->Execute();

			if (GetDetainedIndex(*command) == -1)
			{
				delete &command;
			}
		}
	}
}