#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "Event.h"
#include "EventDispatcher.h"
#include "View.h"
#include "MediatorMap.h"
#include "Context.h"

class Mediator
{
	friend class MediatorMap;

private:
	View*				m_View;
	Context*			m_Context;

private:
	void				SetContext(Context& value)				{ m_Context = &value; }

public:
	View&				GetView()								{ return *m_View; }
	void				SetView(View& value)					{ m_View = &value; }

	MediatorMap&		GetMediatorMap()						{ return m_Context->GetMediatorMap(); }
	Injector&			GetInjector()							{ return m_Context->GetInjector(); } 
	EventDispatcher&	GetDispatcher()							{ return m_Context->GetDispatcher(); }

protected:
	Mediator() {}
	virtual ~Mediator() {}

	template<class C>
	int		AddContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy);

	template<class C>
	void	RemoveContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy);

	void	DispatchContextEvent(Event& evt);

	virtual void OnInitialized() {};
};


template<class C>
int Mediator::AddContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	return GetDispatcher().AddListener(eventType, fct, proxy);
}

template<class C>
void Mediator::RemoveContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	GetDispatcher().RemoveListener(eventType, fct, proxy);
}

#endif