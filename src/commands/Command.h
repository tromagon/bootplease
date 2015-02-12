#ifndef _COMMAND_H_
#define _COMMAND_H_

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
    friend class EventCommandMap;
    friend class DirectCommandMap;

public:
    Command() : m_IsDetained(false), m_Event(nullptr) {}
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

    EventDispatcherPtr& GetDispatcher();
    InjectorPtr&        GetInjector();
    const Event&        GetEvent();
    bool                GetIsDetained();

private:
    void                SetEvent(const Event& evt);
    void                SetCommandMap(CommandMap& commandMap)   { m_CommandMap = &commandMap; }

    CommandMap*         m_CommandMap;
    const Event*        m_Event;
    bool                m_IsDetained;
};

typedef unique_ptr<Command> CommandPtr;

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