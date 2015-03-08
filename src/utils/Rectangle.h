#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Vec2d.h"

namespace bootplease
{
    class Rectangle
    {
    public:
        float m_X;
        float m_Y;
        float m_Width;
        float m_Height;

    public:
        explicit Rectangle(float x = 0, float y = 0, float width = 0, float height = 0) 
            : m_X(x), m_Y(y), m_Width(width), m_Height(height) {}

        explicit Rectangle(int x, int y, int width, int height) 
            : m_X(static_cast<float>(x)), m_Y(static_cast<float>(y)), 
            m_Width(static_cast<float>(width)), m_Height(static_cast<float>(height)) {}

        ~Rectangle() {}

        bool        ContainsPoint(Vec2d point);
        void        SetTo(float x, float y, float width, float height);
        float       GetRight();
        float       GetBottom();
        void        Substract(Rectangle& rect);
        Rectangle   Clone();

    };
}


#endif
