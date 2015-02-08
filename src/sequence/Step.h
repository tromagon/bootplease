#ifndef _SEQUENCESTEP_H_
#define _SEQUENCESTEP_H_

#include "ISequence.h"

/** Step **/

class Step
{
    friend class Sequence;

protected:
    explicit Step(ISequence& sequence) : m_Sequence(sequence) {}

    virtual bool IsAsync() { return false; };
    virtual void Run() {};

    ISequence& m_Sequence;
};

typedef unique_ptr<Step> StepPtr;

/** CallStep **/

template<class C, class P = void>
class CallStep : public Step
{
    friend class Sequence;

protected:
    CallStep(ISequence& sequence, void (C::*fct)(P&), C& proxy, P& params) : 
        Step(sequence), m_Fct(fct), m_Proxy(proxy), m_Params(params) {}
    
    virtual void Run() override;

private:
    void    (C::*m_Fct)(P&);
    C&      m_Proxy;
    P&      m_Params;
};

template<class C>
class CallStep<C, void> : public Step
{
    friend class Sequence;

protected:
    CallStep(ISequence& sequence, void (C::*fct)(), C& proxy) : 
        Step(sequence), m_Fct(fct), m_Proxy(proxy) {}

    virtual void Run() override;

private:
    void    (C::*m_Fct)();
    C&      m_Proxy;    
};

/** EventStep **/

class EventStep : public Step
{
    friend class Sequence;

protected:
    EventStep(ISequence& sequence, const Event& evt, EventDispatcherPtr& dispatcher) : 
        Step(sequence), m_Event(evt), m_Dispatcher(dispatcher) {}

    virtual void Run() override;

private:
    const Event&        m_Event;
    EventDispatcherPtr& m_Dispatcher;
};

/** WaitForEventStep **/

template<class C>
class WaitForEventStep : public Step
{
    friend class Sequence;

protected:
    WaitForEventStep(ISequence& sequence, const char* type, void (C::*fct)(const Event&), C& proxy, EventDispatcherPtr& dispatcher) :
        Step(sequence), m_Type(type), m_Fct(fct), m_Proxy(proxy), m_Dispatcher(dispatcher) {};

    bool IsAsync() override { return true; }
    virtual void Run() override;

    void OnWaitForEventReceived(const Event& evt);

private:
    const char*         m_Type;
    void                (C::*m_Fct)(const Event&);
    C&                  m_Proxy;
    EventDispatcherPtr& m_Dispatcher;
    int                 m_EventId;
};

template<>
class WaitForEventStep<void> : public Step
{
    friend class Sequence;

private:
    const char*         m_Type;
    EventDispatcherPtr& m_Dispatcher;

protected:
    WaitForEventStep(ISequence& sequence, const char* type, EventDispatcherPtr& dispatcher) : 
        Step(sequence), m_Type(type), m_Dispatcher(dispatcher) {};

    virtual bool IsAsync() override { return true; }

    virtual void Run() override;

    void OnWaitForEventReceived(const Event& evt);
};

/** Definitions **/

template<class C, class P>
void CallStep<C, P>::Run()
{
    m_Sequence.IncrementIndex();

    (&m_Proxy->*m_Fct)(m_Params);

    m_Sequence.CompleteStep();
}

template<class C>
void CallStep<C, void>::Run()
{
    m_Sequence.IncrementIndex();

    (&m_Proxy->*m_Fct)();

    m_Sequence.CompleteStep();
}

template<class C>
void WaitForEventStep<C>::Run()
{
    m_Dispatcher->AddListener(m_Type, &WaitForEventStep<C>::OnWaitForEventReceived, *this);
}

template<class C>
void WaitForEventStep<C>::OnWaitForEventReceived(const Event& evt)
{
    m_Dispatcher->RemoveListener(m_Type, &WaitForEventStep<C>::OnWaitForEventReceived, *this);

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

#endif
