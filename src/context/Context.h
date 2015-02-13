#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <memory>
#include <vector>

#include "events\EventDispatcher.h"
#include "injection\Injector.h"
#include "commands\EventCommandMap.h"
#include "commands\DirectCommandMap.h"
#include "mediator\MediatorMap.h"
#include "core\UpdateManager.h"
#include "core\Renderer.h"
#include "context\ContextConfig.h"

using namespace std;

class Renderable;
class Updateable;

class Context
{
private:
    EventDispatcherPtr  m_Dispatcher;
    InjectorPtr         m_Injector;
    EventCommandMapPtr  m_EventCommandMap;
    DirectCommandMapPtr m_DirectCommandMap;
    MediatorMapPtr      m_MediatorMap;
    UpdateManagerPtr    m_UpdateManager;
    RendererPtr         m_Renderer;

    vector<ContextConfigPtr>    m_Configs;
    int                         m_NumConfigs;
    
public:
    EventDispatcherPtr&     GetDispatcher()         { return m_Dispatcher; }
    InjectorPtr&            GetInjector()           { return m_Injector; }
    EventCommandMapPtr&     GetEventCommandMap()    { return m_EventCommandMap; }
    DirectCommandMapPtr&    GetDirectCommandMap()   { return m_DirectCommandMap; }
    MediatorMapPtr&         GetMediatorMap()        { return m_MediatorMap; }
    
public:
    Context();
    ~Context() {}

    void Update(float deltaTime = 0.0f);
    void Render();

    template<class T>
    void AddConfig();

    void Execute();

    void AddToUpdate(Updateable& updateable);
    void AddToRenderer(Renderable& renderable);
    void RemoveFromUpdate(Updateable& updateable);
    void RemoveFromRenderer(Renderable& renderable);

    void Dispose();
};

template<class T>
void Context::AddConfig()
{
    m_Configs.push_back(ContextConfigPtr(new T()));
    m_NumConfigs++;
}

#endif