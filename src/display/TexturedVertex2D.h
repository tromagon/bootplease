#ifndef _TEXTUREDVERTEX2D_H_
#define _TEXTUREDVERTEX2D_H_

#include <SDL_opengl.h>

struct VertexPos2D
{
    GLfloat x;
    GLfloat y;
};

struct TexCoord
{
    GLfloat s;
    GLfloat t;
};

struct TexturedVertex2D
{
    VertexPos2D position;
    TexCoord texCoord;
};

#endif