#include <iostream>

#include <glad/glad.h>

#include "shader.hpp"

#define ASSERT_LOC(LOCATION) (assert((location) > -1))

Shader::Shader() : m_Program(0) 
{
    m_Program = glCreateProgram(); 
}

bool Shader::AttachShader(const char* shaderSrc, GLenum shaderType) 
{
    int32_t success;
    char infoLog[512]; 
    uint32_t shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false; 
    }

    glAttachShader(m_Program, shader);
    m_AttachedShaders.emplace_back(shader); 
    return true; 
}

bool Shader::CompileProgram() 
{
    int32_t success;
    char infoLog[512]; 
    glLinkProgram(m_Program);
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (success) {
        for (auto& shader : m_AttachedShaders) {
            glDeleteShader(shader); 
        }

        m_AttachedShaders.clear(); 
    } else {
        glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    return success; 
}

void Shader::Bind() 
{
    glUseProgram(m_Program); 
}

GLint Shader::GetUniformLocation(const char* name) 
{
    return glGetUniformLocation(m_Program, name); 
}

void Shader::SetUniformVec2f(const char* name, const VML::Vec2f& vec) 
{
    GLint location = GetUniformLocation(name); 
    ASSERT_LOC(location); 
    glUniform2fv(location, 1, &vec.x); 
}

void Shader::SetUniformMat3f(const char* name, const VML::Mat3f& mat, GLboolean transpose) 
{
    GLint location = GetUniformLocation(name); 
    ASSERT_LOC(location); 
    glUniformMatrix3fv(location, 1, transpose, &mat[0]); 
}

void Shader::SetUniformMat4f(const char* name, const VML::Mat4f& mat, GLboolean transpose) 
{
    GLint location = GetUniformLocation(name); 
    ASSERT_LOC(location); 
    glUniformMatrix4fv(location, 1, transpose, &mat[0]); 
}