#pragma once 

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>

#include "VulkanManager.h"
#include "Timestep.h"

#include <chrono>
#include <cstdint>


#define BILLION  1000000000L;
#define MILLION  1000000;

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class Application
{
public:
    Application();
    ~Application();
    void Run();
    void CloseApplication();

    VulkanManager* m_pVulkanManager;

    GLFWwindow* m_pWindow;

    void InitWindow();

    void mainLoop() {

    }

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<VulkanManager*>(glfwGetWindowUserPointer(window));
        app->m_framebufferResized = true;
    }

    void UpdateTimestep() {
        std::chrono::high_resolution_clock m_clock;
        double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

        double time = nanoSec / BILLION;

        m_timestep.SetTimestep(time - m_LastFrameTime);

        m_LastFrameTime = time;
    }

private:
    bool m_Running;
    double m_LastFrameTime;

    Timestep m_timestep;
};
