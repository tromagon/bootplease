#ifndef _SUBTEXTURE_H_
#define _SUBTEXTURE_H_

#include "Texture.h"
#include "utils\Rectangle.h"

class SubTexture : public ITexture
{
public:
    explicit SubTexture(TexturePtr& parentTexture, bootplease::Rectangle region) :
        m_ParentTexture(parentTexture), m_Region(region) {}

    ~SubTexture() {}

private:
    TexturePtr&             m_ParentTexture;
    bootplease::Rectangle   m_Region;

    const int           GetX()                  { return static_cast<int>(m_Region.m_X); }
    const int           GetY()                  { return static_cast<int>(m_Region.m_Y); }
    const int           GetWidth()              { return static_cast<int>(m_Region.m_Width); }
    const int           GetHeight()             { return static_cast<int>(m_Region.m_Height); }
    const unsigned int  GetId()                 { return m_ParentTexture->GetId(); }
    const unsigned int  GetVertexBufferId()     { return m_ParentTexture->GetVertexBufferId(); }
    const unsigned int  GetIndexBufferId()      { return m_ParentTexture->GetIndexBufferId(); }
};

#endif