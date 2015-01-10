#ifndef  _RENDERABLE_H_
#define  _RENDERABLE_H_

#include <list>

using namespace std;

class IRenderable
{
public:
	IRenderable() {}
	virtual ~IRenderable() {}

	virtual void Render() {}
};

class Renderer
{
private:
	list<IRenderable*> m_Renderables;

public:
	Renderer() {}
	~Renderer() {}

	void    Render();
	void    Add(IRenderable* renderable);
	void    Remove(IRenderable* renderable);
};

#endif