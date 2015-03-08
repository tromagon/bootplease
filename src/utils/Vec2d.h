#ifndef _VEC2D_H_
#define _VEC2D_H_

#include <math.h>

class Vec2d
{
public:
    float x, y;

public:
    Vec2d(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2d(const Vec2d& v) : x(v.x), y(v.y) {}

    double GetLength()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    Vec2d& operator-(Vec2d& vec)
    {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }
};

#endif