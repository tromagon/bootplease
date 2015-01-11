#include "Injector.h"

Injector::~Injector()
{
	UnMapAll();
}

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

void Injector::UnMapAll()
{
	InjectorMapping* mapping;

	int i = m_NumInjections;
	while (i-- > 0)
	{
		delete &mapping;
	}

	m_Maps.clear();

}