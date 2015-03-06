#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <memory>

using namespace std;

class Texture;
typedef unique_ptr<Texture> TexturePtr;

class ITexture
{
public:
    virtual const int           GetX() const = 0;
    virtual const int           GetY() const = 0;
    virtual const int           GetWidth() const = 0;
    virtual const int           GetHeight() const = 0;
    virtual const unsigned int  GetId() const = 0;
    virtual const unsigned int  GetVertexBufferId() const = 0;
    virtual const unsigned int  GetIndexBufferId() const = 0;
    virtual const Texture*      GetParent() const = 0;
};

class Texture : public ITexture
{
public:
    explicit Texture(const unsigned int textureId, int textureWidth, int textureHeight, const unsigned int vertexBufferId, const unsigned int indexBufferId) 
        : m_textureId(textureId), m_textureWidth(textureWidth), m_textureHeight(textureHeight), m_vertexBufferId(vertexBufferId), m_indexBufferId(indexBufferId) {}

    const int           GetX() const                { return 0; }
    const int           GetY() const                { return 0; }
    const int           GetWidth() const            { return m_textureWidth; }
    const int           GetHeight() const           { return m_textureHeight; }
    const unsigned int  GetId() const               { return m_textureId; }
    const unsigned int  GetVertexBufferId() const   { return m_vertexBufferId; }
    const unsigned int  GetIndexBufferId() const    { return m_indexBufferId; }
    const Texture*      GetParent() const           { return nullptr; }

protected:
    const unsigned int  m_textureId;
    const unsigned int  m_vertexBufferId;
    const unsigned int  m_indexBufferId;
    int                 m_textureWidth;
    int                 m_textureHeight;
};

#endif