
#include "Managers/WindowManager.h"
#include "Managers/VulkanManager.h"
#include "Engine.h"
#include <stb_image.h>
#include <string>

GLFWwindow* m_pWindow;

void SetWindowIcon()
{
    std::string iconPath = "Engine/Media/Icon.png";
    GLFWimage icon[1];
    icon[0].pixels = stbi_load(iconPath.c_str(), &icon[0].width, &icon[0].height, nullptr, STBI_rgb_alpha);
    glfwSetWindowIcon(m_pWindow, 1, icon);
    stbi_image_free(icon[0].pixels);
}

void InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);

    SetWindowIcon();

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