#pragma once

#include <vector>

#include "math/math.hpp"

class Shader 
{

public:
    Shader();

    bool AttachShader(const char* shaderSrc, GLenum shaderType); 
    bool CompileProgram(); 

    void Bind(); 

    // Uniforms

    GLint GetUniformLocation(const char* name); 

    void SetUniformVec2f(const char* name, const Vec2f& vec);
    void SetUniformVec3f(const char* name, const Vec3f& vec); 
    void SetUniformVec4f(const char* name, const Vec4f& vec); 

    void SetUniformMat3f(const char* name, const Mat3f& mat, GLboolean transpose = GL_FALSE);
    void SetUniformMat4f(const char* name, const Mat4f& mat, GLboolean transpose = GL_FALSE); 

private:
    uint32_t m_Program;
    std::vector<uint32_t> m_AttachedShaders{}; 

};