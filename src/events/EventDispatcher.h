#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include "Event.h"
#include <vector>

using namespace std;

class EventDispatcher
{
private:
	class IEventCallBackSpec
	{
	public:
		IEventCallBackSpec() {}
		virtual ~IEventCallBackSpec() {}

		virtual void operator()(const Event& evt) {}
	};

	template<class C>
	class EventCallBackSpec : public IEventCallBackSpec
	{
	private:
		C&		m_Proxy;
		void	(C::*m_Fct)(const Event&);

	public:
		C&		GetProxy()								{ return m_Proxy; }
		void	(C::*GetFct())(const Event&)			{ return m_Fct; }

	public:
		EventCallBackSpec(C& proxy, void (C::*fct)(const Event&)) : m_Proxy(proxy), m_Fct(fct) {}
		void operator()(const Event& evt) override		{ (&m_Proxy->*m_Fct)(evt); }
	};


	class EventCallBack
	{
	private:
		IEventCallBackSpec* spec;

	public:
		template<class C>
		void	(C::*GetFct())(const Event&)					{ return static_cast<EventCallBackSpec<C>*>(spec)->GetFct(); }
		template<class C>
		C&		GetProxy()										{ return static_cast<EventCallBackSpec<C>*>(spec)->GetProxy(); }

	public:
		template<class C>
		EventCallBack(C& proxy, void (C::*fct)(const Event&))	{ spec = new EventCallBackSpec<C>(proxy, fct); }
		~EventCallBack()										{ delete spec; }

		void operator()(const Event& evt)						{ (*spec)(evt);	}
	};

	struct Listener
	{
	private:
		const int				m_Id;
		const char*				m_Type;
		EventCallBack&			m_Cb;

	public:
		int						GetId()				{ return m_Id; }
		const char*				GetType()			{ return m_Type; }
		EventCallBack&			GetCallBack()		{ return m_Cb; }

	public:
		Listener(const int id, const char* type, EventCallBack& cb) : 
			m_Id(id), m_Type(type), m_Cb(cb) {}
	};

	vector<Listener*>*	m_Listeners;
	int					m_CurrentId;
	int					m_NumListeners;

public:
	EventDispatcher();
	virtual ~EventDispatcher();

	void	RemoveListener(int listenerId);
	bool	HasListener(const char* eventType);
	void	Dispatch(const Event& evt);

	template<class C>
	int		AddListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

	template<class C>
	void	RemoveListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

private:
	void	RemoveAllListeners();
};

template<class C>
int EventDispatcher::AddListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
	if (!m_Listeners)
	{
		m_Listeners = new vector<Listener*>();
	}

	int listenerId = m_CurrentId;
	m_CurrentId++;

	EventCallBack* cb = new EventCallBack(proxy, fct);

	Listener* listener = new Listener(listenerId, eventType, *cb);
	m_Listeners->push_back(listener);
	m_NumListeners++;

	return listenerId;
}

template<class C>
void EventDispatcher::RemoveListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
	Listener* listener;
	EventCallBack* cb;

	const unsigned short l = m_Listeners->size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		listener = (*m_Listeners)[i];
		cb = &listener->GetCallBack();

		if (listener->GetType() == eventType && cb->GetFct<C>() == fct
			&& &(cb->GetProxy<C>()) == &proxy)
		{
			m_Listeners->erase(m_Listeners->begin() + i);
			delete cb;
			delete listener;
			m_NumListeners--;

			break;
		}
	}
}

#endif

