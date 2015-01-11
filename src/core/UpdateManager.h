#ifndef  _UPDATEMANAGER_H_
#define  _UPDATEMANAGER_H_

#include "Updateable.h"
#include <list>

using namespace std;

class UpdateManager
{
private:
	list<Updateable*> m_Updateables;

public:
	UpdateManager() {}
	~UpdateManager() {}

	void    Update(float deltaTime = 0.0f);
	void    Add(Updateable& updateable);
	void    Remove(Updateable& updateable);
};

#endif
