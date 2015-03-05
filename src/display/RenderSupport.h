#ifndef _RENDERSUPPORT_H_
#define _RENDERSUPPORT_H_

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include "utils\Matrix.h"
#include "DisplayObject.h"
#include "utils\Pool.h"
#include "ShaderProgram.h"
#include <vector>

using namespace std;

class Image;
class Texture;

class RenderSupport
{
public:
    RenderSupport(const int screenWidth = 800, const int screenHeight = 600);
    ~RenderSupport();

    void NextFrame();
    void EndFrame();
    void PrependMatrix(Matrix& matrix);
    void TransformMatrix(DisplayObject& object);
    void PushMatrix();
    void PopMatrix();
    void DrawImage(Image& image, float parentAlpha);

    int GetDrawCount() { return m_DrawCount; }

private:
    void    ResetMatrix();
    void    initSDL();
    void    initGL();
    GLuint  loadShaderFromFile(string path, GLenum shaderType);

    SDL_Window*         m_window;
    SDL_GLContext       m_context;
    const int           m_screenWidth;
    const int           m_screenHeight;
    GLuint              m_gProgramID;
    ShaderProgram       m_shaderProgram;
    LColorRGBA          m_textureColor;

    vector<Matrix*>     m_MatrixStack;
    unsigned int        m_MatrixStackSize;
    Matrix              m_ModelViewMatrix;
    Texture*            m_CurrentTexture;
    int                 m_DrawCount;
    Pool<Matrix>        m_MatrixPool;
};

#endif