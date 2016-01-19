#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
    public:
        Shader();
        void CreateProgram();
        void Bind();
        void AddShader(const GLenum shaderType, const GLchar* shaderPath);
        GLuint CreateShader(const GLenum shaderType, const GLchar* shaderPath);
        void loadShaderFile(const GLchar * filepath, std::string & str);
        GLuint GetProgram();
        void AddUniform(const std::string &name);
        GLuint GetUniform(const std::string name);
        void UpdateUniform(const std::string &name, const glm::mat4 &matrix);
		void UpdateUniform(const std::string &name, const glm::vec3 &vec);
        void UpdateUniform(const std::string &name, int &textureNumber);
        virtual ~Shader();
    protected:
    private:
        GLuint program;
        std::vector<GLuint> shaders;
        std::map<std::string, GLuint> uniforms;
};

#endif // SHADER_H
