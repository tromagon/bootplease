#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "TextureAtlas.h"
#include <SDL_opengl.h>
#include <unordered_map>
#include <string>

using namespace std;

class AssetManager
{
public:
    AssetManager() {}
    ~AssetManager() {}

    static const char* ID;

    void                loadAtlas(const string name, const string imagePath, const string dataPath);
    TextureAtlasPtr&    GetTextureAtlas(const string name);

private:
    void loadTextureFromPixels(TexturePtr& texture, GLuint* pixels, GLuint width, GLuint height, GLuint mode);

    static const GLenum DEFAULT_TEXTURE_WRAP;
    unordered_map<string, TextureAtlasPtr> m_Atlases;
};

#endif