#ifndef _TOUCHESMANAGER_H_
#define _TOUCHESMANAGER_H_

#include "core\Updateable.h"
#include "Touch.h"
#include "GestureManager.h"
#include "utils\Vec2d.h"
#include "utils\Pool.h"

#include <vector>
#include <memory>

using namespace std;

class TouchesManager : public Updateable
{
private:
	vector<Touch*>		m_TouchList;
	GestureManager&		m_GestureManager;
	Stage&				m_Stage;
	unsigned int		m_ActiveTouchesCount;
	long				m_Timer;
	Pool<Touch>			m_TouchPool;

protected:
	static long			timeHelper;

public:
	explicit TouchesManager(GestureManager& gestureManager, Stage& stage) 
		: m_GestureManager(gestureManager), m_Stage(stage), m_ActiveTouchesCount(0), m_Timer(0) {}
	
	~TouchesManager();

	void	OnTouchBegin(int touchID, Vec2d& point);
	void	OnTouchEnd(int touchID, Vec2d& point);
	void	OnTouchMove(int touchID, Vec2d& point);

	bool	Update(float deltaTime = 0.0f) override;

private:
	Touch*	GetTouchByTouchID(int touchID);
	int		GetIndexByTouchID(int touchID);
};

typedef unique_ptr<TouchesManager> TouchesManagerPtr;

#endif