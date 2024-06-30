#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rect.h"
#include "shader.h"

#include "gl_renderer.h"

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

    const size_t vertexSize = sizeof(GLRect::Vertex); 

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GLRect::Vertex, rgba))); 
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GLRect::Vertex, center))); 
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(GLRect::Vertex, radius))); 
    glEnableVertexAttribArray(4); 
    glVertexAttribIPointer(4, 1, GL_INT, vertexSize, (void*)(offsetof(GLRect::Vertex, axis)));

    auto rect = Rectangle(0.25f, 0.25f, 0.5f, 0.5f);
    auto vertexData = GLRect::GenVertexData(rect); 

    vertexCount += vertexData.size(); 
    glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);

    auto rectShader = Shader();
    rectShader.AttachShader(GLRect::RECT_VERTEX_SHADER, GL_VERTEX_SHADER);
    rectShader.AttachShader(GLRect::RECT_FRAG_SHADER, GL_FRAGMENT_SHADER); 
    rectShader.CompileProgram(); 

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        rectShader.Bind(); 
        glDrawArrays(GL_TRIANGLES, 0, vertexCount); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}