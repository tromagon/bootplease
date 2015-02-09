#ifndef _COMMAND_H_
#define _COMMAND_H_

//#include "events\EventDispatcher.h"
//#include "injection\Injector.h"

#include <memory>

using namespace std;

class EventCommandMap;
class DirectCommandMap;
class MediatorMap;

class Injector;
typedef unique_ptr<Injector> InjectorPtr;

class CommandMap;

class EventDispatcher;
typedef unique_ptr<EventDispatcher> EventDispatcherPtr;

class Event;

class Command
{
public:
    friend class EventCommandMap;
    friend class DirectCommandMap;

private:
    CommandMap&         m_CommandMap;
    MediatorMap*        m_MediatorMap;
    const Event*        m_Event;

private:
    void                SetEvent(const Event& evt);

protected:
    EventDispatcherPtr& GetDispatcher();
    InjectorPtr&        GetInjector();
    MediatorMap&        GetMediatorMap();
    const Event&        GetEvent();

public:
    Command(CommandMap& commandMap) : m_CommandMap(commandMap), m_Event(nullptr) {}
    virtual ~Command() {}

protected:
    template<class C>
    int     AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

    template<class C>
    void    RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy);

    void    DispatchContextEvent(const Event& evt);

    virtual void Execute() {}
    virtual void Detain() final;
    virtual void Release() final;
};


template<class C>
int Command::AddContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
    return GetDispatcher().AddListener(eventType, fct, proxy);
}

template<class C>
void Command::RemoveContextListener(const char* eventType, void (C::*fct)(const Event&), C& proxy)
{
    GetDispatcher().RemoveListener(eventType, fct, proxy);
}

#endif