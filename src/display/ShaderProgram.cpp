#include "ShaderProgram.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

bool ShaderProgram::loadProgram()
{
    m_programID = glCreateProgram();

    GLuint vertexShader = loadShaderFromFile("LTexturedPolygonProgram2D.glvs", GL_VERTEX_SHADER);

    //Check for errors
    if( vertexShader == 0 )
    {
        glDeleteProgram(m_programID);
        m_programID = 0;
        return false;
    }

    //Attach vertex shader to program
    glAttachShader(m_programID, vertexShader);

    //Create fragment shader
    GLuint fragmentShader = loadShaderFromFile("LTexturedPolygonProgram2D.glfs", GL_FRAGMENT_SHADER);

    //Check for errors
    if(fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        glDeleteProgram(m_programID);
        m_programID = 0;
        return false;
    }

    //Attach fragment shader to program
    glAttachShader(m_programID, fragmentShader);

    //Link program
    glLinkProgram(m_programID);

    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &programSuccess);
    if( programSuccess != GL_TRUE )
    {
        printf( "Error linking program %d!\n", m_programID);
        printProgramLog(m_programID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(m_programID);
        m_programID = 0;
        return false;
    }

    //Clean up excess shader references
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_vertexPos2DLocation = glGetAttribLocation(m_programID, "LVertexPos2D");
    m_texCoordLocation = glGetAttribLocation(m_programID, "LTexCoord");
    m_textureColorLocation = glGetUniformLocation(m_programID, "LTextureColor");
    m_textureUnitLocation = glGetUniformLocation(m_programID, "LTextureUnit");
    m_projectionMatrixLocation = glGetUniformLocation(m_programID, "LProjectionMatrix");
    m_modelViewMatrixLocation = glGetUniformLocation(m_programID, "LModelViewMatrix");

    return true;
}

bool ShaderProgram::bind()
{
    glUseProgram(m_programID);
    //Check for error

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error binding shader! %s\n", gluErrorString( error ) );
        printProgramLog(m_programID);
        return false;
    }

    return true;
}

void ShaderProgram::unbind()
{
    //Use default program
    glUseProgram( NULL );
}

void ShaderProgram::setProjection(glm::mat4 matrix)
{
    m_projectionMatrix = matrix; 
}

void ShaderProgram::updateProjection()
{
    glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
}

void ShaderProgram::setModelView(glm::mat4 matrix)
{
    m_modelViewMatrix = matrix;
}

void ShaderProgram::leftMultModelView( glm::mat4 matrix )
{
    m_modelViewMatrix = matrix * m_modelViewMatrix;
}

void ShaderProgram::enableVertexPointer()
{
    glEnableVertexAttribArray(m_vertexPos2DLocation);
}

void ShaderProgram::disableVertexPointer()
{
    glDisableVertexAttribArray(m_vertexPos2DLocation);
}

void ShaderProgram::enableTexCoordPointer()
{
    glEnableVertexAttribArray(m_texCoordLocation);
}

void ShaderProgram::disableTexCoordPointer()
{
    glDisableVertexAttribArray(m_texCoordLocation);
}

void ShaderProgram::setTexCoordPointer(GLsizei stride, const GLvoid* data)
{
    glVertexAttribPointer(m_texCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void ShaderProgram::setVertexPointer( GLsizei stride, const GLvoid* data)
{
    glVertexAttribPointer(m_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void ShaderProgram::updateModelView()
{
    glUniformMatrix4fv(m_modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_modelViewMatrix));
}

void ShaderProgram::setTextureUnit(GLuint unit)
{
    glUniform1i(m_textureUnitLocation, unit);
}

void ShaderProgram::setTextureColor(LColorRGBA color)
{
    glUniform4f(m_textureColorLocation, color.r, color.g, color.b, color.a);
}

GLuint ShaderProgram::loadShaderFromFile(std::string path, GLenum shaderType)
{
    //Open file
    GLuint shaderID = 0;
    std::string shaderString;
    std::ifstream sourceFile(path.c_str());

    if(sourceFile)
    {
        //Get shader source
        shaderString.assign(std::istreambuf_iterator<char>(sourceFile), std::istreambuf_iterator<char>());

        //Create shader ID
        shaderID = glCreateShader( shaderType );

        //Set shader source
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

        //Compile shader source
        glCompileShader( shaderID );

        //Check shader for errors
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if(shaderCompiled != GL_TRUE)
        {
            printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
            printShaderLog(shaderID);
            glDeleteShader(shaderID);
            shaderID = 0;
        }
    }
    else
    {
        printf("Unable to open file %s\n", path.c_str());
    }

    return shaderID;
}

void ShaderProgram::printProgramLog(GLuint program)
{
    //Make sure name is shader
    if(glIsProgram(program))
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if(infoLogLength > 0)
        {
            //Print Log
            printf("%s\n", infoLog);
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf("Name %d is not a program\n", program);
    }
}

void ShaderProgram::printShaderLog( GLuint shader )
{
    //Make sure name is shader
    if(glIsShader(shader))
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if(infoLogLength > 0)
        {
            //Print Log
            printf("%s\n", infoLog);
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf("Name %d is not a shader\n", shader);
    }
}