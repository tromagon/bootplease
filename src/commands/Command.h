#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "EventDispatcher.h"
#include "EventCommandMap.h"
#include "Context.h"

class Command
{
	friend class EventCommandMap;
	friend class DirectCommandMap;

private:
	Context*			m_Context;
	const Event*		m_Event;
	CommandMap*			m_CommandMap;			

private:
	void				SetContext(Context& value)					{ m_Context = &value; }
	void				SetEvent(const Event& evt)					{ m_Event = &evt; }
	void				SetCommandMap(CommandMap& value)			{ m_CommandMap = & value; }

protected:
	EventDispatcher&	GetDispatcher()								{ return m_Context->GetDispatcher(); }
	const Event&		GetEvent()									{ return *m_Event; }
	Injector&			GetInjector()								{ return m_Context->GetInjector(); }

public:
	Command() {}
	virtual ~Command() {}

protected:
	template<class C>
	int		AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

	template<class C>
	void	RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

	void	DispatchContextEvent(Event& evt);

	virtual void Execute() {}
	virtual void Detain() final;
	virtual void Release() final;
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