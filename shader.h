#pragma once

#include <vector>

class Shader {

public:
    Shader();

    bool AttachShader(const char* shaderSrc, GLenum shaderType); 
    bool CompileProgram(); 

    void Bind(); 

private:
    uint32_t m_Program;
    std::vector<uint32_t> m_AttachedShaders{}; 

};