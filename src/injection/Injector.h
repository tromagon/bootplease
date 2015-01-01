#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include "EventDispatcher.h"
#include "Command.h"
#include "MediatorMap.h"
#include <vector>

using namespace std;


class InjectorMappingSpecBase
{
public:
	InjectorMappingSpecBase() {};
	virtual ~InjectorMappingSpecBase() {};
};

template<class C>
class InjectorMappingSpec : public InjectorMappingSpecBase
{
private:
	C&				m_Instance;
	
public:
	C&				GetInstance()	{ return m_Instance; }

public:
	explicit InjectorMappingSpec(C& instance) : m_Instance(instance) {};
	virtual ~InjectorMappingSpec() {};
};

class InjectorMapping
{
private:
	InjectorMappingSpecBase*	spec;
	const char*					m_Id;

public:
	template<class C>
	C&				GetInstance()	{ return static_cast<InjectorMappingSpec<C>*>(spec)->GetInstance(); }
	const char*		GetId()			{ return m_Id; }

public:
	template<class C>
	InjectorMapping(C& instance, const char* id) : m_Id(id) { spec = new InjectorMappingSpec<C>(instance); };
	virtual ~InjectorMapping() { delete spec; };
};


class Injector
{
private:
	EventDispatcher				m_Dispatcher;
	vector<InjectorMapping*>	m_Maps;
	ICommandMap*				m_CommandMap;
	IMediatorMap*				m_MediatorMap;

public:
	EventDispatcher&	GetDispatcher()								{ return m_Dispatcher; }

	ICommandMap&		GetCommandMap()								{ return *m_CommandMap; }
	void				SetCommandMap(ICommandMap& commandMap);

	IMediatorMap&		GetMediatorMap()							{ return *m_MediatorMap; }
	void				SetMediatorMap(IMediatorMap& mediatorMap);

public:
	Injector() {};
	~Injector() {};

	void	UnMap(const char* id);

	template<class C>
	void	Map(C& obj, const char* id);

	template<class C>
	void	UnMap(C& obj);

	template<class C>
	C*		GetInstanceById(const char* id);
};

template<class C>
void Injector::Map(C& instance, const char* id)
{
	InjectorMapping* mapping = new InjectorMapping(instance, id);
	m_Maps.push_back(mapping);
}

template<class C>
void Injector::UnMap(C& obj)
{
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		InjectorMapping& mapping = *m_Maps[i];
		if (mapping.GetInstance<C>() == obj)
		{
			m_Maps.erase(m_Maps.begin() + i);
			delete &mapping;
			return;
		}
	}
}

template<class C>
C* Injector::GetInstanceById(const char* id)
{
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		InjectorMapping& mapping = *m_Maps[i];
		if (mapping.GetId() == id)
		{
			return &(mapping.GetInstance<C>());
		}
	}

	return nullptr;
}


#endif