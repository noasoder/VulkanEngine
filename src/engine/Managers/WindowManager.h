#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Vulkan.h"

#define WIDTH 800
#define HEIGHT 600

namespace WindowManager
{
    void Init();
    void Destroy();

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* GetWindow();
}

#endif // !WINDOW_MANAGER_H