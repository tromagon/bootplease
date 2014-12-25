#include "Updateable.h"

UpdateManager* g_pUpdateManager = nullptr;

void UpdateManager::Update(float deltaTime)
{
	for (std::list<IUpdateable*>::iterator it = m_Updateables.begin(); it != m_Updateables.end(); ++it)
	{
		(*it)->Update(deltaTime);
	} 
}

void UpdateManager::Add(IUpdateable* updateable)
{
	m_Updateables.push_back(updateable);
}

void UpdateManager::Remove(IUpdateable* updateable)
{
	m_Updateables.remove(updateable);
}