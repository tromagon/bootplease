#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "events\Event.h"
#include "events\EventDispatcher.h"
#include "mediator\View.h"
#include "MediatorMap.h"

class Mediator
{
    friend class MediatorMap;

private:
    View*               m_View;
    MediatorMap*        m_MediatorMap;

public:
    template<class C>
    C&                  GetView()                               { return static_cast<C&>(*m_View); }

    View&               GetView()                               { return *m_View; }
    void                SetView(View& value)                    { m_View = &value; }

    MediatorMap&            GetMediatorMap()                        { return *m_MediatorMap; }
    InjectorPtr&            GetInjector()                           { return m_MediatorMap->GetInjector(); } 
    EventDispatcherPtr&     GetDispatcher()                         { return m_MediatorMap->GetDispatcher(); }

protected:
    Mediator() {}
    virtual ~Mediator() {}

    template<class C>
    int     AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

    template<class C>
    void    RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

    void    DispatchContextEvent(const Event& evt);

    virtual void OnInitialized() {};

private:
    void    SetMediatorMap(MediatorMap& mediatorMap)            { m_MediatorMap = &mediatorMap; }
};


template<class C>
int Mediator::AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
    return GetDispatcher().AddListener(eventType, fct, proxy);
}

template<class C>
void Mediator::RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
    GetDispatcher().RemoveListener(eventType, fct, proxy);
}

#endif