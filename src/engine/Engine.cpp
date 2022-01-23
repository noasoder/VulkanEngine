
#include "Engine.h"
#include "Managers/GLManager.h"
//#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "Managers/WindowManager.h"

Engine::Engine()
{
    WindowManager::Init();
    InputManager::Init();
    
    GLManager::Init();
    //VulkanManager::Init();

    CameraManager::Init();
}

Engine::~Engine()
{
    CameraManager::Destroy();

    GLManager::Destroy();
    //VulkanManager::Destroy();

    InputManager::Destroy();
    WindowManager::Destroy();
}

void Engine::Update()
{

}