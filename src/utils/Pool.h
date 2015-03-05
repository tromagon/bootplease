#ifndef _POOL_H_
#define _POOL_H_

#include <vector>

using namespace std;

template<class C>
class Pool
{
private:
	vector<C*>		m_List;
	vector<C*>		m_Available;

	int				m_NumAvailable;
	int				m_NumCreated;

public:
	Pool() : m_NumAvailable(0), m_NumCreated(0) {}
	~Pool();

	C*		Get();
	void	Release(C* p);
};

template <class C>
Pool<C>::~Pool()
{
	int i = m_List.size();
	while (--i >= 0)
	{
		delete m_List[i];
	}

	m_List.clear();
}

template <class C>
C* Pool<C>::Get()
{
	C* p;
	if (m_NumAvailable == 0)
	{
		p = new C();
		m_List.push_back(p);
		m_NumCreated++;

		return p;
	}
	
	p = m_Available[0];
	m_Available.erase(m_Available.begin());
	m_NumAvailable--;

	/*p = new C();
	m_List.push_back(p);
		m_NumCreated++;*/

	return p;
}

template <class C>
void Pool<C>::Release(C* p)
{
	m_Available.push_back(p);
	m_NumAvailable++;
}
#endif
