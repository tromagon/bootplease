#include "Step.h"

void EventStep::Run()
{
	bool nextStepAsync = m_Sequence.IsNextStepAsync();

	m_Sequence.IncrementIndex();

	m_Dispatcher.Dispatch(m_Event);

	if (!nextStepAsync)
	{
		m_Sequence.CompleteStep();
	}
}

void WaitForEventStep<void>::Run()
{
	m_Dispatcher.AddListener(m_Type, &WaitForEventStep<void>::OnWaitForEventReceived, *this);
}

void WaitForEventStep<void>::OnWaitForEventReceived(Event& evt)
{
	m_Dispatcher.RemoveListener(m_Type, &WaitForEventStep<void>::OnWaitForEventReceived, *this);

	m_Sequence.IncrementIndex();

	m_Sequence.CompleteStep();
}