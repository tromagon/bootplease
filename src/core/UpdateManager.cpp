#include "UpdateManager.h"

void UpdateManager::Update(float deltaTime)
{
	for (std::list<Updateable*>::iterator it = m_Updateables.begin(); it != m_Updateables.end(); ++it)
	{
		(*it)->Update(deltaTime);
	} 
}

void UpdateManager::Add(Updateable& updateable)
{
	m_Updateables.push_back(&updateable);
}

void UpdateManager::Remove(Updateable& updateable)
{
	m_Updateables.remove(&updateable);
}