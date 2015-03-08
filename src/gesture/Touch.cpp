#include "Touch.h"

void Touch::SetLocation(Vec2d& point, long time)
{
    m_Location.Set(point.x, point.y);
    m_BeginLocation.Set(point.x, point.y);
    m_PrevLocation.Set(point.x, point.y);

    m_Time = m_BeginTime = time;
}

bool Touch::UpdateLocation(Vec2d& point, long time)
{
    if (m_Location.x == point.x && m_Location.y == point.y)
    {
        return false;
    }

    m_PrevLocation.Set(m_Location.x, m_Location.y);
    m_Location.Set(point.x, point.y);
    m_Time = time;

    return true;
}

Vec2d Touch::GetLocationOffset()
{
    return m_Location - m_BeginLocation;
}