#ifndef _CONTEXTCONFIG_H_
#define _CONTEXTCONFIG_H_

#include "Injector.h"
#include "CommandMap.h"

class ContextConfig
{
	friend class Context;

private:
	Injector*			m_Injector;
	CommandMap*			m_CommandMap;
	MediatorMap*		m_MediatorMap;

public:
	Injector&		GetInjector()						{ return *m_Injector; }
	CommandMap&		GetCommandMap()						{ return *m_CommandMap; }
	MediatorMap&	GetMediatorMap()					{ return *m_MediatorMap; }

private:
	void			SetInjector(Injector& value)		{ m_Injector = &value; }
	void			SetCommandMap(CommandMap& value)	{ m_CommandMap = &value; }
	void			SetMediatorMap(MediatorMap& value)	{ m_MediatorMap = &value; }

public:
	ContextConfig() {};
	virtual ~ContextConfig() {};

protected:
	virtual void Configure() {};
};

#endif