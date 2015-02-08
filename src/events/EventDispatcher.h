#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include "Event.h"
#include <vector>
#include <memory>

using namespace std;

class EventDispatcher
{
public:
    EventDispatcher();
	virtual ~EventDispatcher() {};

	bool	HasListener(const char* eventType);
	void	Dispatch(const Event& evt);

	template<class C>
	void	AddListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

	template<class C>
	void	RemoveListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

private:
	class IEventCallBackSpec
	{
	public:
		IEventCallBackSpec() {}
		virtual ~IEventCallBackSpec() {}
		virtual void Call(const Event& evt)	= 0;
	};

	typedef unique_ptr<IEventCallBackSpec> IEventCallBackSpecPtr;

	template<class C>
	class EventCallBackSpec : public IEventCallBackSpec
	{
	private:
		C&		m_Proxy;
		void	(C::*m_Fct)(const Event&);

	public:
		C&		GetProxy()						{ return m_Proxy; }
		void	(C::*GetFct())(const Event&)	{ return m_Fct; }

	public:
		EventCallBackSpec(C& proxy, void (C::*fct)(const Event&)) : m_Proxy(proxy), m_Fct(fct) {}
		void Call(const Event& evt)				{ (&m_Proxy->*m_Fct)(evt); }
	};

	class EventCallBack
	{
	private:
		IEventCallBackSpecPtr	m_Spec;
		const char*				m_Type;

	public:
		const char*				GetType()		{ return m_Type; }

		template<class C>
		void	(C::*GetFct())(const Event&)	{ return static_cast<EventCallBackSpec<C>*>(m_Spec.get())->GetFct(); }
		template<class C>
		C&		GetProxy()						{ return static_cast<EventCallBackSpec<C>*>(m_Spec.get())->GetProxy(); }

		template<class C>
		EventCallBack(const char* type, C& proxy, void (C::*fct)(const Event&)) 
			: m_Type(type), m_Spec(IEventCallBackSpecPtr(new EventCallBackSpec<C>(proxy, fct))) {}

		void Call(const Event& evt)				{ m_Spec->Call(evt); }
	};

	typedef unique_ptr<EventCallBack> EventCallBackPtr;

	vector<EventCallBackPtr>	m_EventCallBacks;
	int							m_NumListeners;
};

typedef unique_ptr<EventDispatcher> EventDispatcherPtr;

template<class C>
void EventDispatcher::AddListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
	EventCallBackPtr cb = EventCallBackPtr(new EventCallBack(eventType, proxy, fct));
	m_EventCallBacks.push_back(move(cb));
	m_NumListeners++;
}

template<class C>
void EventDispatcher::RemoveListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
	for (int i = 0 ; i < m_NumListeners ; i++)
	{
		EventCallBackPtr& cb = m_EventCallBacks[i];
		
		if (cb->GetType() == eventType && cb->GetFct<C>() == fct
			&& &(cb->GetProxy<C>()) == &proxy)
		{
			m_EventCallBacks.erase(m_EventCallBacks.begin() + i);
			m_NumListeners--;
			break;
		}
	}
}

#endif

