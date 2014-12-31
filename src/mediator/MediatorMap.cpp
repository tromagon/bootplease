#include "MediatorMap.h"

View* MediatorMap::GetView(const char* id)
{
	View* view = GetViewInstance(id);

	if (view) return view;

	const unsigned short l = m_Map.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		MediatorMapItem& item = *(m_Map[i]);
		if (item.GetId() == id)
		{
			view = &(item.GetViewInstance());
			Mediator& mediator = item.GetMediatorInstance();

			ViewMediatorItem* vm = new ViewMediatorItem(id, *view, mediator); 
			m_VmList.push_back(vm);

			return view;
		}
	}

	return nullptr;
}

View* MediatorMap::GetViewInstance(const char* id)
{
	const unsigned short l = m_VmList.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		ViewMediatorItem& item = *(m_VmList[i]);
		if (item.GetId() == id)
		{
			return &(item.GetView());
		}
	}

	return nullptr;
}