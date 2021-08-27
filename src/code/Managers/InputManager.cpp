#include "InputManager.h"

#include "Application.h"
#include "Utility/Types.h"

InputManager::InputManager(Application* pApplication)
: m_pApplication(pApplication)
{
    GLFWwindow* window = m_pApplication->m_pWindow;

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

InputManager::~InputManager()
{

}

int InputManager::GetKey(int key)
{
    return glfwGetKey(m_pApplication->m_pWindow, key);
}

const char* InputManager::GetKeyName(int key, int scancode)
{
    return glfwGetKeyName(key, scancode);
}

glm::vec2 InputManager::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(m_pApplication->m_pWindow, &xpos, &ypos);

    return glm::vec2(xpos, ypos);
}