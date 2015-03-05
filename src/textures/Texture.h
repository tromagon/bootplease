#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <Iw2D.h>

class Texture
{
protected:
	CIw2DImage&		m_Image;

public:
	virtual float		GetX()		{ return 0; }
	virtual float		GetY()		{ return 0; }
	virtual float		GetWidth()	{ return m_Image.GetWidth(); }
	virtual float		GetHeight() { return m_Image.GetHeight(); }
	CIw2DImage&			GetImage()	{ return m_Image; }

public:
	explicit Texture(CIw2DImage& image) : m_Image(image) {}
	virtual ~Texture() {}

	
};

#endif