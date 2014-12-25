#ifndef  _UPDATEABLE_H_
#define  _UPDATEABLE_H_

#include <list>

using namespace std;

class IUpdateable
{
public:
	IUpdateable() {}
	virtual ~IUpdateable() {}

	virtual void Update(float deltaTime = 0.0f) {}
};

class UpdateManager
{
private:
	list<IUpdateable*> m_Updateables;

public:
	UpdateManager() {}
	~UpdateManager() {}

	void    Update(float deltaTime = 0.0f);
	void    Add(IUpdateable* updateable);
	void    Remove(IUpdateable* updateable);
};

extern UpdateManager* g_pUpdateManager;

#endif
