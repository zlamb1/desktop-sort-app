#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // in pixels
        auto borderSize = 10.0f; 

        auto borderWidth = borderSize / fbWidth;
        auto borderLeft = -(1 - borderWidth);
        auto borderRight = 1 - borderWidth;

        auto borderHeight = borderSize / fbHeight;
        auto borderTop = -(1 - borderHeight);
        auto borderBottom = 1 - borderHeight;

        glColor3f(1.0f, 1.0f, 1.0f);
        glRectf(-1.0f, -1.0f, 1.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(borderLeft, borderTop, borderRight, borderBottom);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}