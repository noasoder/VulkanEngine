
#include "Engine.h"


#ifdef OPENGL
#include "Managers/GLManager.h"
#endif // OPENGL

#ifdef VULKAN
#include "Managers/VulkanManager.h"
#endif // VULKAN

#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "Managers/WindowManager.h"

Engine::Engine()
{
    WindowManager::Init();
    InputManager::Init();
    
#ifdef OPENGL
    GLManager::Init();
#endif // OPENGL

#ifdef VULKAN
    VulkanManager::Init();
#endif // VULKAN

    CameraManager::Init();
}

Engine::~Engine()
{
    CameraManager::Destroy();

#ifdef OPENGL
    GLManager::Destroy();
#endif // OPENGL

#ifdef VULKAN
    //VulkanManager::Destroy();
#endif // VULKAN

    InputManager::Destroy();
    WindowManager::Destroy();
}

void Engine::Update()
{

}