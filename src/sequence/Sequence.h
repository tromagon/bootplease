#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "ISequence.h"
#include "Step.h"
#include <vector>

using namespace std;


class Sequence : public ISequence
{
private:
	EventDispatcher		m_SequenceDispatcher;
	EventDispatcher&	m_Dispatcher;
	vector<Step*>*		m_List;
	int					m_CurrentIndex;
	int					m_NumSteps;

public:
	explicit Sequence(EventDispatcher& dispatcher);
	~Sequence();

	virtual int		IncrementIndex() override;
	virtual void	CompleteStep() override;
	virtual bool	IsNextStepAsync() override;

	void			Dispatch(const Event& evt, EventDispatcher* dispatcher = nullptr);

	template<class C>
	void			Call(void (C::*fct)(), C& proxy);

	template<class C, class P>
	void			Call(void (C::*fct)(P&), C& proxy, P& params);

	void			WaitFor(const char* eventType, EventDispatcher* dispatcher = nullptr);

	template<class C>
	void			WaitFor(const char* eventType, void (C::*fct)(const Event&), C& proxy, EventDispatcher* dispatcher = nullptr);

	void			Start();

private:
	void NextStep();
};

template<class C>
void Sequence::Call(void (C::*fct)(), C& proxy)
{
	if (!m_List)
	{
		m_List = new vector<Step*>();
	}

	CallStep<C>* step = new CallStep<C>(*this, fct, proxy);
	m_List->push_back(step);
}

template<class C, class P>
void Sequence::Call(void (C::*fct)(P&), C& proxy, P& params)
{
	if (!m_List)
	{
		m_List = new vector<Step*>();
	}

	CallStep<C, P>* step = new CallStep<C, P>(*this, fct, proxy, params);
	m_List->push_back(step);
}

template<class C>
void Sequence::WaitFor(const char* eventType, void (C::*fct)(const Event&), C& proxy, EventDispatcher* dispatcher)
{
	if (!m_List)
	{
		m_List = new vector<Step*>();
	}

	WaitForEventStep<C>* step = new WaitForEventStep<C>(*this, eventType, fct, proxy, (dispatcher ? *dispatcher : m_Dispatcher));
	m_List->push_back(step);
}

#endif