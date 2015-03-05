#ifndef _TEXTUREATLAS_H_
#define _TEXTUREATLAS_H_

#include "Texture.h"
#include "SubTexture.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class TextureAtlas
{
public:
    explicit TextureAtlas(TexturePtr& atlasTexture, const string atlasData);
    ~TextureAtlas();

    TexturePtr& GetAtlasTexture() { return m_AtlasTexture; }
    ITexture*    GetTexture(const string name);
    
private:
    void ParseAtlas(const string atlasData);
    void AddRegion(const string name, bootplease::Rectangle region);

    class SubTextureItem
    {
    public:
        const string    m_Name;
        SubTexture&     m_SubTexture;

    public:
        explicit SubTextureItem(const string name, SubTexture& texture) 
            : m_Name(name), m_SubTexture(texture) {}
    };

    TexturePtr              m_AtlasTexture;
    vector<SubTextureItem*> m_SubTextures;
};

typedef unique_ptr<TextureAtlas> TextureAtlasPtr;

#endif