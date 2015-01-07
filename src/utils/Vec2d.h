#ifndef _VEC2D_H_
#define _VEC2D_H_

class Vec2d
{
public:
	float x, y;

public:
	Vec2d();
	explicit Vec2d(int x, int y);
	explicit Vec2d(float x, float y);
	~Vec2d() {}

	void	Set(int x, int y);
	void	Set(float x, float y);
};

#endif