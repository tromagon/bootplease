#ifndef _EVENTCOMMANDMAP_H_
#define _EVENTCOMMANDMAP_H_

#include "EventDispatcher.h"
#include "Context.h"
#include "CommandMap.h"

class Command;

class EventCommandMap : public CommandMap
{
	friend class Context;

private:
	class EventCommandMapItemSpecBase
	{
	public:
		EventCommandMapItemSpecBase() {}
		virtual ~EventCommandMapItemSpecBase() {}
		virtual Command* GetCommand() { return nullptr; }
	};

	template<class C>
	class EventCommandMapItemSpec : public EventCommandMapItemSpecBase
	{
	private:
		C&			m_Proxy;
		Command&	(C::*m_Fct)();

	public:
		C&			GetProxy()						{ return m_Proxy; }
		Command&	(C::*GetFct())()				{ return m_Fct; }

	public:
		EventCommandMapItemSpec(C& proxy, Command& (C::*fct)()) : m_Proxy(proxy), m_Fct(fct) {}
		virtual Command* GetCommand() override { return &((&m_Proxy->*m_Fct)()); }
	};

	class EventCommandMapItem
	{
	private:
		const char*					m_EventType;
		EventCommandMapItemSpecBase*		m_Spec;

	public:
		const char*					GetEventType()	{ return m_EventType; };
		Command&					GetCommand()	{ return *(m_Spec->GetCommand()); }

		template<class C>
		Command&	(C::*GetFct())()			{ return static_cast<EventCommandMapItemSpec<C>*>(m_Spec)->GetFct(); }

		template<class C>
		C&			GetProxy()					{ return static_cast<EventCommandMapItemSpec<C>*>(m_Spec)->GetProxy(); }

	public:
		template<class C>
		EventCommandMapItem(const char* eventType, C& proxy, Command& (C::*fct)()) 
			: m_EventType(eventType) { m_Spec = new EventCommandMapItemSpec<C>(proxy, fct); };

		~EventCommandMapItem() { delete m_Spec; };
	};

private:
	vector<EventCommandMapItem*>	m_Maps;
	vector<Command*>				m_Detained;

public:
	explicit EventCommandMap(Context& context) : CommandMap(context) {}
	~EventCommandMap() {}

	template<class C>
	void				Map(const char* eventType, Command& (C::*fct)(), C& proxy);

	template<class C>
	void				UnMap(const char* eventType, Command& (C::*fct)(), C& proxy);

private:
	void				OnCommandEvent(const Event& evt);
};

template<class C>
void EventCommandMap::Map(const char* eventType, Command& (C::*fct)(), C& proxy)
{
	EventDispatcher& dispatcher = GetDispatcher();
	if (!dispatcher.HasListener(eventType))
	{
		dispatcher.AddListener(eventType, &EventCommandMap::OnCommandEvent, *this);
	}
	
	EventCommandMapItem* mapItem = new EventCommandMapItem(eventType, proxy, fct);
	m_Maps.push_back(mapItem);
}

template<class C>
void EventCommandMap::UnMap(const char* eventType, Command& (C::*fct)(), C& proxy)
{
	EventDispatcher& dispatcher = GetDispatcher();
	if (dispatcher.HasListener(eventType))
	{
		dispatcher.RemoveListener(eventType, &EventCommandMap::OnCommandEvent, *this);
	}
	
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		EventCommandMapItem& mapping = *m_Maps[i];

		if (mapping.GetEventType() == eventType && mapping.GetFct<C>() == fct
			&& &(mapping.GetProxy<C>()) == &proxy)
		{
			m_Maps.erase(m_Maps.begin() + i);
			delete &mapping;
			return;
		}
	}
}

#endif