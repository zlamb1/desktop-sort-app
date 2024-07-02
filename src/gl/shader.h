#pragma once

#include <vector>

#include "math.h"

class Shader {

public:
    Shader();

    bool AttachShader(const char* shaderSrc, GLenum shaderType); 
    bool CompileProgram(); 

    void Bind(); 

    // Uniforms

    void SetUniformVec2f(const char* name, Vec2<float> data);

private:
    uint32_t m_Program;
    std::vector<uint32_t> m_AttachedShaders{}; 

};