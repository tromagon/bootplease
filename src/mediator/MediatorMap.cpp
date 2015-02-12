#include "mediator\MediatorMap.h"
#include "mediator\View.h"

View* MediatorMap::GetViewInstance(const char* id)
{
    for (int i = 0 ; i < m_NumVM ; i++)
    {
        ViewMediatorItemPtr& item = m_VMList[i];
        if (item->GetId() == id)
        {
            return (item->GetView().get());
        }
    }

    return nullptr;
}

void MediatorMap::DisposeView(View& view)
{
    for (int i = 0 ; i < m_NumVM ; i++)
    {
        ViewMediatorItemPtr& item = m_VMList[i];
        if ((item->GetView().get()) == &view)
        {
            m_VMList.erase(m_VMList.begin() + i);
            m_NumVM--;

            return;
        }
    }
}

void MediatorMap::DisposeView(const char* id)
{
    for (int i = 0 ; i < m_NumVM ; i++)
    {
        ViewMediatorItemPtr& item = m_VMList[i];
        if (item->GetId() == id)
        {
            m_VMList.erase(m_VMList.begin() + i);
            m_NumVM--;

            return;
        }
    }
}

void MediatorMap::UnMap(const char* viewId)
{
    for (int i = 0 ; i < m_NumMaps ; i++)
    {
        MediatorMapItemPtr& item = m_Maps[i];
        if (item->GetViewId() == viewId)
        {
            m_Maps.erase(m_Maps.begin() + i);
            m_NumMaps--;

            return;
        }
    }
}