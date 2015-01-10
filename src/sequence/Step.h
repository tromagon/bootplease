#ifndef _SEQUENCESTEP_H_
#define _SEQUENCESTEP_H_

#include "ISequence.h"

/** Step **/

class Step
{
	friend class Sequence;

protected:
	ISequence& m_Sequence;

protected:
	explicit Step(ISequence& sequence) : m_Sequence(sequence) {}
	virtual ~Step(){}

	virtual bool IsAsync() { return false; };
	virtual void Run() {};
};



/** CallStep **/

template<class C, class P = void>
class CallStep : public Step
{
	friend class Sequence;

private:
	void	(C::*m_Fct)(P&);
	C&		m_Proxy;
	P&		m_Params;

protected:
	CallStep(ISequence& sequence, void (C::*fct)(P&), C& proxy, P& params) : 
		Step(sequence), m_Fct(fct), m_Proxy(proxy), m_Params(params) {}
	
	void Run() override;
};

template<class C, class P>
void CallStep<C, P>::Run()
{
	m_Sequence.IncrementIndex();

	(&m_Proxy->*m_Fct)(m_Params);

	m_Sequence.CompleteStep();
}


template<class C>
class CallStep<C, void> : public Step
{
	friend class Sequence;

private:
	void	(C::*m_Fct)();
	C&		m_Proxy;    

protected:
	CallStep(ISequence& sequence, void (C::*fct)(), C& proxy) : 
		Step(sequence), m_Fct(fct), m_Proxy(proxy) {}

	void Run() override;
};

template<class C>
void CallStep<C, void>::Run()
{
	m_Sequence.IncrementIndex();

	(&m_Proxy->*m_Fct)();

	m_Sequence.CompleteStep();
}



/** EventStep **/

class EventStep : public Step
{
	friend class Sequence;

private:
	const Event&		m_Event;
	EventDispatcher&	m_Dispatcher;

protected:
	EventStep(ISequence& sequence, const Event& evt, EventDispatcher& dispatcher) : 
		Step(sequence), m_Event(evt), m_Dispatcher(dispatcher) {}

	void Run() override;
};



/** WaitForEventStep **/

template<class C>
class WaitForEventStep : public Step
{
	friend class Sequence;

private:
	const char*			m_Type;
	void				(C::*m_Fct)(const Event&);
	C&					m_Proxy;
	EventDispatcher&	m_Dispatcher;
	int					m_EventId;

protected:
	WaitForEventStep(ISequence& sequence, const char* type, void (C::*fct)(const Event&), C& proxy, EventDispatcher& dispatcher) :
		Step(sequence), m_Type(type), m_Fct(fct), m_Proxy(proxy), m_Dispatcher(dispatcher) {};

	bool IsAsync() override { return true; }
	void Run() override;

	void OnWaitForEventReceived(const Event& evt);
};

template<class C>
void WaitForEventStep<C>::Run()
{
	m_Dispatcher.AddListener(m_Type, &WaitForEventStep<C>::OnWaitForEventReceived, *this);
}

template<class C>
void WaitForEventStep<C>::OnWaitForEventReceived(const Event& evt)
{
	m_Dispatcher.RemoveListener(m_Type, &WaitForEventStep<C>::OnWaitForEventReceived, *this);

	if (m_Sequence.IsNextStepAsync())
	{
		m_Sequence.IncrementIndex();
		m_Sequence.CompleteStep();
		(&m_Proxy->*m_Fct)(evt);
	}
	else
	{
		(&m_Proxy->*m_Fct)(evt);
		m_Sequence.IncrementIndex();
		m_Sequence.CompleteStep();
	}
};

template<>
class WaitForEventStep<void> : public Step
{
	friend class Sequence;

private:
	const char*			m_Type;
	EventDispatcher&	m_Dispatcher;

protected:
	WaitForEventStep(ISequence& sequence, const char* type, EventDispatcher& dispatcher) : 
		Step(sequence), m_Type(type), m_Dispatcher(dispatcher) {};

	bool IsAsync() override { return true; }

	void Run() override;

	void OnWaitForEventReceived(const Event& evt);
};

#endif
