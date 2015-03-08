#include "SwipeGesture.h"
#include "GestureEvent.h"

#include <iostream>
#include <cmath>

using namespace std;

const float SwipeGesture::ANGLE = 0.69f;
const int	SwipeGesture::MAX_DURATION = 500;
const float SwipeGesture::MIN_OFFSET = 35;
const float SwipeGesture::MIN_VELOCIY = 2 * MIN_OFFSET / MAX_DURATION;

Vec2d SwipeGesture::absVel;

void SwipeGesture::OnTouchBegin(Touch& touch)
{
	SetState(BEGAN);

	m_StartTime = touch.GetTime();
	m_AvrgVel.Set(0, 0);
}

void SwipeGesture::OnTouchEnd(Touch& touch)
{
	if (m_State == BEGAN)
	{
		SetState(ENDED);
	}
}

void SwipeGesture::OnTouchMove(Touch& touch)
{
	if (m_State == ENDED)
	{
		return;
	}

	m_Offset= touch.GetLocationOffset();
	//cout << "x: " << m_Offset.x << " , y:" << m_Offset.y << endl;

	long totalTime = (touch.GetTime() - m_StartTime);

	//cout << "total time : " << totalTime << endl;

	m_AvrgVel.Set(m_Offset.x / totalTime, m_Offset.y / totalTime);
	absVel.Set(m_AvrgVel.x > 0 ? m_AvrgVel.x : - m_AvrgVel.x, 
		m_AvrgVel.y > 0 ? m_AvrgVel.y : - m_AvrgVel.y);

	float absOffset;

	//cout << "absVel.x : " << absVel.x << " , y : " << absVel.y << endl;

	if (absVel.x > absVel.y)
	{
		absOffset = m_Offset.x > 0 ? m_Offset.x : - m_Offset.x;
		if (absOffset > m_Slop)
		{
			//cout << "beyiond slop" << endl;

			if (abs(atan(m_Offset.y / m_Offset.x) > ANGLE))
			{
				m_State = FAILED;
			}
			else if (absVel.x >= MIN_VELOCIY || absOffset >= MIN_OFFSET)
			{
				m_State = ENDED;
				m_Offset.y = 0;
				GestureEvent evt(GestureEvent::GESTURE_RECOGNIZED, *this);
				Dispatch(evt);
			}
		}
	}
	else if (absVel.y > absVel.x)
	{
		absOffset = m_Offset.y > 0 ? m_Offset.y : - m_Offset.y;
		if (absOffset > m_Slop)
		{
			if (abs(atan(m_Offset.x / m_Offset.y) > ANGLE))
			{
				m_State = FAILED;
			}
			else if (absVel.y >= MIN_VELOCIY || absOffset >= MIN_OFFSET)
			{
				m_State = ENDED;
				m_Offset.x = 0;
				GestureEvent evt(GestureEvent::GESTURE_RECOGNIZED, *this);
				Dispatch(evt);
			}
		}
	}
}