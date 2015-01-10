#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
	m_Listeners = nullptr;
	m_CurrentId = 0;
}

EventDispatcher::~EventDispatcher()
{
	RemoveAllListeners();

	if (m_Listeners)
	{
		delete m_Listeners;
	}	
}

void EventDispatcher::RemoveListener(int listenerId)
{
	const unsigned short l = m_Listeners->size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		Listener* listener = (*m_Listeners)[i];
		if (listener->GetId() == listenerId)
		{
			m_Listeners->erase(m_Listeners->begin() + i);
			delete &(listener->GetCallBack());
			delete listener;
			break;
		}
	}
}

bool EventDispatcher::HasListener(const char* eventType)
{
	if (!m_Listeners)
	{
		return false;
	}

	const unsigned short l = m_Listeners->size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		Listener* listener = (*m_Listeners)[i];
		const EventCallBack& cb = listener->GetCallBack();
		if (listener->GetType() == eventType)
		{
			return true;
		}
	}

	return false;
}

void EventDispatcher::Dispatch(const Event& evt)
{
	if (!m_Listeners)
	{
		return;
	}

	const unsigned short l = m_Listeners->size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		Listener* listener = (*m_Listeners)[i];
		if (listener->GetType() == evt.GetType())
		{
			listener->GetCallBack()(evt);
		}
	}
}

void EventDispatcher::RemoveAllListeners()
{
	if (!m_Listeners) return;

	const unsigned short l = m_Listeners->size();
	for (int i = l - 1 ; i >= 0 ; i--)
	{
		Listener* listener = (*m_Listeners)[i];
		m_Listeners->erase(m_Listeners->begin() + i);
		delete &(listener->GetCallBack());
		delete listener;
	}
}


