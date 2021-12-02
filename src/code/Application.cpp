
#include "Application.h"

#include "Networking/NetHandler.h"

#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "Managers/WindowManager.h"
#include "Managers/MaterialManager.h"
#include "Camera/CameraControllers/CameraController.h"
#include "Camera/Camera.h"

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Timestep.h"
#include "Maths.h"
#include "Types.h"
#include "Model.h"
#include "Engine.h"

//#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <backends/imgui_impl_vulkan.h

Application::Application()
{
    //Start the core engine
    m_pEngine = new Engine();

    VkExtent2D* swapChainExtent = VulkanManager::GetSwapChainExtent();
    CameraManager::CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 500.0f);

    CameraController* con = CameraManager::CreateCameraController();
    CameraManager::SetCurrentCameraController(con);

    MaterialCreateDesc createDesc{ "../bin/Assets/Shaders/flat" };
    MaterialManager::CreateNewMaterial(createDesc);

    Time::UpdateTimestep();

    m_pNetHandler = new NetHandler();
}

Application::~Application()
{
    if (m_pNetHandler)
        delete m_pNetHandler;

    delete m_pEngine;
}

void Application::Run()
{
    GLFWwindow* pWindow = WindowManager::GetWindow();

    float writeCooldown = 1.0f;
    float lerp = 0;
    float lerpValue = 0;

    glm::vec2 lastMousePos = InputManager::GetMousePosition();

    while (!glfwWindowShouldClose(pWindow)) {
        if (InputManager::GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }

        Time::UpdateTimestep();

        m_pNetHandler->Update();
        CameraManager::Update(Time::GetDeltaTime());


        if (InputManager::GetKeyDown(GLFW_KEY_1) || InputManager::GetKey(GLFW_KEY_2))
        {
            //Model* model = ModelManager::CreateModel(MODEL_CUBE_OBJ_PATH);
            Model* model = ModelManager::CreateModel(MODEL_ICOSPHERE_FBX_PATH);
            Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
            model->TranslateWorld(move);

            MaterialManager::GetMaterials()[0]->AddModel(model);
        }

        if (InputManager::GetKeyDown(GLFW_KEY_4))
        {
            Model* model = ModelManager::CreateModel(MODEL_ICOSPHERE_FBX_PATH);
            Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
            model->TranslateWorld(move);

            MaterialManager::GetMaterials()[1]->AddModel(model);
        }

        if (lerpValue > TWO_PI)
            lerpValue -= TWO_PI;
        else
            lerpValue += Time::GetDeltaTime();
        //std::cout << "lerpValue: " << lerpValue << " lerp: " << lerp << std::endl;
        lerp = cos(lerpValue);


        if (writeCooldown > 0.0f)
        {
            writeCooldown -= Time::GetDeltaTime();
        }
        else
        {
            //std::cout << "FPS: " << Timestep::Instance().GetFPS() << " delta: " << Timestep::Instance().GetDeltaTime() << std::endl;
            writeCooldown = 1.0f;
        }

        InputManager::Update();
        glfwPollEvents();

        VulkanManager::DrawFrame(Time::GetDeltaTime());
    }

    vkDeviceWaitIdle(*VulkanManager::GetDevice());
}