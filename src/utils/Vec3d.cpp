#include "Vec3d.h"

Vec3d::Vec3d()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3d::Vec3d(int x, int y, int z)
{
	Set(x, y, z);
}

void Vec3d::Set(int x, int y, int z)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
	this->z = static_cast<float>(z);
}
