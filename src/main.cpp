#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ui/rect.h"

#include "gl/shader.h"
#include "gl/gl_renderer.h"

static int fbWidth = 640, fbHeight = 480; 

static void onFramebufferResize(GLFWwindow* window, int width, int height) {
    fbWidth = width;
    fbHeight = height; 
    glViewport(0, 0, width, height); 
}


int main() {
    if (!glfwInit()) {
        std::cout << "failed to initialize GLFW" << std::endl;
        return -1; 
    }

    GLFWwindow* window = glfwCreateWindow(fbWidth, fbHeight, "Hello, window!", NULL, NULL);
    if (!window) {
        std::cout << "failed to initialize GLFW window" << std::endl;
        return -1; 
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    
    glfwSetFramebufferSizeCallback(window, onFramebufferResize);

    uint32_t vbo = 0, vertexCount = 0;

    glGenBuffers(1, &vbo);  
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    const size_t vertexSize = sizeof(GL::RectVertex); 

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GL::RectVertex, rgba))); 
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GL::RectVertex, center))); 
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GL::RectVertex, extents))); 
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GL::RectVertex, radius))); 

    auto rect = GL::GLRectangle(0.05f, 0.05f, 0.9f, 0.9f);
    auto vertexData = GL::GenVertexData(rect); 

    vertexCount += vertexData.size(); 
    glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);

    auto rectShader = Shader();
    rectShader.AttachShader(GL::RECT_VERTEX_SHADER, GL_VERTEX_SHADER);
    rectShader.AttachShader(GL::RECT_FRAG_SHADER, GL_FRAGMENT_SHADER); 
    rectShader.CompileProgram(); 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    glEnable(GL_STENCIL_TEST);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        rectShader.Bind(); 
        rectShader.SetUniformVec2f("uResolution", Vec2<float>{ (float)fbWidth, (float)fbHeight });
        glDrawArrays(GL_TRIANGLES, 0, vertexCount); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}