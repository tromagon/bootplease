#include "EventCommandMap.h"
#include "Command.h"
#include "EventDispatcher.h"

EventCommandMap::~EventCommandMap()
{
	UnMapAll();
}

void EventCommandMap::UnMapAll()
{
	int i = m_NumMap;
	EventCommandMapItem* item;

	while(i-- > 0)
	{
		item = m_Maps[i];
		delete item;
	}

	m_Maps.clear();
}

void EventCommandMap::OnCommandEvent(const Event& evt)
{
	EventCommandMapItem* item;
	Command* command;

	const unsigned short l = m_NumMap;
	for (unsigned int i = 0 ; i < l ; i++)
	{
		item = m_Maps[i];
		if (item->GetEventType() == evt.GetType())
		{
			command = &item->GetCommand();
			command->SetContext(m_Context);
			command->SetCommandMap(*this);
			command->SetEvent(evt);
			command->Execute();

			if (GetDetainedIndex(*command) == -1)
			{
				delete &command;
			}
		}
	}
}