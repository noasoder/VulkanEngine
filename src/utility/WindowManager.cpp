
#include "WindowManager.h"

#ifdef OPENGL
#include <stb_image.h>
#endif // OPENGL

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

void InitWindow(std::string windowName, int width, int height, bool useVulkan)
{
    if (!glfwInit())
    {
        printf("glfwInit() failed");
        return;
    }

    if (useVulkan)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_pWindow);

    SetWindowIcon();
}

namespace WindowManager
{
    void Init(std::string windowName, int width, int height, bool useVulkan)
    {
        InitWindow(windowName, width, height, useVulkan);
    }

    void Destroy()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    GLFWwindow* GetWindow()
    {
        return m_pWindow;
    }
}