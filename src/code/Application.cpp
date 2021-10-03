
#include "Application.h"

#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "Managers/WindowManager.h"
#include "Camera/CameraControllers/CameraController.h"
#include "Camera/Camera.h"

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Timestep.h"
#include "Utility/Maths.h"
#include "Utility/Types.h"
#include "Model.h"
#include "Engine.h"

#include "Utility/Singleton.h"

//#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <backends/imgui_impl_vulkan.h

Application::Application()
{
	m_Running = true;

    m_pEngine = new Engine();

    VkExtent2D* swapChainExtent = &m_pEngine->m_pVulkanManager->m_swapChainExtent;
    CameraManager::Instance().CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 500.0f);

    CameraController* con = CameraManager::Instance().CreateCameraController();
    CameraManager::Instance().SetCurrentCameraController(con);

    m_timestep = Timestep(0);

    UpdateTimestep();
}

Application::~Application()
{
    delete m_pEngine;
}

void Application::Run()
{
    GLFWwindow* pWindow = WindowManager::Instance().m_pWindow;
    struct std::tm start;
    std::chrono::high_resolution_clock m_clock;

    float writeCooldown = 1.0f;
    float lerp = 0;
    float lerpValue = 0;

    glm::vec2 lastMousePos = InputManager::Instance().GetMousePosition();
    
    bool pressing1 = false;
    bool pressing4 = false;

    while (!glfwWindowShouldClose(pWindow)) {
        UpdateTimestep();

        CameraManager::Instance().Update(m_timestep.GetDeltaTime());

        Vec3 newRot = Vec3();

        if (InputManager::Instance().GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }

        if (InputManager::Instance().GetKey(GLFW_KEY_Y))
            newRot = newRot + Vec3(1, 0, 0);
        if (InputManager::Instance().GetKey(GLFW_KEY_H))
            newRot = newRot + Vec3(-1, 0, 0);
        if (InputManager::Instance().GetKey(GLFW_KEY_U))
            newRot = newRot + Vec3(0, 1, 0);
        if (InputManager::Instance().GetKey(GLFW_KEY_J))
            newRot = newRot + Vec3(0, -1, 0);
        if (InputManager::Instance().GetKey(GLFW_KEY_I))
            newRot = newRot + Vec3(0, 0, 1);
        if (InputManager::Instance().GetKey(GLFW_KEY_K))
            newRot = newRot + Vec3(0, 0, -1);
        if (InputManager::Instance().GetKey(GLFW_KEY_1) && !pressing1 || InputManager::Instance().GetKey(GLFW_KEY_2))
        {
            pressing1 = true;
            Model* model = m_pEngine->m_pVulkanManager->m_pModelManager->CreateModel(MODEL_CUBE_OBJ_PATH);
            Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
            model->TranslateWorld(move);
        }
        if (InputManager::Instance().GetKey(GLFW_KEY_1) == 0)
        {
            pressing1 = false;
        }
        if (InputManager::Instance().GetKey(GLFW_KEY_4) && !pressing4)
        {
            pressing4 = true;
            std::cout << "4" << std::endl;
        }
        if (InputManager::Instance().GetKey(GLFW_KEY_4) == 0)
        {
            pressing4 = false;
        }

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
        //pModel->Render();
        m_pEngine->m_pVulkanManager->DrawFrame(m_timestep.GetDeltaTime());
    }

    vkDeviceWaitIdle(m_pEngine->m_pVulkanManager->m_device);
}

void Application::CloseApplication()
{
    m_Running = false;
}