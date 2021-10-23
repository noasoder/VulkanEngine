
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

//#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <backends/imgui_impl_vulkan.h

Application::Application()
{
	m_Running = true;

    m_pEngine = new Engine();

    VkExtent2D* swapChainExtent = &VulkanManager::Instance().m_swapChainExtent;
    CameraManager::Instance().CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 500.0f);

    CameraController* con = CameraManager::Instance().CreateCameraController();
    CameraManager::Instance().SetCurrentCameraController(con);

    Timestep::Init();
    Timestep::Instance().UpdateTimestep();
}

Application::~Application()
{
    delete m_pEngine;

    Timestep::Destroy();
}

void Application::Run()
{
    GLFWwindow* pWindow = WindowManager::Instance().m_pWindow;

    float writeCooldown = 1.0f;
    float lerp = 0;
    float lerpValue = 0;

    glm::vec2 lastMousePos = InputManager::Instance().GetMousePosition();
    
    bool pressing1 = false;
    bool pressing4 = false;

    while (!glfwWindowShouldClose(pWindow)) {
        if (InputManager::Instance().GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }

        Timestep::Instance().UpdateTimestep();

        CameraManager::Instance().Update(Timestep::Instance().GetDeltaTime());


        if (InputManager::Instance().GetKey(GLFW_KEY_1) && !pressing1 || InputManager::Instance().GetKey(GLFW_KEY_2))
        {
            pressing1 = true;
            //Model* model = ModelManager::Instance().CreateModel(MODEL_CUBE_OBJ_PATH);
            Model* model = ModelManager::Instance().CreateModel(MODEL_ICOSPHERE_FBX_PATH);
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
            lerpValue += Timestep::Instance().GetDeltaTime();
        //std::cout << "lerpValue: " << lerpValue << " lerp: " << lerp << std::endl;
        lerp = cos(lerpValue);


        if (writeCooldown > 0.0f)
        {
            writeCooldown -= Timestep::Instance().GetDeltaTime();
        }
        else
        {
            //std::cout << "FPS: " << Timestep::Instance().GetFPS() << " delta: " << Timestep::Instance().GetDeltaTime() << std::endl;
            writeCooldown = 1.0f;
        }

        glfwPollEvents();
        //pModel->Render();
        VulkanManager::Instance().DrawFrame(Timestep::Instance().GetDeltaTime());
    }

    vkDeviceWaitIdle(VulkanManager::Instance().m_device);
}

void Application::CloseApplication()
{
    m_Running = false;
}