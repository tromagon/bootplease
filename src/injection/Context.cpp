#include "Context.h"
#include "EventCommandMap.h"
#include "DirectCommandMap.h"
#include "MediatorMap.h"
#include "ContextConfig.h"
#include "Injector.h"
#include "UpdateManager.h"
#include "Renderer.h"

Context::Context()
{
	m_Dispatcher = new EventDispatcher();
	m_Injector = new Injector();
	m_EventCommandMap = new EventCommandMap(*this);
	m_DirectCommandMap = new DirectCommandMap(*this);
	m_MediatorMap = new MediatorMap(*this);
	m_Renderer = new Renderer();
	m_UpdateManager = new UpdateManager();
}

Context::~Context()
{
	delete m_MediatorMap;

	m_Config->Dispose();

	delete m_Injector;
	delete m_Dispatcher;
	delete m_EventCommandMap;
	delete m_DirectCommandMap;
	delete m_Renderer;
	delete m_UpdateManager;
}

void Context::Update(float deltaTime)
{
	m_UpdateManager->Update(deltaTime);
}

void Context::Render()
{
	m_Renderer->Render();
}

void Context::Configure(ContextConfig& config)
{
	m_Config = &config;
	m_Config->SetContext(*this);
	m_Config->Configure();
}

void Context::Execute()
{
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
	m_Config->Dispose();
}