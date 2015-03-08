#include "Gesture.h"
#include <iostream>

using namespace std;

bool Gesture::isTrackingTouch(int touchId)
{
    int i = m_TouchMap.size();
    while (i-- > 0 )
    {
        if (m_TouchMap[i]->GetId() == touchId)
        {
            return true;
        }
    }

    return false;
}

void Gesture::BeginTouch(Touch& touch)
{
    for (int i = 0 ; i < m_TouchMap.size() ; ++i)
    {
        if (m_TouchMap[i] == &touch)
        {
            return;
        }
    }

    m_TouchMap.push_back(&touch);
    OnTouchBegin(touch);
}

void Gesture::EndTouch(Touch& touch)
{
    for (int i = 0 ; i < m_TouchMap.size() ; ++i)
    {
        if (m_TouchMap[i] == &touch)
        {
            m_TouchMap.erase(m_TouchMap.begin() + i);
            OnTouchEnd(touch);
            return;
        }
    }
}

void Gesture::MoveTouch(Touch& touch)
{
    OnTouchMove(touch);
}

void Gesture::SetState(GestureState state)
{
    m_State = state;
}