#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cout << "failed to initialize GLFW" << std::endl;
        return -1; 
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, window!", NULL, NULL);
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

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}