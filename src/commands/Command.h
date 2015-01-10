#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "EventDispatcher.h"
#include "Injected.h"
#include "CommandMap.h"

class Command
{
private:
	EventDispatcher*	m_Dispatcher;
	CommandMap*			m_CommandMap;
	const Event*		m_Event;

public:
	EventDispatcher&	GetDispatcher()								{ return *m_Dispatcher; }
	void				SetDispatcher(EventDispatcher& dispatcher)	{ m_Dispatcher = &dispatcher; }
	CommandMap&			GetCommandMap()								{ return *m_CommandMap; }
	void				SetCommandMap(CommandMap& commandMap)		{ m_CommandMap = &commandMap; }
	const Event&		GetEvent()									{ return *m_Event; }
	void				SetEvent(const Event& evt)					{ m_Event = &evt; }

protected:
	Injector&			GetInjector()								{ return m_CommandMap->GetInjector(); }

public:
	Command() {}
	virtual ~Command() {}

	template<class C>
	int		AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

	template<class C>
	void	RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

	void	DispatchContextEvent(Event& evt);

	virtual void execute() {};
};


template<class C>
int Command::AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
	return GetDispatcher().AddListener(eventType, fct, proxy);
}

template<class C>
void Command::RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
	GetDispatcher().RemoveListener(eventType, fct, proxy);
}

#endif