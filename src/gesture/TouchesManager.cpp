#include "TouchesManager.h"
#include "display\Stage.h"
#include <time.h>
#include <iostream>

long TouchesManager::timeHelper;

void TouchesManager::OnTouchBegin(int touchID, Vec2d& point)
{
    for (unsigned int i = 0 ; i < m_TouchList.size() ; i++)
    {
        if (m_TouchList[i]->GetId() == touchID)
        {
            return;
        }
    }

    TouchPtr touch = TouchPtr(new Touch());
    touch->SetId(touchID);

    DisplayObject& target = *m_Stage.HitTest(point);
    touch->SetTarget(&target);

    touch->SetLocation(point, m_Timer);

    m_GestureManager.OnTouchBegin(*touch);

    m_TouchList.push_back(move(touch));
}

void TouchesManager::OnTouchEnd(int touchID, Vec2d& point)
{
    for (unsigned int i = 0 ; i < m_TouchList.size() ; i++)
    {
        TouchPtr& touch = m_TouchList[i];
        touch->UpdateLocation(point, m_Timer);

        m_GestureManager.OnTouchEnd(*touch);

        touch->SetTarget(nullptr);

        m_TouchList.erase(m_TouchList.begin() + i);
    }
}

void TouchesManager::OnTouchMove(int touchID, Vec2d& point)
{
    for (unsigned int i = 0 ; i < m_TouchList.size() ; i++)
    {
        TouchPtr& touch = m_TouchList[i];
        if (touch->UpdateLocation(point, m_Timer))
        {
            m_GestureManager.OnTouchMove(*touch);
        }
    }
}

bool TouchesManager::Update(float deltaTime)
{
    m_Timer += static_cast<long>(deltaTime * 1000);
    return true;
}