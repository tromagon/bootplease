#ifndef  _RENDERER_H_
#define  _RENDERER_H_

#include "Renderable.h"
#include <list>
#include <memory>

using namespace std;

class Renderer
{
private:
    list<Renderable*> m_Renderables;

public:
    Renderer() {}
    ~Renderer() {}

    void    Render();
    void    Add(Renderable& renderable);
    void    Remove(Renderable& renderable);
};

typedef unique_ptr<Renderer> RendererPtr;

#endif