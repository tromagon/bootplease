#include "Injector.h"

Injector::Injector()
{
	m_CommandMap = new CommandMap(m_Dispatcher);
}

Injector::~Injector()
{
	delete m_CommandMap;
}

void Injector::UnMap(const char* id)
{
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		InjectorMapping& mapping = *m_Maps[i];
		if (mapping.GetId() == id)
		{
			m_Maps.erase(m_Maps.begin() + i);
			delete &mapping;
			return;
		}
	}
}