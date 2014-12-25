#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "EventDispatcher.h"

class CommandMap;

class Command
{
private:
	EventDispatcher*	m_Dispatcher;
	CommandMap*			m_CommandMap;
	Event*				m_Event;

public:
	EventDispatcher&	GetDispatcher()								{ return *m_Dispatcher; }
	void				SetDispatcher(EventDispatcher& dispatcher)	{ m_Dispatcher = &dispatcher; }
	CommandMap&			GetCommandMap()								{ return *m_CommandMap; }
	void				SetCommandMap(CommandMap& commandMap)		{ m_CommandMap = &commandMap; }
	Event&				GetEvent()									{ return *m_Event; }
	void				SetEvent(Event& evt)						{ m_Event = &evt; }

public:
	Command() {}
	virtual ~Command() {}

	virtual void execute() {};
};

class CommandMapItemSpecBase
{
public:
	CommandMapItemSpecBase() {}
	virtual ~CommandMapItemSpecBase() {}
	virtual Command* GetCommand() { return nullptr; }
};

template<class C>
class CommandMapItemSpec : public CommandMapItemSpecBase
{
private:
	C&			m_Proxy;
	Command&	(C::*m_Fct)();

public:
	C&			GetProxy()						{ return m_Proxy; }
	Command&	(C::*GetFct())()				{ return m_Fct; }

public:
	CommandMapItemSpec(C& proxy, Command& (C::*fct)()) : m_Proxy(proxy), m_Fct(fct) {}
	virtual Command* GetCommand() override { return &((&m_Proxy->*m_Fct)()); }
};

class CommandMapItem
{
private:
	const char*					m_EventType;
	CommandMapItemSpecBase*		m_Spec;

public:
	const char*					GetEventType()	{ return m_EventType; };
	Command&					GetCommand()	{ return *(m_Spec->GetCommand()); }

	template<class C>
	Command&	(C::*GetFct())()			{ return static_cast<CommandMapItemSpec<C>*>(m_Spec)->GetFct(); }

	template<class C>
	C&			GetProxy()					{ return static_cast<CommandMapItemSpec<C>*>(m_Spec)->GetProxy(); }

public:
	template<class C>
	CommandMapItem(const char* eventType, C& proxy, Command& (C::*fct)()) 
		: m_EventType(eventType) { m_Spec = new CommandMapItemSpec<C>(proxy, fct); };

	~CommandMapItem() { delete m_Spec; };
};


class CommandMap
{
private:
	EventDispatcher&			m_Dispatcher;
	vector<CommandMapItem*>		m_Maps;
	vector<Command*>			m_Detained;

public:
	explicit CommandMap(EventDispatcher& dispatcher) : m_Dispatcher(dispatcher) {}
	~CommandMap() {}

	void				Detain(Command& command);
	void				Release(Command& command);

	template<class C>
	void				Map(const char* eventType, Command& (C::*fct)(), C& proxy);

	template<class C>
	void				UnMap(const char* eventType, Command& (C::*fct)(), C& proxy);

private:
	int					GetDetainedIndex(Command& command);
	void				OnCommandEvent(Event& evt);
};

template<class C>
void CommandMap::Map(const char* eventType, Command& (C::*fct)(), C& proxy)
{
	if (!m_Dispatcher.HasListener(eventType))
	{
		m_Dispatcher.AddListener(eventType, &CommandMap::OnCommandEvent, *this);
	}
	
	CommandMapItem* mapItem = new CommandMapItem(eventType, proxy, fct);
	m_Maps.push_back(mapItem);
}

template<class C>
void CommandMap::UnMap(const char* eventType, Command& (C::*fct)(), C& proxy)
{
	if (m_Dispatcher.HasListener(eventType))
	{
		m_Dispatcher.RemoveListener(eventType, &CommandMap::OnCommandEvent, *this);
	}
	
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		CommandMapItem& mapping = *m_Maps[i];

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