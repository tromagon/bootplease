#ifndef _TEXTUREATLAS_H_
#define _TEXTUREATLAS_H_

#include "Texture.h"
#include "SubTexture.h"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class TextureAtlas
{
    typedef unordered_map<string, ITexturePtr> TextureMap;

public:
    explicit TextureAtlas(TexturePtr& atlasTexture, const string atlasData);
    //~TextureAtlas();

    TexturePtr&     GetAtlasTexture() { return m_AtlasTexture; }
    ITexturePtr&    GetTexture(const string name);
    
private:
    void ParseAtlas(const string atlasData);

    TexturePtr      m_AtlasTexture;
    TextureMap      m_subTextures;
};

typedef unique_ptr<TextureAtlas> TextureAtlasPtr;

#endif