#include "MediatorMap.h"

void Mediator::DispatchContextEvent(Event& evt)
{
	m_MediatorMap->GetDispatcher()->Dispatch(evt);
}

MediatorMapItem::~MediatorMapItem()
{
	delete &m_ViewMapper;
	delete &m_MediatorMapper;
}

ViewMediatorItem::~ViewMediatorItem()
{
	delete &m_View;
	delete &m_Mediator;
}

MediatorMap::~MediatorMap()
{
	DisposeAll();
	UnMapAll();
}

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
			mediator.SetView(*view);
			mediator.SetMediatorMap(*this);
			mediator.OnInitialized();

			ViewMediatorItem* vm = new ViewMediatorItem(id, *view, mediator); 
			m_VmList.push_back(vm);

			return view;
		}
	}

	return nullptr;
}

void MediatorMap::UnMap(const char* id)
{
	const unsigned short l = m_Map.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		MediatorMapItem* item = m_Map[i];
		if (item->GetId() == id)
		{
			m_Map.erase(m_Map.begin() + i);
			delete item;
		}
	}
}

void MediatorMap::DisposeView(View& view)
{
	const unsigned short l = m_VmList.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		ViewMediatorItem* item = m_VmList[i];
		if (&(item->GetView()) == &view)
		{
			m_VmList.erase(m_VmList.begin() + i);
			delete item;
		}
	}
}

void MediatorMap::DisposeViewById(const char* id)
{
	const unsigned short l = m_VmList.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		ViewMediatorItem* item = m_VmList[i];
		if (item->GetId() == id)
		{
			m_VmList.erase(m_VmList.begin() + i);
			delete item;
		}
	}
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

void MediatorMap::UnMapAll()
{
	const unsigned short l = m_Map.size();
	for (int i = l - 1 ; i >= 0 ; i--)
	{
		MediatorMapItem* item = m_Map[i];
		m_Map.erase(m_Map.begin() + i);
		delete item;
	}
}

void MediatorMap::DisposeAll()
{
	const unsigned short l = m_VmList.size();
	for (int i = l - 1 ; i >= 0 ; i--)
	{
		ViewMediatorItem* item = m_VmList[i];
		m_VmList.erase(m_VmList.begin() + i);
		delete item;
	}
}