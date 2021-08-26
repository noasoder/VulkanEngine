
#include "Application.h"

#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Camera/CameraControllers/CameraController.h"
#include "Camera/Camera.h"

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Timestep.h"
#include "Utility/Maths.h"
#include "Utility/Types.h"

//#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <backends/imgui_impl_vulkan.h>


Application::Application()
{
	m_Running = true;

    InitWindow();

    m_pInputManager = new InputManager(this);
    m_pVulkanManager = new VulkanManager(this);
    m_pCameraManager = new CameraManager(this);

    VkExtent2D* swapChainExtent = &m_pVulkanManager->m_swapChainExtent;

    m_pCameraManager->CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 500.0f);

    CameraController* con = m_pCameraManager->CreateCameraController(this);
    m_pCameraManager->SetCurrentCameraController(con);

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

    Matrix4 mat = Matrix4();
    Vec2 lastMousePos = m_pInputManager->GetMousePosition();
    
    while (!glfwWindowShouldClose(m_pWindow)) {
        UpdateTimestep();

        m_pCameraManager->Update(m_timestep.GetDeltaTime());

        Vec3 newRot = Vec3();

        if (m_pInputManager->GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }

        if (m_pInputManager->GetKey(GLFW_KEY_Y))
            newRot = newRot + Vec3(1, 0, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_H))
            newRot = newRot + Vec3(-1, 0, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_U))
            newRot = newRot + Vec3(0, 1, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_J))
            newRot = newRot + Vec3(0, -1, 0);
        if (m_pInputManager->GetKey(GLFW_KEY_I))
            newRot = newRot + Vec3(0, 0, 1);
        if (m_pInputManager->GetKey(GLFW_KEY_K))
            newRot = newRot + Vec3(0, 0, -1);
        

        newRot = newRot * m_timestep.GetDeltaTime();

        //Rotor3 rotor = Rotor3(10, 0, 1, 0);

        //Vec3 rot = rotor.rotate(Vec3(PI, 0, 0));
        //
        //printf("\nL: %f, %f, %f, %f\n", mat.m0.x, mat.m0.y, mat.m0.z, mat.m0.z);
        //printf("U: %f, %f, %f, %f\n", mat.m1.x, mat.m1.y, mat.m1.z, mat.m1.z);
        //printf("A: %f, %f, %f, %f\n", mat.m2.x, mat.m2.y, mat.m2.z, mat.m2.z);
        //mat = mat.Rotate(newRot);

        
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