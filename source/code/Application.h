#pragma once 

#include "Vulkan.h"

#include <chrono>
#include <cstdint>

#include "Timestep.h"
#include "Utility/Maths.h"

class VulkanManager;
class InputManager;
class CameraManager;

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

class Application
{
public:
    Application();
    ~Application();
    void Run();
    void CloseApplication();

    void InitWindow();

    void mainLoop() {

    }

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

    void UpdateTimestep() {
        std::chrono::high_resolution_clock m_clock;
        double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

        double time = nanoSec / BILLION;

        m_timestep.SetTimestep(time - m_LastFrameTime);

        m_LastFrameTime = time;
    }
    VulkanManager* m_pVulkanManager;
    InputManager* m_pInputManager;
    CameraManager* m_pCameraManager;

    GLFWwindow* m_pWindow;

private:
    bool m_Running;
    double m_LastFrameTime;

    Timestep m_timestep;
};
