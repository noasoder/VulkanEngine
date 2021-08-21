
#include "Application.h"

#include <cmath>
#include <iostream>
#include <iomanip>

#include <chrono>
#include <cstdint>

#include "Timestep.h"
#include "math.h"

Application::Application()
{
	m_Running = true;

    InitWindow();

    m_pVulkanManager = new VulkanManager(m_pWindow);

    m_timestep = Timestep(0);

    UpdateTimestep();
}

Application::~Application()
{
    m_pVulkanManager->Cleanup();

    delete m_pVulkanManager;

    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void Application::Run()
{
    struct std::tm start;
    std::chrono::high_resolution_clock m_clock;

    float writeCooldown = 1.0f;
    float lerp = 0;
    float lerpValue = 0;
    while (!glfwWindowShouldClose(m_pWindow)) {
        UpdateTimestep();
        
        if (lerpValue > TWO_PI)
            lerpValue -= TWO_PI;
        else
            lerpValue += m_timestep.GetDeltaTime();
        //std::cout << "lerpValue: " << lerpValue << " lerp: " << lerp << std::endl;
        lerp = cos(lerpValue);


        if (writeCooldown > 0.0f)
        {
            writeCooldown -= m_timestep.GetDeltaTime();
        }
        else
        {
            std::cout << "FPS: " << m_timestep.GetFPS() << " delta: " << m_timestep.GetDeltaTime() << std::endl;
            writeCooldown = 1.0f;
        }
        

        glfwPollEvents();
        m_pVulkanManager->DrawFrame();
    }

    vkDeviceWaitIdle(m_pVulkanManager->m_device);
}

void Application::CloseApplication()
{
    m_Running = false;
}

void Application::InitWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
    glfwSetWindowUserPointer(m_pWindow, this);
    glfwSetFramebufferSizeCallback(m_pWindow, FramebufferResizeCallback);
}