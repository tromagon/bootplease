#include "Sequence.h"

const char* SequenceEvent::STARTED = "SequenceEvent_STARTED";
const char* SequenceEvent::COMPLETE = "SequenceEvent_COMPLETE";
const char* SequenceEvent::STEP_COMPLETE = "SequenceEvent_STEP_COMPLETE";


Sequence::Sequence(EventDispatcher& dispatcher) : m_Dispatcher(dispatcher)
{
	m_List = nullptr;
}

Sequence::~Sequence()
{
	if (m_List)
	{
		const unsigned short l = m_List->size();
		for (int i = l - 1 ; i >= 0 ; i--)
		{
			delete (*m_List)[i];
			m_List->erase(m_List->begin() + i);
		}

		delete m_List;
	}
}

void Sequence::Dispatch(Event& evt, EventDispatcher* dispatcher)
{
	if (!m_List)
	{
		m_List = new vector<Step*>();
	}

	EventStep* step = new EventStep(*this, evt, (dispatcher ? *dispatcher : m_Dispatcher));
	m_List->push_back(step);
}

void Sequence::WaitFor(const char* eventType, EventDispatcher* dispatcher)
{
	if (!m_List)
	{
		m_List = new vector<Step*>();
	}

	WaitForEventStep<void>* step = new WaitForEventStep<void>(*this, eventType, (dispatcher ? *dispatcher : m_Dispatcher));
	m_List->push_back(step);
}

void Sequence::Start()
{
	SequenceEvent evt(SequenceEvent::STARTED, *this);
	m_SequenceDispatcher.Dispatch(evt);

	m_CurrentIndex = 0;
	m_NumSteps = m_List->size();

	if (m_CurrentIndex < m_NumSteps)
	{
		NextStep();
	}
}

bool Sequence::IsNextStepAsync()
{
	if (m_CurrentIndex + 1 < m_NumSteps)
	{
		Step* nextStep = (*m_List)[m_CurrentIndex + 1];
		return nextStep->IsAsync();
	}

	return false;
}

void Sequence::NextStep()
{
	Step* step = (*m_List)[m_CurrentIndex];
	bool isAsync = false;

	if (IsNextStepAsync())
	{
		Step* nextStep = (*m_List)[m_CurrentIndex + 1];
		nextStep->Run();
	}

	step->Run();
}

int Sequence::IncrementIndex()
{
	return ++m_CurrentIndex;
}

void Sequence::CompleteStep()
{
	SequenceEvent stepCompleteEvt(SequenceEvent::STEP_COMPLETE, *this);
	m_SequenceDispatcher.Dispatch(stepCompleteEvt);

	if (m_CurrentIndex < m_NumSteps)
	{
		NextStep();
	}
	else
	{
		SequenceEvent evt(SequenceEvent::COMPLETE, *this);
		m_SequenceDispatcher.Dispatch(evt);
	}
}
