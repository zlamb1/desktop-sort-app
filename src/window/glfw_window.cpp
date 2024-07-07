#include "glfw_window.hpp"

#include <assert.h>

GLFWWindowWrapper::GLFWWindowWrapper(std::string title, int32_t width, int32_t height) 
{
    m_Hnd = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    assert(m_Hnd); 
    glfwMakeContextCurrent(m_Hnd); 
}

GLFWWindowWrapper::~GLFWWindowWrapper()
{
    if (m_Hnd) glfwDestroyWindow(m_Hnd); 
}

bool GLFWWindowWrapper::IsRunning() 
{
    return !glfwWindowShouldClose(m_Hnd); 
}

void GLFWWindowWrapper::OnFrame() 
{
    glfwSwapBuffers(m_Hnd); 
    glfwPollEvents(); 
}

void GLFWWindowWrapper::OnFramebufferResize(GLFWwindow* window, int width, int height)
{
    GLFWWindowWrapper* ptr = (GLFWWindowWrapper*)glfwGetWindowUserPointer(window); 
    ptr->SetFramebufferSize({ width, height }); 
    ptr->m_FramebufferSizeDirty = true; 
}