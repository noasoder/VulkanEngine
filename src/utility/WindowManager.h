#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GLFW/glfw3.h>
#include <string>

namespace WindowManager
{
    void Init(std::string windowName, int width, int height, bool useVulkan = true);
    void Destroy();

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* GetWindow();
}

#endif // !WINDOW_MANAGER_H