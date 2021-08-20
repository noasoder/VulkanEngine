
#include "Application.h"

#include <cmath>
#include <iostream>
#include <iomanip>

#include <chrono>
#include <cstdint>

#include "Timestep.h"

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
    cleanup();

    delete m_pVulkanManager;
}

void Application::Run()
{
    struct std::tm start;
    std::chrono::high_resolution_clock m_clock;

    double secondsTest = 0;
    
    while (!glfwWindowShouldClose(m_pWindow)) {
        glfwPollEvents();
        m_pVulkanManager->DrawFrame();

        UpdateTimestep();

        secondsTest += m_timestep.GetDeltaTime();
        std::cout << "FPS: " << m_timestep.GetFPS() << " delta: " << m_timestep.GetDeltaTime() << " time test: " << secondsTest << std::endl;
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