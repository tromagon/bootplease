#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <string>
#include <glm\glm.hpp>

struct LColorRGBA
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

class ShaderProgram
{
public:
    ShaderProgram() {}

    bool loadProgram();
    bool bind();
    void unbind();
    void setProjection(glm::mat4 matrix);
    void setModelView(glm::mat4 matrix);
    void leftMultModelView(glm::mat4 matrix);
    void updateProjection();
    void updateModelView();
    void setTextureUnit(GLuint unit);
    void setTextureColor(LColorRGBA color);
    void enableVertexPointer();
    void disableVertexPointer();
    void enableTexCoordPointer();
    void disableTexCoordPointer();
    void setTexCoordPointer(GLsizei stride, const GLvoid* data);
    void setVertexPointer( GLsizei stride, const GLvoid* data);

private:
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);
    void printProgramLog(GLuint program);
    void printShaderLog( GLuint shader );

    GLuint m_programID;

    GLint m_vertexPos2DLocation;
    GLint m_texCoordLocation;

    //Coloring location
    GLint m_textureColorLocation;

    //Texture unit location
    GLint m_textureUnitLocation;

    //Projection matrix
    glm::mat4 m_projectionMatrix;
    GLint m_projectionMatrixLocation;

    //Modelview matrix
    glm::mat4 m_modelViewMatrix;
    GLint m_modelViewMatrixLocation;
};

#endif