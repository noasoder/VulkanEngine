#include "Vulkan.h"

#define ENGINE_NAME "VulkanEngine"
#define PROJECT_NAME "VulkanEngine"

class VulkanManager;
class InputManager;
class CameraManager;
class WindowManager;

class Engine
{
public:
    Engine();
    ~Engine();

    void Update();

    VulkanManager* m_pVulkanManager;
private:

};