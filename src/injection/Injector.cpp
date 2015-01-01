#include "Injector.h"

void Injector::SetCommandMap(ICommandMap& commandMap)
{
	m_CommandMap = &commandMap;
	m_CommandMap->SetInjector(*this);
}

void Injector::SetMediatorMap(IMediatorMap& mediatorMap)
{
	m_MediatorMap = &mediatorMap;
	m_MediatorMap->SetInjector(*this);
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