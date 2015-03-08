#ifndef _GESTURE_H_
#define _GESTURE_H_

#include "events\EventDispatcher.h"
#include "display\DisplayObject.h"
#include "Touch.h"

class Gesture : public EventDispatcher
{
private:
	DisplayObject&	    m_Target;
	bool			    m_Enabled;
    vector<Touch*>      m_TouchMap;


protected:
	int				m_TouchCount;

	enum GestureState
	{
		BEGAN,
		ENDED,
		FAILED
	};

	GestureState	m_State;

public:
	DisplayObject&	GetTarget() const   { return m_Target; }

	bool		GetEnabled()			{ return m_Enabled; }
	void		SetEnabled(bool value)	{ m_Enabled = value; }

public:
	explicit Gesture(DisplayObject& target) : m_Target(target), m_TouchCount(0) {}
	virtual ~Gesture() {}

    bool isTrackingTouch(int touchId);

	void BeginTouch(Touch& touch);
	void EndTouch(Touch& touch);
	void MoveTouch(Touch& touch);

protected:
	void        SetState(GestureState state);

    int         GetTouchIndexById(int touchId);

	virtual void OnTouchBegin(Touch& touch) {}
	virtual void OnTouchEnd(Touch& touch) {}
	virtual void OnTouchMove(Touch& touch) {}
};

#endif