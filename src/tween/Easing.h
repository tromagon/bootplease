#ifndef _EASING_H_
#define _EASING_H_

//class Easing
//{
//	virtual float calculate(float p) {}
//};

class Linear /*: public Easing*/
{
public:
	static float EaseNone(float p)
	{
		return p;
	}
};

#endif