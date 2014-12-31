#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "Display.h"
#include "Transitions.h"
#include <vector>

using namespace std;

class TransitionItemSpecBase
{
private:
	Transition&		m_Transition;

public:
	Transition&		GetTransition()			{ return m_Transition; }

public:
	explicit TransitionItemSpecBase(Transition&	transition) : m_Transition(transition) {}
	~TransitionItemSpecBase() {}
};

template<class C>
class TransitionItemSpec : public TransitionItemSpecBase
{
private:
	Transition&		(C::*m_Fct)();

public:
	Transition&		(C::*GetFunction())()	{ return m_Fct; }

public:
	explicit TransitionItemSpec(Transition&	transition, Transition& (C::*fct)()) 
		: TransitionItemSpecBase(transition), m_Fct(fct) {}

	~TransitionItemSpec() {}
};

class TransitionItem
{
private:
	TransitionItemSpecBase& m_Spec;

public:
	template<class C>
	explicit TransitionItem(Transition&	transition, Transition& (C::*fct)())
	{
		m_Spec = new TransitionItemSpec<C>(transition, fct);
	}

	Transition&		GetTransition()
	{
		return m_Spec.GetTransition();
	}

	template<class C>
	Transition&		(C::*GetFunction())() 
	{ 
		return (static_cast<TransitionItemSpec<C>&>(m_Spec)).GetFunction(); 
	}
};


class ScreenManagerEvent : public Event
{
public:
	static const char* TRANSITION_COMPLETE;

public:
	explicit ScreenManagerEvent(const char* type) : Event(type) {}
	virtual ~ScreenManagerEvent() {}	
};


class ScreenManager : public EventDispatcher
{
private:
	EventDispatcher				m_Dispatcher;
	bool						m_Busy;
	vector<TransitionItem*>		m_Transitions;
	vector<IDisplay*>			m_ScreenStack;
	TweenManager&				m_TweenManager;

public:
	explicit ScreenManager(TweenManager& tweenManager) : m_TweenManager(tweenManager) {}
	~ScreenManager() {}

	template<class C>
	void ShowScreen(IDisplay& screen, Transition& (C::*fct)(), C& proxy);

	void ShowPreviousScreen() {};

private:
	template<class C>
	Transition* GetTransition(Transition& (C::*fct)());

	void OnNextScreen(Event& evt);
};

template<class C>
void ScreenManager::ShowScreen(IDisplay& screen, Transition& (C::*fct)(), C& proxy)
{
	if (m_Busy) return;

	Transition* transition = GetTransition(fct);
	if (!transition)
	{
		transition = proxy.fct();
		transition->SetTweenManager(m_TweenManager);
		transition->AddListener(TransitionEvent::COMPLETE, &ScreenManager::OnNextScreen, *this);

		TransitionItem& item(transition, fct);
		m_Transitions.push_back(&item);
	}

	int numViews = m_ScreenStack.size();
	if (numViews > 0)
	{
		transition->SetPreviousScreen(*(m_ScreenStack[numViews - 1]));
	}

	transition->SetNextScreen(screen);
	m_ScreenStack.push_back(&screen);

	m_Busy = true;
}

template<class C>
Transition* ScreenManager::GetTransition(Transition& (C::*fct)())
{
	const unsigned short l = m_Transitions.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		TransitionItem& item = *m_Transitions[i];
		if (item.GetFunction<C>() == fct)
		{
			return &item.GetTransition();
		}
	}

	return nullptr;
}

#endif