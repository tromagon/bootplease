#ifndef _EVENTCOMMANDMAP_H_
#define _EVENTCOMMANDMAP_H_

#include "events\EventDispatcher.h"
#include "injection\Context.h"
#include "commands\CommandMap.h"
#include <unordered_map>

using namespace std;

class Command;

class EventCommandMap final : public CommandMap
{
public:
    explicit EventCommandMap(EventDispatcherPtr& dispatcher, InjectorPtr& injector) : CommandMap(dispatcher, injector) {}
    ~EventCommandMap() {};

    template<class C>
    void                Map(const char* eventType);

    template<class C>
    void                UnMap(const char* eventType);

private:
    class IEventCommandMapItemSpec
    {
    public:
        IEventCommandMapItemSpec() {}
        virtual ~IEventCommandMapItemSpec() {}
        virtual Command* GetCommand() = 0;
    };

    typedef unique_ptr<IEventCommandMapItemSpec> EventCommandMapItemSpecPtr;

    template<class C>
    class EventCommandMapItemSpec : public IEventCommandMapItemSpec
    {
    public:
        EventCommandMapItemSpec(C& proxy, Command& (C::*fct)()) : m_Proxy(proxy), m_Fct(fct) {}
        virtual Command* GetCommand() override { return &((&m_Proxy->*m_Fct)()); }

        C&          GetProxy()          { return m_Proxy; }
        Command&    (C::*GetFct())()    { return m_Fct; }

    private:
        C&          m_Proxy;
        Command&    (C::*m_Fct)();
    };

    class EventCommandMapItem
    {
    public:
        template<class C>
        EventCommandMapItem(const char* eventType, C& proxy, Command& (C::*fct)()) 
            : m_EventType(eventType), m_Spec(EventCommandMapItemSpecPtr(new EventCommandMapItemSpec<C>(proxy, fct))) {}

        const char* GetEventType()      { return m_EventType; };
        Command&    GetCommand()        { return *(m_Spec->GetCommand()); }

        template<class C>
        Command&    (C::*GetFct())()    { return static_cast<EventCommandMapItemSpec<C>*>(m_Spec.get())->GetFct(); }

        template<class C>
        C&          GetProxy()          { return static_cast<EventCommandMapItemSpec<C>*>(m_Spec.get())->GetProxy(); }

    private:
        const char*                     m_EventType;
        EventCommandMapItemSpecPtr      m_Spec;
    };

    typedef unique_ptr<EventCommandMapItem> EventCommandMapItemPtr;

    void                UnMapAll();
    void                OnCommandEvent(const Event& evt);

    template<class T>
    Command&            CreateCommand();

    vector<EventCommandMapItemPtr>  m_Maps;
};

template<class T>
Command& EventCommandMap::CreateCommand()
{
    return *(new T());
}

template<class C>
void EventCommandMap::Map(const char* eventType)
{
    m_Dispatcher->AddListener(eventType, &EventCommandMap::OnCommandEvent, *this);
    m_Maps.push_back(EventCommandMapItemPtr(new EventCommandMapItem(eventType, *this, &EventCommandMap::CreateCommand<C>)));
    m_NumMap++;
}

template<class C>
void EventCommandMap::UnMap(const char* eventType)
{
    m_Dispatcher->RemoveListener(eventType, &EventCommandMap::OnCommandEvent, *this);

    const unsigned short l = m_Maps.size();
    for (int i = l - 1 ; i >= 0 ; i--)
    {
        EventCommandMapItemPtr& mapping = m_Maps[i];

        if (mapping->GetEventType() == eventType && 
            mapping->GetFct<EventCommandMap>() == &EventCommandMap::CreateCommand<C>)
        {
            m_Maps.erase(m_Maps.begin() + i);
            m_NumMap--;
            return;
        }
    }
}

#endif