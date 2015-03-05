#include "GL/glew.h"
#include "AssetManager.h"
#include "TexturedVertex2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>

const char* AssetManager::ID = "AssetManager_ID";
const GLenum AssetManager::DEFAULT_TEXTURE_WRAP = GL_REPEAT;

void AssetManager::loadAtlas(const string name, const string imagePath, const string dataPath)
{
    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", imagePath.c_str(), IMG_GetError());
        return;
    }

    GLuint nOfColors = loadedSurface->format->BytesPerPixel;
    GLuint pixelFormat = GL_RGBA;

    if (nOfColors == 4)     // contains an alpha channel
    {
        if (loadedSurface->format->Rmask == 0x000000ff)
        {
            pixelFormat = GL_RGBA;
        }
        else
        {
            pixelFormat = GL_BGRA;
        }
                    
    } 
    else if (nOfColors == 3)     // no alpha channel
    {
        if (loadedSurface->format->Rmask == 0x000000ff)
        {
            pixelFormat = GL_RGB;
        }
        else
        {
            pixelFormat = GL_BGR;
        }
    } 
    else 
    {
        printf("warning: the image is not truecolor..  this will probably break\n");
        return;
        // this error should not go unhandled
    }

    TexturePtr texture;
    loadTextureFromPixels(texture, static_cast<GLuint*>(loadedSurface->pixels), loadedSurface->w, loadedSurface->h, pixelFormat);
    SDL_FreeSurface( loadedSurface );

    string dataString;
    ifstream dataFile(dataPath.c_str());

    if (!dataFile)
    {
        printf("Unable to load data %s !", dataPath.c_str());
        return;
    }

    dataString.assign(std::istreambuf_iterator<char>(dataFile), std::istreambuf_iterator<char>());
    m_Atlases.insert(pair<string, TextureAtlasPtr>(name, TextureAtlasPtr(new TextureAtlas(texture, dataString))));

}

TextureAtlasPtr& AssetManager::GetTextureAtlas(const string name)
{
    unordered_map<string, TextureAtlasPtr>::iterator it = m_Atlases.find(name);
    return it->second;
}

void AssetManager::loadTextureFromPixels(TexturePtr& texture, GLuint* pixels, GLuint textureWidth, GLuint textureHeight, GLuint mode)
{
    GLuint textureId;

    glGenTextures(1, &textureId);

    //Bind texture ID
    glBindTexture(GL_TEXTURE_2D, textureId);

    //Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, DEFAULT_TEXTURE_WRAP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, DEFAULT_TEXTURE_WRAP );

    //Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, mode, textureWidth, textureHeight, 0, mode, GL_UNSIGNED_BYTE, pixels);

    //Unbind texture
    glBindTexture(GL_TEXTURE_2D, NULL);

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return;
    }

    //Generate VBO
    //Vertex data
    TexturedVertex2D vData[4];
    GLuint iData[4];

    //Set rendering indices
    iData[0] = 0;
    iData[1] = 1;
    iData[2] = 2;
    iData[3] = 3;

    GLuint vertexBufferId;
    GLuint indexBufferId;

    //Create VBO
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TexturedVertex2D), vData, GL_DYNAMIC_DRAW);

    //Create IBO
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

    //Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

    texture = TexturePtr(new Texture(textureId, textureWidth, textureHeight, vertexBufferId, indexBufferId));
}