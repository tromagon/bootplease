#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "Injector.h"
#include "CommandMap.h"
#include "ContextConfig.h"

class Context
{
private:
	EventDispatcher m_Dispatcher;
	Injector		m_Injector;
	CommandMap*		m_CommandMap;
	MediatorMap*	m_MediatorMap;

public:
	Injector&		GetInjector()	{ return m_Injector; }
	CommandMap&		GetCommandMap()	{ return *m_CommandMap; }

public:
	Context();
	~Context();

	void Update(float deltaTime = 0.0f) {}
	void Render() {}

	void Configure(ContextConfig& config);
};

#endif