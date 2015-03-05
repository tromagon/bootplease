#include "Vec2d.h"
#include <math.h>

Vec2d::Vec2d()
{
	x = 0;
	y = 0;
}

Vec2d::Vec2d(float x, float y)
{
	Set(x, y);
}

Vec2d::Vec2d(int x, int y)
{
	Set(x, y);
}

void Vec2d::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vec2d::Set(int x, int y)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
}

Vec2d Vec2d::Clone()
{
	return Vec2d(x, y);
}

double Vec2d::GetLength()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2d& Vec2d::operator-(Vec2d& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}