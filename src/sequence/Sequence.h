#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "sequence\ISequence.h"
#include "sequence\Step.h"
#include <vector>

using namespace std;

class Sequence : public ISequence
{
public:
    explicit Sequence(EventDispatcherPtr& dispatcher);
    ~Sequence() {};

    virtual int     IncrementIndex() override;
    virtual void    CompleteStep() override;
    virtual bool    IsNextStepAsync() override;

    void            Start();
    void            Dispatch(const Event& evt);
    void            Dispatch(const Event& evt, EventDispatcherPtr& dispatcher);
    void            WaitFor(const char* eventType);
    void            WaitFor(const char* eventType, EventDispatcherPtr& dispatcher);

    template<class C>
    void            Call(void (C::*fct)(), C& proxy);
    template<class C>
    void            WaitFor(const char* eventType, void (C::*fct)(const Event&), C& proxy);
    template<class C>
    void            WaitFor(const char* eventType, void (C::*fct)(const Event&), C& proxy, EventDispatcherPtr& dispatcher);

private:
    void            NextStep();

    EventDispatcherPtr&         m_Dispatcher;
    vector<StepPtr>             m_List;
    int                         m_CurrentIndex;
    int                         m_NumSteps;
};

template<class C>
void Sequence::Call(void (C::*fct)(), C& proxy)
{
    StepPtr step = StepPtr(new CallStep<C>(*this, fct, proxy));
    m_List.push_back(move(step));
    m_NumSteps++;
}

template<class C>
void Sequence::WaitFor(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
    StepPtr step = StepPtr(new WaitForEventStep<C>(*this, eventType, fct, proxy, m_Dispatcher));
    m_List.push_back(move(step));
    m_NumSteps++;
}

template<class C>
void Sequence::WaitFor(const char* eventType, void (C::*fct)(const Event&), C& proxy, EventDispatcherPtr& dispatcher)
{
    StepPtr step = StepPtr(new WaitForEventStep<C>(*this, eventType, fct, proxy, dispatcher));
    m_List.push_back(move(step));
    m_NumSteps++;
}

#endif