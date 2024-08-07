#include <iostream>

#include <glad/glad.h>

#include "ref.hpp"

#include "gl/shader.hpp"
#include "gl/gl_renderer.hpp"
#include "window/glfw_window.hpp"

int main() 
{
    if (!glfwInit()) 
    {
        std::cout << "failed to initialize GLFW" << std::endl;
        return -1; 
    }

    int32_t width = 500, height = 500; 
    Ref<WindowWrapper> window = CreateRef<GLFWWindowWrapper>("Hello, window!", width, height);
    VML::Mat4f orthoProjection = VML::CreateOrthoProjectionf(0.0f, width, 0.0f, height, -1.0f, 1.0f); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    
    uint32_t vbo = 0, vertexCount = 0;

    glGenBuffers(1, &vbo);  
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    const size_t vertexSize = sizeof(GL::RectVertex); 

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GL::RectVertex, rgba))); 

    auto rect = GL::Rectangle();
    rect.m_BBox = { 50.0f, 100.0f, 50.0f, 100.0f };
    std::vector<GL::RectVertex> vec{};
    auto vertexData = GL::GenVertexData(vec, rect); 

    vertexCount += vertexData.size(); 
    glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);

    auto rectShader = Shader();
    rectShader.AttachShader(GL::RECT_VERTEX_SHADER, GL_VERTEX_SHADER);
    rectShader.AttachShader(GL::RECT_FRAG_SHADER, GL_FRAGMENT_SHADER); 
    rectShader.CompileProgram(); 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    while (window->IsRunning()) 
    {
        if (window->m_FramebufferSizeDirty)
        {
            window->m_FramebufferSizeDirty = false; 
            auto framebufferSize = window->GetFramebufferSize(); 
            orthoProjection = VML::CreateOrthoProjectionf(0.0f, framebufferSize.width, 0.0f, framebufferSize.height, -1.0f, 1.0f); 
            glViewport(0, 0, framebufferSize.width, framebufferSize.height); 
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        rectShader.Bind(); 
        rectShader.SetUniformMat4f("uProjection", orthoProjection, GL_TRUE); 
        glDrawArrays(GL_TRIANGLES, 0, vertexCount); 
        window->OnFrame(); 
    }
}