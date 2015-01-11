#include "Context.h"
#include "EventCommandMap.h"
#include "DirectCommandMap.h"
#include "MediatorMap.h"
#include "ContextConfig.h"
#include "Injector.h"

Context::Context()
{
	m_Dispatcher = new EventDispatcher();
	m_Injector = new Injector();
	m_EventCommandMap = new EventCommandMap(*this);
	m_DirectCommandMap = new DirectCommandMap(*this);
	m_MediatorMap = new MediatorMap(*this);
}

Context::~Context()
{
	delete m_Dispatcher;
	delete m_Injector;
	delete m_MediatorMap;
	delete m_EventCommandMap;
	delete m_DirectCommandMap;
}

void Context::Update(float deltaTime)
{
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

void Context::Dispose()
{
	m_Config->Dispose();
}