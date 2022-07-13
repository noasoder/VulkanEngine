
#include "Managers/WindowManager.h"

#ifdef VULKAN
#include "Managers/VulkanManager.h"
#endif // VULKAN

#ifdef OPENGL
#include <stb_image.h>
#endif // OPENGL

#include "Engine.h"
#include <string>

GLFWwindow* m_pWindow;

void SetWindowIcon()
{
    #ifdef OPENGL
    std::string iconPath = "Engine/Media/Icon.png";
    GLFWimage icon[1];
    icon[0].pixels = stbi_load(iconPath.c_str(), &icon[0].width, &icon[0].height, nullptr, STBI_rgb_alpha);
    glfwSetWindowIcon(m_pWindow, 1, icon);
    stbi_image_free(icon[0].pixels);
    #endif // OPENGL
}

void InitWindow()
{
    if (!glfwInit())
    {
        printf("glfwInit() failed");
        return;
    }

#ifdef VULKAN
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif // VULKAN

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);

    glfwMakeContextCurrent(m_pWindow);

    SetWindowIcon();

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
#ifdef VULKAN
        VulkanManager::SetFrameBufferResized(true);
#endif // VULKAN
    }

    GLFWwindow* GetWindow()
    {
        return m_pWindow;
    }
}