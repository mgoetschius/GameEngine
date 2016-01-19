#include "Shader.h"

Shader::Shader()
{
}

void Shader::CreateProgram()
{
    program = glCreateProgram();

    for(unsigned int i = 0; i < shaders.size(); i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(this->program);
    GLint result;
    GLchar infoLog[512];
    glGetProgramiv(this->program, GL_LINK_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR Linking Program" << std::endl;
        std::cout << infoLog << std::endl;
    }

    for(unsigned int i = 0; i < shaders.size(); i++)
        glDetachShader(program, shaders[i]);

    for(std::vector<GLuint>::const_iterator i = shaders.begin(); i != shaders.end(); i++ )
    {
        glDeleteShader(*i);
    }
}

void Shader::Bind()
{
    glUseProgram(program);
}

GLuint Shader::GetProgram()
{
    return program;
}

void Shader::AddShader(const GLenum shaderType, const GLchar* shaderPath)
{
    shaders.push_back(CreateShader(shaderType, shaderPath));
}

GLuint Shader::CreateShader(const GLenum shaderType, const GLchar* shaderPath)
{
    GLuint shader = glCreateShader(shaderType);
    std::string shaderCode;
    loadShaderFile(shaderPath, shaderCode);
    char const * shaderSource = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint result;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(!result)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR: " << shaderPath << std::endl;
        std::cout << infoLog << std::endl;
    }

    return shader;
}

void Shader::loadShaderFile(const GLchar * filepath, std::string & str)
{
        std::ifstream shaderFile(filepath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        str = shaderStream.str();
}

void Shader::AddUniform(const std::string &name)
{
    uniforms[name] = glGetUniformLocation(program, name.c_str());
}

GLuint Shader::GetUniform(const std::string name)
{
    return uniforms[name.c_str()];
}

void Shader::UpdateUniform(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(uniforms[name.c_str()], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UpdateUniform(const std::string &name, const glm::vec3 &vec)
{
	glUniform3fv(uniforms[name.c_str()], 1, glm::value_ptr(vec));
}

void Shader::UpdateUniform(const std::string &name, int &value)
{
    glUniform1i(uniforms[name.c_str()], value);
}

Shader::~Shader()
{
    //dtor
}
