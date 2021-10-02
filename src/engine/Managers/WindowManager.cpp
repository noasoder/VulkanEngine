
#include "WindowManager.h"
#include "Managers/VulkanManager.h"
#include "Engine.h"

WindowManager::WindowManager()
{
    InitWindow();
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void WindowManager::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
    glfwSetWindowUserPointer(m_pWindow, this);
    glfwSetFramebufferSizeCallback(m_pWindow, FramebufferResizeCallback);
}

void WindowManager::FramebufferResizeCallback(GLFWwindow* window, int width, int height) 
{
    auto app = reinterpret_cast<VulkanManager*>(glfwGetWindowUserPointer(window));
    app->m_framebufferResized = true;
}