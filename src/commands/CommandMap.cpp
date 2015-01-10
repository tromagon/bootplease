#include "CommandMap.h"
#include "Command.h"

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