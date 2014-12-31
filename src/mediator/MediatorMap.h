#ifndef _MEDIATORMAP_H_
#define _MEDIATORMAP_H_

#include "EventDispatcher.h"
#include <vector>

using namespace std;

class View
{
public:
	View() {}
	virtual ~View() {}
};


class Mediator
{
public:
	Mediator() {}
	virtual ~Mediator() {}
};


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
private:
	D& (C::*m_Fct)();
	C& m_Proxy;

public:
	D&	(C::*GetFunction())()	{ return m_Fct; }
	C&	GetProxy()				{ return m_Proxy; }

public:
	MapperSpec(D& (C::*fct)(), C& proxy) : m_Fct(fct), m_Proxy(proxy) {}
	virtual ~MapperSpec() {}
	
	void* GetInstance() override { return &(&m_Proxy->*m_Fct)(); }
};


template<class D>
class BaseMapper
{
protected:
	IMapperSpec* m_Spec;

public:
	virtual ~BaseMapper() { delete m_Spec; }

	template<class C>
	D&	(C::*GetFunction())()	{ return (static_cast<MapperSpec<D, C>*>(m_Spec))->GetFunction(); }

	template<class C>
	C&	GetProxy()				{ return (static_cast<MapperSpec<D, C>*>(m_Spec))->GetProxy(); }

	D&	GetInstance()			{ return *(static_cast<D*>(m_Spec->GetInstance())); }
};


class ViewMapper : public BaseMapper<View>
{
public:
	template<class C>
	ViewMapper(View& (C::*fct)(), C& proxy);
	~ViewMapper() {}
};

template<class C>
ViewMapper::ViewMapper(View& (C::*fct)(), C& proxy)
{
	m_Spec = new MapperSpec<View, C>(fct, proxy);
}


class MediatorMapper : public BaseMapper<Mediator>
{
public:
	MediatorMapper() {}
	~MediatorMapper() {}

	template<class C>
	void To(Mediator& (C::*fct)(), C& proxy);
};

template<class C>
void MediatorMapper::To(Mediator& (C::*fct)(), C& proxy)
{
	m_Spec = new MapperSpec<Mediator, C>(fct, proxy);
}


class MediatorMapItem
{
private:
	const char*			m_Id;
	ViewMapper&			m_ViewMapper;
	MediatorMapper&		m_MediatorMapper;

public:
	const char*			GetId()						{ return m_Id; }
	MediatorMapper&		GetMediatorMapper()			{ return m_MediatorMapper; }
	View&				GetViewInstance()			{ return m_ViewMapper.GetInstance(); }
	Mediator&			GetMediatorInstance()		{ return m_MediatorMapper.GetInstance(); }

public:
	MediatorMapItem(const char* id, ViewMapper& viewMapper) 
		: m_Id(id), m_ViewMapper(viewMapper), m_MediatorMapper(*(new MediatorMapper())) {}
	~MediatorMapItem();
};


class ViewMediatorItem
{
private:
	const char*			m_Id;
	View&				m_View;
	Mediator&			m_Mediator;

public:
	const char*		GetId()			{ return m_Id; }
	View&			GetView()		{ return m_View; }
	Mediator&		GetMediator()	{ return m_Mediator; }

public:
	ViewMediatorItem(const char* id, View& view, Mediator& mediator) 
		: m_Id(id), m_View(view), m_Mediator(mediator) {}
	~ViewMediatorItem();
};


class MediatorMap
{
private:
	vector<MediatorMapItem*>	m_Map;
	vector<ViewMediatorItem*>	m_VmList;

public:
	MediatorMap() {}
	~MediatorMap();

	template<class C>
	MediatorMapper& Map(const char* id, View& (C::*fct)(), C& proxy);
	
	View*	GetView(const char* id);
	void	UnMap(const char* id);
	void	DisposeView(View& view);
	void	DisposeViewById(const char* id);

private:
	View*	GetViewInstance(const char* id);
	void	UnMapAll();
	void	DisposeAll();
};

template<class C>
MediatorMapper& MediatorMap::Map(const char* id, View& (C::*fct)(), C& proxy)
{
	MediatorMapItem* item;
	item = new MediatorMapItem(id, *(new ViewMapper(fct, proxy)));
	m_Map.push_back(item);

	return item->GetMediatorMapper();
}

#endif