#ifndef _MEDIATORMAP_H_
#define _MEDIATORMAP_H_

#include "mediator\View.h"
#include "injection\Injector.h"
#include "events\EventDispatcher.h"
#include <vector>

using namespace std;

class Mediator;

class MediatorMap final
{
private:
    class MediatorMapper;

public:
    explicit MediatorMap(EventDispatcherPtr& eventDispatcher, InjectorPtr& injector) 
        : m_EventDispatcher(eventDispatcher), m_Injector(injector) {}
    ~MediatorMap();

    EventDispatcherPtr& GetDispatcher()     { return m_EventDispatcher; }
    InjectorPtr&        GetInjector()       { return m_Injector; }

    template<class C>
    MediatorMapper& Map(const char* id, View& (C::*fct)(), C& proxy);

    template<class C>
    C*  GetView(const char* id);

    void    UnMap(const char* id);
    void    DisposeView(View& view);
    void    DisposeViewById(const char* id);

private:
    class IMapperSpec
    {
    public:
        IMapperSpec() {}
        virtual ~IMapperSpec() {}

        virtual void* GetInstance() { return nullptr; }
    };

    template<class D, class C>
    class MapperSpec : public IMapperSpec
    {
    public:
        MapperSpec(D& (C::*fct)(), C& proxy) : m_Fct(fct), m_Proxy(proxy) {}
        virtual ~MapperSpec() {}
    
        void* GetInstance() override { return &(&m_Proxy->*m_Fct)(); }

        D&  (C::*GetFunction())()   { return m_Fct; }
        C&  GetProxy()              { return m_Proxy; }

    private:
        D& (C::*m_Fct)();
        C& m_Proxy;
    };

    template<class D>
    class BaseMapper
    {
    public:
        virtual ~BaseMapper() { delete m_Spec; }

        template<class C>
        D&  (C::*GetFunction())()   { return (static_cast<MapperSpec<D, C>*>(m_Spec))->GetFunction(); }

        template<class C>
        C&  GetProxy()              { return (static_cast<MapperSpec<D, C>*>(m_Spec))->GetProxy(); }

        D&  GetInstance()           { return *(static_cast<D*>(m_Spec->GetInstance())); }

    protected:
        IMapperSpec* m_Spec;
    };

    class ViewMapper : public BaseMapper<View>
    {
    public:
        template<class C>
        ViewMapper(View& (C::*fct)(), C& proxy);
        ~ViewMapper() {}
    };

    class MediatorMapper : public BaseMapper<Mediator>
    {
    public:
        MediatorMapper() {}
        ~MediatorMapper() {}

        template<class C>
        void To(Mediator& (C::*fct)(), C& proxy);
    };

    class MediatorMapItem
    {
    public:
        MediatorMapItem(const char* id, ViewMapper& viewMapper) 
            : m_Id(id), m_ViewMapper(viewMapper), m_MediatorMapper(*(new MediatorMapper())) {}
        ~MediatorMapItem();

        const char*         GetId()                     { return m_Id; }
        MediatorMapper&     GetMediatorMapper()         { return m_MediatorMapper; }
        View&               GetViewInstance()           { return m_ViewMapper.GetInstance(); }
        Mediator&           GetMediatorInstance()       { return m_MediatorMapper.GetInstance(); }

    private:
        const char*         m_Id;
        ViewMapper&         m_ViewMapper;
        MediatorMapper&     m_MediatorMapper;
    };

    class ViewMediatorItem
    {
    public:
        ViewMediatorItem(const char* id, View& view, Mediator& mediator) 
            : m_Id(id), m_View(view), m_Mediator(mediator) {}
        ~ViewMediatorItem();

        const char*     GetId()         { return m_Id; }
        View&           GetView()       { return m_View; }
        Mediator&       GetMediator()   { return m_Mediator; }

    private:
        const char*         m_Id;
        View&               m_View;
        Mediator&           m_Mediator;
    };

    vector<MediatorMapItem*>    m_Map;
    vector<ViewMediatorItem*>   m_VmList;

    EventDispatcherPtr&         m_EventDispatcher;
    InjectorPtr&                m_Injector;

    View*               GetViewInstance(const char* id);
    ViewMediatorItem&   AddViewMediatorItem(MediatorMapItem* item);
    void                UnMapAll();
    void                DisposeAll();

    template<class T>
    Mediator&           CreateMediator();

    template<class T>
    View&               CreateView();
};

template<class T>
Mediator& MediatorMap::CreateMediator()
{
    return *(new T(*this));
}

template<class T>
View& MediatorMap::CreateView()
{
    return *(new T(*this));
}

template<class C>
C* MediatorMap::GetView(const char* id)
{
    C* view = static_cast<C*>(GetViewInstance(id));

    if (view) return view;

    MediatorMapItem* item;
    ViewMediatorItem* vm;

    const unsigned short l = m_Map.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        item = m_Map[i];
        if (item->GetId() == id)
        {
            vm = &AddViewMediatorItem(item);
            return static_cast<C*>(&vm->GetView());
        }
    }

    return nullptr;
}

template<class C>
MediatorMap::MediatorMapper& MediatorMap::Map(const char* id, View& (C::*fct)(), C& proxy)
{
    MediatorMapItem* item;
    item = new MediatorMapItem(id, *(new ViewMapper(fct, proxy)));
    m_Map.push_back(item);

    return item->GetMediatorMapper();
}

template<class C>
MediatorMap::ViewMapper::ViewMapper(View& (C::*fct)(), C& proxy)
{
    m_Spec = new MapperSpec<View, C>(fct, proxy);
}

template<class C>
void MediatorMap::MediatorMapper::To(Mediator& (C::*fct)(), C& proxy)
{
    m_Spec = new MapperSpec<Mediator, C>(fct, proxy);
}

#endif