#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Core.h"

#define WIDTH 1280
#define HEIGHT 720

namespace WindowManager
{
    void Init();
    void Destroy();

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* GetWindow();
}

#endif // !WINDOW_MANAGER_H