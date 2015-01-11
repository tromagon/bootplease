#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include <vector>

using namespace std;

class Injector
{
private:
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
		const C*		m_Instance;
	
	public:
		const C*		GetInstance()	{ return m_Instance; }

	public:
		explicit InjectorMappingSpec(const C* instance) : m_Instance(instance) {};
		virtual ~InjectorMappingSpec() {};
	};

	class InjectorMapping
	{
	private:
		InjectorMappingSpecBase*	m_Spec;
		const char*					m_Id;

	public:
		template<class C>
		const C*		GetInstance()	{ return static_cast<InjectorMappingSpec<C>*>(m_Spec)->GetInstance(); }
		const char*		GetId()			{ return m_Id; }

	public:
		template<class C>
		InjectorMapping(const C* instance, const char* id) : m_Id(id) { m_Spec = new InjectorMappingSpec<C>(instance); };
		virtual ~InjectorMapping() { delete m_Spec; };
	};

private:
	vector<InjectorMapping*>	m_Maps;
	int							m_NumInjections;

public:
	Injector() : m_NumInjections(0) {}
	~Injector();

	void		UnMap(const char* id);

	template<class C>
	void		Map(const C* obj, const char* id);

	template<class C>
	void		UnMap(C& obj);

	template<class C>
	const C*	GetInstanceById(const char* id);

private:
	void	UnMapAll();
};

template<class C>
void Injector::Map(const C* instance, const char* id)
{
	InjectorMapping* mapping = new InjectorMapping(instance, id);
	m_Maps.push_back(mapping);
	m_NumInjections++;
}

template<class C>
void Injector::UnMap(C& obj)
{
	InjectorMapping* mapping;

	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		mapping = m_Maps[i];
		if (mapping->GetInstance<C>() == obj)
		{
			m_Maps.erase(m_Maps.begin() + i);
			delete mapping;
			return;
		}
	}

	m_NumInjections--;
}

template<class C>
const C* Injector::GetInstanceById(const char* id)
{
	InjectorMapping* mapping;

	const unsigned short l = m_NumInjections;
	for (unsigned int i = 0 ; i < l ; i++)
	{
		mapping = m_Maps[i];
		if (mapping->GetId() == id)
		{
			return mapping->GetInstance<C>();
		}
	}

	return nullptr;
}


#endif