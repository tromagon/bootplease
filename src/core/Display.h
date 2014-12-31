#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class IDisplay
{

public:
	 virtual int	GetX()						{ return 0; }
	 virtual void	SetX(int value)				{}

	 virtual int	GetY()						{ return 0; }
	 virtual void	SetY(int value)				{}

	 virtual int	GetWidth()					{ return 0; }
	 virtual void	SetWidth(int value)			{}

	 virtual int	GetHeight()					{ return 0; }
	 virtual void	SetHeight(int value)		{}

	 virtual float	GetRotation()				{ return 0; }
	 virtual void	SetRotation(float value)	{}

	 virtual float	GetScaleX()					{ return 0; }
	 virtual void	SetScaleX(float value)		{}

	 virtual float	GetScaleY()					{ return 0; }
	 virtual void	SetScaleY(float value)		{}

	 virtual float	GetAlpha()					{ return 0; }
	 virtual void	SetAlpha(float value)		{}

	 virtual int	GetScreenWidth()			{ return 0; }
	 virtual void	SetScreenWidth(int value)	{}

	 virtual int	GetScreenHeight()			{ return 0; }
	 virtual void	SetScreenHeight(int value)	{}

	 virtual bool	HitTest(int x, int y)		{ return false; }

public:
	IDisplay() {}
	virtual ~IDisplay() {}
};

#endif