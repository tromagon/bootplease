#include "Injector.h"

void Injector::UnMap(const char* id)
{
	InjectorMapping* mapping;

	const unsigned short l = m_NumInjections;
	for (unsigned int i = 0 ; i < l ; i++)
	{
		mapping = m_Maps[i];
		if (mapping->GetId() == id)
		{
			m_Maps.erase(m_Maps.begin() + i);
			delete &mapping;
			return;
		}
	}
}