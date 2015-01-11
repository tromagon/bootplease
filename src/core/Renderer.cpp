#include "Renderer.h"

void Renderer::Render()
{
	for (std::list<Renderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
	{
		(*it)->Render();
	} 
}

void Renderer::Add(Renderable& renderable)
{
	m_Renderables.push_back(&renderable);
}

void Renderer::Remove(Renderable& renderable)
{
	m_Renderables.remove(&renderable);
}