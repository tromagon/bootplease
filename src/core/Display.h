#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class Display
{
private:
	int		m_X;
	int		m_Y;
	int		m_Width;
	int		m_Height;
	float	m_ScaleX;
	float	m_ScaleY;
	float	m_Rotation;
	float	m_Alpha;
	int		m_ScreenWidth;
	int		m_ScreenHeight;

public:
	 int	GetX()						{ return m_X; }
	 void	SetX(int value)				{ m_X = value; }

	 int	GetY()						{ return m_Y; }
	 void	SetY(int value)				{ m_Y = value; }

	 int	GetWidth()					{ return m_Width; }
	 void	SetWidth(int value)			{ m_Width = value; }

	 int	GetHeight()					{ return m_Height; }
	 void	SetHeight(int value)		{ m_Height = value; }

	 float	GetRotation()				{ return m_Rotation; }
	 void	SetRotation(float value)	{ m_Rotation = value; }

	 float	GetScaleX()					{ return m_ScaleX; }
	 void	SetScaleX(float value)		{ m_ScaleX = value; }

	 float	GetScaleY()					{ return m_ScaleY; }
	 void	SetScaleY(float value)		{ m_ScaleY = value; }

	 float	GetAlpha()					{ return m_Alpha; }
	 void	SetAlpha(float value)		{ m_Alpha = value; }

	 int	GetScreenWidth()			{ return 0; }
	 void	SetScreenWidth(int value)	{ m_ScreenWidth = value; }

	 int	GetScreenHeight()			{ return 0; }
	 void	SetScreenHeight(int value)	{ m_ScreenHeight = value; }



public:
	Display() : m_X(0), m_Y(0), m_Width(0), m_Height(0), 
		 m_ScaleX(1), m_ScaleY(1), m_Rotation(0), m_Alpha(1) {}

	virtual ~Display() {}
};

#endif