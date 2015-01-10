#ifndef _VEC2D_H_
#define _VEC2D_H_

class Vec2d
{
public:
	float x, y;

public:
	Vec2d();
	explicit Vec2d(float x, float y );	
	explicit Vec2d(int x, int y);
	~Vec2d() {}

	void	Set(float x, float y);
	void	Set(int x, int y);
	Vec2d	Clone();
	double	GetLength();
	Vec2d&	operator-(Vec2d& vec);
};

#endif