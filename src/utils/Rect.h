#ifndef _RECT_H_
#define _RECT_H_

class Rect
{
public:
	int m_X;
	int m_Y;
	int m_W;
	int m_H;

public:
	explicit Rect(int x = 0, int y = 0, int width = 0, int height = 0) : m_X(x), m_Y(y), m_W(width), m_H(height) {}
	~Rect() {}
};


#endif