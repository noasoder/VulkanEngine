
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
    m_pVulkanManager = new VulkanManager(this, WindowManager::Instance().m_pWindow);
    CameraManager::Init();
}

Engine::~Engine()
{
    CameraManager::Destroy();
    delete m_pVulkanManager;

    InputManager::Destroy();
    WindowManager::Destroy();
}

void Engine::Update()
{

}