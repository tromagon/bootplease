#ifndef _MEDIATORMAP2_H_
#define _MEDIATORMAP2_H_

#include "injection\Injector.h"
#include "events\EventDispatcher.h"

class Mediator;
class View;

class MediatorMap
{
public:
    explicit MediatorMap(EventDispatcherPtr& eventDispatcher, InjectorPtr& injector) 
        : m_EventDispatcher(eventDispatcher), m_Injector(injector), m_NumMaps(0), m_NumVM(0) {}

    EventDispatcherPtr&     GetDispatcher()     { return m_EventDispatcher; }
    InjectorPtr&            GetInjector()       { return m_Injector; }

    template<class V, class M>
    void Map(const char* viewId);

    template<class C>
    C&  GetView(const char* id);

private:
    class MediatorMapItem
    {
    public:
        MediatorMapItem(const char* viewId, MediatorMap& proxy, 
            View& (MediatorMap::*createViewFct)(), Mediator& (MediatorMap::*createMediatorFct)()) 
            : m_ViewId(viewId), m_Proxy(proxy), m_CreateViewFct(createViewFct), m_CreateMediatorFct(createMediatorFct) {}

        const char *    GetViewId() { return m_ViewId; }
        View&           (MediatorMap::*GetCreateViewFct())()        { return m_CreateViewFct; }
        Mediator&       (MediatorMap::*GetCreateMediatorFct())()    { return m_CreateMediatorFct; }
        View&           GetView()                                   { return ((&m_Proxy->*m_CreateViewFct)()); }
        Mediator&       GetMediator()                               { return ((&m_Proxy->*m_CreateMediatorFct)()); }

    private:
        const char*     m_ViewId;
        MediatorMap&   m_Proxy;
        View&           (MediatorMap::*m_CreateViewFct)();
        Mediator&       (MediatorMap::*m_CreateMediatorFct)();
    };

    typedef unique_ptr<MediatorMapItem> MediatorMapItemPtr;

    class ViewMediatorItem
    {
    public:
        ViewMediatorItem(const char* id, View& view, Mediator& mediator) 
            : m_Id(id), m_View(view), m_Mediator(mediator) {}
        ~ViewMediatorItem() {}

        const char*     GetId()         { return m_Id; }
        View&           GetView()       { return m_View; }
        Mediator&       GetMediator()   { return m_Mediator; }

    private:
        const char*         m_Id;
        View&               m_View;
        Mediator&           m_Mediator;
    };

    typedef unique_ptr<ViewMediatorItem> ViewMediatorItemPtr;

    View*                       GetViewInstance(const char* id);

    EventDispatcherPtr&         m_EventDispatcher;
    InjectorPtr&                m_Injector;
    vector<MediatorMapItemPtr>  m_Maps;
    int                         m_NumMaps;
    vector<ViewMediatorItemPtr> m_VMList;
    int                         m_NumVM;

    template<class V>
    View& CreateView();

    template<class M>
    Mediator& CreateMediator();
};

template<class V>
View& MediatorMap::CreateView()
{
    return *(new V()); 
}

template<class M>
Mediator& MediatorMap::CreateMediator()
{
    return *(new M()); 
}

template<class V, class M>
void MediatorMap::Map(const char* viewId)
{
    m_Maps.push_back(MediatorMapItemPtr(new MediatorMapItem(viewId, *this, 
        &MediatorMap::CreateView<V>, &MediatorMap::CreateMediator<M>)));
    m_NumMaps++;
}

template<class C>
C& MediatorMap::GetView(const char* id)
{
    C* view = static_cast<C*>(GetViewInstance(id));

    if (view) return *view;

    for (int i = 0 ; i < m_NumMaps ; i++)
    {
        MediatorMapItemPtr& item = m_Maps[i];
        if (item->GetViewId() == id)
        {
            view = static_cast<C*>(&item->GetView());
            Mediator& mediator = item->GetMediator();
            mediator.SetMediatorMap(*this);
            mediator.SetView(*view);
            mediator.OnInitialized();

            m_VMList.push_back(ViewMediatorItemPtr(new ViewMediatorItem(id, *view, mediator)));
            m_NumVM++;
            break;
        }
    }

    return *view;
}

#endif