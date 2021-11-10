
#include "Managers/WindowManager.h"
#include "Managers/VulkanManager.h"
#include "Engine.h"

GLFWwindow* m_pWindow;

void InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
    //glfwSetWindowUserPointer(m_pWindow, this);
    glfwSetFramebufferSizeCallback(m_pWindow, WindowManager::FramebufferResizeCallback);
}

namespace WindowManager
{
    void Init()
    {
        InitWindow();
    }

    void Destroy()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
    void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
    {
        VulkanManager::SetFrameBufferResized(true);
    }

    GLFWwindow* GetWindow()
    {
        return m_pWindow;
    }
}