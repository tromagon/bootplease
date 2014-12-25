#ifndef _VEC2D_H_
#define _VEC2D_H_

class Vec2d
{
public:
	int x, y;

public:
	Vec2d();
	explicit Vec2d(int x, int y );
	~Vec2d() {}

	void	Set(int x, int y);
};

#endif