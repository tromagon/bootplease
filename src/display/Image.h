#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "RenderSupport.h"
#include "utils\Rectangle.h"

class ITexture;

class Image : public DisplayObject
{
private:
    ITexture*       m_Texture;
    vector<Vec2d>   m_Vertex;

public:
    ITexture&   GetTexture()                { return *m_Texture; }
    void        SetTexture(ITexture& value)  { m_Texture = &value; }

public:
    explicit Image(ITexture& texture);
    virtual ~Image() {}

    virtual bootplease::Rectangle&  GetBounds(DisplayObject& target, bootplease::Rectangle& resultRect) override;
    virtual void        Render(RenderSupport& renderSupport, float parentAlpha) override;
};

#endif