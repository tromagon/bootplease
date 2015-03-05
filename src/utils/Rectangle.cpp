#include "Rectangle.h"
#include "Vec2d.h"

using namespace bootplease;

void Rectangle::SetTo(float x, float y, float width, float height)
{
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;
}

float Rectangle::GetRight()
{
    return m_X + m_Width;
}

float Rectangle::GetBottom()
{
    return m_Y + m_Height;
}

bool Rectangle::ContainsPoint(Vec2d point)
{
    return (point.x >= m_X && point.x <= GetRight() 
        && point.y >= m_Y && point.y <= GetBottom());
}

void Rectangle::Substract(Rectangle& rect)
{
    m_X -= rect.m_X;
    m_Y -= rect.m_Y;
    m_Width -= rect.m_Width;
    m_Height -= rect.m_Height;
}

Rectangle Rectangle::Clone()
{
    Rectangle rect(m_X, m_Y, m_Width, m_Height);
    return rect;
}