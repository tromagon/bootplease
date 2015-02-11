#include "mediator\MediatorMap.h"
#include "mediator\View.h"

View* MediatorMap::GetViewInstance(const char* id)
{
    for (int i = 0 ; i < m_NumVM ; i++)
    {
        ViewMediatorItemPtr& item = m_VMList[i];
        if (item->GetId() == id)
        {
            return &(item->GetView());
        }
    }

    return nullptr;
}