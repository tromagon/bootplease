#ifndef _CONTEXTCONFIG_H_
#define _CONTEXTCONFIG_H_

#include "Context.h"

class Injector;
class EventCommandMap;
class DirectCommandMap;
class MediatorMap;

class ContextConfig
{
	friend class Context;

private:
	Context*			m_Context;

public:
	Context&			GetContext()					{ return *m_Context; }
	Injector&			GetInjector()					{ return m_Context->GetInjector(); }
	EventCommandMap&	GetEventCommandMap()			{ return m_Context->GetEventCommandMap(); }
	DirectCommandMap&	GetDirectCommandMap()			{ return m_Context->GetDirectCommandMap(); }
	MediatorMap&		GetMediatorMap()				{ return m_Context->GetMediatorMap(); }

private:
	void				SetContext(Context& value)		{ m_Context = &value; }

public:
	ContextConfig() {};
	virtual ~ContextConfig() {};

protected:
	virtual void Configure() {};
	virtual void Dispose() {};
};

#endif