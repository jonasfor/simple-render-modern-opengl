#include "shaders.h"
#include <iostream>
#include <fstream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string fileName);
static GLuint CreateShader(const std::string text, GLenum shader_type);

Shader::Shader(const std::string fileName)
{
    m_program = glCreateProgram();

    m_shaders[0] = CreateShader(LoadShader(fileName + ".ws"), GL_VERTEX_SHADER);
    m_shaders[0] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);



    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "postition");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR: Program linking failed: ");    

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR: Program is invalid: ");
    
}

Shader::~Shader()
{

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
        
    }
    glDeleteProgram(m_program);
}

void Shader::Bind()
{
    glUseProgram(m_program);   
}

static GLuint CreateShader(const std::string text, GLenum shader_type)
{

    
    GLuint shader = glCreateShader(shader_type);

    if(shader == 0)
        std::cerr << "Error: Shader creation failed" << std::endl;

    const GLchar * shaderSourceStrings[1];
    GLint shaderSourceStringsLen[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLen[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLen);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compile error: ");


    return shader;
}
static std::string LoadShader(const std::string fileName)
{
    std::ifstream file;

    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
        
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }
    
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ":  '" << error << "'" << std::endl;

    }
}