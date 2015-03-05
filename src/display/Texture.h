#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <memory>

using namespace std;

class ITexture
{
public:
    virtual const int           GetX() = 0;
    virtual const int           GetY() = 0;
    virtual const int           GetWidth() = 0;
    virtual const int           GetHeight() = 0;
    virtual const unsigned int  GetId() = 0;
    virtual const unsigned int  GetVertexBufferId() = 0;
    virtual const unsigned int  GetIndexBufferId() = 0;
};

class Texture : public ITexture
{
public:
    explicit Texture(const unsigned int textureId, int textureWidth, int textureHeight, const unsigned int vertexBufferId, const unsigned int indexBufferId) 
        : m_textureId(textureId), m_textureWidth(textureWidth), m_textureHeight(textureHeight), m_vertexBufferId(vertexBufferId), m_indexBufferId(indexBufferId) {}

    const int           GetX()                  { return 0; }
    const int           GetY()                  { return 0; }
    const int           GetWidth()              { return m_textureWidth; }
    const int           GetHeight()             { return m_textureHeight; }
    const unsigned int  GetId()                 { return m_textureId; }
    const unsigned int  GetVertexBufferId()     { return m_vertexBufferId; }
    const unsigned int  GetIndexBufferId()      { return m_indexBufferId; }

protected:
    const unsigned int  m_textureId;
    const unsigned int  m_vertexBufferId;
    const unsigned int  m_indexBufferId;
    int                 m_textureWidth;
    int                 m_textureHeight;
};

typedef unique_ptr<Texture> TexturePtr;

#endif