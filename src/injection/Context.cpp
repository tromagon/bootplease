#include "Context.h"

Context::Context()
{
	m_CommandMap = new CommandMap(m_Dispatcher);
	m_MediatorMap = new MediatorMap(m_Dispatcher);
}

Context::~Context()
{
	delete m_MediatorMap;
	delete m_CommandMap;
}

void Context::Configure(ContextConfig& config)
{
	config.SetInjector(m_Injector);
	config.SetCommandMap(*m_CommandMap);
	config.SetMediatorMap(*m_MediatorMap);

	config.Configure();
}