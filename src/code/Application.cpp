
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
//#include <backends/imgui_impl_Core.h

Application::Application()
{
    //Start the core engine
    m_pEngine = new Engine();

    //VkExtent2D* swapChainExtent = VulkanManager::GetSwapChainExtent();
    //CameraManager::CreateCamera(Vec3(0, -5, 2), Vec3(0, 1, 0), 45, swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 500.0f);

    //CameraController* con = CameraManager::CreateCameraController();
    //CameraManager::SetCurrentCameraController(con);

    //MaterialCreateDesc createDesc{ "../bin/Assets/Shaders/flat" };
    //MaterialManager::CreateNewMaterial(createDesc);

    //Time::UpdateTimestep();

    //m_pNetHandler = new NetHandler();
}

Application::~Application()
{
    if (m_pNetHandler)
        delete m_pNetHandler;

    if(m_pEngine)
        delete m_pEngine;
}

void Application::Run()
{
    GLFWwindow* pWindow = WindowManager::GetWindow();

    //glm::vec2 lastMousePos = InputManager::GetMousePosition();
    float writeCooldown = 0;

    while (!glfwWindowShouldClose(pWindow)) {
        if (InputManager::GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //shutdown application
            break;
        }

        Time::UpdateTimestep();

        //CameraManager::Update(Time::GetDeltaTime());
        //m_pNetHandler->Update();


        //if (InputManager::GetKeyDown(GLFW_KEY_1) || InputManager::GetKey(GLFW_KEY_2))
        //{
        //    //Model* model = ModelManager::CreateModel(MODEL_CUBE_OBJ_PATH);
        //    Model* model = ModelManager::CreateModel(MODEL_ICOSPHERE_FBX_PATH);
        //    Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
        //    model->TranslateWorld(move);

        //    MaterialManager::GetMaterials()[0]->AddModel(model);
        //}

        //if (InputManager::GetKeyDown(GLFW_KEY_4))
        //{
        //    Model* model = ModelManager::CreateModel(MODEL_ICOSPHERE_FBX_PATH);
        //    Vec3 move = Vec3(Random(-5.0f, 5.0f), Random(-5.0f, 5.0f), Random(-5.0f, 5.0f));
        //    model->TranslateWorld(move);

        //    MaterialManager::GetMaterials()[1]->AddModel(model);
        //}

        if (writeCooldown > 0.0f)
        {
            writeCooldown -= Time::GetDeltaTime();
        }
        else
        {
            std::cout << "FPS: " << Time::GetFPS() << " delta: " << Time::GetDeltaTime() << std::endl;
            writeCooldown = 1.0f;
        }
        InputManager::Update();

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.0f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(WindowManager::GetWindow());
        glfwPollEvents();

        //VulkanManager::DrawFrame(Time::GetDeltaTime());
    }

    //vkDeviceWaitIdle(*VulkanManager::GetDevice());
}

