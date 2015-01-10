#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "Event.h"
#include "EventDispatcher.h"
#include "View.h"
#include "MediatorMap.h"

class Mediator
{
private:
	View*				m_View;
	MediatorMap*		m_MediatorMap;

public:
	View&				GetView()						{ return *m_View; }
	void				SetView(View& value)			{ m_View = &value; }

	MediatorMap&		GetMediatorMap()						{ return *m_MediatorMap; }
	void				SetMediatorMap(MediatorMap& value)		{ m_MediatorMap = &value; }

	EventDispatcher*	GetDispatcher() { return nullptr; }

protected:
	Injector&			GetInjector();

	template<class C>
	int		AddContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy);

	template<class C>
	void	RemoveContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy);

	void	DispatchContextEvent(Event& evt);

public:
	Mediator() {}
	virtual ~Mediator() {}

	virtual void OnInitialized() {};
};


template<class C>
int Mediator::AddContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	return m_MediatorMap->GetDispatcher()->AddListener(eventType, fct, proxy);
}

template<class C>
void Mediator::RemoveContextListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	m_MediatorMap->GetDispatcher()->RemoveListener(eventType, fct, proxy);
}

#endif