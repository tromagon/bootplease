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

    const int           GetX() const                { return static_cast<int>(m_Region.m_X); }
    const int           GetY() const                { return static_cast<int>(m_Region.m_Y); }
    const int           GetWidth() const            { return static_cast<int>(m_Region.m_Width); }
    const int           GetHeight() const           { return static_cast<int>(m_Region.m_Height); }
    const unsigned int  GetId() const               { return m_ParentTexture->GetId(); }
    const unsigned int  GetVertexBufferId() const   { return m_ParentTexture->GetVertexBufferId(); }
    const unsigned int  GetIndexBufferId() const    { return m_ParentTexture->GetIndexBufferId(); }
    const Texture*      GetParent() const           { return m_ParentTexture.get(); }
};

#endif