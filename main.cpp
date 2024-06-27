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

    Rectangle rect{};

    uint32_t vbo, program, vertexCount;
    glGenBuffers(1, &vbo);  
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    const float data[] = {
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float))); 

    Shader rectangleShader(RECT_VERTEX_SHADER, RECT_FRAG_SHADER);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        rectangleShader.Bind(); 
        glDrawArrays(GL_TRIANGLES, 0, 3); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}