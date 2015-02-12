#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "events\Event.h"
#include "events\EventDispatcher.h"
#include <memory>

class MediatorMap;
class View;

class Injector;
typedef unique_ptr<Injector> InjectorPtr;

class Mediator
{
    friend class MediatorMap;

public:
    Mediator() {}
    virtual ~Mediator() {}

    template<class C>
    C&                  GetView()               { return static_cast<C&>(*m_View); }

    View&               GetView()               { return *m_View; }
    void                SetView(View& value)    { m_View = &value; }

    MediatorMap&            GetMediatorMap()    { return *m_MediatorMap; }
    InjectorPtr&            GetInjector();
    EventDispatcherPtr&     GetDispatcher();

protected:
    template<class C>
    int     AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

    template<class C>
    void    RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

    void    DispatchContextEvent(const Event& evt);

    virtual void OnInitialized() {};

private:
    void    SetMediatorMap(MediatorMap& mediatorMap)            { m_MediatorMap = &mediatorMap; }

    View*               m_View;
    MediatorMap*        m_MediatorMap;
};

typedef unique_ptr<Mediator> MediatorPtr;

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