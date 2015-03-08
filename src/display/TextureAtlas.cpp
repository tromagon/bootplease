#include "TextureAtlas.h"
#include "cJSON.h"
#include <memory>

TextureAtlas::TextureAtlas(TexturePtr& atlasTexture, const string atlasData) 
    : m_AtlasTexture(move(atlasTexture))
{
    ParseAtlas(atlasData);
}

ITexturePtr& TextureAtlas::GetTexture(const string name)
{
    TextureMap::iterator it = m_subTextures.find(name);
    return it->second;
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

        bootplease::Rectangle region(x, y, w, h);
        m_subTextures.insert(pair<string, ITexturePtr>(name, ITexturePtr(new SubTexture(m_AtlasTexture, region))));
    }

    cJSON_Delete(root);
}