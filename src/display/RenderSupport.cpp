#include "RenderSupport.h"
#include "utils\MatrixUtil.h"
#include "Image.h"
#include "Texture.h"
#include "TexturedVertex2D.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

RenderSupport::RenderSupport(const int screenWidth, const int screenHeight) 
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_MatrixStackSize(0), 
    m_CurrentTexture(nullptr), m_DrawCount(0)
{
    m_textureColor.r = 1.f;
    m_textureColor.g = 1.f;
    m_textureColor.b = 1.f;
    m_textureColor.a = 1.f;

    initSDL();
    initGL();
}

RenderSupport::~RenderSupport()
{
    m_MatrixStack.clear();
}

void RenderSupport::initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);

    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    m_context = SDL_GL_CreateContext(m_window);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    //Use Vsync
    SDL_GL_SetSwapInterval(1);
}

void RenderSupport::initGL()
{
    //Enable texturing
    glEnable( GL_TEXTURE_2D );

    //Set blending
    glEnable( GL_BLEND );
    glDisable( GL_DEPTH_TEST );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return;
    }

    m_shaderProgram.loadProgram();

    //Bind textured shader program
    m_shaderProgram.bind();

    //Initialize projection
    m_shaderProgram.setProjection(glm::ortho<GLfloat>(0.0, m_screenWidth, m_screenHeight, 0.0, 1.0, -1.0));
    m_shaderProgram.updateProjection();

    //Initialize modelview
    m_shaderProgram.setModelView(glm::mat4());
    m_shaderProgram.updateModelView();

    //Set texture unit
    m_shaderProgram.setTextureUnit(0);
}

void RenderSupport::NextFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Reset transformations
    m_shaderProgram.setModelView(glm::mat4());

    //Render texture centered
    m_shaderProgram.setTextureColor(m_textureColor);

    ResetMatrix();

    m_DrawCount = 0;
}

void RenderSupport::EndFrame()
{
    SDL_GL_SwapWindow(m_window);
}

void RenderSupport::PrependMatrix(Matrix& matrix)
{
    MatrixUtil::PrependMatrix(m_ModelViewMatrix, matrix);
}

void RenderSupport::TransformMatrix(DisplayObject& object)
{
    MatrixUtil::PrependMatrix(m_ModelViewMatrix, object.GetTransformationMatrix());
}

void RenderSupport::PushMatrix()
{
    if (m_MatrixStack.size() < m_MatrixStackSize + 1)
    {
        /*Matrix* mat = m_MatrixPool.Get();
        mat->Identity();
        m_MatrixStack.push_back(mat);*/

        m_MatrixStack.push_back(new Matrix());
    }

    m_MatrixStack[m_MatrixStackSize++]->CopyFrom(m_ModelViewMatrix);
}

void RenderSupport::PopMatrix()
{
    int index = m_MatrixStackSize - 1;
    Matrix* matrix = m_MatrixStack[index];
    m_MatrixStack.erase(m_MatrixStack.begin() + index);
    m_ModelViewMatrix.CopyFrom(*(matrix));
    //m_MatrixPool.Release(matrix);

    delete matrix;

    m_MatrixStackSize--;
}

void RenderSupport::DrawImage(Image& image, float parentAlpha)
{
    /*if (!m_CurrentTexture || (&m_CurrentTexture->GetImage() != &image.GetTexture().GetImage()))
    {
        m_DrawCount++;
    }*/

    //m_CurrentTexture = &image.GetTexture();

    ITexture& texture = image.GetTexture();
    //CIw2DImage* cIw2DImage = &(texture.GetImage());

    float x = image.GetX();
    float y = image.GetY();
    float w = texture.GetWidth();
    float h = texture.GetHeight();
    float clipX = texture.GetX();
    float clipY = texture.GetY();
    float clipW = texture.GetWidth();
    float clipH = texture.GetHeight();

    const ITexture* parent = texture.GetParent();
    int textureWidth = (parent) ? parent->GetWidth() : texture.GetWidth();
    int textureHeight = (parent) ? parent->GetHeight() : texture.GetHeight();

    float a = m_ModelViewMatrix.m_A;
    float b = m_ModelViewMatrix.m_B;
    float c = m_ModelViewMatrix.m_C;
    float d = m_ModelViewMatrix.m_D;

    float tx = m_ModelViewMatrix.m_Tx;
    float ty = m_ModelViewMatrix.m_Ty;
    float sx = (a / abs(a)) * (sqrt(pow(a, 2.0f) + pow(c, 2.0f)));
    float sy = (d / abs(d)) * (sqrt(pow(b, 2.0f) + pow(d, 2.0f)));
    float q = atan2(b, d);

    //Texture coordinates
    GLfloat texTop = 0.f;
    GLfloat texBottom = (GLfloat)h / (GLfloat)clipH;
    GLfloat texLeft = 0.f;
    GLfloat texRight = (GLfloat)w / (GLfloat)clipW;

    //Texture coordinates
    texLeft = clipX / textureWidth;
    texRight = (clipX + clipW) / textureWidth;
    texTop = clipY / textureHeight;
    texBottom = (clipY + clipH) / textureHeight;

    //Vertex coordinates
    GLfloat quadWidth = w;
    GLfloat quadHeight = h;

    //Move to rendering point
    m_shaderProgram.leftMultModelView(glm::translate(glm::vec3(x, y, 0.f)));
    m_shaderProgram.updateModelView();

    //Set vertex data
    TexturedVertex2D vData[4];

    //Texture coordinates
    vData[0].texCoord.s =  texLeft; vData[0].texCoord.t =    texTop;
    vData[1].texCoord.s = texRight; vData[1].texCoord.t =    texTop;
    vData[2].texCoord.s = texRight; vData[2].texCoord.t = texBottom;
    vData[3].texCoord.s =  texLeft; vData[3].texCoord.t = texBottom;

    //Vertex positions
    vData[0].position.x =       0.f; vData[0].position.y =        0.f;
    vData[1].position.x = quadWidth; vData[1].position.y =        0.f;
    vData[2].position.x = quadWidth; vData[2].position.y = quadHeight;
    vData[3].position.x =       0.f; vData[3].position.y = quadHeight;

    //Set texture ID
    glBindTexture(GL_TEXTURE_2D, texture.GetId());

        //Enable vertex and texture coordinate arrays
    m_shaderProgram.enableVertexPointer();
    m_shaderProgram.enableTexCoordPointer();

    //Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, texture.GetVertexBufferId());

    //Update vertex buffer data
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(TexturedVertex2D), vData);

    //Set texture coordinate data
    m_shaderProgram.setTexCoordPointer( sizeof(TexturedVertex2D), (GLvoid*)offsetof(TexturedVertex2D, texCoord));

    //Set vertex data
    m_shaderProgram.setVertexPointer( sizeof(TexturedVertex2D), (GLvoid*)offsetof(TexturedVertex2D, position));

    //Draw quad using vertex data and index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture.GetIndexBufferId());
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    //Disable vertex and texture coordinate arrays
    m_shaderProgram.disableVertexPointer();
    m_shaderProgram.disableTexCoordPointer();

    /*Iw2DSetColour(0xffffffff);
    Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);
    CIwFMat2D mat;
    mat.SetRot(q);
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.SetTrans(CIwFVec2(tx, ty));
    Iw2DSetTransformMatrix(mat);*/

    //Iw2DDrawImageRegion(cIw2DImage, CIwFVec2(0, 0), CIwFVec2(w, h), CIwFVec2(srcX, clipY), CIwFVec2(srcW, srcH));
}

void RenderSupport::ResetMatrix()
{
    m_MatrixStackSize = 0;
    m_ModelViewMatrix.Identity();
}