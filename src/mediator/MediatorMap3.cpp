#include "MediatorMap3.h"
#include "Mediator.h"

MediatorMap3::MediatorMapItem::~MediatorMapItem()
{
    delete &m_ViewMapper;
    delete &m_MediatorMapper;
}

MediatorMap3::ViewMediatorItem::~ViewMediatorItem()
{
    delete &m_View;
    //delete &m_Mediator;
}

MediatorMap3::~MediatorMap3()
{
    DisposeAll();
    UnMapAll();
}

void MediatorMap3::UnMap(const char* id)
{
    MediatorMapItem* item;

    const unsigned short l = m_Map.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        item = m_Map[i];
        if (item->GetId() == id)
        {
            m_Map.erase(m_Map.begin() + i);
            delete item;
        }
    }
}

void MediatorMap3::DisposeView(View& view)
{
    ViewMediatorItem* item;

    const unsigned short l = m_VmList.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        item = m_VmList[i];
        if (&(item->GetView()) == &view)
        {
            m_VmList.erase(m_VmList.begin() + i);
            delete item;
        }
    }
}

void MediatorMap3::DisposeViewById(const char* id)
{
    ViewMediatorItem* item;

    const unsigned short l = m_VmList.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        item = m_VmList[i];
        if (item->GetId() == id)
        {
            m_VmList.erase(m_VmList.begin() + i);
            delete item;
        }
    }
}

View* MediatorMap3::GetViewInstance(const char* id)
{
    ViewMediatorItem* item;

    const unsigned short l = m_VmList.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        item = m_VmList[i];
        if (item->GetId() == id)
        {
            return &(item->GetView());
        }
    }

    return nullptr;
}

MediatorMap3::ViewMediatorItem& MediatorMap3::AddViewMediatorItem(MediatorMapItem* item)
{
    View* view = &(item->GetViewInstance());
    Mediator& mediator = item->GetMediatorInstance();
    //mediator.SetMediatorMap(*this);
    mediator.SetView(*view);
    //mediator.OnInitialized();

    ViewMediatorItem* vm = new ViewMediatorItem(item->GetId(), *view, mediator); 
    m_VmList.push_back(vm);

    return *vm;
}

void MediatorMap3::UnMapAll()
{
    MediatorMapItem* item;

    const unsigned short l = m_Map.size();
    for (int i = l - 1 ; i >= 0 ; i--)
    {
        item = m_Map[i];
        m_Map.erase(m_Map.begin() + i);
        delete item;
    }
}

void MediatorMap3::DisposeAll()
{
    ViewMediatorItem* item;

    const unsigned short l = m_VmList.size();
    for (int i = l - 1 ; i >= 0 ; i--)
    {
        item = m_VmList[i];
        m_VmList.erase(m_VmList.begin() + i);
        delete item;
    }
}