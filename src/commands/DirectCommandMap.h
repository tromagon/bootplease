#ifndef _DIRECTCOMMANDMAP_H_
#define _DIRECTCOMMANDMAP_H_

#include "EventDispatcher.h"
#include "CommandMap.h"

class Context;
class Command;

class DirectCommandMap final : public CommandMap
{
	friend class Context;

private:
	class DirectCommandMapItemSpecBase
	{
	public:
		DirectCommandMapItemSpecBase() {}
		virtual ~DirectCommandMapItemSpecBase() {}
		virtual Command* GetCommand() { return nullptr; }
	};

	template<class C>
	class DirectCommandMapItemSpec : public DirectCommandMapItemSpecBase
	{
	private:
		C&			m_Proxy;
		Command&	(C::*m_Fct)();

	public:
		C&			GetProxy()						{ return m_Proxy; }
		Command&	(C::*GetFct())()				{ return m_Fct; }

	public:
		DirectCommandMapItemSpec(C& proxy, Command& (C::*fct)()) : m_Proxy(proxy), m_Fct(fct) {}
		virtual Command* GetCommand() override { return &((&m_Proxy->*m_Fct)()); }
	};

	class DirectCommandMapItem
	{
	private:
		DirectCommandMapItemSpecBase*		m_Spec;

	public:
		Command&					GetCommand()	{ return *(m_Spec->GetCommand()); }

		template<class C>
		Command&	(C::*GetFct())()				{ return static_cast<DirectCommandMapItemSpec<C>*>(m_Spec)->GetFct(); }

		template<class C>
		C&			GetProxy()						{ return static_cast<DirectCommandMapItemSpec<C>*>(m_Spec)->GetProxy(); }

	public:
		template<class C>
		DirectCommandMapItem(C& proxy, Command& (C::*fct)()) { m_Spec = new DirectCommandMapItemSpec<C>(proxy, fct); };
		~DirectCommandMapItem() { delete m_Spec; };
	};

private:
	vector<DirectCommandMapItem*>	m_Maps;

public:
	explicit DirectCommandMap(Context& context) : CommandMap(context) {}
	~DirectCommandMap();

	void				Execute();

	template<class C>
	void				Map(Command& (C::*fct)(), C& proxy);

	template<class C>
	void				UnMap(Command& (C::*fct)(), C& proxy);

private:
	void				UnMapAll();
};

template<class C>
void DirectCommandMap::Map(Command& (C::*fct)(), C& proxy)
{
	DirectCommandMapItem* mapItem = new DirectCommandMapItem(proxy, fct);
	m_Maps.push_back(mapItem);

	m_NumMap++;
}

template<class C>
void DirectCommandMap::UnMap(Command& (C::*fct)(), C& proxy)
{
	const unsigned short l = m_Maps.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		DirectCommandMapItem& mapping = *m_Maps[i];

		if (mapping.GetFct<C>() == fct && &(mapping.GetProxy<C>()) == &proxy)
		{
			m_Maps.erase(m_Maps.begin() + i);

			m_NumMap--;
			delete &mapping;
			return;
		}
	}
}

#endif