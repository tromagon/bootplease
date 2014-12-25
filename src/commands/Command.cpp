#include "Command.h"
#include "EventDispatcher.h"

void CommandMap::Detain(Command& command)
{
	m_Detained.push_back(&command);
}

void CommandMap::Release(Command& command)
{
	int index = GetDetainedIndex(command);
	if (index != -1)
	{
		m_Detained.erase(m_Detained.begin() + index);
		delete &command;
	}
}

int CommandMap::GetDetainedIndex(Command& command)
{
	const unsigned short l = m_Detained.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		if (m_Detained[i] == &command)
		{
			return i;
		}
	}

	return -1;
}

void CommandMap::OnCommandEvent(Event& evt)
{
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		CommandMapItem& item = *(m_Maps[i]);
		if (item.GetEventType() == evt.GetType())
		{
			Command& command = item.GetCommand();
			command.SetCommandMap(*this);
			command.SetDispatcher(m_Dispatcher);
			command.SetEvent(evt);
			command.execute();

			if (GetDetainedIndex(command) == -1)
			{
				delete &command;
			}
		}
	}
}