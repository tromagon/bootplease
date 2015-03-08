#include "Gesture.h"
#include <iostream>

using namespace std;

bool Gesture::isTrackingTouch(int touchId)
{
    return (GetTouchIndexById(touchId) != -1);
}

void Gesture::BeginTouch(Touch& touch)
{
    int index = GetTouchIndexById(touch.GetId());
    if (index != -1) 
    {
        m_TouchMap[index] = &touch;
    }
    else
    {
        m_TouchMap.push_back(&touch);
    }

	OnTouchBegin(touch);
}

void Gesture::EndTouch(Touch& touch)
{
    int index = GetTouchIndexById(touch.GetId());
    m_TouchMap.erase(m_TouchMap.begin() + index);

	OnTouchEnd(touch);
}

void Gesture::MoveTouch(Touch& touch)
{
	OnTouchMove(touch);
}

void Gesture::SetState(GestureState state)
{
	m_State = state;
}

int Gesture::GetTouchIndexById(int touchId)
{
    int i = m_TouchMap.size();
    while (i-- > 0 )
    {
        if (m_TouchMap[i]->GetId() == touchId)
        {
            return i;
        }
    }

    return -1;
}