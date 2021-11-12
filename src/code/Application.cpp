
#include "Application.h"

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
#include "Utility/Maths.h"
#include "Utility/Types.h"
#include "Model.h"
#include "Engine.h"

#include "Networking/WebClient.h"

//#include <imgui.h>
//#include <backends/imgui_impl_sdl.h>
//#include <backends/imgui_impl_vulkan.h

Application::Application()
{
	m_Running = true;

    //Start the core engine
    m_pEngine = new Engine();

    VkExtent2D* swapChainExtent = VulkanManager::GetSwapChainExtent();
    CameraManager::CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 500.0f);

    CameraController* con = CameraManager::CreateCameraController();
    CameraManager::SetCurrentCameraController(con);

    MaterialCreateDesc createDesc{ "../bin/Assets/Shaders/flat" };
    MaterialManager::CreateNewMaterial(createDesc);

    Time::UpdateTimestep();

    //const std::string url = "www.noasoderlund.com";
    //const std::string ext = "/projects/index.html";
    const std::string url = "www.worldtimeapi.org";
    //const std::string ext = "/api/timezone/Europe/Stockholm";
    //const std::string ext = "/api/timezone/Africa/Johannesburg";
    const std::string ext = "/api/timezone/Asia/Tokyo";

    m_pWebClient = new WebClient(url);

    if (!m_pWebClient->Connect())
        std:throw("Failed to connect to web server\n");
    else
        m_pWebClient->GetHTTP(url, ext);
}

Application::~Application()
{
    if (m_pWebClient)
        delete m_pWebClient;

    delete m_pEngine;
}

void Application::Run()
{
    GLFWwindow* pWindow = WindowManager::GetWindow();

    float writeCooldown = 1.0f;
    float lerp = 0;
    float lerpValue = 0;

    glm::vec2 lastMousePos = InputManager::GetMousePosition();
    
    bool pressing1 = false;
    bool pressing4 = false;

    while (!glfwWindowShouldClose(pWindow)) {
        if (InputManager::GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }

        Time::UpdateTimestep();

        CameraManager::Update(Time::GetDeltaTime());


        if (InputManager::GetKey(GLFW_KEY_1) && !pressing1 || InputManager::GetKey(GLFW_KEY_2))
        {
            pressing1 = true;
            //Model* model = ModelManager::CreateModel(MODEL_CUBE_OBJ_PATH);
            Model* model = ModelManager::CreateModel(MODEL_ICOSPHERE_FBX_PATH);
            Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
            model->TranslateWorld(move);

            MaterialManager::GetMaterials()[0]->AddModel(model);
        }
        if (InputManager::GetKey(GLFW_KEY_1) == 0)
        {
            pressing1 = false;
        }
        if (InputManager::GetKey(GLFW_KEY_4) && !pressing4)
        {
            pressing4 = true;
            Model* model = ModelManager::CreateModel(MODEL_ICOSPHERE_FBX_PATH);
            Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
            model->TranslateWorld(move);

            MaterialManager::GetMaterials()[1]->AddModel(model);
        }
        if (InputManager::GetKey(GLFW_KEY_4) == 0)
        {
            pressing4 = false;
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

        glfwPollEvents();
        //pModel->Render();
        VulkanManager::DrawFrame(Time::GetDeltaTime());
    }

    vkDeviceWaitIdle(*VulkanManager::GetDevice());
}

void Application::CloseApplication()
{
    m_Running = false;
}