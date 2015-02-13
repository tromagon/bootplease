#include "context\Context.h"

Context::Context() : m_NumConfigs(0)
{
    m_Dispatcher = EventDispatcherPtr(new EventDispatcher());
    m_Injector = InjectorPtr(new Injector());
    m_EventCommandMap = EventCommandMapPtr(new EventCommandMap(m_Dispatcher, m_Injector));
    m_DirectCommandMap = DirectCommandMapPtr(new DirectCommandMap(m_Dispatcher, m_Injector));
    m_MediatorMap = MediatorMapPtr(new MediatorMap(m_Dispatcher, m_Injector));
    m_Renderer = RendererPtr(new Renderer());
    m_UpdateManager = UpdateManagerPtr(new UpdateManager());
}

void Context::Update(float deltaTime)
{
    m_UpdateManager->Update(deltaTime);
}

void Context::Render()
{
    m_Renderer->Render();
}

void Context::Execute()
{
    for (int i = 0 ; i < m_NumConfigs ; i++)
    {
        ContextConfigPtr& config = m_Configs[i];
        config->SetInjector(*m_Injector.get());
        config->SetEventCommandMap(*m_EventCommandMap.get());
        config->SetDirectCommandMap(*m_DirectCommandMap.get());
        config->SetMediatorMap(*m_MediatorMap.get());
        config->Configure();
    }

    m_DirectCommandMap->Execute();
}

void Context::AddToUpdate(Updateable& updateable)
{
    m_UpdateManager->Add(updateable);
}

void Context::AddToRenderer(Renderable& renderable)
{
    m_Renderer->Add(renderable);
}

void Context::RemoveFromUpdate(Updateable& updateable)
{
    m_UpdateManager->Remove(updateable);
}

void Context::RemoveFromRenderer(Renderable& renderable)
{
    m_Renderer->Remove(renderable);
}

void Context::Dispose()
{
    for (int i = m_NumConfigs - 1 ; i >= 0 ; i--)
    {
        ContextConfigPtr& config = m_Configs[i];
        config->Dispose();
    }
}