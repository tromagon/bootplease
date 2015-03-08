#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "RenderSupport.h"
#include "utils\Rectangle.h"

class ITexture;
typedef unique_ptr<ITexture> ITexturePtr;

class Image : public DisplayObject
{
public:
    explicit Image(ITexturePtr& texture);
    virtual ~Image() {}

    ITexturePtr&   GetTexture()     { return m_Texture; }

    virtual bootplease::Rectangle&  GetBounds(DisplayObject& target, bootplease::Rectangle& resultRect) override;
    virtual void        Render(RenderSupport& renderSupport, float parentAlpha) override;

private:
    ITexturePtr&    m_Texture;
    vector<Vec2d>   m_Vertex;
};

#endif