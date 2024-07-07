#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

class GLFWWindowWrapper : public WindowWrapper {

    public:
        GLFWWindowWrapper(std::string title, int32_t width, int32_t height); 
        ~GLFWWindowWrapper(); 

        bool IsRunning() override; 
        void OnFrame() override; 
    
    private:
        GLFWwindow* m_Hnd = nullptr; 

        // GLFW callback functions
        static void OnFramebufferResize(GLFWwindow* window, int width, int height); 

};