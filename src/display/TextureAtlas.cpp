#include "TextureAtlas.h"
#include "cJSON.h"
#include <memory>


TextureAtlas::TextureAtlas(TexturePtr& atlasTexture, const string atlasData) 
    : m_AtlasTexture(move(atlasTexture))
{
    ParseAtlas(atlasData);
}

TextureAtlas::~TextureAtlas()
{
    const int l = m_SubTextures.size();
    for (int i = l - 1 ; i >= 0 ; i--)
    {
        SubTextureItem* item = m_SubTextures[i];
        delete &(item->m_SubTexture);

        m_SubTextures.erase(m_SubTextures.begin() + i);
        delete item;
    }
}

ITexture* TextureAtlas::GetTexture(const string name)
{
    const int l = m_SubTextures.size();
    for (int i = 0 ; i < l ; i++)
    {
        SubTextureItem* item = m_SubTextures[i];
        if (item->m_Name == name)
        {
            return &(item->m_SubTexture);
        }
    }

    return nullptr;
}

void TextureAtlas::ParseAtlas(const string atlasData)
{
    cJSON* root = cJSON_Parse(atlasData.c_str());
    cJSON* frames = cJSON_GetObjectItem(root, "frames");

    int numFrames = cJSON_GetArraySize(frames);
    for (int i = 0 ; i < numFrames ; i++)
    {
        cJSON* frameItem = cJSON_GetArrayItem(frames, i);
        cJSON* frame = cJSON_GetObjectItem(frameItem, "frame");

        const string name = static_cast<string>(cJSON_GetObjectItem(frameItem, "filename")->valuestring);
        int x = cJSON_GetObjectItem(frame, "x")->valueint;
        int y = cJSON_GetObjectItem(frame, "y")->valueint;
        int w = cJSON_GetObjectItem(frame, "w")->valueint;
        int h = cJSON_GetObjectItem(frame, "h")->valueint;
        
        AddRegion(name, bootplease::Rectangle(x, y, w, h));
    }

    cJSON_Delete(root);
}

void TextureAtlas::AddRegion(const string name, bootplease::Rectangle region)
{
    SubTexture* subTexture = new SubTexture(m_AtlasTexture, region);
    SubTextureItem* item = new SubTextureItem(name, *subTexture);
    m_SubTextures.push_back(item);

}