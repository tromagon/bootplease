#ifndef _DIRECTCOMMANDMAP_H_
#define _DIRECTCOMMANDMAP_H_

#include "events\EventDispatcher.h"
#include "commands\CommandMap.h"

class Command;

class DirectCommandMap final : public CommandMap
{
public:
    explicit DirectCommandMap(EventDispatcherPtr& dispatcher, InjectorPtr& injector) 
        : CommandMap(dispatcher, injector) {}
    ~DirectCommandMap() {};

    void        Execute();

    template<class C>
    void        Map();

    template<class C>
    void        UnMap();

private:
    class IDirectCommandMapItemSpec
    {
    public:
        IDirectCommandMapItemSpec() {}
        virtual ~IDirectCommandMapItemSpec() {}
        virtual Command* GetCommand() = 0;
    };

    typedef unique_ptr<IDirectCommandMapItemSpec> DirectCommandMapItemSpecPtr;

    template<class C>
    class DirectCommandMapItemSpec : public IDirectCommandMapItemSpec
    {
    public:
        DirectCommandMapItemSpec(C& proxy, Command& (C::*fct)()) : m_Proxy(proxy), m_Fct(fct) {}
        virtual Command* GetCommand() override { return &((&m_Proxy->*m_Fct)()); }

        C&          GetProxy()                      { return m_Proxy; }
        Command&    (C::*GetFct())()                { return m_Fct; }

    private:
        C&          m_Proxy;
        Command&    (C::*m_Fct)();

    };

    class DirectCommandMapItem
    {
    public:
        template<class C>
        DirectCommandMapItem(C& proxy, Command& (C::*fct)()) 
            : m_Spec(DirectCommandMapItemSpecPtr(new DirectCommandMapItemSpec<C>(proxy, fct))) {}

        Command&    GetCommand()        { return *(m_Spec->GetCommand()); }

        template<class C>
        Command&    (C::*GetFct())()    { return static_cast<DirectCommandMapItemSpec<C>*>(m_Spec.get())->GetFct(); }

        template<class C>
        C&          GetProxy()          { return static_cast<DirectCommandMapItemSpec<C>*>(m_Spec.get())->GetProxy(); }

    private:
        DirectCommandMapItemSpecPtr    m_Spec;

    };

    typedef unique_ptr<DirectCommandMapItem> DirectCommandMapItemPtr;

    void            UnMapAll();

    template<class T>
    Command&        CreateCommand();

    vector<DirectCommandMapItemPtr>   m_Maps;
};

template<class T>
Command& DirectCommandMap::CreateCommand()
{
    return *(new T());
}

template<class C>
void DirectCommandMap::Map()
{
    m_Maps.push_back(DirectCommandMapItemPtr(new DirectCommandMapItem(*this, &DirectCommandMap::CreateCommand<C>)));
    m_NumMap++;
}

template<class C>
void DirectCommandMap::UnMap()
{
    const unsigned short l = m_Maps.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        DirectCommandMapItemPtr& mapping = m_Maps[i];

        if (mapping.GetFct<DirectCommandMap>() == &DirectCommandMap::CreateCommand<C>)
        {
            m_Maps.erase(m_Maps.begin() + i);
            m_NumMap--;
            return;
        }
    }
}

#endif