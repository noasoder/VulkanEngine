#include "Managers/InputManager.h"
#include "Managers/WindowManager.h"

#include "Engine.h"
#include "Utility/Types.h"

InputManager::InputManager()
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(WindowManager::Instance().m_pWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetInputMode(WindowManager::Instance().m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

InputManager::~InputManager()
{

}

int InputManager::GetKey(int key)
{
    return glfwGetKey(WindowManager::Instance().m_pWindow, key);
}

const char* InputManager::GetKeyName(int key, int scancode)
{
    return glfwGetKeyName(key, scancode);
}

glm::vec2 InputManager::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(WindowManager::Instance().m_pWindow, &xpos, &ypos);

    return glm::vec2(xpos, ypos);
}