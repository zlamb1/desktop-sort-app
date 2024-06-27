#pragma once

class Shader {

public:
    Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc);

    void Bind(); 

private:
    uint32_t m_Program; 

};