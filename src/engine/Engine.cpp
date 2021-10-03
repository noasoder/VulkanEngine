
#include "Engine.h"
#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "Managers/WindowManager.h"

Engine::Engine()
{
    WindowManager::Init();
    InputManager::Init();
    VulkanManager::Init();
    CameraManager::Init();
}

Engine::~Engine()
{
    CameraManager::Destroy();
    VulkanManager::Destroy();
    InputManager::Destroy();
    WindowManager::Destroy();
}

void Engine::Update()
{

}