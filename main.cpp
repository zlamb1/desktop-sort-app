#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rect.h"
#include "shader.h"

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
    if (!window)
    {
        std::cout << "failed to initialize GLFW window" << std::endl;
        return -1; 
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    
    glfwSetFramebufferSizeCallback(window, onFramebufferResize);

    uint32_t vbo, program, vertexCount;
    glGenBuffers(1, &vbo);  
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float))); 

    auto rectShader = Shader();
    rectShader.AttachShader(RECT_VERTEX_SHADER, GL_VERTEX_SHADER);
    rectShader.AttachShader(RECT_FRAG_SHADER, GL_FRAGMENT_SHADER); 
    rectShader.CompileProgram(); 

    auto rect = Rectangle(0.25f, 0.25f, 0.5f, 0.5f);
    rect.BufferData(); 

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        rectShader.Bind(); 
        glDrawArrays(GL_TRIANGLES, 0, 6); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}