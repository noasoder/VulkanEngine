
#include "Application.h"

#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/Camera.h"

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Timestep.h"
#include "Utility/Maths.h"
#include "Utility/Types.h"



Application::Application()
{
	m_Running = true;

    InitWindow();

    m_pInputManager = new InputManager(this);
    m_pVulkanManager = new VulkanManager(this);
    m_pCameraManager = new CameraManager(this);

    VkExtent2D* swapChainExtent = &m_pVulkanManager->m_swapChainExtent;

    m_pCameraManager->CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height);

    m_timestep = Timestep(0);

    UpdateTimestep();
}

Application::~Application()
{
    delete m_pCameraManager;

    delete m_pVulkanManager;
    delete m_pInputManager;

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

    float movSpeed = 25;
    Vec3 pos = Vec3(0, -10, 0);

    while (!glfwWindowShouldClose(m_pWindow)) {
        UpdateTimestep();
        Vec3 moveRDB = Vec3();
        Vec3 moveLUF = Vec3();


        if (m_pInputManager->GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }


        if (m_pInputManager->GetKey(GLFW_KEY_W))
            moveLUF = moveLUF + Vec3(0, 1, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_A))
            moveLUF = moveLUF + Vec3(-1, 0, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_S))
            moveRDB = moveRDB + Vec3(0, -1, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_D))
            moveRDB = moveRDB + Vec3(1, 0, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_E))
            moveLUF = moveRDB + Vec3(0, 0, 1);
        if (m_pInputManager->GetKey(GLFW_KEY_Q))
            moveRDB = moveRDB + Vec3(0, 0, -1);

        pos = pos + (moveLUF + moveRDB) * movSpeed * m_timestep.GetDeltaTime();

        Camera* currCamera = m_pCameraManager->GetCurrentCamera();
        currCamera->Translate(pos);
        //printf("move: X: %f Y: %f Z: %f\n", currCamera->GetPos().x, currCamera->GetPos().y, currCamera->GetPos().z);


        Vec2 pos = m_pInputManager->GetMousePosition();
        //printf("Mouse: X: %f Y: %f\n", pos.x, pos.y);

        
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
        m_pVulkanManager->DrawFrame(m_timestep.GetDeltaTime());
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

void Application::FramebufferResizeCallback(GLFWwindow* window, int width, int height) 
{
    auto app = reinterpret_cast<VulkanManager*>(glfwGetWindowUserPointer(window));
    app->m_framebufferResized = true;
}