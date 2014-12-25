#ifndef _VEC3D_H_
#define _VEC3D_H_

class Vec3d
{
public:
	float x, y, z;

public:
	Vec3d();
	explicit Vec3d(float x, float y, float z) : x(x), y(y), z(z) {}
	explicit Vec3d(int x, int y, int z);
	~Vec3d() {}

	void	Set(int x, int y, int z);
};

#endif