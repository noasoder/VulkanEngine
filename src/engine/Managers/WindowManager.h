#include "Vulkan.h"
#include "Utility/Singleton.h"

#define WIDTH 800
#define HEIGHT 600

class WindowManager : public Singleton<WindowManager>
{
public:
    WindowManager();
    ~WindowManager();

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* m_pWindow;

private:
    void InitWindow();
};