
#include "Engine.h"


#ifdef OPENGL
#include "Managers/GLManager.h"
#endif // OPENGL

#ifdef VULKAN
#include "Managers/VulkanManager.h"
#endif // VULKAN

#include "InputManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ModelManager.h"
#include "WindowManager.h"

Engine::Engine()
{
    WindowManager::Init(PROJECT_NAME, WIDTH, HEIGHT);
    InputManager::Init();
    
#ifdef OPENGL
    GLManager::Init();
#endif // OPENGL

#ifdef VULKAN
    glfwSetFramebufferSizeCallback(WindowManager::GetWindow(), [](GLFWwindow* window, int width, int height) { VulkanManager::SetFrameBufferResized(true); });

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