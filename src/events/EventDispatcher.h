#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include <vector>

using namespace std;

class Event
{
private:
	const char* m_Type;

public:
	const char* GetType() { return m_Type; }

public:
	explicit Event(const char* type):m_Type(type) {};
	virtual ~Event() {};
};

class IEventCallBackSpec
{
public:
	IEventCallBackSpec() {}
	virtual ~IEventCallBackSpec() {}

	virtual void operator()(Event& evt) {}
};

template<class C>
class EventCallBackSpec : public IEventCallBackSpec
{
private:
	C& m_Proxy;
	void (C::*m_Fct)(Event&);

public:
	C&		GetProxy()						{ return m_Proxy; }
	void	(C::*GetFct())(Event&)			{ return m_Fct; }

public:
	EventCallBackSpec(C& proxy, void (C::*fct)(Event&)) : m_Proxy(proxy), m_Fct(fct) {}
	void operator()(Event& evt) override	{ (&m_Proxy->*m_Fct)(evt); }
};


class EventCallBack
{
private:
	IEventCallBackSpec* spec;

public:
	template<class C>
	void	(C::*GetFct())(Event&)		{ return static_cast<EventCallBackSpec<C>*>(spec)->GetFct(); }
	template<class C>
	C&		GetProxy()					{ return static_cast<EventCallBackSpec<C>*>(spec)->GetProxy(); }

public:
	template<class C>
	EventCallBack(C& proxy, void (C::*fct)(Event&)) { spec = new EventCallBackSpec<C>(proxy, fct); }
	~EventCallBack() { delete spec; }

	void operator()(Event& evt)			{ (*spec)(evt);	}
};


class EventDispatcher
{
private:
	struct Listener
	{
	private:
		const int		m_Id;
		const char*		m_Type;
		EventCallBack&	m_Cb;

	public:
		int				GetId()			{ return m_Id; }
		const char*		GetType()		{ return m_Type; }
		EventCallBack&	GetCallBack()	{ return m_Cb; }

	public:
		Listener(const int id, const char* type, EventCallBack& cb) : 
			m_Id(id), m_Type(type), m_Cb(cb) {}
	};

	vector<Listener*>* m_Listeners;

	int m_CurrentId;

public:
	EventDispatcher();
	virtual ~EventDispatcher();

	void	RemoveListener(int listenerId);
	bool	HasListener(const char* eventType);
	void	Dispatch(Event& evt);

	template<class C>
	int		AddListener(const char* eventType, void (C::*fct)(Event&), C& proxy);

	template<class C>
	void	RemoveListener(const char* eventType, void (C::*fct)(Event&), C& proxy);

private:
	void	RemoveAllListeners();
};

template<class C>
int EventDispatcher::AddListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
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

	return listenerId;
}

template<class C>
void EventDispatcher::RemoveListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	const unsigned short l = m_Listeners->size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		Listener* listener = (*m_Listeners)[i];
		EventCallBack& cb = listener->GetCallBack();
		if (listener->GetType() == eventType && cb.GetFct<C>() == fct
			&& &(cb.GetProxy<C>()) == &proxy)
		{
			m_Listeners->erase(m_Listeners->begin() + i);
			delete &(listener->GetCallBack());
			delete listener;
			break;
		}
	}
}

#endif

