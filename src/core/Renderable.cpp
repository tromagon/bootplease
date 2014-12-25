#include "Renderable.h"

Renderer* g_pRenderer = nullptr;

void Renderer::Render()
{
	for (std::list<IRenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
	{
		(*it)->Render();
	} 
}

void Renderer::Add(IRenderable* updateable)
{
	m_Renderables.push_back(updateable);
}

void Renderer::Remove(IRenderable* updateable)
{
	m_Renderables.remove(updateable);
}