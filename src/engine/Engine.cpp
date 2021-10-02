
#include "Engine.h"
#include "Managers/VulkanManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "Managers/WindowManager.h"

Engine::Engine()
{
    m_pWindowManager = new WindowManager();
    m_pInputManager = new InputManager(this, m_pWindowManager->m_pWindow);
    m_pVulkanManager = new VulkanManager(this, m_pWindowManager->m_pWindow);
    m_pCameraManager = new CameraManager(this);
}

Engine::~Engine()
{
    delete m_pCameraManager;

    delete m_pVulkanManager;
    delete m_pInputManager;

    delete m_pWindowManager;
}

void Engine::Update()
{

}