#include "sequence\Sequence.h"
#include "sequence\SequenceEvent.h"

Sequence::Sequence(EventDispatcherPtr& dispatcher) : m_Dispatcher(dispatcher), m_NumSteps(0) {}

void Sequence::Dispatch(const Event& evt)
{
    StepPtr step = StepPtr(new EventStep(*this, evt, m_Dispatcher));
    m_List.push_back(move(step));
    m_NumSteps++;
}

void Sequence::Dispatch(const Event& evt, EventDispatcherPtr& dispatcher)
{
    StepPtr step = StepPtr(new EventStep(*this, evt, dispatcher));
    m_List.push_back(move(step));
    m_NumSteps++;
}

void Sequence::WaitFor(const char* eventType)
{
    StepPtr step = StepPtr(new WaitForEventStep<void>(*this, eventType, m_Dispatcher));
    m_List.push_back(move(step));
    m_NumSteps++;
}

void Sequence::WaitFor(const char* eventType, EventDispatcherPtr& dispatcher)
{
    StepPtr step = StepPtr(new WaitForEventStep<void>(*this, eventType, dispatcher));
    m_List.push_back(move(step));
    m_NumSteps++;
}

void Sequence::Start()
{
    SequenceEvent evt(SequenceEvent::STARTED, *this);
    EventDispatcher::Dispatch(evt);

    m_CurrentIndex = 0;
    if (m_CurrentIndex < m_NumSteps)
    {
        NextStep();
    }
}

bool Sequence::IsNextStepAsync()
{
    if (m_CurrentIndex + 1 < m_NumSteps)
    {
        StepPtr& nextStep = m_List[m_CurrentIndex + 1];
        return nextStep->IsAsync();
    }

    return false;
}

void Sequence::NextStep()
{
    StepPtr& step = m_List[m_CurrentIndex];

    if (IsNextStepAsync())
    {
        StepPtr& nextStep = m_List[m_CurrentIndex + 1];
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
    EventDispatcher::Dispatch(stepCompleteEvt);

    if (m_CurrentIndex < m_NumSteps)
    {
        NextStep();
    }
    else
    {
        SequenceEvent evt(SequenceEvent::COMPLETE, *this);
        EventDispatcher::Dispatch(evt);
    }
}
